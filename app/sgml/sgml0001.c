/*
 *  FILE ~/usr/sgml/sgml0001.c
 *
 *  sgml_filter: SGML-Dokument in
 *               (a) eigentlichen Text
 *               (b) SGML-Tags mit Parametern
 *               (c) SGML-Kommentar
 *               aufsplitten.
 *
 *  written:       1989 11 03
 *                 1990 09 23: Umstellung der Filter Ausgabe in LONGs
 *  latest update: 1994-06-04
 *
 */

#pragma check_stack(off)

/* Prototypes fÅr hier definierte Funktionen: ----------------------------- */
void cdecl sgml_filter_reset   (void);
void cdecl sgml_filter         (int ch);

void cdecl sgml_filter_tag_chr (long);
void cdecl sgml_filter_tag_beg (void);
void cdecl sgml_filter_tag_end (void);

void cdecl sgml_filter_com_chr (long);
void cdecl sgml_filter_com_beg (void);
void cdecl sgml_filter_com_end (void);

void cdecl sgml_filter_chr     (long);

/* ------------------------------------------------------------------------ */
/* Schnittstellen:
/* sgml_filter_reset ()         reset the SGML filter system                */
/* sgml_filter (ch)             character to be processed                   */
void sgml_filter_tag_chr (long ch) {ch;}/* Ausgabe eines gelesenen Tags mit Parametern */
void sgml_filter_tag_beg ()        {}   /* Beginn eines Tags festgestellt              */
void sgml_filter_tag_end ()        {}   /* Ende eines Tags festgestellt                */
void sgml_filter_com_chr (long ch) {ch;}/* Ausgabe eines gelesenen Kommentar-Zeichens  */
void sgml_filter_com_beg ()        {}   /* Beginn eines Kommentars festgestellt        */
void sgml_filter_com_end ()        {}   /* Ende eines Kommentars festgestellt          */
void sgml_filter_chr     (long ch) {ch;}/* Ausgabe eines gelesenen Text-Zeichens       */

/* ------------------------------------------------------------------------ */
static int sgml_filter_status = 0;
static int state_at_end_of_comment;

static long val;                        /* Character Code in Oct, Dec, Hex  */

/* ------------------------------------------------------------------------ */
void sgml_filter_reset (void)
{
  sgml_filter_status = 0;
}

/* ------------------------------------------------------------------------ */
void sgml_filter (int ch)
{
  switch (sgml_filter_status)
  {
    case 0: /* normal text so far ... */
            if (ch == '<')
                 sgml_filter_status = 1;
            else sgml_filter_chr ((long) ch);
            break;
    case 1: /* beginning of a tagged sequence */
            val = 0L;
            switch (ch)
            {
              case '0':
                sgml_filter_status = 2;
                break;
              case '1': case '2': case '3': /* character code in decimal */
              case '4': case '5': case '6':
              case '7': case '8': case '9':
                val = (long) (ch - '0');
                sgml_filter_status = 4;
                break;
              case '-': /* this could be the beginning of a SGML-comment */
                sgml_filter_status = 7;
                state_at_end_of_comment=1;
                break;
              case '>': /* this was an empty tagging sequence */
                sgml_filter_status = 0;
                break;
# ifdef JUNK /* filter this out at this state may not be optimal ... */
              case ' ': /* white spaces are ignored */
              case 0x09:
              case 0x0D:
              case 0x0A:
                break;
# endif
              case '\"':
                sgml_filter_tag_beg ();
                sgml_filter_tag_chr ((long) ch);
                sgml_filter_status = 10;
                break;
              case '\\':
                sgml_filter_tag_beg ();
                sgml_filter_tag_chr ((long) ch);
                sgml_filter_status = 12;
                break;
              default: /* a normal tagging sequence starts */
                sgml_filter_tag_beg ();
                sgml_filter_tag_chr ((long) ch);
                sgml_filter_status = 6;
                break;
            }
            break;
    case 2: /* character code, beginning with 0 */
            switch (ch)
            {
              case 'x': case 'X':
                sgml_filter_status = 3;
                break;
              case '0': case '1':
              case '2': case '3':
              case '4': case '5':
              case '6': case '7':
                val = (long) (ch - '0');
                sgml_filter_status = 5;
                break;
              case '>':
                sgml_filter_status = 0;
                sgml_filter_chr ((long) 0);
                break;
             default:
                sgml_filter_status = 6;
                sgml_filter_tag_beg ();
                sgml_filter_tag_chr ((long) '0');
                break;
            }
            break;
    case 3: /* character code in hexadecimal */
            if (ch >= '0' && ch <= '9')      val= 16L*val+(long)(ch-'0');
            else if (ch >= 'a' && ch <= 'f') val= 16L*val+(long)(ch-'a'+10);
            else if (ch >= 'A' && ch <= 'F') val= 16L*val+(long)(ch-'A'+10);
            else if (ch == '>')
                 {
                   sgml_filter_chr (val);
                   sgml_filter_status = 0;
                 }
            else { /* this case is *ILLEGAL* ... we handle this later! */
                   sgml_filter_tag_beg ();
                   sgml_filter_tag_chr (val);
                   sgml_filter_status = 6;
                 }
            break;
    case 4: /* character code in decimal */
            if (ch >= '0' && ch <= '9')      val= 10L*val+(long)(ch-'0');
            else if (ch == '>')
                 {
                   sgml_filter_chr (val);
                   sgml_filter_status = 0;
                 }
            else { /* this case is *ILLEGAL* ... we handle this later! */
                   sgml_filter_tag_beg ();
                   sgml_filter_tag_chr (val);
                   sgml_filter_status = 6;
                 }
            break;
    case 5: /* character code in octal */
            if (ch >= '0' && ch <= '7')      val= 8L*val+(long)(ch-'0');
            else if (ch == '>')
                 {
                   sgml_filter_chr (val);
                   sgml_filter_status = 0;
                 }
            else { /* this case is *ILLEGAL* ... we handle this later! */
                   sgml_filter_tag_beg ();
                   sgml_filter_tag_chr (val);
                   sgml_filter_status = 6;
                 }
            break;
    case 6: /* a normal tagging sequence */
            switch (ch)
            {
              case '>':
                sgml_filter_tag_end ();
                sgml_filter_status = 0;
                break;
              case '-':
                sgml_filter_status=7;
                state_at_end_of_comment=6;
                break;
              case '\"':
                sgml_filter_tag_chr ((long) ch);
                sgml_filter_status=10;
                break;
              case '\\':
                sgml_filter_tag_chr ((long) ch);
                sgml_filter_status=12;
                break;
              default:
                sgml_filter_tag_chr ((long) ch);
                break;
            }
            break;
    case 7: /* maybe the begginning of a SGML comment */
            switch (ch)
            {
              case '-': /* yes, second - we see... this is a SGML comment */
                sgml_filter_status = 8;
                sgml_filter_com_beg ();
                break;
              case '>': /* this was only one - as a SGML tag! */
                sgml_filter_status = 0;
                sgml_filter_tag_beg ();
                sgml_filter_tag_chr ((long) '-');
                sgml_filter_tag_end ();
                break;
              default: /* this is now a regular SGML tag */
                sgml_filter_status = 6;
                if (state_at_end_of_comment == 1)
                  sgml_filter_tag_beg ();
                sgml_filter_tag_chr ((long) '-');
                sgml_filter_tag_chr ((long) ch);
                break;
            }
            break;
    case 8: /* inside of a SGML comment */
            if (ch == '-')
                {
                  sgml_filter_status = 9;
                }
           else {
                  sgml_filter_com_chr ((long) ch);
                }
            break;
    case 9: /* maybe the end of a SGML comment */
            if (ch == '-')
                 { /* yes, the second - that's the end of the comment */
                   sgml_filter_status = state_at_end_of_comment;
                   sgml_filter_com_end ();
                 }
            else {
                   sgml_filter_com_chr ((long) '-');
                   sgml_filter_com_chr ((long) ch);
                   sgml_filter_status = 8;
                 }
            break;
    case 10: /* tag sequence under quote */
      sgml_filter_tag_chr ((long) ch);
      if (ch=='\"') sgml_filter_status=6; else
      if (ch=='\\') sgml_filter_status=11;
      break;
    case 11: /* backslash inside a quoted tag sequence */
      sgml_filter_tag_chr ((long) ch);
      sgml_filter_status=10;
      break;
    case 12: /* backslash inside a tag sequence */
      sgml_filter_tag_chr ((long) ch);
      sgml_filter_status=6;
      break;
  }
}
