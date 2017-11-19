/*
 *  FILE %ds/irdb/irdb0014.c
 *
 *  irrelational database
 *
 *  written:       1996-04-06
 *  latest update: 1996-05-05 11:17:20
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/irdb.h>

#ifdef DEBUG0
#define DEBUG2
#endif

/* ------------------------------------------------------------------------ */
long *irdb_locate_info (
struct IRDB_POS *pos,
char *slots[],
int slot_cnt,
int create,
long ty)                        /* type of last dimenstion, if created      */
{
  struct YTREE *yt= (struct YTREE *) 0;
  struct IRDB_HANDLE *hnd;
  char *slot;

  if (pos == (struct IRDB_POS *) 0
       || slot_cnt <= 0
      ) return (long *) 0;

  hnd= pos->IRDB_handle;

  while (slot_cnt > 0)
  {
    slot= *slots++;
    slot_cnt--;

    if (hnd == (struct IRDB_HANDLE *) 0)
      return (long *) 0;

    if (hnd->IRDB_type == IRDBty_struct_dumped)
    {
      int rc;

      rc= irdb_restore (pos, hnd);
printf ("irdb0014: restore, rc=%d\n", rc);
    }

    if (hnd->IRDB_type != IRDBty_struct)
      return (long *) 0;

    if (create)
    {
#ifdef DEBUG2
printf ("irdb0014: check slot_cnt=%d slot='%s' ", slot_cnt, slot);
#endif /* DEBUG2 */
      if ((yt= ytree_insert_word ((struct YTREE **) &hnd->IRDB_payload,
                                  (unsigned char *) slot))
            == (struct YTREE *) 0)
        return (long *) 0;

      if (!(yt->YT_flags & YTflag_EOW))
      { /* create new substructure, since it doesn't already exist */
#ifdef DEBUG2
fputs ("created", stdout);
#endif /* DEBUG2 */
        yt->YT_flags |= YTflag_EOW;

        if (slot_cnt > 1)
          yt->YT_info= (long) irdb_new_struct_handle ((char *) 0,
                                                      (long) IRDBty_struct);

        if (slot_cnt == 1)
        {
          yt->YT_info= (long) irdb_new_struct_handle ((char *) 0, ty);
#ifdef DEBUG2
printf (" **pl_ty=%s**", irdb_type (ty));
#endif /* DEBUG2 */
        }

#ifdef DEBUG2
        if (slot_cnt == 0)
          fputs (" ***final element***", stdout);
#endif /* DEBUG2 */
      }
#ifdef DEBUG2
fputc ('\n', stdout);
#endif /* DEBUG2 */
    }
    else
    {
#ifdef DEBUG2
printf ("irdb0014: get slot_cnt=%d slot='%s'\n", slot_cnt, slot);
#endif /* DEBUG2 */
      yt= ytree_lookup_word ((struct YTREE *) hnd->IRDB_payload,
                             (unsigned char *) slot);
    }

    if (yt == (struct YTREE *) 0 || !(yt->YT_flags & YTflag_EOW))
      return (long *) 0;

    if (slot_cnt == 0)
    {
      if (hnd->IRDB_payload_type == IRDBty_string_dumped)
      {
        int rc;

        rc= irdb_restore (pos, hnd);
printf ("irdb0014: restore payload, ty=%s rc=%d\n",
irdb_type (hnd->IRDB_payload_type), rc);
      }

      if (hnd->IRDB_payload_type != ty)
      {
#ifdef DEBUG0
printf ("*** type mismatch, IRDB_payload_type=%s ty=%s\n",
irdb_type (hnd->IRDB_payload_type), irdb_type (ty));
#endif /* DEBUG2 */
        return (long *) 0;
      }
      break;
    }

    /* descend the structure, if it's indeed a structure */
    if (hnd->IRDB_payload_type == IRDBty_struct_dumped)
    {
      int rc;

      rc= irdb_restore (pos, hnd);
printf ("irdb0014: restore payload, rc=%d\n", rc);
    }

    if (hnd->IRDB_payload_type != IRDBty_struct)
    {
#ifdef DEBUG0
printf ("*** not a structure, IRDB_payload_type=%s ty=%s\n",
irdb_type (hnd->IRDB_payload_type), irdb_type (ty));
#endif /* DEBUG2 */
      return (long *) 0;
    }
    hnd= (struct IRDB_HANDLE *) yt->YT_info;
  }

  return &yt->YT_info;
}
