/*
 *  FILE %ned/03/ned0333.c
 *
 *  written:       1995-10-22
 *  latest update: 1997-01-19 15:26:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_save_reload (struct WINDOWCTRL *wc, int change_tag_display_mode)
{
  if (wc == (struct WINDOWCTRL *) 0) return;

  if (wc->file_or_frame != (void *) 0 && wc->f_upd) ned_w_save (wc, 1);

  switch (change_tag_display_mode)
  {
    case WCTDM_no_change:
      break;
    case WCTDM_show_tag:
    case WCTDM_show_full_tag:
      wc->wc_tag_display_mode= change_tag_display_mode;
      break;

    case WCTDM_SGML:
      wc->file_format= FMT_SGML;
      wc->wc_tag_display_mode= WCTDM_normal;
      break;
    case WCTDM_ASCII:
      wc->file_format= FMT_ASCII;
      wc->wc_tag_display_mode= WCTDM_normal;
      break;

    case WCTDM_normal:
    default:
      wc->wc_tag_display_mode= WCTDM_normal;
      break;
  }

  ned_reset_markers (wc);
  s_fget (wc);
  ned_display_window (wc);
}
