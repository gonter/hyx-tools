/*
 *  FILE %ds/hyxl/hyxl0101.c
 *
 *  analyze a string if it contains a date
 *
 *  written:       1996-11-10
 *  latest update: 1996-11-10 16:31:09
 *  $Id: hyxl0101.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* see: #include "edctx.h" */
#include <stdio.h>
#include <string.h>
#include <gg/dates.h>
#include <gg/hyx.h>

/* ------------------------------------------------------------------------ */
int hyx_rule_calendar (
const char *token,
char **res_string,
char **res_type,
void *client_data)
{
  int jahr, mon, tag, std, minutes, sek, x_timezone;
  char str1 [80];

#ifdef MSDOS
  client_data;
#endif

  if (analyze_date (token,
                    &jahr, &mon, &tag,
                    &std, &minutes, &sek,
                    &x_timezone) == -1
      || jahr == -1
      || mon == -1
      || tag == -1
     )
    return 0;

  sprintf (str1,
           "<hyx.l cl=\"%%cal-%04d\" fr=\"%04d-%02d-%02d\" tdp=%d>",
           jahr, jahr, mon, tag, strlen (token));

  *res_string= strdup (str1);
  *res_type= strdup ("F");

  return 1;
}
