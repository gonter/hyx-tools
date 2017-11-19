/*
 *   include FILE <gg/objdec.h>
 *
 *   Decoder fuer Files im INTEL RELOCATIBLE OBJECT FORMAT
 *   in der MICROSOFT Variante
 *
 *   written:       1988 01 12
 *                  1990 04 26: Revision
 *   latest update: 1997-08-16  9:47:22
 *
 */

#ifndef __GG_objdec__
#define __GG_objdec__

#include <gg/floskel.h>

#ifdef NIL
#undef NIL
#endif
#define NIL (void *) 0

#define CROSS_REFERENCE         /* Diese Variante von OBJDEC kann           */
                                /* auch Cross References erzeugen           */

#pragma pack(1)

/* ------------------------------------------------------------------------ */
struct OBJ_RECORD               /* Beginn eines Object Records              */
{                               /* ... es werden 3 Byte des Records gelesen */
  char rec_typ;                 /* Record Type Code                         */
  char rec_lng [2];             /* Laenge des Records: wie's im File steht  */
  int  Irec_lng;                /* Laenge des Records: ausgerechnet         */
} ;

/* ------------------------------------------------------------------------ */
struct DEF_NAME                 /* Segment- und Group Names udgl. */
{
  struct DEF_NAME *next;
  int  nsize;
  char nm [2];
} ;

/* ------------------------------------------------------------------------ */
struct DEF_SEG                  /* Segment Definition */
{
  struct DEF_SEG *next;
  int    a, c, b, p;
  int    seg_lng,
         frnum,
         offs;
  int    Xname_seg,             /* Index fuer Segment Namen */
         Xname_class,           /* .     .    Class   .     */
         Xname_overlay;
} ;

/* ------------------------------------------------------------------------ */
struct DEF_GROUP_COMPONENT      /* Segmentliste fuer Group Definition */
{
  struct DEF_GROUP_COMPONENT *next;
  int    si,
         Xseg;
} ;

/* ------------------------------------------------------------------------ */
struct DEF_GRP                  /* Group Definition */
{
  struct DEF_GRP *next;
  int    Xname_grp;             /* Index fuer Group Namen */
  int    cnt_seg;               /* Anzahl der Segmente in der Group */
  struct DEF_GROUP_COMPONENT *seg_list;
} ;

/* ------------------------------------------------------------------------ */
struct DEF_EXT
{
  struct DEF_EXT *next;
  int  Xtype,                   /* Type Index        */
       nsize;                   /* Laenge des Namens */
  char nm [2];
} ;

/* ------------------------------------------------------------------------ */
struct DEF_PUB
{
  struct DEF_PUB *next;
  int  Xgrp;                    /* Index fuer Group   Namen    */
  int  Xseg;                    /* .     .    Segment .        */
  int  frnum;                   /* Frame Number; gueltig wenn  */
                                /* Xseg= Xgrp= 0               */
  int  Xtype;
  int  offs;
  int  nsize;
  char nm [2];
} ;

/* ------------------------------------------------------------------------ */
struct LST_STR                  /* String Listen */
{
  struct LST_STR *next;
  char *str1,
       *str2;
} ;

/* Cross Reference -------------------------------------------------------- */
struct CRF_TITLE                /* Liste der untersuchten Module */
{
  struct CRF_TITLE
         *crf_title_nxt;
  char nm [2];                  /* Name des Moduls */
} ;

/* ------------------------------------------------------------------------ */
struct CRF_SEGMENT
{
  struct CRF_SEGMENT
         *crf_segment_nxt;
  char nm [2];                  /* Name des Segments */
} ;

/* ------------------------------------------------------------------------ */
struct CRF_EXTERNAL             /* Verwendung eines Symbols    */
{
  struct CRF_EXTERNAL
         *ref_ext_title;        /* Modulname der Verwendung    */
  struct CRF_TITLE
         *title;
} ;

/* ------------------------------------------------------------------------ */
struct CRF_PUBLIC               /* Definition eines Symbols    */
{
  struct CRF_PUBLIC             /* Sortiert nach ...           */
         *nxt_occ,              /* ... 1. Verwendung           */
         *nxt_name,             /* ... Name des Public Symbols */
         *nxt_title,            /* ... Name des Moduls (title) */
         *nxt_segment;          /* ... Segment                 */

  struct CRF_EXTERNAL
         *ref_ext_title;        /* Modulname der Verwendung    */
  struct CRF_TITLE
         *title;
  struct CRF_SEGMENT
         *segment;
  char nm [2];                  /* Name des Symbols */
} ;

/* ------------------------------------------------------------------------ */
struct RECORD_BUFFER
{
  struct RECORD_BUFFER          /* double linked list, if necessary         */
       *RB_next,
       *RB_prev;

  int   RB_record_type;         /* type of the buffered record              */
  int   RB_record_length;       /* length of the buffered record            */
  int   RB_buffer_size;         /* size of the allocated buffer             */
  long  RB_position_source;     /* position of record in the source file    */
  char *RB_buffer;              /* buffered OBJ-record, comlete with        */
                                /* fields for record type, record length    */
                                /* and calculated checksum                  */
} ;

#pragma pack()

/* Output Modi: ----------------------------------------------------------- */
#define OM_DIAGNOSTIC     0x01          /* Record Struktur anzeigen         */
#define OM_DIA_2          0x02          /* Struktur 'etwas' interpretieren  */
#define OM_ASM            0x04          /* MASM-Header erzeugen             */
#define OM_LEX            0x08          /* LEX records erzeugen             */
#define OM_FEATURE        0x10          /* feature records erzeugen         */

/* Record Types: ---------------------------------------------------------- */
#define RT__fill_      0x00     /* Filler: ?? undokumentiert                */
                                /*   scheinbar wirden diese das in          */
                                /*   Libraries zwischen 2 Module gesetzt,   */
                                /*   sodass jedes Modul an einer            */
                                /* 16-Byte-Grenze beginnt.                  */
#define RT_0x01__      0x01     /* Filler: ?? undokumentiert                */
#define RT_RHEADR      0x6E
#define RT_REGINT      0x70
#define RT_REDATA      0x72
#define RT_RIDATA      0x74
#define RT_OBLDEF      0x76
#define RT_ENDREC      0x78
#define RT_BLKDEF      0x7A
#define RT_BLKEND      0x7C
#define RT_DEBSYM      0x7E
#define RT_THEADR      0x80
#define RT_LHEADR      0x82
#define RT_PEDATA      0x84
#define RT_PIDATA      0x86
#define RT_COMENT      0x88
#define RT_MODEND      0x8A
#define RT_EXTDEF      0x8C
#define RT_TYPDEF      0x8E
#define RT_PUBDEF      0x90
#define RT_LOCSYM      0x92
#define RT_LINNUM      0x94
#define RT_LNAMES      0x96
#define RT_SEGDEF      0x98
#define RT_GRPDEF      0x9A
#define RT_FIXUPP      0x9C
#define RT__none_      0x9E     /* Undokumentiert, keine Funktion ???       */
#define RT_LEDATA      0xA0
#define RT_LIDATA      0xA2
#define RT_LIBHED      0xA4
#define RT_LIBNAM      0xA6
#define RT_LIBLOC      0xA8
#define RT_LIBDIC      0xAA
#define RT_BSSDEF      0xB0     /* ?? Globale BSS Variable ????             */
#define RT__libH_      0xF0     /* library header                           */
#define RT__libX_      0xF1     /* library index at the end of a library    */
#define RT__libD_      0xF2     /* library extended dictionary              */

#define COMENT_TRANSLATOR       0x00
#define COMENT_LIBRARY1         0x81
#define COMENT_MEM_MODEL        0x9D    /* e.g: 0s, 0l, ... */
#define COMENT_0x9E             0x9E    /* ??? */
#define COMENT_LIBRARY2         0x9F
#define COMENT_0xA0             0xA0    /* e.g. CV */
#define COMENT_0xA1             0xA1    /* e.g. CV */
#define COMENT_0xA2             0xA2    /* e.g. CV */
#define COMENT_OBJECT           0xA3

#ifndef NO_PROTOTYPING
/* objproc.c: ------------------------------------------------------------- */
struct DEF_NAME *cdecl get_find_name (char *name, int code);

/* objdec01.c: */ char *cdecl get_record_type (int record_type);
/* objdec02.c: */ char *cdecl get_alignment (int number);
/* objdec03.c: */ char *cdecl get_combination (int number);

/* objdec04.c: ------------------------------------------------------------ */
void cdecl crf_option (char *option_string);
struct CRF_PUBLIC *cdecl get_crf_public (char *n);
struct CRF_PUBLIC *cdecl set_crf_public (char *n);
struct CRF_TITLE *cdecl get_crf_title (char *n, int flg);
struct CRF_SEGMENT *cdecl get_crf_segment (char *n, int flg);
void cdecl sort_crf_external (struct CRF_PUBLIC   *cpp,
                              struct CRF_EXTERNAL *cee);
void cdecl sort_crf_pub_name (void);
void cdecl sort_crf_pub_title (void);
void cdecl sort_crf_pub_seg (void);
void cdecl print_CRF (int argc, char *argv[], char *date_and_time);

/* objdec05.c ------------------------------------------------------------- */
void init_lists (void);
struct DEF_NAME *cdecl get_names (void);
struct DEF_NAME *cdecl get_name (int idx);
void cdecl show_names (FILE *fo);
struct DEF_SEG *cdecl get_segment (int idx);
struct DEF_NAME *cdecl new_name (int slng, char *name);
struct DEF_PUB *cdecl new_public (int slng, char *name, int offs, int xtype,
  int idx_grp, int idx_seg, int frnum);
struct DEF_PUB *cdecl get_publics (void);
struct DEF_EXT *cdecl new_extern (int slng, char *name, int idx);
struct DEF_EXT *cdecl get_externs (void);
struct DEF_SEG *cdecl new_segment (void);
struct DEF_SEG *cdecl get_segments (void);
struct DEF_GRP *cdecl new_group (int idx);
struct DEF_GRP *cdecl get_groups (void);
void cdecl free_all (void);

/* objdec06.c ------------------------------------------------------------- */
struct RECORD_BUFFER *cdecl obj_get_record_buffer (int type, int lng);
void cdecl obj_free_record_buffer (struct RECORD_BUFFER *rec);
void cdecl obj_release_buffers (void);

/* objdec07.c */ void cdecl scan_THEADR (struct RECORD_BUFFER *rec,
                   char *tit, int OM);
/* objdec08.c */ int cdecl obj_rd_name (char *source, char *dest);
/* objdec09.c */ int cdecl obj_rd2_name (char *source, char *dest, int cnt);
/* objdec10.c */ int cdecl rd_index (char *s, int *v);
/* objdec11.c */ int cdecl rd_number (char *v1, int *v2);
/* objdec12.c */ int cdecl rd_leaf_descriptor (char *s, long *v);
/* objdec13.c */ int cdecl calc_date_time (char *datim);
/* objdec14.c */ int cdecl create_objproc_version (struct RECORD_BUFFER *rec,
                   char *datim);
/* objdec15.c */ int cdecl calculate_checksum (char *s, int lng);
/* objdec16.c */ void cdecl print_ASM (char *title, struct DEF_NAME *np1,
                   struct DEF_SEG *sp, struct DEF_GRP *gp,
                   struct DEF_EXT *ep, struct DEF_PUB *pp);
/* objdec17.c */ int cdecl scan_LNAMES (struct RECORD_BUFFER *rec,
                   char *name, char *tit, char *fnm, int lnm_cnt, int OM);
/* objdec18.c */ void cdecl scan_COMENT (struct RECORD_BUFFER *rec,
                   char *name, int OM);
/* objdec19.c */ void cdecl scan_MODEND (struct RECORD_BUFFER *rec, int OM);
/* objdec20.c */ void cdecl scan_PUBDEF (struct RECORD_BUFFER *rec,
                   char *name, char *title, char *fnm, int en_crf, int OM);
/* objdec21.c */ void cdecl scan_EXTDEF (struct RECORD_BUFFER *rec,
                   char *name, char *title, char *fnm, int en_crf, int OM);
/* objdec22.c */ void cdecl scan_BSSNAM (struct RECORD_BUFFER *rec,
                   char *name, char *title, char *fnm, int en_crf, int OM);
/* objdec23.c */ int cdecl scan_SEGDEF (struct RECORD_BUFFER *rec,
                   int seg_cnt, int OM);
/* objdec24.c */ int cdecl scan_GRPDEF (struct RECORD_BUFFER *rec,
                   int grp_cnt, int OM);
/* objdec25.c */ int cdecl scan_TYPDEF (struct RECORD_BUFFER *rec,
                   int type_cnt, int OM);
/* objdec26.c */ void cdecl scan_LINNUM (struct RECORD_BUFFER *rec, int OM);
/* objdec27.c */ int cdecl print_LEX (FILE *fo, char *title,
                   struct DEF_EXT *ep, struct DEF_PUB *pp);
/* objdec28.c */ int cdecl print_feature_table (FILE *fo, char *title,
                   struct DEF_PUB *pp);
/* objdec29.c */ struct RECORD_BUFFER *cdecl obj_read_record (FILE *fi,
                   int akt_record_type, long pos);
#endif

#endif /* __GG_objdec__ */
