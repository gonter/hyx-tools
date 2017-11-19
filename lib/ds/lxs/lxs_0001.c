/*
 *  FILE ~/usr/ds/lxs/lxs_0001.c
 *
 *  lexicon services
 *
 *  written:       1994-03-27
 *  latest update: 1995-07-18
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/lxs.h>
#include <gg/attlist.h>

/* ------------------------------------------------------------------------ */
/* a cache of already requested words is kept in a ytree structure */

static int max_lexicons= 0;
static struct YTREE *lxs_ytree= (struct YTREE *) 0;

static char **lut_file;
static char **word_ref_file;
static FILE **f_lut;
static FILE **f_wr;

/* ------------------------------------------------------------------------ */
struct LXS_OLD_ENTRY *lxs_get_word (
int lexicon_number,                     /* lexicon to be used               */
unsigned char *wrd,                     /* word to be lookup up             */
int cr_flag)                            /* insert in temporary structures   */
{
  struct YTREE *yt;
  int yt_update= 0;     /* 1 -> yt pointer must be updated */
  int flg_word_ref= 0;  /* 1 -> word_ref found */

  /* datastructures created and returned */
  struct LXS_OLD_ENTRY *lxse= (struct LXS_OLD_ENTRY *) 0;
  struct WORD_REF *wref= (struct WORD_REF *) 0;
/*  struct ATTRIBUTE_LIST *attl= (struct ATTRIBUTE_LIST *) 0; ****/

  if (lexicon_number < 0
      || lexicon_number >= max_lexicons) return (struct LXS_OLD_ENTRY *) 0;

  if (cr_flag)
  {
    if ((yt= ytree_insert_word (&lxs_ytree, wrd)) == (struct YTREE *) 0)
      return (struct LXS_OLD_ENTRY *) 0; /* error */

    yt->YT_flags |= YTflag_EOW;
    if (yt->YT_info != 0L) return (struct LXS_OLD_ENTRY *) yt->YT_info;
    yt_update= 1;
  }
  else
  {
    if ((yt= ytree_lookup_word (lxs_ytree, wrd)) != (struct YTREE *) 0)
      return (struct LXS_OLD_ENTRY *) yt->YT_info;
  }

  if (f_lut [lexicon_number] != (FILE *) 0
      && f_wr [lexicon_number] != (FILE *) 0)
  {
    if ((wref= calloc (sizeof (struct WORD_REF), 1)) == (void *) 0)
      goto NO_MEMORY;

    if (lmd_deref_word_ref (f_lut [lexicon_number],
                            f_wr [lexicon_number], wrd, 1, wref) == 0)
      flg_word_ref= 1;
  }

  if (flg_word_ref)
  {
    if ((lxse= calloc (sizeof (struct LXS_OLD_ENTRY), 1)) == (void *) 0)
    {
NO_MEMORY:
      fprintf (stderr, "error: lxs_get_word() no memory!\n");
      return (struct LXS_OLD_ENTRY *) 0;
    }

    lxse->lxs_entry_type= LXS_ty_word_ref;
    lxse->lxs_entry_size= sizeof (struct WORD_REF *) 0;
    lxse->lxs_entry= wref;

    if (!yt_update)
    { /* created only if found */
      if ((yt= ytree_insert_word (&lxs_ytree, wrd)) == (struct YTREE *) 0)
        return (struct LXS_OLD_ENTRY *) 0;
      yt->YT_flags |= YTflag_EOW;
    }

    yt->YT_info= (long) lxse;
  }

  return lxse;
}

/* ------------------------------------------------------------------------ */
int lxs_set_word_ref (
int lexicon_number,                     /* lexicon to be used               */
char *fnm_lut,
char *fnm_wr)
{
  if (lexicon_number < 0
      || lexicon_number >= max_lexicons) return -1;

  if ((f_lut[lexicon_number]=
         fopen (lut_file[lexicon_number]= fnm_lut, "rb"))
      == (FILE *) 0) goto ERROR;

  if ((f_wr[lexicon_number]=
         fopen (word_ref_file[lexicon_number]= fnm_wr, "rb"))
      == (FILE *) 0)
  {
    fclose (f_lut[lexicon_number]);
    f_lut[lexicon_number]= (FILE *) 0;
ERROR:
    return -1;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int lxs_shutdown_word_ref (
int lexicon_number)                     /* lexicon to be used               */
{
  if (lexicon_number < 0
      || lexicon_number >= max_lexicons) return -1;

  if (f_lut[lexicon_number] != (FILE *) 0) fclose (f_lut[lexicon_number]);
  if (f_wr[lexicon_number] != (FILE *) 0) fclose (f_wr[lexicon_number]);
  f_lut[lexicon_number]= f_wr[lexicon_number]= (FILE *) 0;

  return 0;
}

/* ------------------------------------------------------------------------ */
int lxs_intialize (int num)
{
  if (num < 0) return -1;

  lut_file= (char **) calloc (sizeof (char *), num);
  word_ref_file= (char **) calloc (sizeof (char *), num);
  f_lut= (FILE **) calloc (sizeof (FILE *), num);
  f_wr= (FILE **) calloc (sizeof (FILE *), num);

  max_lexicons= num;

  return 0;
}
