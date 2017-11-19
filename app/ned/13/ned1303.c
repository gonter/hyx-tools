/*
 *  FILE %ned/13/ned1303.c
 *
 *  written:       2000-12-09
 *  latest update: 2001-02-11 14:06:21
 *  $Id: ned1303.c,v 1.3 2003/10/01 21:51:06 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern struct WINDOWCTRL *windows;
extern struct FILECTRL   *files;

/* ------------------------------------------------------------------------ */
int ned_debug_info (char *p1)
{
  printf ("\n--- BEGIN -----------------------\nned_debug_info: %s\n", p1);

  if (strcmp (p1, "W") == 0)
  {
    ned_debug_windowctrl (stdout, aw);
  }
  else if (strcmp (p1, "W*") == 0)
  {
    struct WINDOWCTRL *wc;
    for (wc= windows; wc != (struct WINDOWCTRL *) 0; wc= wc->WC_next)
      ned_debug_windowctrl (stdout, wc);
  }
  else if (strcmp (p1, "F*") == 0)
  {
    struct FILECTRL *fc;
    for (fc= files; fc != (struct FILECTRL *) 0; fc= fc->FC_next)
      ned_debug_filectrl (stdout, fc);
  }
  else if (strcmp (p1, "C*") == 0)
  {
    struct CLUSTERCTRL *cc;
    for (cc= ned_get_cluster_list ();
         cc != (struct CLUSTERCTRL *) 0;
         cc= cc->FC_next)
      ned_debug_clusterctrl (stdout, cc);
  }
  else if (strcmp (p1, "T") == 0)
  {
    print_virtual_filename_table (stdout);
  }
  else if (strcmp (p1, "TF") == 0)
  {
    flush_virtual_filename_table (stdout);
    ned_init_virtual_filename_table ();
  }
  else return -1;
  printf ("--- END -------------------------\n");

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_debug_windowctrl (FILE *fp, struct WINDOWCTRL *wc)
{
  fprintf (fp, "WINDOWCTRL=0x%08lX\n", wc);
  fprintf (fp, "title_short='%s'\n", wc->WC_title_short);
  fprintf (fp, "title_long='%s'\n", wc->WC_title_long);
  fprintf (fp, "file_or_frame=0x%08lX file_type=%d file_format=%d\n",
           wc->file_or_frame, wc->file_type, wc->file_format);
  fprintf (fp, "ax=%d ay=%d bx=%d by=%d cx=%d cy=%d\n",
           wc->ax, wc->ay, wc->bx, wc->by, wc->cx, wc->cy);

  if (wc->file_type == FTY_PLAIN)
    ned_debug_filectrl (fp, (struct FILECTRL *) wc->file_or_frame);
  else if (wc->file_type == FTY_HYPER)
    ned_debug_framectrl (fp, (struct FRAMECTRL *) wc->file_or_frame, 0);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_debug_filectrl (FILE *fp, struct FILECTRL *fc)
{
  fprintf (fp, "FILECTRL=0x%08lX\n", fc);
  fprintf (fp, "fnm_txt='%s'\n", fc->FC_fnm_txt);
  fprintf (fp, "fnm_ftr='%s'\n", fc->FC_fnm_ftr);
  fprintf (fp, "fnm_bak='%s'\n", fc->FC_fnm_bak);
  fprintf (fp, "links=%d upd=%d num=%d flags=0x%04X\n",
           fc->FC_links, fc->FC_upd, fc->FC_num, fc->FC_flags);
  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_debug_framectrl (FILE *fp, struct FRAMECTRL *fc, int show_cluster)
{
  fprintf (fp, "FRAMECTRL=0x%08lX\n", fc);
  fprintf (fp, "name='%s'\n", fc->frame_name);
  fprintf (fp, "cluster=0x%08lX\n", fc->cluster);
  fprintf (fp, "idx=0x%08lX begin=0x%08lX end=0x%08lX\n",
           fc->frame_index, fc->frame_begin, fc->frame_end);
  fprintf (fp, "lookup=%d status=%d upd=%d links=%d\n",
           fc->frame_lookup, fc->frame_status, fc->upd, fc->links);
  if (show_cluster) ned_debug_clusterctrl (fp, fc->cluster, 0);
  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_debug_clusterctrl (FILE *fp, struct CLUSTERCTRL *cc, int show_frames)
{
  fprintf (fp, "CLUSTERCTRL=0x%08lX\n", cc);
  fprintf (fp, "name_logic='%s'\n", cc->cluster_name_logic);
  fprintf (fp, "name_hyx='%s'\n", cc->cluster_name_hyx);
  fprintf (fp, "name_idx='%s'\n", cc->cluster_name_idx);
  fprintf (fp, "name_lut='%s'\n", cc->cluster_name_lut);
  fprintf (fp, "name_xfn='%s'\n", cc->cluster_name_xfn);
  fprintf (fp, "read_only=%d locked=%d frames_complete=%d flags0x%04X\n",
           cc->cluster_readonly, cc->cluster_locked,
           cc->frames_complete, cc->CC_flags);
  fprintf (fp, "next_index=0x%08lX highest_index=%08lX\n",
           cc->next_index, cc->highest_index);

  if (show_frames)
  {
    struct FRAMECTRL *fc;
    for (fc= cc->frames; fc != (struct FRAMECTRL *) 0; fc= fc->next)
      ned_debug_framectrl (fp, fc, 0);
  }

  return 0;
}
