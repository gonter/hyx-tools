/*
 *  FILE %ned/02/ned0244.c
 *
 *  vi emulation: read commands for ex mode
 *
 *  written:       1993-07-31
 *  latest update: 2000-12-09 12:55:41
 *  $Id: ned0244.c,v 1.7 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
void vi_ex ()
{
#define B_SIZ 128
  char buffer [B_SIZ];

  buffer [0]= 0;
  if (rd_str (":", buffer, B_SIZ) == -1) return;

  if (vi_ex_interp (buffer) == -1)
  {
    ned_message_2 ("unsupported ex command: ", buffer);
  }
}

extern struct WINDOWCTRL *aw;
#define LOGIC_LINK(dir)  eval_logic_link (aw, (dir))
/* ------------------------------------------------------------------------ */
int vi_ex_interp (char *buffer)
{
  int beg;
  int lnr;
#define MAX_FIELDS 3
  char *fields [MAX_FIELDS];

  if ((beg= (int) buffer [0]) == 0) return 0;

  if (beg == '!') q_shell (buffer+1); else
  if (beg == '\"') mac_call_tcl (buffer+1); else
  if (beg == '@') ned_tcl_run_file (buffer+1); else
  if (beg == '<') ned_paste_tcl (buffer+1); else
  if (beg == '=') ned_show_total_lines (); else
  if (beg == '/') ned_jmp_pattern (aw, aw->WC_act, buffer+1, 0x0000); else
  if (beg == '?') ned_jmp_pattern (aw, aw->WC_act, buffer+1, OPT_backward); else
  if (beg == ':') ex_tag_command (buffer+1);  else

  if (strcmp (buffer, "^k") == 0) p_ctrlk (); else
  if (strcmp (buffer, "^o") == 0) p_ctrlo (); else
  if (strcmp (buffer, "^q") == 0) p_ctrlq (); else
  if (strcmp (buffer, "^s") == 0) ned_cursor_left (); else
  if (strcmp (buffer, "^a") == 0
      || strcmp (buffer, "alt") == 0) p_ctrlu (); else

  if (strncmp (buffer, "tag ", 4) == 0
    ||strncmp (buffer, "tag!", 4) == 0) ex_tag_command (buffer+4);  else
  if (strncmp (buffer, "crf ", 4) == 0)
    ned_cross_ref (buffer+4, 0, CRF_IN_CRF, CRF_GLOBAL_AND_LOCAL, 1);
  else
  if (strncmp (buffer, "all", 3) == 0)
  {
    int i;
    int ch;
    int c_mstr= 0;
    int use_matching= 1;
    char *mstr[2];
#define MAX_WORD_BUFF 40
    char word_buff [MAX_WORD_BUFF];

    for (i= 3; (ch= buffer [i]) != 0; i++)
    {
      if (ch == '!' && use_matching) { use_matching= 0; continue; }
      if (!(ch == ' ' || ch == '/')) break;
    }

    if (buffer [i] != 0)
    {
      if (buffer [i] == '`')
      {
        q_isolate_word (word_buff, MAX_WORD_BUFF-1, CHARSET_filename, 0);
        mstr [0]= word_buff;
      }
      else mstr [0]= buffer+i;
      c_mstr= 1;
    }

    ned_all_lines (aw, use_matching, c_mstr, mstr);
    p_refresh ();
  }
  else
  if (strncmp (buffer, "abbrev ", 7) == 0 || strncmp (buffer, "ab ", 3) == 0)
  {
    if (isolate_tokens (buffer, fields, 3) >= 3)
      ned_define_abbrev (fields [1], fields [2]);
  }
  else
  if (strncmp (buffer, "unabbreviate ", 13) == 0
      || strncmp (buffer, "una ", 4) == 0)
  {
    if (isolate_tokens (buffer, fields, 2) >= 2)
      ned_undefine_abbrev (fields [1]);
  }
  else
  if (strncmp (buffer, "set", 3) == 0) ex_set_command (buffer);
  else

#ifdef __TEST_SYM_BMK__ /* 1998-07-19 17:51:27 */
... replaced by note cluster system ...
  if (strcmp (buffer, "cl0")            == 0
    ||abbrev ("start", buffer, 3)       == 1) p_activate_cl0 ();        else
  if (strcmp (buffer, "cl1")            == 0
    ||abbrev ("help", buffer, 1)        == 1) p_activate_cl1 ();        else
  if (strcmp (buffer, "cl2")            == 0
    ||abbrev ("notes", buffer, 2)       == 1) p_activate_cl2 ();        else
  if (strcmp (buffer, "cl3")            == 0) p_activate_cl3 ();        else
  if (strcmp (buffer, "cl4")            == 0
    ||abbrev ("t2d",  buffer, 2)        == 1) p_activate_cl4 ();        else
#endif /* __TEST_SYM_BMK__ 1998-07-19 17:51:27 */

  if (abbrev ("next", buffer, 2)        == 1) LOGIC_LINK ("next");      else
  if (abbrev ("prev", buffer, 2)        == 1) LOGIC_LINK ("prev");      else
  if (abbrev ("up",   buffer, 2)        == 1) LOGIC_LINK ("up");        else
  if (abbrev ("up",   buffer, 2)        == 1) LOGIC_LINK ("lang");      else
  if (abbrev ("down", buffer, 2)        == 1) LOGIC_LINK ("menu");      else
  if (abbrev ("root", buffer, 2)        == 1) p_activate_fr_root ();    else
  if (strcmp (buffer, "o")              == 0) p_wdwopen ();             else
  if (strncmp (buffer, "ow", 2)         == 0) q_wdwsize (buffer[2]);    else
  if (strcmp (buffer, "e")              == 0) p_ofile2 ();              else
  if (strncmp (buffer, "e ", 2)         == 0) ex_e_command (buffer);    else
  if (strcmp (buffer, "q!")             == 0
    ||abbrev ("qquit", buffer, 2)       == 1) p_exit ();                else
  if (strcmp (buffer, "q")              == 0
    ||abbrev ("quit", buffer, 2)        == 1) p_abandon ();             else
  if (strcmp (buffer, "vi")             == 0) vi_mode ();               else
  if (strcmp (buffer, "ws")             == 0) wordstar_mode ();         else
  if (strcmp (buffer, "pico")           == 0) pico_mode ();             else
  if (strcmp (buffer, "w")              == 0
    ||strcmp (buffer, "w!")             == 0) p_save ();                else
  if (strcmp (buffer, "wq")             == 0
    ||abbrev ("xit", buffer, 1)
    ||abbrev ("file", buffer, 2)
    ||abbrev ("ffile", buffer, 2)           ) p_ssave ();               else
  if (strcmp ("fffile", buffer)         == 0) ned_ssave_all ();         else
  if (strcmp (buffer, "wq!")            == 0) p_sx ();                  else
  if (abbrev ("version", buffer, 2)         ) ned_show_version ();      else
  if (strcmp (buffer, "$")              == 0
    ||abbrev ("bottom", buffer, 3)          ) pq_dn ();                 else
  if (strcmp (buffer, "1")              == 0
    ||strcmp (buffer, "top")            == 0) pq_up ();                 else
  if (strncmp (buffer, "D ", 2) == 0)
  {
    if (isolate_tokens (buffer, fields, 2) >= 2)
      ned_debug_info (fields [1]);
  }
  else
  if (verify (buffer, "1234567890")     == 0)
  {
    lnr= (int) get_parameter_value (buffer);
    ned_jmp_2line_by_nr (aw, lnr, 3);
  }
  else
  if (strncmp (buffer, "defnote", 7) == 0)
  {
    int i;
    int create_mode= 0;
    int memorize= 0;

    for (i= 7; buffer [i]; i++)
    {
      switch (buffer [i])
      {
        case '!': create_mode= 1; break;
        case '?': memorize= 1; break;
        case ' ': case '\t': goto DONE;
      }
    }

DONE:
    if (isolate_tokens (buffer, fields, 3) >= 3)
      ned_define_note_cluster (fields [1], fields [2], create_mode, memorize);
  }
  else
  {
    char *b2;
    int res;

    if ((b2= strdup (buffer)) == (char *) 0)
    {
      printf ("0244: out of memory!\n");
      return -1;
    }

    /* ned_activate_note_cluster destroys the buffer! */
    res= ned_activate_note_cluster (b2);
    free (b2);
    if (res == 0) return 0;

#ifdef USE_TCL
    mac_call_tcl (buffer);
#else
    return -1;
#endif /* USE_TK */
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int ex_e_command (char *buffer)
{
  int flags= NED_OPENF_HISTORY | NED_OPENF_REDRAW;
  int fc, i;
  char *fnm= (char *) 0;
  char *arg;
#define MAX_E_FIELDS 3
  char *fields [MAX_E_FIELDS];
  int jmp_line= -1;
  char *jmp_pattern= (char *) 0;

  if ((fc= isolate_tokens (buffer, fields, MAX_E_FIELDS)) >= 2)
  {
    for (i= 1; i < fc; i++)
    {
      arg= fields [i];
      if (strcmp (arg, "[sgml]") == 0) flags |= NED_OPENF_SGML; else
      if (arg [0] == '+')
      {
        switch (arg [1])
        {
          case 0:
          case '$':
            jmp_line= 32700;
            break;
          case '/':
          case '?':
            jmp_pattern= arg+1;
            break;
          default:
            jmp_line= (int) get_parameter_value (arg+1);
            break;
        }
      } else
      if (fnm == (char *) 0) fnm= arg;
    }

    if (fnm != (char *) 0)
    {
      ned_open_file (fnm, (char *) 0, (char *) 0, flags);

      /* from ned00.c; T2D: we have to assume that aw is now differnt! */
      ned_jmp_complex (aw, jmp_line, jmp_pattern);

      return 0;
    }
  }

  p_ofile2 ();
  return 0;
}

/* ------------------------------------------------------------------------ */
int ex_set_command (char *buffer)
{
  char *wp;

  wp= locate_word (buffer, 1);

  if (wp == (char *) 0)
  {
    goto NOP;
  }
  else if (strcmp (wp, "ic") == 0 || strcmp (wp, "ignorecase") == 0)
  {
    ned_set_ic (1);
  }
  else if (strcmp (wp, "noic") == 0 || strcmp (wp, "noignorecase") == 0)
  {
    ned_set_ic (0);
  }
  else if (strcmp (wp, "ws") == 0 || strcmp (wp, "wrapscan") == 0)
  {
    ned_set_wrapscan (1);
  }
  else if (strcmp (wp, "nows") == 0 || strcmp (wp, "nowrapscan") == 0)
  {
    ned_set_wrapscan (0);
  }
  else if (abbrev ("create", wp, 4) == 1)
  {
    ned_set_create_special (1);
  }
  else if (abbrev ("nocreate", wp, 6) == 1)
  {
    ned_set_create_special (0);
  }
  else
  {
NOP:
#ifdef USE_TK
    mac_call_tcl ("show_settings");
#else
    ned_message_1 ("not yet implemented!");
#endif
  }

  return 0;
}
