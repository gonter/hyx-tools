/*
 *  FILE %ned/01/ned0115.c
 *
 *  Aktivierung von Sub-Kommando Prozessoren
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1997-02-20 12:41:30
 *  $Id: ned0115.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>
#ifdef USE_MOUSE
#include <gg/maus.h>
#else
extern ned_input_handler *nextchar;  /* Editor Eingabe: KBD | FILE ..       */
#endif

extern int key;
extern int akt_page;
extern int COL_STATUS;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_ctrlp ()
{
  char key_str [5];

  key_str [0]= '^';
  key_str [1]= 'P';
  key_str [2]= 0;

  w_setstring (akt_page, aw->ax+4, aw->ay-1, aw->ax+7, aw->ay-1,
               COL_STATUS, key_str, 0x01);

#ifdef USE_MOUSE
  key= ned_check_mouse ();
#else
  key= (*nextchar) ();
#endif

  ned_insert_special_char (key);
}
