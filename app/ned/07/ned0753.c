/*
 *  FILE %ned/07/ned0753.c
 *
 *  paste a string into the current window
 *
 *  written:       1995-11-09
 *  latest update: 1997-06-11 15:01:37
 *  $Id: ned0753.c,v 1.3 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_paste_string (
const char *buffer,
int ai_mode,
char *line_prefix,
char *line_postfix)
/* RETURN:                              */
/* -1 ... ERROR                         */
/* 0  ... no change                     */
/* >1 ... number of lines changed       */
{
  int ch;
  int ai;
  int i;
  int lines_changed= 0;
  int df= 0;

  if (aw == (struct WINDOWCTRL *) 0
      || buffer == (char *) 0
     ) return -1;

  ai= aw->ai;
  aw->ai= 0;

  if (*buffer) lines_changed= 1;

  while ((ch= (*buffer++ & 0x00FF)) != 0)
  {
    switch (ch)
    {
      case '\n':
        if (line_postfix != (char *) 0) q_insert_string (line_postfix, 0);
        p_nl ();
        if (*buffer) /* look ahead */
        {
          if (line_prefix != (char *) 0) q_insert_string (line_prefix, 0);
          for (i= ai_mode; i > 0; i--) q_insert (' ', 0);
        }
        lines_changed++;
        df= 0;
        break;

      default:
        q_insert (ch, 0);
        df= 1;
        break;
    }
  }

  aw->ai= ai;
  if (df) p_refresh ();

  return lines_changed;
}
