/*
 *  FILE %usr/lexicon/dictadd9.c
 *
 *  int dict_combine_entries ()
 *
 *  written:       1991 04 12
 *                 1995-07-16
 *  latest update: 2001-02-18 19:22:08
 *  $Id: dictadd9.c,v 1.2 2001/02/19 00:27:18 gonter Exp $
 *
 */


#include <stdio.h>
#include <gg/parse.h>
#include <gg/sgml.h>

/* ------------------------------------------------------------------------ */
#define purge_cnt_old 4
static long purge_list_old [purge_cnt_old] =
{
  SGML_TAG_frame, SGML_TAG_endframe,
  SGML_TAG_ned_sgml, SGML_TAG_hyx_stamp
} ;

static int purge_flags_old [purge_cnt_old] = { 0, 0, 0, 0 } ;

/* ------------------------------------------------------------------------ */
#define purge_cnt_new 6
static long purge_list_new [purge_cnt_new] =
{
  SGML_TAG_frame, SGML_TAG_endframe,
  SGML_TAG_ned_sgml, SGML_TAG_hyx_stamp,
  LEX_sTAG_LE, LEX_eTAG_LE
} ;

static int purge_flags_new [purge_cnt_new]= { 0, 0, 0, 0, 1, 0 } ;

/* ------------------------------------------------------------------------ */
int dict_combine_entries (
struct TEXT_ELEMENT **tx_old,
struct TEXT_ELEMENT **tx_new)
{
  struct TEXT_ELEMENT **tx;

  if (tx_new == (struct TEXT_ELEMENT **) 0
      || tx_old == (struct TEXT_ELEMENT **) 0
     ) return -1;

  dict_purge_entry (tx_old, purge_list_old, purge_flags_old, purge_cnt_old);
  dict_purge_entry (tx_new, purge_list_new, purge_flags_new, purge_cnt_new);

  /* look for the end of the old entry */
  for (tx= tx_old; *tx != (struct TEXT_ELEMENT *) 0; tx= &(*tx)->TE_next);

  /* append new list to old list */
  *tx= *tx_new;

  /* note: tx_new is now more or less invalid (or not so??) */
  *tx_new= (struct TEXT_ELEMENT *) 0;

  return 0;
}
