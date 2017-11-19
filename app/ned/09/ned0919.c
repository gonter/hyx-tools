/*
 *  FILE %ned/09/ned0919.c
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
 *  latest update: 1997-02-11 23:56:45
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edctx.h"
#include "proto.h"

extern int MPflag;
extern ned_input_handler *nextchar;  /* Editor Eingabe: KBD | FILE ..       */
extern ned_input_handler *nxtchs;    /* Zwischenspeicher fuer (*nextchar)   */

extern struct NED_CONTEXT *ned_main_context;

/* ------------------------------------------------------------------------ */
void p_macro (int num)
{
  if (   num <  0                       /* macro number ...                 */
      || num >= N_MACRO                 /* ... valid number?                */
      || ned_main_context == (struct NED_CONTEXT *) 0
     )
    return;

  ned_q_macro (ned_main_context->NED_macro_table [num]);
}

/* ------------------------------------------------------------------------ */
void ned_q_macro (struct NED_MACRO *mp)
{
  char *mac_txt;

  if (mp == (struct NED_MACRO *) 0
      || MPflag                         /* macro already active?            */
      || (mac_txt= mp->NED_mac_contents) == (char *) 0
      || *mac_txt == 0
     ) return;

  switch (mp->NED_mac_type)
  {
    case MPt_key_sequence:
      nxtchs=      nextchar;            /* previous character function      */
      nextchar=  mac_expand;            /* macro expander                   */
      MPflag=             1;            /* ... mark as active               */
      ned_main_context->NED_macro_pointer= mac_txt;
      break;

    case MPt_tcl:
      mac_call_tcl (mac_txt);           /* hand string over to tcl interp.  */
      break;

    case MPt_tag:
      ex_tag_command (mac_txt);
      break;

    case MPt_feature:
      ned_eval_string (mac_txt, 0);
      break;

    case MPt_undefined:
    default:
      break;
  }

}
