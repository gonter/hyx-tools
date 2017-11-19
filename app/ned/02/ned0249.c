/*
 *  FILE %ned/02/ned0249.c
 *
 *  vi emulation: join current line with next line
 *  - goto end of line, delete line end char
 *
 *  written:       1994-10-15
 *  latest update: 1999-05-01 10:24:05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void vi_join ()
{
  int cursor_index;
  int ch;
  int iflg;

  if (aw == (struct WINDOWCTRL *) 0) return;

  ned_jmp_eoln ();              /* goto end of the line */
  ned_del_char_right ();        /* join the next line   */

  cursor_index= aw->cx + aw->hv - aw->ax;
  if ((ch= get_txt (aw->WC_act, cursor_index)) == -1) return; /* ok: EOLN   */
  /* it's not necessary to delete or add anything at the End of a Line      */

  if (in_charset (ch, CHARSET_blank))
    ned_lp_delete_word (aw->WC_act, cursor_index, 0);

  iflg= aw->ins_flg;
  aw->ins_flg= INSFLG_insert;
  q_insert (0x20, 1);
  ned_cursor_left ();
  aw->ins_flg= iflg;
}
