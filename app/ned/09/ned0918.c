/*
 *  FILE %ned/09/ned0918.c
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
 *  latest update: 1997-10-26 10:59:52
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edctx.h"
#include "proto.h"

extern int MPflag;
extern ned_input_handler *nxtchs, *nextchar;

extern struct NED_CONTEXT *ned_main_context;

/* Bedienprozeduren fuer Makroprozessor: ---------------------------------- */
int mac_expand ()
{
  int k= 0;
  char *mp;

  if (ned_main_context == (struct NED_CONTEXT *) 0
      || (mp= ned_main_context->NED_macro_pointer) == (char *) 0
      || (k= *mp++ & 0x00FF) == 0
      || *mp == 0
     )
  {
    nextchar= nxtchs;
    MPflag= 0;
  }
  else
  {
    ned_main_context->NED_macro_pointer++;
  }

  return k;
}
