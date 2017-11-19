/*
 *  FILE ~/usr/window/utl/video.c
 *
 *  Einstellen der Hintergrund/Vordergrund/Border-Farben
 *
 *  written:       1988 02 05
 *  latest update: 1994-08-20
 *
 */

#include <string.h>
#include <stdio.h>
#include <dos.h>
/*******
#define W_MODEL_CGA
#include <gg/window.h>
*******/
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
#define TBL_size   19

#define DEF_V  0x0E
#define DEF_H  0x01
#define DEF_B  0x04
#define DEF_P  0x00

/* ------------------------------------------------------------------------ */
static struct
  { char *nm;
    int   value;
  } definitions [TBL_size] =
{ { "BLINK",      0x08 },  { "HELL",       0x08 },

  { "SCHWARZ",    0x00 },  { "BLAU",       0x01 },
  { "GRUEN",      0x02 },  { "KOBALT",     0x03 },
  { "ROT",        0x04 },  { "VIOLETT",    0x05 },
  { "BRAUN",      0x06 },  { "WEISS",      0x07 },

  { "HSCHWARZ",   0x08 },  { "HBLAU",      0x09 },
  { "HGRUEN",     0x0A },  { "HKOBALT",    0x0B },
  { "HROT",       0x0C },  { "HVIOLETT",   0x0D },
  { "HBRAUN",     0x0E },  { "HWEISS",     0x0F },

  { "GELB",       0x0E }
} ;

/* ------------------------------------------------------------------------ */
static int CLS = 0;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE:   video ([-Opt] (Farbe)* )*\n",
  "         Veraendern der Bildschirmattribute\n",
  "Options: -v     ... Vordergrundfarbe\n",
  "         -h     ... Hintergrundfarbe\n",
  "         -b     ... Umrandungsfarbe\n",
  "         -p <n> ... Umschalten auf Page <n>\n",
  "         -c     ... Clear Screen\n",
  "         -d     ... Default Farben\n",
  "         -m <n> ... Screen Mode\n",
  "         -f[m]  ... Farbpalette; x -> Hex d -> Dez; Def: Name\n",
  "\n",
  "(@)Avideo.c 1.2 #D$1992-01-15 10:30:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  union REGS ra, rb;
  int i, j, basis = 10, mode = 0,
      c_v = 0, c_h = 0, c_b = 0, page = 0;
  int fp = 0, fc = 0, fb = 0, fm=0, modus;

  for (i = 1; i < argc; i++)
      if (argv [i][0] == '-')
         switch (argv [i][1])
         { case 'v': case 'V': mode = 1; break;
           case 'h': case 'H': mode = 2; break;
           case 'b': case 'B': mode = 3; break;
           case 'p': case 'P': mode = 4; break;
           case 'm': case 'M': mode = 5; break;
           case 'd': case 'D': c_v  = DEF_V;
                               c_h  = DEF_H;
                               c_b  = DEF_B;
                               page = DEF_P;
                               fb = fp = fc = 1;
                               break;
           case 'c': case 'C': CLS = 1; break;
           case 'f': case 'F': help (page, argv [i][2]);
                               return;
#include <gg/help.inc>
         }
      else switch (mode)
           { case 1: c_v  |= indent (argv [i]);       fc = 1; break;
             case 2: c_h  |= indent (argv [i]);       fc = 1; break;
             case 3: c_b  |= indent (argv [i]);       fb = 1; break;
             case 4: sscanf (argv [i], "%d", &page); fp = 1; break;
             case 5: sscanf (argv [i], "%d", &modus);fm = 1; break;
           }

  if (fm) xx_w_mode (modus);
  if ((fc && (c_v != 0 || c_h != 0)) || CLS)
     if (CLS)         xx_w_cls80xx (page, c_v | (c_h << 4));
     else             xx_w_cls80   (page, c_v | (c_h << 4));
  if (fp)             w_selpage (page);
  if (fb && c_b != 0) w_border  (c_b);
}

/* ------------------------------------------------------------------------ */
help (page, x_mode)
int page,
    x_mode;   /* 1 -> Hexwerte ausgeben */
{
  int v, h, a = 0;
  char puf [14];

  xx_w_cls80xx (page, 0x1E);
  xx_w_prnt2col (page, 0, 1, 0x43, 25, "Zeilen:  Vordergrund");
  xx_w_prnt2col (page, 0, 2, 0x43, 25, "Spalten: Hintergrund");
  for (h = 0; h < 8; h++)
      xx_w_prnt2col (page, h*10, 4, (h) ? h : 1, 8,
                  definitions [h+2].nm);
  switch (x_mode)
  { default :
    case 'n': case 'N':
              for (v = 0; v < 16; v++)
                  for (h = 0; h < 8; h++)
                      xx_w_prnt2col (page, h*10, v+5, v | (h << 4), 8,
                                  definitions [v+2].nm);
              break;
    case 'x': case 'X':
              for (v = 0; v < 16; v++)
                  for (h = 0; h < 16; h++)
                      {
                        sprintf (puf, "0x%02X", h*16+v);
                        xx_w_prnt2col (page, h*5, v+5,
                                    v | (h << 4), 4, puf);
                      }
            break;
    case 'd': case 'D':
              for (v = 0; v < 16; v++)
                  for (h = 0; h < 16; h++)
                      {
                        sprintf (puf, "%3d", h*16+v);
                        xx_w_prnt2col (page, h*5+1, v+5,
                                    v | (h << 4), 4, puf);
                      }
            break;
  }
  xx_w_prnt2col (page, 0, 23, DEF_V | (DEF_H << 4), 25,
  "Default: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

/* ------------------------------------------------------------------------ */
indent (char *s)
{
  int i;

  for (i = 0; i < TBL_size; i++)
      if (strcmp (definitions [i].nm, to_upper (s)) == 0)
         return definitions [i].value;
  return 0;
}


/* ------------------------------------------------------------------------ */
xx_w_mode (m)
int m;
{ union REGS rega, regb;
  rega.h.ah = 0;
  rega.h.al = m;
  int86 (0x10, &rega, &regb);
}

/* ------------------------------------------------------------------------ */
xx_w_cls80 (page, col)
int page, col;
{ union REGS rega, regb;
  int x, y, sxy;
  rega.h.ah = 3;
  rega.h.bh = page;
  int86 (0x10, &rega, &regb);
  sxy = regb.x.dx;
  for (x = 0; x < 80; x++)
  for (y = 0; y < 25; y++)
  { rega.h.ah = 2;
    rega.h.bh = page;
    rega.h.dl = x;
    rega.h.dh = y;
    int86 (0x10, &rega, &regb);

    rega.h.ah = 8;
    rega.h.bh = page;
    int86 (0x10, &rega, &regb);

    rega.h.ah = 9;
    rega.h.bh = page;
    rega.x.cx = 1;
    rega.h.al = regb.h.al;
    rega.h.bl = col;
    int86 (0x10, &rega, &regb);
  }
  rega.h.ah = 2;
  rega.h.bh = page;
  rega.x.dx = sxy;
  int86 (0x10, &rega, &regb);
}

/* ------------------------------------------------------------------------ */
xx_w_cls80xx (page, col)
int page, col;
{
  union REGS rega, regb;
  rega.h.ah = 6;
  rega.h.al = 0;
  rega.h.ch = rega.h.cl = 0;
  rega.h.dh = 24;
  rega.h.dl = 79;
  rega.h.bh = col;
  int86 (0x10, &rega, &regb);
  rega.h.ah = 2;
  rega.h.bh = page;
  rega.x.dx = 0;
  int86 (0x10, &rega, &regb);
}

/* ------------------------------------------------------------------------ */
xx_w_prnt2col (p, x, y, a, m, s)
int p, x, y, a, m;
char *s;
{
  while (*s)
  {
    if (x > 79) break;
    w_setchar (p, x++, y, a, *s++); m--;
  }
  while (m)
  {
    if (x > 79) break;
    w_setchar (p, x++, y, a, ' '); m--;
  }
}

/* ------------------------------------------------------------------------ */
#define JUNK
#ifdef JUNK
w_selpage (p)
int p;
{ union REGS rega, regb;
  rega.h.ah = 5;
  rega.h.al = p;
  int86 (0x10, &rega, &regb);
}

/* ------------------------------------------------------------------------ */
w_border (col)
int col;
{ union REGS rega, regb;
  rega.h.ah = 11;
  rega.h.bh = 0;    /* Colour Palette 0 */
  rega.h.bl = col;
  int86 (0x10, &rega, &regb);
}

/* ------------------------------------------------------------------------ */
w_setchar (p, x, y, a, c)
int p, x, y, a, c;
{ union REGS rega, regb;
    if (x < 0 || x > 79 || y < 0 || y > 24) return;
    rega.h.ah = 2;
    rega.h.bh = p;
    rega.h.dl = x;
    rega.h.dh = y;
    int86 (0x10, &rega, &regb);

    rega.h.ah = 9;
    rega.h.bh = p;
    rega.x.cx = 1;
    rega.h.al = c;
    rega.h.bl = a;
    int86 (0x10, &rega, &regb);
}

#endif
