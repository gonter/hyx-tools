/*
 *  FILE /usr/window/cga/win_0045.C
 *
 *  1991 12 07
 *
 */

#pragma check_stack(off)

#include <dos.h>

extern int W_TEXT_MAX_Y;
extern int W_TEXT_CELL_Y;

/* ------------------------------------------------------------------------ */
int vga_set_screen_mode (int mode)
{
  union REGS ra, rb;
  int max_y=24;

#ifdef W_MODEL_CGA
  char *cp;

  /* Žnderung der Zeilenzahl erm”glichen */
  ra.h.ah=0x11;
  ra.h.bl=0;
  switch (mode)
  {
    case  1: ra.h.al=0x14; break;
    case  2: ra.h.al=0x11; break;
    case  3: ra.h.al=0x15; break;
    case  4: ra.h.al=0x12; break;
    case  5: ra.h.al=0x13; break;
    case  6: ra.h.al=0x16; break;
    case  7: ra.h.al=0x17; break;
    case  8: ra.h.al=0x18; break;
    case  9: ra.h.al=0x19; break;
    default: return;
  }
  int86 (0x10, &ra, &rb);  

  set_cp (&cp, 0, 0x0040);
  max_y = cp [0x84] & 0x00FF;
  if (max_y<19 || max_y >60) max_y=24;
#endif

/* set_line_mode (max_y); ... ehedem */
  W_TEXT_MAX_Y = max_y + 1;

  ra.x.ax=8;            /* Maus auf neuen Textbereich einstellen */
  ra.x.cx=0;
  ra.x.dx=max_y*W_TEXT_CELL_Y;
  int86 (0x33, &ra, &rb);

  return max_y;
}
