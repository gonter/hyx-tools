/*
 *  FILE %ned/03/ned0332b.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1996-11-03
 *  latest update: 1996-11-03 16:48:33
 *  $Id: ned0332b.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int qq_insert_string_array (
struct LINE *lp,
int insert_idx,                 /* Einfuegeposition innerhalb der Zeile     */
const char *ftxt[],
int t_cnt,
int insert_flag)                /* 0 -> overwrite mode; 1 -> insert mode;   */
{
  int fc;                       /* insert pointer within feature text line  */
  int fl;                       /* length of feature text line              */
  int i;

  fc= insert_idx;
  for (i= 0; i < t_cnt; i++)
    if (ftxt [i] != (char *) 0)
    {
      fl= strlen (ftxt [i]);
      qq_insert_string (lp, fc, ftxt [i], fl, insert_flag);
      fc += fl;
    }

  return 0;
}
