/*
 *  FILE %sgml/hyxd03.c
 *
 *  Hypertext engine
 *
 *  commands:
 *    cluster <name>            ... OK
 *    fetch <frame>             ... DATA size + data
 *    store <frame>             ... OK
 *    delete <frame>            ... OK
 *    exists <frame>            ... OK size
 *    translate <frame>         ... OK real name
 *    last                      ... OK last index
 *    frames                    ... DATA + list of frames
 *    translate <frame>         ... OK real frame name
 *    check
 *    diag
 *    reindex
 *    fullindex
 *    purge
 *    quit                      ... no reply
 *
 *  see also:
 *    hyx.pm                    ... perl 5 module implementing a hash tie
 *    hyxtest.pl                ... perl 5 test program for hyx.pm
 *
 *  written:       1992 12 08
 *  latest update: 1999-04-24 12:01:58
 *  $Id: hyxd03.c,v 1.3 2002/01/27 23:01:34 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/hytxt.h>
#include <gg/hyxd.h>

/* ------------------------------------------------------------------------ */
#define N_COMMANDS 16
static char *commands [N_COMMANDS+1] =
{
           "quit",
#define CMD_quit        0
           "cluster",
#define CMD_cluster     1
           "fetch",
#define CMD_fetch       2
           "store",
#define CMD_store       3
           "delete",
#define CMD_delete      4
           "exists",
#define CMD_exists      5
           "last",
#define CMD_last_index  6
           "check",
#define CMD_check       7
           "diag",
#define CMD_diag        8
           "reindex",
#define CMD_reindex     9
           "fullindex",
#define CMD_fullindex   10
           "md5table",
#define CMD_md5table    11
           "purge",
#define CMD_purge       12
           "frames",
#define CMD_frames      13
           "translate",
#define CMD_translate   14
           "parse",
#define CMD_parse       15
  (char *) 0
} ;

/* ------------------------------------------------------------------------ */
int hyx_d_command (
struct HYXD_THREAD *thr,
char *line)
{
  int cmd;
  char *wp= (char *) 0;
  char *afn;
  char *line2;
  char *tfn;                    /* translated frame name                    */
  long size;
  int rc;
  struct HYX_CLUSTER_CONTROL *hcc;
  struct FILE_SEGMENT *fseg, *fseg_new;

  /*** fprintf (stderr, ">> hyx_d_command: line=%s\n", line); ***/
  if (line [0] == '#' || line [0] == 0) return 0;

  if (thr == (struct HYXD_THREAD *) 0
      || (hcc= thr->hcc) == (struct HYX_CLUSTER_CONTROL *) 0
     )
    return -1;

  line2= thr->line2;

  cmd= find_command (line, commands, 0, N_COMMANDS-1);
  wp= locate_word (line, 1);

  switch (cmd)
  {
    case CMD_cluster:
      if (thr->hcc_defined)
      {
        fprintf (thr->fo, "ERROR cluster already set!\n");
        break;      /* set cluster only once! */
      }

      if ((afn= translate_logic_filename (wp)) == (char *) 0) break;
      hcc_set_cluster_name (hcc, afn);
      free_or_what (afn);
      thr->hcc_defined= 1;

      fprintf (thr->fo, "OK cluster set\n");
      break;

    case CMD_quit:
      return 1;

    case CMD_fetch:
      if (hcc_open (hcc, HCC_om_read) != 0
          || hyx_extract (thr->fo, hcc->HCC_f_hyx, hcc->HCC_f_idx,
                          hcc->HCC_f_lut, hcc->HCC_f_xfn,
                          wp, 0, HYXEF_add_dot) != 0
         )
        fprintf (thr->fo, "ERROR frame not found\n");
      break;

    case CMD_parse:
      if (hcc_open (hcc, HCC_om_read) != 0
          || hyx_extract (thr->fo, hcc->HCC_f_hyx, hcc->HCC_f_idx,
                          hcc->HCC_f_lut, hcc->HCC_f_xfn,
                          wp, 0, HYXEF_add_dot) != 0
         )
        fprintf (thr->fo, "ERROR frame not found\n");
      break;

    case CMD_store:
    case CMD_delete:
      hcc_close (hcc);
      fseg= (struct FILE_SEGMENT *) 0;
      size= 0L;

      if (cmd == CMD_delete)
        rc= hyx_setup_delete_segment (&fseg, &fseg_new, wp, &size);
      else
        rc= hyx_setup_stdin_segment (&fseg, &fseg_new, wp, &size);

      if (rc == 0)
        fprintf (thr->fo, "OK %ld\n", size);
      else
        fprintf (thr->fo, "ERROR frame not found\n");

      fflush (thr->fo); /* flush now, if client waits for OK */

      if (!rc)
      {
        hyx_update (hcc->HCC_fnm_hyx, hcc->HCC_fnm_idx, hcc->HCC_fnm_lut,
                    hcc->HCC_fnm_xfn, fseg, 0);
        hyx_destroy_segments (fseg);
      }
      break;

    case CMD_translate:
      if ((tfn= hyx_translate_special_frame (wp)) != (char *) 0)
      {
        fprintf (thr->fo, "OK %s\n", tfn);
        free_or_what (tfn);
      }
      else
        fprintf (thr->fo, "ERROR\n");
      break;

    case CMD_exists:
      if (hcc_open (hcc, HCC_om_read) != 0
          || (size= hyx_seek_by_name (hcc->HCC_f_hyx, hcc->HCC_f_idx,
                              hcc->HCC_f_lut, hcc->HCC_f_xfn, wp)) < 0L
         )
        fprintf (thr->fo, "ERROR frame not found\n");
      else
        fprintf (thr->fo, "OK %ld\n", size);
      break;

    case CMD_last_index:
      if ((size= hyx_get_last_index (hcc->HCC_fnm_idx)) <= 0L)
        fprintf (thr->fo, "OK 0\n");
      else
        fprintf (thr->fo, "OK %ld\n", size);
      break;

    case CMD_frames:
      if (hcc_open (hcc, HCC_om_read) != 0)
      {
        fprintf (thr->fo, "ERROR\n");
        return -1;
      }
      fprintf (thr->fo, "DATA\n");
      hyx_dump_frame_list (hcc->HCC_f_lut, hcc->HCC_f_xfn);
      fputs (".\n", thr->fo);
      break;

    case CMD_check:
    case CMD_diag:
    case CMD_reindex:
    case CMD_fullindex:
    case CMD_md5table:
    case CMD_purge:
      hcc_close (hcc);
      switch (cmd)
      {
        case CMD_check:
          sprintf (line2, "chksgml %s", hcc->HCC_fnm_hyx);
          break;
        case CMD_diag:
          sprintf (line2, "chksgml -v %s", hcc->HCC_fnm_hyx);
          break;
        case CMD_reindex:
          sprintf (line2, "hyxidx %s", hcc->HCC_fnm_hyx);
          break;
        case CMD_fullindex:
          sprintf (line2, "hyxidx -i %s", hcc->HCC_fnm_hyx);
          break;
        case CMD_md5table:
          sprintf (line2, "hyxidx -m %s", hcc->HCC_fnm_hyx);
          break;
        case CMD_purge:
          sprintf (line2, "hyxpurge %s", hcc->HCC_fnm_hyx);
          break;
      }

      fprintf (thr->fo, "DATA\n%s\n", line2);
      fflush (thr->fo);

      system (line2);
      fputs ("\n.\n", thr->fo);
      break;

    default:
      fprintf (thr->fo, "ERROR unknown command\n");
      break;
  }
  fflush (thr->fo);

  return 0;
}
