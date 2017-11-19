/*
 *  FILE %ned/11/ned1112w.c
 *
 *  Text search and replace functions
 *  see: C API documentation
 *
 *  written:       1997-01-06
 *  latest update: 1997-01-08 21:39:20
 *  $Id: ned1112w.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <gg/strings.h>
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"
#include <gg/window.h>
#ifdef USE_MOUSE
#include <gg/maus.h>
#else
extern ned_input_handler *nextchar;
#endif

extern struct WINDOWCTRL *aw;
extern int key;

/* ------------------------------------------------------------------------ */
void ned_ws_aw_find_str ()
{
  int first_key;
  char key_str [2];

  switch (key)
  {
    case 0x07: case 'G': case 'g':
      first_key= 'f';
      break;
    case 0x08: case 'H': case 'h':
      first_key= 'F';
      break;
    default:
      return;
  }

#ifdef USE_MOUSE
  key= ned_check_mouse ();
#else
  key= (*nextchar) ();
#endif

  key_str [0]= (char) key;
  key_str [1]= 0;

  if (ned_vi_wc_find_str (aw, key_str, 1, first_key) == -1) vi_bell ();
}
