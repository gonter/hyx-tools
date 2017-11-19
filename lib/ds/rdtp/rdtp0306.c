/*
 *  FILE %ds/rdtp/rdtp0306.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-22
 *  latest update: 1996-09-15 10:19:58
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
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_name_end (
struct SGML_BUILDUP *sgml_structure,
int ch,
struct YTREE **name_table)
{
#ifdef _JUNK_
  struct SGML_TAG_NAME *cmd;
  struct YTREE *yt;

  if (sgml_structure == (struct SGML_BUILDUP *) 0
      || name_table == (struct YTREE **) 0
     )
  {
    fprintf (stderr, "rdtp0204: bad thread\n");
    return -1;
  }

#ifdef MSDOS
  ch;
#endif /* MSDOS */

  sgml_structure->bl1 [sgml_structure->bl1_cnt]= 0;
  printf ("sgml: name='%s'\n", sgml_structure->bl1);

  if ((yt= ytree_insert_word (name_table, (unsigned char *) sgml_structure->bl1))
           == (struct YTREE *) 0) return -1;

  /* create a new command statistics control structure */
  if (!(yt->YT_flags & YTflag_EOW)
      || (cmd= (struct SGML_COMMAND_NAME *) yt->YT_info)
               == (struct SGML_COMMAND_NAME *) 0
     )
  {
    if ((cmd= (struct SGML_COMMAND_NAME *)
              calloc (sizeof (struct SGML_COMMAND_NAME), 1))
              == (struct SGML_COMMAND_NAME *) 0) return -1;

    yt->YT_flags |= YTflag_EOW;
    yt->YT_info= (long) cmd;
    cmd->cmd_name= strdup (sgml_structure->bl1);
  }

  cmd->counter++;

#else
#ifdef MSDOS
  sgml_structure; ch; name_table;
#endif /* MSDOS */
#endif /* !_JUNK_ */
  return 0;
}
