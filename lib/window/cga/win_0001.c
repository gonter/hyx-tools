/*
 *  FILE ~/usr/window/cga/win_0001.c
 *
 *  written:       1989 08 17: aus WIN0BIOS.ARC Åbernommen
 *  latest update: 1994-08-20
 *
 */

#pragma check_stack(off)

/* #define ET4000 */
/* #define T8900  */

#include <gg/window.h>
#include <dos.h>

#ifdef W_MODEL_CGA
/* 14 standard video modes */
#ifdef T8900
#define KNOWN_MODES 29
#endif
#ifdef ET4000
#define KNOWN_MODES 17
#endif
#ifndef KNOWN_MODES
#define KNOWN_MODES 14
#endif
static char VVVxxx [] = "(@)BWindow CGA #D$1991-05-13 01:15:00";
#endif

#ifdef W_MODEL_BIOS
#ifdef T8900
# define KNOWN_MODES 28
#endif
#ifdef ET4000
# define KNOWN_MODES 16
#endif
#ifndef KNOWN_MODES
#define KNOWN_MODES 13
#endif
static char VVVxxx [] = "(@)BWindow BIOS #D$1991-05-13 01:15:00";
#endif

extern struct W_SCREEN_AND_MODES    w_screen_and_modes;

extern int W_DATA_initialized,
           W_TEXT_MAX_X,
           W_TEXT_MAX_Y,
           W_TEXT_CELL_X,
           W_TEXT_CELL_Y,
           W_GRAPH_MAX_X,
           W_GRAPH_MAX_Y;

extern int W_AKT_MODE;

/* ------------------------------------------------------------------------ */
static struct W_SCREEN_CAPABILITIES w_screen_capabilities =
{
  "CGA", W_MODEL_CODE_CGA, KNOWN_MODES, 3
} ;

static struct W_MODE_CAPABILITIES   w_mode_capabilities [KNOWN_MODES] =
{
/* standard modes: --- */
{ /* 40x25 B/W Text    */ 0x00,  40,  25,   2, 16,  8, 8,  -1,  -1,  -1, -1 },
{ /* 40x25 COL Text    */ 0x01,  40,  25, 256, 16,  8, 8,  -1,  -1,  -1, -1 },
{ /* 80x25 B/W Text    */ 0x02,  80,  25,   2,  8,  8, 4,  -1,  -1,  -1, -1 },
{ /* 80x25 COL Text    */ 0x03,  80,  25, 256,  8,  8, 4,  -1,  -1,  -1, -1 },
{ /* 320x200x2 Graph   */ 0x04,  40,  25,   2,  8,  8, 1, 320, 200,   2,  1 },
{ /* 320x200x4 Graph   */ 0x05,  40,  25,   4,  8,  8, 1, 320, 200,   4,  1 },
{ /* 640x200x2 Graph   */ 0x06,  80,  25,   2,  8,  8, 1, 640, 200,   2,  1 },
{ /* 80x25 B/W Alpha   */ 0x07,  80,  25,   2,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 320x200x16 Graph  */ 0x0D,  80,  25,  16,  8,  8, 1, 320, 200,  16,  1 },
{ /* 640x200x16 Graph  */ 0x0E,  80,  25,  16,  8,  8, 1, 640, 200,  16,  1 },
{ /* 640x350x16 Graph  */ 0x10,  80,  25,  16,  8, 14, 1, 640, 350,  16,  1 },
#ifdef W_MODEL_CGA
{ /* 640x480x2 Graph   */ 0x11,  80,  25,   2,  8, 16, 1, 640, 480,   2,  1 },
#endif
{ /* 640x480x16 Graph  */ 0x12,  80,  25,  16,  8, 16, 1, 640, 480,  16,  1 },
{ /* 320x200x256 Graph */ 0x13,  40,  25, 256,  8,  8, 1, 320, 200, 256,  1 }

#ifdef T8900
/* extended modes: for Trident 8900 --- */
,
{ /* 80x30 COL Text    */ 0x50,  80,  30, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 80x43 COL Text    */ 0x51,  80,  43, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 80x60 COL Text    */ 0x52,  80,  60, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 132x25 COL Text   */ 0x53, 132,  25, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 132x30 COL Text   */ 0x54, 132,  30, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 132x43 COL Text   */ 0x55, 132,  43, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 132x60 COL Text   */ 0x56, 132,  60, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 132x25b COL Text  */ 0x57, 132,  25, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 132x30b COL Text  */ 0x58, 132,  30, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 132x43b COL Text  */ 0x59, 132,  43, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 132x60b COL Text  */ 0x5A, 132,  60, 256,  8,  8, 1,  -1,  -1,  -1, -1 },
{ /* 800x600x16 Graph  */ 0x5B, 100,  75, 256,  8,  8, 1, 800, 600,  16,  1 },
{ /* 640x400x256 Graph */ 0x5C,  80,  25, 256,  8,  8, 1, 640, 400, 256,  1 },
{ /* 640x480x256 Graph */ 0x5D,  80,  30, 256,  8,  8, 1, 640, 480, 256,  1 },
{ /* 1024x768x16 Graph */ 0x5F, 128,  48, 256,  8,  8, 1,1024, 768,  16,  1 }
#endif

#ifdef ET4000
/* extended modes: for ET 4000 --- */
,
{ /* 640x400x256 Graph */ 0x2F,  80,  25, 256,  8,  8, 1, 640, 400, 256,  1 },
{ /* 640x480x256 Graph */ 0x2E,  80,  30, 256,  8,  8, 1, 640, 480, 256,  1 },
{ /* 1024x768x16 Graph */ 0x38, 128,  48, 256,  8,  8, 1,1024, 768,  16,  1 }
#endif
} ;

/* Model abhÑngige Daten: ------------------------------------------------- */
#ifdef W_MODEL_CGA
int W_TEXT_AKT_MEM = 0xB800;    /* aktuelle Position der Textseite      */
                                /* im Bilsspeicher                      */
int W_TEXT_AKT_MULT = 160;      /* Zahl der Byte je Bildschirmzeile     */
#endif

/* ------------------------------------------------------------------------ */
static void cdecl _init_data (void);

static void _init_data ()
{
  w_screen_and_modes.w_screen_capabilities = &w_screen_capabilities;
  w_screen_and_modes.w_mode_capabilities   =  w_mode_capabilities;
  W_DATA_initialized = 1;
}

/* ------------------------------------------------------------------------ */
void w_init (int flags)         /* Bit 0: Mode Initialisieren lassen        */
                                /* Bit 1: Zeilen/Spalten *NICHT* ermitteln  */
{
  _init_data ();

  if (flags & 0x0001)
       w_init_mode (w_screen_capabilities.w_mode_default, flags);
  else w_init_mode (W_AKT_MODE=w_get_mode(), flags);
}

/* ------------------------------------------------------------------------ */
int w_init_mode (int num, int flags)
/* flags: bit 0: initialize the controller (by calling bios) */
/*        bit 1: don't get maximum screen coordinates */
/*        bit 3: mode num is a bios mode number */
{
  union REGS rega, regb;
  register struct W_MODE_CAPABILITIES *wmc;

  if (! W_DATA_initialized) _init_data ();

  if (flags & 0x0004)
  {
    int i;
    for (i=0; i < w_screen_capabilities.w_mode_count; i++)
      if (w_mode_capabilities [i].w_mode_code == num) break;
    num=i;
  }
  if (num < 0 || num >= w_screen_capabilities.w_mode_count) return -1;

  wmc = &w_mode_capabilities [num];

#ifdef NOT_IMPLEMENTED
  if (wmc->w_mode_code == -1)
  {
    /* Sonder Modus: z.Z. nicht handhabbar #### */
    return -1;
  }
#endif

  W_AKT_MODE=num;
/******************************************
  if (num >= 0x50) W_TEXT_AKT_MEM = 0xA000;
******************************************/

  W_GRAPH_MAX_Y = wmc->w_graph_max_y;
  W_GRAPH_MAX_X = wmc->w_graph_max_x;
  W_TEXT_CELL_X = wmc->w_text_cell_x;
  W_TEXT_CELL_Y = wmc->w_text_cell_y;
  W_TEXT_MAX_Y  = wmc->w_text_max_y;
  W_TEXT_MAX_X  = wmc->w_text_max_x;

#ifdef W_MODEL_CGA
  switch (wmc->w_text_max_x)
  {
    case  40: W_TEXT_AKT_MULT =  80; W_TEXT_AKT_MEM = 0xB800; break;
    case  80: W_TEXT_AKT_MULT = 160; W_TEXT_AKT_MEM = 0xB800; break;
    case 132: W_TEXT_AKT_MULT = 264; W_TEXT_AKT_MEM = 0xBC00; break;
  }
#endif

  if (flags & 0x0001) w_set_mode (wmc->w_mode_code);
  if (!(flags & 0x0002)) w_get_screen_max();

  return 0;
}

/* ------------------------------------------------------------------------ */
int w_get_mode ()
{
  register int am,i;

  am= _cga_get_mode ();
  for (i= 0; i<KNOWN_MODES; i++)
    if (am == w_mode_capabilities [i].w_mode_code) return i;

  return -1;
}
