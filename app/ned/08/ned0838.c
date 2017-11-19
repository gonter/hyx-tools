/*
 *  FILE %ned/08/ned0838.c
 *
 *  Transfer a block of text beginning with (la, la_idx) up to
 *  (lz, lz_idx) into a string dst with a maximum size buffer_size.
 *
 *  written:       1991 05 23
 *  latest update: 1999-05-14 21:18:10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
char *ned_line_2_string (
struct LINE *la,
int la_idx,
struct LINE *lz,
int lz_idx,
char *buffer,           /* malloc if (char *) 0         */
int buffer_size,
long offset,            /* skip <offset> bytes          */
int flags)              /* bit 0: convert \n to blanks  */
{
  int idx;
  struct TXT *tx;
  int ll;
  int lsl;
  char *cp;
  int malloced= 0;
  char *dst;

  if ((dst= buffer) == (char *) 0 || buffer_size <= 0)
  {
    long MB;

    MB= ned_line_list_size (la, la_idx, lz, lz_idx, flags);

    MB += 5;    /* T2D find out if this is necessary ! */

    buffer_size= (MB > 32000L) ? 32000 : ((int) MB);
    if ((buffer= malloc (buffer_size)) == (char *) 0) return (char *) 0;
    malloced= 1;
    dst= buffer;
  }

  buffer_size--;   /* need space for the 0-character too! */
  *dst= 0;

  for (; la != (struct LINE *) 0; la= la->next)
  {
    if ((tx= la->txt) == (struct TXT *) 0)
    {
      ll= lsl= 0;
      cp= (char *) 0;
    }
    else
    {
      ll= la->lng;
      lsl= tx->t_lng;
      cp= tx->t;
    }

    for (idx= 0; idx < ll; idx++)
    {
      if (la == lz && idx >= lz_idx) return buffer;
      if (lsl == 0)
      {
        if ((tx= tx->next) == (struct TXT *) 0)
        { /* ERROR: text segment shorter than expected !!! */
          if (malloced) free (buffer);
          return (char *) 0;
        }

        lsl= tx->t_lng;
        cp= tx->t;
      }

      if (idx >= la_idx)
      {
        if (offset <= 0L)
        {
          *dst++= *cp;
          *dst= 0;
          buffer_size--;
          if (buffer_size <= 0) return buffer;
        }
        else offset--;
      }
      lsl--;
      cp++;
    }

    if (la == lz) return buffer;

    if (offset <= 0L)
    {
      *dst++= (char) ((flags & 0x0001) ? '\n' : ' ');
      *dst= 0;
      buffer_size--;
      if (buffer_size <= 0) return buffer;
    }
    else offset--;

    la_idx= 0;
  }

  return buffer;
}
