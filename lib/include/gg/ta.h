/*
 *  include FILE <gg/ta.h>
 *
 *  general textual analysis
 *  .  see also: <gg/parse.h>
 *
 *  written:       1990-11-10
 *  latest update: 1996-12-22 20:47:43
 *
 */

#ifndef __GG_ta__
#define __GG_ta__

#define DEBTA_100

#include <gg/attlist.h>         /* attribute lists must be defined!         */
#include <gg/signatur.h>        /* signatures must be defined!              */
#include <gg/floskel.h>

#ifndef int32
#define int32 long
#endif /* int32 */

/* ------------------------------------------------------------------------ */
struct TA_TAG
{
  long sig; 
  struct TA_TAG *TAtag_next;

  long TAtag_type;
#define TAtag_8BIT      1       /* node contains a character string         */
#define TAtag_16BIT     2       /* node contains a 16-bit character string  */
#define TAtag_32BIT     3       /* node contains a 32-bit character string  */

  struct TA_TAG *TAtag_related; /* this tag is related to other tag         */
  char *TAtag_relation;         /* relationship of these tags               */

  struct ATTRIBUTE_LIST *TAtag_attributes;
} ;

/* *** OBSOLETE *** ------------------------------------------------------- */
struct TA_TEXT
{
  int sig; 
  struct TA_TEXT *ta_next;

  struct TA_TAG *ta_tag;        /* type of the node:                        */
  long ta_cat_flags;            /* flags for category codes (TA_CATF_xxx)   */
  long ta_data_lng;             /* used space                               */
  long ta_data_size;            /* reserved space                           */

  char ta_data [2];             /* text segment                             */
} ;

/* constraints: - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/*   ta_data_lng < ta_data_size                                             */
/*   ta_data [ta_data_lng] = 0;                                             */

/* ------------------------------------------------------------------------ */
struct TA_OBJECT                /* describes a very general data object     */
{                               /* very similar to a markup structure       */
  int sig; 
  struct TA_OBJECT *TAO_next;
  long TAO_type;                /* defines the type of this object node     */
#define TAOT_object           0 /* TAO_body is another TA_OBJECT            */
#define TAOT_string           1 /* TAO_body is a string block               */
#define TAOT_tag              2 /* TAO_body is a TA_TAG structure           */
#define TAOT_text             3 /* TAO_body is a TA_TEXT structure          */
#define TAOT_other            4 /* any other contents type                  */
  struct TA_TAG *TAO_tag;
  long TAO_size;                /* size of the text block or other struct   */

  void *TAO_head;
  void *TAO_body;
  void *TAO_tail;
} ;

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
#define _TA_SOURCE_DEFINED
struct TA_SOURCE                /* describes a source object                */
{
  FILE *TAS_file;
  char *TAS_filename;
  long TAS_line_number;
  int TAS_is_eof;               /* EOF has been detected                    */
} ;
#endif

/* *** OBSOLETE *** ------------------------------------------------------- */
#ifdef JUNK
#define MAX_SEGMENT_BUFFER 1024
struct TA_SEGMENT_STATUS
{
  int TSS_last_cat_code;                /* undefined category code so far   */
  int TSS_buffer_size;                  /* number of chars in buffer        */
  long TSS_cat_flags;                   /* category flags of buffer         */

  char TSS_buffer [MAX_SEGMENT_BUFFER]; /* temporary data storage           */
} ;

/* ------------------------------------------------------------------------ */
struct TA_NODE_LIST_STATUS
{
  struct TEXT_ELEMENT *TNLS_nlist;
  struct TEXT_ELEMENT **TNLS_napp;
  long TNLS_ncnt;
} ;
#endif /* JUNK */

#define MAX_BUFFERED_NODES 4096

/* ------------------------------------------------------------------------ */
#define TA_CAT_CODES          25
#define TA_CAT_control1        1
#define TA_CAT_control2        2
#define TA_CAT_small           3
#define TA_CAT_capital         4
#define TA_CAT_digit           5
#define TA_CAT_nat_small       6
#define TA_CAT_nat_capital     7
#define TA_CAT_nat_currency    8
#define TA_CAT_greek           9
#define TA_CAT_graphic        10
#define TA_CAT_math1          11
#define TA_CAT_math2          12
#define TA_CAT_sond1          13
#define TA_CAT_sond2          14
#define TA_CAT_sond3          15
#define TA_CAT_nat_satz       16
#define TA_CAT_satz1          17
#define TA_CAT_satz2          18
#define TA_CAT_satz3          19
#define TA_CAT_satz4          20
#define TA_CAT_space1         21
#define TA_CAT_space2         22
#define TA_CAT_space3         23
#define TA_CAT_ligature       24

#define TA_CATF_none           0x00000000L
#define TA_CATF_control1       0x00000001L
#define TA_CATF_control2       0x00000002L
#define TA_CATF_control        0x00000003L
#define TA_CATF_small          0x00000004L
#define TA_CATF_capital        0x00000008L
#define TA_CATF_letter         0x0000000CL      /* small | capital          */
#define TA_CATF_digit          0x00000010L
#define TA_CATF_nat_small      0x00000020L
#define TA_CATF_nat_capital    0x00000040L
#define TA_CATF_nat_letter     0x00000060L      /* nat small | capital      */
#define TA_CATF_nat_currency   0x00000080L
#define TA_CATF_greek          0x00000100L
#define TA_CATF_graphic        0x00000200L
#define TA_CATF_math1          0x00000400L
#define TA_CATF_math2          0x00000800L
#define TA_CATF_sond1          0x00001000L
#define TA_CATF_sond2          0x00002000L
#define TA_CATF_sond3          0x00004000L
#define TA_CATF_nat_satz       0x00008000L
#define TA_CATF_satz1          0x00010000L
#define TA_CATF_satz2          0x00020000L
#define TA_CATF_satz3          0x00040000L
#define TA_CATF_satz4          0x00080000L
#define TA_CATF_satz           0x000F8000L      /* satz 1|2|3|4|nat         */
#define TA_CATF_space1         0x00100000L
#define TA_CATF_space2         0x00200000L
#define TA_CATF_space3         0x00400000L
#define TA_CATF_space          0x00700000L      /* space 1 | 2 | 3          */
#define TA_CATF_ligature       0x00800000L
#define TA_CATF_other          0x80000000L

#define BREAK_DEFAULT_init     0x06

#define N_PAR_TYPE              5
#define PAR_TYPE_text           0
#define PAR_TYPE_section_head   1
#define PAR_TYPE_table_head     2
#define PAR_TYPE_figure_head    3
#define PAR_TYPE_chapter        4

/* prototypes: ------------------------------------------------------------ */
/* ta001.c */   extern struct TA_TAG TA_TAG_8BIT;
                extern struct TA_TAG TA_TAG_16BIT;
                extern struct TA_TAG TA_TAG_32BIT;
                extern struct TA_TAG *TA_TAG_LIST;
                extern struct TA_TAG **TA_TAG_APPEND;

/* ta005.c */   struct TA_TEXT *cdecl ta_get_new_node (
                  struct TA_TAG *tag_code, long data_size);
                int cdecl ta_free_node (struct TA_TEXT *node);

/* ta006.c */   long cdecl ta_get_new_id_code (void);
/* ta007.c */   int cdecl ta_read_setup (char *fn);
/* ta008.c */   void cdecl ta_reset_cat_names (void);
                int cdecl ta_get_cat_name (char *s, int mode);

/* ta010.c */   int cdecl ta_free_node_list (struct TA_TEXT *nlist);
/* ta012.c */   int cdecl ta_identify_par_type (struct TEXT_ELEMENT *li);

#ifdef _FILE_DEFINED
                int cdecl ta_print_paragraph (FILE *fo,
                  struct TEXT_ELEMENT *li, long ncnt);
                int cdecl ta_print_nodelist (FILE *fo,
                  struct TEXT_ELEMENT *li, long ncnt, int par_type);
                int cdecl ta012_finish (FILE *fo);
                int cdecl ta_print_toc (FILE *fo, char *frame_name);

/* ta015.c */   int cdecl hyx_ta_print_text_segments (FILE *fo,
                  struct TEXT_SEGMENT *ts);
#endif /* _FILE_DEFINED */

/* ta016.c */   struct HYX_PARSER_STATUS *cdecl ta_collect_init (void);

/* ta019.c */   struct HYX_PARSER_STATUS *ta_create_node_list (void);
/* ta020.c */   int cdecl hyx_ta_flush_node_list (
                  struct HYX_PARSER_STATUS *hps);
/* ta021.c */   int cdecl ta_collect_node (struct HYX_PARSER_STATUS *hps,
                  struct TEXT_ELEMENT *node);

#ifdef _TA_SOURCE_DEFINED
/* ta101.c */   struct TA_OBJECT *cdecl tao_rd_sgml_body (
                  struct TA_SOURCE *source);
#endif /* _TA_SOURCE_DEFINED */

/* ta102.c */   struct TA_OBJECT *cdecl tao_mk_string (char *str, int size);
/* tax01.c */   void cdecl ta_transmit_mode (int mode);
                int cdecl ta_transmit_node (
                  struct HYX_PARSER_STATUS *hps,
                  struct TEXT_ELEMENT *node);

#endif /* __GG_ta__ */
