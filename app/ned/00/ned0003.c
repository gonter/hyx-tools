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
   { 0, 1, "³Save & Reload³", (long) (&MMitem[56]),      0, 1 } ,
   { 0, 2, "³Save & Close ³", (long) (&MMitem[ 1]),      0, 1 } ,
   { 0, 3, "³Save & Exit  ³", (long) (&MMitem[ 0]),      0, 1 } ,
   { 0, 4, "³Save         ³", (long) (&MMitem[ 2]),      0, 1 } ,
   { 0, 5, "³Restore File ³", (long) (&MMitem[ 3]),      0, 1 } ,
   { 0, 6, "³ÄÄÄÄÄÄÄÄÄÄÄÄÄ³", -1L,                       0, 1 } ,
   { 0, 7, "³Abort        ³", (long) (&MMitem[ 4]),      0, 1 } ,
   { 0, 8, "³Panic        ³", (long) (&MMitem[ 5]),      0, 1 } ,
   { 0, 9, "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÙ", -1L,                       0, 1 } ,

   { 1, 0, "Cluster", -1L,                               0, 1 } ,
   { 1, 1, "³$$root    ³", (long) (&MMitem[ 6]),         0, 1 } ,
   { 1, 2, "³$$notes   ³", (long) (&MMitem[ 7]),         0, 1 } ,
   { 1, 3, "³$$help    ³", (long) (&MMitem[ 8]),         0, 1 } ,
   { 1, 4, "³cl? + fr? ³", (long) (&MMitem[ 9]),         0, 1 } ,
   { 1, 5, "³%cl0:start³", (long) (&MMitem[57]),         0, 1 } ,
   { 1, 6, "³%cl1:help ³", (long) (&MMitem[10]),         0, 1 } ,
   { 1, 7, "³%cl2:notes³", (long) (&MMitem[11]),         0, 1 } ,
   { 1, 8, "³%cl3:     ³", (long) (&MMitem[12]),         0, 1 } ,
   { 1, 9, "³%cl4:t2d  ³", (long) (&MMitem[13]),         0, 1 } ,
   { 1,10, "ÀÄÄÄÄÄÄÄÄÄÄÙ", -1L,                          0, 1 } ,

   { 2, 0, "Window", -1L,                               0, 1 } ,
   { 2, 1, "³open         ³", (long) (&MMitem[16]),     0, 1 } ,
   { 2, 2, "³read         ³", (long) (&MMitem[17]),     0, 1 } ,
   { 2, 3, "³link         ³", (long) (&MMitem[18]),     0, 1 } ,
   { 2, 4, "³selection box³", (long) (&MMitem[19]),     0, 1 } ,
   { 2, 5, "³stack windows³", (long) (&MMitem[20]),     0, 1 } ,
   { 2, 6, "³ÄÄÄÄÄÄÄÄÄÄÄÄÄ³", -1L,                      0, 1 } ,
   { 2, 7, "³ins/ovr      ³", (long) (&MMitem[14]),     0, 1 } ,
   { 2, 8, "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÙ", -1L,                      0, 1 } ,

   { 3, 0, "Block", -1L,                                0, 1 } ,
   { 3, 1, "³mark begin³",    (long) (&MMitem[44]),     0, 1 } ,
   { 3, 2, "³mark end  ³",    (long) (&MMitem[45]),     0, 1 } ,
   { 3, 3, "³copy      ³",    (long) (&MMitem[46]),     0, 1 } ,
   { 3, 4, "³move      ³",    (long) (&MMitem[47]),     0, 1 } ,
   { 3, 5, "³delete    ³",    (long) (&MMitem[49]),     0, 1 } ,
   { 3, 6, "³iconify   ³",    (long) (&MMitem[48]),     0, 1 } ,
   { 3, 7, "ÀÄÄÄÄÄÄÄÄÄÄÙ",    -1L,                      0, 1 } ,

/*   4 ... frei */
/*   5 ... frei */

   { 6, 0, "Hyper", -1L,                                 0, 1 } ,
   { 6, 1, "³->next         ³", (long) (&MMitem[21]),    0, 1 } ,
   { 6, 2, "³->prev         ³", (long) (&MMitem[22]),    0, 1 } ,
   { 6, 3, "³->up           ³", (long) (&MMitem[23]),    0, 1 } ,
   { 6, 4, "³->menu         ³", (long) (&MMitem[24]),    0, 1 } ,
   { 6, 5, "³->lang         ³", (long) (&MMitem[25]),    0, 1 } ,
   { 6, 6, "³->sort         ³", (long) (&MMitem[51]),    0, 1 } ,
   { 6, 7, "³->view         ³", (long) (&MMitem[52]),    0, 1 } ,
   { 6, 8, "³->??           ³", (long) (&MMitem[26]),    0, 1 } ,
   { 6, 9, "³links ??       ³", (long) (&MMitem[27]),    0, 1 } ,
   { 6,10, "³logic links ?? ³", (long) (&MMitem[28]),    0, 1 } ,
   { 6,11, "³ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ³", (long) (&MMitem[29]),    0, 1 } ,
   { 6,12, "³mem. location  ³", (long) (&MMitem[31]),    0, 1 } ,
   { 6,13, "³forget location³", (long) (&MMitem[61]),    0, 1 } ,
   { 6,14, "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ", -1L,                     0, 1 } ,

   { 7, 0, "SGML", -1L,                                  0, 1 } ,
   { 7, 1, "³set entity      ³", (long) (&MMitem[33]),   0, 1 } ,
   { 7, 2, "³set tag         ³", (long) (&MMitem[32]),   0, 1 } ,
   { 7, 3, "³set 'mark' tag  ³", (long) (&MMitem[50]),   0, 1 } ,
   { 7, 4, "³set 'hyx.l' tag ³", (long) (&MMitem[30]),   0, 1 } ,
   { 7, 5, "³lookup+set link ³", (long) (&MMitem[55]),   0, 1 } ,
   { 7, 6, "³ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ³", -1L,                    0, 1 } ,
   { 7, 7, "³set feature     ³", (long) (&MMitem[53]),   0, 1 } ,
   { 7, 8, "³reset feature   ³", (long) (&MMitem[54]),   0, 1 } ,
   { 7, 9, "³edit features   ³", (long) (&MMitem[34]),   0, 1 } ,
   { 7,10, "³ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ³", -1L,                    0, 1 } ,
   { 7,11, "³tag disp normal ³", (long) (&MMitem[58]),   0, 1 } ,
   { 7,12, "³tag disp        ³", (long) (&MMitem[59]),   0, 1 } ,
   { 7,13, "³tag disp full   ³", (long) (&MMitem[60]),   0, 1 } ,
   { 7,14, "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ", -1L,                    0, 1 } ,

   { 8, 0, "Setup", -1L,                                0, 1 } ,
   { 8, 1, "³ED setup ³", (long) (&MMitem[35]),         0, 1 } ,
   { 8, 2, "³RD setup ³", (long) (&MMitem[36]),         0, 1 } ,
   { 8, 3, "³def macro³", (long) (&MMitem[37]),         0, 1 } ,
   { 8, 4, "ÀÄÄÄÄÄÄÄÄÄÙ", -1L,                          0, 1 } ,

   { 9, 0, "Misc", -1L,                                 0, 1 } ,
   { 9, 1, "³Shell         ³", (long) (&MMitem[38]),    0, 1 } ,
   { 9, 2, "³Author        ³", (long) (&MMitem[39]),    0, 1 } ,
   { 9, 3, "³Window Page   ³", (long) (&MMitem[40]),    0, 1 } ,
   { 9, 4, "³VI mode       ³", (long) (&MMitem[41]),    0, 1 } ,
   { 9, 5, "³insert mode   ³", (long) (&MMitem[42]),    0, 1 } ,
   { 9, 6, "³overwrite mode³", (long) (&MMitem[43]),    0, 1 } ,
   { 9, 7, "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ", -1L,                     0, 1 }
} ;

/* Maus + Menue Steuerung ------------------------------------------------- */
void maus_setup ()
{
  int x, y;

  x= sizeof (MMs) / sizeof (struct MMen_short);
  for (y= 0; y < x; y++) mm_short_install_function (&MMs [y]);
}
