/*
 *  FILE %ds/cal/dt031.c
 *
 *  analyze a string in a Date: line
 *
 *  written:       1989 10 13
 *                 1991 09 16: Revision
 *                 1991 09 21: timezones
 *                 1994-05-14: restructuring and renaming
 *                             (was: ~/usr/mail/datanal.c)
 *  latest update: 1997-08-20 18:18:14
 *  $Id: dt031.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/dates.h>

#define STACK_SIZE 20

/* ------------------------------------------------------------------------ */
int analyze_date (
const char *s,
int *jahr,
int *mon,
int *tag,
int *std,
int *minutes,
int *sek,
int *x_timezone)                  /* time zone offset */
{
#define STAT_start      0
#define STAT_string     1
#define STAT_integer    2
  int stat=STAT_start;
  int ch, sidx;
  int value;
  int signum= 0;
  int f_jahr= 0;
  int dat_stack= 0;
  int dat_typ [STACK_SIZE];
  int dat_val [STACK_SIZE];
  int dat_sgn [STACK_SIZE];
  char dat_name [40];

  *mon= -1;  *tag= -1;      *jahr= -1;
  *std= -1;  *minutes= -1;  *sek= -1;
  *x_timezone= 0;
  if (s == (char *) 0 || *s == 0) return -1;

  for (;; s++)
  {
    ch= *s;

    switch (stat)
    {
      case STAT_start:
        if (ch >= 'A' && ch <= 'Z')
        {
          ch= ch + 'a' - 'A';
          signum= 0;
          goto X0;
        }

        if (ch >= 'a' && ch <= 'z')
        {
X0:       sidx= 0;
          dat_name [sidx++]= (char) ch;
          stat= STAT_string;
          signum= 0;
        } else
        if  (ch >= '0' && ch <= '9')
        {
          value= ch - '0';
          stat= STAT_integer;
          sidx= 0;
          dat_name [sidx++]= (char) ch;
        } else
        if (ch == '-') signum= 1; else
        if (ch == '+') signum= 2; else
                       signum= 0;
        break;

      case STAT_string:
        if (ch >= 'A' && ch <= 'Z')
        {
              ch = ch + 'a' - 'A';
              goto X1;
        }
        if (ch >= 'a' && ch <= 'z')
        {
X1:           if (sidx >= STACK_SIZE) stat=0;
              else dat_name [sidx++]= (char) ch;
        }
        else
        if (ch >= '0' && ch <= '9')
        {
          dat_name [sidx]= 0;
          analyze_dat_str (dat_name,dat_val,dat_typ, &dat_stack,STACK_SIZE);
          value= ch - '0';
          stat= 2;
        }
        else
        {
          stat= 0;
          dat_name [sidx]= 0;
          analyze_dat_str (dat_name,dat_val,dat_typ, &dat_stack,STACK_SIZE);
        }
        break;

      case STAT_integer:
        if (ch >= 'A' && ch <= 'Z')
        {
          ch= ch + 'a' - 'A';
          goto X3;
        }
        if (ch >= 'a' && ch <= 'z')
        {
X3:       if (dat_stack >= STACK_SIZE) break;
          dat_name [sidx]= 0;
          dat_typ [dat_stack]= check_for_timezone (&value, &signum, dat_name);
          dat_sgn [dat_stack]= signum;
          dat_val [dat_stack]= value;
          dat_stack++;
          signum= 0;
          sidx= 0;
          dat_name [sidx++]= (char) ch;
          stat= 1;
        }
        else
        if (ch >= '0' && ch <= '9')
        {
          value= value*10 + ch - '0';
          dat_name [sidx++]= (char) ch;
          dat_name [sidx]= 0;
        }
        else
        {
          stat= 0;
          if (dat_stack >= STACK_SIZE) break;
          dat_name [sidx]=0;
          dat_typ [dat_stack] =
            check_for_timezone (&value, &signum, dat_name);
          dat_sgn [dat_stack] = signum; signum=0;
          dat_val [dat_stack++] = value;
        }
        break;
    }
    if (ch == 0) break;
  }

  for (stat= 0; stat < dat_stack; stat++)
    if (dat_typ [stat] == DT_str_mon)   /* month string; expected format:   */
                                        /* dd mmm (yy)yy                    */
    {
      if (stat > 0 && dat_typ [stat-1] ==  1 && dat_val [stat-1] <= 31)
        dat_typ [stat-1]= DT_int_day;

      if (stat+1 < dat_stack
          && dat_typ [stat+1] == 1
          && dat_val [stat+1] < 2000
         )
      {
        if (dat_val [stat+1] <= 31 && dat_val [stat+1] >= 1)
          dat_typ [stat+1]= DT_int_day;
        else
        {
          dat_typ [stat+1]= DT_int_year;
          f_jahr=1;
        }
        stat+=2;
      }
      break; /* ... */
    }

  /* hours */
  if (stat < dat_stack)
    if (dat_typ [stat] == 1 && dat_val [stat] <= 24)
      dat_typ [stat++]= 301;

  /* minutes */
  if (stat < dat_stack)
     if (dat_typ [stat] == 1 && dat_val [stat] <= 59)
       dat_typ [stat++]= 302;

  /* seconds */
  if (stat < dat_stack)
     if (dat_typ [stat] == 1 && dat_val [stat] <= 59)
       dat_typ [stat++]= 303;

  if (f_jahr == 0)
    for (stat= 0; stat < dat_stack; stat++)
    {
      if (dat_typ [stat] == DT_int
          && ((dat_val [stat] > 31 && dat_val [stat] <= 99)
              || dat_val [stat] > 1900
             )
         )
      {
        if (dat_val [stat] > 31 && dat_val [stat] <= 99)
          dat_val [stat] += 1900;
        dat_typ [stat]= DT_int_year;
        f_jahr= 1;
        break;
      }
    }

#ifdef DEBUG
  for (stat=0; stat < dat_stack; stat++)
  {
    printf ("[%2d] typ=%3d val=%4d sgn=%d",
            stat, dat_typ [stat], dat_val [stat], dat_sgn [stat]);
    switch (dat_typ [stat])
    {
      case DT_str_mon:  printf (" <-- Monat");  break;
      case 201:         printf (" <-- Tag");    break;
      case DT_int_year: printf (" <-- Jahr");   break;
      case 301:         printf (" <-- Stunde"); break;
      case 302:         printf (" <-- Minute"); break;
      case 303: printf (" <-- Sekunde");break;
      case DT_str_tz: printf (" <-- timezone"); break;
      case DT_str_tzm: printf (" <-- timezone modifier"); break;
    }
    putchar ('\n');
  }
#endif

  for (stat= 0; stat < dat_stack; stat++)
    switch (dat_typ [stat])
    {
      case DT_str_mon:          *mon            = dat_val [stat]; break;
      case DT_str_tz:           *x_timezone     = dat_val [stat]; break;
      case DT_str_tzm:          *x_timezone    += dat_val [stat]; break;
      case 201:                 *tag            = dat_val [stat]; break;
      case DT_int_year:         *jahr           = dat_val [stat]; break;
      case 301:                 *std            = dat_val [stat]; break;
      case 302:                 *minutes        = dat_val [stat]; break;
      case 303:                 *sek            = dat_val [stat]; break;
    }

  /* assign remaining integers to remaining slots */
  for (stat= 0; stat < dat_stack; stat++)
  {
    if (dat_typ [stat] == 1)
    {
      if (*mon == -1) *mon= dat_val [stat]; else
      if (*tag == -1) *tag= dat_val [stat]; else
      if (*std == -1) *std= dat_val [stat]; else
      if (*minutes == -1) *minutes= dat_val [stat]; else
      if (*sek == -1) *sek= dat_val [stat];
    }
  }

  return 0;
}
