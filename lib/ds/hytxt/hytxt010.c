/*
 *  FILE %ds/hytxt/hytxt010.c
 *
 *  written:       1991 07 20
 *                 1994-06-03: old version sequencer removed
 *                 1994-06-19: sequencer uses list of FILE_SEGMENTs
 *  latest update: 1996-03-24 17:40:22
 *  $Id: hytxt010.c,v 1.3 2002/01/27 23:01:39 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/hytxt.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/filename.h>
#include <contrib/md5gg.h>

static char tmp []= "@@TMP@@.SEQ";

/* ------------------------------------------------------------------------ */
int hyx_sequencer (
FILE *fo,
char *fnm_hyx,
char *fnm_idx,
char *fnm_lut,
char *fnm_xfn,
struct FILE_SEGMENT *fseg,
int verbose_mode,
int extract_flags)
{
  int rv;
  int rc;
  int ch;
  FILE *fo_tmp;                 /* temporary output file                    */
  FILE *fi;                     /* file containing frame list               */
  FILE *fi_hyx= (FILE *) 0;     /* cluster file                             */
  FILE *fi_idx= (FILE *) 0;     /* index file                               */
  FILE *fi_lut= (FILE *) 0;     /* lookup table file                        */
  FILE *fi_xfn= (FILE *) 0;     /* extra lookup table file                  */
#define FRAME_strlng 260
  char frame [FRAME_strlng];    /* buffer for a frame name from list        */
  char *frame_ptr;
  char *fseg_name;
  int fseg_op;
  long last_index;
  long cnt;

  rv= -1;
  if ((last_index= hyx_get_last_index (fnm_idx)) <= 0L
     ||(fi_hyx= flopen (fnm_hyx, "rb")) == (FILE *) 0) goto END1;
  if ((fi_idx= flopen (fnm_idx, "rb")) == (FILE *) 0) goto END2;
  fi_lut= flopen (fnm_lut, "rb");
  fi_xfn= flopen (fnm_xfn, "rb");
  if (fi_lut == (FILE *) 0 && fi_xfn == (FILE *) 0) goto END5;
  rv= 0;

  for (; fseg != (struct FILE_SEGMENT *) 0; fseg= fseg->FS_next)
  {
    fseg_name= fseg->FS_frame_name;
    fseg_op= fseg->FS_operation;
    if (verbose_mode > 0)  printf ("%c: %s\n", fseg_op, fseg_name);
      /* print operation code and name of first extracted frame             */

    switch (fseg_op)
    {
      case 'l': case 'L':       /* list of frames in a file                 */
        if (verbose_mode > 0)
          printf ("transfering frames from logic file '%s'\n", fseg_name);
        if ((fi= (strcmp (fseg_name, "-") == 0)
                 ? ((FILE *) stdin)
                 : fopen (translate_logic_filename (fseg_name), "rt"))
            == (FILE *) 0) return -1;
PROC_LIST:
        for (;;)
        {
NEXT:
          rc= fread_line (fi, frame, FRAME_strlng);
          if ((rc <= 0 && feof (fi)) || strcmp (frame, ".") == 0) break;
          frame_ptr= frame;
NEXT_TRY:
          switch (*frame_ptr)
          {
            case '<': /* ############ */
              do
              {
                ch= *frame_ptr++ & 0x00FF;
                if (ch == 0) goto NEXT;
              } while (ch != '>');
              goto NEXT_TRY;

            case 0:
            case '#':
            case 0x0D:
            case 0x0A:
              goto NEXT;
          }

          if (hyx_extract (fo, fi_hyx, fi_idx, fi_lut, fi_xfn, frame_ptr,
                           verbose_mode, extract_flags) != 0)
          {
            fprintf (stderr, "error: frame \"%s\" not found in %s!\n",
              frame, fnm_hyx);
            continue;
          }
        }
        if (strcmp (fseg_name, "-") != 0) fclose (fi);
        break;

      case 'f': case 'F':       /* list of frames is in the frame           */
        if (verbose_mode > 0)
          printf ("transfering frames from frame '%s', tmp_file=%s\n",
                  fseg_name, tmp);
        if ((fo_tmp= fopen (tmp, "wb")) == (FILE *) 0)
        {
ERR1:
          fprintf (stderr, "error: can\'t open tmpfile\n");
          goto END5;
        }
        if (hyx_extract (fo_tmp, fi_hyx, fi_idx, fi_lut, fi_xfn,
                         fseg_name, verbose_mode, extract_flags) != 0)
        fflush (fo_tmp);
        rc= fclose (fo_tmp);
        if ((fi= fopen (tmp, "rt")) == (FILE *) 0) goto ERR1;
        goto PROC_LIST;
        break;

      case 'm': case 'M':
        fseg_name= MD5check_string ((unsigned char *) fseg_name);

      case 'x': case 'X':       /* extract just one named frame             */
        if (verbose_mode > 0)
          printf ("transfering single frame '%s'\n", fseg_name);
        if (hyx_extract (fo, fi_hyx, fi_idx, fi_lut, fi_xfn,
                         fseg_name, verbose_mode, extract_flags) != 0)
        {
          fprintf (stderr,
                   "error: frame \"%s\" not found in %s!\n",
                   fseg_name, fnm_hyx);
          goto END5;
        }
        break;

      case 't': case 'T':       /* total recall: extract all frames         */
        if (verbose_mode > 0)
          printf ("transfering *ALL* frames\n");
        for (cnt= 1L; cnt <= last_index; cnt++)
        {
          sprintf (frame, "$#%ld", cnt);
          if (hyx_extract (fo, fi_hyx, fi_idx, fi_lut, fi_xfn,
                           frame, verbose_mode, extract_flags) != 0)
          {
            fprintf (stderr,
                     "error: frame \"%s\" not found in %s!\n",
                     fseg_name, fnm_hyx);
            goto END5;
          }
        }
        break;
    }
  }

END5:
#ifndef NOT_USED
  if (fi_xfn != (FILE *) 0) fclose (fi_xfn);
  if (fi_lut != (FILE *) 0) fclose (fi_lut);
  fclose (fi_idx);
#endif

END2:
#ifndef NOT_USED
  fclose (fi_hyx);
#endif

END1:
  return rv;
}
