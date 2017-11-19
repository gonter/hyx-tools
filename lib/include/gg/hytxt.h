/*
 *  include FILE <gg/hytxt.h>
 *
 *  declaration of HYX hypertext structures
 *
 *  written:       1990 02 14
 *  latest update: 1997-11-09 12:47:53
 *  $Id: hytxt.h,v 1.4 2005/09/04 20:27:37 gonter Exp $
 *
 */

#ifndef __GG_hytxt__
#define __GG_hytxt__

#include <gg/floskel.h>
#include <gg/ytree.h>

/* limits: ---------------------------------------------------------------- */
#define FRAME_NAME_LNG 1024     /* maximum length of a frame name           */

/* ------------------------------------------------------------------------ */
struct HYTXT_ATTR               /* Hypertext Frame Attribut Liste           */
{
  struct HYTXT_ATTR
       *hytxt_attr_next;
  char *hytxt_attr_id;          /* Frame Attribut Name                      */
  char *hytxt_attr_pars;        /* Frame Attribut Parameter                 */
} ;

/* ------------------------------------------------------------------------ */
struct HYTXT_FRAME              /* Hypertext Frame Descriptor               */
{                               /* not much used anymore ...                */
  struct HYTXT_FRAME
       *hytxt_frame_next,       /* Naechster Frame; bezogen auf Fileposition*/
       *hytxt_frame_prev,       /* Vorheriger Frame; bezogen auf File-Pos   */
       *hytxt_frame_earlier,    /* Aeltere Version des *selben* Frames      */
       *hytxt_frame_newer;      /* Neuere Version des *selben* Frames       */

  struct HYTXT_ATTR
       *hytxt_attr,             /* Frame Attribut Liste                     */
      **hytxt_attr_append;      /* Pointer zum Anhaengen des                */
                                /* naechsten Attributs                      */

  long  hytxt_frame_pos_beg;    /* Anfang des Frames im File                */
  long  hytxt_frame_pos_end;    /* Ende des Frames im File                  */
  char *hytxt_frame_name;       /* Name des Frames (gestrippt)              */

  int hytxt_frame_flags;        /* Flags fuer interne Verwendung            */
#define HYTXT_FRFLAG_Deleted   0x01     /* Frame was deleted                */
#define HYTXT_FRFLAG_Rename    0x02     /* Frame was renamed                */
#define HYTXT_FRFLAG_Move      0x04     /* Frame was moved                  */
#define HYTXT_FRFLAG_TOPURGE   0x07     /* Frame should be purged next time */

  char *hytxt_frame_buffer;     /* space to store frame data                */
  int   hytxt_frame_bsize;      /* size of frame buffer                     */
} ;

/* ------------------------------------------------------------------------ */
struct FILE_SEGMENT
{
  struct FILE_SEGMENT *FS_next; /* ... next one please!                     */

  char *FS_frame_name;          /* frame name involved                      */
  long FS_index;                /* frame's index number                     */
  long FS_begin;                /* frame's coordinates in the cluster       */
  long FS_end;                  /*                                          */
  long FS_cluster;              /* cluster number (dummy value!)            */

  char *FS_file_name;           /* file to transfer to or from              */
  long FS_from;                 /* part of file to start transfering        */
  long FS_size;                 /* size of file segment transfer            */

  int FS_operation;             /* what to do with the frame                */
#define FSop_frame      'f'
#define FSop_list       'l'
#define FSop_number     'n'
#define FSop_update     'u'
#define FSop_extract    'x'
#define FSop_delete     'd'

  int FS_update_state;          /* when adding a frame, conflict resolution */
#define FSupd_added     'a'     /* new frame added, no conflict             */
#define FSupd_replaced  'r'     /* update: replaced old frame               */
#define FSupd_renamed   'n'     /* update: renamed new frame automatically  */
#define FSupd_prompted  'p'     /* update: prompted new frame's name        */
#define FSupd_ignored   'i'     /* update: ignored new frame                */
/* The same flags in uppercase indicate that the update was performed       */
/* after prompting the user.                                                */
} ;

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
#define _HYX_CLUSTER_CONTROL_DEFINED
struct HYX_CLUSTER_CONTROL
{
  char *HCC_fnm_hyx;
  char *HCC_fnm_idx;
  char *HCC_fnm_lut;
  char *HCC_fnm_xfn;
  char *HCC_fnm_kill_by_id;
  char *HCC_fnm_kill_by_lx;

  struct YTREE *HCC_ytree;
  long HCC_next_index;
  int HCC_dictadd1_inited;
  int HCC_dict_mode;
  int HCC_mode_frame_name;
  int HCC_lut_mode;
#define HCC_lm_full_write  0    /* write complete LUT file                  */
#define HCC_lm_incremental 1    /* only add new frames to XFN file          */

  int HCC_open_mode;
#define HCC_om_error        -1  /* cluster is not usable!                   */
#define HCC_om_closed        0  /* cluster was not opened sofar             */
#define HCC_om_read          1  /* cluster was opened for reading only      */
#define HCC_om_update        2  /* cluster was opened to perform updates    */

  FILE *HCC_f_hyx;              /* opened hyx file                          */
  FILE *HCC_f_idx;              /* opened idx file                          */
  FILE *HCC_f_lut;              /* opened lut file                          */
  FILE *HCC_f_xfn;              /* opened xfn file                          */

                                /* read cache                               */
  int read_wall;                /* max. number of elements to be cached     */
  int read_cnt;                 /* number of elements cached                */
  struct YTREE *read_cache;

                                /* write cache                              */
  int write_wall;               /* max. number of elements to be cached     */
  int write_cnt;                /* number of elements cached                */
  struct YTREE *write_cache;
} ;
typedef struct HYX_CLUSTER_CONTROL HYX_CLUSTER_CONTROL;
#endif /* _FILE_DEFINED */

/* ------------------------------------------------------------------------ */
struct HYX_OBJECT_COUNTER       /* tag or entity counter                    */
{
  struct HYX_OBJECT_COUNTER *HOC_next;
  long HOC_cnt1;                /* subtotal counter                         */
  long HOC_cnt1b;               /* . of entities within a tag               */
  long HOC_cnt2;                /* overall total counter                    */
  long HOC_cnt2b;               /* . of entities within a tag               */
  char *HOC_str;                /* tag or entity name                       */
} ;

/* ------------------------------------------------------------------------ */
/* scan modes: */
#define HYXSM_hide_earlier      0x0001
#define HYXSM_hide_purged       0x0002
#define HYXSM_no_attributes     0x0010
#define HYXSM_no_allocation     0x0100

/* extract flags: */
#define HYXEF_write_frame_number 0x0001
#define HYXEF_append_eoln        0x0002
#define HYXEF_write_frame_name   0x0004
#define HYXEF_add_dot            0x0008

/* macros: ---------------------------------------------------------------- */
#define hyx_new_cluster_control() \
  ((struct HYX_CLUSTER_CONTROL *) \
  calloc (sizeof (struct HYX_CLUSTER_CONTROL), 1))

#define hyx_new_file_segment() \
  ((struct FILE_SEGMENT *) calloc (sizeof (struct FILE_SEGMENT), 1))

/* prototypes for hytxt modules: ------------------------------------------ */
/* hytxt001.c */ int cdecl hytxt_scan (char *fname, struct HYTXT_FRAME **fl,
                   int scan_mode);
#ifdef _FILE_DEFINED
/* hytxt002.c */ int cdecl hytxt_scan_entry (FILE *fi, long *fi_pos,
                   struct HYTXT_FRAME *fd, int scan_mode, char *md5_cks);
#endif /* _FILE_DEFINED */

/* hytxt003.c */ int cdecl hytxt_purge (char *hypertext_file,
                   char *purge_file,char *temp_file);
/* hytxt003.c */ int cdecl hytxt_purge_seperator (char *seperator,
                   int seperator_size);
/* hytxt004.c */ int cdecl hytxt_sort (struct HYTXT_FRAME **liste,
                   int sort_mode);
/* hytxt005.c */ void cdecl free_HYTXT_FRAME (struct HYTXT_FRAME *fd);
/* hytxt006.c */ void cdecl hytxt_hide_earlier (struct HYTXT_FRAME **fl);
#ifdef __GG_fnames__
/* hytxt007.c */ int cdecl hytxt_frame2dta2 (struct HYTXT_FRAME *fr,
                   struct dta2_buff **d2);
#endif
#ifdef _FILE_DEFINED
/* hytxt008.c */ int cdecl hytxt_report_frame (FILE *fo, char *txt,
                   struct HYTXT_FRAME *fd, int ret_val);
#endif /* _FILE_DEFINED */

/* prototypes for *NEW* hytxt modules: ------------------------------------ */
/* hytxt009.c */ int cdecl hyx_purge2 (char *fni, char *fni_tmp,
                   char *fnh, char *fnh_tmp, int verbose_level);
#ifdef _FILE_DEFINED
/* hytxt010.c */ int cdecl hyx_sequencer (FILE *fo, char *fnm_hyx,
                   char *fnm_idx, char *fnm_lut, char *fnm_xfn,
                   struct FILE_SEGMENT *fseg, int verbose_mode,
                   int extract_flags);
/* hytxt011.c */ long cdecl find_frame_lut (FILE *lut, char *fr_name);
/* hytxt012.c */ long cdecl find_frame_xfn (FILE *lut, char *fr_name);
/* hytxt013.c */ int cdecl deref_index (FILE *fidx, long idx, long *p1,
                   long *p2, long *p3);
/* hytxt014.c */ long cdecl hyx_write_stamp (FILE *fo, char *sig);
/* hytxt015.c */ int cdecl sgml_write_data (FILE *fo, char *open_tag,
                   char *close_tag, char *buffer, int buffer_size);
/* hytxt016.c */ int cdecl hyx_extract (FILE *fo, FILE *fi_hyx, FILE *fi_idx,
                   FILE *fi_lut, FILE *fi_xfn, char *frame_name,
                   int verbose_mode, int extract_flags);
#endif /* _FILE_DEFINED */
/* hytxt017.c */ long cdecl hyx_get_last_index (char *fnm);
#ifdef _FILE_DEFINED
/* hytxt018.c */ long cdecl hyx_get_random_index (FILE *fi_idx);
#endif /* _FILE_DEFINED */
/* hytxt019.c */ int cdecl hyx_update (char *fn_hyx, char *fn_idx,
                   char *fn_lut, char *fn_xfn,
                   struct FILE_SEGMENT *segment, int verbose_mode);
/* hytxt020.c */ struct FILE_SEGMENT *hyx_make_segment (
                   struct FILE_SEGMENT **fs_app, char *fn, char *frame_name,
                   long *index_number, int operation,
                   long fs_from, long fs_size);
/* hytxt021.c */ int cdecl hyx_destroy_segments (struct FILE_SEGMENT *fs);
#ifdef _FILE_DEFINED
/* hytxt022.c */ long cdecl hyx_get_index (FILE *fi_idx, FILE *fi_lut,
                   FILE *fi_xfn, char *frame_name);
/* hytxt023.c */ int cdecl hytxt_scan_file (FILE *fo, char *fn);
/* hytxt024.c */ int cdecl hyx_seq (FILE *fo, char *fnm_hyx,
                   struct FILE_SEGMENT *fs_list, int verbose_level,
                   int extract_flags);
#endif /* _FILE_DEFINED */
/* hytxt025.c */ int cdecl hyx_purge (char *hyx_in, int verbose_level);
#ifdef _FILE_DEFINED
/* hytxt026.c */ long cdecl hyx_seek_by_name (FILE *fi_hyx, FILE *fi_idx,
                   FILE *fi_lut, FILE *fi_xfn, char *frame_name);
/* hytxt027.c */ int cdecl hyx_print_segment (FILE *fo,
                   struct FILE_SEGMENT *fseg);
/* hytxt028.c */ int cdecl hyx_setup_segment (
                   struct FILE_SEGMENT **app_segments,
                   struct FILE_SEGMENT **fs_new,
                   char *x_line, long *index_number);

/* hytxt029.c */ int cdecl hyx_thr (
                   FILE *fo, char *fnm_hyx,
                   struct FILE_SEGMENT *fs_list, int verbose_level,
                   int extract_flags, char *wanted_thread);
/* hytxt030.c */ int cdecl hyx_threader (
                   FILE *fo, char *fnm_hyx,
                   char *fnm_idx, char *fnm_lut, char *fnm_xfn,
                   struct FILE_SEGMENT *fseg, int verbose_mode,
                   int extract_flags, char *wanted_thread);
/* hytxt031.c */ int cdecl hyx_thr_extract (
                   FILE *fo, FILE *fi_hyx,
                   FILE *fi_idx, FILE *fi_lut, FILE *fi_xfn,
                   char *frame_name, int verbose_mode, int extract_flags,
                   char *wanted_thread);
#ifdef __GG_parse__
/* hytxt032.c */ void cdecl hyx_thr_process (
                   FILE *fo, FILE *fi_hyx,
                   FILE *fi_idx, FILE *fi_lut, FILE *fi_xfn,
                   int verbose_mode, int extract_flags,
                   char *wanted_thread,
                   struct TEXT_ELEMENT *t, int verbosity,
                   int append_eoln);
#endif /* __GG_parse__ */
#endif /* _FILE_DEFINED */

/* hytxt033.c */ int cdecl hyx_update_index (char *index_file,
                   long li_begin, long li_end, long li_cluster_number,
                   long *frame_index, long *next_index);

#ifdef _FILE_DEFINED
/* hytxt034.c */ int cdecl hyx_setup_delete_segment (
                   struct FILE_SEGMENT **app_segments,
                   struct FILE_SEGMENT **fs_new,
                   char *frame_name, long *index_number);
/* hytxt035.c */ long hyx_seek_by_index (FILE *fi_hyx, FILE *fi_idx,long idx);
#endif /* _FILE_DEFINED */
/* hytxt036.c */ int hyx_setup_stdin_segment (
                   struct FILE_SEGMENT **app_segments,
                   struct FILE_SEGMENT **fs_new,
                   char *frame_name, long *index_number);

#ifdef _FILE_DEFINED
/* hytxt037.c */ int hyx_dump_frame_list (FILE *fi_lut, FILE *fi_xfn);
/* hytxt038.c */ /** DONT USE **/
                 long find_frame_lut_or_xfn (FILE *lut, FILE *xfn,
                   char *fr_name);
#endif /* _FILE_DEFINED */

/* prototypes for application modules: hyxidx01.c ------------------------- */
int cdecl hyx_index (char *fn, char *idx_frame, char *md5_frame,
            int idx_format, int flags, int verbose_mode);
int cdecl hyx_index_insert (char *frame_name, long idx, void *client_data);
int cdecl sort_frame (char *fn, long idx, long siz, char *md5);
#ifdef _FILE_DEFINED
int cdecl hyx_index_dump_frame (FILE *fo, char *idx_frame, int idx_format);
#endif /* _FILE_DEFINED */
int cdecl hyx_index_full_scan (int verbose_mode);
int cdecl hyx_index_rescan (void);

#define HYXIDX_FMT_NORMAL       0
#define HYXIDX_FMT_LINK         1
#define HYXIDX_FMT_DOCDIR       2
#define HYXIDX_FMT_MD5          3

#define HYXIDX_REC_SIZE         12

#define HYXIDX_FLAG_default     0x0000
#define HYXIDX_FLAG_full_scan   0x0001

/* ------------------------------------------------------------------------ */
/* hyxadd01.c */ int cdecl hyx_add (char *fn_hyx,
                   struct FILE_SEGMENT *segments, int verbose_mode);

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
/* sf01.c */ int cdecl hytxt_filter (FILE *fi, FILE *fo,
                                     long transfer_length,
                                     int translit_entities);
/* sf02.c */ long cdecl hytxt_hyx2html (FILE *fo, char *bu);
             int cdecl hyx_print_relational_links (FILE *fo);
#endif /* _FILE_DEFINED */

/* sf03.c */ int cdecl frame_name2url (char *frame, char *url, int max_url);
/* sf04.c */ int cdecl url2frame_name (char *url, char *frame, int max_frame);

/* ------------------------------------------------------------------------ */
#define TAGo_Frame      101
#define TAGc_Frame      102
#define TAGso_Frame     103
#define TAGsc_Frame     104

/* chksgml ---------------------------------------------------------------- */
#define CHKSGML_Fign_case       0x0001

#ifdef _FILE_DEFINED
/* chksgml1.c */ int cdecl hoc_print_counter (FILE *fo,
                   struct HYX_OBJECT_COUNTER *x,int what);
/* chksgml2.c */ int cdecl chksgml_file (FILE *fo, FILE *fo_report, char *fn,
                   int verbose_level, long byte_offset, long byte_count,
                   int flags);

/* chksgml3.c */ int chksgml_stream (FILE *fo, FILE *fo_report, FILE *fi,
                   char *fn,
                   int verbose_level, long byte_offset, long byte_count,
                   int flags);
                 int cdecl chksgml_print_total_counter (FILE *fo);
#endif /* _FILE_DEFINED */

/* chksgml4.c */ int cdecl analyze_tag (char *tag, int *tag_code,
                   struct HYX_OBJECT_COUNTER **x_app, int *frame_state);
/* chksgml5.c */ int cdecl analyze_entity (char *entity, int what,
                   struct HYX_OBJECT_COUNTER **x_app);
/* chksgml6.c */ int cdecl hoc_reset_counter (
                   struct HYX_OBJECT_COUNTER *x_app);

#ifdef _HYX_CLUSTER_CONTROL_DEFINED
/* hyxl0005.c */ int cdecl hcc_set_cluster_name (
                  struct HYX_CLUSTER_CONTROL *hcc, char *fnm_hyx);
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */

#ifdef _FILE_DEFINED
/* hyxl0006.c */ int cdecl print_hyx_link (FILE *fo, char *destination_frame,
                   char *destination_cluster, char *destination_file,
                   char *color, char *text);
#endif /* _FILE_DEFINED */

#ifdef _HYX_CLUSTER_CONTROL_DEFINED
/* hyxl0007.c */ int cdecl hcc_destroy (struct HYX_CLUSTER_CONTROL *hcc);
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */
/* hyxl0008.c */ char *cdecl hyx_make_stop_tag (const char *s);
/* hyxl0009.c */ char *cdecl hyx_translate_special_frame (const char *s);

#ifdef _HYX_CLUSTER_CONTROL_DEFINED
/* hyxl0010.c */ int cdecl hcc_open (struct HYX_CLUSTER_CONTROL *hcc,
                   int mode);
/* hyxl0011.c */ long hcc_update_index (struct HYX_CLUSTER_CONTROL *hcc,
                   YTREE_PROCESSOR *lut_processor,
                   YTREE_PROCESSOR *xfn_processor);
/* hyxl0012.c */ long hcc_seek_by_name (struct HYX_CLUSTER_CONTROL *hcc,
                   char *frame_name);
/* hyxl0013.c */ HYX_CLUSTER_CONTROL *new_HYX_CLUSTER_CONTROL (char *fnm_hyx);
#endif /* _HYX_CLUSTER_CONTROL_DEFINED */

#define hcc_close(x) hcc_open((x), HCC_om_closed);

#endif /* __GG_hytxt__ */
