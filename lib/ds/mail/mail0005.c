/*
 *  FILE ~/usr/mail/mail0007.c
 *
 *  convert a date string into a filename
 *
 *  written:       1995-01-29
 *  latest update: 1995-01-29
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
int record_mails (
struct BREAKUP_CONTROL *bc,
char *frame,
char *addr,
char *date,
char *subj,
int cnt)
{
  struct MAIL_DESCRIPTION *md;

  if ((md= (struct MAIL_DESCRIPTION *)
           calloc (sizeof (struct MAIL_DESCRIPTION), 1))
      == (struct MAIL_DESCRIPTION *) 0)
    return -1;

  str_assign (&md->MD_frame, frame);
  str_assign (&md->MD_subj, subj);
  str_assign (&md->MD_addr, addr);
  str_assign (&md->MD_date, date);
  md->MD_cnt= cnt;
  *bc->BC_MD_append= md;
  bc->BC_MD_append= &md->MD_next;

  sort_mail (&bc->BC_yt_addr, md, &md->MD_by_addr, str_or_undef (addr));
  sort_mail (&bc->BC_yt_date, md, &md->MD_by_date, str_or_undef (date));
  sort_mail (&bc->BC_yt_subj, md, &md->MD_by_subj, str_or_undef (subj));

  return 0;
}
