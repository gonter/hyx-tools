/*
 *  FILE /usr/sbr/arcfiles.c
 *
 *  Verarbeiten von Archiv Files fÅr FM File Manager
 *
 *  1989 01 20
 *  1989 07 02: File ARCHEAD.H extrahiert
 *  1990 02 03: Revision
 *
 */

# include <stdio.h>
# include <dos.h>
# include <direct.h>
# include <ctype.h>
# include <string.h>
# include <gg/fnames.h>
# include <gg/archead.h>

static struct heads pu;

# pragma check_stack(off)

/* ------------------------------------------------------------------------ */
int get_arc_file (
FILE *fi,               /* Archiv File, binÑr erîffnet  */
struct dta_buff *p)     /* DOS DTA-Puffer               */
/* RETURN:  -1 Error or no Archive                      */
/*           0 EOF: no more files in archive            */
/*           1 Archiv File gefunden; DTA gÅltig         */
{ int ch;

  if (feof (fi)) return -1;      /* EOF ??? kommt ueberraschend */
  ch =fgetc (fi);
  if (ch != 0x01A) return -1;   /* no Archive */
  ch =fgetc (fi);
  if (ch == 0x00) return 0;     /* EOF */
  fread ((char *) &pu, 27, 1, fi);
  strncpy (p->name, pu.name,13);
  p->time = pu.time;
  p->date = pu.date;
  p->size = pu.length;
  p->att  = (char) ch;                 /* Compressing Mode */
  fseek (fi, pu.size, 1);
  return 1;
}
