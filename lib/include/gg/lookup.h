/*
 *  include FILE <gg/lookup.h>
 *
 *  using the Look Up Table (LUT)
 *  * macro functions
 *  * prototypes
 *
 *  related information:
 *  * <gg/ytree.h>
 *  * <gg/ztree.h>
 *  * LMD-Engine
 *
 *  written:       1989-05-01
 *                 1989 06 11: replaced previous file
 *                 1991 03 15: revision; AIX
 *                 1993-02-28: word info and doc info data structures
 *  latest update: 2000-09-01 12:10:56
 *  $Id: lookup.h,v 1.11 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifndef __GG_lookup__
#define __GG_lookup__

#include <gg/floskel.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
#define MAX_LUT_KEY_LENGTH 1024 /* maximum size of LUT entry allowed        */
#define STOP_WORD_LIMIT    1000 /* The first 1000 words are considered      */
                                /* stop words.                              */
#define MAX_WORD_COUNT     1000 /* Number of hits for a word to be          */
                                /* dropped from document list.              */
#define MIN_WORDLENGTH        3 /* word must be at least (or at most) this  */
#define MAX_WORDLENGTH       24 /* long to be indexed.                      */
#define LMD_BUFFER_SIZE    2048 /* various character buffers                */

/* data structure design features ----------------------------------------- */
#define MAX_DI_POS 2
#define LMD_EXTENDED_MODEL

/* LUT Index Reference ---------------------------------------------------- */
struct LUT_REFERENCE    /*** this data structure is more or less obsolete ***/
{
  long LR_off_next;     /* Offset des naechsten Records zu selben Key       */
  long LR_off_prev;     /* Offset des vorherigen Records zu selben Key      */
  short LR_file_id;     /* File ID Schluessel (z.B. als Index in Tabelle)   */
  short LR_cnt;         /* Zahl der Offset Eintraege in der Offset Tabelle  */
  long LR_offset [1];   /* Offset Tabelle; selber Key und selbe File ID     */
} ;

/* document information --------------------------------------------------- */
struct DOCUMENT_INFO
{
  long DI_document_id;          /* reference code of document               */
  long DI_hit_count;            /* number of hits of word in that document  */

#ifdef LMD_EXTENDED_MODEL
  long DI_document_ptr;         /* pointer into document info table or so   */
  long DI_pos [MAX_DI_POS];     /* position(s) of word within document      */
#endif /* LMD_EXTENDED_MODEL */
} ;

#define DOCUMENT_INFO_SIZE (sizeof (struct DOCUMENT_INFO))

/* NOTE: DI_document_ptr and DI_pos are not really used by the NL_KR        */
/*       library.  These parameters are simply stored and passed along      */
/*       and could be used by an embedding application.                     */

/* document information --------------------------------------------------- */
struct DOCUMENT_INFO_LIST
{
  struct DOCUMENT_INFO_LIST *DIL_next;
  struct DOCUMENT_INFO *DIL;
} ;
typedef struct DOCUMENT_INFO_LIST DIL;

/* document directory ----------------------------------------------------- */
struct DOCDIR_LIST
{
  struct DOCDIR_LIST *DL_next;
  struct DOCUMENT_INFO *DL_di;
  char *DL_name;
  char *DL_path;
  char *DL_file;
  long DL_from;
  long DL_to;
  long DL_size;
  long DL_lfrom;
  long DL_lto;
  long DL_lines;
} ;

/* word information ------------------------------------------------------- */
struct WORD_REF
{
  long WR_count;                /* number of references to that entry       */
                                /* more or less the real word count!        */

  /* only temporarily used during reading and writing !!                    */
  long WR_docinfo_offset;       /* begin of document info block             */
  long WR_docinfo_count;        /* number of entries in doc info block      */
                                /* number of documents associated with that */
                                /* word; 0 implies almost certainly a       */
                                /* stop word!                               */

  /* pointers to the document descriptor                                    */
  struct YTREE *WR_ytree;       /* hash table for doc ids                   */

  void *WR_extra;               /* additional payload for special apps.     */
} ;

/* number of bytes actually written to the file for a WORD_REF record       */
#define WORD_REF_SIZE (3*sizeof (long))

#define WRlang_english  1
#define WRlang_german   2

#define WRint_null      0x00000000
#define WRint_evaled    0x00000001
#define WRint_atomic    0x00000002
#define WRint_ignore    0x00001000
#define WRint_logic_and 0x00001001
#define WRint_logic_or  0x00001002
#define WRint_logic_not 0x00001003
#define WRint_logic_but 0x00001004
#define WRint_ling_and  0x00001101
#define WRint_ling_or   0x00001102
#define WRint_ling_not  0x00001103
#define WRint_ling_but  0x00001104

/* word information list -------------------------------------------------- */
struct WORD_REF_LIST                    /* datastructure describing any     */
{                                       /* hit word                         */
  struct WORD_REF_LIST *WRL_next;       /* following word                   */
  struct WORD_REF WRL;                  /* description of word              */
  char *WRL_string;                     /* associated string for word ref   */
  long WRL_index;                       /* word index of that word          */
  struct DOCUMENT_INFO_LIST *WRL_dil;   /* document list for that word      */
} ;
typedef struct WORD_REF_LIST WRL;

/* NOTE: this structure is only used during a search and not for index      */
/* generation any longer.                                                   */

/* term evaluation list --------------------------------------------------- */
struct TERM_EVAL                        /* evaluation of boolean or         */
{                                       /* linguistic expressions           */
  struct TERM_EVAL *TE_left;            /* next term or right hand ...      */
  struct TERM_EVAL *TE_right;           /* left hand operand                */
  long TE_operator;                     /* WRint_xxx                        */
  char *TE_string;                      /* string representation of         */
                                        /* evaluated term                   */
  struct WORD_REF_LIST *TE_wrl;         /* words used in evaluation         */
  struct DOCUMENT_INFO_LIST *TE_dil;    /* resulting document list          */
} ;

/* lutmake/deref creation control: ---------------------------------------- */
struct LMDC_CONTROL
{
  struct YTREE *LMDC_ytree;

  /* information about the latest added item */
  struct WORD_REF *LMDC_act_word_ref;   /* word reference structure         */
  long LMDC_word_index;                 /* word reference index (ytree key) */

  long LMDC_cnt_sw_idx;                 /* total number of words processed  */
                                        /* in all documents during one run  */

  /* limiting the number of items */
  long LMDC_max_word_count;
  long LMDC_stop_word_limit;
  long LMDC_max_doc_count;              /* max number of documents for word */

  /* "quality" of each added word */
  int LMDC_min_wordlength;
  int LMDC_max_wordlength;

  /* temporary storage and run-time options */
  char *LMDC_buffer1;
  char *LMDC_buffer2;
  int LMDC_buffer_size;

  int LMDC_verbosity;
} ;

/* lutmake dump control: -------------------------------------------------- */
/* NOTE: this structure is used while simultanously dumping the word        */
/*       reference and document info structures to seperates files          */

#ifdef _FILE_DEFINED
#define _LMDD_CONTROL_DEFINED
struct LMDD_CONTROL             /* lutmake dump control                     */
{
  struct LMDC_CONTROL *LMDD_lmdc;
  FILE *LMDD_fo_wr;             /* word ref file currently being written    */
  FILE *LMDD_fo_di;             /* document info file currently written     */
  long LMDD_doc_items_offset;   /* 0th entry dummy!!                        */
  long LMDD_doc_items_written;  /* number of document entries in word ref   */
                                /* block written to DI file.                */
  long LMDD_items_written;      /* CLEANUP: not necessary!!??!!             */
  long LMDD_word_index;         /* number of item in the WR file            */

  int LMDD_mode;
#define LMDD_mode_full     0    /* dump the complete wr and di structures   */
#define LMDD_mode_partial  1    /* only dump partial di structures          */
} ;
#endif /* _FILE_DEFINED */

/* lutmake/deref test control: -------------------------------------------- */
#ifdef _FILE_DEFINED
#define _LMDT_CONTROL_DEFINED
struct LMDT_CONTROL
{
  char *LMDT_LUT;
  FILE *LMDT_LUT_FILE;
  FILE *LMDT_TFB_FILE;

  char *LMDT_pfx;
  int LMDT_rep2_cnt;

  char LMDT_ext_pattern [MAX_LUT_KEY_LENGTH];
  char LMDT_complete_key [MAX_LUT_KEY_LENGTH];
} ;
#endif /* _FILE_DEFINED */

/* ------------------------------------------------------------------------ */
struct DEREF_CONTROL
{
  struct DOCUMENT_INFO_LIST *DC_dil;
  struct DOCUMENT_INFO_LIST **DC_dil_app;
} ;

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
#define _LMD_QUERY_SET_defined
struct LMD_QUERY_SET
{
  struct LMD_QUERY_SET *LMDQS_next;
  struct LMD_QUERY_SET *LMDQS_sub;

  char *LMDQS_fn_lut;
  char *LMDQS_fn_wr;
  char *LMDQS_fn_di;

  FILE *LMDQS_F_lt;
  FILE *LMDQS_F_wr;
  FILE *LMDQS_F_di;

  int LMDQS_initialized;

  /* temporary data used during lookup and reference */
  char LMDQS_ext_pattern  [MAX_LUT_KEY_LENGTH];
  char LMDQS_found_string [MAX_LUT_KEY_LENGTH];
  struct WORD_REF_LIST **LMDQS__wrl;
  int LMDQS__error_flag;
  char *LMDQS_pfx;              /* prefix of all found words */
  int LMDQS_pfx_lng;
} ;
typedef struct LMD_QUERY_SET LMDQS;
#endif /* _FILE_DEFINED */

/* ------------------------------------------------------------------------ */
#define RM_words        0
#define RM_fcy          1
#define RM_tokens       2
#define RM_veronica     3
#define RM_stream       4
#define RM_lfcy         5
#define RM_tfb          6
#define RM_hyx_cluster  7

/* ------------------------------------------------------------------------ */
#define lmdt_control_new() \
  ((struct LMDT_CONTROL *) calloc (sizeof (struct LMDT_CONTROL), 1))

/* LOOKUP functions ------------------------------------------------------- */
int cdecl lookup_char (char *lut, const char *w, long *w_info, int *lng);
char *cdecl lut_char_get_word_buffer (void);
char *cdecl lut_char_get_dump_beg (void);
char *cdecl lut_char_get_dump_end (void);

#ifdef _FILE_DEFINED
int cdecl lookup_file (FILE *lut, const char *w, long *w_info, int *lng);
#endif /* _FILE_DEFINED */
char *cdecl lut_file_get_word_buffer (void);
long cdecl lut_file_get_dump_beg (void);
long cdecl lut_file_get_dump_end (void);

#ifdef _FILE_DEFINED
int cdecl lookup_file_xfn (FILE *xfn, const char *w, long *w_info);
#endif /* _FILE_DEFINED */

/* int lookup_XXXX (lut, w, w_info, lng)                                    */
/* XXXX *lut;                      Look Up Table (File bzw. Array of char)  */
/* char *w;                        Word                                     */
/* long *w_info;                   -> Informationen ueber Word              */
/* int  *lng;                      -> Laenge des gematchten Wortes          */
/*                                    Wichtig bei LOOKUP_prefix             */
/* RETURN:                                                                  */

/* LUT_RETURN_CODES:                                                        */
#define LOOKUP_empty       -4   /* ERR: LUT is still empty                  */
#define LOOKUP_invalid     -3   /* ERR: structure of LUT is unknown         */
#define LOOKUP_error_size  -2   /* ERR: LUT is too large                    */
#define LOOKUP_error       -1   /* ERR: string is invalid, can't be located */
#define LOOKUP_not_found    0   /* string could not be found                */
#define LOOKUP_found    0x0001  /* w in LUT                                 */
#define LOOKUP_prefix   0x0002  /* w=uv, u in LUT, w not in LUT             */
                                /* Der Anfang von w (= die ersten lng Bytes)*/
                                /* kann in der LUT gefunden werden.         */
#define LOOKUP_prefix_3 0x0004  /* w not in LUT, u=wv in LUT                */
                                /* w ist der Anfang EINES Wortes in der LUT */
#define LOOKUP_prefix_4 0x0008  /* w not in LUT, u=wv in LUT, x=wy in LUT   */
                                /* w ist der Anfang von ZWEI ODER MEHR      */
                                /* Worten in der LUT                        */

/* macro functions: ------------------------------------------------------- */
#define lmd_new_word_ref_list() \
  ((struct WORD_REF_LIST *) calloc (sizeof (struct WORD_REF_LIST), 1))

#define lmd_new_word_ref() \
  ((struct WORD_REF *) calloc (sizeof (struct WORD_REF), 1))

#define lmd_new_document_info_list() \
 ((struct DOCUMENT_INFO_LIST *) calloc (sizeof (struct DOCUMENT_INFO_LIST),1))

#define lmd_new_document_info() \
 ((struct DOCUMENT_INFO *) calloc (sizeof (struct DOCUMENT_INFO),1))

#define lmd_new_term_eval() \
  ((struct TERM_EVAL *) calloc (sizeof (struct TERM_EVAL),1))

#define lmd_new_query_set() \
  ((struct LMD_QUERY_SET *) calloc (sizeof (struct LMD_QUERY_SET), 1))

#define lmd_SW(lmdc,s)           lmd_score((lmdc), (s),    1L, 0x0003)
#define lmd_SWT(lmdc,s,add)      lmd_score((lmdc), (s), (add), 0x0003)
#define lmd_SWX(lmdc,s,cnt)      lmd_score((lmdc), (s), (cnt), 0x0002)

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
/* nl_00001.c */ int cdecl nl_get_str (FILE *fi, char *s);
#endif

/* nl_00002.c */ int cdecl nl_key_valid (const char *w);

/* Ausgabe einer LUT in Klarschrift --------------------------------------- */
#ifdef _FILE_DEFINED
int cdecl lut_print (FILE *fo, char *lut_name, char *fmp, long start);
int cdecl lut_print_block (FILE *fo, FILE *lut, char *format);
#endif /* _FILE_DEFINED */

/* NL_00004.C: Ein Token einlesen: ---------------------------------------- */
#ifdef _FILE_DEFINED
int cdecl nl_get_token (
FILE *fi,               /* Input File                                       */
char *s,                /* gelesenes Token                                  */
int   mode,             /* Controlvektor                                    */
int  *push_back,        /* zuletzt gelesenes Zeichen                        */
long *filepos_beg);     /* Beginn des Wortes im File                        */
/* Return: Controlvektor ... Das Bit gibt an warum abgebrochen wurde;       */
/*         0 -> EOF                                                         */
#endif /* _FILE_DEFINED */

int cdecl lut_process (char *lut_name,
  int (*processor) (char *w, long i, void *client_data),
  void *client_data, long start);
#ifdef _FILE_DEFINED
int cdecl lut_process_block (FILE *lut,
  int (*processor) (char *w, long i, void *client_data),
  void *client_data);
#endif /* _FILE_DEFINED */

/* lut_0010.c */ int cdecl xfn_process (char *xfn_name,
  int (*processor) (char *w, long i, void *client_data),
  void *client_data, long start);
#ifdef _FILE_DEFINED
/* lut_0011.c */ int cdecl xfn_process_block (FILE *xfn,
  int (*processor) (char *w, long i, void *client_data),
  void *client_data);
#endif /* _FILE_DEFINED */
/* lut_0012.c */ int lut_dump_file (char *fn, int out_mode, long dump_start);
/* lut_0013.c */ int lut_dump_entry (char *wrd, long info, void *client_data);
/* lut_0015.c */ struct YTREE *lut_scan_ytree (char *fn, long start);
                 int lut_ytree_entry (char *wrd, long info, void *client_data);
#ifdef _FILE_DEFINED
                 struct YTREE *lut_scan_ytree_file (FILE *lut, long start);
#endif /* _FILE_DEFINED */
/* prototypes: ------------------------------------------------------------ */
/* nl_00101.c */ struct DOCUMENT_INFO_LIST *cdecl
                   lmd_find_document_info_list (
                   struct DOCUMENT_INFO_LIST *start, long doc_id);
#ifdef _FILE_DEFINED
/* nl_00102.c */ int cdecl lmd_dump_document_info_list (struct YTREE *yt,
                   void *client_data);

/* nl_00104.c */ struct WORD_REF_LIST *cdecl lmd_deref_word (
                   struct LMD_QUERY_SET *lmdqs, char *w, int exact);
/* nl_00105.c */ struct WORD_REF_LIST *cdecl lmd_deref1 (
                   struct LMD_QUERY_SET *lmdqs,
                   char *str, int min_wordlength, int max_wordlength);

/* nl_00106.c */ int cdecl lmd_deref_word_ref (
                   struct LMD_QUERY_SET *lmdqs,
                   char *w, int exact, struct WORD_REF_LIST **wrl);
/* nl_00107.c */ int lmd_read_word_ref_list (struct YTREE *yt,
                   void *client_data);
/* nl_00108.c */ int cdecl lmd_read_word_ref (FILE *fi_word_ref,
                   struct WORD_REF *wr);
/* nl_00109.c */ long cdecl lmd_read_document_info_list (FILE *fi,
                   struct YTREE **wrl_ytree, long offset, long cnt);
#endif /* _FILE_DEFINED */

/* nl_00111.c */ int cdecl lmd_discard_doc_id (struct YTREE *yt,
                   void *client_data);

/* nl_00112.c */ int cdecl lmd_free_docdir_list (struct DOCDIR_LIST *dl1);
/* nl_00113.c */ struct DOCDIR_LIST *cdecl lmd_read_docdir_info (
                   char *document_dir, struct WORD_REF_LIST *wrl);
/* nl_00114.c */ struct DOCDIR_LIST *cdecl lmd_get_docdir_info (char *line1,
                   char *line2, int MAX_LINE, long docid,
                   struct WORD_REF_LIST *wrl);

#ifdef _FILE_DEFINED
/* nl_00115.c */ int lmd_find_word_ref (FILE *f_wr, long w_info,
                   struct WORD_REF *wr);
/* nl_00116.c */ int cdecl lmd_print_word_ref_info (FILE *fo,
                   struct WORD_REF *wr);
/* nl_00117.c */ int cdecl lmd_print_doc_hit_list (FILE *fo,
                   struct WORD_REF_LIST *wrl, int print_dil);
/* nl_00118.c */ int cdecl lmd_print_document_info_list (FILE *fo,
                   struct DOCUMENT_INFO_LIST *start);
/* nl_00119.c */ int cdecl lmd_print_veronica_hit_list (FILE *fo,
                   char *veronica_file, struct WORD_REF_LIST *wrl);
/* nl_00120.c */ int cdecl lmd_print_veronica_docinfo_list (FILE *fo,
                   FILE *vf, struct DOCUMENT_INFO_LIST *start);
/* nl_00121.c */ int cdecl lmd_print_hyx_hit_list (FILE *fo,
                   char *document_dir, struct WORD_REF_LIST *wrl);
/* nl_00122.c */ int cdecl lmd_print_docdir_hyx (FILE *fo,
                   struct DOCDIR_LIST *docdir);
/* nl_00123.c */ int cdecl lmd_print_gopher_hit_list (FILE *fo,
                   char *document_dir, struct WORD_REF_LIST *wrl,
                   char *path_prefix, char *item_type, char *host_name,
                   long port_number);
/* nl_00124.c */ int cdecl lmd_print_docdir_gopher (FILE *fo,
                   struct DOCDIR_LIST *dl2, char *path_prefix,
                   char *item_type, char *host_name, long port_number);
/* nl_00125.c */ long cdecl lmd_write_word_ref (FILE *fo_word_ref,
                   struct WORD_REF *wr, long doc_items_offset,
                   long doc_items_written);
#endif /* _FILE_DEFINED */

/* nl_00126.c */ int cdecl lmd_docid_list_insert (
                   struct DOCUMENT_INFO *element,
                   struct YTREE **wrl_ytree, char *docid_str);
/* nl_00127.c */ struct TERM_EVAL *cdecl lmd_build_term_eval (char *str,
                   struct WORD_REF_LIST *wrl);
/* nl_00128.c */ struct TERM_EVAL *lmd_evaluate_terms (
                   struct TERM_EVAL *te_list, long opcode);
/* nl_00129.c */ struct DOCUMENT_INFO_LIST *cdecl lmd_dil_accumulate (
                   struct WORD_REF_LIST *wrl);
/* nl_00130.c */ struct DOCUMENT_INFO_LIST *cdecl lmd_dil_dup (
                   struct DOCUMENT_INFO_LIST *org);
                 struct DOCUMENT_INFO *lmd_di_dup (struct DOCUMENT_INFO *org);
/* nl_00131.c */ struct DOCUMENT_INFO_LIST *cdecl lmd_dil_operator (
                   struct DOCUMENT_INFO_LIST *dil_op1, 
                   struct DOCUMENT_INFO_LIST *dil_op2,
                   long operation);
/* nl_00132.c */ struct DOCUMENT_INFO *cdecl lmd_find_document_info (
                   struct WORD_REF *wr, char *doc_id_str);
/* nl_00133.c */ struct DOCUMENT_INFO *cdecl lmd_insert_document_info (
                   struct WORD_REF *wr, long doc_id, char *doc_id_str);
/* nl_00134.c */ int cdecl lmd_create_dil (struct YTREE *yt,
                   void *client_data);

#ifdef _LMD_QUERY_SET_defined
/* nl_00135.c */ int cdecl lmd_qs_setup_table_names (
                   struct LMD_QUERY_SET *lmdq, char *s);
/* nl_00136.c */ int cdecl lmd_deref_init (struct LMD_QUERY_SET *lmdqs);
/* nl_00137.c */ int cdecl lmd_deref_finish (struct LMD_QUERY_SET *lmdqs);
#endif /* _LMD_QUERY_SET_defined */

/* nl_00138.c */ int cdecl lmd_store_word_ref (char *str, long info,
                   void *client_data);

#ifdef _FILE_DEFINED
/* nl_00139.c */ int cdecl lmd_print_hyx_cluster_hit_list (FILE *fo,
                   struct WORD_REF_LIST *wrl, char *cluster_name);
#endif /* _FILE_DEFINED */

/* ------------------------------------------------------------------------ */
/* nl_00201.c */ int cdecl lmd_set_location_code (struct DOCUMENT_INFO *di,
                   int loc_operator, int loc_number, long loc_code);
/* loc_operator */
#define LOC_CODE_NOP    0
#define LOC_CODE_SET    1
#define LOC_CODE_ADD    2
#define LOC_CODE_OR     3

/* ------------------------------------------------------------------------ */
#ifdef _LMDT_CONTROL_DEFINED
/* nl_00301.c */ int cdecl lmd_TWF (struct LMDT_CONTROL *lmdt, char *w);
/* nl_00302.c */ int cdecl lmd_report_tfb (struct LMDT_CONTROL *lmdt,
                   long inf);
/* nl_00303.c */ int cdecl lmd_report2 (char *str, long inf,
                   void *client_data);
/* nl_00304.c */ int cdecl lmd_report (struct LMDT_CONTROL *lmdt, char *w,
                   int rv, int lng, long wi);
/* nl_00305.c */ int cdecl lmd_RL3 (struct LMDT_CONTROL *lmdt, char *fn,
                   int mode);
/* nl_00306.c */ int cdecl lmd_RL3_set_tfb_file (struct LMDT_CONTROL *lmdt,
                           char *fn);
#endif /* _LMDT_CONTROL_DEFINED */

/* ------------------------------------------------------------------------ */
/* nl_00401.c */ int cdecl lmd_score (struct LMDC_CONTROL *lmdc, char *s,
                   long cnt, int mode);
/* nl_00402.c */ int cdecl lmd_idx (struct LMDC_CONTROL *lmdc, char *s,
                   long document_id, long document_ptr, char *document_id_str,
                   int loc_operator, int loc_number, long loc_code);
/* nl_00403.c */ struct WORD_REF *cdecl lmd_lookup_entry (
                   struct LMDC_CONTROL *lmdc, char *string);

#ifdef __GG_ytree__
/* nl_00404.c */ long cdecl lmd_PL (struct YTREE *yt, char *LUT_out,
                    char *TABLE_out);
#endif /* __GG_ytree__ */

/* nl_00405.c */ int cdecl lmd_RL4 (struct LMDC_CONTROL *lmdc, char *LUT_in);
/* nl_00407.c */ void cdecl lmd_initialize_control(struct LMDC_CONTROL *lmdc);
/* nl_00408.c */ void cdecl lmd_error04 (char *msg);
#ifdef _FILE_DEFINED
/* nl_00409.c */ void cdecl lmd_print_04statistics (
                   struct LMDC_CONTROL *lmdc, FILE *fo);
#endif

#ifdef __GG_ytree__
/* nl_00410.c */ int cdecl ytree_wr_ptr2idx (struct YTREE *yt, void *lmdc);
/* nl_00411.c */ int cdecl ytree_wr_idx2ptr (struct YTREE *yt, void *lmdc);
#endif /* __GG_ytree__ */

/* ------------------------------------------------------------------------ */
/* nl_00500.c */ struct LMDC_CONTROL *cdecl lmd_create_control (void);

/* nl_00501.c */ int cdecl lmd_word_statistics (struct LMDC_CONTROL *lmdc,
                   struct WORD_REF *wi, char *string, long document_id,
                   long document_ptr, char *document_id_str, int operation,
                   int loc_operator, int loc_number, long loc_code);

/* operation: */
#define ADD_WORD_REF    1
#define DEL_WORD_REF    0

/* nl_00502.c */ int cdecl lmd_write_tables (struct LMDC_CONTROL *lmdc,
                   char *fn_wr, char *fn_di, int mode);
/* nl_00503.c */ long cdecl lmd_read_tables (struct LMDC_CONTROL *lmdc,
                   char *fn_wr, char *fn_di);
/* nl_00504.c */ int cdecl lmd_discard_document_id (struct LMDC_CONTROL *lmdc,
                   long doc_id);
#ifdef _FILE_DEFINED
/* nl_00510.c */ int cdecl lmd_dump_word_entry (struct YTREE *yt,
                   void *client_data);
/* nl_00511.c */ int cdecl lmd_print_lmdd (FILE *fo,
                   struct LMDD_CONTROL *lmdd);
#endif /* _FILE_DEFINED */
/* nl_00512.c */ long cdecl lmd_get_interpretation (char *s);
/* nl_00514.c */ int cdecl lmd_discard_document_node (struct YTREE *yt,
                   void *cd);

/* ------------------------------------------------------------------------ */
/* nl_00601.c */ long cdecl lmd_read_stream (
                   struct LMDC_CONTROL *lmdc, char *fn);
/* nl_00602.c */ long cdecl lmd_read_tokens (
                   struct LMDC_CONTROL *lmdc, char *fn, long docid,
                   char *docid_str,
                   long f_from, long f_size, long f_end, int verbosity);
/* nl_00603.c */ long cdecl lmd_batch_process (
                   struct LMDC_CONTROL *lmdc, char *fn, int verbosity);
/* nl_00604.c */ long cdecl lmd_docdir_process (
                   struct LMDC_CONTROL *lmdc, char *fn,
                   int match_c, char *match_v [], int verbosity);
/* nl_00605.c */ long cdecl lmd_veronica_process (
                   struct LMDC_CONTROL *lmdc, char *fn, int *alphabet);
/* nl_00606.c */ long cdecl lmd_read_tfb (
                   struct LMDC_CONTROL *lmdc, char *fn,
                   int position, int TFB_delimiter, int *alphabet);
/* nl_00607.c */ long cdecl lmd_read_words (
                   struct LMDC_CONTROL *lmdc, char *fn);
/* nl_00608.c */ long cdecl lmd_read_fcy (
                   struct LMDC_CONTROL *lmdc, char *fn);
/* nl_00609.c */ long cdecl lmd_read_long_fcy (
                   struct LMDC_CONTROL *lmdc, char *fn);
/* nl_00610.c */ long lmd_read_hyx_cluster (struct LMDC_CONTROL *lmdc,
                   char *fnm_hyx, char *fnm_idx, int *alphabet);

/* ------------------------------------------------------------------------ */
/* util_001.c */ int cdecl sort_by_frequency (char *wort, long frequency);
#ifdef _FILE_DEFINED
                 int cdecl print_sorted (FILE *fo);
#endif /* _FILE_DEFINED */

#endif /* __GG_lookup__ */
