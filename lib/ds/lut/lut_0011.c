/*
 *  FILE %ds/lut/lut_0011.c
 *
 *  processing of XFN-files
 *
 *  written:       1995-01-07
 *  latest update: 1996-10-13 12:18:48
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int xfn_process_block (
FILE *xfn,                      /* XFN file stream                          */
int (*processor) (char *w, long i, void *client_data),
void *client_data)
{
  long idx;
  char xfn_word_buffer [MAX_LUT_KEY_LENGTH];

  if (xfn == (FILE *) 0) return 0;

  for (;;)
  {
    fscanf (xfn, "%lx", &idx);
    if (feof (xfn)) break;
    fscanf (xfn, "%*[ \t]");
    fscanf (xfn, "%[^\n]", xfn_word_buffer);
    if (feof (xfn)) break;
    fgetc (xfn);

    (*processor) (xfn_word_buffer, idx, client_data);
  }

  return 0;
}
