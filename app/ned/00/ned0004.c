/*
 *  FILE %ned/00/ned0004.c
 *
 *  Datenstrukturen fuer EDITOR NED
 *
 *  written:       1987 09 09
 *  latest update: 1996-05-16 19:08:49
 *
 */

#include "ed.h"

/* ------------------------------------------------------------------------ */
/* list of currently active windoww                                         */
struct WINDOWCTRL *windows= (struct WINDOWCTRL *) 0;

/* current working window                                                   */
struct WINDOWCTRL *aw= (struct WINDOWCTRL *) 0;

/* list of currently active files                                           */
struct FILECTRL *files= (struct FILECTRL *) 0;

/* number of the displayed screen                                           */
int akt_page= 0;
