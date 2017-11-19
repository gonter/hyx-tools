/*
 *  FILE %ds/cal/dt022.c
 *
 *  operations with date and time
 *
 *  written:       1988 03 28: (as datum.c)
 *                 1991 06 24: revision
 *                 1994-05-07: revision: split up in more modules
 *  latest update: 1996-11-10 15:06:26
 *
 */

#include <string.h>
#include <gg/strings.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
#define N_mon 19
static char *monate [N_mon] =
{
  "j„n", "feb", "m„r", "apr", "mai", "jun",
  "jul", "aug", "sep", "okt", "nov", "dez",
  "jae", "jan", "mae",
  "mar", "may", "oct", "dec"
} ;

/* ------------------------------------------------------------------------ */
static int monatnum [N_mon] =
{
   1,  2,  3,  4,  5,  6,
   7,  8,  9, 10, 11, 12,
   1,  1,  3,
   3,  5, 10, 12
} ;

/* ------------------------------------------------------------------------ */
int get_datum (
char *s,        /* Datumsstring */
int zone_begin,
int zone_end,         /* Laenge von s */
int *jahr,
int *mon,
int *tag)
{
  int i, c;
  int ms= -1;
  int mi= 1;
  char monat [20];

  *jahr= *mon= *tag= 0;

  for (i= 0; (c= s [i]) && mi; i++)
       if (c < '0' || c > '9') mi= 0;

  if (mi)
  {
    mi= 0;
    for (i= zone_begin; s [i] && i < zone_end; i++)
    {
      c= s [i] -'0';
      switch (i)
      {
        case  0: *jahr =              c; break;
        case  1: *jahr = 10*(*jahr) + c; break;
        case  2: *mon  =              c; break;
        case  3: *mon  = 10*(*mon)  + c; break;
        case  4: *tag  =              c; break;
        case  5: *tag  = 10*(*tag)  + c; break;
        case  6:  mi   =              c; break;
        case  7:  mi   = 10*mi      + c; break;
      }
    }

    if (*jahr > 31)
    {
      *jahr += 1900;
      return 0;
    }

    if (*mon > 31 && *jahr >= 15 && *jahr <= 21)
    {
      *jahr= (*jahr) * 100 + (*mon);
      *mon  = *tag;
      *tag  = mi;
      return 0;
    }

    if (*tag > 31)
    {
      mi   = *tag;
      *tag  = *jahr;
      *jahr =  mi + 1900;
      return 0;
    }

    if (mi > 31 && *tag >= 15 && *tag <= 21)
    {
      c     = *tag;
      *tag  = *jahr;
      *jahr =  mi + c*100;
      return 0;
    }
    return -1;
  }

  i= 0;
  get_jahr_mon_tag (s, &i, jahr, monat, 0, &ms);
  get_jahr_mon_tag (s, &i, mon,  monat, 1, &ms);
  get_jahr_mon_tag (s, &i, tag,  monat, 2, &ms);

  if (ms != -1)
  {
    to_lower (monat);
    for (i = 0; i < N_mon; i++)
      if (strncmp (monate [i], monat, 3) == 0)
      {
        mi = monatnum [i];
        break;
      }
    if (i == N_mon) return -1;
  }

  i = 0;
  if (*jahr == 0) i++;
  if (*mon  == 0) i++;
  if (*tag  == 0) i++;

  if (ms == -1)
  {
    if (i > 0) return -1;
      if (*tag  > 31)
      {
        i     = *tag;
        *tag  = *jahr;
        *jahr = i;
      }
    return 0;
  }
  else
  {
    if (i > 1) return -1;
    switch (ms)
    {
      case  0:
        if (*tag > 31)
        {
          *jahr = *tag;
          *tag  = *mon;
        }
        else   *jahr = *mon;
        break;
      case  1:
        if (*tag > 31)
        {
          i    = *jahr;
          *jahr = *tag;
          *tag  =  i;
        }
        break;
      case  2:
        if (*jahr > 31)
          *tag  = *mon;
        else
        {
          i    = *jahr;
          *jahr = *mon;
          *tag  =  i;
        }
        break;
      default:
        return -1;
    }
    *mon = mi;
    return 0;
  }

  return 0;
}
