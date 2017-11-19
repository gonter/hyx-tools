/*
 *  FILE %ned/ed.h
 *
 *  written:       1987 03 20
 *                 1990 05 12: Revision
 *                 1991 01 01: Revision
 *                 1991 02 03: Revision
 *                 1992 04 21: <g.gonter@ieee.org> revision
 *                 1993-01-18: revision
 *                 1999-05-14 20:00:36
 *  latest update: 2001-02-11 22:06:54
 *  $Id: ed.h,v 1.6 2002/06/15 04:35:20 gonter Exp $
 *
 */

#ifndef __NED_ed__
#define __NED_ed__

#ifndef MSDOS
#define UNIX

#ifndef __SINIX__
/* #define __SINIX__ */         /* well, if you want SINIX ...              */
#endif
#endif

/* Debugging, Test, Development: ------------------------------------------ */
/* #define DEVEL1 */            /* reserves additional space in most        */
                                /* data structures.                         */

/* configuration for MSDOS: ----------------------------------------------- */
#ifdef MSDOS
#define W_MODEL_CGA             /* Direkte Bildschirmsteuerung              */
/* #define W_MODEL_BIOS */      /* Bildschirmsteuerung via BIOS             */
#define USE_MOUSE               /* Maus wird verwendet                      */
/* #define USE_FULL_SETUP */    /* Setup auch mit Tastatur Redefinition etc.*/
#endif

/* configuration for UNIX: ------------------------------------------------ */
#ifdef UNIX
/* #define USE_TK */               /* turn on TK tools too...                  */
#ifdef USE_TK
#define USE_TCL                 /* turn on TCL scripting for macros         */
#define W_MODEL_TK              /* for X with TK                            */
#else
#define W_MODEL_CURSES          /* use curses for screen management         */
#define USE_TCL                 /* turn on TCL scripting for macros         */
/* #define W_MODEL_NCURSES */   /* for linux, this can be defined also      */
#endif
/* #define USE_MOUSE */         /* Maus wird verwendet                      */
/* #define USE_FULL_SETUP */    /* Setup auch mit Tastatur Redefinition etc.*/
#endif

/* environment specific definitions: -------------------------------------- */
/* #define VW5                  .. not used anymore                         */

/* other configuraable options: ------------------------------------------- */
#define USE_GOPHER              /* -> GOPHER links can be accessed          */
#define WINSTACK                /* windows are pushed up/popped off a stack */
#define USE_ABBREVIATIONS       /* Abbreviations are enabled                */

/* SGML Konfiguration: ---------------------------------------------------- */
/* #define SGML_PARSE_STRIP */
#define SGML_PARSE_NO_STRIP

#ifdef MSDOS
#define SGML_32BIT_REPLACEMENT 0xF7     /* Character to represent codes     */
                                        /* >= 0x0100                        */
#else
#define SGML_32BIT_REPLACEMENT '@'
#endif

/* ------------------------------------------------------------------------ */
#define TXT_LNG        19       /* Laenge eines Textsegments:               */
                                /* Das Speicherverwaltungssystem von MSC5.0 */
                                /* vergibt immer eine gerade Anzahl von     */
                                /* Bytes als Speicher. Der fixe Teil von    */
                                /* TXT hat eine Laenge von 5 Byte, daher    */
                                /* kann jede ungerade Anzahl von Bytes fuer */
                                /* Textsegmente verwendet werden. Tests     */
                                /* haben ergeben, dass Textfiles durch-     */
                                /* schnittlich 32 Zeichen/Zeile haben.      */

#define minTXT_LNG      7       /* minimale Laenge eines Text Segments      */
                                /* kuerzer hat keinen Sinn (siehe oben)     */

#define LINE_LNG_TXT     32760  /* Maximale Zeilenlaenge fuer Text Zeilen   */
                                /* ... das ist die absolute Obergrenze      */
#define LINE_LNG_BIN        70  /* Maximale Zeilenlaenge fuer Binaere Zeilen*/

#define TAB_CHAR          0x09  /* code of the TAB character                */
#define TAB_EXPN          0x20  /* character that TAB gets expanded to      */

#define CHARSET_token        0
#define CHARSET_normal       0  /* old name for token ...                   */
#define CHARSET_filename     1
#define CHARSET_include      2
#define CHARSET_blank        3
#define CHARSET_non_blank    4

/* jump tables: ----------------------------------------------------------- */
#define N_CODES       128       /* number of key codes per jump table       */

#ifndef TBL_CTRL_SIZE
#define TBL_CTRL_SIZE 32        /* size of the key table for the control    */
                                /* chars (WordStar, Pico, Vi Switch)        */
#endif /* TBL_CTRL_SIZE */

#ifdef MSDOS
#define N_PFX           8       /* number of jump tables, including f-keys  */
#else
#define N_PFX           8       /* number of jump tables, curses func. keys */
#endif

#define P_NONE          0       /* normal jump table                        */
#define P_CTRLQ         2       /* jump table for prefix code Ctrl-Q        */
#define P_CTRLK         3       /* jump table for prefix code Ctrl-K        */
#define P_CTRLO         4       /* jump table for prefix code Ctrl-O        */
#define P_CTRLU         5       /* jump table for prefix code Ctrl-U        */
#define P_VI            6       /* jump table for vi mode                   */
#define P_FUNCT         7       /* jump table for PC function keys          */

/* ------------------------------------------------------------------------ */
#define N_MARKER       10       /* Anzahl der Marker                        */
#define N_MACRO        75       /* Anzahl der moeglichen Makros             */

#define FILE_READ               "rb"
#define FILE_WRITE              "wb"
#define FILE_APPEND             "ab"
#define FILE_TEXT_READ          "rt"
#define FILE_TEXT_WRITE         "wt"

                                        /* see NED_OPENF_* cross reference  */
#define NED_OPENF_REDRAW        0x0001  /* redraw window                    */
#define NED_OPENF_CONTEXT       0x0002  /* get filename from cursor pos.    */
#define NED_OPENF_HISTORY       0x0004  /* take history notes               */
#define NED_OPENF_EXISTS        0x0008  /* check if file is accessible      */
#define NED_OPENF_PROMPT        0x0010  /* prompt for file name             */
#define NED_OPENF_NO_REL_PATH   0x0020  /* ignore relative path of file     */
#define NED_OPENF_SGML          0x0040  /* open in SGML format              */
#define NED_OPENF_BINARY        0x0080  /* open in binary format            */
#define NED_OPENF_READ_ONLY     0x0100  /* open in readonly mode            */

#define NED_OPENF_RST_FORMAT    0xFF3F  /* reset format flags               */
#define NED_OPENF_DEF_STP       0x0005  /* Setup file: REDRAW, HISTORY      */
#define NED_OPENF_DEF1          0x0027  /* REDRAW, CONTEXT, HISTORY, NO REL */

struct NED_CB_OF                /* callback structure for open file         */
{
  struct WINDOWCTRL *wc;
  int flags;
} ;

#define wdw_off(wc) ((wc)->cx + (wc)->hv - (wc)->ax)
/* offset of cursor in window */

/* methods: --------------------------------------------------------------- */
typedef int ned_input_handler (void);
typedef int ned_primitive (void);

/* methods: --------------------------------------------------------------- */
#ifndef __NED_proto_prim__
#define __NED_proto_prim__
struct NED_PRIMITIVES
{
  char *NP_name;
  ned_primitive *NP_func;
} ;
#endif /* __NED_proto_prim__ */

/* ------------------------------------------------------------------------ */
struct FEATURE
{
  struct FEATURE *ftr_next;
  struct FEATURE *ftr_peer;     /* dazugehoeriger open|close Tag            */
  struct FEATURE *ftr_upper;    /* uebergeordnetes Tag                      */
  void *ftr_text_line;          /* struct LINE * txt_line                   */
                                /* Feature Text                             */
  int ftr_pos;                  /* Zeilen-Offset des Features               */

  int ftr_type;                 /* type of the feature                      */
#define Ftype_undefined       0
#define Ftype_SGML_TAG        1 /* any SGML tag                             */
#define Ftype_SGML_ENTITY     2 /* any SGML entity                          */
#define Ftype_SGML_entity_string   2001 /* &something;                      */
#define Ftype_SGML_tag_string      2002 /* <something>                      */
#define Ftype_SGML_tag_string2     2003 /* something, <> to be added        */
#define Ftype_hidden_text     3 /* hidden text within regular text          */
#define Ftype_hyx_l        1000 /* a hyx.l tag                              */
#define Ftype_mark         1001 /* a mark tag                               */
#define Ftype_lookup       1002 /* lookup tag text from /etc/feature.tfb    */
#define Ftype_hyx_l_mark   1003 /* set hyx.l with mark                      */
#define Ftype_lookup_fr    1004 /* set frame tag                            */
#define Ftype_lookup_fr2   1005 /* set frame tag, reuse current frame name  */


  int ftr_subtype;              /* weitere Untergliederung des Features     */
  int ftr_edit_flags;           /* see FTR_EDIT_                            */
#define FTR_EDIT_NO_TEXT        0x0001  /* must not be edited in text form  */
#define FTR_EDIT_NO_EDIT        0x0002  /* feature must not be edited       */
#define FTR_EDIT_NO_INSERT      0x0004  /* no inserts immediately before    */
                                        /* this feature                     */

#define FTR_EDIT_PROTECTED      0x0007  /* no editing anywhere              */

  int ftr_weight;               /* Wichtungscode fuer dieses Feature        */

  int ftr_display_mode;         /* Art der Anzeige des Features             */
#define FTR_display_hide      1 /* feature is not displayed at all          */
#define FTR_display_point     2 /* feature is displayed by single character */
#define FTR_display_region    3 /* feature is displayed as a string         */
#define FTR_display_replarray 4 /* feature is displayed by a replacement    */

  int ftr_colour;               /* Farbe des angezeigten Bereichs           */
  int ftr_replarray_size;       /* Laenge des Replacement Strings im Text   */

  int ftr_duplication;          /* duplication control                      */
#define FTR_dup_copy     0x0001 /* copied at 'Copy Block'                   */
#define FTR_dup_write    0x0002 /* written at 'Write Block'                 */
#define FTR_dup_allways  0x0003
#define FTR_delete       0x0010 /* *DON'T* delete at 'Delete Block'         */

#ifdef DEVEL1
  int ftr_new1;                 /* reserve */
  int ftr_new2;
  int ftr_new3;
  int ftr_new4;
#endif
} ;

/* Sub Types: rarely used! */
#define Ftype_SGML_closeTAG     0x01    /* close tag                        */
#define Ftype_SGML_autoTAG      0x02    /* autonomes tag (empty element)    */
#define Ftype_SGML_openTAG      0x0C    /* entweder recursiv oder non-rec   */
#define Ftype_SGML_recTAG       0x04    /* open tag/recursives Markup       */
#define Ftype_SGML_nonrecTAG    0x08    /* open tag/non-recursives Markup   */
#define Ftype_SGML_ENTITY1      0x01    /* extended character               */
#define Ftype_SGML_ENTITY2      0x02

#define FTR_EDIT_NONE           0
#define FTR_EDIT_STRING         1
#define FTR_EDIT_STRUCTURED     2
#define FTR_EDIT_ATTRIBUTE      3
#define FTR_EDIT_ALL            4
#define FTR_EDIT_ALL_COND       5

/* ------------------------------------------------------------------------ */
#ifdef MSDOS
#pragma pack(1)
#endif
struct TXT                      /* Textsegment einer Zeile                  */
{
  struct TXT *next;
  unsigned char t_lng;          /* Laenge des Textsegments                  */
  char t [3];                   /* 3 .. Dummywert                           */
} ;
#ifdef MSDOS
#pragma pack()
#endif

/* ------------------------------------------------------------------------ */
typedef int line_callback (int event, void *line, void *cd,
int column, void *op2);

/* ------------------------------------------------------------------------ */
struct LINE_CALLBACK
{
  struct LINE_CALLBACK *next;
  line_callback *func;
  void *cd;
  int event;
#define LCB_edit        0x0001  /* insert/delete in line at column          */
#define LCB_delete      0x0002  /* line was deleted                         */
#define LCB_chg_line    0x0004  /* line was changed at column               */
#define LCB_chg_wdw     0x0008  /* window was changed                       */

#define LCB_standard    0x000F
} ;

/* ------------------------------------------------------------------------ */
struct LINE                     /* normale Zeile mit CTRL                   */
{
  struct LINE *next;
  struct LINE *prev;            /* doppelte Verkettung                      */
  struct FEATURE *ftr;          /* Attribute usw.                           */
  struct FEATURE *l_active_ftr; /* gueltiges Markup fuer diese Zeile        */
  int lng;                      /* Laenge ueber alles                       */
  int line_flg;                 /* Flags: 1 == True                         */
                                /* Bit 0: Block Beg | End                   */
                                /*     1: im Block                          */
                                /* Bit 7: 0x0D in Zeile gefunden            */
                                /*        Text Modus !!!                    */
  struct TXT *txt;              /* ^ 1. Textsegment                         */

  struct LINE_CALLBACK *callbacks;
} ;

/* LINE_: see $line_ ------------------------------------------------------ */
#define LINE_BLOCK_BEGEND       0x0001  /* Zeile ist Block Anfang | Ende    */
#define LINE_BLOCK_INBLOCK      0x0002  /* Zeile (mitten) im Block          */
#define LINE_inBLOCK            0x0003  /* Zeile im Block                   */
#define LINE_TAGGED_GLOBAL      0x0020  /* line was tagged in global cmd    */
#define LINE_PROTECTED          0x0040  /* no editing in this line          */
#define LINE_CODE_0x0D          0x0080  /* line ends with CR-LF pair        */
#define LINE_HIDDEN             0x0100  /* the line is not visible          */
#define LINE_FOLDED_AWAY        0x0200  /* line is not visible, fold closed */
#define LINE_VIRTUAL            0x0400  /* text is not part of the file     */

#define LINE_BLOCK_CLR          0xFFFC  /* Block Flags loeschen             */
#define LINE_BLOCK_CLR_BEGEND   0xFFFE  /* Block Marker Flags loeschen      */

/* ------------------------------------------------------------------------ */
struct FILECTRL                 /* Filesteuerung                            */
{
  struct FILECTRL *next;
  struct FILECTRL *prev;
#define FC_next next
#define FC_prev prev
  int  FC_links;                /* Anzahl der Windows / File                */
  int  FC_upd;                  /* 1 x Save bei ^KX                         */
  int  FC_num;                  /* Nummer des Filectrl Blocks               */
  int  FC_flags;                /* FCflg_*                                  */
#define FCflg_RO         0x0001 /* read only                                */
  char *FC_fnm_txt;             /* Text File Name                           */
  char *FC_fnm_ftr;             /* Feature File Name                        */
  char *FC_fnm_bak;             /* Feature File Name                        */
} ;

/* ------------------------------------------------------------------------ */
typedef void window_callback (int event, void *window, void *cd);

/* ------------------------------------------------------------------------ */
struct WINDOW_CALLBACK
{
  struct WINDOW_CALLBACK *next;
  window_callback *func;
  void *cd;
  int event;
#define WCB_close       0x0001
#define WCB_save        0x0002  /* => recompile */
#define WCB_abort       0x0004
#define WCB_read        0x0008
#define WCB_resize      0x0010
#define WCB_iconify     0x0020
#define WCB_withdraw    0x0040
#define WCB_deiconify   0x0080
} ;

/* ------------------------------------------------------------------------ */
struct WINDOWCTRL               /* Windowsteuerung                          */
{
  struct LINE *WC_act;          /* Zeile mit Cursor                         */
  struct LINE *first;           /* 1. angezeigte Zeile                      */
#define WC_first first
  void *file_or_frame;          /* File oder Frame zum Window               */
  struct WINDOWCTRL *next;      /* Windows sind                             */
#define WC_next next
  struct WINDOWCTRL *prev;      /* doppelt verkettet                        */
#define WC_prev prev
  struct WINDOWCTRL *feature_window;    /* Window mit Feature Text          */
  char *WC_title_short;         /* name to be displayed                     */
  char *WC_title_long;          /* name to be displayed                     */
  
  int ax, ay;                   /* Koordinaten | inklusive                  */
  int bx, by;                   /* des Windows | Werte                      */
  int cx, cy;                   /* Aktuelle Cursor Position                 */
  int page;                     /* Bildschirmseite                          */
                                /* -1 .. Window wird nicht angezeigt        */
  int znr;                      /* Zeilennummer der akt. Zeile              */
  int hv;                       /* Horizontal View                          */
  int tlines;                   /* Zahl der Zeilen im Window Text           */

  int attr_text;                /* Colour-Attribut des Text                 */
  int attr_box;                 /* Colour-Attribut der Window-Umrandung     */
  int box_type;                 /* Art der Windowumrandung                  */
#define BOX_TYPE_none   0       /* keine Umrandung                          */
#define BOX_TYPE_single 1       /* einfache Umrandung                       */
#define BOX_TYPE_double 2       /* doppelte Umrandung                       */
  int attr_block;               /* Attribut von Blocks                      */
  int attr_feature;             /* Attribut von Feature Markern             */
#define COL_DEF_TEXT    0x0100  /* Feature -> Colour wie normaler Text      */
#define COL_DEF_FEATURE 0x0200  /* Feature -> Colour Feature Default        */
  int attr_markup;              /* default-Attribut von Markups             */
  int attr_status;              /* Attribut der Window-Status-Zeile         */
  int wflags;                   /* Window Flags:                            */
                                /* Bit 0: Window ueberlappend               */
#define HIDE_LINES      0x0200  /* do not show hidden lines                 */

  int ins_flg;                  /* 1 -> Insert enabled                      */
#define INSFLG_overwrite        0
#define INSFLG_insert           1
/* #define INSFLG_change_word      2  ... not used !!! */
  int ai;                       /* 1 -> Auto Ident Mode                     */
  int wwc;                      /* Word Wrap Count                          */
  int file_format;              /* Format siehe FMT_xxxx                    */
#define FMT_BINARY      0
#define FMT_ASCII       1
#define FMT_SGML        2
  int file_type;                /* 1 -> HYX Strukturierung mit Frames       */
#define FTY_PLAIN       0       /* normal file                              */
#define FTY_HYPER       1       /* Hypertext File                           */
#define FTY_FTRWDW     17       /* Window ist ein Feature Window            */
                                /* feature_window zeigt auf Haupt-Window    */
  int f_upd;                    /* 1 -> File Update                         */
  int l_upd;                    /* 1 -> Line Update                         */
  int w_upd;                    /* erforderliche Aktionen bei Window Update */
#define W_UPD_WINDOW    0x01    /* Bit 0: Window Update                     */
#define W_UPD_JMP2LINE  0x02    /*     1: jmp2line ausfuehren               */
#define W_UPD_WSHIFT    0x04    /*     2: Window Verschoben; -> Box         */
#define W_UPD_WSETUP    0x80    /*     7: Window per Setup definiert        */

  int WC_edit_mode;             /* moegliche Editierfaehigkeit              */
#define EDIT_READ_ONLY  0x0001  /* Bit 0: Read Only                         */
#define EDIT_NOTOGGLE   0x0002  /*     1: Bit 0 nicht togglen               */
#define EDIT_NOLINEOPS  0x0004  /* kein Operationen mit Zeilen              */
#define EDIT_LINENR     0x0010  /* show line numbers                        */
#define EDIT_LINENR0    0x0020  /* show line numbers with leadin 0          */
                                /* OBSOLETE: 2: Binary File Mode            */

  int bin_eoln;                 /* End-Of-Line  im Binaer Modus             */
  int bin_llng;                 /* Zeilenlaenge .  .      .                 */
  int wc_ll_flags;              /* logic link flags                         */

  int wc_window_number;         /* number of the window                     */

  void *wc_widget;              /* TK widget control struct for that window */

  int wc_tag_display_mode;
#define WCTDM_no_change      0  /* don't switch tag display mode            */
#define WCTDM_normal         1  /* standard way to display tags             */
#define WCTDM_show_tag       2  /* display all tags, but only the name      */
#define WCTDM_show_full_tag  3  /* display all tags with full text          */

#define WCTDM_SGML           4
#define WCTDM_ASCII          5

  int wc_taint_level;           /* degree of untrustworthyness of a window  */
  void *wc_file_mode;           /* editing mode depending on file type      */
  int longest_line;             /* length of longest line in this window    */

  struct WINDOW_CALLBACK *wcb_list;

#ifdef DEVEL1
  int wc_new1;                  /* unused, temporary .... */
  int wc_new2;
  int wc_new3;
  int wc_new4;
#endif
} ;

/* ------------------------------------------------------------------------ */
struct MARKER
{
  struct WINDOWCTRL *wptr;      /* File in dem Marker gueltig ist           */
  struct LINE *ptr;             /* Zeile mit Marker                         */
  int offset;                   /* Spalte des Markers                       */
} ;

/* marker with special purpose  */
#define NED_TMARK_INSERT2 4     /* block insertion [That's digit 4, ^D !]   */
#define NED_MARKER_BEG  '('     /* block begin marker                       */
#define NED_MARKER_END  ')'     /* block end marker                         */

/* Pointer Lists: --------------------------------------------------------- */
struct PLIST                    /* used for: window stack                   */
{
  struct PLIST *PL_lnk;
  void *PL_val;
} ;

/* Buttons: --------------------------------------------------------------- */
struct BUTTON_DESCRIPTOR
{
  struct BUTTON_DESCRIPTOR *BD_next;                                                                                  

  int BD_id;
  int (*BD_function)(long par1, int x, int y, int t);   /* unused still */
  long BD_parameter;                                    /* unused still */

  int BD_type;                  /* button type: 1 -> macro */
  int BD_macro_num;             /* number of macro to execute */
  int BD_x;
  int BD_y;
  char *BD_text;                /* the button's text */
  int BD_colour;

#ifdef DEVEL1
  int BD_new1;
  int BD_new2;
  int BD_new3;
  int BD_new4;
#endif
} ;

/* Menu Descriptors: ----------------------------------------------------- */
struct mm_item  /* item in the mouse menu */
{
  int MMI_type;
#define MMI_undef       0
#define MMI_func        1
#define MMI_macro       2
  int MMI_flag;
  long MMI_value;
  int MMI_res1;
  int MMI_res2;
} ;

#define MACRO_SUBMIT 0          /* number of macro for submit function      */

/* Macro Descriptors: ----------------------------------------------------- */
struct NED_MACRO
{
  int NED_mac_type;
  char *NED_mac_contents;
} ;

/* Operation Levels ------------------------------------------------------- */
#define LEV_SPECIAL    100      /* Z.B. Push to Command (Quick Exit)        */
#define LEV_STP        150      /* Read Setup File                          */
#define LEV_FNM        150      /* Filename angeben, Feature Files          */
#define LEV_LINK       180      /* Windows oeffnen, verketten ...           */
#define LEV_FIO        200      /* File I/O                                 */
#define LEV_FBLK       250      /* Block-File-Operationen                   */
#define LEV_BLK        500      /* Block-Operationen                        */
#define LEV_WDW        950      /* Window Verschieben ...                   */
#define LEV_SEXIT     1000      /* Save and Exit; sonst nur Exit            */

/* macro types */
#define MPt_undefined           0
#define MPt_key_sequence        1
#define MPt_tcl                 2
#define MPt_tag                 3
#define MPt_feature             4

#define BLOCK_MODE_standard     1
#define BLOCK_MODE_line         2
#define BLOCK_MODE_box          3

#ifdef MSDOS
#define DEFAULT_WDW_MODE 0
#else
#define DEFAULT_WDW_MODE 5
#endif

#ifndef MAX_FNM_LENGTH
#ifdef MSDOS
#define MAX_FNM_LENGTH 66
#else
#define MAX_FNM_LENGTH 1026
#endif
#endif

/* find and replace options */
#define OPT_global      0x0001          /* global search                    */
#define OPT_local       0xFFFE
#define OPT_upper       0x0002          /* ignore case                      */
#define OPT_mixed       0xFFFD
#define OPT_ask         0x0004          /* ask before replace               */
#define OPT_no_ask      0xFFFB
#define OPT_backward    0x0008          /* search backward                  */
#define OPT_wrapscan    0x0010          /* wrap scan enabled                */
#define OPT_forward     0xFFF7
#define OPT_end_mark    0x0100          /*     8: end at marker #1          */
#define OPT_end_block   0x0200          /*     9: end at block end          */
#define OPT_beg_block   0x0400          /*     A: begin at block start      */

#endif /* __NED_ed__ */
