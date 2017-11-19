/*
 *  FILE %ds/hyxl/hyxl0006.c
 *
 *  written:       1994-12-11
 *  latest update: 1995-12-16
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int print_hyx_link (
FILE *fo,
char *destination_frame,
char *destination_cluster,
char *destination_file,
char *color,
char *text)
{
  int size= 0;
  int txs= 0;

  fputs ("<hyx.l", fo);
  size= 6;

  if (destination_file != (char *) 0)
  {
    size += fprintf (fo, " file=\"%s\"", destination_file);
  }
  else
  {
    if (destination_cluster != (char *) 0)
      size += fprintf (fo, " cl=\"%s\"", destination_cluster);
    if (destination_frame != (char *) 0)
      size += fprintf (fo, " fr=\"%s\"", destination_frame);
  }

  if (color != (char *) 0)
    size += fprintf (fo, " tdc=\"%s\"", color);

  if (text != (char *) 0)
  {
    txs= strlen (text);
    size += fprintf (fo, " tdp=%d", txs);
  }

  fputc ('>', fo);
  size++;

  if (text != (char *) 0)
  {
    fputs (text, fo);
    size += txs;
  }

  return size;  
}
