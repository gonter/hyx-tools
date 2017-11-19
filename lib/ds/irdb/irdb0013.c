/*
 *  FILE %ds/irdb/irdb0013.c
 *
 *  irrelational database
 *
 *  written:       1996-04-06
 *  latest update: 1996-04-14 20:29:20
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_strdup_to_struct (
struct IRDB_HANDLE *hnd,
char *slot,
char *value)
{
  int rc= 0;
  struct YTREE *yt;

  if (hnd == (struct IRDB_HANDLE *) 0
      || hnd->IRDB_type != IRDBty_struct
      || (yt= ytree_insert_word ((struct YTREE **) &hnd->IRDB_payload,
                                  (unsigned char *) slot))
            == (struct YTREE *) 0
     )
    return -1;

  if (yt->YT_flags & YTflag_EOW) free_or_what ((char *) yt->YT_info);

  yt->YT_flags |= YTflag_EOW;
  yt->YT_info= (long) strdup (value);

  return rc;
}
