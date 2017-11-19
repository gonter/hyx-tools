/*
 *  FILE %ned/09/ned0979.c
 *
 *  universal macro binding
 *  currently not really used ...
 *
 *  written:       1994-08-21
 *  latest update: 1999-04-25 16:36:21
 *  $Id: ned0979.c,v 1.3 2001/04/01 22:45:04 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/dpp.h>
#include <gg/ytree.h>
#include "ed.h"
#include "proto.h"

extern int ptbl_offset;

static struct YTREE *mb_table= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
void p_mac ()
{
  int num= -1;
  unsigned char tbl_off [6];

  long_to_hex ((long) ptbl_offset, (char *) tbl_off);
/************************ T2D */
  {
    char xline [80];
    sprintf (xline, "[ptbl_offset=0x%s]", tbl_off);
    ned_message_1 (xline);
  }
/*****************************/

  if ((num= (int) ytree_get_value (mb_table, tbl_off)) != 0)
    p_macro (num);
}

/* ------------------------------------------------------------------------ */
int mac_bind (int n_ptbl_offset, int num)
{
  unsigned char tbl_off [6];

  long_to_hex ((long) n_ptbl_offset, (char *) tbl_off);
  ytree_set_value (&mb_table, tbl_off, (long) num);
  return 0;
}

/* ------------------------------------------------------------------------ */
int mac_unbind (int n_ptbl_offset)
{
  unsigned char tbl_off [6];

  long_to_hex ((long) n_ptbl_offset, (char *) tbl_off);

  if (n_ptbl_offset == -1) /* delete all bindings! */
  {
    ytree_free (mb_table);
    mb_table= (struct YTREE *) 0;
  }
  else
    ytree_delete_word (&mb_table, tbl_off);

  return 0;
}
