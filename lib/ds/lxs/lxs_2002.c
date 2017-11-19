/*
 *  FILE %ds/lxs/lxs_2002.c
 *
 *  lexicon services
 *
 *  written:       1996-12-20
 *  latest update: 1996-12-22 11:48:01
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/lxs2.h>

/* ------------------------------------------------------------------------ */
static struct LEXICON_ENTRY *ins_entry (struct YTREE **ytp, char **sp);

/* ------------------------------------------------------------------------ */
struct LEXICON_ENTRY *lxs_record (
struct LEXICON_CONTEXT *lxc,
char *str,
int is_mixed)
{
  struct LEXICON_ENTRY *lxe= (struct LEXICON_ENTRY *) 0;
  struct LEXICON_ENTRY *lxe_mixed= (struct LEXICON_ENTRY *) 0;
  struct LEXICON_ENTRY *lxe_lower= (struct LEXICON_ENTRY *) 0;
  char *w_mixed;
  char *w_lower;
  int ref= 0;

  if (lxc == (struct LEXICON_CONTEXT *) 0
      || str == (char *) 0
      || (w_lower= strdup (str)) == (char *) 0
     )
  {
DONE:
    fprintf (stderr, "lxs_2002: error or no memory! (ref=%d)\n", ref);

    return (struct LEXICON_ENTRY *) 0;
  }
  ref++;

  if (is_mixed == -1)
    is_mixed= (verify (str, "abcdefghijklmnopqrstuvwxyz")) ? 1 : 0;

  if (is_mixed && lxc->to_lower)
  {
    to_lower (w_lower);
    is_mixed= 0;
  }

  if (is_mixed)
  {
    if ((w_mixed= strdup (w_lower)) == (char *) 0) goto DONE;
    to_lower (w_lower);
  }

  if ((lxe_lower= ins_entry (&lxc->lower_case, &w_lower))
      == (struct LEXICON_ENTRY *) 0
     ) goto DONE;

  if (is_mixed)
  {
    if ((lxe_mixed= ins_entry (&lxc->mixed_case, &w_mixed))
        == (struct LEXICON_ENTRY *) 0
       ) goto DONE;

    lxe= lxe_mixed;
    lxc->num_entries_mixed++;
  }
  else
  {
    lxe= lxe_lower;
    lxc->num_entries_lower++;
  }

  lxe->ref_count++;

  return lxe;
}

/* ------------------------------------------------------------------------ */
static struct LEXICON_ENTRY *ins_entry (
struct YTREE **ytp,
char **sp)
{
  struct LEXICON_ENTRY *lxe= (struct LEXICON_ENTRY *) 0;
  struct YTREE *yt;

  if ((yt= ytree_insert_word (ytp, (unsigned char *) *sp))
      == (struct YTREE *) 0
     )
  {
ERR:
    return (struct LEXICON_ENTRY *) 0;
  }

  if (yt->YT_flags & YTflag_EOW)
  {
    if ((lxe= (struct LEXICON_ENTRY *) yt->YT_info)
        == (struct LEXICON_ENTRY *) 0) goto ERR;

    free (*sp);
    *sp= lxe->entry;
  }
  else
  {
    if ((lxe= (struct LEXICON_ENTRY *)
              calloc (sizeof (struct LEXICON_ENTRY), 1))
        == (struct LEXICON_ENTRY *) 0) goto ERR;

    yt->YT_info= (long) *sp;
    yt->YT_flags |= YTflag_EOW;

    lxe->entry= *sp;
  }

  return lxe;
}
