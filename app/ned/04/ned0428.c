/*
 *  FILE %ned/04/ned0428.c
 *
 *  fetch an item from a GOPHER server
 *
 *  written:       1992 02 24
 *  latest update: 1998-08-16 12:52:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/filename.h>
#include <gg/hyx.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
#ifdef JUNK
struct GOPHER_item
{
  struct GOPHER_item *Gi_next;
  char *Gi_host;
  char *Gi_port;
  char *Gi_type;
  char *Gi_path;
  char *Gi_file;
} ;

static struct GOPHER_item *Gi= (struct GOPHER_item *) 0;
#endif

/* ------------------------------------------------------------------------ */
static char *SELFILE= "@5";

#define PATH_SIZE 2048
#define PORT_SIZE   18
#define LINE_SIZE  256

static char port [PORT_SIZE];
static char ty   [PORT_SIZE];

/* ------------------------------------------------------------------------ */
int access_gopher (char *hlink, char *fil)
{
  char *path;
  char *host;
  char *lin;
  char *search= (char *) 0;
  FILE *fsearch;
  int rc= -1;
  char *selfile;

  if ((path= malloc (PATH_SIZE)) == (char *) 0) goto E1;
  if ((host= malloc (LINE_SIZE)) == (char *) 0) goto E2;
  if ((lin=  malloc (LINE_SIZE)) == (char *) 0) goto E3;
  if ((selfile= set_tmp_filename ((char *) 0, SELFILE)) == (char *) 0)
    goto E4;

  if (find_attr_value (hlink, host, LINE_SIZE, "gh")==-1) goto ERROR;
  if (find_attr_value (hlink, port, PORT_SIZE, "gp")==-1) strcpy (port,"70");
  if (find_attr_value (hlink,   ty,        16, "gt")==-1) goto ERROR;
  if (find_attr_value (hlink, path, PATH_SIZE, "gs")==-1) path [0]= 0;

#ifdef DEB1
{
FILE *fx;
fx=fopen("@@@","at");
hyx_write_stamp (fx, (char *) 0);
fprintf (fx, "\nHost=%s\n", host);
fprintf (fx, "Port=%s\n", port);
fprintf (fx, "Type=%s\n", ty);
fprintf (fx, "Path=%s\n\n", path);
fclose (fx);
}
#endif

  /* future: check out if item is already present */

  /* search request? */
  if (strcmp (ty, "7") == 0 || strcmp (ty, "w") == 0)
  {
    if ((search= malloc (128)) == (char *) 0) goto ERROR;
    search [0]= 0;
    if (rd_str ("search: ", search, 80) == -1) goto ERROR;
  }

  if (set_tmp_filename (fil, (char *) 0) == (char *) 0)
    goto ERROR;

  if ((fsearch= fopen (selfile, "wt")) == (FILE *) 0) goto ERROR;
  if (path != (char *) 0) fputs (path, fsearch);
  if (search != (char *) 0)
  {
    if (path != (char *) 0 && path [0] != 0) fputc (0x09, fsearch);
    fputs (search, fsearch);
    free (search);
  }
  fputc ('\n', fsearch);
  fclose (fsearch);

  sprintf (lin, "gophftch %s %s %s %s %s", fil, ty, host, port, selfile);
  ned_message_3 ("accessing gopher ", host, "); hold on...");

  rc= system (lin);
/* unlink (selfile); */

ERROR:
  free (lin);
E4:
  free (selfile);
E3:
  free (host);
E2:
  free (path);
E1:
  return rc;
}
