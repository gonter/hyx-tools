/*
 *  FILE %ned/03/ned0332.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1991 01 29: aus NED0305.C extrahiert
 *  latest update: 1999-07-17 19:29:35
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int qq_insert_string (
struct LINE *lp,
int insert_idx,         /* Einfuegeposition innerhalb der Zeile             */
const char *str,
int str_lng,
int insert_flag)        /* 0 -> overwrite modus; 1 -> insert modus;         */
/* RETURN -1 ... error; 0 ... ok                                            */
{
/** printf ("0332: insert_string='%s' lng=%d lp=%08lX\n", str, str_lng, lp); **/
  while (str_lng-- > 0)
    if (qq_insert (lp, insert_idx++, (*str++) & 0x00FF, insert_flag) == -1)
      return -1;

  return 0;
}
