/*
 *  FILE %ned/00/ned0003.c
 *
 *  mouse menus for the editor NED
 *
 *  written:       1987 03 21
 *                 1988 ?? ??: Kommando System (fuer Setup)
 *                 1989 04 23: Maus Menu System
 *                 1992 07 12: Reorganisation der Menu Items
 *  latest update: 1998-08-15 12:28:24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/maus.h>

#include "ned0009.c"            /* Deklaration der primitiven Funktionen    */

void cdecl maus_setup (void);

/* ------------------------------------------------------------------------ */
static struct mm_item MMitem [] =
{
/* 00 */ { 1, 0, (long) p_sx } ,
/* 01 */ { 1, 0, (long) p_ssave } ,
/* 02 */ { 1, 0, (long) p_save } ,
/* 03 */ { 1, 0, (long) p_fget } ,
/* 04 */ { 1, 0, (long) p_abandon } ,
/* 05 */ { 1, 0, (long) p_qabandon } ,
/* 06 */ { 1, 0, (long) p_activate_fr_root } ,
/* 07 */ { 1, 0, (long) p_activate_fr_notes } ,
/* 08 */ { 1, 0, (long) p_activate_fr_help } ,
/* 09 */ { 1, 0, (long) ned_p_activate_cl_fr } ,

/* 10 */ { 1, 0, (long) p_activate_cl1 } ,
/* 11 */ { 1, 0, (long) p_activate_cl2 } ,
/* 12 */ { 1, 0, (long) p_activate_cl3 } ,
/* 13 */ { 1, 0, (long) p_activate_cl4 } ,
/* 14 */ { 1, 0, (long) p_ovins } ,
/* 15 */ { 1, 0, (long) p_turn_line } ,          /* unused */
/* 16 */ { 1, 0, (long) p_wdwopen } ,
/* 17 */ { 1, 0, (long) p_ofile1} ,
/* 18 */ { 1, 0, (long) p_link } ,
/* 19 */ { 1, 0, (long) p_window_menu } ,

/* 20 */ { 1, 0, (long) p_wdwfaecher } ,
/* 21 */ { 1, 0, (long) p_logic_link_next } ,
/* 22 */ { 1, 0, (long) p_logic_link_prev } ,
/* 23 */ { 1, 0, (long) p_logic_link_up } ,
/* 24 */ { 1, 0, (long) p_logic_link_menu } ,
/* 25 */ { 1, 0, (long) p_logic_link_lang } ,
/* 26 */ { 1, 0, (long) p_logic_link } ,
/* 27 */ { 1, 0, (long) p_link_more } ,
/* 28 */ { 1, 0, (long) p_logic_link_more } ,
/* 29 */ { 1, 0, (long) p_logic_link } ,

/* 30 */ { 1, 0, (long) ned_set_hyx_l } ,
/* 31 */ { 1, 0, (long) ned_memorize_location } ,
/* 32 */ { 1, 0, (long) ned_set_SGML_tag } ,
/* 33 */ { 1, 0, (long) ned_set_SGML_entity } ,
/* 34 */ { 1, 0, (long) p_link_feature } ,
/* 35 */ { 1, 0, (long) p_edsetup } ,
/* 36 */ { 1, 0, (long) p_rdsetup } ,
/* 37 */ { 1, 0, (long) p_mac_define } ,
/* 38 */ { 1, 0, (long) p_shell } ,
/* 39 */ { 1, 0, (long) ned_show_author } ,

/* 40 */ { 1, 0, (long) p_pushpage } ,
/* 41 */ { 1, 0, (long) vi_on } ,
/* 42 */ { 1, 0, (long) vi_ins } ,
/* 43 */ { 1, 0, (long) vi_ovr } ,
/* 44 */ { 1, 0, (long) p_blkbeg } ,
/* 45 */ { 1, 0, (long) p_blkend } ,
/* 46 */ { 1, 0, (long) ned_blk_copy } ,
/* 47 */ { 1, 0, (long) ned_blk_move } ,
/* 48 */ { 1, 0, (long) ned_blk_iconify } ,
/* 49 */ { 1, 0, (long) ned_blk_delete } ,

/* 50 */ { 1, 0, (long) ned_set_mark } ,
/* 51 */ { 1, 0, (long) p_logic_link_sort } ,
/* 52 */ { 1, 0, (long) p_logic_link_view } ,
/* 53 */ { 1, 0, (long) p_feature_set } ,
/* 54 */ { 1, 0, (long) p_feature_reset } ,
/* 55 */ { 1, 0, (long) ned_set_lookup_tag } ,
/* 56 */ { 1, 0, (long) p_save_reload } ,
/* 57 */ { 1, 0, (long) p_activate_cl0 } ,
/* 58 */ { 1, 0, (long) p_show_tag_normally } ,
/* 59 */ { 1, 0, (long) p_show_tag } ,

/* 60 */ { 1, 0, (long) p_show_full_tag } ,
/* 61 */ { 1, 0, (long) ned_forget_location }
} ;

/* ------------------------------------------------------------------------ */
static struct MMen_short MMs [] =
{
   { 0, 0, "File",           -1L,                        0, 1 } ,
   { 0, 1, "�Save & Reload�", (long) (&MMitem[56]),      0, 1 } ,
   { 0, 2, "�Save & Close �", (long) (&MMitem[ 1]),      0, 1 } ,
   { 0, 3, "�Save & Exit  �", (long) (&MMitem[ 0]),      0, 1 } ,
   { 0, 4, "�Save         �", (long) (&MMitem[ 2]),      0, 1 } ,
   { 0, 5, "�Restore File �", (long) (&MMitem[ 3]),      0, 1 } ,
   { 0, 6, "�������������ĳ", -1L,                       0, 1 } ,
   { 0, 7, "�Abort        �", (long) (&MMitem[ 4]),      0, 1 } ,
   { 0, 8, "�Panic        �", (long) (&MMitem[ 5]),      0, 1 } ,
   { 0, 9, "���������������", -1L,                       0, 1 } ,

   { 1, 0, "Cluster", -1L,                               0, 1 } ,
   { 1, 1, "�$$root    �", (long) (&MMitem[ 6]),         0, 1 } ,
   { 1, 2, "�$$notes   �", (long) (&MMitem[ 7]),         0, 1 } ,
   { 1, 3, "�$$help    �", (long) (&MMitem[ 8]),         0, 1 } ,
   { 1, 4, "�cl? + fr? �", (long) (&MMitem[ 9]),         0, 1 } ,
   { 1, 5, "�%cl0:start�", (long) (&MMitem[57]),         0, 1 } ,
   { 1, 6, "�%cl1:help �", (long) (&MMitem[10]),         0, 1 } ,
   { 1, 7, "�%cl2:notes�", (long) (&MMitem[11]),         0, 1 } ,
   { 1, 8, "�%cl3:     �", (long) (&MMitem[12]),         0, 1 } ,
   { 1, 9, "�%cl4:t2d  �", (long) (&MMitem[13]),         0, 1 } ,
   { 1,10, "������������", -1L,                          0, 1 } ,

   { 2, 0, "Window", -1L,                               0, 1 } ,
   { 2, 1, "�open         �", (long) (&MMitem[16]),     0, 1 } ,
   { 2, 2, "�read         �", (long) (&MMitem[17]),     0, 1 } ,
   { 2, 3, "�link         �", (long) (&MMitem[18]),     0, 1 } ,
   { 2, 4, "�selection box�", (long) (&MMitem[19]),     0, 1 } ,
   { 2, 5, "�stack windows�", (long) (&MMitem[20]),     0, 1 } ,
   { 2, 6, "�������������ĳ", -1L,                      0, 1 } ,
   { 2, 7, "�ins/ovr      �", (long) (&MMitem[14]),     0, 1 } ,
   { 2, 8, "���������������", -1L,                      0, 1 } ,

   { 3, 0, "Block", -1L,                                0, 1 } ,
   { 3, 1, "�mark begin�",    (long) (&MMitem[44]),     0, 1 } ,
   { 3, 2, "�mark end  �",    (long) (&MMitem[45]),     0, 1 } ,
   { 3, 3, "�copy      �",    (long) (&MMitem[46]),     0, 1 } ,
   { 3, 4, "�move      �",    (long) (&MMitem[47]),     0, 1 } ,
   { 3, 5, "�delete    �",    (long) (&MMitem[49]),     0, 1 } ,
   { 3, 6, "�iconify   �",    (long) (&MMitem[48]),     0, 1 } ,
   { 3, 7, "������������",    -1L,                      0, 1 } ,

/*   4 ... frei */
/*   5 ... frei */

   { 6, 0, "Hyper", -1L,                                 0, 1 } ,
   { 6, 1, "�->next         �", (long) (&MMitem[21]),    0, 1 } ,
   { 6, 2, "�->prev         �", (long) (&MMitem[22]),    0, 1 } ,
   { 6, 3, "�->up           �", (long) (&MMitem[23]),    0, 1 } ,
   { 6, 4, "�->menu         �", (long) (&MMitem[24]),    0, 1 } ,
   { 6, 5, "�->lang         �", (long) (&MMitem[25]),    0, 1 } ,
   { 6, 6, "�->sort         �", (long) (&MMitem[51]),    0, 1 } ,
   { 6, 7, "�->view         �", (long) (&MMitem[52]),    0, 1 } ,
   { 6, 8, "�->??           �", (long) (&MMitem[26]),    0, 1 } ,
   { 6, 9, "�links ??       �", (long) (&MMitem[27]),    0, 1 } ,
   { 6,10, "�logic links ?? �", (long) (&MMitem[28]),    0, 1 } ,
   { 6,11, "���������������ĳ", (long) (&MMitem[29]),    0, 1 } ,
   { 6,12, "�mem. location  �", (long) (&MMitem[31]),    0, 1 } ,
   { 6,13, "�forget location�", (long) (&MMitem[61]),    0, 1 } ,
   { 6,14, "�����������������", -1L,                     0, 1 } ,

   { 7, 0, "SGML", -1L,                                  0, 1 } ,
   { 7, 1, "�set entity      �", (long) (&MMitem[33]),   0, 1 } ,
   { 7, 2, "�set tag         �", (long) (&MMitem[32]),   0, 1 } ,
   { 7, 3, "�set 'mark' tag  �", (long) (&MMitem[50]),   0, 1 } ,
   { 7, 4, "�set 'hyx.l' tag �", (long) (&MMitem[30]),   0, 1 } ,
   { 7, 5, "�lookup+set link �", (long) (&MMitem[55]),   0, 1 } ,
   { 7, 6, "����������������ĳ", -1L,                    0, 1 } ,
   { 7, 7, "�set feature     �", (long) (&MMitem[53]),   0, 1 } ,
   { 7, 8, "�reset feature   �", (long) (&MMitem[54]),   0, 1 } ,
   { 7, 9, "�edit features   �", (long) (&MMitem[34]),   0, 1 } ,
   { 7,10, "����������������ĳ", -1L,                    0, 1 } ,
   { 7,11, "�tag disp normal �", (long) (&MMitem[58]),   0, 1 } ,
   { 7,12, "�tag disp        �", (long) (&MMitem[59]),   0, 1 } ,
   { 7,13, "�tag disp full   �", (long) (&MMitem[60]),   0, 1 } ,
   { 7,14, "������������������", -1L,                    0, 1 } ,

   { 8, 0, "Setup", -1L,                                0, 1 } ,
   { 8, 1, "�ED setup �", (long) (&MMitem[35]),         0, 1 } ,
   { 8, 2, "�RD setup �", (long) (&MMitem[36]),         0, 1 } ,
   { 8, 3, "�def macro�", (long) (&MMitem[37]),         0, 1 } ,
   { 8, 4, "�����������", -1L,                          0, 1 } ,

   { 9, 0, "Misc", -1L,                                 0, 1 } ,
   { 9, 1, "�Shell         �", (long) (&MMitem[38]),    0, 1 } ,
   { 9, 2, "�Author        �", (long) (&MMitem[39]),    0, 1 } ,
   { 9, 3, "�Window Page   �", (long) (&MMitem[40]),    0, 1 } ,
   { 9, 4, "�VI mode       �", (long) (&MMitem[41]),    0, 1 } ,
   { 9, 5, "�insert mode   �", (long) (&MMitem[42]),    0, 1 } ,
   { 9, 6, "�overwrite mode�", (long) (&MMitem[43]),    0, 1 } ,
   { 9, 7, "����������������", -1L,                     0, 1 }
} ;

/* Maus + Menue Steuerung ------------------------------------------------- */
void maus_setup ()
{
  int x, y;

  x= sizeof (MMs) / sizeof (struct MMen_short);
  for (y= 0; y < x; y++) mm_short_install_function (&MMs [y]);
}
