/*
 *  FILE %sgml/hyxd02.c
 *
 *  hypertext daemon
 *  +  extract a frame
 *
 *  written:       1992-12-08
 *  latest update: 1999-04-24 12:00:04
 *  $Id: hyxd02.c,v 1.3 2002/01/27 23:01:33 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/hytxt.h>
#include <gg/hyxd.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int hyx_d_extract (
FILE *fo,
char *cluster,
char *frame,
char *default_path,
int mode)
{
  struct FILE_SEGMENT *fs= (struct FILE_SEGMENT *) 0;
  char *afn_hyx;
  char *fnm_idx;
  char *fnm_lut;
  char *fnm_xfn;
  int rc= 0;
  long index_number= 0L;

  fprintf (stderr,
           "hyx_d_extract: cluster='%s' frame='%s'\n", cluster, frame);

  if (cluster == (char *) 0 || !*cluster
      || frame == (char *) 0 || !*frame) return -2;

  if (cluster [0] != '/'
     &&  default_path != (char *) 0
     && *default_path != 0)
  {
    afn_hyx= malloc (strlen (default_path) + strlen (cluster) + 2);
    sprintf (afn_hyx, "%s/%s", default_path, cluster);
  }
  else
  {
    if ((afn_hyx= translate_logic_filename (cluster)) == (char *) 0)
      afn_hyx= cluster;
  }

  fnm_idx= fnmcpy2 (afn_hyx, ".idx");
  fnm_lut= fnmcpy2 (afn_hyx, ".lut");
  fnm_xfn= fnmcpy2 (afn_hyx, ".xfn");

  fprintf (stderr, "hyx_d_extract: afn_hyx=%s\n", afn_hyx);
  fprintf (stderr, "hyx_d_extract: fnm_idx=%s\n", fnm_idx);
  fprintf (stderr, "hyx_d_extract: fnm_lut=%s\n", fnm_lut);
  fprintf (stderr, "hyx_d_extract: fnm_xfn=%s\n", fnm_xfn);

  if (mode & HYXD_lexicon_server)
  {
    /* BEGIN Lexicon Server: This section can be used for                   */
    /* lexicon specific code to hack the lexicon server.                    */
    /* see T2D for more details about this topic.                             */

    /* END Lexicon Server */
  }
  else
  {
    hyx_make_segment (&fs, (char *) 0, frame, &index_number, FSop_extract,
                      0L, 0L);

    rc= hyx_sequencer (
          (fo == (FILE *) 0) ? (FILE *) stdout : fo,
          afn_hyx, fnm_idx, fnm_lut, fnm_xfn, fs, 0, 0);
  }

  flclose_all ();

  free (fnm_idx);
  free (fnm_lut);
  free (fnm_xfn);

  return rc;
}
