/*
 *  FILE /usr/sbr/ebcasc.c
 *
 *  Umwandlung von EBCDIC nach ASCII
 *
 *  1988 12 13
 *  1990 06 02: Revision
 *
 */

#include <stdio.h>
#include <io.h>
#include <gg/ebcasc.h>
#include <gg/filename.h>

#pragma check_stack(off)

static char table_name [66];
static char EBCDIC_ASCII_Table [256];

static int  module_initialized=0;

/* initialize the module: ------------------------------------------------- */
int EBCDIC_ASCII_INIT ()
{
  FILE *fi;

  if (access (table_name, 0) != 0) return -1;

  module_initialized=1;
  set_etc_filename (table_name, TABLE_NAME);
  fi = fopen (table_name, "rb");
  fread  (EBCDIC_ASCII_Table, 1, 256, fi);
  fclose (fi);

  return 0;
}

/* convert a block of characters: ----------------------------------------- */
int EBCDIC_ASCII_convert (char p[], int start, int lng)
{
  int i,j;

  if (! module_initialized)
  {
    if (EBCDIC_ASCII_INIT () < 0) return -1;
  }

  for (i=start; lng > 0; lng--)
  { 
    p [i] = (EBCDIC_ASCII_Table [j = (p[i] & 0x00FF)]) & 0x00FF;
/************
    printf ("Convert %3d: %02X -> %02X\n", i, j, p[i]);
************/
    i++;
  }

  return 0;
}

/* convert one character: ------------------------------------------------- */
int EBCDIC_ASCII_char_convert (int ch)
{
  if (! module_initialized)
  {
    if (EBCDIC_ASCII_INIT () < 0) return -1;
  }

  return (EBCDIC_ASCII_Table [ch & 0x00FF]) & 0x00FF;
}
