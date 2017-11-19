/*
 *  FILE %ned/09/ned0916.c
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
 *  latest update: 1997-10-26 11:15:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

extern FILE *jou;
extern char jou_name [];
extern int jou_flag;
extern ned_input_handler *nextchar;

/* ------------------------------------------------------------------------ */
void p_open_jou_wr ()         /* Open Jour File for Write (Backup) */
{
  p_close_jou ();

  jou= fopen (jou_name, "wb");

  jou_flag= 1;
  nextchar= kbin_jou;
}
