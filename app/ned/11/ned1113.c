/*
 *  FILE %ned/11/ned1113.c
 *
 *  Text search and replace functions
 *  see: C API documentation
 *
 *  written:       1997-01-12
 *  latest update: 1998-08-16 19:15:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

static int ignore_case= 0;
static int wrapscan= 1;

/* ------------------------------------------------------------------------ */
int ned_jmp_pattern (
struct WINDOWCTRL *wc,
struct LINE *lp,
char *pattern,
int back)
{
  int options= 0;
  
  ned_set_marker (wc, '/');
  if (pattern != (char *) 0) ned_save_search_string (pattern);

  if (back)             options |= OPT_backward;
  if (ignore_case)      options |= OPT_upper;
  if (wrapscan)         options |= OPT_wrapscan;

  ned_save_search_options (options);

  return ned_wc_find_replace (wc, lp, get_coln(wc),
                              (struct LINE *) 0, 12345, 0,
                              options, 1, pattern, (char *) 0, 1, 1,
                              ned_get_marker ('9', 1));
}

/* ------------------------------------------------------------------------ */
int ned_jmp_complex (
struct WINDOWCTRL *wc,
int jmp_line,
char *jmp_pattern)
{
  if (jmp_line > 0) ned_jmp_2line_by_nr (wc, jmp_line, 0x00);

  if (jmp_pattern != (char *) 0)
  {
    int opt;
    opt= (*jmp_pattern == '?') ? OPT_backward : 0;

    ned_jmp_pattern (wc, (jmp_line > 0)
                         ? wc->WC_act
                         : ((opt)
                            ? ned_find_last_line (wc->WC_act)
                            : ned_find_first_line (wc->WC_act)),
                     jmp_pattern+1, opt);
    jmp_pattern= (char *) 0;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int vi_find (struct WINDOWCTRL *wc, int back)
{
  char *pattern;

  if ((pattern= ned_prompt_find ((back) ? "?" : "/")) == (char *) 0)
    return -1;

  return ned_jmp_pattern (wc, wc->WC_act, pattern, back);
}

/* ------------------------------------------------------------------------ */
void ned_set_ic       (int mode) { ignore_case= mode; }
void ned_set_wrapscan (int mode) { wrapscan=    mode; }
