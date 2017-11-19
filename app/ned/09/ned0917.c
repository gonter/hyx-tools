/*
 *  FILE ~/usr/ned/09/ned0917.c
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
 *                 1991 06 01: Revision
 *  latest update: 1997-10-26 10:48:16
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

extern FILE *jou;
extern int jou_flag;
extern ned_input_handler *nextchar;

/* ------------------------------------------------------------------------ */
void p_close_jou ()
{
  if (jou_flag == 1 || jou_flag == 2) fclose (jou);
  jou_flag= 0;
  nextchar= q_kbin;
}
