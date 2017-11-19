/*
 *  FILE %ds/hyxl/hyxl0010.c
 *
 *  written:       1996-10-12
 *  latest update: 1996-10-12 12:43:07
 *  $Id: hyxl0010.c,v 1.2 2002/01/27 23:01:44 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/fileio.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hcc_open (struct HYX_CLUSTER_CONTROL *hcc, int mode)
{
  if (hcc == (struct HYX_CLUSTER_CONTROL *) 0) return -1;

  /* indicate success if requested open mode matches current state          */
  if (hcc->HCC_open_mode == mode) return 0;

  /* otherwise close the cluster                                            */
  fclose_or_what (hcc->HCC_f_hyx);
  fclose_or_what (hcc->HCC_f_idx);
  fclose_or_what (hcc->HCC_f_lut);
  fclose_or_what (hcc->HCC_f_xfn);
  hcc->HCC_f_hyx=
  hcc->HCC_f_idx=
  hcc->HCC_f_lut=
  hcc->HCC_f_xfn= (FILE *) 0;
  hcc->HCC_open_mode= HCC_om_closed;

  switch (mode)
  {
    case HCC_om_closed:
      break;

    case HCC_om_read:
      hcc->HCC_f_hyx= fopen (hcc->HCC_fnm_hyx, "rb");
      hcc->HCC_f_idx= fopen (hcc->HCC_fnm_idx, "rb");
      hcc->HCC_f_lut= fopen (hcc->HCC_fnm_lut, "rb");
      hcc->HCC_f_xfn= fopen (hcc->HCC_fnm_xfn, "rb");
      hcc->HCC_open_mode= HCC_om_read;
      break;

    case HCC_om_update:
      hcc->HCC_f_hyx= fopen (hcc->HCC_fnm_hyx, "ab");
      hcc->HCC_f_idx= fopen (hcc->HCC_fnm_idx, "a+b");
      hcc->HCC_f_lut= fopen (hcc->HCC_fnm_lut, "rb");
      hcc->HCC_f_xfn= fopen (hcc->HCC_fnm_xfn, "ab");
      hcc->HCC_open_mode= HCC_om_update;
      break;

    default:
      return -1;
  }

  return 0;
}
