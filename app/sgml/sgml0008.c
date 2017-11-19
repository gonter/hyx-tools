/*
 *  FILE ~/usr/sgml/sgml0008.c
 *
 *  written:       1990 10 01
 *  latest update: 1999-04-25 16:40:28
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/sgml.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
static struct SGML_LIST *segments= (struct SGML_SEGMENT *) 0;
static struct SGML_LIST **append_segments= &segments;
static struct SGML_LIST *actual_frame= (struct SGML_SEGMENT *) 0;

/* ------------------------------------------------------------------------ */
static int processor_code= 1;
static int italic_correction= 0;
static int process_data= 1;             /* Daten ausgeben                   */

/* ------------------------------------------------------------------------ */
static int paragraph_depth= 0;          /* Zahl der offenen paragraphs      */
static int hervorhebung_depth= 0;       /* Zahl der offenen hervorhebungen  */
static int formel_depth= 0;
static int gleichung_depth= 0;
static int definition_depth= 0;
static int verbatim_depth= 0;
static int inhibit_hyphenation= 0;
static int inhibit_hyphenation2= 0;
static int errors_in_frame= 0;
static int slanted= 0;
static int math_mode= 0;                /* 1 -> 'billiges' math             */
                                        /* 2 -> 'teures' math               */

static int quote_type= 0;               /* 1 -> english double quotes       */
                                        /* 2 -> german double quotes        */
static int quote_depth= 0;
static int quote_stack[10]; /* #### */

static int note_type= 0;                /* 1 -> footnote                    */

static int typographic_type= 0;         /* 1 -> ty=legato                   */
                                        /*      Bindestrich                 */
                                        /* 2 -> ty=cont(inuation)           */
                                        /*      'Fortsetzungsstich'         */
                                        /* 3 -> ty=dash                     */
                                        /*      Gedankenstrich              */
                                        /* 4 -> ty=hyphen                   */
                                        /*      moegliche Abteilungsposition*/
                                        /* 5 -> ty=space                    */
                                        /*      Unteilbarer Zwischenraum    */

/* prototypes: ------------------------------------------------------------ */
/* global: void sgml_transmit_2segment (void *segment);                     */
/* global: void flush_segments (void);                                      */
static process_segments (void *segment, int level);
static void process_1segment (void *segment, int level);
static void print_tag_sequence (struct SGML_LIST *sl, int mode);
static int process_tag_sequence (struct SGML_LIST *tl);
static void report_tagging_error (struct SGML_LIST *tl,
  char *message, int p1);

/* ------------------------------------------------------------------------ */
/* SGML List Segment uebernehmen, und am Ende eines Frames das              */
/* Verarbeiten (flushen) der bisherigen Liste ausloesen.                    */
void sgml_transmit_2segment (void *segment)
{
  struct SGML_LIST *nl;
  struct SGML_TAG  *tg;

  if (segment == (void *) 0) return;
  nl = (struct SGML_LIST *) calloc (sizeof (struct SGML_LIST), 1);
  nl->sig= SIG_LIST;
  nl->car = segment;
  nl->cdr = (void *) 0;
  *append_segments=nl;
   append_segments = &(nl->cdr);

  if (((struct SGML_LIST *) segment)->sig == SIG_LIST)
  {
    tg = (struct SGML_TAG *) ((struct SGML_LIST *) segment)->car;
    if (tg->sig == SIG_TAG)
    {
      if (tg->sgml_tag_id == SGML_TAG_endframe
          || tg->sgml_tag_id == SGML_TAG_Sendframe)
      { /* make output every time, when a frame ends ... */
        flush_segments ();
      }
    }
  }
}

/* ------------------------------------------------------------------------ */
void flush_segments ()
{
  printf ("*** flush segments ***\n");
  process_segments (segments, 1);
  free_tag_list (segments);
  segments=(struct SGML_SEGMENT *) 0;
  append_segments= &segments;
}

/* ------------------------------------------------------------------------ */
static process_segments (void *segment, int level)
{
  struct SGML_LIST *sl;

  if (segment == (void *) 0)
  {
    printf ("*** segment list empty ***\n");
    return;
  }
  sl = segment;
AGAIN:
  process_1segment (sl, level);

  if (sl->sig==SIG_LIST)
  {
    if (((struct SGML_TAG *) sl->car)->sig == SIG_TAG)
         { /* Process Tag and his parameters */
           process_tag_sequence (sl);
         }
    else { /* process this list */
           process_segments (sl->car, level+1);
           sl = sl->cdr;
           if (sl != (struct SGML_LIST *) 0) goto AGAIN;
         }
  }
}

/* ------------------------------------------------------------------------ */
static void process_1segment (void *segment, int level)
{
  struct SGML_LIST *sl;
  struct SGML_INFO_BYTE *sib;
  struct SGML_TAG *st;
  int mode;

  sl = segment;
  /* printf ("segment (%d) 0x%02X\n", level, sl->sig); */

  if (sl->sig==SIG_INFO_BYTE && process_data)
  { /* send information block to the output;                                */
    /* tex-symbols must be processed, if we are not in verbatim-mode !!!    */
    sib = segment;
    mode  = (verbatim_depth>0)    ? 0x00 : 0x01;
    mode |= (inhibit_hyphenation) ? 0x02 : 0x00;
    if (italic_correction)
    {
      mode |= 0x04;
      italic_correction= 0;
    }
    sgml_data_block (processor_code, mode, sib->info, sib->size);
  }
  if (sl->sig==SIG_TAG)
  {
    st = segment;
    printf ("* TAG %s\n", st->sgml_tag_name);
    dump (stdout, st, sizeof (struct SGML_TAG));
  }
  if (sl->sig==SIG_PARAMETER)
  {
    printf ("* PARAMETER\n");
    sib = segment;
    dump (stdout, sib, sib->size+4);
  }
}

/* ------------------------------------------------------------------------ */
static void print_tag_sequence (struct SGML_LIST *sl, int mode)
/* mode: bit 0: output full tag information                     */
/*       bit 1: send output to the information stream,          */
/*              otherwise send it to stdout                     */
/*       bit 2: the tag sequence must be processed for TeX      */
{
  struct SGML_TAG       *st;
  struct SGML_INFO_BYTE *sp;
  int done=0;
  int i;
  char *cp;
  int quoted;

  for (; sl != (void *) 0 && sl->sig == SIG_LIST; sl=sl->cdr)
  {
    st = sl->car;
    if ((mode & 0x01) && st->sig==SIG_TAG)
    {
      printf ("<%s", st->sgml_tag_name);
      done=1;
    }
    sp=sl->car;
    if (sp->sig==SIG_PARAMETER)
    {
      if (mode & 0x02)
           {
             if (done) sgml_data_byte (SGML_PROC_verbatim, 0x00, ' ');
             sgml_data_block ((mode & 0x04) ? processor_code 
                                            : SGML_PROC_verbatim, 
                              (mode & 0x04) ? 0x01 
                                            : 0x00,
                              sp->info, sp->size);
           }
      else {
             if (done) fputc (' ', stdout);
             cp=sp->info;
             for (i=sp->size; i > 0; i--) fputc (*cp++, stdout);
           }
      done=1;
    }
  }
  if (done && (mode & 0x01)) printf (">\n");
}

/* ------------------------------------------------------------------------ */
static int process_tag_sequence (struct SGML_LIST *tl)
{
  struct SGML_TAG *tag;
  struct SGML_INFO_BYTE *par;
  struct SGML_LIST *tl2;
  int title_type;

  if (tl == (void *) 0) return 0;

  tag= tl->car;
  if (tag->sig != SIG_TAG) return -1;

  switch (tag->sgml_tag_id)
  {
    case SGML_TAG_frame:        /* frame tags are deleted here */
    case SGML_TAG_Sframe:
      actual_frame = tl;
      errors_in_frame=0;
      /* ausgabe des Frame names als TeX Makro, fuer debugging ... */
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\framemark{", 11);
      print_tag_sequence (tl, 0x06);    /* Frame tag sequence must be   */
                                        /* prepared for use with TeX    */
      sgml_data_byte (SGML_PROC_verbatim, 0x00, '}');
      break;
    case SGML_TAG_endframe:
    case SGML_TAG_Sendframe:
      if (errors_in_frame > 0)
         printf ("*** %d errors here!\n\n", errors_in_frame);
      actual_frame = (void *) 0;
      break;
    case SGML_TAG_paragraph:
      if (++paragraph_depth != 1)
         report_tagging_error (tl, "* Error %d paragraphs are open after ",
                               paragraph_depth);
      break;
    case SGML_TAG_endparagraph:
      if (--paragraph_depth != 0)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d paragraphs are open after ", paragraph_depth);
        print_tag_sequence (tl, 0x01);
      }
      sgml_data_byte (SGML_PROC_verbatim, 0x00, '\n');
      break;
    case SGML_TAG_Titel:
      if (!process_data) break;
      title_type=-1;
      if (tl->cdr != (void *) 0)
      {
        par= tl->cdr->car;
        if (par->sig == SIG_PARAMETER)
        {
          if (strncmp (par->info, "K",1) == 0) title_type=1;
          if (strncmp (par->info, "A",1) == 0) title_type=2;
          if (strncmp (par->info, "B",1) == 0) title_type=3;
          if (strncmp (par->info, "C",1) == 0) title_type=4;
          if (strncmp (par->info, "D",1) == 0) title_type=5;
          if (strncmp (par->info, "E",1) == 0) title_type=6;
        }
      }
      switch (title_type)
      {
        case 1:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\chapter{", 9);
          break;
        case 2:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\section{", 9);
          break;
        case 3:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\subsection{", 12);
          break;
        case 4:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\subsubsection{", 15);
          break;
        case 5:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\paragraph{", 11);
          break;
        case 6:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\subparagraph{", 14);
          break;
        default:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\subparagraph{(??) ", 19);
          break;
      }
      inhibit_hyphenation2 = inhibit_hyphenation;
      inhibit_hyphenation = 1;
      processor_code = SGML_PROC_text;
      /* processor_code = SGML_PROC_title_1; */
      /* processor_code = SGML_PROC_title_2; */
      break;
    case SGML_TAG_endTitel:
      if (!process_data) break;
      inhibit_hyphenation = inhibit_hyphenation2;
      switch (processor_code)
      {
        case SGML_PROC_text:
          sgml_data_byte (SGML_PROC_verbatim, 0x00, '}');
          break;
        case SGML_PROC_title_1:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\-}", 3);
          break;
        case SGML_PROC_title_2:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "}}", 2);
          break;
      }
      processor_code = SGML_PROC_text;
      break;

    case SGML_TAG_BodyText:
    case SGML_TAG_endBodyText:
    case SGML_TAG_OverheadText:
    case SGML_TAG_endOverheadText:
      /* simply ignore these things ... */
      break;

    case SGML_TAG_Hervorhebung:
      if (++hervorhebung_depth != 1)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d \'hervorhebung\' are open after ", hervorhebung_depth);
        print_tag_sequence (tl, 0x01);
      }
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\it{}", 5);
      break;
    case SGML_TAG_endHervorhebung:
      if (--hervorhebung_depth != 0)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d \'hervorhebung\' are open after ", hervorhebung_depth);
        print_tag_sequence (tl, 0x01);
      }
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\rm{}", 5);
      italic_correction=1;
      break;

    case SGML_TAG_Definition:
#ifdef NOT_USED_NOW
      if (++definition_depth != 1)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d \'definition\' are open after ", definition_depth);
        print_tag_sequence (tl, 0x01);
      }
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\bf{}", 5);
#endif
      break;
    case SGML_TAG_endDefinition:
#ifdef NOT_USED_NOW
      if (--definition_depth != 0)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d \'definition\' are open after ", definition_depth);
        print_tag_sequence (tl, 0x01);
      }
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\rm{}", 5);
#endif
      break;

    case SGML_TAG_Gleichung:
      if (++gleichung_depth != 1)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d \'gleichung\' are open after ", gleichung_depth);
        print_tag_sequence (tl, 0x01);
      }
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\[", 2);
      math_mode=2;
      break;
    case SGML_TAG_endGleichung:
      if (--gleichung_depth != 0)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d \'gleichung\' are open after ", gleichung_depth);
        print_tag_sequence (tl, 0x01);
      }
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\]", 2);
      math_mode=0;
      break;

    case SGML_TAG_Formel:
      if (++formel_depth != 1)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d \'formel\' are open after ", formel_depth);
        print_tag_sequence (tl, 0x01);
      }
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\(", 2);
      math_mode=1;
      break;
    case SGML_TAG_endFormel:
      if (--formel_depth != 0)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d \'formel\' are open after ", formel_depth);
        print_tag_sequence (tl, 0x01);
      }
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\)", 2);
      math_mode=0;
      break;

    case SGML_TAG_slant:
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\sl{}", 5);
      break;
    case SGML_TAG_endslant:
      sgml_data_block (SGML_PROC_verbatim, 0x00, "\\rm{}", 5);
      italic_correction=1;
      break;

    case SGML_TAG_Tex:
      if (!process_data) break;
      if (math_mode == 0)
         sgml_data_block (SGML_PROC_verbatim, 0x00, "\\(", 2);
      sgml_data_byte (SGML_PROC_verbatim, 0x00, '{');
      print_tag_sequence (tl, 0x02);    /* Tex tag sequence must not        */
                                        /* be prepared for use with TeX     */
      sgml_data_byte (SGML_PROC_verbatim, 0x00, '}');
      if (math_mode == 0)
         sgml_data_block (SGML_PROC_verbatim, 0x00, "\\)", 2);
      break;

    case SGML_TAG_verbatim:
      if (++verbatim_depth != 1)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d verbatim are open after ", verbatim_depth);
        print_tag_sequence (tl, 0x01);
      }
      /* #### verbatim ty=xxxx checken; #### ggf. process_data=0 setzen ### */
      processor_code = SGML_PROC_verbatim;
      break;
    case SGML_TAG_endverbatim:
      if (--verbatim_depth != 0)
      {
        if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
        printf ("* Error %d \'verbatim\' are open after ", verbatim_depth);
        print_tag_sequence (tl, 0x01);
      }
      /* #### verbatim ty=xxxx checken; #### ggf. process_data=1 setzen ### */
      processor_code = SGML_PROC_text;
      break;

    case SGML_TAG_quote:
      if (!process_data) break;
      quote_stack [quote_depth++] = quote_type;
      quote_type = 0;
      tl2 = tl->cdr;
      while (tl2 != (void *) 0)
      {
        par= tl2->car;
        tl2= tl2->cdr;
        if (par->sig == SIG_PARAMETER)
        {
          if (strncmp (par->info, "lang=english", 12) == 0) quote_type=1;
          if (strncmp (par->info, "lang=german",  11) == 0)
             quote_type = (quote_depth == 1) ? 2 : 3;
        }
      }
      switch (quote_type)
      {
        case 2:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "{\\glqq}", 7);
          break;
        case 3:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "{\\glq}", 6);
          break;
        case 0:
          break;
        default:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "``", 2);
          break;
      }
      break;
    case SGML_TAG_endquote:
      if (!process_data) break;
      if (quote_depth <= 0) break;
      if (italic_correction)
      {
        sgml_data_block (SGML_PROC_verbatim, 0x00, "\\/", 2);
        italic_correction = 0;
      }
      switch (quote_type)
      {
        case 2:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "{\\grqq}", 7);
          break;
        case 3:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "{\\grq}", 6);
          break;
        case 0:
          break;
        default:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\'\'", 2);
          break;
      }
      quote_type = quote_stack [--quote_depth];
      break;

    case SGML_TAG_note:
      if (!process_data) break;
      note_type = 0;
      tl2 = tl->cdr;
      while (tl2 != (void *) 0)
      {
        par= tl2->car;
        tl2= tl2->cdr;
        if (par->sig == SIG_PARAMETER)
        {
          if (strncmp (par->info, "ty=footnote", 11) == 0) note_type=1;
        }
      }
      switch (note_type)
      {
        case 1:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\footnote{", 10);
          break;
        default:
          break;
      }
      break;
    case SGML_TAG_endnote:
      if (!process_data) break;
      switch (note_type)
      {
        case 1:
          sgml_data_byte (SGML_PROC_verbatim, 0x00, '}');
          break;
        default:
          break;
      }
      note_type=0;
      break;

    case SGML_TAG_typographic:
      if (!process_data) break;
      typographic_type=-1;
      if (tl->cdr != (void *) 0)
      {
        par= tl->cdr->car;
        if (par->sig == SIG_PARAMETER)
        {
          if (strncmp (par->info, "ty=legato", 9) == 0) typographic_type=1;
          if (strncmp (par->info, "ty=minus",  8) == 0) typographic_type=1;
          if (strncmp (par->info, "ty=cont",   7) == 0) typographic_type=2;
          if (strncmp (par->info, "ty=dash",   7) == 0) typographic_type=3;
          if (strncmp (par->info, "ty=hyphen", 9) == 0) typographic_type=4;
          if (strncmp (par->info, "ty=space",  8) == 0) typographic_type=5;
          if (strncmp (par->info, "ty=linebreak",12) == 0) typographic_type=6;
          if (strncmp (par->info, "ty=linebreak[0]",12) == 0) typographic_type=7;
          if (strncmp (par->info, "ty=linebreak[1]",12) == 0) typographic_type=8;
          if (strncmp (par->info, "ty=linebreak[2]",12) == 0) typographic_type=9;
          if (strncmp (par->info, "ty=linebreak[3]",12) == 0) typographic_type=10;
          if (strncmp (par->info, "ty=linebreak[4]",12) == 0) typographic_type=11;
        }
      }
      switch (typographic_type)
      {
        case 1:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "--", 2);
          break;
        case 2:
          sgml_data_byte (SGML_PROC_verbatim, 0x00, '-');
          break;
        case 3:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "---", 3);
          break;
        case 4:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\-", 2);
          break;
        case 5:
          sgml_data_byte (SGML_PROC_verbatim, 0x00, '~');
          break;
        case 6:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\linebreak ", 11);
          break;
        case 7:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\linebreak[0] ", 14);
          break;
        case 8:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\linebreak[1] ", 14);
          break;
        case 9:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\linebreak[2] ", 14);
          break;
        case 10:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\linebreak[3] ", 14);
          break;
        case 11:
          sgml_data_block (SGML_PROC_verbatim, 0x00, "\\linebreak[4] ", 14);
          break;
        default: /* keine Aktion */
          break;
      }
      break;

    case SGML_TAG_link:
      if (!process_data) break;
      {
        int   link_type=-1;
        int   link_id_size;
        char *link_id=(char *) 0;
        int   link_type_lng;
        char *link_type_str;

        tl2 = tl->cdr;
        sgml_data_block (SGML_PROC_verbatim, 0x00, "\\linkmark{link", 10);
        while (tl2 != (void *) 0)
        {
          par= tl2->car;
          tl2= tl2->cdr;
          if (par->sig == SIG_PARAMETER)
          {
            sgml_data_byte (SGML_PROC_verbatim, 0x00, ' ');
            sgml_data_block (SGML_PROC_verbatim, 0x00,
                             par->info, par->size);
            if (strncmp (par->info, "ty=label",    8) == 0) link_type=1;
            if (strncmp (par->info, "ty=ref",      6) == 0) link_type=2;
            if (strncmp (par->info, "ty=pageref", 10) == 0) link_type=3;
            if (strncmp (par->info, "ty=TeX:",     7) == 0)
            {
              link_type=4;
              link_type_str = par->info + 7;
              link_type_lng = par->size - 7;
            }
            if (strncmp (par->info, "ty=LaTeX:",   9) == 0)
            {
              link_type=4;
              link_type_str = par->info + 9;
              link_type_lng = par->size - 9;
            }
            if (strncmp (par->info, "id=",         3) == 0)
            {
              link_id      = par->info + 3;
              link_id_size = par->size - 3;
            }
          }
        }
        sgml_data_byte (SGML_PROC_verbatim, 0x00, '}');
        if (link_type == -1 || link_id == (char *) 0) break;
        switch (link_type)
        {
          case 1:
            sgml_data_block (SGML_PROC_verbatim, 0x00, "\\label{", 7);
            break;
          case 2:
            sgml_data_block (SGML_PROC_verbatim, 0x00, "\\ref{", 5);
            break;
          case 3:
            sgml_data_block (SGML_PROC_verbatim, 0x00, "\\pageref{", 9);
            break;
          case 4:
            sgml_data_byte  (SGML_PROC_verbatim, 0x00, '\\');
            sgml_data_block (SGML_PROC_verbatim, 0x00, link_type_str, link_type_lng);
            sgml_data_byte  (SGML_PROC_verbatim, 0x00, '{');
            break;
          default: /* keine Aktion */
            break;
        }
        sgml_data_block (SGML_PROC_verbatim, 0x01, link_id, link_id_size);
        sgml_data_byte  (SGML_PROC_verbatim, 0x00, '}');
      }
      break;

    case SGML_TAG_Ref:
    case SGML_TAG_SIG1:
    case SGML_TAG_SIG2:
    case SGML_TAG_FrAttr:
    case SGML_TAG_name:
    case SGML_TAG_endname:
    case SGML_TAG_reference:
    case SGML_TAG_endreference:
      /* simply ignore these things ########## NOW ######## */
      break;
    default:
      report_tagging_error (tl, "* unknown TAG: ", 0);
      break;
  }
  return 0;
}

/* ------------------------------------------------------------------------ */
static void report_tagging_error (
struct SGML_LIST *tl,
char *message,
int p1)
{
  if (errors_in_frame++ == 0) print_tag_sequence (actual_frame, 0x01);
  printf (message, p1);
  print_tag_sequence (tl, 0x01);
}

