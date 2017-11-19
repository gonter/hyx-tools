/*
 *  include FILE <gg/maus.h>
 *
 *  written:       1988 09 04
 *  latest update: 1995-04-29
 *
 */

#ifndef __GG_maus__
#define __GG_maus__

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif
#endif

#define MAUS_key_left          0x01
#define MAUS_key_right         0x02
#define MAUS_key_middle        0x04

/* Pop Up Menue ----------------------------------------------------------- */
struct MMen
{
  int   mm_sub_sp;
  int   mm_sub_z;
  char *mm_name;
  long  mm_function;
  int   mm_key;                 /* Tastencode                           */
  int   mm_type;                /* 0 -> leer                            */
                                /* 1 -> vordefiniert                    */
                                /* 2 -> Setup (dynamisch allociert)     */
  struct MMen *mm_next;
  struct MMen *mm_sub;
} ;

/* Pop Up Menue ----------------------------------------------------------- */
struct MMen_short
{
  int   mm_sub_sp;
  int   mm_sub_z;
  char *mm_name;
  long  mm_function;
  int   mm_key;                 /* Tastencode                           */
  int   mm_type;                /* 0 -> leer                            */
                                /* 1 -> vordefiniert                    */
                                /* 2 -> Setup (dynamisch allociert)     */
} ;

/* Pop Up Menue Steuerung ------------------------------------------------- */
struct MMctrl
{
  struct MMen *mm_men;
  int mm_akt_page;
  int mm_menu_line;
  int mm_color_1;
  int mm_color_2;
  int mm_color_3;
  int mm_color_4;
  int mm_smen;
  int mm_sel;
} ;

/* ANM: Die Struktur MMctrl beschreibt das Menue-System vollst„ndig.        */
/*      Mit mm_save und und mm_load k”nnen unterschiedliche Menue-System    */
/*      umgeschaltet werden !!!                                             */

/* Maus Library ----------------------------------------------------------- */
struct SELBOX_LIST
{
  struct SELBOX_LIST *sbl_next;
  struct SELBOX_LIST *sbl_prev;
  char *sbl_display;
  long  sbl_cookie;
} ;

/* Maus Library ----------------------------------------------------------- */
int     cdecl maus_reset                (void);
void    cdecl maus_enable               (void);
void    cdecl maus_disable              (void);
void    cdecl maus_position             (int *, int *, int *);
void    cdecl maus_setposition          (int, int);
void    cdecl maus_set_x_margins        (int min_x, int max_x);
void    cdecl maus_set_y_margins        (int min_y, int max_y);
void    cdecl maus_set_cursor_type      (int type, int p1, int p2);

/* Pop Up Menue ----------------------------------------------------------- */
#ifdef W_MODEL_CGA
#define mm_maus_menu           mmcga_maus_menu
#define mm_install_function    mmcga_install_function
#define mm_setup               mmcga_setup
#define mm_clear_menu          mmcga_clear_menu
#define mm_save                mmcga_save
#define mm_load                mmcga_load
#define mm_set_home            mmcga_set_home

#define mm_short_install_function mmcga_short_install_function
#endif

#ifdef W_MODEL_BIOS
#define mm_maus_menu           mmbios_maus_menu
#define mm_install_function    mmbios_install_function
#define mm_setup               mmbios_setup
#define mm_clear_menu          mmbios_clear_menu
#define mm_save                mmbios_save
#define mm_load                mmbios_load
#define mm_set_home            mmbios_set_home

#define mm_short_install_function mmbios_short_install_function
#endif

/* ------------------------------------------------------------------------ */
long    cdecl mm_maus_menu (int mode, int use_maus, int use_key);
int     cdecl mm_install_function (int spalte, int zeile, char *name,
                                   long value, int m_key, int modus);
void    cdecl mm_setup (int, int, int, int, int, int);
void    cdecl mm_clear_menu (void);
void    cdecl mm_save (struct MMctrl *);
void    cdecl mm_load (struct MMctrl *);
void    cdecl mm_set_home (void);

int     cdecl mm_short_install_function (struct MMen_short *mm);

/* selbox01: -------------------------------------------------------------- */
int cdecl selbox_select (int mode, int act_page, int ax, int ay,
            int bx, int by, int cy, int box_type, int box_colour,
            int text_colour, int sel_colour, struct SELBOX_LIST *sbl,
            long *cookie);

#endif /* __GG_maus__ */
