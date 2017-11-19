/*
 *  FILE %sgml/hyxidx01.c
 *
 *  make index for hyx-hypertext cluster
 *
 *  written:       1991 05 17
 *  latest update: 1999-04-24 12:00:33
 *  $Id: hyxidx01.c,v 1.3 2002/07/17 07:19:40 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#include <io.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/ytree.h>
#include <gg/lookup.h>
#include <gg/hytxt.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
static char *name_hyx;
static char *name_idx;
static char *name_lut;
static char *name_xfn;

static int ex_hyx;
static int ex_idx;
static int ex_lut;
static int ex_xfn;

static int index_format;
static char *index_frame= (char *) 0;
static char *x_md5_frame= (char *) 0;

static struct HYTXT_FRAME frame;
static char frame_name [1024];

/* ------------------------------------------------------------------------ */
static struct YTREE *ytree= (struct YTREE *) 0;

/* limitations: ----------------------------------------------------------- */
#ifdef MSDOS
#define LEX_IDX_BLOCKS        128
#define LEX_IDX_BLOCKSIZE    1024
#else
#define LEX_IDX_BLOCKS       2048
#define LEX_IDX_BLOCKSIZE    2048
#endif

static long lex_idx_cnt= 1L;
static int lex_idx_block_cnt= 0;
static int initialized= 0;

/* ------------------------------------------------------------------------ */
struct LEXICON_INDEX
{
  long LEXI_begin;
  long LEXI_end;
} ;

static struct LEXICON_INDEX *lex_idxs [LEX_IDX_BLOCKS];

/* Note: Frame begin and end coordinates (byte counts incremented by 1)     */
/*       are stored in struct LEXICON_INDEX.                                */
/*       lex_idxs is a table that points to up to 128 tables                */
/*       of LEXICON_INDEX tables which can store 1024 such entries.         */
/*       Complicated? Uh, is it?                                            */
/* ------------------------------------------------------------------------ */
struct SORT_LIST
{
  struct SORT_LIST *sl_next;
  char *sl_name;
  long sl_index;
  long sl_size;
  char *sl_md5;
} ;

struct SORT_LIST *s_list= (struct SORT_LIST *) 0;

/* ------------------------------------------------------------------------ */
int hyx_index (
char *fn,
char *idx_frame,
char *md5_frame,
int idx_format,
int idx_flags,
int verbose_mode)
{
  char *afn;
  int rv= 0;

  if (fn == (char *) 0 || *fn == 0) return -1;

  if ((afn= translate_logic_filename (fn)) == (char *) 0) afn= fn;

  if (!initialized)
  {
    int i;

    initialized= 1;
    for (i= 0; i < LEX_IDX_BLOCKS; i++) lex_idxs [0]= (void *) 0;
  }

  /* setup frame names used for indexes */
  if (idx_frame != (char *) 0 && *idx_frame == 0) idx_frame= (char *) 0;
  index_frame= idx_frame;
  index_format= idx_format;
  if (md5_frame != (char *) 0 && *md5_frame == 0) md5_frame= (char *) 0;
  x_md5_frame= md5_frame;

  name_hyx= strdup (afn);
  name_idx= fnmcpy2 (afn, ".idx");
  name_lut= fnmcpy2 (afn, ".lut");
  name_xfn= fnmcpy2 (afn, ".xfn");

  ex_hyx= access (name_hyx, 0) ? 0 : 1;
  ex_idx= access (name_idx, 0) ? 0 : 1;
  ex_lut= access (name_lut, 0) ? 0 : 1;
  ex_xfn= access (name_xfn, 0) ? 0 : 1;

  if (verbose_mode)
  {
    printf ("HYX (%d): %s\n", ex_hyx, name_hyx);
    printf ("IDX (%d): %s\n", ex_idx, name_idx);
    printf ("LUT (%d): %s\n", ex_lut, name_lut);
    printf ("XFN (%d): %s\n", ex_xfn, name_xfn);
  }

  if (!ex_hyx) return -1;

  if ((idx_flags & HYXIDX_FLAG_full_scan)
      || !ex_idx
      || !ex_lut
     ) rv= hyx_index_full_scan (verbose_mode);
  else
  if (ex_xfn) rv= hyx_index_rescan ();

  /* else: nothing to do! */

  free (name_hyx);
  free (name_idx);
  free (name_lut);
  free (name_xfn);

  return rv;
}

/* ------------------------------------------------------------------------ */
int hyx_index_insert (char *frnm, long idx, void *client_data)
{
  struct YTREE *yt;

#ifdef MSDOS
  client_data;
#endif

  if (frnm == (char *) 0) return -1;

  if ((yt= (struct YTREE *) ytree_insert_word (&ytree,
                                               (unsigned char *) frnm))
      == (struct YTREE *) 0)
  {
    fprintf (stderr, "error: yt==0 !!!\n");
    return -1;
  }

  if (index_frame != (char *) 0) sort_frame (frnm, idx, 123L, (char *) 0);

  yt->YT_flags |= YTflag_EOW;
  yt->YT_info= idx;

  return 0;
}

/* ------------------------------------------------------------------------ */
int sort_frame (char *fn, long idx, long siz, char *md5)
{
  struct SORT_LIST **slp, *sl;
  int x;

  for (slp= &s_list;; slp= &(*slp)->sl_next)
  {
    if (*slp != (struct SORT_LIST *) 0
       && strcmp ((*slp)->sl_name, fn) == 0)
    { /* update */
      sl= *slp;
      goto UPDATE;
    }

    if (*slp == (struct SORT_LIST *) 0
       || (x= strcmp_c ((*slp)->sl_name, fn)) > 0
       || (x == 0 && strcmp ((*slp)->sl_name, fn) > 0))
    {
      if ((sl= (struct SORT_LIST *) calloc (sizeof (struct SORT_LIST), 1))
          == (struct SORT_LIST *) 0)
      {
        fprintf (stderr, "sort_frame: out of memory!\n");
        return -1;
      }

      sl->sl_name= strdup (fn);
      if (md5 != (char *) 0) sl->sl_md5= strdup (md5);
      sl->sl_next= *slp;
      *slp= sl;
UPDATE:
      sl->sl_index= idx;
      sl->sl_size= siz;
      return 0;
    }
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int hyx_index_dump_frame (FILE *fo, char *idx_frame, int idx_format)
{
  struct SORT_LIST *sl;
  char *frnm;

  fprintf (fo, "<Frame %s>", idx_frame);
  hyx_write_stamp (fo, "p=\"hyxidx\"");
  if (strcmp (idx_frame, "$$root") != 0)
    fprintf (fo, "<hyx.l dir=up fr=\"$$root\">\n");
  else fputc ('\n', fo);

  switch (idx_format)
  {
    default:
      fprintf (fo, "  This is \'%s\', the index of all frames\n", idx_frame);
      fprintf (fo, "  in the hypertext cluster \'%s\'\n", name_hyx);
      fprintf (fo, "  as generated by hyxidx.\n\n");
      break;
  }

  switch (idx_format)
  {
    case HYXIDX_FMT_LINK:
      fprintf (fo, "  frame name\n");
      fprintf (fo, "---------------------------------------------------\n");
      fprintf (fo, "<hyx.index fmt=%d>\n", idx_format);
      for (sl= s_list; sl != (struct SORT_LIST *) 0; sl = sl->sl_next)
      {
        frnm= sl->sl_name;
        fprintf (fo, "<hyx.l fr=\"%s\" tdc=index tdp=%d>%s\n",
                 frnm, strlen (frnm), frnm);
      }
      fprintf (fo, "</hyx.index>\n");
      break;

    case HYXIDX_FMT_MD5:
      fprintf (fo,
"MD5 Checksum                      index num.   size frame name\n");
      fprintf (fo,
"--------------------------------------------------------------\n");
      fprintf (fo, "<hyx.index fmt=%d>\n", idx_format);
      for (sl= s_list; sl != (struct SORT_LIST *) 0; sl= sl->sl_next)
      {
        frnm= sl->sl_name;
        fprintf (fo, "%s  0x%08lX %6ld <hyx.l fr=\"%s\" tdc=index tdp=%d>%s\n",
                 (sl->sl_md5 == (char *) 0)
                   ? "................................"
                   : sl->sl_md5,
                 sl->sl_index, sl->sl_size,
                 frnm, strlen (frnm), frnm);
      }
      fprintf (fo, "</hyx.index>\n");
      break;

    case HYXIDX_FMT_NORMAL:
    default:
      fprintf (fo, "index num.   size frame name\n");
      fprintf (fo, "----------------------------\n");
      fprintf (fo, "<hyx.index fmt=%d>\n", idx_format);
      for (sl= s_list; sl != (struct SORT_LIST *) 0; sl= sl->sl_next)
      {
        frnm= sl->sl_name;
        fprintf (fo, "0x%08lX %6ld <hyx.l fr=\"%s\" tdc=index tdp=%d>%s\n",
                 sl->sl_index, sl->sl_size,
                 frnm, strlen (frnm), frnm);
      }
      fprintf (fo, "</hyx.index>\n");
      break;
  }
  fprintf (fo, "</Frame>\n");

  return 0;
}

/* ------------------------------------------------------------------------ */
/* scan hyx file completely and produce idx and lut files */
int hyx_index_full_scan (int verbose_mode)
{
  FILE *hyx;
  FILE *lut;
  FILE *idx;
  long hyx_pos= 0L;
  struct YTREE *yt;
  int rc;
  long act_index;
  long act_length;
  int block_num;
  int block_idx;
  int i;
  long ii;
  struct LEXICON_INDEX *lex_idx;
  char md5_str [34];
  char *md5_ptr;
  int index_dumps= 0;
  char *idx_frame= (char *) 0;
  int idx_format= 0;

  ytree= (struct YTREE *) 0;
  frame.hytxt_frame_name= frame_name;

  md5_str [0]= 0;
  md5_ptr= (x_md5_frame == (char *) 0) ? (char *) 0 : md5_str;

  ii= hyx_get_last_index (name_idx);
  printf ("hyxidx: index=%s last_index=0x%08lX\n", name_idx, ii-1);

  if ((hyx= fopen (name_hyx, "rb")) == (FILE *) 0) return -1;

  for (;;)
  {
    rc= hytxt_scan_entry (hyx, &hyx_pos, &frame,
                          HYXSM_no_attributes|HYXSM_no_allocation,
                          md5_ptr);

    if (rc != 0)
    {
      fclose (hyx);
      idx_frame= (char *) 0;
      idx_format= 0;

DUMP_INDEX:
      if (index_dumps >= 2 || index_dumps < 0
          || s_list == (void *) 0) break;

      switch (index_dumps)
      {
        case 0:
          idx_frame= index_frame;
          idx_format= index_format;
          break;
        case 1:
          idx_frame= x_md5_frame;
          idx_format= HYXIDX_FMT_MD5;
          break;
      }
      if (idx_frame == (char *) 0) break;

      /* als letztes den Index Frame einbauen */
      strcpy (frame_name, idx_frame);
      if ((hyx= fopen (name_hyx, "ab")) != (FILE *) 0)
      {
        fputc ('\n', hyx);
        fseek (hyx, 0L, 2);
        frame.hytxt_frame_pos_beg= ftell (hyx);
        hyx_index_dump_frame (hyx, idx_frame, idx_format);
        frame.hytxt_frame_pos_end= ftell (hyx) -1L;
        fclose (hyx);
      }
      index_dumps++;
    }

    if (*frame_name == 0) continue;  /* don't want empty frame names */

    if ((yt= (struct YTREE *) ytree_insert_word (&ytree,
                                (unsigned char *) frame_name))
        == (struct YTREE *) 0)
    {
      printf ("error: yt == 0 !!!\n");
      return -1;
    }

    if (yt->YT_info == 0L)
    {
      yt->YT_flags |= YTflag_EOW;
      yt->YT_info= act_index= lex_idx_cnt;
      lex_idx_cnt++;
    }
    else
    {
      act_index= yt->YT_info;
    }

    act_length= frame.hytxt_frame_pos_end - frame.hytxt_frame_pos_beg + 1L;
    if (index_frame != (char *) 0)
      sort_frame (frame_name, act_index, act_length, md5_ptr);

    if (verbose_mode > 1)
    {
      printf ("0x%08lX 0x%08lX 0x%08lX %s %s\n",
              act_index, frame.hytxt_frame_pos_beg,
              act_length, md5_str, frame_name);
    }

    if (act_index > lex_idx_cnt)
    {
      fprintf (stderr,
        "act_index > lex_idx_cnt: %ld > %ld\n", act_index, lex_idx_cnt);
      fprintf (stderr,
        "... this should not happen, I guess, isn't it?\n");
      fclose (hyx);
      return -1;
    }

    block_num= (int) (act_index/((long)LEX_IDX_BLOCKSIZE));
    block_idx= (int) (act_index%((long)LEX_IDX_BLOCKSIZE));
    if (block_num >= lex_idx_block_cnt)
    {
      if (lex_idx_block_cnt >= LEX_IDX_BLOCKS)
        lex_idx= (void *) 0;
      else
      {
        lex_idx= lex_idxs[block_num]
               = (struct LEXICON_INDEX *)
                   calloc (sizeof (struct LEXICON_INDEX), LEX_IDX_BLOCKSIZE);
        lex_idx_block_cnt++;
      }
    }
    else lex_idx= lex_idxs[block_num];

    if (lex_idx == (void *) 0)
    {
      fprintf (stderr, "index block %d not available for %ld\n",
               block_num, act_index);
      fclose (hyx);
      return -1;
    }
    lex_idx [block_idx].LEXI_begin= frame.hytxt_frame_pos_beg;
    lex_idx [block_idx].LEXI_end= frame.hytxt_frame_pos_end;

    if (rc != 0) goto DUMP_INDEX;
  }

  /* write LUT file */
  if ((lut= fopen (name_lut, "wb")) == (FILE *) 0) return -1;
  ytree_size (ytree);
  ytree_dump (lut, ytree);
  fclose (lut);

  /* write IDX file */
  if ((idx= fopen (name_idx, "wb")) == (FILE *) 0) return -1;
  dpp_fwrite_long (idx, -1L, 4);        /* Dummy Index # 0 */
  dpp_fwrite_long (idx, -1L, 4);
  dpp_fwrite_long (idx, -1L, 4);
  lex_idx= lex_idxs[0];
  block_num= 1;
  i= 1;
  for (ii= 1; ii < lex_idx_cnt; ii++, i++)
  {
    if (i == LEX_IDX_BLOCKSIZE)
    {
      lex_idx=lex_idxs[block_num++];
      i=0;
    }
    dpp_fwrite_long (idx, lex_idx[i].LEXI_begin, 4);
    dpp_fwrite_long (idx, lex_idx[i].LEXI_end, 4);
    dpp_fwrite_long (idx, 0L, 4);
  }
  fclose (idx);

  fprintf (stderr, "highest index: %ld;  index blocks: %d\n",
           lex_idx_cnt, lex_idx_block_cnt);

  if (ex_xfn) unlink (name_xfn);

  return 0;
}

/* ------------------------------------------------------------------------ */
/* scan lut file and include the xfn file into it */
int hyx_index_rescan ()
{
  ytree= (struct YTREE *) 0;
  lut_process (name_lut, hyx_index_insert, (void *) 0, 0L);
  xfn_process (name_xfn, hyx_index_insert, (void *) 0, 0L);
  ytree_dump_to_lut_file (name_lut, ytree);
  unlink (name_xfn);

  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef OLD_VERSION
int hyx_index_rescan ()
{
  FILE *lut;
  FILE *xfn;
  long idx;

  /* scan lut file ... */
  if ((lut= fopen (name_lut, "rb")) == (FILE *) 0) return -1;
  ytree_full_scan (lut, &ytree, (void *) 0, 0, (void *) 0, 0);
  fclose (lut);

  /* scan extended frame name file */
  if ((xfn= fopen (name_xfn, "rb")) == (FILE *) 0) return -1;
  for (;;)
  {
    fscanf (xfn, "%lx", &idx);
    if (feof (xfn)) break;
    fscanf (xfn, "%*[ \t]");
    fscanf (xfn, "%[^\n]", frame_name);
    if (feof (xfn)) break;
    fgetc (xfn);

    hyx_index_insert (frame_name, idx, (void *) 0);
  }
  fclose (xfn);

  /* write lut file back */
  if ((lut= fopen (name_lut, "wb")) == (FILE *) 0) return -1;
  ytree_size (ytree);
  ytree_dump (lut, ytree);
  fclose (lut);

  unlink (name_xfn);

  return 0;
}
#endif
