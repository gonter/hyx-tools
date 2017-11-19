/*
 *  FILE %ds/tfb/tfb03.c
 *
 *  written:       1996-03-20
 *  latest update: 1996-05-24 16:33:54
 *  $Id: tfb03.c,v 1.3 2001/12/19 08:07:45 gonter Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gg/filename.h>
#include <gg/tfb.h>

/* ------------------------------------------------------------------------ */
struct TFB_HANDLE *tfb_create_handle (char *fn_tfb, char *fn_lut)
{
  struct TFB_HANDLE *h;

  if (fn_tfb == (char *) 0
      || *fn_tfb == 0
      || (h= (struct TFB_HANDLE *) calloc (sizeof (struct TFB_HANDLE), 1))
         == (struct TFB_HANDLE *) 0
     )
   return (struct TFB_HANDLE *) 0;

  h->TFBH_tfb_name= strdup (fn_tfb);
  h->TFBH_lut_name= (fn_lut == (char *) 0 || *fn_lut == 0)
                    ? fnmcpy2 (fn_tfb, ".lut")
                    : strdup (fn_lut);

  return h;
}

/* ------------------------------------------------------------------------ */
TFB_HANDLE *new_TFB_HANDLE (char *fn_tfb, char *fn_lut)
{
  return tfb_create_handle (fn_tfb, fn_lut);
}
