/*
 *  include FILE <gg/gif.h>
 *
 *  datastructures for GIF-files etc.
 *
 *  written:       1989 08 29
 *                 1991 10 03: Revision
 *  latest update: 1994-09-04
 *
 */


#ifndef __GG_gif__
#define __GG_gif__

#define GIF_signature                  "GIF87a"
#define GIF_image_signature            ','
#define GIF_terminator                 ';'
#define GIF_extension_signature        '!'

#pragma pack(1)

/* ------------------------------------------------------------------------ */
struct GIF_screen_descriptor
{
  int   gif_screen_width;
  int   gif_screen_height;
  char  gif_pixels_;
  char  gif_background;
  char  gif_dummy_1;
} ;

/* ------------------------------------------------------------------------ */
struct GIF_color_map
{
  char  gif_intensity_red;
  char  gif_intensity_green;
  char  gif_intensity_blue;
} ;

/* ------------------------------------------------------------------------ */
struct GIF_image_descriptor
{
  int   gif_image_left;
  int   gif_image_top;
  int   gif_image_width;
  int   gif_image_height;
  char  gif_image_flags;
} ;

/* ------------------------------------------------------------------------ */
struct GIFLZW_DATA              /* status variables from module GIFLZWDC.C  */
{                               /* >>>>>> se also GIFLZWDC.C <<<<<<<<<<<<<< */
  int   GLD_block_counter;      /* position in decode-block                 */
  int   GLD_stat;               /* state of the LZW-deocoder                */
  int   GLD_mem_available;      /* 1 -> memory for tables is available      */
                                /* ---------------------------------------- */
  int   GLD_pixies;             /* Bits/Pixel; initial code size            */
  int   GLD_code_size;          /* actual code size: pixies+1 .. 12         */
  int   GLD_bits;               /* compose decoding code                    */
  int   GLD_bit_num;            /* number of bits in bits []                */
  int   GLD_min_code;           /* first available LZW-code                 */
  int   GLD_max_code;           /* first LZW-code with code_size+1 bits     */
  int   GLD_clear;              /* CLEAR-Code (== min_code - 2)             */
  int   GLD_end;                /* END-Code (== min_code - 1)               */
  int   GLD_nvc;                /* Next Valid Code (LZW-code to come)       */
  int   GLD_code;               /* LZW-code just processed                  */
  int   GLD_new_code;           /* LZW-code just processed                  */
  int   GLD_old_code;           /* LZW-code previously processed            */
  int   GLD_color;              /* color derived from LZW-code              */
                                /* ---------------------------------------- */
  int   GLD_sp;                 /* stack pointer for output stack           */
  int  *GLD_stack;              /* output stack                             */
  int  *GLD_shade;              /* color code of the LZW-codes              */
  int  *GLD_child;              /* following LZW-code of the LZW-codes      */
                                /* child [i] = j; j < i;                    */
                                /* in all cases ?                           */
                                /* i < min_code undefined; i is a color     */
} ;

/* ------------------------------------------------------------------------ */
#define GIF_ERROR_invalid_LZW_code 1

/* ------------------------------------------------------------------------ */
struct GIFLZW_DATA *cdecl get_giflzw_data();

#pragma pack()

#endif /* __GG_gif__ */
