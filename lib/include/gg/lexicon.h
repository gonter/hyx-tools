/*
 *  include FILE <gg/lexicon.h>
 *
 *
 *  written:       1990 11 13
 *                 1991 01 09: Revision
 *                 1991 03 16: Revision; AIX
 *  latest update: 1995-06-25
 *
 */

#ifndef __GG_lexicon__
#define __GG_lexicon__

#include <gg/floskel.h>

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
struct LEXICON_FILE
{
  struct LEXICON_FILE *LEXF_next;
  char *LEXF_fnm;               /* real filename */
  FILE *LEXF_fp;                /* 'cached' file pointer */
  char LEXF_open_mode [6];      /* open mode string */
  long LEXF_p1;                 /* parameters: used differently */
  long LEXF_p2;
  long LEXF_p3;
} ;
#endif /* _FILE_DEFINED */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/* usage of parameters:                                                     */
/* LUT:                                                                     */
/*      p1 ... LUT number                                                   */
/*      p2 ... size of LUT in byte                                          */
/*      p3 ... 1 -> LUT can still be expanded                               */

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
struct LEXICON_DESCRIPTION      /* description of files etc. for *one*  */
{                               /* lexicon file system                  */
  char LEX_path [66];
  int  LEX_used;                                /* 1 -> entry used          */
  struct LEXICON_FILE *LEX_main_luts;           /* lists of the different   */
  struct LEXICON_FILE *LEX_clusters;            /* files, used for the      */
  struct LEXICON_FILE *LEX_index_tables;        /* lexicon file system      */
} ;
#endif /* _FILE_DEFINED */

/* ------------------------------------------------------------------------ */
#define LEXICON_INDEX_SIZE     0x00010000L      /* indizes per IDX-file     */
#define LEXICON_LUT_SIZE            50000L      /* byte per LUT-file        */
#define LEXICON_CLUSTER_SIZE       700000L      /* byte per HYX-file        */
/* ... these values are completely arbitrary                                */

/* ------------------------------------------------------------------------ */
#ifdef MSDOS
#define fopen_APPEND "ab"
#define fopen_READ   "rb"
#define fopen_READ_WRITE  "a+b"
#define fopen_WRITE  "wb"
#else
#define fopen_APPEND "a"
#define fopen_READ   "r"
#define fopen_READ_WRITE  "a+"
#define fopen_WRITE  "w"
#endif

/* Notes: ----------------------------------------------------------------- */
/* a) each LEXICON system must reside in it's own directory.                */
/* b) all files in that directory are considered to belong to the           */
/*    particular LEXICON system.                                            */
/* c) the LEXICON system can manipulate all files that belong to it         */
/*    in every way, whatever the system decides.                            */

/* DICTADD Setup flags: --------------------------------------------------- */
#define DASTP_SET_LEXICON_FILE          0x0001
#define DASTP_GET_LEXICON_FILE          0x1001
#define DASTP_SET_INDEX_FILE            0x0002
#define DASTP_GET_INDEX_FILE            0x1002
#define DASTP_SET_MAIN_LUT_FILE         0x0003
#define DASTP_GET_MAIN_LUT_FILE         0x1003
#define DASTP_SET_CLUSTER_NAME          0x0004

/* lex00001.c --- *** not used! *** --------------------------------------- */
struct LEXICON_DESCRIPTION *cdecl LEXICON_get_description (int lexicon_handle);
int cdecl LEXICON_init (int lexicon_handle, char *lexicon_path);
int cdecl LEXICON_get_entry (int lexicon_handle, long frame_index,
                             char *puffer, long puffer_size);
#ifdef _FILE_DEFINED
int cdecl _LEXICON_get_entry (struct LEXICON_DESCRIPTION *ld,
                              long frame_index,
                              char *puffer, long puffer_size,
                              FILE *fo, int out_mode);
#endif /* _FILE_DEFINED */
long cdecl get_usable_cluster (struct LEXICON_DESCRIPTION *ld);
int cdecl LEXICON_add_entry (int lexicon_handle, long frame_index,
                             char *puffer, long siz);
int cdecl _LEXICON_add_entry (struct LEXICON_DESCRIPTION *ld,
                              long frame_index, char *puffer, long siz);
long cdecl LEXICON_new_entry (int lexicon_handle);
#ifdef _FILE_DEFINED
int cdecl LEXICON_print (FILE *fo);
int cdecl LEXICON_print_entry (FILE *fo, int nr);
#endif /* _FILE_DEFINED */
int cdecl LEXICON_flush (void);

/* dict0003.c .. dict0006.c see <gg/parse.h> ------------------------------ */

#endif /* __GG_lexicon__ */
