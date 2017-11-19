/*
 *  FILE %ned/06/ned0624.c
 *
 *  written:       1991 07 01
 *  latest update: 1997-01-12 17:31:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern int akt_page;

int mess_ttl= 0;
int mess_lin= 1;

static char blit_mess [160];

/* ------------------------------------------------------------------------ */
void save_message_line (void)
{
  w_blit_save (blit_mess, akt_page, 0, mess_lin, 79, mess_lin);
}

/* ------------------------------------------------------------------------ */
void restore_message_line (void)
{
  w_blit_load (blit_mess, akt_page, 0, mess_lin, 79, mess_lin);
}
