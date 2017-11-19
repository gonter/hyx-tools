/*
 *  FILE ~/usr/sgml/hytxt003.c
 *
 *  writtne:       1990 02 14
 *  latest update: 1995-07-09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <memory.h>
#include <gg/hytxt.h>
#include <gg/sbr.h>

static char *frame_seperator= (char *) 0;
static int frame_seperator_size= 0;

/* ------------------------------------------------------------------------ */
int hytxt_purge (
char *hypertext_file,
char *purge_file,
char *temp_file)
/* Return:  < 0 ... Error                                       */
/*            0 ... OK                                          */
/*            1 ... File already purged; purge not necessary    */
{
  FILE *fh;                     /* Hypertext Main File          */
  FILE *fp;                     /* Purge File                   */
  FILE *ft;                     /* Temporaeres Hypertext File   */
                                /* == neues Main File           */
  int rv;
  int ch;
  int purge_new= 0;
  int status= 0;
  int frame_counter= 0;         /* number of frames in the new cluster */
  struct HYTXT_FRAME *frames;   /* Frame Liste  */
  struct HYTXT_FRAME *f2;
  long cpy_size;                /* Hypertext Header *VOR* dem ersten Frame  */

  rv= hytxt_scan (hypertext_file, &frames, 0x0000);
                        /* Frame List: a) Alle Frames, auch upgedatete      */
                        /*             b) Frame Attribute einlesen          */

  if (rv == -1) return -1;

  for (f2  = frames;
       ;
       f2  = f2->hytxt_frame_next)
   {
     if (f2 == (struct HYTXT_FRAME *) 0) return 1;
     if (f2->hytxt_frame_newer != (struct HYTXT_FRAME *) 0
         || (f2->hytxt_frame_flags & HYTXT_FRFLAG_TOPURGE)) break;
   }

  if ((fh= fopen (hypertext_file, "rb")) == (FILE *) 0) return -1;
  if ((ft= fopen (temp_file, "wb")) == (FILE *) 0)
  {
    fclose (fh);
    return -1;
  }

  cpy_size= frames->hytxt_frame_pos_beg;

  if (access (purge_file, 0) != 0)
  { /* Purge File neu anlegen */
    if ((fp= fopen (purge_file, "wb")) == (FILE *) 0)
    {
      fclose (fh);
      fclose (ft);
      return -1;
    }
    for (; cpy_size > 0L; cpy_size--)
    {
      ch= fgetc (fh) & 0x00FF;
      if (feof (fh)) goto STOP;
      fputc (ch, ft);
      fputc (ch, fp);
    }
  }
  else
  {
    if ((fp= fopen (purge_file, "ab")) == (FILE *) 0)
    {
      fclose (fh);
      fclose (ft);
      return -1;
    }

    for (; cpy_size > 0L; cpy_size--)
    {
      ch= fgetc (fh) & 0x00FF;
      if (feof (fh)) goto STOP;
      fputc (ch, ft);
    }
  }

  for (;
       frames != (struct HYTXT_FRAME *) 0;
       frames  = frames->hytxt_frame_next)
  {
    cpy_size = frames->hytxt_frame_pos_end -
               frames->hytxt_frame_pos_beg + 1L;
    if (frames->hytxt_frame_newer != (struct HYTXT_FRAME *) 0
        || (frames->hytxt_frame_flags & HYTXT_FRFLAG_TOPURGE))
         ftransfer (fh, fp, cpy_size);  /* purge */
    else
    {
      if (frame_seperator_size > 0 && frame_counter++ > 0)
        fwrite (frame_seperator, frame_seperator_size, 1, ft);
      ftransfer (fh, ft, cpy_size);  /* keep  */
    }

#ifdef JUNK
         { /* Frame in neuen Main Cluster uebernehmen */
           for (; cpy_size > 0L; cpy_size--)
           {
             ch = fgetc (fh) & 0x00FF;
             if (feof (fh)) goto STOP;
             fputc (ch, ft);
           }
         }
    else { /* Frame purgen */
           for (; cpy_size > 0L; cpy_size--)
           {
             ch = fgetc (fh) & 0x00FF;
             if (feof (fh)) goto STOP;
             fputc (ch, fp);
           }
         }
#endif

    /* Zwischenraum zwischen Frames, bzw. nach dem letzten Frame */
    if (frames->hytxt_frame_next == (struct HYTXT_FRAME *) 0)
         cpy_size= 0x0FFFFFFF;
    else cpy_size= frames->hytxt_frame_next->hytxt_frame_pos_beg -
                    frames->hytxt_frame_pos_end - 1L;
    ftransfer (fh, fp, cpy_size);
#ifdef JUNK
    for (; cpy_size > 0L; cpy_size--)
    {
      ch= fgetc (fh) & 0x00FF;
      if (feof (fh)) goto STOP;
      fputc (ch, fp);
    }
#endif
  }

STOP:
  fclose (fp);
  fclose (ft);
  fclose (fh);

  return 0;
}

/* ------------------------------------------------------------------------ */
int hytxt_purge_seperator (char *seperator, int seperator_size)
{
  if (frame_seperator != (char *) 0)
  {
    if (seperator_size && frame_seperator_size >= seperator_size) goto DOIT;
    else
    {
      free (frame_seperator);
      frame_seperator_size = 0;
      frame_seperator = (char *) 0;
    }
  }
  if (seperator_size == 0) return 0;

  if ((frame_seperator= malloc (seperator_size)) == (char *) 0) return -1;

DOIT:
  memcpy (frame_seperator, seperator, frame_seperator_size= seperator_size);

  return 0;
}
