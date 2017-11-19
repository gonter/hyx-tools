/*
 *  FILE ~/usr/window/cga/win_0004.c
 *
 *  written:       1989 08 16: aus WIN0.SAR Åbernommen
 *  latest update: 1994-08-20
 *
 */

#pragma check_stack(off)

/* ------------------------------------------------------------------------ */
void cga_reset ()
{
  bios_init_mode ("80x25 COL Text", -1);
  bios_cursoron  ();
}

