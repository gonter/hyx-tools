/*
 *  FILE %ds/hyxp/hyxp0016.c
 *
 *  make a markup structure from a text list
 *
 *  written:       1991 03 27
 *                 1991 03 30
 *  latest update: 1996-02-18 12:10:06
 *  $Id: hyxp0016.c,v 1.4 2004/05/08 15:40:21 gonter Exp $
 *
 */

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <gg/parse.h>

/** #define DEBUG_001 **/

#ifdef NIL
#undef NIL
#endif
#define NIL ((void *) 0)

static void cdecl POP_mus (void);
static int  cdecl PUSH_mus (struct TAG_DEFINITION *td);
static int  cdecl POP_mus_lt (long w);
static int  cdecl POP_mus_le (long w);

/* ------------------------------------------------------------------------ */
struct MUS                      /* markup stack                             */
{
  struct MUS *prev;
  struct MARKUP **mup;          /* stacked value of muapp                   */
  int stat;                     /* what does *muapp point to????            */
#define STAT_NULL   0           /* *muapp == NIL                            */
#define STAT_TEXT   1           /* *muapp == pointer to struct TEXT_ELEMENT         */
#define STAT_MARKUP 2           /* *muapp == pointer to struct MARKUP       */
  long weight;
  struct TAG_DEFINITION *td;
} ;

static struct MUS *mus= (void *) 0;
static long mus_stack_size= 0L;

static struct MARKUP *mu, **muapp;
static long last_tag_weight;
static int muapp_stat;

/* ------------------------------------------------------------------------ */
#ifdef DEBUG_001
static void cdecl dump_stack (FILE *fo);
static char *MS [] = { "NULL", "TEXT", "MARKUP" } ;

static void dump_stack (FILE *fo)
{
  struct MUS *m;
  int i= 0;

  for (m= mus; m != NIL; m= m->prev)
  {
    fprintf (fo, "MUS[%d]: w=%ld s=%s [", i++, m->weight, MS[m->stat]);
    display_tag_definition (fo, m->td);
    fputc (']', fo);
    fputc ('\n', fo);
  }
}
#endif

/* ------------------------------------------------------------------------ */
static void POP_mus ()
{
  struct MUS *m;

  if (mus == NIL) return;

  muapp= mus->mup;
  /* last_tag_weight= mus->weight; ... dont pop it !!! */
  muapp_stat= mus->stat;
  m= mus;
  mus= mus->prev;
  mus_stack_size--;
  free (m);
}

/* ------------------------------------------------------------------------ */
static int PUSH_mus (struct TAG_DEFINITION *td)
{
  struct MUS *m;

  if ((m= (struct MUS *) calloc (sizeof (struct MUS), 1)) == NIL) return -1;

  m->mup= muapp;
  m->weight= last_tag_weight;
  m->prev= mus;
  m->stat= muapp_stat;
  m->td= td;
  mus= m;
  mus_stack_size++;

  return 0;
}

/* ------------------------------------------------------------------------ */
static int POP_mus_lt (long w)  /* Pop open markups from the stack if their */
                                /* weight is less than the given one.       */
{
  if (mus == NIL) return 0;

#ifdef DEBUG_001
printf ("POP_mus_lt: mw=%ld w=%ld ", mus->weight, w);
#endif

  if (mus->weight < w)
  {
    POP_mus ();
#ifdef DEBUG_001
printf (" -> POP .lt.\n");
#endif
    return 1;
  }
#ifdef DEBUG_001
printf ("\n");
#endif

  return 0;
}

/* ------------------------------------------------------------------------ */
static int POP_mus_le (long w)  /* Pop open markups from the stack if their */
                                /* weight is lighter or equal than the      */
                                /* given one.                               */
{
  if (mus == NIL) return 0;

#ifdef DEBUG_001
printf ("POP_mus_le: mw=%ld w=%ld ", mus->weight, w);
#endif

  if (mus->weight == w)
  {
    POP_mus ();
#ifdef DEBUG_001
printf (" -> POP .eq.\n");
#endif
    return 2;
  }

  if (mus->weight < w)
  {
    POP_mus ();
#ifdef DEBUG_001
printf (" -> POP .lt.\n");
#endif
    return 1;
  }

#ifdef DEBUG_001
printf ("\n");
#endif

  return 0;
}

/* ------------------------------------------------------------------------ */
int hyx_text_to_markup (
struct HYX_PARSER_CLASS *hpc,
struct TEXT_ELEMENT *tx_list,
struct MARKUP **pmarkup)
{
  long last_tag_id= -1L;
  struct TEXT_ELEMENT *tx;
  struct TEXT_ELEMENT *tx_next;
  struct TAG_DEFINITION *td;
  struct MARKUP *markup;

if (mus_stack_size)
{
  printf ("text list to markup structure;");
  printf ("  mus_stack_size=%ld", mus_stack_size);
  while (POP_mus_lt (0x7FFFFFFFL));
  printf ("  mus_stack_size=%ld\n", mus_stack_size);
}

  *pmarkup= NIL;
  if (tx_list == NIL) return 0;  /* empty text -> empty markup; ok   */

  mu= NIL;
  muapp= &mu;
  muapp_stat= STAT_NULL;

  for (tx= tx_list; tx != NIL; tx= tx_next)
  {
    tx_next= tx->TE_next;
    tx->TE_next= NIL;
    if (tx->sig == SIG_TEXT_ELEMENT)
    {
      switch ((int) tx->TE_level)
      {
        case 0:   /* possibly tagged text */
          /* if (hyx_strip_text_elem (tx) == 1) goto DISCARD; */
          *muapp= (void *) tx;
          muapp= (struct MARKUP **) &tx->TE_next;
          muapp_stat= STAT_NULL;
          break;

        case 1:   /* tag */
          last_tag_id= -1L;
          td= tx->TE_tag_definition;
          if (td != NIL)
          {
            last_tag_id=     td->tag_id;
            last_tag_weight= td->tag_weight;
            switch (td->tag_type)
            {
              case TAG_TYPE_recursive:
              case TAG_TYPE_nonrecursive:
                if (td->tag_type == TAG_TYPE_recursive)
                     while (POP_mus_lt (last_tag_weight));
                else while (POP_mus_le (last_tag_weight));

              case TAG_TYPE_HTML:
                markup= hyx_make_markup (hpc, tx, NIL, NIL, td, 0x0001);
                if (markup == NIL) goto ERROR;
                if (muapp_stat == STAT_MARKUP) muapp= &(*muapp)->M_next;
                *muapp= (void *) markup;
                muapp_stat= STAT_MARKUP;
                if (PUSH_mus (td) == -1) goto ERROR;
                muapp= (struct MARKUP **) &markup->tagged_text;
                muapp_stat= STAT_NULL;
                break;

              case TAG_TYPE_endtag:
                if (mus == NIL)
                {
                  if (!(hpc->HPC_meta_flags & HPC_META_HTML))
                  {
printf ("end tag, empty stack, not HTML\n");
                    goto DISCARD;
                  }
                }

#ifdef DEBUG_001
printf ("END: ");
display_tag_definition (stdout, td);
fputc ('\n', stdout);
dump_stack (stdout);
#endif

                if (last_tag_weight == 0L) /* empty end tag </> */
                   POP_mus();
                else {

#ifdef DEBUG_001
printf ("%d AQF [", __LINE__);
display_tag_definition (stdout, td);
fputc (']', stdout);
fputc ('\n', stdout);
#endif

                       while (POP_mus_lt (last_tag_weight) == 1);
                       if (POP_mus_le (last_tag_weight) != 2
                           && !(hpc->HPC_meta_flags & HPC_META_HTML)
                          )
                       {
printf ("end tag, too light\n"); /* this should be a notice or so */
                         goto DISCARD; /* given end tag is too light now */
                       }
                     }

                /* does *muapp now point to a markup??? */
                if (muapp_stat == STAT_MARKUP)
                {
                  (*muapp)->tag_close= tx;
                  muapp= &(*muapp)->M_next;
                  muapp_stat= STAT_NULL;
                }
                break;

              case TAG_TYPE_autonomous:
                /* autonomous tag: put it into the      */
                /*   active markup structure            */
                markup= hyx_make_markup (hpc, tx, NIL, NIL, td, 0x0001);
                if (markup == NIL) goto ERROR;
                *muapp= (void *) markup;
                 muapp= (struct MARKUP **) &markup->M_next;
                muapp_stat= STAT_NULL;
                break;
            }
          }
          break;

        default:  /* other tag-level; e.g.: <<xyz>> */
                  /* thats invalid here -> trash    */
DISCARD:
          printf ("discarding text element: ");
          diag_display_text_element (stdout, tx, "", 1);
          hyx_frtx_elem_list (tx);
          break;
      }
    }
    else
    if (tx->sig == SIG_MARKUP)
    {
      *muapp= (void *) tx;
       muapp= (struct MARKUP **) &tx->TE_next;
       muapp_stat= STAT_MARKUP;
    }
  }

  printf (" ... done\n");
  *pmarkup= mu;
  return 0;

ERROR:
  fprintf (stdout, "ERROR: lexicon_text_to_markup: out of memory\n");

  return -1;
}
