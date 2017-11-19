/*
 *  FILE %ned/11/ned1106.c
 *
 *  written:       1991 02 02
 *                 1991 12 31: revision and bug fix
 *                 1992 01 02: extension: find matching, higher level
 *                             or lower level bracket
 *  latest update: 1997-06-13 13:36:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/window.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
#define N_BRACKETS 10
static unsigned char brackets[] = "()[]{}<>\256\257";

/* ------------------------------------------------------------------------ */
int ned_is_bracket (int chx)
{
  int i;

  for (i= 0; i < N_BRACKETS; i++)
    if ((int) brackets [i] == chx) return 1;

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_find_bracket (int mode)
{
  int i;
  int chx;
  unsigned char search [10];
  unsigned char ignore [10];
  struct LINE *z_fnd;
  int c_start;
  int c_fnd;
  int m_lng;
  int match_level= 0;
  int direction= 0x0000;        /* 0 | OPT_backward                         */
  int search_valid= 0;          /* 1 -> we can search                       */

  if ((chx= get_txt (aw->WC_act, c_start= aw->cx + aw->hv - aw->ax)) == -1)
    return -1;

  if (chx == '/' || chx == '*')
  {
    int chx_pre;
    int chx_post;

    chx_pre= get_txt (aw->WC_act, c_start-1);
    chx_post= get_txt (aw->WC_act, c_start+1);

    if ((chx == '/' && chx_post == '*') || (chx == '*' && chx_pre == '/'))
    { /* opening c comment found */
      search_valid= 1;
      strcpy ((char *) search, "*/");
    }

    if ((chx == '/' && chx_pre == '*') || (chx == '*' && chx_post == '/'))
    { /* closing c comment found */
      search_valid= 1;
      strcpy ((char *) search, "*/");    /* reversed string! */
      direction= OPT_backward;
    }

    ignore [0]= 0;
    match_level= -1;
    goto DO_SEARCH;
  }

  for (i= 0; i < N_BRACKETS; i++)
    if ((int) brackets [i] == chx)
    {
      switch (mode)
      {
        case 1: /* matching bracket */
          search [0]= brackets [(i%2) ? i-1 : i+1];
          ignore [0]= (unsigned char) chx;
          match_level= 0;
          direction= (i%2) ? OPT_backward : 0x0000;
          break;

        case 2: /* higher bracket */
          ignore [0]= brackets [(i%2) ? i-1 : i+1];
          search [0]= (unsigned char) chx;
          match_level= -2;
          direction= (i%2) ? OPT_backward : 0x0000;
          break;

        case 3: /* lower bracket */
          ignore [0]= brackets [(i%2) ? i-1 : i+1];
          search [0]= (unsigned char) chx;
          match_level= -2;
          direction= (i%2) ? 0x0000 : OPT_backward;
          break;

        default:
          return -1;
      }

      search [1]= 0;
      ignore [1]= 0;
      search_valid= 1;
    }

  if (!search_valid)
  {
    /* T2D */
  }

DO_SEARCH:
  if (search_valid)
  {
    if (ned_str_match (aw->WC_act, c_start, (struct LINE *) 0,
                   search, ignore, match_level,
                   &z_fnd, &c_fnd, &m_lng,
                   direction) == 0)
    {
      aw->WC_act= z_fnd;
      aw->cx= c_fnd - aw->hv + aw->ax;
      ned_w_jmp_aktline (aw, NEDJMP_LINE_MID, 0, NEDJMP_FLAG_REDRAW);
    }
    return 0;
  }

  return -1;
}
