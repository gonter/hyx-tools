/*
 *  FILE ~/usr/sbr/freadst.c
 *
 *  read string table
 *
 *  written:       1994-10-08
 *  latest update: 1994-11-06
 *
 */
 
#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int fread_string_table (
FILE *f,
char *string_table [],
int table_size,
char *buffer,
int buffer_size)
{
  int table_cnt= 0;
  int rc;

  for (;;)
  {
    if (table_cnt >= table_size) break;
    rc= fread_line (f, buffer, buffer_size);
    if (rc <= 0 && feof (f)) break;
    string_table [table_cnt++]= strdup (buffer);
  }

  return table_cnt;
}
