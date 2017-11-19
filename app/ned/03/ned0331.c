/*
 *  FILE %ned/03/ned0331.c
 *
 *  written:       1991 01 31
 *  latest update: 1999-05-01  9:14:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_lp_delete_word (struct LINE *lp, int delete_idx, int mode)
{
  int ch;
  int current;
  int charset= CHARSET_token;
  int delete_blanks= 0;

  if ((ch= get_txt (lp, delete_idx)) == -1) return;     /* nothing to do... */

  current= in_charset (ch, (charset= CHARSET_blank));
  if (current == 0)
  {
    charset= (mode == 3 || mode == 4) ? CHARSET_non_blank : CHARSET_token;
    current= in_charset (ch, charset);

    if (mode == 2 || mode == 3) delete_blanks= 1;
  }

AGAIN:
  do
  {
    qq_delete (lp, delete_idx, 1);
    ch= get_txt (lp, delete_idx);
  }
  while (in_charset (ch, charset) == current && ch != -1);

  if (delete_blanks && ch != -1)
  {
    current= in_charset (ch, (charset= CHARSET_blank));
    delete_blanks= 0;
    if (current) goto AGAIN;
  }
}
