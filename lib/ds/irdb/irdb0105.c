/*
 *  FILE %ds/irdb/irdb0105.c
 *
 *  irrelational database
 *
 *  written:       1996-04-14
 *  latest update: 1996-04-14 13:59:41
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_diag_struct (
struct YTREE *yt,
char *str,
void *cd)
{
  int rc= 0;
  struct IRDB_DUMP *dmp;
  long pos;
  FILE *fo;
  int indent;

  if (yt == (struct YTREE *) 0
      || (dmp= (struct IRDB_DUMP *) cd) == (struct IRDB_DUMP *) 0
      || (fo= dmp->fo) == (FILE *) 0
     )
    return -1;

  if (!(yt->YT_flags & YTflag_EOW)) return 0;

  indent= dmp->indent;
  blanks (fo, indent);
  fprintf (fo, "[105] str='%s' := (%s) ", str, irdb_type (dmp->type));

  switch ((int) dmp->type)
  {
    case IRDBty_int:
      fprintf (fo, "%ld\n", yt->YT_info);
      /***** fputs ("this case should't show up here anyway\n", fo); ??? ***/
      break;

    case IRDBty_string:
      irdb_diag_string (fo, (char *) yt->YT_info);
      fputc ('\n', fo);
      break;

    case IRDBty_float:
    case IRDBty_block:
    case IRDBty_array:
      fputs (">>> irdb0105: T2D! <<<\n", fo);
      break;

    case IRDBty_struct:
      fputc ('\n', fo);
      blanks (fo, indent);
      fputs ("{\n", fo);
      pos= irdb_diag_to_stream (fo, (struct IRDB_HANDLE *) yt->YT_info,
                                indent+2);
      blanks (fo, indent);
      fputs ("};\n", fo);
      break;
  }

  return rc;
}
