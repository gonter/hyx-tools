/*
 *  FILE ~/usr/nl_kr/lib/nl_00600.c
 *
 *  written:       1995-03-08: extracted from lutmake.c
 *  latest update: 1995-03-08
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>

#ifdef JUNK
/* ------------------------------------------------------------------------ */
/* Dictonary File einlesen */
read_dic (char *fn)
{
  FILE *fi;
  int  add, ok;

  if ((fi= fopen (fn, "rt")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -1;
  }

  for (;;)
  {
    ok = dic_get_entry (fi, line, &add, klasse, ispell_info);
    if (ok == -1) break;
printf ("wort=%s fcy=%d kl=%s ii=%s\n", line, add, klasse, ispell_info);
    SWT (line, add);
    word_cnt += (long) add;
  }
  fclose (fi);
}

/* ------------------------------------------------------------------------ */
read_thesaurus (char *fn)
{
  FILE *fi;

  if ((fi= fopen (fn, READ_MODE)) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -1;
  }

  for (;;)
  {
    xx_get_str (fi, line);
    if (feof (fi)) break;
    SW (line);
    word_cnt++;
  }
  fclose (fi);
}

/* ------------------------------------------------------------------------ */
xx_get_str (FILE *fi, char *s)   /* Thesaurus Daten File: 54 Byte fixed */
{
  int ch;
  int i;

  for (i=0;i<54;i++)
  {
    ch=fgetc (fi) & 0x00FF;
    if (feof(fi)) { s [0] = 0; return; }
    s[i]=ch;
  }

  for (i= 0; i < 53; i++)
  {
    ch= s[i];
    if (ch == ' '  ||  ch == '\t'  ||
        ch == 0x0A ||  ch == 0x0D)
      break;
  }
  s[i]=0;
}
#endif
