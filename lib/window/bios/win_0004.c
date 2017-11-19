/*
 *  FILE C:\usr\window\win0bios.arc [WIN_0004.C]
 *
 *  1989 08 16: aus WIN0.SAR Åbernommen
 *  Revision
 *
 */

#  pragma check_stack(off)

void bios_reset ()
{
  bios_init_mode ("80x25 COL Text", -1);
  bios_cursoron  ();
}

/* ------------------------------------------------------------------------ */
