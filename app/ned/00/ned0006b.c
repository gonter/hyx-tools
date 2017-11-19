/*
 *  FILE %ned/00/ned0006b.c
 *
 *  global ds: input handler
 *
 *  written:       1997-08-03 [extracted frm ned0006.c]
 *  latest update: 1997-08-03 21:56:59
 *  $Id: ned0006b.c,v 1.3 2005/09/04 19:03:16 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/filename.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
ned_input_handler *nextchar=    /* Editor Eingabe: KBD | FILE ..            */
#ifdef EXPER
                    kbin;
#else
                    q_kbin;
#endif

ned_input_handler *nxtchs;      /* Zwischenspeicher fuer (*nextchar)        */
