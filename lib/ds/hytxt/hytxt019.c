/*
 *  FILE %ds/hytxt/hytxt019.c
 *
 *  update or create a frame in a HYX cluster
 *
 *  written:       1994-06-03
 *  latest update: 1996-12-03 22:14:51
 *
 */

#include <stdio.h>
#include <gg/sbr.h>
#include <gg/dpp.h>
#include <gg/fileio.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_update (
char *fn_hyx,
char *fn_idx,
char *fn_lut,
char *fn_xfn,
struct FILE_SEGMENT *segments,
int verbose_mode)
{
  FILE *fi_lut;
  FILE *fi_xfn;
  FILE *fi_idx;
  FILE *fo_hyx;
  struct FILE_SEGMENT *sg;
  int rc= -1;
  int cnt_new= 0;
  int cnt_upd= 0;
  long idx;
  long last_idx;
  long real_last_idx;
  int i;

  /* check out, if something has to be done at all */
  if (segments == (struct FILE_SEGMENT *) 0) return 0;

  if ((fo_hyx= fopen (fn_hyx, "ab")) == (FILE *) 0)
  {
    fprintf (stderr,
             "hyx_update: can\'t append to cluster file %s\n",
             fn_hyx);
    goto ERR1;
  }
  fseek (fo_hyx, (long) 0, 1);

  real_last_idx= last_idx= hyx_get_last_index (fn_idx);
/*** printf ("hyx_update: last_idx=0x%08lX\n", last_idx); ***/

  if ((fi_idx= fopen (fn_idx, "rb")) == (FILE *) 0)
  {
#ifdef JUNK
    fprintf (stderr,
             "hyx_update: note: can\'t read index file %s!  creating it...\n",
             fn_idx);
#endif /* JUNK */
    real_last_idx= last_idx= 0L;
  }

  fi_lut= fopen (fn_lut, "rb");
  fi_xfn= fopen (fn_xfn, "rb");

  /* Phase 1: find index number and transfer data to HYX file */
  for (sg= segments; sg != (struct FILE_SEGMENT *) 0; sg= sg->FS_next)
  {
    /* Phase 1a: get the current index of the frame, if there's any */
    idx= (sg->FS_index > 0L && sg->FS_index <= last_idx)
         ? sg->FS_index
         : hyx_get_index (fi_idx, fi_lut, fi_xfn, sg->FS_frame_name);

    if (idx <= 0L)              /* this frame was not found in the lookup   */
    {                           /* files, so it must be a new one...        */
      idx= ++last_idx;
      cnt_new++;
    }
    else
    {
      /* update handling */
      cnt_upd++;
    }

    sg->FS_index= idx;

    /* Phase 1b: transfer the data to the cluster */
    if (sg->FS_size > 0L)
    {
      fputc ('\n', fo_hyx);
      sg->FS_begin= ftell (fo_hyx);
      f2transfer (sg->FS_file_name, fo_hyx, sg->FS_from, sg->FS_size);
      sg->FS_end= ftell (fo_hyx) - 1L;
    }
    else
    {
/*** printf (" DELETE\n"); ***/
      sg->FS_begin= 0L;
      sg->FS_end= 0L;
    }
    sg->FS_cluster= 0L;
  }

  fclose (fo_hyx);
  fclose_or_what (fi_lut);
  fclose_or_what (fi_xfn);
  fclose_or_what (fi_idx);

/*** printf ("hyx_update: upd=%d new=%d\n", cnt_upd, cnt_new); ***/

  if (cnt_upd > 0)
  {
    if (verbose_mode >= 1) printf ("updating %d entries\n", cnt_upd);

    if ((fi_idx= fopen (fn_idx, "r+b")) == (FILE *) 0)
    {
      fprintf (stderr,
               "hyx_update: error: can\'t update index file %s!\n",
               fn_idx);
      goto ERR1;
    }

    /* Phase 2: update existing index entries */
    for (sg= segments; sg != (struct FILE_SEGMENT *) 0; sg= sg->FS_next)
    {
      if (sg->FS_index >= 1 && sg->FS_index <= real_last_idx)
      {
/****************
printf ("hyx_update: seeking entry 0x%lx at positition 0x%lx\n",
sg->FS_index, sg->FS_index*((long) HYXIDX_REC_SIZE));
****************/
        fseek (fi_idx, sg->FS_index*((long) HYXIDX_REC_SIZE), 0);
        dpp_fwrite_long (fi_idx, sg->FS_begin, 4);
        dpp_fwrite_long (fi_idx, sg->FS_end, 4);
        dpp_fwrite_long (fi_idx, sg->FS_cluster, 4);
      }
    }
    fclose (fi_idx);
  }

  if (cnt_new > 0)
  {
    if (verbose_mode >= 1) printf ("appending %d entries\n", cnt_new);

    if ((fi_idx= fopen (fn_idx, "ab")) == (FILE *) 0)
    {
      fprintf (stderr,
               "hyx_update: error: can\'t append to index file %s!\n",
               fn_idx);
      goto ERR1;
    }

    if ((fi_xfn= fopen (fn_xfn, "ab")) == (FILE *) 0)
    {
      fclose (fi_idx);
      fprintf (stderr,
               "hyx_update: error: can\'t append to xfn file %s!\n",
               fn_xfn);
      goto ERR1;
    }

    if (real_last_idx == 0L)
      for (i= 0; i < 3; i++) /* create dummy index #0 */
        dpp_fwrite_long (fi_idx, -1L, 4);

    /* Phase 3: append new index and xfn entries to those two files         */
    /* note: the entries in the list should be in the right order!          */
    for (sg= segments; sg != (struct FILE_SEGMENT *) 0; sg= sg->FS_next)
    {
/********************
printf ("hyx_update: sg->FS_index=%ld real_last_idx=%ld\n",
sg->FS_index, real_last_idx);
********************/

      if (sg->FS_index > real_last_idx)
      {
        dpp_fwrite_long (fi_idx, sg->FS_begin, 4);
        dpp_fwrite_long (fi_idx, sg->FS_end, 4);
        dpp_fwrite_long (fi_idx, sg->FS_cluster, 4);
        fprintf (fi_xfn, "%lx %s\n", sg->FS_index, sg->FS_frame_name);
      }
    }

    fclose (fi_idx);
    fclose (fi_xfn);
  }

  rc= 0;

ERR1:
  return rc;
}
