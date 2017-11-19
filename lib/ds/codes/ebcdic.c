/*
 *  File ~/usr/dpp/codes/ebcdic.c
 *
 *  written:       1992-12-25
 *  latest update: 1994-04-03
 *
 */

#include <stdio.h>
#include <gg/asc2ebc.inc>
#include <gg/ebc2asc.inc>

/* ------------------------------------------------------------------------ */
int main ()
{
  int ascii;
  int ebcdic;
  int a2;

  for (ascii=0; ascii<256; ascii++)
  {
    ebcdic = CODE_ASCII_to_EBCDIC [ascii];
    if ((a2= CODE_EBCDIC_to_ASCII [ebcdic]) != ascii)
    {
      printf ("# warning: ascii 0x%02X -> ebcdic 0x%02X -> ascii 0x%02X\n",
        ascii, ebcdic, a2);
    }
    else
    {
      printf ("ascii=0x%02X\tebcdic=0x%02X\n", ascii, ebcdic);
    }
  }

  return 0;
}
