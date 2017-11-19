/*
 *  FILE %ned/00/ned0007.c
 *
 *  Default Farben
 *
 *  written:       1991 05 26
 *  latest update: 1996-09-29  9:39:54
 *  $Id: ned0007.c,v 1.2 2005/06/14 02:36:06 gonter Exp $
 *
 */

#include "ed.h"
#include <gg/window.h>

/* Attribute fuer Windows: ------------------------------------------------ */
int COL_TEXT          = WV_HGRUEN;
int COL_BOX           = WV_GELB;
int COL_BLOCK         = WH_ROT|WV_GELB|W_HELL;
int COL_FEATURE       = WV_WEISS|W_HELL;
int COL_MARKUP        = WV_GRUEN|WH_WEISS;

/* globale Attribute: ----------------------------------------------------- */
int COL_SCROLL        = WV_GELB;
int COL_CONFIRM       = WV_VIOLETT|W_HELL;
int COL_ERROR         = WV_VIOLETT|W_HELL;
int COL_WIN_NUM       = WH_ROT|WV_KOBALT|W_HELL;
int COL_STATUS        = WV_HKOBALT|WH_BRAUN;
int COL_ASK           = WV_VIOLETT|W_HELL;

/* hypertext attributes: -------------------------------------------------- */
int COL_UNKNOWN_FEATURE= WV_BLAU|WH_WEISS;
int COL_FRAME_TAGS= WV_GELB|WH_BRAUN;

#ifdef MSDOS
#define _DEF_UNKNOWN_FEATURE 0x0F
#else
#define _DEF_UNKNOWN_FEATURE '?'
#endif
int CHR_UNKNOWN_FEATURE= _DEF_UNKNOWN_FEATURE;
int CHR_FILLER= 0x20;           /* used to fill up space at end of line     */
int CHR_TAB_FILLER= 0x1A;
int DISPLAY_TABS= 1;            /* -> show tabs as a series of blanks       */
