/*
 *  FILE %ned/06/ned0631.c
 *
 *  prompt a string
 *
 *  written:       1996-07-07: [extracted from ned0613.c]
 *  latest update: 1998-08-15 11:33:44
 *  $Id: ned0631.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"

#ifndef USE_TK
extern int COL_ASK;
extern int mess_lin;
extern int mess_ttl;
#endif /* !USE_TK */

/* ------------------------------------------------------------------------ */
int ned_prompt_string (
const char *msg,
char *str,
int str_lng,
const char *help_cluster,
const char *help_frame,
NED_field_editor_callback *cb,
void *client_data)
/* RETURN: -1 ... Editieren abgebrochen                                     */
/*          0 ... alles OK                                                  */
{
#ifdef USE_TK
  ned_tk_prompt_string (msg, str, help_cluster, help_frame, cb, client_data);
#else
  int rc;
  int last_key;

  mess_ttl= 3;

RETRY:
  rc= ned_rd_str2 (msg, str, str_lng, mess_lin, COL_ASK, &last_key);
  if (rc == -1)
  {
    if (last_key == 0x18) /* CTRL-X or ALT-H */
    {
      ned_activate_special (help_cluster, help_frame, 0x00);
      goto RETRY;
    }
  }
  else
  {
    (*cb) (str, client_data);
  }
#endif /* !USE_TK */

  return 0;
}
