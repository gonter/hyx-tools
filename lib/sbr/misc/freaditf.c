/*
 *  FILE %sbr/freaditf.c
 *
 *  read integer table
 *
 *  written:       1994-10-08
 *  latest update: 1994-10-08
 *  $Id: freaditf.c,v 1.2 2003/06/25 14:38:29 gonter Exp $
 *
 */
 
#include <stdio.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int fread_integer_table_file (
char *fnm,
long int_table [],
int table_size,
char *buffer,
int buffer_size)
{
  FILE *f;
  int table_cnt= 0;

  if ((f= fopen (fnm, "rb")) != (FILE *) 0)
  {
    table_cnt= fread_integer_table (f, int_table, table_size,
                                    buffer, buffer_size);
    fclose (f);
  }

  return table_cnt;
}
