/*
 *  FILE %win/0/win_data.c
 *
 *  globale Daten fuer das Window System
 *
 *  written:       1989 08 17
 *  latest update: 1996-05-27  8:55:20
 *
 */

#include <dos.h>
#include <gg/window.h>

/* ------------------------------------------------------------------------ */
extern struct W_SCREEN_AND_MODES    w_screen_and_modes =
{
  (void *) 0,
  (void *) 0
} ;

/* ------------------------------------------------------------------------ */
#define extern
extern int W_DATA_initialized   =  0;
extern int W_TEXT_MAX_X         = -1;
extern int W_TEXT_MAX_Y         = -1;
extern int W_TEXT_CELL_X        = -1;
extern int W_TEXT_CELL_Y        = -1;
extern int W_GRAPH_MAX_X        = -1;
extern int W_GRAPH_MAX_Y        = -1;
extern int W_AKT_MODE           = -1;
