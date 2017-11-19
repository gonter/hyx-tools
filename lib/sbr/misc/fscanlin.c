/*
 *  FILE ~/usr/sbr/fscanlin.c
 *
 *  Lesen und Parsen von Zeilen aus einem File
 *
 *  written:       1988 09 03
 *  latest update: 1994-12-13
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int fscan_line (
FILE *fi,               /* gelesenes File                                   */
char *line,             /* Pufferbereich fuer Zeile                         */
int max_line,           /* Groesse von line                                 */
int max_par,            /* maximale Zahl der geparsten Zeichen              */
                        /* <<<< nicht verwendet !!!                         */
int comment,            /* Kommentarzeichen (z.b. '#')                      */
int in_flags,           /* Input Flags: siehe FCLI_xxxxx                    */
                        /* <<<< nicht verwendet !!!                         */
char *parse_line [],    /* Zeiger auf geparste Zeilenelemente               */
int parse_pos [],       /* Position der geparsten Zeilenelemente            */
int *parse_cnt,         /* tatsaechlich gelesene Zeilenelemente             */
int *out_flags)         /* Output Flags: siehe FCLO_xxxx                    */
/* RETURN: EOF wenn fgetc EOF liefert                                       */
/*         EOF wenn keine Zeile mehr geparst werden kann                    */
/*         0   alles ok                                                     */
{
  int i, ch, st;
  int ls;               /* Line Size    */
  register char *cp;

#ifdef MSDOS
  max_par;
  in_flags;
#endif

  max_line--;
  cp= line;
  *parse_cnt= *out_flags = 0;

  for (;;)
  { /* Zeile einlesen */
    for (ls= 0; ls < max_line; ls++)
    {
      ch= fgetc (fi) & 0x00FF;
      if (ch == -1 || ch == 0x0D || ch == 0x0A) break;
      *cp++= (char) ch;
    }

    *cp = 0;
    if (ch == -1 && ls == 0) return -1; /* nothing else could be read       */
    if (ls == 0) continue;    /* bei Leerzeile weiterlesen */

    /* Zeile Parsen */
    cp= line;
    st= 0;
    for (i= 0; i < ls; i++)
    {
      if ((ch= *cp) == comment) break;
      switch (ch)
      {
        case 0x20: case 0x09: /* Blanks und Tabs */
          if (st == 1)
          {
            *cp = 0; st = 0;
          }
          break;
        default: /* irgendein Zeichen */
          if (st == 0)
          {
            parse_line [*parse_cnt] = cp;
            parse_pos  [*parse_cnt] =  i;
            (*parse_cnt)++;
            st= 1;
          }
          break;
      }
          cp++;
    }

    if (*parse_cnt)
    { /* es wurde etwas ge'parse't */
      return 0;
    }
  }
}
