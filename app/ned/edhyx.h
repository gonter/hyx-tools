/*
 *  FILE %ned/edhyx.h
 *
 *  NED SGML and Hypertext Datastructures etc...
 *
 *  written:       1991 05 16
 *  latest update: 1997-01-12  0:20:06
 *  $Id: edhyx.h,v 1.2 2002/06/15 04:35:20 gonter Exp $
 *
 */

#ifndef __NED_edhyx__
#define __NED_edhyx__

/* ------------------------------------------------------------------------ */
#ifdef __COMMENT__
Most datastructures for Hypertext in NED are something like caches, since
we expect things to grow rather large and then it would be quite difficult
to get everything necessary into a poor MSDOS box while still doing useful
work ...
#endif /* __COMMENT__ */

/* ------------------------------------------------------------------------ */
struct HISTORYCTRL
{
  struct HISTORYCTRL *next;
  struct HYTXT_FRAME *frame;
  int line;                     /* last cursor position in frame: line      */
  int column;                   /* last cursor position in frame: column    */
} ;

/* ------------------------------------------------------------------------ */
struct CLUSTERCTRL              /* control structure describing a currently */
{                               /* used cluster. there is such a            */
                                /* structure for all clusters in use.       */
  struct CLUSTERCTRL *next;     /* next cluster                             */
  struct FRAMECTRL *frames;     /* information about *some* frames in this  */
                                /* cluster (cached!!!)                      */
  int frames_complete;          /* 1 -> list of all frames in memory        */
  struct HISTORYCTRL *history;  /* history information for this cluster     */
  long next_index;              /* next valid index for a frame             */
  long highest_index;           /* highest index on the index file          */
  char *cluster_name_logic;     /* logic (virtual) name of cluster          */
  char *cluster_name_hyx;       /* name of the cluster file(s):             */
  char *cluster_name_idx;       /* name of the cluster file(s):             */
  char *cluster_name_lut;       /* name of the cluster file(s):             */
  char *cluster_name_xfn;       /* name of the cluster file(s):             */
                                /* extensions used:                         */
                                /* .hyx ... the hypertext cluster           */
                                /* .idx ... the index file                  */
                                /* .lut ... the main lookup table file      */
                                /* .xfn ... the extra framename table file  */
  int cluster_readonly;         /* 1 -> no modifications possible/allowed   */
  int cluster_locked;           /* 1 -> locked by another process           */
  int CC_flags;                 /* same as FCflg_*                          */
} ;

/* ------------------------------------------------------------------------ */
struct FRAMECTRL                /* control structure describing a frame     */
{                               /* this is cached info, usually for *some*  */
                                /* of the frames in the cluster             */
  struct FRAMECTRL   *next;     /* next frame in this cluster               */
  struct CLUSTERCTRL *cluster;  /* cluster where frame belongs to           */
  char *frame_name;             /* name of the frame                        */
  long frame_index;             /* index code of the frame                  */ 
#define FRAME_INDEX_undef -1    /* no index code defined for the frame      */
  long frame_begin;             /* beginning position in cluster            */
  long frame_end;               /* ending position in cluster               */
  int frame_lookup;             /* frame name found in:                     */
#define FRAME_is_new         0  /* nowhere, frame is newly created          */
#define FRAME_in_LUT         1  /* in .lut-file                             */
#define FRAME_in_XFN         2  /* in .xfn-file                             */

  int frame_status;             /* status of the frame control block        */
#define FRAME_is_defined     1  /* frame is defined an can be used          */
#define FRAME_is_loaded      2  /* frame is somewhere in memory             */
#define FRAME_is_unindexed   3  /* frame is not indexed sofar               */

#ifdef __CURRENTLY_NOT_DEFINED__
  int frame_is_latest;          /* 0 ... frame is an older version          */
                                /* 1 ... frame is the newest version        */
#endif /* __CURRENTLY_NOT_DEFINED__ */

  int links;                    /* number of windows linked to this frame   */
  int upd;                      /* frame needs to be updated                */
  int line;                     /* last cursor position in frame: line      */
  int column;                   /* last cursor position in frame: column    */
} ;

/* Tags: ------------------------------------------------------------------ */
struct SGML_TAG_DESCRIPTOR      /* description of a feature element         */
{
  struct SGML_TAG_DESCRIPTOR *STD_next;

  char *STD_tag_name;           /* tag name                                 */
  int   STD_tag_ml;             /* tag match length                         */
  int   STD_tag_mm;             /* tag match mode                           */
  int   STD_tag_id;             /* tag ID code; see STID_xxxxx              */
  int (*STD_activated) (char *s, int op1);
                                /* function to execute activated tag        */
  int (*STD_scanned) (char *s, int op1);
                                /* function to execute after tag is scanned */
  int   STD_display_mode;       /* mode to display a feature element        */
#define STD_display_hide      1 /* feature is not displayed at all          */
#define STD_display_point     2 /* feature is displayed by single character */
#define STD_display_region    3 /* feature is displayed as a string         */
#define STD_display_replarray 4 /* feature is displayed by a replacement    */
#define STD_display_tag_name  5 /* feature is displayed by it's tag name    */
#define STD_display_tag       6 /* feature is displayed by it's full tag    */
                                /* this is mapped to replarray              */
                                /* character (STD_display_character)        */
  int   STD_display_colour;     /* colour attribute of a feature display    */
  int   STD_duplication;        /* copy-mode for the tag                    */
#define STD_dup_copy       0x01 /* copied at 'Copy Block'                   */
#define STD_dup_write      0x02 /* written at 'Write Block'                 */
#define STD_dup_always     0x03
#define STD_dont_delete    0x10 /* *DON'T* delete at 'Delete Block'         */
#define STD_no_dup         0x00
  int   STD_flags;              /* formerly STD_subtype                     */
#define STD_f_none         0x00 /* no flags turned on                       */
#define STD_f_ign_case     0x01 /* ignore case of tag name                  */
  int   STD_weight;             /* weight value for the feature             */
  int   STD_replarray_size;     /* replacement array length                 */
  char *STD_replarray;          /* replacement array                        */

#ifdef DEVEL1
  int STD_new1;                 /* reserve */
  int STD_new2;
  int STD_new3;
  int STD_new4;
#endif
} ;

/* Entities: -------------------------------------------------------------- */
struct SGML_ENTITY_DESCRIPTOR
{
  struct SGML_ENTITY_DESCRIPTOR *SED_next;

  char *SED_entity_name;        /* name of the entity                       */
  int SED_entity_id;            /* entity ID-codes -&gt; SEID_xxxx             */

  int   SED_display_mode;       /* mode to display a feature element        */
#define SED_display_hide      1 /* feature is not displayed at all          */
#define SED_display_point     2 /* feature is displayed by single character */
#define SED_display_region    3 /* feature is displayed as a string         */
#define SED_display_replarray 4 /* feature is displayed by a replacement    */
                                /* character (STD_display_character)        */
  int   SED_display_colour;     /* colour attribute of a feature display    */
  int   SED_duplication;        /* copy-mode for the tag                    */
#define SED_dup_copy       0x01 /* copied at 'Copy Block'                   */
#define SED_dup_write      0x02 /* written at 'Write Block'                 */
#define SED_delete         0x10 /* *DON'T* delete at 'Delete Block'         */
  int   SED_weight;             /* weight value for the feature             */
  int   SED_replarray_size;     /* replacement array length                 */
  char *SED_replarray;          /* replacement array                        */

#ifdef DEVEL1
  int SED_new1;                 /* reserve */
  int SED_new2;
  int SED_new3;
  int SED_new4;
#endif
} ;

/* predefined Tag IDs:  - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define STID_NULL             0 /* standard tag                             */
#define STID_PSEUDO           1 /* standard pseudo character                */
#define STID_hyx_l            2 /* hypertext link type 1                    */
#define STID_NED_MACRO        3 /* NED macro defintion/execution            */
#define STID_NED_PARAMETER    4 /* NED window parameter defintion           */

/* predefined Entity IDs: - - - - - - - - - - - - - - - - - - - - - - - - - */

/* Hypertext Options: - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#define HYOPT_logic_link   1234 /* Logic Link -&gt; Close Window               */

/* flags for logic links: - - - - - - - - - - - - - - - - - - - - - - - - - */
#define LL_next 0x0001
#define LL_prev 0x0002
#define LL_menu 0x0004
#define LL_up   0x0008
#define LL_more 0x0010
#define LL_     0x0020
#define LL_lang 0x0040
#define LL_sort 0x0080
#define LL_view 0x0100

/* style of button bar */
/* #define LL_BUTTONS_1 .......    4 large buttons */
#define LL_BUTTONS_2            /* several small buttons */

/* Entities: -------------------------------------------------------------- */
#define IDX_REC_SIZE 12L        /* number of bytes for a record in .IDX     */

#endif /* __NED_edhyx__ */
