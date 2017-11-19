/*
 *  FILE ~/usr/sbr/dt033.c
 *
 *  analyze a string in a Date: line
 *
 *  written:       1989 10 13
 *                 1991 09 16: Revision
 *                 1991 09 21: timezones
 *                 1994-05-14: restructuring and renaming
 *                             (was: ~/usr/mail/datanal.c)
 *  latest update: 1995-06-11
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int check_for_timezone (
int *v,
int *s,
char *str)
{
  int vv;
  int ss;

  vv= *v;
  ss= *s;

  if ((vv % 100) == 0           /* a timezone as offset in minutes          */
                                /* of 100-minutes per hour                  */
     && (vv / 100) <= 12
     && (ss == 1 || ss == 2)    /* either + or - must be dedected           */
     && (strlen (str) == 3      /* +100 -0400                               */
         || strlen (str) == 4)
     && (str[0] == '0'
         || str[0] == '1'))
  {
    *v= (ss==1) ? -(vv/100) : (vv/100);
    *s= 0;
    return DT_int_tz;
  }

  if (vv <= 12
     && (ss == 1 || ss == 2)    /* either + or - must be dedected           */
     && (strlen (str) == 1      /* +1 -04                                   */
         || (strlen (str) == 2
             && str[0] == '1')))
  {
    *v= (ss == 1) ? -vv : vv;
    *s= 0;
    return DT_int_tz;
  }

  return DT_int;
}
