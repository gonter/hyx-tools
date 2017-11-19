/*
 *  include FILE <gg/macbinar.h>
 *
 *  written:       1990 05 15
 *                 1991 06 24: Revision
 *  latest update: 1995-02-12
 *
 */

#ifndef __GG_macbinary__
#define __GG_macbinary__

#pragma pack(1)

#define MB_READ         0
#define MB_WRITE        1
#define MB_DISABLE      0x80

/* ------------------------------------------------------------------------ */
struct MBHead                   /* MacBinary header                         */
{
  char zero1;                   /* reserved; should be zero                 */
  char nlen;                    /* length of name string                    */
  char name [63];               /* name string                              */
  char type [4];                /* Type ID                                  */
  char creator [4];             /* Creator ID                               */
  char flags;
  char zero2;                   /* reserved; should be zero                 */
  char location [6];
  char protected;
  char zero3;                   /* reserverd; should be zero                */
  long dflen;                   /* data fork length                         */
  long rflen;                   /* resource fork lenth                      */
  char cdate [4];               /* creation date                            */
  char mdate [4];               /* modification date                        */
  char res [29];                /* reserved                                 */
} ;

#pragma pack()

#endif /* __GG_macbinary__ */
