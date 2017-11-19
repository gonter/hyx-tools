/*
 *  FILE /usr/lex/lexm.c
 *
 *
 *  1992 02 19
 *
 */

#include <stdio.h>
#include <io.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>

#ifndef NIL
#define NIL (void *) 0
#endif

extern FILE *logfile;

/* ------------------------------------------------------------------------ */
int cdecl main_fnc (char *fn);
long cdecl lexm_dump (char *fno);

/* ------------------------------------------------------------------------ */
static int file_count=0;
static long file_flag [] =
{
  0x00000000L, 0x00000001L, 0x00000002L, 0x00000004L, 0x00000008L
} ;

static struct YTREE *ytree=NIL;

#define LB_SIZE 1024
static char line_buffer[LB_SIZE];
static char line_buffer2[LB_SIZE];

/* ------------------------------------------------------------------------ */
int main_fnc (char *fn)
{
  FILE *fi;
  int bs;
  struct YTREE *yt;
  int fl;
  int xfl;

  fprintf (logfile, "lexm: %s\n", fn);
  if (access (fn, 0) != 0)
  {
    fprintf (logfile, "** File %s not found!\n", fn);
    return -2;
  }

  file_count++;
  if (file_count > 3)
  {
    fprintf (logfile, "** can't process more that 3 files!\n");
    return -2;
  }

  fi = fopen (fn, "rb");
  if (fi == (FILE *) 0)
  {
    fprintf (logfile, "** can't open file %s for reading!\n", fn);
    return -2;
  }
  for (;;)
  {
    if (fgets (line_buffer, LB_SIZE, fi) == (char *) 0) break;
    if (feof (fi)) break;
    for (bs= strlen (line_buffer)-1; bs >= 0; bs--)
    {
      switch (line_buffer [bs] & 0x00FF)
      {
        case 0x0D:
        case 0x0A:
        case 0x09:
        case 0x20:
          line_buffer[bs]= 0;
          break;
        default:
          bs=0;
          break;
      }
    }

    switch (file_count)
    {
      case 1:
      case 2:
        yt= ytree_insert_word (&ytree, line_buffer);
        if (yt == NIL)
        {
          fprintf (logfile, "*** creating ytree: can't insert %s\n", line_buffer);
          goto STOP;
        }
        yt->YT_info |= file_flag [file_count];
        yt->YT_flags |= YTflag_EOW;
        break;

      case 3:
        yyconvent (line_buffer, line_buffer2);
        xfl = (strcmp (line_buffer, line_buffer2)==0);
        yt= ytree_insert_word (&ytree, line_buffer2);
        if (yt == NIL)
        {
          fprintf (logfile, "*** creating ytree: can't insert %s\n", line_buffer2);
          goto STOP;
        }

        fl = (yt->YT_info != 0);
        yt->YT_flags |= YTflag_EOW;
        if (xfl)
        {
          yt->YT_info |= 0x00000004L;
          break;
        }
        yt->YT_info |= 0x00000008L;

        yt= ytree_insert_word (&ytree, line_buffer);
        if (yt == NIL)
        {
          fprintf (logfile, "*** creating ytree: can't insert %s\n", line_buffer);
          goto STOP;
        }
        yt->YT_info |= 0x00000010L;
        if (fl) yt->YT_info |= 0x00000020L;
        yt->YT_flags |= YTflag_EOW;
        break;
    }
  }

STOP:
  fclose (fi);

  return 0;
}

/* ------------------------------------------------------------------------ */
long lexm_dump (char *fno)
{
  FILE *fo;
  long unique;

  fo = fopen (fno, "wb");
  if (fo == (FILE *) 0) return -1L;

  ytree_size (ytree);
  unique = ytree_dump (fo, ytree);
  fclose (fo);

  return unique;
}
