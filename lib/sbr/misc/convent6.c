/*
 *  FILE %sbr/convent6.c
 *
 *  Convert Characters to SGML Entities
 *
 *  written:       1995-01-29
 *  latest update: 1996-06-09 11:14:06
 *
 */

#include <stdio.h>
#include <gg/convent.h>

/* ------------------------------------------------------------------------ */
int fputs_entity (char *s, FILE *fo, int level)
{
  int ch;

  for (; ((ch= *s) & 0x00FF) != 0; s++)
    fputc_entity (ch, fo, level);

  return 0;
}
