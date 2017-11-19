/*
 *  FILE %sgml/hyxd04.c
 *
 *  Hypertext daemon
 *  - Ticket Operation
 *
 *  written:       1994-04-09
 *  latest update: 1997-09-14 18:34:16
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/hyxd.h>
#include <gg/hytxt.h>
#include <contrib/md5gg.h>

/* ------------------------------------------------------------------------ */
#define MAX_LINE 1024
static char cluster [MAX_LINE];
static char frame   [MAX_LINE];
static char ticket  [MAX_LINE];
static char *path_prefix= "";

/* ------------------------------------------------------------------------ */
int http4hyx_command (FILE *fo, char *line, int mode)
{
  char *used_frame_name;
#define N_FIELDS 24
  char *fields [N_FIELDS];
  char *path_fields [N_FIELDS];
  int n_fields;
  int n_path_fields;
  int i;
  int cluster_lng;

fprintf (stderr, "http4hyx: line=%s\n", line);

  n_fields= isolate_tokens (line, fields, N_FIELDS);
  if (n_fields < 1) return 0;

  for (i= 0; i<n_fields; i++)
    fprintf (stderr, "*** http4hyx (hyxd04): fields[%d]=%s\n", i, fields[i]);

  to_upper (fields [0]);
  if (abbrev ("QUIT", fields [0], 1)
      || abbrev ("EXIT", fields [0], 1)
     ) return 1;

  if (strcmp (fields [0], "GET") == 0)
  {
    if (strncmp (fields [2], "HTTP/", 5))
    {
      fprintf (fo, "HTTP/1.0 200 OK\r\n");
      fprintf (fo, "Content-Type: text/html\r\n\r\n");
    }

    n_path_fields= split_string (fields[1], '/', path_fields, N_FIELDS);
fprintf (stderr, "n_path_fields=%d\n", n_path_fields);
    if (n_path_fields < 1
       || ((mode & HYXD_ticket_required) && n_path_fields < 2) )
    {
      fprintf (stderr, "http4hyx (hyxd04): GET not enough fields!\n");
      return 1;
    }

    for (i= 0; i < n_path_fields; i++)
      fprintf (stderr,
               "*** http4hyx (hyxd04): path_fields[%d]=%s\n",
               i, path_fields[i]);

    if (n_path_fields < 2
        || ((mode & HYXD_ticket_required) && n_path_fields < 3)
       )
    {
      strcpy (frame, "$$root");
    }
    else
    {
      url2frame_name (path_fields [n_path_fields-1], frame, MAX_LINE);
      n_path_fields--;
    }

    if (mode & HYXD_ticket_required)
    {
      strncpy (ticket, path_fields [n_path_fields-1], MAX_LINE-2);
      /* #### TICKET CHECKING HERE #### */
      n_path_fields--;
    }

    sprintf (cluster, "%s", path_fields [1]);
    for (i= 2; i < n_path_fields; i++)
    {
      cluster_lng= strlen (cluster);
      if (strcmp (path_fields [i], ".") == 0
         || strcmp (path_fields [i], "..") == 0) continue;
      sprintf (cluster+cluster_lng, "/%s", path_fields [i]);
    }

    used_frame_name= (mode & HYXD_md5_transformation && *frame != '$')
                     ? MD5check_string ((unsigned char *) frame)
                     : frame;

    fprintf (stderr, "*** http4hyx (hyxd04): cluster=%s\n", cluster);
    fprintf (stderr, "*** http4hyx (hyxd04): frame=%s\n", used_frame_name);
    if (mode & HYXD_ticket_required)
      fprintf (stderr, "*** http4hyx (hyxd04): ticket=%s\n", ticket);

    if (mode & HYXD_preformatted) fprintf (fo, "<PRE>\r\n");
    hyx_d_extract (fo, cluster, used_frame_name, path_prefix, mode);
    if (mode & HYXD_preformatted) fprintf (fo, "</PRE>\r\n");

    fflush (fo);
    if (mode & HYXD_single_transaction) return 1;
  } /* end GET command */

  return 0;
}

/* ------------------------------------------------------------------------ */
int http4hyx_set_path (char *pfx)
{
  path_prefix= pfx;
  return 0;
}
