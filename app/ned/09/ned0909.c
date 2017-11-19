/*
 *  FILE %ned/09/ned0909.c
 *
 *  *** NOT USED ***
 *
 *  Operationen mit dem SETUP-File
 *  o  Installation von Tastenkommandos
 *  o  Installation von Makros
 *  o  Installation von Maus Menu Eintraegen
 *  Makroprozessor
 *  Jour File Prozessor
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *  latest update: 1997-10-26 11:12:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include "ed.h"
#include "message.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void stp_window (FILE *fi)
{
  int i;
  int win_num, scmd_num, value;
  register struct WINDOWCTRL *wc;

  for (;;)
  {
    fscanf (fi, "%s", cmd);
    if (feof (fi)) return;
    if (cmd [0] == '#') continue;
    if (ned_what_stp_cmd (cmd) >= 0) return;
    break;
  }

  win_num= (int) get_parameter_value (cmd);
  if (win_num <= 0) win_num= 1;
  if ((wc= windows) == (struct WINDOWCTRL *) 0) return;
  for (i= 1; i < win_num; i++)
      if ((wc= wc->WC_next) == (struct WINDOWCTRL *) 0) return;

  for (;;)
  {
    fscanf (fi, "%s", cmd);
    if (feof (fi)) break;
    if (cmd [0] == '#')
    {
      trash_until_eol (fi);
      continue;
    }

    scmd_num= ned_what_stp_cmd (cmd);
    if (scmd_num < STP_ax || scmd_num > STP_page)
       return;

    for (;;)
    {
      fscanf (fi, "%s", cmd);
      if (feof (fi)) return;
      if (cmd [0] == '#') continue;
      if (ned_what_stp_cmd (cmd) >= 0) return;
      break;
    }

    value= (int) get_parameter_value (cmd);
    switch (scmd_num)
    {
      case STP_ax:
        if (value < 0) break;
        wc->w_upd |= 0x80;
        wc->cx= wc->ax = value;
        break;
      case STP_ay:
        if (value < 1) break;
        wc->w_upd |= 0x80;
        wc->cy= wc->ay= value;
        break;
      case STP_bx:
        if (value > 79 || value < wc->ax + 5) break;
        wc->w_upd |= 0x80;
        wc->bx= value;
        break;
      case STP_by  :
        if (value > 24 || value < wc->ay + 5) break;
        wc->w_upd |= 0x80;
        wc->by= value;
        break;
      case STP_attr:
        wc->attr_text= value & 0xFF;
        break;
      case STP_btyp:
        wc->box_type= (value > 2) ? 2 : value;
        break;
      case STP_page:
        wc->page= (value > 7 || value < 0) ? 0 : value;
        break;
    }
  }
}
