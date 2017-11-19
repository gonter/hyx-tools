/*
 *  FILE %ned/08/ned0880.c
 *
 *  written:       1991 10 24
 *  latest update: 1998-08-16 12:47:35
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "edctx.h"
#include "proto.h"

extern struct NED_CONTEXT *ned_main_context;

extern struct WINDOWCTRL *aw;
extern int default_cross_ref_fmt;
extern int default_cross_ref_local;
extern char *default_cross_ref_template;

#define CMP_SIZE 36
static char cmp_buffer [CMP_SIZE+1];
static int cmp_cnt= -1;

/* ------------------------------------------------------------------------ */
void ned_activate_cross_ref (
char *str,
int flg_resize,                 /* 1 -> resize windows                      */
int cluster_type,               /* which clusters to search through         */
int local_or_global)            /* include current cluster in search        */
{
  struct FRAMECTRL *fr= (struct FRAMECTRL *) 0;
  struct CLUSTERCTRL *cl;
  struct WINDOWCTRL *xaw;
  struct ARRAY_ELEMENT *e_crf;
  struct ARRAY_CONTROL *a_crf;
  void *ptr;
  int flags= 0x00;
  int where;
  char *crf;

  xaw= aw;

  ned_message_3 ("crf \'", str, "\'");

  if ((local_or_global & CRF_LOCAL)
      && aw->file_type == FTY_HYPER
      && (ptr= aw->file_or_frame) != (void *) 0
      && (cl= ((struct FRAMECTRL *) ptr)->cluster) != (struct CLUSTERCTRL *) 0
     )
  {
    if ((fr= ned_activate_frame (cl, str, (struct WINDOWCTRL *) 0,
                                 (default_cross_ref_local) ? 0x02 : 0x00,
                                 default_cross_ref_fmt,
                                 default_cross_ref_template, (char *) 0))
           != (struct FRAMECTRL *) 0)
      goto RESIZE;
  }

  if (cmp_cnt >= 0 && strcmp (cmp_buffer, str) == 0)
  {
    cmp_cnt++;
  }
  else
  {
    strcpy_max (cmp_buffer, str, CMP_SIZE);
    cmp_cnt= 0;
  }

  if (cmp_cnt == 3) flags |= 0x02;

  for (where= 1; where < 0x4000; where= where << 1)
  {
    if (!(where & cluster_type)) continue;
    a_crf= (struct ARRAY_CONTROL *) 0;

    if (where & CRF_IN_CRF)     a_crf= ned_main_context->NED_CTX_crf; else
    if (where & CRF_IN_LIB)     a_crf= ned_main_context->NED_CTX_lib; else
    if (where & CRF_IN_LEX)     a_crf= ned_main_context->NED_CTX_lex; else
    if (where & CRF_IN_THES)    a_crf= ned_main_context->NED_CTX_thes;

    for (e_crf= array_top (a_crf);
         e_crf != (struct ARRAY_ELEMENT *) 0;
         e_crf= e_crf->next)
    { /* activate the appropriate frame in the first possible crf cluster */
      if ((crf= (char *) e_crf->payload) != (char *) 0
          && (cl= ned_activate_cluster (crf)) != (struct CLUSTERCTRL *) 0
          && (fr= ned_activate_frame (cl, str, (struct WINDOWCTRL *) 0,
                                      flags,
                                      default_cross_ref_fmt,
                                      default_cross_ref_template, (char *) 0))
             != (struct FRAMECTRL *) 0
         ) goto RESIZE;
    }
  }

RESIZE:
  if (fr != (struct FRAMECTRL *) 0 && flg_resize) q_wdwsize ('s');

  q2_jmpwdw (xaw);
  q0_jmpwdw (xaw);
}
