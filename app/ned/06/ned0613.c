/*
 *  FILE %ned/06/ned0613.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1987 04 08
 *                 1991 05 23: Revision
 *  latest update: 1996-11-03 15:30:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"

extern int COL_ASK;
extern int mess_lin;
extern int mess_ttl;

/* ------------------------------------------------------------------------ */
int rd_str (char *msg, char *str, int str_lng)  /* lese einen String        */
/* RETURN: -1 ... Editieren abgebrochen                                     */
/*          0 ... alles OK                                                  */
{
  int last_key;

  mess_ttl= 3;

  return ned_rd_str2 (msg, str, str_lng, mess_lin, COL_ASK, &last_key);
}
