/*
 *  FILE %ds/hytxt/hytxt024.c
 *
 *  linearize hypertext frames
 *  see t2d for information about future enhancements
 *
 *  written:       1991 07 20
 *                 1992 12 07: revision
 *  latest update: 1999-04-25 16:57:39
 *  $Id: hytxt024.c,v 1.3 2002/01/27 23:01:40 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/hytxt.h>
#include <gg/sbr.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
int hyx_seq (
FILE *fo,
char *fnm_hyx,
struct FILE_SEGMENT *fs_list,
int verbose_level,
int extract_flags)
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

  rc= hyx_sequencer (
        (fo == (FILE *) 0) ? (FILE *) stdout : fo,
        afn_hyx, fnm_idx, fnm_lut, fnm_xfn,
        fs_list, verbose_level, extract_flags);

  flclose_all ();

  free (afn_hyx);
  free (fnm_idx);
  free (fnm_lut);
  free (fnm_xfn);

  return rc;
}
