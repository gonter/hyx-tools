/*
 *  FILE ~/usr/window/1/win_0111.c
 *
 *  written:       1989 08 16: aus WIN1.SAR uebernommen
 *                             Revision
 *  latest update: 1995-03-05
 *
 */

#include <gg/window.h>

#ifdef MSDOS
#pragma check_stack(off)
#define RU_OK
#endif

#ifdef W_MODEL_NCURSES
#define RU_OK
#endif

/* Display Box in Blockmode ----------------------------------------------- */
void w_disp_bbox (
int page,
int ax,
int ay,
int bx,
int by,
int attr,
int box_typ)   /* 1 -> einfach; sonst: doppelt */
{
#ifdef JUNKIE
  register int i;
  int linie_waagrecht;
  int linie_senkrecht;
  int ecke_links_oben;
  int ecke_rechts_oben;
  int ecke_rechts_unten;
  int ecke_links_unten;

  /* Koordinaten verdreht: keine Box */
  if (ax > bx || ay > by) return;

#ifdef MSDOS
  /* Box ist nur ein Zeichen gross */
  if (ax == bx && ay == by)
  {
    if (box_typ)
         w_setchar (page, ax, ay, attr, 0x07);
    else w_setchar (page, ax, ay, attr, 0x09);
    return;
  }

  switch (box_typ)
  {
    case 1:
            linie_waagrecht   = 0xC4;
            linie_senkrecht   = 0xB3;
            ecke_links_oben   = 0xDA;
            ecke_rechts_oben  = 0xBF;
            ecke_rechts_unten = 0xD9;
            ecke_links_unten  = 0xC0;
            break;
    case 2: linie_waagrecht   = 0xCD;
            linie_senkrecht   = 0xBA;
            ecke_links_oben   = 0xC9;
            ecke_rechts_oben  = 0xBB;
            ecke_rechts_unten = 0xBC;
            ecke_links_unten  = 0xC8;
            break;
    default: return;
  }
#else
  /* Box ist nur ein Zeichen gross */
  if (ax == bx && ay == by)
  {
    w_setchar (page, ax, ay, attr, '*');
    return;
  }

  linie_waagrecht   = '-';
  linie_senkrecht   = '|';
  ecke_links_oben   =
  ecke_rechts_oben  =
  ecke_rechts_unten =
  ecke_links_unten  = '+';
#endif

  /* Box besteht nur aus der senkrechten Linie */
  if (ax == bx)
  {
    for (i = ay; i <= by; i++)
        w_setchar (page, ax, i, attr, linie_senkrecht);
    return;
  }

  /* Box besteht nur aus der waagrechten Linie */
  if (ay == by)
  {
    w_setnchar (page, ax, ay, attr, linie_waagrecht, bx-ax+1);
    return;
  }

  /* Richtige Box */
  w_setchar (page, ax, ay, attr, ecke_links_oben);

  if (ax+1 < bx)
     w_setnchar (page, ax+1, ay, attr, linie_waagrecht, bx-ax-1);

  w_setchar (page, bx, ay, attr, ecke_rechts_oben);

  for (i= ay + 1; i < by; i++)
  {
    w_setchar (page, bx, i, attr, linie_senkrecht);
    w_setchar (page, ax, i, attr, linie_senkrecht);
  }

  w_setchar (page, ax, by, attr, ecke_links_unten);

#ifdef RU_OK
  w_setchar (page, bx, by, attr, ecke_rechts_unten);
#endif

  if (ax+1 < bx)
    w_setnchar (page, ax+1, by, attr, linie_waagrecht, bx-ax-1);
#else
  w_disp_box (page, ax, ay, bx, by, attr, box_typ, 0x00FF);
#endif /* !JUNKIE */
}
