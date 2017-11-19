/*
 *  FILE %ds/mail/mail0009.c
 *
 *  convert a date string into a filename
 *
 *  written:       1995-01-29
 *  latest update: 1997-11-27 19:59:06
 *
 */

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
int print_mail_description_list (
FILE *fo,
struct MAIL_DESCRIPTION *md,
int sort_mode)
{
  while (md != (struct MAIL_DESCRIPTION *) 0)
  {
    print_mail_description_link (fo, md);

    switch (sort_mode)
    {
      case 0:
        md= md->MD_next;
        break;

      case RFC822_From:
      case RFC822_To:
        md= md->MD_by_addr;
        break;

      case RFC822_Date:
        md= md->MD_by_date;
        break;

      case RFC822_Subject:
        md= md->MD_by_subj;
        break;

      default:
        goto STOP;
    }
  }

STOP:
  return 0;
}
