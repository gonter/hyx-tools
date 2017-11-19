/*
 *  FILE ~/usr/sgml/httpsf.c
 *
 *  HTTP SGML filter stage
 *
 *  written:       1994-04-12
 *  latest update: 1995-03-25
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <gg/hytxt.h>
#ifdef MSDOS
#include <conio.h>
#endif

/* ------------------------------------------------------------------------ */
static int verbose_mode= 0;
static int translit_entities= 1;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: httpsf [options] {file name}\n",
  "OPTIONS:\n",
  "  -v ... verbose mode\n",
  "  -p ... insert <PRE> and </PRE> tags\n",
  "  -r ... raw; don't insert entities for chars over 0x80\n",
  "\n",
  "(@)Ahttpsf.c 0.03 #D$1995-03-25 18:00:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[]);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  FILE *fi;
  FILE *fo;
  int infile= 0;
  int i, j;
  int preformatted= 0;

  fo= stdout;

  for (i= 1; i < argc; i++)
    if (argv [i][0] == '-')
      switch (argv [i][1])
      {
        case 'v': case 'V':
        case 'p': case 'P':
        case 'r': case 'R':
          for (j= 1; argv [i][j]; j++)
            switch (argv [i][j])
            {
              case 'v': case 'V':
                verbose_mode++;
                break;
              case 'p': case 'P':
                preformatted= 1;
                break;
              case 'r': case 'R':
                translit_entities= 0;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", argv[i][j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    else
    {
      if ((fi= fopen (argv[i], "r")) != (FILE *) 0)
      {
        if (preformatted) fprintf (fo, "<PRE>\n");
        hytxt_filter (fi, fo, 0x7FFFFFFFL, translit_entities);
        if (preformatted) fprintf (fo, "</PRE>\n");
        fclose (fi);
      }
    }

  if (infile == 0)
  {
    if (preformatted) fprintf (fo, "<PRE>\n");
    hytxt_filter (stdin, fo, 0x7FFFFFFFL, translit_entities);
    if (preformatted) fprintf (fo, "</PRE>\n");
  }

  return 0;
}
