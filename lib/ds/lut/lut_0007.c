/*
 *  FILE %ds/lut/lut_0007.c
 *
 *  Funktionen zum Durchsuchen von XFN-Woerterbuechern
 *
 *  written:       1991 05 29
 *  latest update: 1996-03-24 17:42:57
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/dpp.h>
#include <gg/strings.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
static char lut_word_buffer [MAX_LUT_KEY_LENGTH+2];

/* ------------------------------------------------------------------------ */
int lookup_file_xfn (
FILE *xfn,                      /* Look Up Table; binaer eroeffnet          */
                                /* und an den Anfang positioniert           */
const char *w,                  /* Word                                     */
long *w_info)                   /* -> Informationen ueber Word              */
/* return values: see file <gg/lookup.h>                                    */
{
  int rc;
#define MAX_FIELDS 2
  char *fields [MAX_FIELDS];

  if (nl_key_valid (w) == -1) return LOOKUP_error;

  fseek (xfn, (long) 0, 0);

  lut_word_buffer [0]= '0';     /* frame number is in hex withou 0x,        */
  lut_word_buffer [1]= 'x';     /* so place it in string to use it later    */

  for (;;)
  {
    rc= fread_line (xfn, lut_word_buffer+2, MAX_LUT_KEY_LENGTH);
    if (rc <= 0 && feof (xfn)) break;

    rc= isolate_tokens (lut_word_buffer, fields, MAX_FIELDS);
    if (rc < 2) continue;

    *w_info= get_parameter_value (fields [0]);
    if (strcmp (fields [1], w) == 0) return LOOKUP_found;
  }

  return LOOKUP_not_found;
}
