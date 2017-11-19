/*
 *  FILE E:\usr\sgml\hyxeng04.c
 *
 *  1990 04 13: aus File HYX.C isoliert
 *
 */

# pragma check_stack(off)
# include <stdio.h>
# include <gg/hytxt.h>
# include "hyxeng.h"

/* ------------------------------------------------------------------------ */
int   hyx_engine_list (
FILE *fo,
char *fn,                               /* Cluster Name */
struct HYTXT_FRAME **hytxt_frame,       /* Frame Liste  */
int   list_mode,        /* 0: Frame Liste scannen           */
                        /* 1: Frame Liste bereits gescannt  */
int   scan_mode,
int   sort_mode,
int   prnt_mode)        /* Bit 0: Frame Names */
                        /* Bit 1: Attributes  */
{
  int rv;
  struct HYTXT_FRAME *ht;
  struct HYTXT_ATTR  *ha;

  ht = (struct HYTXT_FRAME *) 0;

  switch (list_mode)
  {
    case 0:
      rv = hytxt_scan (fn, &ht, scan_mode);
      if (rv < 0)
      {
        /* fprintf (stderr, "Error scanning file %s\n", fn); ### */
        return -1;
      }
      *hytxt_frame = ht;
      break;
    case 1:
      ht = *hytxt_frame;
      break;
  }

/****************************
printf ("<<< sort_mode=%d scan_mode=%d list=%08lX\n",
sort_mode, scan_mode, ht);
****************************/

  hytxt_sort (&ht, sort_mode);
  *hytxt_frame = ht;

  fprintf (fo, "Cl %s\n", fn);
  for (;
       ht != (struct HYTXT_FRAME *) 0;
       ht  = ht->hytxt_frame_next)
    {
      if (ht->hytxt_frame_newer != (struct HYTXT_FRAME *) 0
          && !(prnt_mode & 0x4000)) continue;
      if ((ht->hytxt_frame_flags & HYTXT_FRFLAG_TOPURGE)
          && !(prnt_mode & 0x4000)) continue;

      if (prnt_mode & 0x0001)
         fprintf (fo, "Fr %s\n", ht->hytxt_frame_name);
      if (prnt_mode & 0x8000)
         fprintf (fo, "Bo 0x%08lX 0x%08lX\n",
              ht->hytxt_frame_pos_beg, ht->hytxt_frame_pos_end);
      if (prnt_mode & 0x0002)
      {
        fprintf (fo, "FF %04X\n", ht->hytxt_frame_flags);
        for (ha  = ht->hytxt_attr;
             ha != (struct HYTXT_ATTR *) 0;
             ha  = ha->hytxt_attr_next)
        {
          fprintf (fo, "At %s := %s\n",
                  ha->hytxt_attr_id, ha->hytxt_attr_pars);
        }
      }
    }
  fprintf (fo, "-- ----------------\n");
  return 0;
}
