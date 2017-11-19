/*
 *  FILE %ned/06/ned0622.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1987 04 08
 *                 1991 06 01: Revision
 *  latest update: 1998-08-16 12:58:31
 *  $Id: ned0622.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include <gg/window.h>
#include "proto.h"

#ifdef UX2_DEBUG
#include <stdio.h>
#endif

extern int COL_ASK;
extern int mess_ttl;
extern int mess_lin;

/* ------------------------------------------------------------------------ */
int ned_message_1 (const char *p1)
{
  w_setstring (0, 0, mess_lin, 79, mess_lin, COL_ASK, p1, 0x03);
  mess_ttl= 6;
  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_message_2 (const char *p1, const char *p2)
{
  const char *s[2];
  s [0]= p1;
  s [1]= p2;

  return ned_message_X (2, s);
}

/* ------------------------------------------------------------------------ */
int ned_message_3 (const char *p1, const char *p2, const char *p3)
{
  const char *s[3];
  s [0]= p1;
  s [1]= p2;
  s [2]= p3;

  return ned_message_X (3, s);
}

/* ------------------------------------------------------------------------ */
int ned_message_4 (const char *p1, const char *p2, const char *p3,
const char *p4)
{
  const char *s[4];
  s [0]= p1;
  s [1]= p2;
  s [2]= p3;
  s [3]= p4;

  return ned_message_X (4, s);
}

/* ------------------------------------------------------------------------ */
int ned_message_X (int cnt, const char *s[])
{
  int i;
  int j= 0;

#ifdef UX_DEBUG
  int do_p= 1;
  if (p1[0] == '<') do_p= 0;
#endif

  if (cnt <= 0) return 0;

  for (i= 0; i+1 < cnt; i++)
  {
    w_setstring (0, j, mess_lin, 79, mess_lin, COL_ASK, s [i], 0x00);
#ifdef UX_DEBUG
    if (do_p) printf ("%s ", s [i]);
#endif
    j += strlen (s [i]);
  }

  w_setstring (0, j, mess_lin, 79, mess_lin, COL_ASK, s [i], 0x03);

#ifdef UX_DEBUG
  if (do_p) printf ("%s\n", s [i]);
#endif

  mess_ttl= 6;

  return 0;
}
