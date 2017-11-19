/*
 *  FILE %ds/irdb/irdb0005.c
 *
 *  irrelational database
 *
 *  written:       1996-04-05
 *  latest update: 1996-04-14 15:09:24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_dump_struct (
struct YTREE *yt,
char *str,
void *cd)
{
  int rc= 0;
  struct IRDB_DUMP *dmp;
  long pos;
  FILE *fo;

  if (yt == (struct YTREE *) 0
      || (dmp= (struct IRDB_DUMP *) cd) == (struct IRDB_DUMP *) 0
      || (fo= dmp->fo) == (FILE *) 0
     )
    return -1;

  if (!(yt->YT_flags & YTflag_EOW)) return 0;

#ifdef DEBUG2
printf ("irdb0005: str='%s', type=%s\n", str, irdb_type (dmp->type));
#endif /* DEBUG2 */
#ifdef MSDOS
  str;
#endif /* MSDOS */

  switch ((int) dmp->type)
  {
    case IRDBty_int:
      /* this case should't show up here anyway because */
      /* it's dumped together with the YTREE            */
      break;

    case IRDBty_string:
      pos= irdb_dump_string (fo, (char *) yt->YT_info);
      free_or_what ((void *) yt->YT_info);
      yt->YT_info= pos;
      break;

    case IRDBty_float:
    case IRDBty_block:
    case IRDBty_array:
      fprintf (stderr, "irdb0005: T2D!\n");
      break;

    case IRDBty_struct:
      {
        struct IRDB_HANDLE *hnd;

        if ((hnd= (struct IRDB_HANDLE *) yt->YT_info)
             != (struct IRDB_HANDLE *) 0)
        {
#ifdef DEBUG2
printf ("irdb0005: dump struct\n");
#endif /* DEBUG2 */
          pos= irdb_dump_to_stream (fo, hnd);

#ifdef IRDB_USE_CLASS_NAME
          free_or_what (hnd->IRDB_class_name);
#endif /* IRDB_USE_CLASS_NAME */

          free (hnd);
          yt->YT_info= pos;
        }
      }
      break;
  }

  return rc;
}
