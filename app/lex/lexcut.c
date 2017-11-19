/*
 *  FILE ~/usr/lex/lexcut.c
 *
 *  cut up a lexicon file into seperate files where each entry
 *  shares the first N_PREFIX characters.
 *
 *  written:       1993-07-05
 *  latest update: 1994-07-17
 *
 */


#include <stdio.h>
#include <string.h>

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif
#endif

int cdecl main (int argc, char *argv[]);
int cdecl lexicon_cut (char *fnm);
char *cdecl get_extension (char *key);

#define DO_WRITE_DATA           /* really transfer data to the outfile      */

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  if (argc == 2)
    lexicon_cut (argv[1]);
  else
  {
    fprintf (stderr, "usage: %s lexicon file\n", argv[0]);
  }
  return 0;
}

/* ------------------------------------------------------------------------ */
#define MAX_BUFFER 2000
static char buffer [MAX_BUFFER+10];
static char le_buffer [MAX_BUFFER+10];
static char le_last [MAX_BUFFER]= "shurely not that";
static char outname [200];

/* ------------------------------------------------------------------------ */
int lexicon_cut (char *fnm)
{
  FILE *fi;
  FILE *fo= (FILE *) 0;
  int ch;
#define STAT_start      0
#define STAT_lt         1
#define STAT_colon      2
#define STAT_L          3
#define STAT_LX         4
#define STAT_fr         5
#define STAT_fr_lt      6
#define STAT_fr_l       7
#define STAT_fr_le      8
#define STAT_fr_LE      9
  int stat= STAT_start;
  int buffer_idx;
  int le_idx;
  char *cluster_ext;

  if ((fi= fopen (fnm, "r")) == (FILE *) 0) return -1;
  buffer_idx= 0;
  for (;;)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    switch (stat)
    {
      case STAT_start:
        if (ch == '<')
        {
          buffer [0]= '<';
          buffer [1]= 0;
          buffer_idx= 1;
          stat= STAT_lt;
        }
        else
        {
          if (fo != (FILE *) 0) fputc (ch, fo);
        }
        break;

      case STAT_lt:
        if (ch == ':')
        {
          stat= STAT_colon;
          buffer [buffer_idx++]= (char) ch;
          buffer [buffer_idx]= 0;
        }
        else
        {
FLUSH_BUFFER:
          if (fo != (FILE *) 0)
          {
            fprintf (fo, "%s%c", buffer, ch);
          }
          stat= STAT_start;
        }
        break;

      case STAT_colon:
        if (ch == 'L')
        {
          stat= STAT_L;
          buffer [buffer_idx++]= (char) ch;
          buffer [buffer_idx]= 0;
        }
        else goto FLUSH_BUFFER;
        break;

      case STAT_L:
        if (ch == 'X')
        {
          stat= STAT_LX;
          buffer [buffer_idx++]= (char) ch;
          buffer [buffer_idx]= 0;
        }
        else goto FLUSH_BUFFER;
        break;

      case STAT_LX:
        if (ch == '>')
        {
          stat= STAT_fr;
          buffer [buffer_idx++]= (char) ch;
          buffer [buffer_idx]= 0;
        }
        else
        {
          if (buffer_idx >= MAX_BUFFER)
          {
            fprintf (stderr, "error: frame start sequence too long!\n");
            goto FLUSH_BUFFER;
          }
          else
          {
            buffer [buffer_idx++]= (char) ch;
            buffer [buffer_idx]= 0;
          }
        }
        break;

      case STAT_fr:
        if (ch == '<')
        {
          stat= STAT_fr_lt;
          buffer [buffer_idx++]= (char) ch;
          buffer [buffer_idx]= 0;
        }
        else goto FLUSH_BUFFER;
        break;

      case STAT_fr_lt:
        if (ch == 'L' || ch == 'l')
        {
          stat= STAT_fr_l;
          buffer [buffer_idx++]= (char) ch;
          buffer [buffer_idx]= 0;
        }
        else goto FLUSH_BUFFER;
        break;

      case STAT_fr_l:
        if (ch == 'E' || ch == 'e')
        {
          stat= STAT_fr_le;
          buffer [buffer_idx++]= (char) ch;
          buffer [buffer_idx]= 0;
        }
        else goto FLUSH_BUFFER;
        break;

      case STAT_fr_le:
        if (ch == '>')
        {
          stat= STAT_fr_LE;
          le_idx= 0;
          buffer [buffer_idx++]= (char) ch;
          buffer [buffer_idx]= 0;
        }
        else goto FLUSH_BUFFER;
        break;

      case STAT_fr_LE: /* collect characters from the LE name */
        if (ch == '<')
        {
GOT_PREFIX:
          cluster_ext= get_extension (le_buffer);
          if (strcmp (cluster_ext, le_last) != 0)
          {
            if (fo != (FILE *) 0) fclose (fo);
            sprintf (outname, "lexcut.%s", cluster_ext);
            fo= fopen (outname, "a");
            printf ("appending to: %s\n", outname);
            strcpy (le_last, cluster_ext);
          }
          if (fo != (FILE *) 0)
          {
            fprintf (fo, "%s", buffer); /* <:LX12345678><LE> */
            fprintf (fo, "%s", le_buffer);
            if (ch == '<') fputc ('<', fo);
            stat= STAT_start;
          }
        }
        else
        {
          le_buffer [le_idx++]= (char) ch;
          le_buffer [le_idx]= 0;
          if (le_idx >= MAX_BUFFER) goto GOT_PREFIX;
          /* Note: we collect the complete lexicon entry, not   */
          /*       just the first <chars> characters.           */
          
        }
        break;

    }
  }
  fclose (fi);
  if (fo != (FILE *) 0) fclose (fo);

  return 0;
}
