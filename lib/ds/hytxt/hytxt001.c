/*
 *  FILE %ds/hytxt/hytxt001.c
 *
 *  scan a file for frame entries
 *
 *  written:       1990 02 14
 *  latest update: 1996-10-09 21:29:28
 *  $Id: hytxt001.c,v 1.3 2002/01/27 23:01:39 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hytxt_scan (
char *fname,                    /* Hypertext File Name                      */
struct HYTXT_FRAME **fl,        /* gescannte Frame Liste                    */
int scan_mode)                  /* Bit 0: don't include earlier versions    */
                                /* Bit 1: don't include purgable versions   */
                                /* Bit 4: don't scan frame attributes       */
                                /* Bit 8-F: reserved fuer untergeordnete    */
                                /*          Funktionen                      */
{
  FILE *fi;
  int  ret_val= 0;              /* Return Value dieser Funktion             */

  long pos;                     /* aktuelle Position im File                */
  struct HYTXT_FRAME **fpp;
  struct HYTXT_FRAME  *fd;      /* aktueller Frame-Descriptor               */
  struct HYTXT_FRAME  *fp;      /* vorheriger Frame-Descriptor              */

  if ((fi= fopen (fname, "rb")) == (FILE *) 0) return -1;
  fp= (struct HYTXT_FRAME *) 0;
  fpp= fl;

  for (pos= 0L;;)
  {
    if (feof (fi)) break;

    if ((fd= (struct HYTXT_FRAME *)
              calloc (sizeof (struct HYTXT_FRAME), 1))
        == (struct HYTXT_FRAME *) 0)
    {
      ret_val= -1;
      break;
    }

    ret_val= hytxt_scan_entry (fi, &pos, fd, scan_mode, (char *) 0);
    /* hytxt_report_frame (stdout, "SCAN (1)", ret_val, fd); */
    if (ret_val != 0) break;

    *fpp = fd;
     fpp = &(fd->hytxt_frame_next);
    fd->hytxt_frame_prev=fp;
    fp = fd;

    /* aeltere Frames und purgebare Frames suchen:                          */
    /* Problem: purgeable Frames duerfen nicht sofort entfernt werden,      */
    /*          da von diesem Frame aeltere Versionen existieren koennen.   */
    /*          Daher muss zuerst die Liste abgearbeitet werden, dann       */
    /*          wird der purgeable Frame entfernt.                          */
    for (fd  = fd->hytxt_frame_prev;
         fd != (struct HYTXT_FRAME *) 0;
         fd  = fd->hytxt_frame_prev)
    {
      /* fp ... zuletzt gelesener Frame                                     */
      /* fd ... betrachteter Frame aus der bisherigen Frame Liste           */

      /* hytxt_report_frame (stdout, "SCAN (2)", 0, fd); */

      if (strcmp (fd->hytxt_frame_name, fp->hytxt_frame_name) == 0)
      {
        if (scan_mode & HYXSM_hide_earlier)
        {
               /* aeltere Version aus Liste entfernen */
               if (fd->hytxt_frame_prev != (struct HYTXT_FRAME *) 0)
                  fd->hytxt_frame_prev->hytxt_frame_next
                     = fd->hytxt_frame_next;
               if (fd->hytxt_frame_next != (struct HYTXT_FRAME *) 0)
                  fd->hytxt_frame_next->hytxt_frame_prev
                     = fd->hytxt_frame_prev;
               if (*fl == fd) *fl = fd->hytxt_frame_next;
               free_HYTXT_FRAME (fd);
               break;
        }
        else
        {
               fd->hytxt_frame_newer   = fp;
               fp->hytxt_frame_earlier = fd;
        }
        break;
      }
    }

  }

  /* zum Abschluss purgeable Frames rauswerfen (wenn verlangt) */
  if (scan_mode & HYXSM_hide_purged)
  {
    for (fd  = *fl;
         fd != (struct HYTXT_FRAME *) 0;
         fd  = fd->hytxt_frame_next)
    {
      /* fd ... betrachteter Frame aus der bisherigen Frame Liste           */

      if (fd->hytxt_frame_flags & HYTXT_FRFLAG_TOPURGE)
      {
         /* purgeable Version aus Liste entfernen */
         if (fd->hytxt_frame_prev != (struct HYTXT_FRAME *) 0)
            fd->hytxt_frame_prev->hytxt_frame_next
              = fd->hytxt_frame_next;
         if (fd->hytxt_frame_next != (struct HYTXT_FRAME *) 0)
            fd->hytxt_frame_next->hytxt_frame_prev
              = fd->hytxt_frame_prev;
         if (*fl == fd) *fl = fd->hytxt_frame_next;
         free_HYTXT_FRAME (fd);
      }
    }
  }

  fclose (fi);
  return ret_val;
}
