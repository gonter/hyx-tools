/*
 *  FILE %ned/08/ned0825.c
 *
 *  Einlesen einer SGML Tagging Sequence
 *
 *  written:       1991 02 07
 *                 1991 06 01: Revision
 *  latest update: 1999-04-25 16:32:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/streams.h>
#include "ed.h"
#include "edhyx.h"
#include "message.h"
#include "proto.h"

#ifdef __COMMENT__ /* 1993-06-29 09:30 */
T2D:
+ flag: Blanks in Entity erlaubt oder nicht
+ maximale Laenge des Strings
  -> Bei Fehler: Pufferinhalt als Replacement String
                 in diesem Fall: rc= 3 (transparent tag)
#endif /* __COMMENT__ */

/* ------------------------------------------------------------------------ */
#define LIN_SIZ 1024            /* T2D: should be global constant           */
static char lin [LIN_SIZ];      /* intermediate buffer for up to LIN_SIZ    */
                                /* characters used to identify the tag      */
                                /* or entity.                               */

/* ------------------------------------------------------------------------ */
int rd_sgml_tag (
struct WINDOWCTRL *wc,          /* betroffenes Window                       */
struct LINE *lpt,               /* line where feature is attached to        */
struct STREAM_OBJECT *so,       /* Input file stream from .hyx file         */
struct FEATURE **fp,            /* Feature Liste der bearbeiteten Zeile     */
int idx,                        /* Spaltennummer im eingelesenen File       */
int feature_type,               /* Ftype_SGML_TAG | Ftype_SGML_ENTITY       */
int delimiter1,                 /* oeffnender Delimiter fuer Feature Text   */
int delimiter2,                 /* schliessender Delimiter fuer Feature Text*/
char *repl_array,               /* spaeter einzusetzender Replace Text      */
int *repl_size,                 /* Laenge des einzusetzenden Texts          */
int repl_max)                   /* Groesse des Replace Text Puffers         */
/* Return: -1 .. error                                                      */
/*          0 .. tagging sequence read                                      */
/*          1 .. feature record destroyed again (some entities)             */
{
  struct FEATURE *f;            /* angelegtes Feature Record                */
  register struct TXT *tx=      /* Text Segment in der Zeile                */
              (struct TXT *) 0;
  struct LINE *lp;              /* Feature Line                             */
  int tc;                       /* gelesenes Zeichen                        */
  int xlng= 0;                  /* Laenge des Feature Texts                 */
  int watchout= 32000;          /* watchout counter fuer Strukturfehler     */
  int lin_idx= 0;
  int rc;
  STREAM_next_char *_fgetc;
  STREAM_end *_feof;

  if ((f= ned_new_feature (idx, feature_type)) == (struct FEATURE *) 0)
    return -1;

  lp= f->ftr_text_line;
  _fgetc= so->next_char;
  _feof= so->is_end;

  if (delimiter1 == '&')
  { /* 64 chars entities is long enough!                        */
    /* actually, ISO 8879 defines that entity names must only   */
    /* be 8 chracters long.  This is much longer...             */
    watchout= 64;
  }

  /* read feature text */
  tc= delimiter1;       /* first character is tag opener */
  goto FIRST_READ;

  while (1)
  {
    tc= (*_fgetc) (so) & 0x00FF;
    if ((*_feof) (so)) break;

    if (lin_idx < LIN_SIZ) lin [lin_idx++]= (char) tc;

    if (watchout-- < 0)
    {
      switch (feature_type)
      {
        case Ftype_SGML_TAG:    ned_error_message ("SGML Tag error!\n");    break;
        case Ftype_SGML_ENTITY: ned_error_message ("SGML Entity error!\n"); break;
        default:                ned_error_message ("SGML error!\n");        break;
      }
      return -1;
    }

FIRST_READ:
    if ((xlng % TXT_LNG) == 0)     /* Textsegment aufgebraucht */
       if (xlng == 0)              /* 1. Textsegment           */
       { /* first text segment */
         lp->txt= tx= txch_alloc (TXT_LNG, 0x20);
       }
       else
       { /* more text segments */
         tx->next= txch_alloc (TXT_LNG, 0x20);
         tx= tx->next;
       }

    if (tx == (struct TXT *) 0)
    { 
      ned_error_message (ERR_MEMORY);
      return -1;
    }

    tx->t [xlng % TXT_LNG] = (char) tc;
    xlng++;
    if (tc == delimiter2 || (delimiter2 == ';' && tc <= 0x20)) break;
  }

  lin [--lin_idx]= 0;
  lp->lng= xlng;

  rc= ned_identify_feature (wc, lpt, idx, feature_type, f, lin,
                            repl_array, repl_size, repl_max);

  if (rc == 0)
  { /* normal operation: sort in feature in list */
    ned_insert_feature (fp, f);
  }
  else
  { /* error or no feature needed: destroy feature record again */
    ned_lines_free (lp);
    free (f);
  }

  return rc;
}
