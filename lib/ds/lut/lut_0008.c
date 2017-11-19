/*
 *  FILE %ds/lut/lut_0008.c
 *
 *  Verarbeiten von LUT-Files
 *
 *  written:       1989 06 11: aus WORDCR01.C isolierte Funktionen:
 *                             check_word       -> lookup_char
 *                             check_word_file  -> lookup_file
 *                 1990 01 20: zerlegt in Library-Module
 *                 1991 03 15: Revision; AIX
 *  latest update: 1996-10-13 12:16:39
 *  $Id: lut_0008.c,v 1.2 2003/06/25 14:38:29 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lut_process (
char *lut_name,                         /* Look Up Table                    */
int (*processor) (char *w, long i, void *client_data),
void *client_data,
long start)
{
  FILE *lut;
  int rc;

  if ((lut= fopen (lut_name, "rb")) == (FILE *) 0) return -1;
  fseek (lut, start, 0);
  rc= lut_process_block (lut, processor, client_data);
  fclose (lut);

  return rc;
}
