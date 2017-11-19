/*
 *  FILE %usr/mail/mail0006.c
 *
 *  convert a date string into a filename
 *
 *  written:       1995-01-29
 *  latest update: 1997-01-25 18:56:20
 *
 */

#include <gg/ytree.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
int sort_mail (
struct YTREE **ytr,
struct MAIL_DESCRIPTION *md,
struct MAIL_DESCRIPTION **md_app,
char *str)
{
  struct YTREE *yt;

  if ((yt= ytree_insert_word (ytr, str)) == (struct YTREE *) 0) return -1;

  yt->YT_flags |= YTflag_EOW;
  *md_app= (struct MAIL_DESCRIPTION *) yt->YT_info;
  yt->YT_info= (long) md;

  return 0;
}
