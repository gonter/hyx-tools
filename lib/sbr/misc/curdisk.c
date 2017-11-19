/*
 *  FILE %sbr/curdisk.c
 *
 *  written:       1995-12-03
 *  latest update: 1995-12-03
 *
 */

#include <dos.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
int get_current_disk ()
{
  return bdos (0x19, 0x00, 0x00);
}

/* ------------------------------------------------------------------------ */
int select_disk (int disk_number)
{
  return bdos (0x0E, disk_number, 0x00) & 0x00FF;
}

