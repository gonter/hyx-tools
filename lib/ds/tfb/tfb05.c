/*
 *  FILE %ds/tfb/tfb05.c
 *
 *  written:       1996-03-20
 *  latest update: 1996-05-24 16:33:37
 *  $Id: tfb05.c,v 1.3 2001/12/19 08:07:45 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <gg/strings.h>
#include <gg/fileio.h>
#include <gg/tfb.h>

/* ------------------------------------------------------------------------ */
int tfb_close_handle (struct TFB_HANDLE *h)
{
  if (h == (struct TFB_HANDLE *) 0) return -1;

  fclose_or_what (h->TFBH_tfb);
  fclose_or_what (h->TFBH_lut);
  free_or_what (h->TFBH_tfb_name);
  free_or_what (h->TFBH_lut_name);
  free_or_what (h->TFBH_buffer);
  free (h);

  return 0;
}
