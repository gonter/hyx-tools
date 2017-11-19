/*
 *  FILE %ned/04/ned0433.c
 *
 *  history interface
 *
 *  written:       1993-02-20
 *                 1993-02-21: latest update
 *  latest update: 1995-11-26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/filename.h>
#include <gg/dates.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
static int history_initiated= 0;
static int history_enabled= 1;
static char *history_file= (char *) 0;
static char *HISTORY_FILE= "%history";
static char *FMT []= { "binary", "ascii", "sgml" };

/* ------------------------------------------------------------------------ */
void enable_ned_history ()  { history_enabled= 1; }
void disable_ned_history () { history_enabled= 0; }

/* ------------------------------------------------------------------------ */
int setup_ned_history ()
{
  history_file= translate_logic_filename (HISTORY_FILE);
  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_history (
char *file_or_cluster,
char *frame,
char *comment,
int f_type,
int f_format)
{
  FILE *fo;

  if (!history_enabled) return 0;
  if (f_format < 0 || f_format > FMT_SGML) return -1;
  if (!history_initiated) setup_ned_history ();
  if (history_file == (char *) 0) goto NO_HISTORY;

  if ((fo= fopen (history_file, "a")) == (FILE *) 0)
  {
NO_HISTORY:
    history_enabled= 0;
    return -1;
  }

  fprintf (fo, "<hyx.l");
  switch (f_type)
  {
    default:
    case FTY_PLAIN:
      fprintf (fo, " file=\"%s\"", file_or_cluster);
      break;
    case FTY_HYPER:
      fprintf (fo, " cl=\"%s\" fr=\"%s\"", file_or_cluster, frame);
      break;
  }

  if ((f_type == FTY_HYPER && f_format != FMT_SGML)
      ||(f_type == FTY_PLAIN && f_format == FMT_SGML)
      ||f_format == FMT_BINARY
     )
  {
    fprintf (fo, " fmt=%s", FMT [f_format]);
  }

  fprintf (fo, ">* ");
  print_date_time (fo);
  fputc ('\n', fo);
  if (comment != (char *) 0) fprintf (fo, "  %s\n", comment);
  if (f_type == FTY_HYPER)   fprintf (fo, "  %s\n", frame);
  fprintf (fo, "  %s\n", file_or_cluster);

  fclose (fo);

  return 0;
}
