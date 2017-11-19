/*
 *  FILE %ned/unix/harness.c
 *
 *  hack out unresolved symbols for testing purposes
 *
 *  written:       1992-12-02
 *  latest update: 1997-06-13 13:44:51
 *
 */

/* GG's window library */
int w_init_mode () { return 0; }
void w_selpage () {}
int w_blit_save () { return 0; }
int w_blit_load () { return 0; }
void w_cursoron () {}
int w_set_screen_mode () { return 0; }
int w_get_mode () { return 0; }

/* mouse stuff */
#ifdef NOT_USED
maus_enable () {}
maus_disable () {}
maus_position () {}
mmcga_maus_menu () {}
#endif
int mm_install_function () { return 0; }

/* NEU: */
void w_cursorsize () {}
