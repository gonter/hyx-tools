/*
 *  FILE %ned/11/ned1110.c
 *
 *  Text search and replace functions
 *  see: C API documentation
 *
 *  written:       1996-05-17
 *  latest update: 1998-08-16 12:40:27
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#define __strrev_undefined__
#include <gg/strings.h>
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"
#include <gg/window.h>

/* ------------------------------------------------------------------------ */
int ned_wc_find_replace (
struct WINDOWCTRL *wc,
struct LINE *z_start,
int c_start,
struct LINE *z_end,
int c_end,
int blck_mode,                         /* ???? */
int option,
int find_replace,
char *find_str,
char *repl_str,
int repeat_within_line,
int repeat_counter,
struct MARKER *m_fnd)
{
  struct LINE *z_fnd;                   /* line where search hit target     */
  int c_fnd;                            /* column where search hit target   */
  int ovrins_store;                     /* Puffer fuer OVR INS Modus Flag   */
  int disp_insert;                      /* 1 -> Display bei insert          */
  int aktion;                           /* Ersetzung durchfuehren ja/nein   */
  int m_lng;                            /* length of matched target         */
  int something_found= 0;               /* >1 -> something was found        */
  int scr_ref= 1;                       /* Bildschirm neu aufbauen ??       */
  int i, j;

#ifdef MSDOS
  c_end; blck_mode; repeat_within_line;
#endif /* MSDOS */

  ovrins_store= wc->ins_flg;
  wc->ins_flg= INSFLG_insert;

  /* reverse find string again, when reverse search option is used */
  if (option & OPT_backward) strrev (find_str);

  for (; repeat_counter > 0; repeat_counter--)
  {
    ned_message_2 ("searching ", find_str);
    if (ned_str_match (z_start, c_start, z_end,
                       (unsigned char *) find_str,
                       (unsigned char *) 0,
                       -1, &z_fnd, &c_fnd, &m_lng, option) == 0
       )
    {
      if (m_fnd != (struct MARKER *) 0)
        ned_set_marker2 (wc, z_fnd, c_fnd, m_fnd);

      wc->WC_act= z_fnd;
      wc->cx= c_fnd - wc->hv + wc->ax;
      if (option & OPT_backward) wc->cx -= m_lng-1;
      something_found++;

      switch (find_replace)
      {
        case 1:
          /* if (!(option & OPT_backward)) wc->cx += m_lng; */
          break;

        case 2:
          aktion= 1;
          disp_insert= 0;
          if (option & OPT_ask)
          {
            background ();
            ned_message_1 ("Replace: (Y|N) ");
            ned_w_jmp_aktline (wc, NEDJMP_LINE_MID, 0, NEDJMP_FLAG_REDRAW);
            scr_ref= 0;
            disp_insert= 1;
            setcup (wc);
            switch (test_maus ('Y', 'N', 0))
            {
              case 'j':  case 'J': case 0x09:
              case 'y':  case 'Y': case 0x19:
                aktion= 1;
                break;
              default:
                aktion= 0;
                break;
              case 0x1B:
                case 0x15:
                aktion= -1;
                break;
            }
          }

          switch (aktion)
          {
            case  1: /* Ersetzung Durchfuehren */
              for (i= 0; i < m_lng; i++) ned_wc_delete (wc, disp_insert);
              for (j= strlen (repl_str)-1; j>=0; j--)
                ned_wc_insert (wc, repl_str [j], disp_insert);
              if (!(option & OPT_backward)) wc->cx += strlen (repl_str);
              break;
            case  0: /* NICHT ersetzen */
              if (!(option & OPT_backward)) wc->cx += m_lng;
              break;
            case -1: /* Abbrechen */
              goto AUS;
          }
          break;
      }
    }
    else break;

    z_start= wc->WC_act;
    c_start= wc->cx + wc->hv - wc->ax;
  }

  /* reverse find string again, when searching backwards        */
  /* was used to get back original find string ...              */
  if (option & OPT_backward) strrev (find_str);

AUS:
  wc->ins_flg= ovrins_store;
  if (scr_ref) ned_w_jmp_aktline (wc, NEDJMP_LINE_MID, 0, NEDJMP_FLAG_REDRAW);

  return something_found;
}
