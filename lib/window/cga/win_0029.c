/*
 *  FILE C:\usr\window\win0cga.arc [WIN_0029.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *              Revision
 *
 */

# pragma check_stack(off)

int cga_blit_save (puffer, page, ax, ay, bx, by)
int *puffer;
int   page, ax, ay, bx, by;
{
  register int x, y;

  for (x = ax; x <= bx; x++)
    for (y = ay; y <= by; y++)
    {
      *puffer++ = cga_getchar (page, x, y);
      /* cga_getchar liefert (character, attribut) als Integer wobei        */
      /* character das LSB ist und als erstes in den Puffer wandert.        */
    }
}
