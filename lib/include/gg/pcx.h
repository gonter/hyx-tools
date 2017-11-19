/*
 *  include FILE <gg/pcx.h>
 *
 *  header for PCX files format
 *
 *  written:       1989 08 09
 *                 1991 10 03: Revision
 *  latest update: 1994-11-11
 *
 */

#ifndef __GG_pcx__
#define __GG_pcx__

#pragma pack(1)

/* ------------------------------------------------------------------------ */
struct PCX_TRIPLET
{
  char pcx_red;
  char pcx_green;
  char pcx_blue;
} ;

/* ------------------------------------------------------------------------ */
struct PCX_HEADER
{
  char pcx_maker;
  char pcx_version;
  char pcx_encoding;
  char pcx_bpp;
  int  pcx_ax;
  int  pcx_ay;
  int  pcx_bx;
  int  pcx_by;
  int  pcx_xres;
  int  pcx_yres;
  struct PCX_TRIPLET pcx_triple[16];    /* palette                          */
  char pcx_vmode;
  char pcx_nplanes;
  int  pcx_bpl;                         /* Byte Per Line                    */
  char _pcx_unused[128-68];             /* or 256 color RGB map ??          */
} ;

/* ------------------------------------------------------------------------ */
struct PCX_PICTURE
{
  struct PCX_HEADER pcx_hdr;
  unsigned char **pcx_rows[4];
} ;

#pragma pack()

#endif /* __GG_pcx__ */
