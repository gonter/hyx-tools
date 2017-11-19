/*
 *  FILE %sbr/dirt_012.c
 *
 *  written:       1994-03-12
 *  latest update: 1997-04-05 18:46:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dirty.h>

#define TLT_NONE

#ifdef TLT_INT
#define dump_fnc dump_file_tlti
#define ttype int
#define MASK 0x00FF
#undef TLT_NONE
#endif

#ifdef TLT_LONG
#define dump_fnc dump_file_tltl
#define ttype long
#define MASK 0x00FFL
#undef TLT_NONE
#endif

#ifdef TLT_NONE
#define dump_fnc dump_file
#endif

/* ------------------------------------------------------------------------ */
void dump_fnc (
FILE *fo,
FILE *fi,
long cnt,
int do_flush
#ifndef TLT_NONE
, ttype *tbl
#endif /* TLT_NONE */
)
{
  int i;
  int b;
  int x[16];
  long off= 0;
#ifndef TLT_NONE
  int ch;
#endif /* TLT_NONE */

  for (; cnt > 0L; cnt -= 16L)
  {
    b= (cnt > 16L) ? 16 : ((int) cnt);

    fprintf (fo, "%08lX: ", off);
    for (i= 0; i<  b; i++)
    {
      x[i]= fgetc (fi) & 0x00FF;
      if (feof (fi))
      {
        b= i;
        break;
      }
      fprintf (fo, "%02X ", x[i] & 0x00FF);
    }

    for (    ; i < 16; i++) fputs ("   ", fo);
    for (i= 0; i <  b; i++) fprintf (fo, "%c", char_or_dot (x[i]));

#ifndef TLT_NONE
    if (tbl != (ttype *) 0) 
    {
      fputc ('|', fo);
      for (i= 0; i < b; i++)
      {
        ch= x[i] & 0x00FF;
        ch= (int) (tbl[ch] & MASK);
        fprintf (fo, "%c", char_or_dot (ch));
      }
    }
#endif /* !TLT_NONE */

    fputc ('\n', fo);
    if (do_flush) fflush (fo);
    off += 16L;

    if (feof (fi))
    {
      fflush (fo);
      break;
    }
  }
}
