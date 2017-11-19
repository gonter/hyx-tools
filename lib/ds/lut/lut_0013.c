/*
 *  FILE %ds/lut/lut_0013.c
 *
 *  processing of XFN-files
 *
 *  written:       1996-10-12
 *  latest update: 1996-10-13 12:18:48
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lut_dump_entry (char *wrd, long info, void *client_data)
{
  unsigned int int1, int2;
  int out_mode;
  int *ip;

  out_mode= (int) client_data;

  switch (out_mode)
  {
    default:
      printf ("0x%08lX  %s\n", info, wrd);
      break;
    case 1:
      ip= (int *) &info;
      int1= *ip++;
      int2= *ip;
      printf ("%5u %5u  %s\n", int1, int2, wrd);
      break;
    case 2:
      printf ("%s\n", wrd);
      break;
  }

  return 0;
}
