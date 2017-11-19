/*
 *  FILE ~/usr/sgml/hyxeng05.c
 *
 *  written:       1990 04 13: aus File HYX.C isoliert
 *  latest update: 1994-07-23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/hytxt.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include "hyxeng.h"

/* ------------------------------------------------------------------------ */
int hyx_engine_export (
FILE *fo,                               /* Fehler Ausgabe ???               */
char *fn,                               /* Cluster Name                     */
struct HYTXT_FRAME **hytxt_frame,       /* Frame Liste                      */
int   list_mode,                        /* 0: Frame Liste scannen           */
                                        /* 1: Frame Liste bereits gescannt  */
char *frame,                            /* Name des auszugebenden Frames    */
void (*export_function) (int ch))       /* Ausgabe Funktion                 */
{
  int rv, ch;
  struct HYTXT_FRAME *ht;
  FILE *fi;             /* Hypertext File Input */
  int fi_opened= 0;
  long cpy_size;
  int copied= 0;

  ht= (struct HYTXT_FRAME *) 0;

  switch (list_mode)
  {
    case 0:
      rv = hytxt_scan (fn, &ht, 0x0003);
      if (rv < 0)
      {
        fprintf (fo, "** Error scanning file %s\n", fn);
        return rv;
      }
      *hytxt_frame = ht;
      break;
    case 1:
      ht = *hytxt_frame;
      break;
  }

  for (;
       ht != (struct HYTXT_FRAME *) 0;
       ht  = ht->hytxt_frame_next)
  {
    if (ht->hytxt_frame_newer != (struct HYTXT_FRAME *) 0
        || (ht->hytxt_frame_flags & HYTXT_FRFLAG_TOPURGE)) continue;
    if (match (frame, ht->hytxt_frame_name) > 0)
    {
      if (!fi_opened) fi = fopen (fn, "rb");
      if (fi == (FILE *) 0) break;
      fi_opened = 1;
      cpy_size = ht->hytxt_frame_pos_end - ht->hytxt_frame_pos_beg + 1L;
      fseek     (fi, ht->hytxt_frame_pos_beg, 0);
      /* ftransfer (fi, out_file_ptr, cpy_size); ***/
      while (cpy_size-- > 0L)
      {
        ch = fgetc (fi) & 0x00FF;
        if (feof (fi)) break;
        (*export_function) (ch);
      }
      copied=1;
    }
  }

  if (fi_opened) fclose (fi);
  if (!copied)
  {
    fprintf (fo, "** Frame `%s' not found in %s\n", frame, fn);
  }

  return 0;
}
