/*
 *  FILE %ds/irdb/irdb0025.c
 *
 *  irrelational database
 *
 *  written:       1996-04-28
 *  latest update: 1996-05-06  0:28:50
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_restore (
struct IRDB_POS *pos,
struct IRDB_HANDLE *hnd)
{
  FILE *fi;
  long KBI [1];
  char *KBS [1];
  struct YTREE *yt= (struct YTREE *) 0;
  int rc;
  long pp;
  char *cp;

  if ((fi= irdb_get_pos_file_pointer (pos, IRDBom_read)) == (FILE *) 0
      || (pp= hnd->IRDB_payload) == 0L
     )
    return -1;

  fseek (fi, pp, 0);
  switch ((int) hnd->IRDB_type)
  {
    case IRDBty_struct_dumped:
printf ("irdb0025: restoring dumped struct: pp=0x%08lX\n", pp);

      rc= ytree_full_scan (fi, &yt, KBI, 0, KBS, 0);
      if (rc == 0 && yt != (struct YTREE *) 0)
      {
        hnd->IRDB_payload= (long) yt;
        hnd->IRDB_type= (long) IRDBty_struct;
/* T2D: ev. an dieser Stelle die Payload zurueckladen??? */
      }
      break;

    case IRDBty_struct:
      yt= (struct YTREE *) hnd->IRDB_payload;

      switch ((int) hnd->IRDB_payload_type)
      {
        case IRDBty_string_dumped:
          ytree_process (yt, irdb_restore_strings, (void *) fi);
          hnd->IRDB_payload_type= IRDBty_string;
          break;

        case IRDBty_struct_dumped:
          ytree_process (yt, irdb_restore_handle, (void *) fi);
          hnd->IRDB_payload_type= IRDBty_struct;
          break;
      }
      break;

    case IRDBty_string_dumped:
printf ("irdb0025: restoring dumped string: pp=0x%08lX\n", pp);
      if ((cp= irdb_load_string (fi, (char *) 0, 0)) != (char *) 0)
      {
        hnd->IRDB_payload= (long) cp;
        hnd->IRDB_type= (long) IRDBty_string;
      }
      break;

    default:
      printf ("irdb0025: error, can't restore type %ld, (%s)\n",
              hnd->IRDB_type, irdb_type (hnd->IRDB_type));
      return -1;
  }

  return 0;
}
