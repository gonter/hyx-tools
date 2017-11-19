/*
 *  FILE %ned/04/ned0432.c
 *
 *  *** DEAD CODE ***
 *
 *  IOA: indirect object access
 *    find method to access an object for reading or writing it.
 *
 *  written:       1993 01 31
 *  latest update: 1998-08-16 12:51:23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/sbr.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
static char search [128];
static char prompt [80];
static int do_search= 0;

/* ------------------------------------------------------------------------ */
struct ACCESS_METHOD
{
  struct ACCESS_METHOD *acm_next;
  char *acm_selector;
  char *acm_command;
} ;

/* ------------------------------------------------------------------------ */
static char *default_acm = "ned.acm";
static char *PAR_FILE= "@@loc.par";
static char *par_file= (char *) 0;
static char *acm_file= (char *) 0;
static int initialized= 0;
static char cmd_line [150];

static struct ACCESS_METHOD *acm= (struct ACCESS_METHOD *) 0;
static struct ACCESS_METHOD **acm_app= &acm;

/* ------------------------------------------------------------------------ */
int read_access_methods (char *fn)
{
  char sel [24];
  FILE *fi;
  struct ACCESS_METHOD *nacm;

  if ((fi= fopen (fn, "r")) == (FILE *) 0) return -1;
  ned_message_2 ("reading IOA methods: ", fn);

  for (;;)
  {
    sel[0]= (char) fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    if (sel [0] == '#')
    {
      trash_until_eol (fi);
      continue;
    }
    fscanf (fi, "%s%*[ \t]%[^\n]", &sel[1], cmd_line);
    if (feof (fi)) break;
    fgetc (fi);
    if ((nacm= calloc (sizeof (struct ACCESS_METHOD), 1))
        == (struct ACCESS_METHOD *) 0)
      break;

    nacm->acm_selector= strdup (sel);
    nacm->acm_command= strdup (cmd_line);
    *acm_app= nacm;
     acm_app= &nacm->acm_next;
  }
  fclose (fi);

  initialized= 1;

  return 0;
}

/* ------------------------------------------------------------------------ */
int do_prompt (char *str)
{
  if ((do_search= (str != (char *) 0))) strcpy (prompt, str);
  return 0;
}

/* ------------------------------------------------------------------------ */
int indirect_object_access (
char *tmpfnm,
int read_or_write,      /* 0 .. read;  1 .. write       */
int file_or_cluster,    /* 0 .. file;  1 .. cluster     */
char *location,
char *cl_or_file,
char *fr)
{
  int rc;
  struct ACCESS_METHOD *xacm;
  FILE *par;
  int write_search_string= 0;

  if (cl_or_file == (char *) 0) return -1;
  if (fr == (char *) 0) fr= "";

  if (!initialized)
  {
    acm_file= set_etc_filename ((char *) 0, default_acm);
    read_access_methods (acm_file);
  }

  for (xacm= acm; xacm != (struct ACCESS_METHOD *) 0; xacm= xacm->acm_next)
    if (strncmp (xacm->acm_selector, location,
                 strlen (xacm->acm_selector)) == 0) break;

  if (xacm == (struct ACCESS_METHOD *) 0)
  {
    ned_error_message ("couldn't find an appropriate IOA handler!");
    return -1;
  }

  if (do_search)
  {
    search[0]= 0;
    if (rd_str (prompt, search, 80) == -1) return 0;
    write_search_string= 1;
    do_search= 0;
  }

  if (par_file == (char *) 0)
    par_file= set_tmp_filename ((char *) 0, PAR_FILE);

  if ((par= fopen (par_file, "wb")) == (FILE *) 0) return -1;
  fprintf (par, "<hyx.ioa\n");
  if (file_or_cluster)
       fprintf (par, "cl=\"%s\"\nfr=%s\n", cl_or_file, fr);
  else
  {
    fprintf (par, "file=\"%s\"\n", cl_or_file);
    if (*fr != 0) fprintf (par, "ftr=\"%s\"\n", fr);
  }

  if (write_search_string) fprintf (par, "search=\"%s\"\n", search);
  fprintf (par, "loc=\"%s\"\n>", location);
  fclose (par);

  ned_message_3 (cl_or_file, " on ", location);

  sprintf (cmd_line,
           "%s %s %s %d",
            xacm->acm_command,
               tmpfnm,
                  par_file,
                     read_or_write);

  rc= system (cmd_line);

#ifdef __UNUSED__
{
  char rc_str [60];
  sprintf (rc_str, "*KEY* %d: ", rc),
  ned_message_2 (rc_str, cmd_line);
  kbin();
}
#endif

  return rc;
}
