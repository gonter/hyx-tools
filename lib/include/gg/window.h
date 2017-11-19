/*
 *  include FILE <gg/window.h>
 *
 *  Strukturdefinitionen fuer Bildschirmverwaltung
 *
 *  function redefinitions depending on windowing model
 *  - BIOS      W_MODEL_BIOS    (PCs using the BIOS alone)
 *  - CGA       W_MODEL_CGA     (PCs taking advantage of CGA programming)
 *  - CURSES    W_MODEL_CURSES  (for Unix ASCII terminals)
 *  - NCURSES   W_MODEL_NCURSES (e.g for Linux, mostly like W_MODE_CURSES)
 *  - X and TK  W_MODEL_TK      (X windows using the TK toolkit)
 *
 *  - prototypes
 *
 *  W_MODEL_MSDOS is defined if W_MODEL_BIOS or W_MODEL_CGA are defined
 *
 *  written:       1989 07 xx - 1989 09 xx: Revision
 *                 1991 01 29: Revision
 *  latest update: 1997-05-30 18:01:47
 *  $Id: window.h,v 1.4 2005/09/04 20:27:37 gonter Exp $
 *
 */

#ifndef __GG_window__
#define __GG_window__

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif
#endif

#ifdef W_MODEL_BIOS
#ifndef W_MODEL_MSDOS
#define W_MODEL_MSDOS
#endif
#endif

#ifdef W_MODEL_CGA
#ifndef W_MODEL_MSDOS
#define W_MODEL_MSDOS
#endif
#endif

/* Modus Definition Record: ----------------------------------------------- */
struct MODEDEF          /* aus MAGIS; wird nicht mehr verwendet */
{
  unsigned int
       spalten,
       zeilen,
       seiten,
       farben,
       hgfarben,
       modecode,        /* Wird an BIOS geschickt               */
       scx,             /* X-Scalierung: MSB:Up | LSD:Down      */
       scy,             /* Y-.         : .  :.  | .  :.         */
       flags;           /* Bit 0: Dieser Modus kann nicht       */
                        /*        mit anderen gemischt werden   */
                        /*     1: Grapischer Modus              */
                        /*     2: Text Modus                    */
} ;

/* ------------------------------------------------------------------------ */
struct WINDEF           /* Parameter fuer verwendete IO         */
{                       /* aus MAGIS; wird nicht mehr verwendet */
  int drivercode;       /* 1 -> CGA, EGA und Mono Treiber       */
  int modecnt;
  struct MODEDEF modedef [10];
} ;

/* Definition eines Windows: ---------------------------------------------- */
struct WINDOW
{
  int page;
  int ax, ay;
  int bx, by;
  int cx, cy;
  int attr;
} ;

/* Definition der Editor-Einstellung fuer WEDIT: --------------------------- */
struct EDITOR
{
  int anzeige;          /* 1. angezeigte Zeile                  */
  int scrupd;           /* 1 -> Screen Update noetig            */
  int f_ins;            /* 1 -> Insert Mode                     */
  int lines;            /* aktuelle Zahl der Zeilen             */
  int maxlines;         /* maximale .    .   .                  */
  int lastkey;          /* letzte nicht interpretierte Taste    */
} ;

/* Modus Definition (neue Version): --------------------------------------- */
struct W_MODE_CAPABILITIES
{
  /* allgemgeines */
  /* char *w_mode_name; */      /* Bezeichnung des Modes                    */
  int w_mode_code;              /* BIOS-Code fuer Modus                     */
                                /* -1 -> nicht ueber BIOS aufrufbar         */

  /* Text Characteristiken */
  int w_text_max_x;             /* -1 -> Text nicht verfuegbar              */
  int w_text_max_y;
  int w_text_colors;
  int w_text_cell_x;            /* Zahl der X Pixels fuer ein Zeichen       */
  int w_text_cell_y;            /* Zahl der Y Pixels fuer ein Zeichen       */
                                /* ANM: auch wenn Grafik eigentlich         */
                                /*      nicht moeglich ist. Wird fuer       */
                                /*      die Maus benoetigt                  */
  int w_text_pages;

  /* Grafik Characteristiken */
  int w_graph_max_x;            /* -1 -> Grafik nicht verfuegbar            */
  int w_graph_max_y;
  int w_graph_colors;
  int w_graph_pages;

} ;

/* Definition der Moeglichkeiten des Adapters: ---------------------------- */
struct W_SCREEN_CAPABILITIES
{
  char *w_model_name;
  int w_model_code;
  int w_mode_count;
  int w_mode_default;
} ;

/* ------------------------------------------------------------------------ */
struct W_SCREEN_AND_MODES
{
  struct W_SCREEN_CAPABILITIES          *w_screen_capabilities;
  struct W_MODE_CAPABILITIES            *w_mode_capabilities;
} ;

/* ------------------------------------------------------------------------ */
#define W_MODEL_CODE_BIOS        0x1010
#define W_MODEL_CODE_CGA         0x1011

#define W_CURSOR_LOWER  0x06
#define W_CURSOR_UPPER  0x07

/* ------------------------------------------------------------------------ */
#define W_BLINK       0x80
#define W_HELL        0x08

#define WH_SCHWARZ    0x00
#define WH_BLAU       0x10
#define WH_GRUEN      0x20
#define WH_KOBALT     0x30
#define WH_ROT        0x40
#define WH_VIOLETT    0x50
#define WH_BRAUN      0x60
#define WH_WEISS      0x70

#define WV_SCHWARZ    0x00
#define WV_BLAU       0x01
#define WV_GRUEN      0x02
#define WV_KOBALT     0x03
#define WV_ROT        0x04
#define WV_VIOLETT    0x05
#define WV_BRAUN      0x06
#define WV_WEISS      0x07

#define WV_HSCHWARZ   0x08
#define WV_HBLAU      0x09
#define WV_HGRUEN     0x0A
#define WV_HKOBALT    0x0B
#define WV_HROT       0x0C
#define WV_HVIOLETT   0x0D
#define WV_HBRAUN     0x0E
#define WV_HWEISS     0x0F

#define WV_GELB       WV_BRAUN | W_HELL
#define WV_ERROR      WV_ROT | W_HELL | W_BLINK

/* BIOS: ------------------------------------------------------------------ */
/* HYX: no_links */
#ifdef W_MODEL_BIOS
/* %win/0/(dirinf).fm */
#define w_init                  bios_init
#define w_init_mode             bios_init_mode
#define w_get_mode              bios_get_mode
#define w_reset                 bios_reset
#define w_col80mode()           bios_init_mode(0x03,0x0001)
#define w_col40mode()           bios_init_mode(0x01,0x0001)
#define w_graphmode()           bios_init_mode(0x05,0x0001)
#define w_selpage               bios_selpage
#define w_cursoroff             bios_cursoroff
#define w_cursoron              bios_cursoron
#define w_cursorsize            bios_cursorsize
#define w_border                bios_border
#define w_setchar               bios_setchar
#define w_setnchar              bios_setnchar
#define w_getchar               bios_getchar
#define w_setscreen             bios_setscreen
#define w_cls                   bios_cls
#define w_cls80                 bios_cls
#define w_cls40                 bios_cls
#define w_setarea               bios_setarea
#define w_scrollup              bios_scrollup
#define w_scrolldown            bios_scrolldown
#define w_scrblk_up             bios_scrblk_up
#define w_scrblk_down           bios_scrblk_down
#define w_setcup                bios_setcup
#define wg_wr_dot               bios_wr_dot
#define wg_rd_dot               bios_rd_dot
#define w_clear(w)              bios_scrollup((w),0);
#define w_set_mode              bios_set_mode
#define w_set_col               bios_set_col
#define w_blit_save             bios_blit_save
#define w_blit_load             bios_blit_load
#define w_get_cols              cga_get_cols
#define w_getpage               cga_getpage
#define w_scrblk_left           cga_scrblk_left
#define w_scrblk_right          cga_scrblk_right
#define w_setpalette            vga_setpalette
#define w_setpalette_block      vga_setpalette_block
#define w_getpalette            vga_getpalette
#define w_getpalette_block      vga_getpalette_block
#define w_palette_block_grey    vga_palette_block_grey
#define w_cls_col               bios_cls
#define w_getcup                bios_getcup
#define w_get_screen_max        cga_get_screen_max
#define w_blit_line             cga_blit_line
#define w_set_screen_mode       vga_set_screen_mode

/* %win/1/(dirinf).fm */
#define w_prntcol               bios_prntcol     
#define w_setstring             bios_setstring
#define w_create                bios_create      
#define w_namecreat             bios_namecreat   
#define gr_create               bios_gr_create
#define w_put1ln                bios_put1ln      
#define w_putln                 bios_putln       
#define w_putstr                bios_putstr      
#define w_readstr               bios_readstr     
#define w_readln                bios_readln      
#define w_disp_bbox             bios_disp_bbox
#define w_disp_box              bios_disp_box
#define w_printf                bios_printf
#define w_more                  bios_more
#define w_puts                  bios_puts
#define w_display               bios_display
#define w_display_scr           bios_display_scr
#define w_prtstr                bios_prtstr
#define w_print_long            bios_print_long
#define w_bell                  bios_bell

/* %win/2/(dirinf).fm */
#define wg_box                  bios_box        
#define wg_fbox                 bios_fbos
#define wg_circle               bios_circle
#define wg_fcircle              bios_fcircle
#define _wg_x_line              _bios_x_line
#define _wg_y_line              _bios_y_line
#endif /* W_MODEL_BIOS */

/* CGA: ------------------------------------------------------------------- */
#ifdef W_MODEL_CGA
/* %win/0/(dirinf).fm */
#define w_init                  cga_init
#define w_init_mode             cga_init_mode
#define w_get_mode              cga_get_mode
#define w_reset                 cga_reset
#define w_col80mode()           cga_init_mode(0x03,0x0001)
#define w_col40mode()           cga_init_mode(0x01,0x0001)
#define w_graphmode()           cga_init_mode(0x05,0x0001)
#define w_selpage               cga_selpage
#define w_cursoroff             bios_cursoroff
#define w_cursoron              bios_cursoron
#define w_cursorsize            bios_cursorsize
#define w_border                bios_border
#define w_setchar               cga_setchar
#define w_setnchar              cga_setnchar
#define w_getchar               cga_getchar
#define w_setscreen             bios_setscreen
#define w_cls()                 cga_cls_col(WV_GELB)
#define w_cls80()               cga_cls_col(WV_GELB)
#define w_cls40()               cga_cls_col(WV_GELB)
#define w_setarea               bios_setarea
#define w_scrollup              bios_scrollup
#define w_scrolldown            bios_scrolldown
#define w_scrblk_up             bios_scrblk_up
#define w_scrblk_down           bios_scrblk_down
#define w_setcup                bios_setcup
#define wg_wr_dot               bios_wr_dot
#define wg_rd_dot               bios_rd_dot
#define w_clear(w)              bios_scrollup((w),0)
#define w_set_mode              bios_set_mode
#define w_set_col               bios_set_col
#define w_blit_save             cga_blit_save
#define w_blit_load             cga_blit_load
#define w_get_cols              cga_get_cols
#define w_getpage               cga_getpage
#define w_scrblk_left           cga_scrblk_left
#define w_scrblk_right          cga_scrblk_right
#define w_setpalette            vga_setpalette
#define w_setpalette_block      vga_setpalette_block
#define w_getpalette            vga_getpalette
#define w_getpalette_block      vga_getpalette_block
#define w_palette_block_grey    vga_palette_block_grey
#define w_cls_col               cga_cls_col
#define w_getcup                bios_getcup
#define w_get_screen_max        cga_get_screen_max
#define w_blit_line             cga_blit_line
#define w_set_screen_mode       vga_set_screen_mode

/* %win/1/(dirinf).fm */
#define w_prntcol               cga_prntcol     
#define w_setstring             cga_setstring
#define w_create                bios_create      
#define w_namecreat             cga_namecreat   
#define gr_create               bios_gr_create
#define w_put1ln                cga_put1ln      
#define w_putln                 bios_putln       
#define w_putstr                bios_putstr      
#define w_readstr               bios_readstr
#define w_readln                bios_readln
#define w_disp_bbox             cga_disp_bbox
#define w_disp_box              cga_disp_box
#define w_printf                cga_printf
#define w_more                  cga_more
#define w_puts                  cga_puts
#define w_display               cga_display
#define w_display_scr           cga_display_scr
#define w_prtstr                cga_prtstr
#define w_print_long            cga_print_long
#define w_bell                  bios_bell

/* %win/2/(dirinf).fm */
#define wg_box                  bios_box        
#define wg_fbox                 bios_fbos
#define wg_circle               bios_circle
#define wg_fcircle              bios_fcircle
#define _wg_x_line              _bios_x_line
#define _wg_y_line              _bios_y_line
#endif /* W_MODEL_CGA */

/* CURSES ----------------------------------------------------------------- */
#ifdef W_MODEL_CURSES
#define w_init                  curses_init
#define w_cls                   curses_cls_col
#define w_disp_bbox             curses_disp_bbox
#define w_disp_box              curses_disp_box
#define w_setstring             curses_setstring
#define w_setchar               curses_setchar
#define w_setnchar              curses_setnchar
#define w_prntcol               curses_prntcol
#define w_setcup                curses_setcup
#define w_scrblk_up             curses_scrblk_up
#define w_scrblk_down           curses_scrblk_down
#define w_scrblk_left           curses_scrblk_left
#define w_scrblk_right          curses_scrblk_right
#define w_blit_line             curses_blit_line
#define w_sig_winch             curses_sig_winch
#ifndef W_MODEL_NCURSES
#define w_bell                  bios_bell
#endif /* W_MODEL_NCURSES */
#endif

/* NCURSES ---------------------------------------------------------------- */
#ifdef W_MODEL_NCURSES
#define w_init                  curses_init
#define w_cls                   curses_cls_col
#define w_disp_bbox             curses_disp_bbox
#define w_disp_box              curses_disp_box
#define w_setstring             curses_setstring
#define w_setchar               curses_setchar
#define w_setnchar              curses_setnchar
#define w_prntcol               curses_prntcol
#define w_setcup                curses_setcup
#define w_blit_line             curses_blit_line
#define w_bell                  ncurses_bell
#define w_sig_winch             curses_sig_winch
#endif

/* X and TK --------------------------------------------------------------- */
#ifdef W_MODEL_TK
#define w_setstring             tk_setstring
#define w_setchar               tk_setchar
#define w_setnchar              tk_setnchar
#define w_prntcol               tk_prntcol
#define w_init                  tk_init
#define w_setcup                tk_setcup
#define w_cls                   tk_cls
#define w_bell                  tk_bell
#define w_scrblk_up             tk_scrblk_up
#define w_scrblk_down           tk_scrblk_down
#define w_scrblk_left           tk_scrblk_left
#define w_scrblk_right          tk_scrblk_right
#define w_sig_winch             tk_sig_winch
#endif

/* prototypes: %win/x/(dirinf).fm ----------------------------------------- */
void cdecl w_init (int flags);
int cdecl w_init_mode (int, int);
int cdecl w_get_mode (void);
void cdecl w_reset (void);
void cdecl w_selpage (int);
void cdecl w_cursoroff (void);
void cdecl w_cursoron (void);
void cdecl w_cursorsize (int lower, int upper);
void cdecl w_border (int);
void cdecl w_setcup (int, int, int);
void cdecl w_setchar (int, int, int, int, int);
void cdecl w_setnchar (int, int, int, int, int, int);
int cdecl w_getchar (int, int, int);
void cdecl w_setarea (int, int, int, int, int, int);
int cdecl w_scrollup (struct WINDOW *, int);
int cdecl w_scrolldown (struct WINDOW *, int);
int cdecl w_scrblk_up (int ax, int ay, int bx, int by, int attr, int cnt);
int cdecl w_scrblk_down (int ax, int ay, int bx, int by, int attr, int cnt);
int cdecl w_scrblk_left (int page, int ax, int ay, int bx, int by,
                         int attr, int cnt);
int cdecl w_scrblk_right (int page, int ax, int ay, int bx, int by,
                          int attr, int cnt);
int cdecl wg_wr_dot (int, int, int);
int cdecl wg_rd_dot (int, int);
int cdecl w_set_mode (int);
void cdecl w_set_col (int, int);
int cdecl w_blit_save (void *puffer, int page, int ax, int ay, int bx,int by);
int cdecl w_blit_load (void *puffer, int page, int ax, int ay, int bx,int by);
int cdecl w_get_cols (void);
int cdecl w_getpage (void);
int cdecl w_setpalette (int nr, int red, int green, int blue);
int cdecl w_setpalette_block (int start, int count, void *table);
int cdecl w_getpalette (int nr, int *red, int *green, int *blue);
int cdecl w_getpalette_block (int start, int count, void *table);
int cdecl w_palette_block_grey (int start, int count);
void cdecl cga_cls_col (int color);
void cdecl cursor_cls_col (int color);
void cdecl tk_cls (void);
void cdecl bios_cls (void);
void cdecl w_getcup (int p, int *x, int *y);
void cdecl w_get_screen_max (void);
void cdecl w_blit_line (int page, int ax, int ay, int cnt, char *line);
int cdecl vga_set_screen_mode (int mode);

/* %win/1/(dirinf).fm ----------------------------------------------------- */
void cdecl w_prntcol (int, int, int, int, char *);
void cdecl w_create (struct WINDOW *);
void cdecl w_namecreat (struct WINDOW *, char *);
void cdecl gr_create (struct WINDOW *);
void cdecl w_disp_bbox (int page, int ax, int ay, int bx, int by,
                        int attr, int box_typ);
void cdecl w_disp_box (int page, int ax, int ay, int bx, int by,
                       int attr, int box_typ, int box_edges);
void cdecl gr_setcup (int, int);
void cdecl cga_setcup (int, int, int);
void cdecl ega_setcup (int, int, int);
void cdecl w_setstring (int, int, int, int, int, int, const char *, int);
void cdecl w_putstr (struct WINDOW *, char *);
void cdecl w_setscreen (int attr);/*Page und SP nicht benoetigt*/
int cdecl w_readstr (struct WINDOW *, char *);
int cdecl w_readln (struct WINDOW *, char *);
int cdecl mapkey (void);
void cdecl w_put1ln (struct WINDOW *, char *);
void cdecl w_putln (struct WINDOW *, char *);
void cdecl w_display (int page, char *scr);
void cdecl w_display_scr (int page, char *s);
void cdecl w_prtstr (int p, int x, int y, int attr, char *nm, int l);
void cdecl w_print_long (int p, int x, int y, int c, char *fmt, long val);
void cdecl w_set_332_palette (void);

/* %win/2/(dirinf).fm ----------------------------------------------------- */
void cdecl wg_box (int, int, int, int, int);
void cdecl wg_fbox (int, int, int, int, int);
void cdecl wg_circle (int, int, int, int);
void cdecl wg_fcircle (int, int, int, int);
void cdecl _wg_x_line (int, int, int, int);
void cdecl _wg_y_line (int, int, int, int);

void cdecl report_attribute_value (int attr, char *s);
void cdecl w_bell (void);
void cdecl w_sig_winch (void);
#endif
