/*
 *  include FILE <gg/lzhhead.h>
 *
 *  structure and constants of LH-ARC files (extension LZH)
 *
 *  written:       1990 05 26
 *                 1991 01 28: Revision
 *  latest update: 1994-11-12
 *
 */

#ifndef __GG_lzhhead__
#define __GG_lzhhead__

#pragma pack(1)

/* structure: ------------------------------------------------------------- */
struct LZH_HEAD
{
  /* fix part: 22 bytes                                                     */
  unsigned char  LZH_header_size;
  unsigned char  LZH_header_cks;        /* calculation not known ########## */
  char           LZH_header_sign [5];   /*                                  */
  long           LZH_size_compressed;   /*                                  */
  long           LZH_size_decompressed; /*                                  */
  long           LZH_timestamp;         /* ######                           */
  int            LZH_attributes;        /* ######                           */
  unsigned char  LZH_name_length;       /* 1 if name has one char           */

  /* variable part                                                          */
  char           LZH_name [64];         /* maximum name length in DOS       */
} ;

/* constants: ------------------------------------------------------------- */
#define LZH_FIX_HEAD_SIZE  23           /* includes name length,            */
                                        /* but not the name                 */
#define LZH_SIGN_1     "-lh1-"          /* only known signature so far      */

/* prototypes: ------------------------------------------------------------ */
int cdecl get_lzh_head (
FILE *fi,                       /* archive file, binary opened              */
struct LZH_HEAD *head);         /* LZH-Header                               */
/* RETURN:                                                                  */
/*          -1 error or no archive                                          */
/*           0 EOF: no more files in archive                                */
/*          >0 archived file found; head is valid                           */

#endif
