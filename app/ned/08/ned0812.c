/*
 *  FILE %ned/08/ned0812.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  *** NOT USED ***
 *
 *  written:       1987 09 08
 *                 1991 02 03: Revision
 *  latest update: 1999-04-25 16:32:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* ------------------------------------------------------------------------ */
static char *signature [] =
{
  "NED 2.3 Restart"
} ;

/* ------------------------------------------------------------------------ */
void q_load_restart ()
{
#ifdef __THIS_SHOULD_GET_FIXED__
  FILE *fi;
  struct FILECTRL    *f;
  struct WINDOWCTRL  *w, *w2;
  int i, fc, wc, awn;
  int mc;                       /* Marker Counter */
  int xcx, xznr, xhv, xattr;    /* Sicherungsvariablen;                     */
  int xins_flg, xai, xwwc;      /* wird vom Feature File Åberschrieben      */
  char line [40];

return;         /* ###################### FIX IT ########################## */
  if ((fi= fopen ("NED.RST", "rt")) == (FILE *) 0) goto AUS;

  fscanf (fi, "%[^\n]", line);
  fgetc (fi);
  if (feof (fi) || strcmp (line, signature [0]) != 0) goto AUS;
  fscanf (fi, "%d%d%d%d%d", &fc, &wc, &awn, &mc, &i);
  w_init_mode (i, 0x0001);

  for (i= 0; i< fc; i++)
  {
    if ((f= file_alloc ()) == (struct FILECTRL *)) goto AUS;
    f->FC_next= files;
    files= f;
  }

  for (i= 0; i< wc; i++)
  {
    if ((w= ned_create_window_pair ()) == (struct WINDOWCTRL *) 0)
      goto AUS;

    w->next= windows;
    windows= w;
  }

  for (w= windows, i=1; w != (struct WINDOWCTRL *) 0; w = w->next, i++)
    if (i <= awn)
    {
      aw= w;
      break;
    }

  for (f= files; f != (struct FILECTRL *); f= f->next)
  {
    if (feof (fi)) goto AUS;           fgetc (fi);
    fscanf (fi, "%[^\n]", f->fnm_txt); fgetc (fi); /* ### alloc ### */
    fscanf (fi, "%[^\n]", f->fnm_ftr);             /* ### alloc ### */
  }

  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->next)
  {
    if (feof (fi)) goto AUS;
    fscanf (fi, "%d%d%d%d%d%d%d%d%d%d%d%d%d",
                &fc, &wc, &xznr,
                &w->ax, &w->ay, &w->bx, &w->by, &xcx, &w->cy,
                &w->page, &xattr, &w->box_type, &xhv);
    fscanf (fi, "%d%d%d%d%d%d%d%d",
                &w->wflags, &xins_flg, &xai, &xwwc, &w->f_upd,
                &w->WC_edit_mode, &w->bin_eoln, &w->bin_llng);

    for (f= files; f != (struct FILECTRL *); f= f->next, fc--)
      if (fc == 1)
      {
        w->file_or_frame= f;
        f->links++;
        break;
      }

    if (((struct FILECTRL *) w->file_or_frame)->links > 1)
    {
               for (w2=windows; w2 != (struct WINDOWCTRL *) 0; w2=w2->next)
                   if ((struct FILECTRL *) w2->file_or_frame ==
                       (struct FILECTRL *) w->file_or_frame)
                      {
                        w->first = w2->first;
                        break;
                      }
    }
    else
    {
      ned_f_read (w, ((struct FILECTRL *) w->file_or_frame)->fnm_txt,
                 ((struct FILECTRL *) w->file_or_frame)->fnm_ftr,
                 1, &w->first, &w->WC_act, 0L, 0x7FFFFFFFL);
    }

        w->WC_act=    ned_get_line_by_nr (w->first, &xznr);
        w->first=     ned_get_line_by_nr (w->first, &wc);
        w->cx=        xcx;
        w->znr=       xznr;
        w->hv=        xhv;
        w->attr_text= xattr;
        w->ins_flg=   xins_flg;
        w->ai=        xai;
        w->wwc=       xwwc;
        w->w_upd |=   0x04;
  }

  if (feof (fi)) goto AUS;
  q_load_marker (fi, &b_beg);
  q_load_marker (fi, &b_end);
  ned_set_block_flags ();
  for (i=0; i<10; i++)
      q_load_marker (fi, &marker [i]);

  if (feof (fi)) goto AUS;
  fscanf (fi, "%d%d%d%d",
          &blk, &block_mode, &oper_level, &akt_page);

  if (feof (fi)) goto AUS;
  fscanf (fi, "%s",     stp_fnm);       fgetc (fi);
  fscanf (fi, "%[^\n]", find_str);      fgetc (fi);
  fscanf (fi, "%[^\n]", repl_str);      fgetc (fi);
  fscanf (fi, "%[^\n]", opt_str);       fgetc (fi);
  fscanf (fi, "%d%d%d", &find_replace, &option, &cnt);

AUS:
  fclose (fi);
#endif
}

/* ------------------------------------------------------------------------ */
void q_load_marker (FILE *fi, struct MARKER *m)
{
fi; m;
#ifdef __THIS_SHOULD_GET_FIXED__
  int i1, i2;
  struct FILECTRL    *f;
  struct WINDOWCTRL  *w;

  fscanf (fi, "%d%d%d", &i1, &i2, &m->offset);
  m->ptr= (struct LINE *) 0;

  if (i1 != 0)
    for (f= files; f != (struct FILECTRL *); f= f->next)
      if (i1==1)
      {
        m->wptr = (struct WINDOWCTRL *) 0; /* m->fptr= f; WINDOWCTRL!!! */
        for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->next)
          if (f == (struct FILECTRL *) w->file_or_frame)
          {
            m->ptr= ned_get_line_by_nr (w->first, &i2);
            break;
          }
        break;
      }
#endif
}
