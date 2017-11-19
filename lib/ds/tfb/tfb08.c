/*
 *  FILE %ds/tfb/tfb08.c
 *
 *  written:       2001-12-08
 *  latest update: 2001-12-08 21:12:51
 *  $Id: tfb08.c,v 1.1 2001/12/31 06:29:30 gonter Exp $
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
char *tfb_fetch_entry2 (
TFB_HANDLE *handle,
char *key)
{
  char *buffer;
  int rv;

  if (handle == (TFB_HANDLE *) 0) return (char *) 0;

  if ((buffer= handle->TFBH_buffer) == (char *) 0)
  {
    if ((buffer= malloc (TFB_default_buffer_size)) == (char *) 0)
        return (char *) 0;

    handle->TFBH_buffer= buffer;
    handle->TFBH_buffer_size= TFB_default_buffer_size;
  }

  rv= tfb_fetch_entry (handle, key, buffer, handle->TFBH_buffer_size);
  if (rv > 0) return strdup (buffer);
  return (char *) 0;
}
