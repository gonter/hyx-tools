/*
 *  FILE C:\usr\window\win0cga.arc [WIN_0030.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *              Revision
 *
 */

# pragma check_stack(off)

int cga_blit_load (puffer, page, ax, ay, bx, by)
char *puffer;
int   page, ax, ay, bx, by;
{
  register int x, y;

  for (x = ax; x <= bx; x++)
    for (y = ay; y <= by; y++)
    {
      cga_setchar (page, x, y, *puffer++, *puffer++);
      /*                        attribut   character                        */
      /* ANM: blit_save legt (character, attribut) als integer in den       */
      /*      als INT-Array betrachteten puffer ab, wobei character im      */
      /*      Intel-Format als LSB als ersetes abgelegt wird.               */
      /*      blit_load betrachtet puffer als CHAR-Array.                   */
      /*      Da zuerst das rechte *puffer++ evaluiert wird, kommt          */
      /*      zuerst der character und dann das attribut aus dem            */
      /*      Puffer heraus. (daher alles ok)                               */
    }
}
