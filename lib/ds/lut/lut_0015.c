/*
 *  FILE %ds/lut/lut_0015.c
 *
 *  processing of LUT-files: convert LUT file to YTREE
 *
 *  written:       2003-06-25
 *  latest update: 2003-06-25 15:41:53
 *  $Id: lut_0015.c,v 1.2 2003/10/01 21:52:01 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int lut_ytree_entry (char *wrd, long info, void *client_data)
{
  struct YTREE **ytp= (struct YTREE **) client_data;

  ytree_set_value (ytp, wrd, info);
  return 0;
}

/* ------------------------------------------------------------------------ */
struct YTREE *lut_scan_ytree (char *fn, long start)
{
  struct YTREE *yt= (struct YTREE *) 0;
  int rc;

  rc= lut_process (fn, lut_ytree_entry, (void *) &yt, start);
  return yt;
}

/* ------------------------------------------------------------------------ */
struct YTREE *lut_scan_ytree_file (FILE *lut, long start)
{
  struct YTREE *yt= (struct YTREE *) 0;
  int rc;

  fseek (lut, start, 0);
  rc= lut_process_block (lut, lut_ytree_entry, (void *) &yt);
  return yt;
}
