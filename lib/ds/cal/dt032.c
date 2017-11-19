/*
 *  FILE %ds/cal/dt032.c
 *
 *  analyze a string in a Date: line
 *
 *  written:       1989 10 13
 *                 1991 09 16: Revision
 *                 1991 09 21: timezones
 *                 1994-05-14: restructuring and renaming
 *                             (was: ~/usr/mail/datanal.c)
 *  latest update: 1997-07-03 21:31:23
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
#define N_date_strings 28
static struct DATE_str date_strings [N_date_strings] =
{
  {   DT_str_junk,   1,  4, "date" },
  {   DT_str_mon,    1,  3, "jan" },
  {   DT_str_mon,    2,  3, "feb" },
  {   DT_str_mon,    3,  3, "mar" },
  {   DT_str_mon,    4,  3, "apr" },
  {   DT_str_mon,    5,  3, "may" },
  {   DT_str_mon,    5,  3, "mai" },
  {   DT_str_mon,    6,  3, "jun" },
  {   DT_str_mon,    7,  3, "jul" },
  {   DT_str_mon,    8,  3, "aug" },
  {   DT_str_mon,    9,  3, "sep" },
  {   DT_str_mon,   10,  3, "oct" },
  {   DT_str_mon,   10,  3, "okt" },
  {   DT_str_mon,   11,  3, "nov" },
  {   DT_str_mon,   12,  3, "dec" },
  {   DT_str_mon,   12,  3, "dez" },
  {   DT_str_tz,     1,  3, "cet" },
  {   DT_str_tz,     1,  3, "mez" },
  {   DT_str_tz,     1,  6, "metdst" },
  {   DT_str_tz,     1,  3, "met" },
  {   DT_str_tz,     1,  3, "wut" },    /* WU time ???? */
  {   DT_str_tz,     0,  3, "bst" },    /* british standard time? */
  {   DT_str_tz,     0,  3, "gmt" },
  {   DT_str_tz,    -4,  3, "edt" },
  {   DT_str_tz,    -5,  3, "cdt" },
  {   DT_str_tz,    -6,  3, "mdt" },
  {   DT_str_tz,    -7,  3, "pdt" },
  {   DT_str_tzm,    1,  3, "dst" }     /* daylight savings time */
} ;

/* ------------------------------------------------------------------------ */
int analyze_dat_str (
char *name,
int dat_val [],
int dat_typ [],
int *dat_stack,
int STACK_SIZE)
{
  int typ, value;
  int i;

  typ= -1;
  if (*dat_stack >= STACK_SIZE) return -1;

# ifdef DEBUG
  printf ("[%2d]='%s'\n", *dat_stack, name);
# endif
  for (i= 0; i < N_date_strings; i++)
  {
    if (strncmp (name,
                 date_strings[i].DStr_str,
                 date_strings[i].DStr_min_str) == 0)
    {
      typ= date_strings[i].DStr_type;
      value= date_strings[i].DStr_value;
      break;
    }
  }

  switch (typ)
  {
    case DT_str_tz:
    case DT_str_tzm:
    case  3:
    case DT_str_mon:
      dat_typ [*dat_stack    ]= typ;
      dat_val [(*dat_stack)++]= value;
      return  0;
    default:
      return -1;
  }
}
