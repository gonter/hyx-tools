/*
 *  FILE C:\usr\window\win1.arc [WIN_0118.C]
 *
 *  1989 08 16: aus WIN1.SAR Åbernommen
 *              Revision
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <share.h>
#include <gg/window.h>

extern FILE *fsopen ();

static char VVV [] = "(@)Bwedit.c #D$1988-03-23 17:00:00";

/* ----------------------------------------------------------------- */
int w_more (w, fnm)
struct WINDOW *w;             /* Window, wo ...                      */
char fnm [];                  /*            ... File angezeigt wird  */
/* RETURN:   0 -> File vollstaendig auf 1 Seite angezeigt            */
/*         > 1 -> File benoetigt mehr als 1 Seite am Schirm !!       */
{ FILE *disp;
  char line [100];
  int frei, ch, fullpage = 0;

  if (access (fnm, 0) != 0) return 1;
  frei = w->by - w->ay - 1;
  disp = fsopen (fnm, "rt", O_RDONLY, SH_DENYNO, 16, &ch);
  if (disp == (FILE *) 0) return 1;
  for (;;)
    { fscanf (disp, "%[^\n]s", line); fgetc (disp);
      if (feof (disp)) break;
      if (!frei)
       { ch = mapkey ();
         fullpage = 1;
         if (ch == 0x0d) frei = 1;
         if (ch == 0x20) frei = w->by - w->ay;
         if (ch == 0x1b)
            { fclose (disp);
              return 1;
            }
       }
      w_put1ln  (w, line);
      frei--;
    }
  fclose (disp);
  return fullpage;
}

