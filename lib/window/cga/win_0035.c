/*
 *  FILE C:\usr\window\win0cga.arc [WIN_0034.C]
 *
 *  1989 09 17
 *
 */

# pragma check_stack(off)
# pragma pack(1)

int cga_scrblk_right (page, ax, ay, bx, by, attr, cnt)
int page, ax, ay, bx, by, attr, cnt;
{
  register int x, y;
  union { int  ch_i;
          char ch_c [2];
        } ch;

  if (cnt <= 0 || cnt > bx - ax) return -1;
  for (x = bx-cnt; x >= ax; x--)
    for (y = ay; y <= by; y++)
    {
      ch.ch_i = cga_getchar (page, x, y);
      cga_setchar (page, x+cnt, y, ch.ch_c[1], ch.ch_c[0]);
      /* cga_getchar liefert (character, attribut) als Integer wobei        */
      /* character das LSB ist und als erstes in den Puffer wandert.        */
    }
  for (y = ay; y <= by; y++)
      cga_setchar (page, ax, y, attr, ' ');
}
