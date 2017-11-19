/*
 *  FILE %ned/11/ned1104.c
 *
 *  Text search and replace functions
 *  see: C API documentation
 *
 *  written:       1988 09 20
 *                 1989 06 18
 *                 1990 01 21: Revision
 *                 1991 02 02: Revision
 *  latest update: 1998-08-16 12:33:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#define __strrev_undefined__
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"
#include <gg/window.h>
#include <gg/strings.h>

extern struct MARKER b_beg, b_end;
extern int MPflag;

/* statische Variablen fuer Find & Replace: ------------------------------- */
#define FIND_STR_SIZE 82
#define REPL_STR_SIZE 82
#define OPT_STR_SIZE 20
static char find_str [FIND_STR_SIZE];
static char repl_str [REPL_STR_SIZE];
static char opt_str  [OPT_STR_SIZE];    /* Optionen und Ersatz-String       */

static int find_replace= -1;            /* -1 .. uninitialized              */
                                        /* 0 .. undefiniert                 */
                                        /* 1 .. Find                        */
                                        /* 2 .. Replace (Makro Execution)   */

static int option;
static int repeat_counter;

/* ------------------------------------------------------------------------ */
void ned_ws_find_replace_dialog (
struct WINDOWCTRL *wc,
int fr)                                 /* Find/Replace Mode:               */
                                        /* 0: Find/Replace Next             */
                                        /* 1: Find                          */
                                        /* 2: Replace                       */
{
  struct LINE *z_start;                 /* line where searching starts      */
  struct LINE *z_end;                   /* line where searching may stop    */
  int c_start;                          /* column where searching starts    */
  int something_found= 0;               /* >1 -> something was found        */
  int i, j;

  z_start= wc->WC_act;
  c_start= get_coln (wc);
  repeat_counter= 1;

  if (find_replace == -1 || MPflag)
  {
    find_str [0]= repl_str [0]= opt_str [0]= (char) 0;
    find_replace= 0;
  }

  ned_set_marker (wc, (fr == 0) ? '?' : '/');

  if (fr != 0 || find_replace == 0)
  {
    if (fr == 0) fr= 1;
    find_replace= fr;

    if (MPflag
        || (q_isolate_word (find_str, FIND_STR_SIZE-1, CHARSET_token, 0)
               == 0
           )
       )
      find_str [0]= 0;

    if (rd_str ("Find: ", find_str, FIND_STR_SIZE) == -1) goto ABORT;
    if (fr == 2)
    {
      /** repl_str [0]= 0; TEST: 1996-07-28 11:48:07 */
      if (rd_str ("Replace: ", repl_str, REPL_STR_SIZE) == -1) goto ABORT;
    }

    opt_str [0]= 0;
    if (rd_str ("Option: ", opt_str, OPT_STR_SIZE)  == -1) goto ABORT;

    /************ option String auswerten ***************/
    option= OPT_ask;  /* Default Option ev. per Setup !!! */
    j= 0;
    for (i= 0; opt_str [i]; i++)
      switch (opt_str [i])
      {
        case 'n': case 'N': option &= OPT_no_ask;   break;  /* No Asking */
        case 'a': case 'A': option |= OPT_ask;      break;  /*    Asking */
        case 'i': case 'I':                                 /* ign. Case */
        case 'l': case 'L':                                 /* ign. Case */
        case 'u': case 'U': option |= OPT_upper;    break;  /* ign. Case */
        case 'm': case 'M': option &= OPT_mixed;    break;  /*      Case */
        case 'g': case 'G': option |= OPT_global;   break;  /* Global    */
        case 'r': case 'R': option &= OPT_local;    break;  /* Lokal     */
        case 'b': case 'B': option |= OPT_backward; break;  /* Reverse   */
        case 'f': case 'F': option &= OPT_forward;  break;  /* Forward   */
        case 'x': case 'X': option |= OPT_end_mark; break;  /* Marker #1 */
        case 'y': case 'Y': /* Block */
          if (ned_blk_invalid () || wc != b_beg.wptr) break;
          option |= OPT_beg_block | OPT_end_block;
          break;
        case '0': case '1':
        case '2': case '3':
        case '4': case '5':
        case '6': case '7':
        case '8': case '9':
          j= j*10 + opt_str[i] - '0';
          break;
      }

    if (option & OPT_global)
    {
      /** if (fr == 2) TEST: 1996-07-28 11:50:26 **/
        repeat_counter= 32200;
      option &= OPT_forward;       /* global -> forward */
    }
    if (j) repeat_counter= j;
  } /* prompt and evaluation of options */

  /* set the begin and end position */
  z_end= (struct LINE *) 0;
  if (option & OPT_end_mark)
  {
    struct MARKER *mp;

    if ((mp= ned_get_marker ('1', 0)) != (struct MARKER *) 0)
      z_end= mp->ptr;
  }
  if (option & OPT_end_block) z_end= b_end.ptr;

  if (z_start == (struct LINE *) 0) goto GANZ_AUS;

  if (fr != 0 && (option & OPT_global))
  {
    z_start= ned_find_first_line (z_start);
    c_start= 0;
  }

  if (option & OPT_beg_block
      || ((option & OPT_end_block) && !(z_start->line_flg & LINE_inBLOCK))
     )
  {
    z_start= b_beg.ptr;
    c_start= 0;                 /* b_beg.offset */
    option &= OPT_no_ask;
  }

  if (fr == 0) c_start++;

  /* BEGIN find-replace function: ---------------------- */
  something_found= ned_wc_find_replace (wc, z_start, c_start, z_end,
                                     999, 0, option, find_replace,
                                     find_str, repl_str,
                                     999, repeat_counter,
                                     ned_get_marker ('9', 1));
  /* END find-replace function: ------------------------ */

GANZ_AUS:
  ned_message_1 ((something_found)
                  ? "search done ..."
                  : "nothing found ...");
  return;

ABORT:
  ned_message_1 ("aborted ...");
}

/* ------------------------------------------------------------------------ */
char *ned_prompt_find (char *prompt)
{
  find_str [0]= 0;
  find_replace= 1;

  if (rd_str (prompt, find_str, FIND_STR_SIZE) == -1) return (char *) 0;
  return find_str;      /* sigh ... */
}

/* ------------------------------------------------------------------------ */
int ned_save_search_string (char *s)
{
  find_replace= 1;

  if (s == find_str) return 0;  /* sigh... */

  return (strcpy_max (find_str, s, FIND_STR_SIZE) == (char *) 0) ? -1 : 0;
}

/* ------------------------------------------------------------------------ */
int ned_save_search_options (int opt)
{
  int rc;

  rc= option;
  option= opt;

  return rc;
}
