/*
 *  FILE %ds/rdtp/rdtp0308.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1996-10-13 20:57:29
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
int sgml_print_name_statistics (long cmd_info, void *thr_info)
{
  struct SGML_TAG_NAME *cmd;

  if ((cmd= (struct SGML_TAG_NAME *) cmd_info)
            == (struct SGML_TAG_NAME *) 0)
  {
    fprintf (stderr, "rdtp0308: bad tag record!\n");
    return -1;
  }

#ifdef MSDOS
  thr_info;
#endif /* MSDOS */

  printf ("%5ld %5s '%s'\n",
          cmd->ref_counter,
          (cmd->tag_def == (struct SGML_ELEMENT_DECLARATION *) 0)
            ? "UNDEF" : "DEF",
          cmd->tag_name);

  return 0;
}
