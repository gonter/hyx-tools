/*
 *  FILE %ds/hyxta/hyxta005.c
 *
 *  written:       1994-11-12
 *  latest update: 1996-12-22 18:49:34
 *
 */

#include <stdio.h>
#include <gg/parse.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
long hyx_ta_parse_file (
struct HYX_PARSER_STATUS *hps,
char *fn,
long pos_offset,
long max_to_read)
{
  FILE *fi;
  long rc;
  struct TEXT_ELEMENT *ta_text_element= (struct TEXT_ELEMENT *) 0;

  if ((fi= fopen (fn, "r")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not found!\n", fn);
    return -2L;
  }

fprintf (stderr, ">>> ta_parse_file %s\n", fn);
  fseek (fi, pos_offset, 0);

  rc= hyx_ta_parse_stream (hps->HPS_hpc, hps, fi, max_to_read);

  fclose (fi);

  return rc;
}
