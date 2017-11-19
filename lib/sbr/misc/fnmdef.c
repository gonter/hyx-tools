/*
 *  FILE %sbr/fnmdef.c
 *
 *  written:       1994-08-12
 *  latest update: 1996-03-17 21:07:52
 *  $Id: fnmdef.c,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef DEBUG
#define DFILE stdout
#include <stdio.h>
int main (int argc, char *argv []);
int print_fnmdef (FILE *fo, char *str);
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/filename.h>

#define MAX_RECURSION 25        /* that should be enough, I guess           */
#define VP_BUFFER_SIZE 1024
static char vp_buffer [VP_BUFFER_SIZE];

/* ------------------------------------------------------------------------ */
int filename_definition (
const char *spec,               /* given filename                           */
char **real_fnm,                /* real absolute filename                   */
char **virtual_fnm,             /* translation for a logic path, or NULL    */
char *assumed_path)             /* assumed working directory or NULL        */
{
  int ch;
  char *tfn;
  char *cpath;
  int recursion;                /* recursively resolve virtual paths        */
  char *searched;

  if (spec == (char *) 0
      || real_fnm == (char **) 0
      || virtual_fnm == (char **) 0
      /**** || (ch= *spec) == 0 *****/
     ) return -1;

  read_logic_filename_table ((char *) 0, 1);

  *real_fnm= *virtual_fnm= (char *) 0;

  switch (ch)
  {
    case '%':
    case '~':
    case '$':
    default:    /* TEST1: it needs to be decided if this wide   */
                /* translation mechanism is really wanted...    */

      searched= (char *) spec; /* not a (const char *) anymore ... */
      for (recursion= 0;; recursion++)
      {
        if (recursion >= MAX_RECURSION) return -1;
#ifdef MSDOS
        to_lower (spec);
        xchange (spec, '\\', '/');
#endif /* MSDOS */

        if ((tfn= translate_logic_filename (searched)) == (char *) 0)
          return -1;

        if (tfn == (char *) 0
            || (ch= *tfn) == 0
            || strcmp (searched, tfn) == 0
           )
        {
#ifdef DEBUG
          fprintf (DFILE, 
           ">> fnmdef: spec and tfn are identical, discard and getpath\n");
#endif /* DEBUG */
          free (tfn);
          goto RELATIVE;
        }

        *real_fnm= tfn;
        if (*virtual_fnm == (char *) 0)
          *virtual_fnm= strdup_extra (searched, DEF_FNM_EXTRA);
        if (recursion > 0) free (searched); /* malloc'ed in previous round */
        if (ch != '%' && ch != '~' && ch != '$') return 0;
        searched= tfn; /* start another round of translations */
      }
  }

RELATIVE:
  /* no virtual path found, try to resolve filename relativeley */

  if ((cpath= real_filename (spec, assumed_path)) == (char *) 0) return -1;
#ifdef MSDOS
  to_lower (cpath);
  xchange (cpath, '\\', '/');
#endif /* MSDOS */

  ch= find_logic_filename (*real_fnm= cpath, vp_buffer, VP_BUFFER_SIZE);

#ifdef DEBUG
  fprintf (DFILE, "find_logic_filename (%s)\n", XSTR (*real_fnm));
  fprintf (DFILE, "rv=%d\n", ch);
#endif /* DEBUG */

  if (ch == 1 /* a translation for a logic path exists */
      && (cpath= strdup_extra (vp_buffer, DEF_FNM_EXTRA)) != (char *) 0
     )
  {
#ifdef MSDOS
    to_lower (cpath);
    xchange (cpath, '\\', '/');
#endif /* MSDOS */
    *virtual_fnm= cpath;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef DEBUG_main
static char line [256];
static char *assumed_path= (char *) 0;

int main (int argc, char *argv [])
{
  int i;
  int done= 0;

  for (i= 1; i < argc; i++)
  {
    /* assumed_path= argv [i]; *****/
    print_fnmdef (DFILE, argv [i]);
    done++;
  }

  while (done == 0)
  {
    fprintf (DFILE, "filename: ");
    scanf ("%s", line);
    if (line [0] == '#') line [0]= 0;

    print_fnmdef (DFILE, line);
  }

  return 0;
}

int print_fnmdef (FILE *fo, char *str)
{
  char *vir, *rea;
  char *reverse_lookup;
  int rc;

  rea= vir= reverse_lookup= (char *) 0;
  vp_buffer [0]= 0;
  rc= filename_definition (str, &rea, &vir, assumed_path);

  if (rea != (char *) 0)
    find_logic_filename (rea, vp_buffer, VP_BUFFER_SIZE);

  fprintf (fo, "filename= '%s'\n", XSTR (str));
  fprintf (fo, "real    = '%s'\n", XSTR (rea));
  fprintf (fo, "virtual = '%s'\n", XSTR (vir));
  fprintf (fo, "reverse = '%s'\n", XSTR (vp_buffer));
  fprintf (fo, "--------------\n");

  return 0;
}

#endif /* DEBUG_main */
