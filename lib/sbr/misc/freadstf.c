/*
 *  FILE ~/usr/sbr/freadstf.c
 *
 *  read string table
 *
 *  written:       1994-10-08
 *  latest update: 1994-10-08
 *
 */
 
#include <stdio.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int fread_string_table_file (
char *fnm,
char *string_table [],
int table_size,
char *buffer,
int buffer_size)
{
  FILE *f;
  int table_cnt= 0;

  if ((f= fopen (fnm, "rb")) != (FILE *) 0)
  {
    table_cnt= fread_string_table (f, string_table, table_size,
                                   buffer, buffer_size);
    fclose (f);
  }

  return table_cnt;
}
