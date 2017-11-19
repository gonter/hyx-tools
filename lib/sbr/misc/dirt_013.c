/*
 *  FILE %sbr/dirt_013.c
 *
 *  written:       1984-05-11
 *  latest update: 1997-04-05 18:07:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dirty.h>

#define TLT_NONE

#ifdef TLT_INT
#define dump_fnc dump_str_tlti
#define ttype int
#define MASK 0x00FF
#undef TLT_NONE
#endif

#ifdef TLT_LONG
#define dump_fnc dump_str_tltl
#define ttype long
#define MASK 0x00FFL
#undef TLT_NONE
#endif

#ifdef TLT_NONE
#define dump_fnc dump_str
#endif /* !TLT_NONE */

/* ------------------------------------------------------------------------ */
void dump_fnc (
FILE *fo,
char *x,
int cnt
#ifndef TLT_NONE
, ttype *tbl
#endif /* TLT_NONE */
)
{
  int off= 0;
  int i;
  int b;
#ifndef TLT_NONE
  int ch;
#endif /* TLT_NONE */

  for (; cnt > 0; cnt -= 16)
  {
    b= (cnt > 16) ? 16 : cnt;
    fprintf (fo, "%04X: ", off);
    for (i=0; i<  b; i++) fprintf (fo, "%02X ", x[i] & 0x00FF);
    for (   ; i< 16; i++) fputs ("   ", fo);
    for (i=0; i<  b; i++) fprintf (fo, "%c", char_or_dot (x[i]));
    for (   ; i< 16; i++) fputc (' ', fo);

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
    x += 16;
    off += 16;
  }
}
