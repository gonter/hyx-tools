/*
 *  FILE %ds/rdtp/rdtp0208.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1996-06-22 10:11:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp02.h>

/* ------------------------------------------------------------------------ */
int rtf_print_name_statistics (long cmd_info, void *thr_info)
{
  struct RTF_COMMAND_NAME *cmd;

  if ((cmd= (struct RTF_COMMAND_NAME *) cmd_info)
            == (struct RTF_COMMAND_NAME *) 0)
  {
    fprintf (stderr, "rdtp0208: bad command record!\n");
    return -1;
  }

#ifdef MSDOS
  thr_info;
#endif /* MSDOS */

  printf ("command: %5ld '%s'\n", cmd->counter, cmd->cmd_name);

  return 0;
}
