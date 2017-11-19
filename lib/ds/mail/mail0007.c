/*
 *  FILE ~/usr/mail/mail0007.c
 *
 *  create a breakup control structure
 *
 *  written:       1995-01-29
 *  latest update: 1995-01-29
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
struct BREAKUP_CONTROL *create_breakup_control ()
{
  struct BREAKUP_CONTROL *bc;

  if ((bc= (struct BREAKUP_CONTROL *)
           calloc (sizeof (struct BREAKUP_CONTROL), 1))
      != (struct BREAKUP_CONTROL *) 0)
  {
    bc->BC_delimiter_mode= DELIMIT_Unix;
    bc->BC_f_rename_file= 1;
    bc->BC_counter= 1;          /* message counter                          */
    bc->BC_dummy_lines= 0;      /* number of lines to be inserted in header */
    bc->BC_remove_lines= 0;     /* number of lines to be removed in header  */
    bc->BC_is_hyx= 1;
    bc->BC_hyx= stdout;
    bc->BC_use_addr= RFC822_From;
    bc->BC_report_mail= record_mails;
    bc->BC_MD_append= &bc->BC_MD_list;
    bc->BC_format= "XQQQ%04d.chk";
  }

  return bc;
}
