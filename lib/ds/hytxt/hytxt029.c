/*
 *  FILE %ds/hytxt/hytxt029.c
 *
 *  linearize hypertext frames
 *  see t2d for information about future enhancements
 *
 *  written:       1991 07 20
 *                 1992 12 07: revision
 *  latest update: 1999-04-25 16:57:53
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/hytxt.h>
#include <gg/sbr.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
int hyx_thr (
FILE *fo,
char *fnm_hyx,
struct FILE_SEGMENT *fs_list,
int verbose_level,
int extract_flags,
char *wanted_thread)
{
  int rc;
  char *afn_hyx;
  char *fnm_idx;
  char *fnm_lut;
  char *fnm_xfn;

  if (fnm_hyx == (char *) 0 || !*fnm_hyx) return -2;

  if ((afn_hyx= translate_logic_filename (fnm_hyx)) == (char *) 0)
    afn_hyx= fnm_hyx;

  fnm_idx= fnmcpy2 (afn_hyx, ".idx");
  fnm_lut= fnmcpy2 (afn_hyx, ".lut");
  fnm_xfn= fnmcpy2 (afn_hyx, ".xfn");

  if (verbose_level > 0)
  {
    printf ("HYX (?): %s\n", afn_hyx);
    printf ("IDX (?): %s\n", fnm_idx);
    printf ("LUT (?): %s\n", fnm_lut);
    printf ("XFN (?): %s\n", fnm_xfn);
  }

  rc= hyx_threader (
        (fo == (FILE *) 0) ? (FILE *) stdout : fo,
        afn_hyx, fnm_idx, fnm_lut, fnm_xfn,
        fs_list, verbose_level, extract_flags, wanted_thread);

  flclose_all ();

  free (afn_hyx);
  free (fnm_idx);
  free (fnm_lut);
  free (fnm_xfn);

  return rc;
}
