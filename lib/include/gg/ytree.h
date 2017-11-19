/*
 *  include FILE <gg/ytree.h>
 *
 *  managing of ytree data structures
 *  see also: %ds/ytree/
 *  - prototypes
 *
 *  written:       1989 03 29
 *                 1990 11 11: isolated from WORDCREA.H
 *                 1991-12-10: isolation as a library package
 *  latest update: 1998-08-07 14:16:48
 *  $Id: ytree.h,v 1.4 2005/09/04 20:27:37 gonter Exp $
 *
 */

#ifndef __GG_ytree__
#define __GG_ytree__

#include <gg/floskel.h>

#ifndef ZTREE_DEPTH_MAX         /* from <gg/ztree.h> */
#define ZTREE_DEPTH_MAX  1024   /* max. Laenge eines Wortes,                */
                                /* -> max. Tiefe des Woerterbuches          */
#endif /* !ZTREE_DEPTH_MAX */

/* ------------------------------------------------------------------------ */
#define _YTREE_DEFINED
struct YTREE
{
  struct YTREE *YT_next;        /* anderes Zeichen                          */
  struct YTREE *YT_down;        /* dieses Zeichen; naechste Stelle          */
  long YT_size;                 /* fuer die ganze Substruktur benoetigter   */
                                /* Platz im Binaerfile in Bytes             */
                                /* (Einschliesslich des Vater-Knotens?)     */
  long YT_info;                 /* Informationsteil                         */
  unsigned int YT_lng_str;      /* Laenge der Zeichenkette                  */
  unsigned int YT_flags;        /* siehe unten                              */
  unsigned char YT_str[2];      /* Zeichenstring fuer den Schluessel        */
                                /* veraenderlich !!!!!                      */
} ;

/* ------------------------------------------------------------------------ */
#define YTflag_EOW        0x01  /* End of Word                              */
#define YTflag_TABbeg     0x02  /* Table Begin                              */
#define YTflag_TABend     0x04  /* Table End                                */
#define YTflag_OFF        0x70  /* Offset Groesse                           */
#define YTflag_OFFx       0x8F  /* Offset Groesse (invertiert)              */
#define YTflag_OFF0       0x00  /* Keine Offset noetig; Ende der Liste      */
#define YTflag_OFF1       0x10
#define YTflag_OFF2       0x20
#define YTflag_OFF3       0x30
#define YTflag_OFF4       0x40

/* methods: --------------------------------------------------------------- */
typedef int YTREE_PROCESSOR      (struct YTREE *yt_node, void *client_data);
typedef int YTREE_TRACKER        (struct YTREE *yt_node, char *str, void *client_data);
typedef int YTREE_INFO_PROCESSOR (long info, void *client_data);
typedef int YTREE_INFO_TRACKER   (long info, char *str, void *client_data);

/* ------------------------------------------------------------------------ */
struct YTREE_CONTROL
{
  long signature;
  char *name;

  struct YTREE *yt;
  long size;
  long element_count;

  YTREE_INFO_PROCESSOR *destructor;
  void *destructor_cd;
} ;

/* Ausgabe Funktionen (Klarschrift) --------------------------------------- */
struct LUT_STACK
{
  long offset;          /* next alternative                                 */
  int  key;             /* part of the key                                  */
} ;

/* ------------------------------------------------------------------------ */
#define ytree_get_tree(x) (((x)==(struct YTREE_CONTROL *) 0)\
    ? (struct YTREE *) 0 : (x)->yt)

/* prototypes: ------------------------------------------------------------ */
/* yt_00001.c */ struct YTREE *cdecl ytree_alloc (unsigned char *s,
                   int lng_str);
                 int cdecl ytree_free_node (struct YTREE *yt);

/* yt_00002.c */ int cdecl ytree_free (struct YTREE *yt);

/* yt_00003.c */ struct YTREE *cdecl ytree_insert_word (struct YTREE **ypp,
                   unsigned char *wort);
                 struct YTREE *cdecl ytree_lookup_word_get_last (void);
                 int cdecl ytree_lookup_word_get_lng (void);

/* yt_00004.c */ struct YTREE *cdecl ytree_lookup_word (struct YTREE *yp,
                   unsigned char *wort);

/* yt_00005.c */ int cdecl ytree_delete_word (struct YTREE **ypp,
                   unsigned char *wort);

/* yt_00006.c */ long cdecl ytree_size (struct YTREE *yt);

#ifdef _FILE_DEFINED
/* yt_00007.c */ int cdecl ytree_print (FILE *fo, struct YTREE *yt,
                   int indent);

/* yt_00008.c */ int cdecl ytree_print_node (FILE *fo, struct YTREE *yt,
                   int indent);

/* yt_00009.c */ long cdecl ytree_dump (FILE *fo, struct YTREE *yt);

/* yt_00010.c */ int cdecl ytree_scan (FILE *lut, struct YTREE **ytp);

/* yt_00011.c */ int cdecl ytree_full_scan (FILE *lut, struct YTREE **ytp,
                   long  kill_by_info[], int kill_by_info_cnt,
                   char *kill_by_str [], int kill_by_str_cnt);
#endif

/* yt_00012.c */ int cdecl ytree_process (struct YTREE *yt,
     /***** int (*processor) (struct YTREE *yt_node, void *client_data), ****/
                  YTREE_PROCESSOR *processor,
                  void *client_data);

#ifdef _FILE_DEFINED
/* yt_00013.c */ int cdecl ytree_operations (struct YTREE **ytpp,
                   FILE *fi, FILE *fo);
#endif
/* yt_00014.c */ int cdecl ytree_debug (struct YTREE *yt);
/* yt_00015.c */ int cdecl ytree_dump_to_lut_file (char *name_lut,
                   struct YTREE *yt);

/* yt_00016.c */ long cdecl ytree_set_value (struct YTREE **yt,
                   const unsigned char *w, long v);
/* yt_00017.c */ long cdecl ytree_increment_value (struct YTREE **ytp,
                   const unsigned char *w, long v);
/* yt_00018.c */ long cdecl ytree_get_value (struct YTREE *ytp,
                   const unsigned char *w);
/* yt_00019.c */ struct YTREE *cdecl ytree_duplicate (struct YTREE *yt);
/* yt_00020.c */ int cdecl ytree_repack (struct YTREE **ytp);
/* yt_00021.c */ int cdecl ytree_track (struct YTREE *yt,
                   char *buffer, int buffer_size, int buffer_pos,
                   YTREE_TRACKER *tracker, void *client_data);
/* yt_00022.c */ int ytree_process_info (struct YTREE *yt,
                   YTREE_INFO_PROCESSOR *processor, void *client_data);
/* yt_00023.c */ int ytree_track_info (struct YTREE *yt,
                   char *buffer, int buffer_size, int buffer_pos,
                   YTREE_INFO_TRACKER *tracker, void *client_data);

/* yt_00101.c */ struct YTREE_CONTROL *ytree_new_control (char *name);
/* yt_00102.c */ int ytree_free_control (struct YTREE_CONTROL *yc);

#endif /* !__GG_ytree__ */
