/*
 *  FILE %ds/tfb/tfb04.c
 *
 *  written:       1996-03-20
 *  latest update: 1996-05-24 16:33:21
 *  $Id: tfb04.c,v 1.4 2005/03/11 22:25:08 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/lookup.h>
#include <gg/filename.h>
#include <gg/sbr.h>
#include <gg/tfb.h>

/* ------------------------------------------------------------------------ */
int tfb_transfer_entry (
FILE *fo,
struct TFB_HANDLE *handle,
char *key)
{
  FILE *lut;
  FILE *tfb;
  long w_info;
  int lng;
  int rc;

  if ((lut= handle->TFBH_lut) == (FILE *) 0)
    lut= handle->TFBH_lut= fopen (handle->TFBH_lut_name, "rb");
  if (lut == (FILE *) 0) return -1;

  if (key[0] == 0) goto NO_MATCH;

  fseek (lut, (long) 0, 0);

  rc= lookup_file (lut, key, &w_info, &lng);

  if (rc & LOOKUP_found)
  { /* matching entry was found */
    if ((tfb= handle->TFBH_tfb) == (FILE *) 0)
      tfb= handle->TFBH_tfb= fopen (handle->TFBH_tfb_name, "rb");
    if (tfb == (FILE *) 0) return -1;

    fseek (tfb, (long) w_info-1, 0);
    ftransfer_line (tfb, fo, 100000L);
  }
  else
  { /* no matching entry was found: print an empty line */
NO_MATCH:
    fputc ('\n', fo);
  }

  return 0;
}
