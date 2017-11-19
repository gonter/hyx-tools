/*
 *  FILE %ned/08/ned0845.c
 *
 *  Frame aktivieren, d.h. Informationen laden oder Frame neu anlegen
 *
 *  written:       1991 05 29
 *  latest update: 2000-09-01 18:02:26
 *  $Id: ned0845.c,v 1.6 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/hytxt.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;
extern char *default_start_frame;

/* ------------------------------------------------------------------------ */
struct FRAMECTRL *ned_activate_frame (
struct CLUSTERCTRL *cl,         /* Liste der zu durchsuchenden Cluster      */
const char *fr_name,            /* gesuchter Frame                          */
struct WINDOWCTRL *wc,          /* Window, das uebernommen werden soll      */
int search_mode,                /* Bit 0: alle Cluster durchsuchen          */
                                /* Bit 1: Frame ggf. neu anlegen            */
int file_fmt,                   /* FMT_SGML | FMT_ASCII                     */
const char *template_frame,     /* frame to clone, if necessary             */
const char *alternative_frame)  /* alternative frame to open, if not found  */
{
  struct FRAMECTRL *fr;
  int win_num;
  int rc;
  int frame_new= 0;
  char *cln;
  char *title_short;
#ifndef NED_READ_ONLY
  long new_index;
#endif /* !NED_READ_ONLY */
  char *tlt_frame= (char *) 0;

  if (cl == (struct CLUSTERCTRL *) 0) return (struct FRAMECTRL *) 0;

  /* check if frame name is specified... */
  if (fr_name == (char *) 0 || *fr_name == 0) fr_name= default_start_frame;

  if ((tlt_frame= hyx_translate_special_frame (fr_name)) != (char *) 0)
    fr_name= tlt_frame;

  if ((fr= find_frame (cl, fr_name, search_mode)) == (struct FRAMECTRL *) 0)
  { /* the frame name was not found in any of the clusters */
#ifndef NED_READ_ONLY /* 1996-03-11  1:32:34 */

    if (!(search_mode & 0x02))
    { /* frame does not exist and should not be created */
      if (alternative_frame != (char *) 0
          && (fr= find_frame (cl, fr_name= alternative_frame, search_mode))
             != (struct FRAMECTRL *) 0
         )
        goto FOUND;

      goto DONE;
    }

    /* create a new frame */
    if (template_frame != (char *) 0
        && (fr= ned_activate_frame (cl, template_frame, wc, 0x00, file_fmt,
                                    (char *) 0, (char *) 0))
            != (struct FRAMECTRL *) 0)
    {
      frame_new= 2;
      
      goto JMPWDW;
    }
    else
    { /* create frame */
      new_index= (cl->next_index)++;
      if ((fr= create_framectrl (cl, fr_name, new_index, FRAME_is_new))
          == (struct FRAMECTRL *) 0) goto DONE;

      fr->frame_begin= 0L;
      fr->frame_end= 0L;
      fr->frame_status= FRAME_is_defined;
      frame_new= 1;
    }
#else
    template_frame;
    alternative_frame;
    goto DONE;
#endif /* NED_READ_ONLY */
  }
  else
  {
#ifndef NED_READ_ONLY
FOUND:
#endif

    if (fr->frame_status == FRAME_is_loaded)
    { /* Frame in der Window Liste suchen und anspringen */
      if (wc != (struct WINDOWCTRL *) 0) ned_w_close_window (wc);
      goto JMPWDW;
    }
    else
    { /* Frame Info aus Index laden */
      get_index (fr);
      fr->frame_status= FRAME_is_defined;
    }
  }

  if (wc == (struct WINDOWCTRL *) 0)
  { /* Window erzeugen */
    if (q_wdwopen (&wc, &win_num) == -1)
    {
      fr= (struct FRAMECTRL *) 0;
      goto DONE;
    }

    /* ned_window_size (wc, DEFAULT_WDW_MODE, 1); * 1996-03-02 23:06:05 ?? **/
  } /* else: angegebenes Window verwenden */

  /* Window mit Frame verknpfen */
  wc->file_or_frame= fr;
  wc->file_type= FTY_HYPER;
  wc->file_format= file_fmt;

  if ((cln= cl->cluster_name_logic) == (char *) 0
      && (cln= cl->cluster_name_hyx) == (char *) 0
     )
    cln= "unknown...";

  /* store frame name */
  rc= strlen (cln);
  title_short= malloc (rc + strlen (fr_name) + 5);
  title_short [0] = '[';
  strcpy (title_short + 1, cln);
  strcpy (title_short + rc + 1, "] ");
  strcpy (title_short + rc + 3, fr_name);
  wc->WC_title_short= title_short;
#ifdef USE_TK
  ned_tk_set_window_name (wc, wc->WC_title_short);
#endif /* USE_TK */

  switch (frame_new)
  {
    case 0: s_fget (wc);                        break;  /* File einlesen    */
    case 1: initialize_frame (wc, fr_name);
      break;
  }

  take_history_notes (wc);
  fr->frame_status= FRAME_is_loaded;

JMPWDW:
  for (wc= windows; wc != (struct WINDOWCTRL *) 0; wc= wc->WC_next)
    if (wc->file_or_frame == fr)
    {
      if (frame_new == 2) ned_rename_frame (wc, fr_name, file_fmt);

      q2_jmpwdw (wc);
      q0_jmpwdw (wc);
      break;
    }

DONE:
  free_or_what (tlt_frame);

  return fr;
}
