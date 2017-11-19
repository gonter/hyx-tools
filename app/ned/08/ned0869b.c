/*
 *  $Id: ned0869b.c,v 1.4 2005/09/04 18:36:07 gonter Exp $
 *  FILE %ned/08/ned0869.c
 *
 *  written:       1991 09 25
 *  latest update: 2000-06-05 18:58:07
 *  $Id: ned0869b.c,v 1.4 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
struct FRAMECTRL *ned_activate_cl_fr (
const char *cl_name,
const char *fr_name,
int search_mode,
int format,
const char *template_frame,
const char *alternative_frame)
{
  struct CLUSTERCTRL *cl;
  struct FRAMECTRL *fr;

/*******
printf ("ned0869b: activate_cl_fr fr_name='%s' tf='%s' 0x%08lX\n",
 fr_name, template_frame, template_frame);
*******/

  if (cl_name == (char *) 0 || *cl_name == 0)
  {
    struct WINDOWCTRL *w;

    cl_name= "this cluster";

    w= (aw->file_type == FTY_FTRWDW) ? aw->feature_window : aw;
    if (w->file_type != FTY_HYPER
        || (cl= ((struct FRAMECTRL *) w->file_or_frame)->cluster)
            == (struct CLUSTERCTRL *) 0
       )
    {
      cl_name= "%cl0";
      goto CL0;
    }
  }
  else
  {
CL0:
    if ((cl= ned_activate_cluster (cl_name)) == (struct CLUSTERCTRL *) 0)
      goto ERR;
  }

  if ((fr= ned_activate_frame (cl, fr_name, (struct WINDOWCTRL *) 0,
                               search_mode, format,
                               template_frame, alternative_frame))
      == (struct FRAMECTRL *) 0)
  {
ERR:
    ned_message_4 ("couldn't activate frame ", fr_name, " in ", cl_name);
    return (struct FRAMECTRL *) 0;
  }

  return fr;
}
