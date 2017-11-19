/*
 *  FILE %ds/tfb/tfb07.c
 *
 *  written:       2001-12-08
 *  latest update: 2001-12-08 21:12:51
 *  $Id: tfb07.c,v 1.1 2001/12/31 06:29:30 gonter Exp $
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
int tfb_fetch_entry (
struct TFB_HANDLE *handle,
char *key,
char *buffer,
int buffer_size)
{
  FILE *lut;
  FILE *tfb;
  long w_info;
  int lng;
  int rc;

  if (buffer == (char *) 0) return -1;
  if ((lut= handle->TFBH_lut) == (FILE *) 0)
    lut= handle->TFBH_lut= fopen (handle->TFBH_lut_name, "rb");
  if (lut == (FILE *) 0) return -1;

  fseek (lut, (long) 0, 0);

  rc= lookup_file (lut, key, &w_info, &lng);

  if (rc & LOOKUP_found)
  { /* matching entry was found */
    if ((tfb= handle->TFBH_tfb) == (FILE *) 0)
      tfb= handle->TFBH_tfb= fopen (handle->TFBH_tfb_name, "rb");
    if (tfb == (FILE *) 0) return -1;

    fseek (tfb, (long) w_info-1, 0);
    rc= fread_line (tfb, buffer, buffer_size);
    return rc;
  }

  return -1;
}
