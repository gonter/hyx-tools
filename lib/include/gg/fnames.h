/*
 *  include FILE <gg/fnames.h>
 *
 *  Files suchen Åber DOS
 *
 *  written:       1987 10 21
 *                 1990 02 03: Revision
 *                 1991 01 28: Revision
 *  latest update: 1996-08-11 10:10:11
 *
 */

#ifndef __GG_fnames__
#define __GG_fnames__

/* DOS Function Calls - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define Setdta                 0x1A
#define First                  0x4E
#define Next                   0x4F

/* File Attribute - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define FA_READONLY             0x01
#define FA_HIDDEN               0x02
#define FA_SYSTEM               0x04
#define FA_VOLUME               0x08
#define FA_DIRECTORY            0x10    /* just directories                 */
#define FA_ARCHIVE              0x20
#define FA_FILE                 0x27    /* alle Files                       */
#define FA_ALL                  0x37    /* auch Directories                 */

/* Kontroll-Struktur fÅr Directory Entry  - - - - - - - - - - - - - - - - - */
#pragma pack(1)

struct dta_buff                         /* Standard DTA-Struktur lt. MSDOS  */
{
  char res [21];                        /* (laut MicroSoft reserved)        */
  char att;                             /* File Attribute: FA_xxxx          */
  int  time, date;                      /* Date/Time der letzten énderung   */
  long size;                            /* File Size in Bytes               */
  char name [14];                       /* File Name                        */
} ;

/* erweiterte Kontroll-Struktur fÅr Directory Entry - - - - - - - - - - - - */
struct dta2_buff                        /* Listen + Info */
{
  char att;                             /* File Attribute: FA_xxxx          */
  int  time, date;                      /* Date/Time der letzten énderung   */
  long size;                            /* File Size in Bytes               */
  char name [14];                       /* File Name                        */
  struct dta2_buff *prev, *next;        /* Listenverkettung                 */
  int  info_allocated;                  /* FM: 1 -> Info-EintrÑge gÅltig    */
  int  info_cnt;                        /* FM: Zahl der infos []            */
  int  select_code;                     /* FM: Function-Key fÅr DIESES File */
  int  mark_left;                       /* FM: Markierungsattribut          */
  char *infos [2];                      /* FM: Info EintrÑge                */
} ;

#pragma pack()

/* Modul FNAMES.C --------------------------------------------------------- */
void cdecl Fsetdta (struct dta_buff *dta);
int  cdecl Fsfirst (char *name, int att);
int  cdecl Fsnext  (void);

/* Modul FNAMES2.C -------------------------------------------------------- */
struct dta_buff *cdecl Fdta_find   (char *path, int attr);
char            *cdecl Fname_find  (char *path, int attr);
void             cdecl Freset_find (void);
struct dta_buff *cdecl Fget_dta    (void);

#endif /* __GG_fnames__ */
