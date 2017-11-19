/*
 *  File %dpp/codes/cs107.c
 *
 *  CS_ET8: entity translation functions
 *
 *  written:       1995-12-10: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
long cs_et8_fputc (struct CS_ET8 *et8, int ch, FILE *fo)
{
  char *entity_name;

  if ((ch >= 0x80 && ch <= 0xFF)
      ||(ch >= 0x00 && ch <= 0x09)
      ||(ch >= 0x0B && ch <= 0x0C)
      ||(ch >= 0x0E && ch <= 0x1F)
     )
  {
    if ((entity_name= cs_et8_code2entity (et8, ch)) != (char *) 0)
    {
      fputc ('&', fo);
      fputs (entity_name, fo);
      fputc (';', fo);
      return (long) (strlen (entity_name) + 2);
    }
  }

  fputc (ch, fo);
  return 1L;
}
