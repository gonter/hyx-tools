/*
 *  FILE %sbr/fndvfile.c
 *
 *  written:       1996-03-17: extracted from %ned/04/ned0425.c
 *  latest update: 1997-06-11 14:40:56
 *
 */

#ifdef DEBUG
#define DFILE stdout
#include <stdio.h>
int main (int argc, char *argv []);
int print_virtual_file (FILE *fo, char *str);
#endif

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/url.h>
#include <gg/strings.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
static char *dirinf= "(dirinf).fm";
static int dirinf_allocated= 0;
static FVF_get_directory_listing *fvf_get_dirinf=
         (FVF_get_directory_listing *) 0;
static void *fvf_get_dirinf_cd= (void *) 0;

/* ------------------------------------------------------------------------ */
int find_virtual_file (
char *fnm,
char *current_path,
char **real_fnm,
char **virtual_fnm)
{
  char *r_fnm;
  char *v_fnm;
  int lrf;
  struct stat st;

  /* T2D: current_path could be an URL itself !!! */
  if (url_identify_type (fnm) >= URL_TYPE_file)
  {
    if ((r_fnm= url_fetch (fnm)) == (char *) 0) return -1;
      v_fnm= strdup (fnm);

    *virtual_fnm= v_fnm;
    *real_fnm= r_fnm;
  }
  else
  {
    if (filename_definition (fnm, real_fnm, virtual_fnm, current_path) != 0)
    {
      *real_fnm= strdup (fnm);
      *virtual_fnm= strdup (fnm);
    }

    /* NOTE: 1997-06-11 14:40:28 */
    /* optionally strdup (fnm) if real_fnm or virtual_fnm are NULL ! */

    r_fnm= *real_fnm;
    v_fnm= *virtual_fnm;
  }

  if ((lrf= strlen (r_fnm) - 1) <= 0) return -1;

  if (r_fnm [lrf] == '/'
#ifdef MSDOS
      || r_fnm [lrf] == '\\'
#endif /* MSDOS */
     ) r_fnm [lrf--]= 0; /* skip that / from dirinf */

  if (stat (r_fnm, &st) == 0 && (st.st_mode & S_IFDIR))
  {
    FVF_get_directory_listing *proc;
    char *res;

#ifdef DEBUG
    printf ("is_dir: '%s'\n", r_fnm);
#endif /* DEBUG */

    if ((proc= fvf_get_dirinf) != (FVF_get_directory_listing *) 0
#ifdef DEBUG
        && printf (" -> calling dirinf generator\n")
#endif /* DEBUG */
        && (res= (*fvf_get_dirinf) (r_fnm, fvf_get_dirinf_cd)) != (char *) 0
       )
    {
      free (r_fnm); /* not used anymore */
      *real_fnm= res;
      return 0;
    }

    if (dirinf == (char *) 0
        || lrf <= 0
        || lrf + 14 >= MAX_FNM_LENGTH
       ) return -1;

    /* NOTE: both r_fnm and v_fnm are set up larger than needed */
    /* to be able to add a filename to a directory name!        */

#ifdef DEBUG
    printf (" -> appending '/%s'\n", dirinf);
#endif /* DEBUG */
    strcat (r_fnm, "/");
    strcat (r_fnm, dirinf);
    /* strcat (v_fnm, dirinf); */
  }
  /* END library function isolation (1996-03-17 12:39:48) ***************** */

  return 0;
}

/* ------------------------------------------------------------------------ */
int fvf_set_dirinf (char *s)
{
  if (dirinf_allocated)
  {
    free_or_what (dirinf);
    dirinf= (char *) 0;
  }

  if (s != (char *) 0 && *s != 0)
  {
    if (strlen (s)-4 >= DEF_FNM_EXTRA) return -1; /* T2D: that's ugly! */

    dirinf= strdup (s);
    dirinf_allocated= 1;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int fvf_set_dirinf_callback (
FVF_get_directory_listing *proc,
void *client_data)
{
  fvf_get_dirinf= proc;
  fvf_get_dirinf_cd= client_data;

  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef DEBUG
static char line [256];

char *XSTR (char *str)
{
  return (str == (char *) 0) ? "(null)" : str;
}
#endif /* DEBUG */

#ifdef DEBUG_main
static char *assumed_path= (char *) 0;

int main (int argc, char *argv [])
{
  int i;
  int done= 0;

  for (i= 1; i < argc; i++)
  {
    if (strncmp (argv [i], "-p", 2) == 0)
    {
      assumed_path= argv [i]+2;
      continue;
    }
    
    /* assumed_path= argv [i]; *****/
    print_virtual_file (DFILE, argv [i]);
    done++;
  }

  while (done == 0)
  {
    fprintf (DFILE, "filename: ");
    scanf ("%s", line);
    if (line [0] == '#') line [0]= 0;

    print_virtual_file (DFILE, line);
  }

  return 0;
}

int print_virtual_file (FILE *fo, char *str)
{
  char *vir, *rea;
  char *reverse_lookup;
  int rc;

  rea= vir= reverse_lookup= (char *) 0;
  rc= find_virtual_file (str, assumed_path, &rea, &vir);

  fprintf (fo, "filename= '%s'\n", XSTR (str));
  fprintf (fo, "path    = '%s'\n", XSTR (assumed_path));
  fprintf (fo, "real    = '%s'\n", XSTR (rea));
  fprintf (fo, "virtual = '%s'\n", XSTR (vir));
  fprintf (fo, "--------------\n");

  return 0;
}

#endif /* DEBUG_main */
