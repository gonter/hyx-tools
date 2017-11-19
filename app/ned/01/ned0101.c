/*
 *  FILE %ned/01/ned0101.c
 *
 *  Window Control Block auf einen brauchbaren Wert setzen
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1997-08-03 16:37:21
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int akt_page;
extern int COL_TEXT;
extern int COL_BOX;
extern int word_wrap_count;
extern int default_edit_mode;
extern int default_tag_display_mode;

/* Window Default Values laden -------------------------------------------- */
void wdw_rst (register struct WINDOWCTRL *w)
{
  w->WC_act        = (struct LINE *) 0;
  w->WC_first      = (struct LINE *) 0;
  w->file_or_frame = (void *) 0;
  w->ins_flg       = INSFLG_insert;
  w->w_upd         = 1;
  w->ai            = 1;
  w->wwc           = word_wrap_count;
  w->f_upd         = 0;
  w->file_type     = FTY_PLAIN;
  w->file_format   = FMT_ASCII;
  w->cx            = w->ax;
  w->cy            = w->ay;
  w->znr           = 0;
  w->tlines        = 0;
  w->hv            = 0;
  w->page          = akt_page;
  w->attr_text     = COL_TEXT;
  w->attr_box      = COL_BOX;
  w->box_type      = BOX_TYPE_double;
  w->wflags        = 0;
  w->WC_edit_mode  = default_edit_mode;
  w->bin_eoln      = 0x0A;
  w->bin_llng      = LINE_LNG_TXT;
  w->wc_ll_flags   = 0;

  w->wc_tag_display_mode= default_tag_display_mode;

#ifdef DEVEL1
  w->wc_new1       = 0;
  w->wc_new2       = 0;
  w->wc_new3       = 0;
  w->wc_new4       = 0;
#endif
}
