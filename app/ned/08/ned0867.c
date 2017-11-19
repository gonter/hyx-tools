/*
 *  FILE %ned/08/ned0867.c
 *
 *  written:       1991 07 18
 *  latest update: 1998-08-16 12:39:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#include <gg/strings.h>
#endif

#include <string.h>
#include <gg/hyx.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

#define LIN_SIZ 80
#define MARK_SIZ 80
static char xxx_mark [MARK_SIZ];

char *mem_file= (char *) 0;
char *mem_frame= (char *) 0;
char *mem_cluster= (char *) 0;
char *mem_mark= (char *) 0;
int mem_line= 0;
int mem_column= 0;

/* ------------------------------------------------------------------------ */
void ned_forget_location ()
{
  free_or_what (mem_file);
  free_or_what (mem_frame);
  free_or_what (mem_cluster);
  /**** free_or_what (mem_mark); ATTN: this pointer is not malloc'ed!!! */

  mem_file= mem_frame= mem_cluster= mem_mark= (char *) 0;
  mem_line= mem_column= 0;
}

/* ------------------------------------------------------------------------ */
void ned_wc_memorize_location (struct WINDOWCTRL *wc)
{
  char *ff= "??";
  void *ptr;
  struct LINE *lp;
  struct FEATURE *fp;
  char lin [LIN_SIZ];
  struct FRAMECTRL *fc;
  struct CLUSTERCTRL *cc;

  ned_forget_location ();

  if (wc == (struct WINDOWCTRL *) 0
      || wc->file_or_frame == (void *) 0
      || wc->WC_act == (struct LINE *) 0
     ) return;

  mem_line= wc->znr;
  mem_column= wc->cx - wc->ax + wc->hv;

  switch (wc->file_type)
  {
    case FTY_PLAIN:
      if ((mem_file= wc->WC_title_short) == (char *) 0)
        mem_file= ((struct FILECTRL *) wc->file_or_frame)->FC_fnm_txt;

      if (mem_file != (char *) 0
          && (mem_file= strdup (mem_file)) != (char *) 0
         )
      {
        ff= "file";
#ifdef MSDOS
        to_lower (mem_file);
#endif
      }
      break;

    case FTY_HYPER:
      mem_frame= strdup ((fc= wc->file_or_frame)->frame_name);
      if (fc != (struct FRAMECTRL *) 0
          && (cc= fc->cluster) != (struct CLUSTERCTRL *) 0)
        mem_cluster= strdup (cc->cluster_name_hyx);

      ff= "frame";
      break;

    default: return;
  }

  for (fp= wc->WC_act->ftr; fp != (struct FEATURE *) 0; fp= fp->ftr_next)
    if (fp->ftr_pos == mem_column
        && (lp= fp->ftr_text_line) != (struct LINE *) 0
        && (ptr= lp->txt) != (struct LINE *) 0
        && ((strncmp (&((struct TXT *) ptr)->t[1], "mark ", 5) == 0
             && ned_line_2_string (lp, 1, lp, lp->lng-1, lin, LIN_SIZ,
                               0L, 0x0) != (char *) 0
             && find_attr_value (lin, xxx_mark, MARK_SIZ, "id") == 0
            )
            ||(strncmp (&((struct TXT *) ptr)->t[1], "hyx.l ", 6) == 0
               && ned_line_2_string (lp, 1, lp, lp->lng-1, lin, LIN_SIZ,
                                 0L, 0x0) != (char *) 0
               && find_attr_value (lin, xxx_mark, MARK_SIZ, "name") == 0
              )
           )
       )
    { /* <mark> gefunden */
      mem_mark= xxx_mark;
    }

  ned_message_2 (ff, " memorized");
}
