/*
 *  FILE %sbr/convent1.c
 *
 *  Convert Characters to SGML Entities
 *
 *  written:       1991-07-03: <Gerhard.Gonter@wu-wien.ac.at>
 *  latest update: 1997-10-24 11:46:52
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/fileio.h>
#include <gg/convent.h>

/* ------------------------------------------------------------------------ */
int sgml_entity_conversion (
char *fni,              /* input file name                                  */
char *fno,              /* output file name                                 */
int level)              /* bit 0: convert &                                 */
                        /* bit 1: convert <>                                */
                        /* bit 2: convert 0x80..0xFF (PC)                   */
                        /* bit 3: convert 0x80..0xFF (Mac)                  */
{
  FILE *fi;
  FILE *fo;
  int ch;
  int fi_open= 0;
  int fo_open= 0;
  int rc= 0;

  FXOPEN (fni, fi, stdin,  "rb", fi_open);
  FXOPEN (fno, fo, stdout, "wb", fo_open);

  if (fi != (FILE *) 0 && fo != (FILE *) 0)
  {
    rc= 0;

    for (;;)
    {
      ch= fgetc (fi) & 0x00FF;
      if (feof (fi)) break;
      fputc_entity (ch, fo, level);
    }
  }

  FXCLOSE (fi, fi_open);
  FXCLOSE (fo, fo_open);

  return rc;
}
