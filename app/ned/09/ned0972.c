/*
 *  FILE %ned/09/ned0972.c
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
 *                 1991 05 26: Revision
 *  latest update: 1997-10-26 10:46:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/dpp.h>
#include "ed.h"
#include "message.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_mac_define ()
{
  int mac_type= MPt_key_sequence;
#define NUM_TOKEN_SIZE 10
#define CMD_SIZE 84
  char num_token [NUM_TOKEN_SIZE];
  char token [CMD_SIZE];

  num_token [0]= 0;
  if (rd_str (QST_MAC_NUM, num_token, NUM_TOKEN_SIZE) == -1) return;

#ifdef USE_TCL
  /* TCL_MACROS: Prompt user if the macro should be defined as tcl string.  */
  /* see: NED tcl macros for more information about this stuff.             */

  token [0]= 0;  
  if (rd_str (QST_MAC_TYPE, token, CMD_SIZE) == -1) return;
  switch (token [0])
  {
    case 't': case 'T':
      mac_type=  MPt_tcl;
      break;
    default:
      mac_type= MPt_key_sequence;
      break;
  }
#endif /* USE_TCL */

  token [0]= 0;  
  if (rd_str (QST_MAC_TXT, token, CMD_SIZE) == -1) return;

  mac_definition (num_token, token, mac_type);

#ifdef __OLD__ /* 1996-11-03 18:03:51 */
  int mac_num;
  int mac_siz;
  mac_num= (int) get_parameter_value (num_token);
  mac_siz= trans_str (token, token, CMD_SIZE);
  mac_undef (mac_num);
  mac_define (mac_num, mac_type, token, mac_siz);
#endif
}
