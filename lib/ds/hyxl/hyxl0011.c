/*
 *  FILE %ds/hyxl/hyxl0011.c
 *
 *  written:       1997-11-01
 *  latest update: 2001-02-18 17:59:27
 *  $Id: hyxl0011.c,v 1.2 2001/02/19 00:39:52 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/fileio.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
long hcc_update_index (
struct HYX_CLUSTER_CONTROL *hcc,
YTREE_PROCESSOR *lut_processor,
YTREE_PROCESSOR *xfn_processor)
{
  FILE *fo;
  long unique;

  if (hcc == (struct HYX_CLUSTER_CONTROL *) 0) return -1L;

  if (hcc->HCC_lut_mode == HCC_lm_full_write)
  {
printf ("hyxl0011.c e\n");
    ytree_process (hcc->HCC_ytree, lut_processor, (void *) 0);
    ytree_size (hcc->HCC_ytree);
printf ("hyxl0011.c f\n");

    if ((fo= fopen (hcc->HCC_fnm_lut, "wb")) == (FILE *) 0)
    {
      fprintf (stdout, "%ds/hyxl/hyxl0011.c: error opening lut file %s\n",
               hcc->HCC_fnm_lut);
    }
    else
    {
      unique= ytree_dump (fo, hcc->HCC_ytree);
      fclose (fo);
    }
  }
  else
  if (hcc->HCC_lut_mode == HCC_lm_incremental)
  {
    if ((fo= fopen (hcc->HCC_fnm_xfn, "a")) == (FILE *) 0)
    {
      fprintf (stdout, "%ds/hyxl/hyxl0011.c: error opening xfn file %s\n",
               hcc->HCC_fnm_xfn);
    }
    else
    {
      ytree_process (hcc->HCC_ytree, xfn_processor, (void *) fo);
      fclose (fo);
    }
  }
  else
  {
    fprintf (stderr, "unknown lut_mode: %d\n", hcc->HCC_lut_mode);
    return -1;
  }

  ytree_free (hcc->HCC_ytree);
  hcc->HCC_ytree= (struct YTREE *) 0;

  return unique;
}
