/*
 *  FILE ~/usr/window/1/win_0112.c
 *
 *  written:       1989 08 16: aus WIN1.SAR uebernommen
 *                             Revision
 *  latest update: 1995-03-05: extracted from win_0111.c
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
void w_disp_box (
int page,
int ax,
int ay,
int bx,
int by,
int attr,
int box_typ,    /* 1 -> einfach; sonst: doppelt                             */
int box_edges)  /* bit 0: upper edge                                        */
                /* bit 1: upper right corner                                */
                /* bit 2: right edge                                        */
                /* bit 3: lower right corner                                */
                /* bit 4: lower edge                                        */
                /* bit 5: lower left corner                                 */
                /* bit 6: left edge                                         */
                /* bit 7: upper left corner                                 */
{
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
  if (ax == bx && (box_edges & 0x0044))
  {
    for (i= ay; i <= by; i++)
      w_setchar (page, ax, i, attr, linie_senkrecht);
    return;
  }

  /* Box besteht nur aus der waagrechten Linie */
  if (ay == by && (box_edges & 0x0011))
  {
    w_setnchar (page, ax, ay, attr, linie_waagrecht, bx-ax+1);
    return;
  }

  /* Richtige Box */
  if (ax+1 < bx && (box_edges & 0x0001))
     w_setnchar (page, ax+1, ay, attr, linie_waagrecht, bx-ax-1);

  if (box_edges & 0x0002)
    w_setchar (page, bx, ay, attr, ecke_rechts_oben);

  if (box_edges & 0x0004)
    for (i= ay + 1; i < by; i++)
      w_setchar (page, bx, i, attr, linie_senkrecht);

#ifdef RU_OK
  if (box_edges & 0x0008)
    w_setchar (page, bx, by, attr, ecke_rechts_unten);
#endif

  if (ax+1 < bx && (box_edges & 0x0010))
    w_setnchar (page, ax+1, by, attr, linie_waagrecht, bx-ax-1);

  if (box_edges & 0x0020)
  w_setchar (page, ax, by, attr, ecke_links_unten);

  if (box_edges & 0x0040)
    for (i= ay + 1; i < by; i++)
      w_setchar (page, ax, i, attr, linie_senkrecht);

  if (box_edges & 0x0080)
    w_setchar (page, ax, ay, attr, ecke_links_oben);

}
