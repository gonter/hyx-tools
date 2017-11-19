/*
 *  FILE %ned/02/ned0245.c
 *
 *  vi emulation: double key sequences
 *  see also: ned0319.c NED_interpreter
 *
 *  written:       1993-08-01
 *  latest update: 2001-02-11 11:48:09
 *  $Id: ned0245.c,v 1.3 2001/02/12 00:03:25 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>
#ifdef USE_MOUSE
#include <gg/maus.h>
#endif

extern struct WINDOWCTRL *aw;
extern int akt_page;
extern int COL_STATUS;
extern int key;
extern int block_mode;
extern ned_input_handler *nextchar;  /* Editor Eingabe: KBD | FILE ..       */

/* ------------------------------------------------------------------------ */
void vi_dkey ()
{
  int first_key;
  int t1;
  char key_str [5];

  if (aw == (struct WINDOWCTRL *) 0) return;

  first_key= key;

  key_str [0]= 'V';
  key_str [1]= 'I';
  key_str [2]= (char) key;
  key_str [3]= '?';
  key_str [4]= 0;

  w_setstring (akt_page, aw->ax+4, aw->ay-1, aw->ax+7, aw->ay-1,
               COL_STATUS, key_str, 0x01);

#ifdef USE_MOUSE
  key= check_maus ();
#else
  key= (*nextchar) ();
#endif

  switch (first_key)
  {
    case 0x17:          /* ^W, VIM extension */
      switch (key)
      {
        case 'f':
          p_ofile1 ();
          break;
      }
      break;

    case 'm':
      if (ned_set_marker (aw, key) == -1) vi_bell ();
      break;

    case '`':
    case '\'':
      /*** TMP if (key != '`' && key != '\'') ned_set_marker (aw, '\''); ***/
      if (ned_jmp_marker (key, (first_key == '\'') ? 0x0001 : 0x0000) == -1)
        vi_bell ();
      break;

    case 'Z':
      switch (key)
      {
        case 'Z':
          p_ssave ();
          break;
      }
      break;

    case 'c':
      switch (key)
      {
        case 'c':
          vi_change_line ();
          break;
        case 'w':       /* cw and ce seem to be the same in VI */
        case 'e':
          vi_change_text (aw, VI_CHG_WORD, 1);
          set_repeat_command ((void *) 0);
          break;
        case 'W':       /* cW and cE seem to be the same in VI */
        case 'E':
          vi_change_text (aw, VI_CHG_WORD4, 1);
          set_repeat_command ((void *) 0);
          break;
        case '$':
          vi_change_2eoln ();
          break;
        case '^':
        case '0':
          vi_change_2boln ();
          break;
      }
      break;

    case 'd':
      switch (key)
      {
        case 'd':
          /* fuer VI puristen, T2D: ned_fresh_buffer () */
          block_mode= BLOCK_MODE_line;
          ned_delete_line ();
          break;
        case 'e': /* delete to end of word (OK) */
          ned_delete_word ();
          break;
        case 'E': /* delete to end of word (OK) */
          ned_delete_word_4 ();
          break;
        case 'w': /* as above including blanks at end of word */
          ned_delete_word_2 ();
          break;
        case 'W': /* as above including blanks at end of word */
          ned_delete_word_3 ();
          break;
        case '$':
          ned_del2eoln ();
          break;
        case '^':
        case '0':
          ned_del2boln ();
          break;
      }
      break;

    case 'f': case 'F':
    case 't': case 'T':
      key_str [0]= (char) key;
      key_str [1]= 0;
      if (ned_vi_wc_find_str (aw, key_str, 1, first_key) == -1) vi_bell ();
      break;

    case 'r':
      t1= aw->ins_flg;
      aw->ins_flg= INSFLG_overwrite;
      if (key == 0x0A || key == 0x0D)
      {
        ned_wc_delete (aw, 1);
        p_nl ();
      }
      else
        if (key != 0x1B) q_insert (key, 1);
      aw->ins_flg= t1;
      break;

    case 'y':
      ned_set_marker (aw, '(');
      switch (key)
      {
        case '$':
          ned_jmp_eoln ();
          ned_set_marker (aw, '}');
          ned_jmp_marker ('[', 0x0000);
          break;
        case '%':
          ned_group_set_marker ();
          ned_jmp_marker ('[', 0x0000);
          break;
        case 'e':
        case 'w':
          ned_wc_word_lr (aw, JMPWRD_right_end);
          ned_cursor_right ();
          ned_set_marker (aw, '}');
          ned_jmp_marker ('[', 0x0000);
          break;
        case 'E':
        case 'W':
          ned_wc_word_lr (aw, JMPWRD_right_end_2);
          ned_cursor_right ();
          ned_set_marker (aw, '}');
          ned_jmp_marker ('[', 0x0000);
          break;
        case 'y':
          ned_set_marker (aw, ']');
          break;
      }

      ned_yank_block (0);
      break;

    case 'z':
      /* Note: it is not necessary to count the current line number here */

      switch (key)
      {
        case 0x0D: case 0x0A:           /* original vi */
        case '/': case 't':             /* ned extension */
          ned_w_jmp_aktline (aw, NEDJMP_LINE_TOP, 0, NEDJMP_FLAG_STD);
          break;
        case '+': /* vi: next page */
          ned_w_jmp_aktline (aw, NEDJMP_LINE_TOP,
                             aw->by - aw->ay, NEDJMP_FLAG_STD);
          break;
        case '.':       /* vi   */
        case 'm':       /* ned  */
        case 'z':       /* vim? */
          ned_w_jmp_aktline (aw, NEDJMP_LINE_MID, 0, NEDJMP_FLAG_STD);
          break;
        case ',':       /* non standard extension */
          ned_w_jmp_aktline (aw, NEDJMP_LINE_3, 0, NEDJMP_FLAG_STD);
          break;
        case '^':       /* vi: prev page */
          ned_w_jmp_aktline (aw, NEDJMP_LINE_TOP,
                             aw->ay - aw->by, NEDJMP_FLAG_STD);
          break;
        case '-':       /* vi   */
        case 'b':       /* ned  */
          ned_w_jmp_aktline (aw, NEDJMP_LINE_BOT, 0, NEDJMP_FLAG_STD);
          break;
      }
      break;

  }

#ifdef USE_MOUSE
  maus_enable ();
#endif
}
