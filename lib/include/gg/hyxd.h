/*
 *  include FILE <gg/hyxd.h>
 *
 *  Hypertext daemon
 *
 *  written:       1992 12 08
 *  latest update: 1997-09-14 19:13:49
 *
 */

#ifndef __GG_hyxd__
#define __GG_hyxd__

#include <gg/hytxt.h>
#include <gg/floskel.h>

#define HYXD_single_transaction 0x01
#define HYXD_md5_transformation 0x02
#define HYXD_ticket_required    0x04
#define HYXD_lexicon_server     0x08
#define HYXD_verbose            0x10
#define HYXD_preformatted       0x20

#define HYXD_LINE_SIZE 1024
/* structures: ------------------------------------------------------------ */
struct HYXD_THREAD
{
  FILE *fi;                     /* input file stream                        */
  FILE *fo;                     /* output file stream                       */
  char line [HYXD_LINE_SIZE];   /* line buffer                              */
  char line2 [HYXD_LINE_SIZE];  /* line buffer                              */
  struct HYX_CLUSTER_CONTROL *hcc;
  int hcc_defined;
} ;

/* macros: ---------------------------------------------------------------- */
#define hyx_d_new_thread() \
  ((struct HYXD_THREAD *) calloc (sizeof (struct HYXD_THREAD), 1))

/* prototypes: ------------------------------------------------------------ */
/* hyxd01.c */ int cdecl hyx_d_daemon (FILE *fi, FILE *fo,
                 char *cluster, char *credential_file);
/* hyxd02.c */ int cdecl hyx_d_extract (FILE *fo, char *cluster, char *frame,
                 char *default_path, int mode);
/* hyxd03.c */ int cdecl hyx_d_command (struct HYXD_THREAD *thr, char *line);
/* hyxd03.c */ int cdecl hyx_d_set_cluster (char *cl);
/* hyxd04.c */ int cdecl http4hyx_command (FILE *fo, char *line, int mode);
/* hyxd04.c */ int cdecl http4hyx_set_path (char *pfx);
/* hyxd05.c */ int cdecl http4hyx_daemon (FILE *fi, FILE *fo, int mode);

#endif /* __GG_hyxd__ */
