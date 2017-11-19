/*
 *  FILE %win/1/win_0125.c
 *
 *  written:       1995-10-01
 *  latest update: 1995-10-20
 *
 */

#include <stdio.h>
#include <gg/window.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

#define SIMPLE_BELL
#ifdef W_MODEL_TK
#undef SIMPLE_BELL
#endif

/* ------------------------------------------------------------------------ */
#ifdef SIMPLE_BELL
void w_bell ()
{
  putchar (0x07);
}
#endif
