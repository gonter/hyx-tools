/*
 *  FILE %ned/01/ned0115b.c
 *
 *  insert a special character into the text
 *
 *  written:       1997-01-05
 *  latest update: 1998-08-16 12:39:24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_insert_special_char (int ins_code)
{
  char code [10];

  switch (ins_code)
  {
    case '0':
      ins_code= 0x00;
      break;

    case 'e':
      ins_code= 0x1B;
      break;

    case 'p':   /* ^P */
      ins_code= 0x10;
      break;
  }

  sprintf (code, "0x%04X", ins_code);
  ned_message_2 ("ins_code: ", code);

  if (ins_code >= 0x00 && ins_code <= 0xFF) q_insert (ins_code, 1);
}
