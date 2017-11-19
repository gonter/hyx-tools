/*
 *  include FILE <gg/parse.h>
 *
 *  HYX SGML Parser System
 *
 *  - notes: about a restructuration
 *  - methods
 *  - structures:
 *      TAG_DEFINITION, TEXT_SEGMENT, TEXT_ELEMENT,
 *      MARKUP, HYX_PARSER_STATUS, ENTRY_DESCRIPTOR, ENTRY_QUEUE,
 *      LEXICON_GLOBAL_CONTROL, LEXICON_CONTROL, LEXICON_INDEX,
 *      LEX_SESSION, HYX_OUTPUT_DESCRIPTOR
 *  - macros
 *  - prototypes
 *
 *  written:       1991 03 11
 *  latest update: 1997-11-02 23:29:38
 *  $Id: parse.h,v 1.6 2004/05/08 15:45:04 gonter Exp $
 *
 */

#ifndef __GG_parse__
#define __GG_parse__

#include <gg/attlist.h>         /* attribute lists must be defined!         */
#include <gg/signatur.h>        /* signatures must be defined!              */
#include <gg/floskel.h>

/* #define PARSER_DEBUG 1   */  /* debugging level                          */
/* #define PARSER_DEBUG_B 1 */

/* limits: ---------------------------------------------------------------- */
#ifdef MSDOS
#define ENTRY_KEY_SIZE 128
#define QUEUE_SIZE 128
#else
#define ENTRY_KEY_SIZE 512
#define QUEUE_SIZE 4096
#endif

/* ------------------------------------------------------------------------ */
struct TAG_DEFINITION           /* Beschreibung eines Tags                  */
{
  long sig;                     /* Signatur: SIG_TAG_DEFINITION             */
  struct TAG_DEFINITION
    *TAG_DEF_next;              /* Verkettung (ungluecklicher Umstaende...) */
  char *tag_name;               /* Name des Tags                            */
  long tag_id;                  /* ID Code des Tags; siehe <gg/sgml.h>      */
  int  match_mode;              /* Art des Tag Name Vergleichs              */
  int  tag_type;                /* Art des Tags                             */
  long tag_weight;              /* Wichtung des Tags                        */
  char *tag_comment;            /* comment about that tag, if present       */
} ;

#define TAG_TYPE_recursive     1
#define TAG_TYPE_nonrecursive  2
#define TAG_TYPE_endtag        3
#define TAG_TYPE_autonomous    4
#define TAG_TYPE_HTML          5

/* ------------------------------------------------------------------------ */
struct TEXT_SEGMENT             /* logisch zusammenhaengender Textabschnitt */
{                               /* ... fragmentiert in einzelne Segmente    */
  long sig;                     /* Signatur: SIG_TEXT_SEGMENT               */
  struct TEXT_SEGMENT *TSEG_next;
  long TSEG_text_lng;           /* Laenge des verwendeten Textes            */
  char TSEG_text_array [2];     /* abgespeicherter Text                     */
} ;

/* ------------------------------------------------------------------------ */
struct TEXT_ELEMENT             /* textliches Element: entweder getaggter   */
{                               /* Text oder Tag-Text                       */
  long sig;                     /* Signatur: SIG_TEXT_ELEMENT               */
  struct TEXT_ELEMENT *TE_next;

  int TE_type;                  /* what kind of element there is            */
#define TEt_text             0  /* element is a piece of normal text        */
#define TEt_tag              1  /* element is a tag                         */
#define TEt_declaration      2  /* element contains a declaration           */
#define TEt_processing       3  /* element contains processing instructions */

  char *TE_tag_name;            /* Tag Name                                 */
  struct ATTRIBUTE_LIST
    *TE_attributes;
  struct TEXT_SEGMENT           /* Folge von logischen zusammenhaengenden   */
    *TE_text_segment;           /* Text Segmenten                           */
  struct TAG_DEFINITION         /* Tag Definition, sobald diese bekannt ist */
    *TE_tag_definition;

  long TE_level;                /* level==0: (getaggter) Text               */
                                /* level==1: Text innerhalb von <..>        */
                                /* sonst:    z.Z. nicht vorgesehen!!!       */
  long TE_link_count;           /* number of references to this element     */
  long TE_cat_flags;
  long TE_text_lng;             /* Laenge aller Textsegmente                */

} ;

/* BEGIN 1995-12-21 10:52:19 ---------------------------------------------- */
struct ATTRIBUTE_DECLARATION_LIST
{
  struct ATTRIBUTE_DECLARATION_LIST *ADL_next;

  char *ADL_name;
  struct TEXT_ELEMENT *ADL_te;
} ;

/* ------------------------------------------------------------------------ */
struct ELEMENT_DECLARATION
{
  char *ED_name;
  int ED_omit_start_tag;        /* 1 -> start tag is omissible              */
  int ED_omit_end_tag;          /* 1 -> end tag is omissible                */

  struct ATTRIBUTE_DECLARATION_LIST *ED_adl;
  struct TEXT_ELEMENT *ED_te;
} ;

/* ------------------------------------------------------------------------ */
struct ELEMENT_DECLARATION_LIST
{
  struct ELEMENT_DECLARATION_LIST *EDL_next;
  struct ELEMENT_DECLARATION *EDL;
} ;
/* END 1995-12-21 10:52:19 ------------------------------------------------ */

/* ------------------------------------------------------------------------ */
struct MARKUP                   /* logisch zusammengehoeriger Abschnitt     */
{                               /* Textes; mit Start Tag und End Tag        */
  long sig;                     /* Markus Signatur: SIG_MARKUP              */
  struct MARKUP *M_next;        /* guess what?                              */
  struct TAG_DEFINITION *tag_definition; /* TAG des Start Tags              */
  struct TEXT_ELEMENT *tag_open;    /* Start Tag mit allem drum und dran    */
  struct TEXT_ELEMENT *tagged_text; /* in der Liste des getaggten Text      */
                                    /* koennen auch wieder Markups sein     */
  struct TEXT_ELEMENT *tag_close;   /* End Tag                              */
} ;
/* Anmerkung: Start Tag und End Tag koennen unter Umstaenden ausgelassen    */
/* werden. Die Art des Markups wird in von irgendeiner Prozessorstufe       */
/* in struct TAG_DEFINITION *tag_definition eingetragen, sodass die Art     */
/* des Markups ersichtlich ist.                                             */

/* ------------------------------------------------------------------------ */
struct HYX_PARSER_CONTEXT               /* pushed parser status             */
{                                       /* this is a stack!!!               */
                                        /* used for recursive SGML structs  */
  struct HYX_PARSER_CONTEXT *HPC_next;  /* next context frame in stack      */

  int HPC_state;
} ;

/* ------------------------------------------------------------------------ */
struct HYX_PARSER_CLASS                 /* definitions about the parser in  */
{                                       /* a meta level                     */
  /* content model and tag definitions */
  struct TAG_DEFINITION *HPC_tag_list;
  struct TAG_DEFINITION **HPC_tag_append;

  struct YTREE *HPC_tags;
  /* note: the hash list for tag names can be used if exact tag names are   */
  /*       searched                                                         */


  /* DTD Class Options */
  int HPC_tag_open;                     /* tag open character               */
  int HPC_tag_close;                    /* tag close character              */
  int HPC_entity_open;                  /* enitity open character           */
  int HPC_entity_close;                 /* enitity close character          */
  int HPC_declaration_start;            /* mdo char                         */
  int HPC_processing_start;             /* processing instr. start          */
  int HPC_minimization_char;            /* character used for minimization  */

  char *HPC_entity_tag_open;            /* string to use as tag open entity */
  char *HPC_entity_tag_close;
  char *HPC_entity_entity_open;

  /* processing options                                                     */
  int HPC_po_strip;                     /* strip text segments              */
  int HPC_po_id_tag;                    /* identify tag                     */

  /* runtime characteristics */
  long HPC_next_tag_id;

  /* statistics */
  long HPC_TAG_DEFINITION_allocated;
  int HPC_debug_flags;
  int HPC_meta_flags;
#define HPC_META_HTML            0x0001
#define HPC_META_show_new_tags   0x0002
} ;

/* ------------------------------------------------------------------------ */
struct HYX_PARSER_STATUS
{
  struct HYX_PARSER_CLASS *HPS_hpc;     /* DTD class options                */

  long HPS_segment_length;              /* number of bytes in segment sofar */
  long HPS_parser_level;                /* 0: currently processing text     */
                                        /* 1: currently processing tag      */

  int HPS_level_changed;                /* switch from tag to text or back  */


#define MAX_SEGMENT_LENGTH 2048
  char HPS_segment [MAX_SEGMENT_LENGTH];/* buffer for new text segment      */

  struct TEXT_ELEMENT *HPS_tx_last;     /* last created text element list   */
  struct TEXT_ELEMENT *HPS_tx_list;     /* newly created text element list  */
  struct TEXT_ELEMENT **HPS_ptx;        /* append possition to list         */
  struct TEXT_SEGMENT **HPS_ptxs;       /* append possition for *segments*  */
  int HPS_text_alloc_flag;              /* text element already allocated   */

  int HPS_minimization_seen;            /* text is within minimization      */
  int HPS_white_spaces;                 /* number of white spaces seen      */

  /* items from <gg/ta.h> */
  int HPS_last_cat_code;                /* last text category code          */
  long HPS_cat_flags;                   /* text category flags              */
  long HPS_tx_cnt;                      /* number of elements in tx_list    */

  int HPS_element_type;                 /* type of TEXT_ELEMENT             */

  /* operation state for recursive SGML strutures                           */
  int HPS_state;                        /* opaque state identifier          */
  struct HYX_PARSER_CONTEXT *HPS_ctx;   /* context frame pointer            */
  int HPS_cnt;                          /* context frame counter            */

  int HPS_other_quote;
} ;

/* ------------------------------------------------------------------------ */
struct ENTRY_DESCRIPTOR         /* information about an lexicon entry       */
{                               /* while processed in memory                */
  struct TEXT_ELEMENT *ED_te;   /* data of lexicon entry                    */
  long ED_index;                /* index of lexicon entry                   */
  char *ED_frame_name;          /* strdup'ed name of the frame              */
  int ED_status;
#define ED_stat_is_new   0
#define ED_stat_from_LUT 1      /* Entry was generated while processing     */
                                /* a YTREE node, it was read from a LUT     */
                                /* or XFN file.                             */
} ;

/* ------------------------------------------------------------------------ */
struct ENTRY_QUEUE
{
  struct ENTRY_QUEUE *EQ_next;          /* list to form the queue           */
  struct ENTRY_DESCRIPTOR *EQ_ed;
  int EQ_is_dirty;
} ;

/* ------------------------------------------------------------------------ */
struct LEXICON_GLOBAL_CONTROL           /* see also HYX_CLUSTER_CONTROL     */
{
  /* entry queue: - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  int LGC_queue_size;                   /* max number of elements allowed   */
                                        /* in queue, flush if more in q.    */
  int LGC_EQ_count;                     /* number of elements already in q. */
  struct ENTRY_QUEUE *LGC_EQ_first;     /* begin of the queue               */
  struct ENTRY_QUEUE **LGC_EQ_append;   /* position to append to queue      */
} ;

/* ------------------------------------------------------------------------ */
struct LEXICON_CONTROL                  /* see also HYX_CLUSTER_CONTROL     */
{
  struct LEXICON_GLOBAL_CONTROL *LC_lgc;

  /* processing options:  - - - - - - - - - - - - - - - - - - - - - - - - - */
  int LC_do_strip;                      /* strip white space in text        */
                                        /* NOTE: in tags, always strip      */
  int LC_write_nl;                      /* write LF after text              */

  int LC_end_tag_count;
#define MAX_LC_END_TAGS 8
  long LC_end_tags [MAX_LC_END_TAGS];

  char *LC_head_tag_str;                /* tag to be added to entry         */
  char *LC_tail_tag_str;                /* tag to be appended to entry      */
} ;

/* ------------------------------------------------------------------------ */
struct LEXICON_INDEX
{
  long LEXI_begin;              /* begin offset of entry in the cluster     */
  long LEXI_end;                /* end offset                               */
  long LEXI_cluster_number;     /* number of the cluster                    */
} ;

/* ------------------------------------------------------------------------ */
#ifdef _HYX_CLUSTER_CONTROL_DEFINED
struct LEX_SESSION
{
  struct HYX_CLUSTER_CONTROL *LEXS_hcc;
  struct LEXICON_CONTROL *LEXS_lcc;
  struct HYX_PARSER_CLASS *LEXS_hpc;
  struct HYX_PARSER_STATUS *LEXS_hps;
  long LEXS_record_counter;
  struct TEXT_ELEMENT *LEXS_tx_new_entry;
} ;
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */

/* methods: --------------------------------------------------------------- */
typedef int hyx_output_processor (void *cd, struct TEXT_ELEMENT *te);

/* ------------------------------------------------------------------------ */
struct HYX_OUTPUT_DESCRIPTOR
{
  long HOD_signature;           /* SIG_OUTPUT_DESCRIPTOR */

  char *HOD_buffer;
  int HOD_buffer_size;
  int HOD_buffer_index;

  void *HOD_client_data;
  hyx_output_processor *HOD_output_processor;
  /* HOD_output_processor's argument is a HYX_OUTPUT_DESCRIPTOR structure!  */
} ;

/* Lexicon Tag IDs: ------------------------------------------------------- */
#define LEX_sTAG_LE     0x0201
#define LEX_eTAG_LE     0x0202
#define LEX_sTAG_LM     0x0203
#define LEX_eTAG_LM     0x0204
#define LEX_sTAG_LX     0x0205
#define LEX_eTAG_LX     0x0206

/* DICTADD operation modes: ----------------------------------------------- */
#define DAMODE_MERGE    0       /* merge entry with new one                 */
#define DAMODE_REPLACE  1       /* replace entry by new one                 */
#define DAMODE_DIVIDE1  2       /* divide according to one key char         */
#define DAMODE_DIVIDE2  3       /* divide according to two key chars        */
#define DAMODE_DIVIDE3  4       /* divide according to three key chars      */
#define DAMODE_LOOKUP   5       /* just get the entry from the lexicon      */
#define DAMODE_CHECK    9       /* check: test new entries                  */

/* DICTADD frame name modes: ---------------------------------------------- */
#define DAFNM_md5       0       /* generate MD5 string for frame name       */
#define DAFNM_entry_key 1       /* use entry key as frame name              */
#define DAFNM_index     2       /* use index as frame name                  */

/* macros: ---------------------------------------------------------------- */
#define hyx_new_lexicon_control() \
  ((struct LEXICON_CONTROL *) calloc (sizeof (struct LEXICON_CONTROL), 1))

#define hyx_new_lexicon_global_control() \
  ((struct LEXICON_GLOBAL_CONTROL *)    \
  calloc (sizeof (struct LEXICON_GLOBAL_CONTROL), 1))

#define hyx_new_entry_queue() \
  ((struct ENTRY_QUEUE *) calloc (sizeof (struct ENTRY_QUEUE), 1))

#define hyx_new_markup() \
  ((struct MARKUP *) calloc (sizeof (struct MARKUP), 1))

#define hyx_new_tag_definition() \
  ((struct TAG_DEFINITION *) calloc (sizeof (struct TAG_DEFINITION), 1))

#define hyx_new_parser_class() \
  ((struct HYX_PARSER_CLASS *) calloc (sizeof (struct HYX_PARSER_CLASS), 1))

#define hyx_new_parser_status() \
  ((struct HYX_PARSER_STATUS *) calloc (sizeof (struct HYX_PARSER_STATUS), 1))

/* prototypes: ------------------------------------------------------------ */
#ifdef _FILE_DEFINED
/* parse007.c */ void cdecl print_text_element_list (FILE *fo,
                   struct TEXT_ELEMENT *t);
/* parse008.c */ int cdecl print_text_segment_list (FILE *fo,
                   struct TEXT_SEGMENT *ts);
/* parsd008.c */ int cdecl diag_print_text_segment_list (FILE *fo,
                   struct TEXT_SEGMENT *ts);
#endif /* _FILE_DEFINED */
/* parse014.c */ int cdecl key_string_transform (char *s, int lng);
#ifdef _FILE_DEFINED
/* parse016.c */ void display_text_element (FILE *fo,
                   struct TEXT_ELEMENT *t, char *txt, int strip);
/* parsd016.c */ void cdecl display_markup (FILE *fo,
                   struct HYX_PARSER_CLASS *hpc,
                   struct TEXT_ELEMENT *t, int indent, int verbosity,
                   int append_eoln, int strip);
/* parsd016.c */ void diag_display_text_element (FILE *fo,
                   struct TEXT_ELEMENT *t, char *txt, int strip);
/* parsd016.c */ void cdecl diag_display_markup (FILE *fo,
                   struct HYX_PARSER_CLASS *hpc,
                   struct TEXT_ELEMENT *t, int indent, int verbosity,
                   int append_eoln, int strip);
/* parse017.c */ void cdecl display_tag_definition (FILE *fo,
                   struct TAG_DEFINITION *td);
#endif /* _FILE_DEFINED */
/* parse019.c */ int cdecl parse_tag_sequence (char *tag_str,
                   char *parse_string_array, char *pt_array [],
                   int pt_type [], int pt_max);
#define TAG_ITEM_TAG            1
#define TAG_ITEM_PARAMETER      2
#define TAG_ITEM_ATTR_NAME      3
#define TAG_ITEM_ATTR_VALUE     4

#ifdef _FILE_DEFINED
/* parse021.c */ void cdecl dump_text_element_list (FILE *fo,
                   struct TEXT_ELEMENT *t);
/* parse022.c */ int dump_text_segment_list (FILE *fo,
                   struct TEXT_SEGMENT *ts);
#endif /* _FILE_DEFINED */

/* ------------------------------------------------------------------------ */
#ifdef _HYX_CLUSTER_CONTROL_DEFINED
/* dictadd1.c */ int cdecl dict_add_file (
                   struct HYX_PARSER_CLASS *hpc,
                   struct HYX_CLUSTER_CONTROL *hcc,
                   struct LEXICON_CONTROL *lcc, char *fn, int verbose_level);
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */

/* dictadd2.c */ long cdecl dict_restructure_new_entry (
                   struct HYX_PARSER_CLASS *hpc,
                   struct TEXT_ELEMENT **tx_list, char *key_string,
                   int key_string_length, int do_strip,
                   struct TEXT_ELEMENT *insert_head,
                   struct TEXT_ELEMENT *insert_tail);

#ifdef _HYX_CLUSTER_CONTROL_DEFINED
/* dictadd3.c */ int cdecl dict_update_entry (
                   struct HYX_PARSER_CLASS *hpc,
                   struct HYX_CLUSTER_CONTROL *hcc,
                   struct LEXICON_CONTROL *lcc, char *frame_name,
                   struct TEXT_ELEMENT *tx_new_entry,
                   hyx_output_processor *op, void *op_client_data,
                   int verbose_level);
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */

/* dictadd4.c */ int cdecl write_lexicon_entry (char *lexicon_file,
                   char *index_file, long *framme_index, char *entry_key,
                   struct TEXT_ELEMENT *lexicon_entry,
                   long *next_index, int write_nl);
#ifdef _FILE_DEFINED
/* dictadd6.c */ int cdecl write_lexicon_text (FILE *fhyx,
                   struct TEXT_ELEMENT *le, int write_nl);
#endif /* _FILE_DEFINED */
/* dictadd8.c */ int cdecl dict_purge_entry (struct TEXT_ELEMENT **tx_list,
                   long purge_tags [], int purge_tags_flags [],
                   int purge_tags_cnt);
/* dictadd9.c */ int cdecl dict_combine_entries (struct TEXT_ELEMENT **tx_old,
                   struct TEXT_ELEMENT **tx_new);

/* ------------------------------------------------------------------------ */
/* dict0001.c */ char *cdecl get_divided_lexicon (char *base_name,
                   int divide_mode, char *entry_key);

/* dict0002.c */ int cdecl dict_check_integrity (
                   struct HYX_PARSER_CLASS *hpc);

#ifdef _FILE_DEFINED
/* dict0003.c */ int cdecl write_lexicon_frame (FILE *fhyx, char *frame_name,
                   struct TEXT_ELEMENT *lexicon_entry, int write_nl);
#endif /* _FILE_DEFINED */

#ifdef _HYX_CLUSTER_CONTROL_DEFINED
/* dict0004.c */ int cdecl dict_add_init (struct HYX_CLUSTER_CONTROL *hcc);
/* dict0005.c */ int cdecl dict_add_finish (struct HYX_CLUSTER_CONTROL *hcc,
                   struct LEXICON_CONTROL *lcc);
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */

#ifdef _FILE_DEFINED
/* dict0006.c */ void cdecl memory_statistics (FILE *fo, long record_counter);
#endif /* _FILE_DEFINED */

#ifdef _YTREE_DEFINED
/* dict0007.c */ int cdecl ytree_index_to_entry_descriptor (
                   struct YTREE *yt_node, void *client_data);
/* dict0008.c */ int cdecl ytree_entry_descriptor_to_index (
                   struct YTREE *yt_node, void *client_data);
#endif /* _YTREE_DEFINED */

/* dict0009.c */ int cdecl dict_queue (struct LEXICON_CONTROL *lcc,
                   struct ENTRY_DESCRIPTOR *ed, int mark_dirty);
#ifdef _HYX_CLUSTER_CONTROL_DEFINED
/* dict0010.c */ int cdecl dict_flush_queue (struct HYX_CLUSTER_CONTROL *hcc,
                   struct LEXICON_CONTROL *lcc);
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */

#ifdef _YTREE_DEFINED
/* dict0011.c */ int cdecl dict_write_xfn_entry (struct YTREE *yt_node,
                   void *client_data);
#endif /* _YTREE_DEFINED */

#ifdef _HYX_CLUSTER_CONTROL_DEFINED
/* dict0012.c */ int cdecl dict_read_setup_file (
                   struct HYX_CLUSTER_CONTROL *hcc, char *fn,
                   char *line, int MAX_LINE, char **tag_definition);
/* dict0013.c */ char *cdecl dict_get_frame_name (
                   struct HYX_CLUSTER_CONTROL *hcc,
                   char *entry_key, char *index_str);
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */

/* dict0014.c */ long cdecl dict_restructure2_entry (
                   struct HYX_PARSER_CLASS *hpc,
                   struct LEXICON_CONTROL *lcc,
                   struct TEXT_ELEMENT **tx_new_entry,
                   char *entry_key, int entry_key_size);

#ifdef _HYX_CLUSTER_CONTROL_DEFINED
/* dict0015.c */ int cdecl dict_process_entry (
                   struct HYX_PARSER_CLASS *hpc,
                   struct HYX_CLUSTER_CONTROL *hcc,
                   struct LEXICON_CONTROL *lcc,
                   struct TEXT_ELEMENT *tx_new_entry,
                   hyx_output_processor *op, void *op_client_data,
                   int verbose_level);
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */

#ifdef _DYNAMIC_BLOCK_DEFINED
/* dict0016.c */ int cdecl hyx_unroll_text (struct DYNAMIC_BLOCK *dyb,
                   struct TEXT_ELEMENT *t, int indent, int verbosity,
                   int append_eoln);
/* dict0017.c */ /* unroll tag defintion */
/* dict0018.c */ int cdecl hyx_unroll_text_segment_list (
                   struct DYNAMIC_BLOCK *dyb, struct TEXT_SEGMENT *ts);
#endif /* _DYNAMIC_BLOCK_DEFINED */

/* %ds/hyxp/ hyx parser package: ------------------------------------------ */
/* hyxp0001.c */ struct HYX_PARSER_STATUS *cdecl hyx_parser_reset (
                   struct HYX_PARSER_CLASS *hpc);
/* hyxp0002.c */ struct TEXT_ELEMENT *cdecl hyx_parse_char (
                   struct HYX_PARSER_STATUS *lps, int ch);
#define hyx_parser_get_text_list(lps) ((lps)->HPS_tx_list)

/* hyxp0003.c */ int cdecl hyx_parse2_char (struct HYX_PARSER_STATUS *hps,
                   struct TEXT_ELEMENT **le, int ch, long end_tags [],
                   int end_tag_count);

#ifdef _FILE_DEFINED
/* hyxp0004.c */ int cdecl hyx_parse1_file (struct HYX_PARSER_CLASS *hpc,
                   FILE *fhyx, struct TEXT_ELEMENT **le, long end_tags[],
                   int end_tag_count, long max_to_read, long *bytes_read);
/* hyxp0005.c */ int cdecl hyx_parse2_file (
                   struct HYX_PARSER_STATUS *hps,
                   FILE *fhyx, struct TEXT_ELEMENT **le, long end_tags[],
                   int end_tag_count, long max_to_read, long *bytes_read);
#endif /* _FILE_DEFINED */

/* hyxp0006.c */ int cdecl hyx_parse1_string ( struct HYX_PARSER_CLASS *hpc,
                   char *str, struct TEXT_ELEMENT **le, long end_tags [],
                   int end_tag_count, long max_to_read, long *bytes_read);

/* hyxp0007.c */ int cdecl hyx_parse2_string (
                   struct HYX_PARSER_STATUS *hps,
                   char *str, struct TEXT_ELEMENT **le, long end_tags [],
                   int end_tag_count, long max_to_read, long *bytes_read);
/* hyxp0008.c */ int cdecl hyx_parse2_block (struct HYX_PARSER_STATUS *hps,
                   char *str, struct TEXT_ELEMENT **le, long end_tags [],
                   int end_tag_count, long max_to_read, long *bytes_read);
/* hyxp0009.c */ struct TEXT_SEGMENT *cdecl hyx_mktx_segm (char *s,
                   long lng);
/* hyxp0010.c */ struct TEXT_ELEMENT *cdecl hyx_mktx_elem (long lev, int typ);
/* hyxp0011.c */ struct TEXT_ELEMENT *cdecl hyx_mktx_elem_and_segm (
                   struct HYX_PARSER_CLASS *hpc, char *str, long lng,
                   long level, int typ, int get_tag_def, int append);
/* hyxp0012.c */ int cdecl hyx_frtx_elem_list (
                   struct TEXT_ELEMENT *t1);
/* hyxp0013.c */ int cdecl hyx_frtx_segm_list (
                   struct TEXT_SEGMENT *ts1);
/* hyxp0014.c */ int cdecl hyx_strip_text_elem (struct TEXT_ELEMENT *t);
/* hyxp0015.c */ struct MARKUP *cdecl hyx_make_markup (
                   struct HYX_PARSER_CLASS *hpc, void *start_tag,
                   void *marked_text, void *stop_tag,
                   struct TAG_DEFINITION *tag_def, int flags);
/* hyxp0016.c */ int cdecl hyx_text_to_markup (
                   struct HYX_PARSER_CLASS *hpc,
                   struct TEXT_ELEMENT *tx_list, struct MARKUP **pmarkup);

/* hyxp0017.c */ int cdecl hyx_copy_tx_segm_list (char *dest, int size,
                   struct TEXT_SEGMENT *ts);
/* hyxp0018.c */ struct TEXT_ELEMENT *cdecl hyx_append_tx_elem_list (
                   struct TEXT_ELEMENT **d, struct TEXT_ELEMENT *s);
/* hyxp0019.c */ struct TEXT_ELEMENT **cdecl hyx_find_last_tx_elem_ptr (
                   struct TEXT_ELEMENT **d);
/* hyxp0020.c */ long cdecl hyx_tx_segm_count_char (
                   struct TEXT_SEGMENT *ts, int code);
/* hyxp0021.c */ struct TEXT_ELEMENT *cdecl hyx_parse_block (
                   struct HYX_PARSER_STATUS *lps,
                   char *block, long size);
/* hyxp0022.c */ struct TEXT_ELEMENT *cdecl hyx_parse_string (
                   struct HYX_PARSER_STATUS *lps, char *string);

/* hyxp0023.c */ int cdecl hyx_parse_hyx_frame (
                   struct HYX_PARSER_CLASS *hpc,
                   char *lexicon_file,
                   char *index_file, long frame_index,
                   struct TEXT_ELEMENT **lexicon_entry,
                   long end_tags [], int num_end_tags);

#ifdef _FILE_DEFINED
/* hyxp0024.c */ int cdecl hyx_parse_hyx_frame_file (
                   struct HYX_PARSER_CLASS *hpc,
                   FILE *fhyx, FILE *fidx,
                   long frame_index, struct TEXT_ELEMENT **lexicon_entry,
                   long end_tags [], int num_end_tags);
#endif /* _FILE_DEFINED */

/* hyxp0025.c */ int cdecl hyx_transfer_details (
                   struct HYX_PARSER_STATUS *hps, struct TEXT_ELEMENT *tt);
/* hyxp0026.c */ int cdecl hyx_parser_add_char (
                   struct HYX_PARSER_STATUS *lps, int ch);
/* hyxp0027.c */ struct TEXT_ELEMENT *cdecl hyx_parser_finish (
                   struct HYX_PARSER_STATUS *hps);
/* hyxp0028.c */ struct TEXT_SEGMENT *cdecl hyx_parser_finish_segment (
                    struct HYX_PARSER_STATUS *lps);
/* hyxp0029.c */ struct HYX_PARSER_CLASS *cdecl hyx_init_parser_class (void);

/* hyxp0030.c */ int cdecl hyx_read_tag_definition (
                   struct HYX_PARSER_CLASS *hpc, char *fn);
/* hyxp0031.c */ int cdecl hyx_process_tag_definition (
                   struct HYX_PARSER_CLASS *hpc, char *line);
/* hyxp0032.c */ struct TAG_DEFINITION *cdecl hyx_identify_tag (
                   struct HYX_PARSER_CLASS *hpc, char *str, int append);
                 int hyx_copy_tag (char *src, char *dst, int size, int lower);
/* hyxp0033.c */ struct TAG_DEFINITION *cdecl hyx_make_tag_definition (
                   struct HYX_PARSER_CLASS *hpc, char *str, long id,
                   int mm, long weight, int ty, char *comment);
/* hyxp0034.c */ struct TAG_DEFINITION *cdecl hyx_find_tag_definition (
                   struct HYX_PARSER_CLASS *hpc, char *str);
/* hyxp0035.c */ long cdecl hyx_get_tag_definition (
                   struct HYX_PARSER_CLASS *hpc, struct TEXT_ELEMENT *tx,
                   int append);

/* hyx ta parser package: ------------------------------------------------- */
/* hyxta001.c */ int cdecl hyx_ta_parse_char (struct HYX_PARSER_STATUS *hps,
                   int ch, struct TEXT_ELEMENT **generated_node);
/* hyxta002.c */ int cdecl hyx_ta_parse_flush (
                   struct HYX_PARSER_CLASS *hpc,
                   struct HYX_PARSER_STATUS *hps,
                   struct TEXT_ELEMENT **generated_node);

/* hyxta003.c */ int cdecl hyx_ta_get_break_code (int last_cat_code,
                   int act_cat_code);
                 int cdecl hyx_ta_break_table_init (int mode);
                 void cdecl hyx_ta_break_table_dump (char *s);
                 void cdecl hyx_ta_break_table_overlay (int pairs [],
                   int cnt, int code);
                 int cdecl hyx_ta_set_break_code (int last_cat_code,
                   int act_cat_code, int code);

/* hyxta004.c */ long cdecl hyx_ta_get_cat_flags (int cat);
                 int cdecl hyx_ta_set_cat_flags (int cat, long catf);
/* hyxta005.c */ long cdecl hyx_ta_parse_file (struct HYX_PARSER_STATUS *hps,
                   char *fn, long pos_offset, long max_to_read);

#ifdef _FILE_DEFINED
/* hyxta006.c */ long cdecl hyx_ta_parse_stream (
                   struct HYX_PARSER_CLASS *hpc,
                   struct HYX_PARSER_STATUS *hps,
                   FILE *fi, long max_to_read);
#endif /* _FILE_DEFINED */

/* hyxta007.c */ int cdecl hyx_ta_store_node (
                   struct HYX_PARSER_CLASS *hpc,
                   struct HYX_PARSER_STATUS *hps,
                   struct TEXT_ELEMENT *node);
/* hyxta008.c */ struct TAG_DEFINITION *cdecl hyx_ta_find_tag_definition (
                   struct HYX_PARSER_CLASS *hpc,
                   long cat_flags);

#endif /* __GG_parse__ */
