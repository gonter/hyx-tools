/*
 *  FILE ~/usr/gophtool/msrv04.c
 *
 *  written:       1994-06-20
 *  latest update: 1999-04-25 16:39:50
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include "msrvh.h"

/* ------------------------------------------------------------------------ */
char *msrv_pick_reply_address (
char *from,
char *reply_to)
{
  if (reply_to != (char *) 0 && *reply_to != 0) return reply_to;
  return from;
}
