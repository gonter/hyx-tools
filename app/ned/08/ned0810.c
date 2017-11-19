/*
 *  FILE %ned/08/ned0810.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  *** NOT USED ***
 *
 *  written:       1987 09 08
 *                 1991 02 03: Revision
 *  latest update: 1997-10-26 10:24:35
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* Modul NED11: (Find & Replace) ------------------------------------------ */
extern char find_str [],
            repl_str [],
            opt_str  [];        /* Optionen und Ersatz-String               */

extern char stp_fnm [];

extern int find_replace,        /* 0 .. undefiniert                         */
                                /* 1 .. Find                                */
                                /* 2 .. Replace (Makro Execution)           */
           option;              /* bit 0: global                            */
                                /*     1: ingore case                       */
                                /*     2: Ask before replace                */
           cnt;

extern int akt_page;

static char *signature [] =
{
  "NED 2.3 Restart"
} ;

/* ------------------------------------------------------------------------ */
void q_save_restart (void)
{
  FILE *fo;
  struct FILECTRL *f;
  struct WINDOWCTRL *w;
  int i, fc= 0, wc= 0;

  for (f= files;   f != (struct FILECTRL *) 0; f= f->FC_next) f->FC_num= ++fc;
  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->WC_next)
  {
    wc++;
    if (w == aw) i= wc;
  }

  if ((fo= fopen ("NED.RST", "wt")) == (FILE *) 0) return;

  fprintf (fo, "%s\n%d %d %d %d %d\n",
           signature[0], fc, wc, i, N_MARKER, w_get_mode ());

  for (f= files; f != (struct FILECTRL *) 0; f= f->FC_next)
    fprintf (fo, "%s\n%s\n", f->FC_fnm_txt, f->FC_fnm_ftr);

  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->WC_next)
  {
    if (w->file_type == FTY_HYPER) continue;

    fprintf (fo, "%2d %4d %4d %2d %2d %2d %2d %2d %2d %d %2d %d %d ",
             ((struct FILECTRL *) w->file_or_frame)->FC_num,
             ned_cnt_line_2beg (w->first),
             w->znr,
             w->ax, w->ay,
             w->bx, w->by,
             w->cx, w->cy,
             w->page, w->attr_text, w->box_type, w->hv);

    fprintf (fo, "%d %d %d %d %d %d %d %d\n",
             w->wflags, w->ins_flg, w->ai, w->wwc, w->f_upd,
             w->WC_edit_mode, w->bin_eoln, w->bin_llng);
  }

  q_save_marker (fo, &b_beg);
  q_save_marker (fo, &b_end);
  for (i= 0; i<10; i++)
    q_save_marker (fo, &marker [i]);

  fprintf (fo, "%d %d %d %d\n",
           blk, block_mode, oper_level, akt_page);

  fprintf (fo, "%s\n", stp_fnm);

  fprintf (fo, "%s\n%s\n%s\n%d %d %d\n",
           find_str, repl_str, opt_str, find_replace, option, cnt);

  fclose (fo);
}
