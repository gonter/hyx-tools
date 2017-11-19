/*
 *  include FILE <gg/archead.h>
 *
 *  Verarbeiten von Archiv Files (.ARC, .PAK)
 *
 *  written:       1989 01 20
 *                 1989 07 02: aus ARCFILES.C extrahiert
 *                 1990 02 03: Revision
 *                 1991 01 28: Revision
 *  latest update: 1994-11-11
 *
 */

#ifndef __GG_archead__
#define __GG_archead__

#pragma pack(1)

/* PKARC, PKPACK, ARC ----------------------------------------------------- */
struct heads
{                               /* archive entry header format              */
  char name[13];                /* file name                                */
  long size;                    /* size of file, in bytes IM ARCHIV !!!!    */
  unsigned int date;            /* creation date                            */
  unsigned int time;            /* creation time                            */
  int crc;                      /* cyclic redundancy check                  */
  long length;                  /* true file length DECOMPRIMIERT !!!!      */
} ;

/* Compression Methods: Wird im Archiv VOR dem Header gespeichert --------- */
#define ARC_END         0       /* -> Ende des ARC-Files                    */
#define ARC_store_1     1       /* -> unkomprimiert                         */
#define ARC_store_2     2
#define ARC_pack        3
#define ARC_squeeze     4
#define ARC_crunch_1    5
#define ARC_crunch_2    6
#define ARC_crunch_3    7
#define ARC_crunch_4    8
#define ARC_squash      9

/* Modul ARCHEAD.C -------------------------------------------------------- */
int cdecl get_arc_head (FILE *fi, struct heads *head);

/* Modul ARCFILES.C ------------------------------------------------------- */
int cdecl get_arc_file (FILE *fi, struct dta_buff *p);

#endif
