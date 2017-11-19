/*
 *  FILE %ds/rdtp/rdtp0206.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1997-01-15 10:52:13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp02.h>

/* ------------------------------------------------------------------------ */
int rtf_cmd_name_end (void *thrp, int ch)
{
  struct RTF_BUILDUP *rtf;
  struct YTREE *yt;
  struct RTF_COMMAND_NAME *cmd;
  struct RDTP_THREAD *thr;

  if ((thr= (struct RDTP_THREAD *) thrp) == (struct RDTP_THREAD *) 0
      || (rtf= thr->payload) == (struct RTF_BUILDUP *) 0
     )
  {
    fprintf (stderr, "rdtp0204: bad thread\n");
    return -1;
  }

#ifdef MSDOS
  ch;
#endif /* MSDOS */

  rtf->bl1 [rtf->bl1_cnt]= 0;
  /* printf ("rtf: name='%s'\n", rtf->bl1); */

  if ((yt= ytree_insert_word (&rtf->names, (unsigned char *) rtf->bl1))
           == (struct YTREE *) 0) return -1;

  /* create a new command statistics control structure */
  if (!(yt->YT_flags & YTflag_EOW)
      || (cmd= (struct RTF_COMMAND_NAME *) yt->YT_info)
               == (struct RTF_COMMAND_NAME *) 0
     )
  {
    if ((cmd= (struct RTF_COMMAND_NAME *)
              calloc (sizeof (struct RTF_COMMAND_NAME), 1))
              == (struct RTF_COMMAND_NAME *) 0) return -1;

    yt->YT_flags |= YTflag_EOW;
    yt->YT_info= (long) cmd;
    cmd->cmd_name= strdup (rtf->bl1);
  }

  cmd->counter++;

  return 0;
}
