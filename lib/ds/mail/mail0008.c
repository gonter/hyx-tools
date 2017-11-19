/*
 *  FILE %usr/mail/mail0008.c
 *
 *  convert a date string into a filename
 *
 *  written:       1995-01-29
 *  latest update: 1996-06-09 11:14:39
 *
 */

#include <stdio.h>
#include <gg/convent.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
int print_mail_description_link (
FILE *fo,
struct MAIL_DESCRIPTION *md)
{
  char *s;
  int cnt;
  int ch;

  fprintf (fo,
           "<hyx.l tdc=hyx.l tdp=14 fr=\"%s\">%14s %4d ",
           str_or_undef (md->MD_frame),
           str_or_undef (md->MD_date),
           md->MD_cnt);

  cnt= 24;
  for (s= str_or_undef (md->MD_addr);
       (ch= *s & 0x00FF) != 0 && cnt > 0;
       s++, cnt--)
    fputc_entity (ch, fo, CONVENT_pc_text);

  blanks (fo, cnt);

  fputs_entity (str_or_undef (md->MD_subj), fo, CONVENT_pc_text);
  fputc ('\n', fo);

  return 0;
}
