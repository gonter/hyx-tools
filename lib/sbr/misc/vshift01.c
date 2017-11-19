/*
 *  FILE %sbr/vshift01.c
 *
 *  written:       1994-03-06
 *  latest update: 1997-05-30 13:05:23
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <gg/filename.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
#define FNM_SIZE 256
static char fnm_old [FNM_SIZE];
static char fnm_new [FNM_SIZE];

/* ------------------------------------------------------------------------ */
#define TBL_SIZE 32
static long shift_tbl [TBL_SIZE] =
{
  0x00000001,
  0x00000002,
  0x00000004,
  0x00000008,

  0x00000010,
  0x00000020,
  0x00000040,
  0x00000080,

  0x00000100,
  0x00000200,
  0x00000400,
  0x00000800,

  0x00001000,
  0x00002000,
  0x00004000,
  0x00008000,

  0x00010000,
  0x00020000,
  0x00040000,
  0x00080000,

  0x00100000,
  0x00200000,
  0x00400000,
  0x00800000,

  0x01000000,
  0x02000000,
  0x04000000,
  0x08000000,

  0x10000000,
  0x20000000,
  0x40000000,
  0x80000000
} ;

/* ------------------------------------------------------------------------ */
int vshift (char *fnm, long version, char *fmt, int doit, int verbose)
{
  int i;
  int ops= 0;

  if (verbose)
    printf ("vshift: %s version=%ld\n", fnm, version);

  for (i= 0; i < TBL_SIZE; i++)
  {
    if (version & shift_tbl [i])
    {
      for (; i>= 0; i--)
      {
        if (i == 0)
             strcpy (fnm_old, fnm);
        else sprintf (fnm_old, fmt, fnm, shift_tbl [i-1]);
        sprintf (fnm_new, fmt, fnm, shift_tbl [i]);

        if (verbose) printf ("unlinking %s\n", fnm_new);
        if (doit)    unlink (fnm_new);

        if (verbose) printf ("renaming %s to %s\n", fnm_old, fnm_new);
        if (doit)    rename (fnm_old, fnm_new);

        ops++;
      }

      return ops;
    }
  }

  return ops;
}
