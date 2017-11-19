/*
 *  FILE %sbr/freadit.c
 *
 *  read integer table
 *
 *  written:       1994-10-08
 *  latest update: 1994-10-08
 *  $Id: freadit.c,v 1.2 2003/06/25 14:38:29 gonter Exp $
 *
 */
 
#include <stdio.h>
#include <gg/sbr.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int fread_integer_table (
FILE *f,
long int_table [],
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
    int_table [table_cnt++]= get_parameter_value (buffer);
  }

  return table_cnt;
}
