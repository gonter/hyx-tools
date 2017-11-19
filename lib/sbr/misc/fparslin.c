/*
 *  FILE c:/usr/sbr/fparslin.c
 *
 *  Parsen von Zeilen
 *
 *  written:       1989 03 18: extrahiert aus fscanlin.c
 *  latest update: 1994-12-13
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int fpars_line (
char *line,             /* Pufferbereich fuer Zeile                         */
int comment,            /* Kommentarzeichen (z.b. '#')                      */
int in_flags,           /* Input Flags: siehe FCLI_xxxxx                    */
char *parse_line [],    /* Zeiger auf geparste Zeilenelemente               */
int parse_pos [],       /* Position der geparsten Zeilenelemente            */
int *parse_cnt,         /* tatsaechlich gelesene Zeilenelemente             */
int *out_flags)         /* Output Flags: siehe FCLO_xxxx                    */
/* RETURN: EOF wenn fgetc EOF liefert                                       */
/*         EOF wenn keine Zeile mehr geparst werden kann                    */
/*         0   alles ok                                                     */
{
  int i, ch, st, ls;
  register char *cp;

#ifdef MSDOS
  in_flags;
#endif

  *parse_cnt= *out_flags = 0;

  if ((ls = strlen (line)) == 0) return 0;

      /* Zeile Parsen */
      cp = line; st = 0;
      for (i = 0; i < ls; i++)
        { if ((ch = *cp) == comment) break;
          switch (ch)
          { case 0x20: case 0x09: /* Blanks und Tabs */
                       if (st == 1)
                          { *cp = 0; st = 0;
                          }
                       break;
            default  : /* irgendein Zeichen */
                       if (st == 0)
                          { parse_line [*parse_cnt] = cp;
                            parse_pos  [*parse_cnt] =  i;
                            (*parse_cnt)++;
                            st = 1;
                          }
                       break;
          }
          cp++;
        }
  return 0;
}
