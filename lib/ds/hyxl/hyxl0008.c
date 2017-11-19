/*
 *  FILE %ds/hyxl/hyxl0008.c
 *
 *  written:       1996-03-07
 *  latest update: 1996-03-15
 *  $Id: hyxl0008.c,v 1.3 2005/09/04 20:27:37 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
char *hyx_make_stop_tag (const char *s)
{
  int i, ch;
#define STAT_BEGIN 0
#define STAT_TAG   1
#define STAT_IN_TAG 2
  int status= STAT_BEGIN;
  int t_beg, t_end;
  int siz;
  char *cp;

  if (s == (char *) 0 || *s == 0) return (char *) 0;

  for (i= 0; (ch= s [i] & 0x00FF) != 0; i++)
  {
    switch (status)
    {
      case STAT_BEGIN:
        status= (ch == '<') ? STAT_TAG : -1;
        break;
      case STAT_TAG:
        if ((ch >= 'a' && ch <= 'z')
            || (ch >= 'A' && ch <= 'Z')
            || (ch >= '0' && ch <= '9')
            || ch == '.' || ch == '_'
           )
        {
          t_beg= i;
          t_end= i;
          status= STAT_IN_TAG;
        }
        break;

      case STAT_IN_TAG:
        if ((ch >= 'a' && ch <= 'z')
            || (ch >= 'A' && ch <= 'Z')
            || (ch >= '0' && ch <= '9')
            || ch == '.' || ch == '_' || ch == '-'
           )
        {
          t_end= i;
        }
        else
          goto DONE;
        break;

      default:
        return (char *) 0;
    }
  }

DONE:
  siz= t_end-t_beg+1;
  if (siz < 64
      && (cp= malloc (siz+6)) != (char *) 0
     )
  {
    strncpy (cp+2, s+t_beg, siz);
    cp [0]= '<';
    cp [1]= '/';
    cp [siz+2]= '>';
    cp [siz+3]= 0;
    return cp;
  }

  return (char *) 0;
}
