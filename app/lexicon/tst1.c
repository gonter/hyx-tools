/*
 *  FILE ~/usr/lexicon/tst1.c
 *
 *  Test fuer Modul lexut001.c
 *
 *  written:       1991 04 28
 *  latest update: 1995-07-16
 *
 */


#include <stdio.h>
#include <gg/sbr.h>
#include <gg/lexutil.h>

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif
#endif

/* ------------------------------------------------------------------------ */
#define LINE_SIZE 256
static char line1   [LINE_SIZE];
static char line2   [LINE_SIZE];
static char word    [LINE_SIZE];
static char flags   [LINE_SIZE];
static char derived [LINE_SIZE];

static long records= 0L;
static long records_out= 0L;
static long flagged_records= 0L;

int cdecl main (int argc, char *argv[]);
int cdecl read_ispell (FILE *fo, char *fn);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  int i;
  FILE *fo;
  int fo_open= 0;

  for (i= 1; i<argc; i++)
  {
    if (argv [i][0] == '-')
       switch (argv [i][1])
       {
         case 'o': case 'O':
           if (fo_open) fclose (fo);
           fo_open= 0;
           if ((fo= fopen (&argv[i][2], "wb")) != (FILE *) 0) fo_open= 1;
           break;
       }
    else read_ispell ((fo_open) ? fo : (FILE *) stdout, argv[i]);
  }

  fprintf (stderr, "# flagged   records=%8ld\n", flagged_records);
  fprintf (stderr, "# unflagged records=%8ld\n", records-flagged_records);
  fprintf (stderr, "                    --------\n");
  fprintf (stderr, "# total     records=%8ld\n", records);
  fprintf (stderr, "# derivates        =%8ld\n", records_out);
  fprintf (stderr, "# output records   =%8ld\n", records_out+flagged_records);

  return 0;

}

/* ------------------------------------------------------------------------ */
int read_ispell (FILE *fo, char *fn)
{
  FILE *fi;
  char *cp;
  int i,rc;
  int inflags;

  if ((fi= fopen (fn, "rb")) == (FILE *) 0) return -1;

  for (;;)
  {
    rc= fread_line (fi, line1, LINE_SIZE);
    if (rc <= 0 && feof (fi)) break;

    cp= word;
    flags[0]= 0;
    inflags= 0;
    for (i= 0; line1 [i]; i++)
    {
      if (line1 [i] == '/')
      {
        if (!inflags)
        {
          *cp= 0;
          cp= flags;
          inflags= 1;
        }
      } else *cp++= line1[i];
    }

    *cp= 0;
    /* printf ("line1='%s'\n", line1); */
    /* printf ("word='%s'  flags='%s'\n", word, flags); */
    records++;
    if (flags[0])
    {
      flagged_records++;
      fprintf (fo, "<:><LE>%s</LE><F l=e wf=IS:O>", word);
    }

    for (i= 0; flags[i]; i++)
    {
      rc= ISPELL_derive (word, flags[i], derived);
      /*******************
      printf ("word='%s' flag='%c' derived='%s' (rc=%d)\n",
              word, flags[i], derived, rc);
      *******************/
      fprintf (fo, "<WF l=e wf=IS:%c>%s</WF>", flags[i], derived);
      records_out++;
    }
    if (flags[0]) fprintf (fo, "<;>\n");
    for (i=0; flags[i]; i++)
    {
      rc= ISPELL_derive (word, flags[i], derived);
      fprintf (fo, "<:><LE>%s</LE><F l=e wf=IS:%c>", derived, flags[i]);
      fprintf (fo, "<WF l=e wf=IS:O>%s</WF><;>\n", word);
    }
  }

  fclose (fi);
  return 0;
}
