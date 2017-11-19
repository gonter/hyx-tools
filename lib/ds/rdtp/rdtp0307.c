/*
 *  FILE %ds/rdtp/rdtp0307.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1996-09-15 13:51:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_print_statistics (struct RDTP_THREAD *thr)
{
  struct SGML_BUILDUP *sb;

  if (thr == (struct RDTP_THREAD *) 0
      || (sb= (struct SGML_BUILDUP *) thr->payload)
               == (struct SGML_BUILDUP *) 0
     )
  {
    rdtp_bad_thread ("rdtp0307");
    return -1;
  }

  printf ("tag names\n");
  ytree_process_info (sb->element_names, sgml_print_name_statistics, (void *) 0);

  printf ("entity names\n");
  ytree_process_info (sb->entity_names, sgml_print_name_statistics, (void *) 0);

  return 0;
}
