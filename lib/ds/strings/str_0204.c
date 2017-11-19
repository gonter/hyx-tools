/*
 *  FILE ~/usr/sbr/str_0204.c
 *
 *  strip a string (see REXX)
 *
 *  written:       1993-04-23
 *  latest update: 1993-09-27
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int strip (char *string, char *where)
{
  int ch;
  int str_lead=  0;
  int str_trail= 0;
  int str_inter= 0;
  char *dest;
#define STAT_top        0
#define STAT_char       1
#define STAT_blank      2
  int stat=STAT_top;
  int blank_count;

  if (string == (char *) 0) return -1;

  if (where != (char *) 0 && *where != 0)
  {
    for (; ch= *where; where++)
      switch (ch)
      {
        case 'l': case 'L':
          str_lead= 1;
          break;
        case 'b': case 'B':
          str_lead= 1;
        case 't': case 'T':
          str_trail= 1;
          break;
        case 'i': case 'I':
          str_inter= 1;
          break;
      }
  }
  else
    str_lead= str_trail= 1;

  dest= string;
  while (ch= (int) *string++)
  {
    switch (stat)
    {
      case STAT_top:
        if (ch == ' ' || ch == '\t')
        {
          if (!str_lead) *dest++= (char) ch;
        }
        else
        {
          stat= STAT_char;
          *dest++= (char) ch;
        }
        break;
      case STAT_char:
        if (ch == ' ' || ch == '\t')
        {
          stat= STAT_blank;
          blank_count= 1;
        }
        else
          *dest++= (char) ch;
        break;
      case STAT_blank:
        if (ch == ' ' || ch == '\t')
          blank_count++;
        else
        {
          stat= STAT_char;

          if (!str_inter)
            while (blank_count-- > 0)
              *dest++= ' ';
          else *dest++= ' '; /* just once if stripping is on */

          *dest++= (char) ch;
        }
        break;
      default:
        return -1;
    }
  }

  if (!str_trail)
    while (blank_count-- > 0)
      *dest++= ' ';

  *dest= 0;

  return 0;
}
