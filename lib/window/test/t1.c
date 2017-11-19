/*
 *  FILE ~/usr/window/t1.c
 *
 *  Generelle Test Routine fuer das WINDOW-System
 *
 *  written:      1989 08 16
 *  latest updte: 1994-08-20
 *
 */

#define W_MODEL_CGA
#include <gg/window.h>

/* ------------------------------------------------------------------------ */
extern struct W_SCREEN_AND_MODES w_screen_and_modes;

extern int W_TEXT_MAX_X,
           W_TEXT_MAX_Y,
           W_GRAPH_MAX_X,
           W_GRAPH_MAX_Y;

static char blit_puffer [200];

static int akt_mode     = -1,
           color        = WV_GRUEN,
           known_modes;

/* ------------------------------------------------------------------------ */
struct M
{
  int   M_v;
  char *M_n;
} ;

static struct M Mm [] =
{
  {     0, "Exit",              },
  {     9, "Menu"               },
  {     1, "Select Mode"        },
  {     2, "Text Test 1"        },
  {     5, "Text Test 2"        },
  {     3, "80 Z nchar"         },
  {     4, "BLIT"               },
  {    10, "wint"               },
  {    11, "wint2"              },
  {    12, "Check Mode"         },
  {    13, "Show modes"         },
  {    14, "Boxes"              },
} ;

/* ------------------------------------------------------------------------ */
int main ()
{
  int i, test, test_cnt;

  w_init (0x0001);
  known_modes = w_screen_and_modes.w_screen_capabilities->w_mode_count;

MENU:
  test_cnt = sizeof (Mm) / sizeof (struct M);
  for (i =0; i < test_cnt; i++)
      printf ("%3d: %s\n", i, Mm[i].M_n);

  for (;;)
  {
    w_setcup (0, 0, 0);
    printf ("                                ");
    w_setcup (0, 0, 0);
    printf ("Test #: "); scanf ("%d", &test);
    if (test < 0 || test >= test_cnt) continue;
    test = Mm[test].M_v;
    if (test == 0) break;

TEST:
    switch (test)
    { case 1: test_mode (); break;
      case 2: test_text_1 (); break;
      case 3: test_n80 (); break;
      case 4: test_blit (); break;
      case 5: test_text_2 (); break;
      case 9: goto MENU;
      case 10: wint (); break;
      case 11: wint2 (); break;
      case 12: check_mode (); break;
      case 13: show_modes (); break;
      case 14: boxes (); break;
    }
    switch (getch ())
    {
      case 0x0D: case 0x20: goto TEST;
    }
    printf ("\n");
  }

  w_init_mode (-1, 0x0001);
  return 0;
}

/* ------------------------------------------------------------------------ */
test_mode ()
{
  int i, j;
  do {
       show_modes ();
       printf ("Select Mode: "); scanf ("%d", &j);
     } while (j < -1 || j >= known_modes);
  if (j == -1) return;

  w_init_mode (j, 0x0001);
}

/* ------------------------------------------------------------------------ */
test_n80 ()
{
  int i, j;

  if (akt_mode != 80)
  {
    w_init_mode (-1, 0x0001);
    akt_mode= 80;
  }

  for (j= 24; j >= 0; j--)
    for (i= 7; i >= 0; i--)
      cga_setnchar (0, i*10, j, color, ((j*80+i) % 63) + 0x41, 12);

  color++;
  if (color > 15) color= 1;
}

/* ------------------------------------------------------------------------ */
test_text_1 ()
{
  int i, j;

  for (j=0; j<W_TEXT_MAX_Y; j++)
      for (i=0; i<W_TEXT_MAX_X; i++)
          w_setchar (0, i, j, color, ((j*40+i) % 63) + 0x41);
  color++; if (color > 15) color=1;
}

/* ------------------------------------------------------------------------ */
test_text_2 ()
{
  int i, j, v;

  for (i=2; i<W_TEXT_MAX_X; i++) w_setchar (0, i, 0, color, '0'+i/100);
  for (i=2; i<W_TEXT_MAX_X; i++) w_setchar (0, i, 1, color, '0'+(i%100)/10);
  for (i=2; i<W_TEXT_MAX_X; i++) w_setchar (0, i, 2, color, '0'+(i%10));

  for (i=2; i<W_TEXT_MAX_Y; i++) w_setchar (0, 0, i, color, '0'+i/100);
  for (i=2; i<W_TEXT_MAX_Y; i++) w_setchar (0, 1, i, color, '0'+(i%100)/10);
  for (i=2; i<W_TEXT_MAX_Y; i++) w_setchar (0, 2, i, color, '0'+(i%10));

  color++; if (color > 15) color=1;
}

/* ------------------------------------------------------------------------ */
show_modes ()
{
  int i;
  struct W_MODE_CAPABILITIES *wmc;

  for (i= 0; i < known_modes; i++)
  {
    wmc= &w_screen_and_modes.w_mode_capabilities [i];
    printf ("%s %2d %-24s %3d %3d %3d %3d %3d\n",
            (w_screen_and_modes.w_screen_capabilities->w_mode_default == i)
            ? "->" : "  ", i,
    /* wmc->w_mode_name */ "unknown",
    wmc->w_text_max_x,  wmc->w_text_max_y,
    wmc->w_graph_max_x, wmc->w_graph_max_y,
    wmc->w_graph_colors);
  }
}

/* ------------------------------------------------------------------------ */
check_mode ()
{ int m1, m2;
  m1 = w_get_mode ();
  m2 = _cga_get_mode ();
  printf ("WINDOW-Modus: %d  Bios-Modus: %d\n", m1, m2);
}

/* ------------------------------------------------------------------------ */
test_blit ()
{
  w_init_mode (-1, 0x0001); akt_mode=80;
  system ("DIR");
  
  w_blit_save (blit_puffer, 0, 2, 2, 10, 10);
  w_blit_load (blit_puffer, 0, 52, 2, 60, 10);
}

/* ------------------------------------------------------------------------ */
boxes ()
{
  int yy, cc= 1;

  if (W_GRAPH_MAX_X <= 0) return;

  for (yy=0; yy<100; yy++)
      wg_box (yy, yy, 319-yy, 199-yy, cc++);
  for (yy=0; yy<100; yy++)
      wg_box (yy, yy, 319-yy, 199-yy, cc++);
  for (yy=0; yy<100; yy++)
      wg_box (yy, yy, 319-yy, 199-yy, cc++);
}

/*****************************************************************************
 *
 *  Funktion wint
 *  Testprogramm fuer Herculeskarten Primitives
 *  1987 10 08
 *
 */


wint ()
{
  int x, y, v, i, mode;

  for (v = 0;; v %= 256)
  { w_graphmode ();
    for (x = 50; x < 200; x++)
        for (y = 50; y < 200; y++)
           wg_wr_dot (x, y, 0x81);
    for (x = 50; x < 200; x++)
        for (y = 50; y < 200; y++)
           wg_wr_dot (x, y, 0x81);

    if (getch () == 0x1b) break;
  }
  w_reset ();
}

/*****************************************************************************
 *
 *  FILE wint.c
 *  Testprogramm fuer Herculeskarten Primitives
 *  1987 10 08
 *
 */


wint2 ()
{
  int x, y, v, i, mode;

  for (v = 0;; v %= 256)
  { w_col80mode ();
    for (y = 0; y < 28; y++)
        { for (x = 0; x < 90; x++)
              w_setnchar (0,x,y,1,v++ %256,3);
          if (getch () == 0x1b) goto L1;
          w_setcup (0, 0, 24);
/*          w_printf ("Zeile %02x %3d ", y, y); ######### */
        }
L1:
    if (getch () == 0x1b) break;
    w_col40mode ();
    for (y = 0; y < 28; y++)
        { for (x = 0; x < 45; x++)
              w_setnchar (0, x,y,1,v++ %256,3);
          if (getch () == 0x1b) goto L2;
          w_setcup (0, 0, 24);
/*           w_printf ("Zeile %02x %3d ", y, y); ######### */
        }
L2:
    if (getch () == 0x1b) break;
/*    w_graphmode (); */
    for (x = 0; x < 720; x += 10)
        if (kbhit ()) { if (getch () == 0x1b) goto L3; }
        else for (y = 0; y < 348; y += 20)
                 for (i = 0; i < 12; i++)
                     wg_wr_dot (x, y+i, 0x81);
L3:
    if (getch () == 0x1b) break;
/*    w_graphmode ();     */
    for (x = 0; x < 720; x++)
        if (kbhit ()) { if (getch () == 0x1b) goto L4; }
        else for (y = 0; y < 348; y++)
                 wg_wr_dot (x, y, 0x81);
L4:
    if (getch () == 0x1b) break;
    for (x = 0; x < 720; x++)
        if (kbhit ()) { if (getch () == 0x1b) goto L5; }
        else for (y = 0; y < 348; y++)
                 wg_wr_dot (x, y, 0x00);
L5:
    if (getch () == 0x1b) break;
  }
  w_reset ();
}


