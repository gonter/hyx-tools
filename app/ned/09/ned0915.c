/*
 *  FILE %ned/09/ned0915.c
 *
 *  Operationen mit dem SETUP-File
 *  o  Installation von Tastenkommandos
 *  o  Installation von Makros
 *  o  Installation von Maus Menu Eintraegen
 *  Makroprozessor
 *  Jour File Prozessor
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *                 1991 02 07: Revision
 *  latest update: 1997-10-26 11:14:23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "message.h"
#include "proto.h"

extern FILE *jou;
extern char jou_name [];
extern int jou_flag;
extern ned_input_handler *nextchar;

/* ------------------------------------------------------------------------ */
int p_open_jou_rd ()    /* Open Jour File for Read (Recover) */
{
  p_close_jou ();

  if ((jou= fopen (jou_name, "rb")) == (FILE *) 0) return -1;

  jou_flag= 2;
  nextchar= jou_in;

  return 0;
}
