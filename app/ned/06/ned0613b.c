/*
 *  FILE %ned/06/ned0613b.c
 *
 *  prompt a string
 *
 *  written:       1996-07-07: [extracted from ned0613.c]
 *  latest update: 1997-06-17 10:56:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include <gg/window.h>
#include <gg/keys.h>
#include "proto.h"

extern int pfx;                 /* Kommand Key Praefix                      */
extern ned_input_handler *nextchar;  /* Editor Eingabe: KBD | FILE ..       */

/* ------------------------------------------------------------------------ */
int ned_rd_str2 (
const char *msg,
char *str,
int str_lng,
int msg_lin,
int col_ask,
int *last_key)
/* RETURN: -1 ... Editieren abgebrochen                                     */
/*          0 ... alles OK                                                  */
{
  int i;
  int m= 0;             /* length of string sofar                           */
  int k= 0;             /* key entered                                      */
  int modified= 0;      /* 1 -> buffer has been modified                    */
  int st;
  int spfx;

  if (str == (char *) 0 || (i= strlen (str)) >= str_lng) return -1;

  w_setstring (0, 0, msg_lin, 79, msg_lin, col_ask, msg, 0x01);
  st= strlen (msg);

  while (k != 0x0D)
  {
    w_setstring (0, st, msg_lin, 79, msg_lin, col_ask, str, 0x01);
    w_setcup (0, st+i, msg_lin);
    if (m < i) m= i;

    spfx= pfx;                  /* save and restore the command prefix code */
    pfx= 0;                     /* for editing modes like vi                */
    k= (*nextchar) ();
    if (pfx == P_FUNCT) k |= 0x0100;
    pfx= spfx;

    switch (k)
    {
      case 0x04:        /* Ctrl-D */
      case K_CRIGHT:
        if (i < m) i++;
        break;
      case 0x08:
      case 0x7F:
        if (!i) break;
        str [--i]= 0;
        m= i;
        modified= 1;
        break;
      case 0x07:
      case K_DEL:
        str [i]= 0;
        m= i;
        modified= 1;
        break;

      case 0x0A:
      case 0x0D:
        *last_key= k;
        k= 0x0D;
        break;

      case 0x13:        /* Ctrl-S */
      case K_CLEFT:
        if (i) i--;
        break;

      case 0x0123:      /* ALT-H:  request help         */
      case 0x18:        /* CTRL-X: request help         */
        *last_key= 0x18;
        return -1;

      case 0x1B:        /* ESC:    abort editing        */
      case 0x03:        /* CTRL-C: abort editing        */
        i= m= 0;
        str [0]= 0;
        *last_key= k;
        return -1;

      case 0x01:        /* Ctrl-A */
      case K_HOME:
        i= 0;
        break;
      case 0x06:        /* Ctrl-F */
      case K_END:
        i= m;
        break;

      case 0x19:        /* Ctrl-Y: clear line */
        i= m= 0;
        str [0]= 0;
        break;

      default:
        if (k < 0 || k > 0x00FF) break;
        if (i >= str_lng) break;
        str [i++]= (char) k;
        if (m < i) m= i;
        str [m]= 0;
        modified= 1;
        break;
    }
  }

  return modified;
}
