/*
 *  FILE %sbr/wcrd_008.c
 *
 *  redesigned wildcard matching
 *
 *  written:       1996-08-10 redesigned wildcard.c
 *  latest update: 1998-07-19 11:25:09
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/strings.h>

#ifdef MSDOS
#include <gg/fnames.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#endif /* !MSDOS */

#include <gg/array.h>
#include <gg/filename.h>
#include <gg/wildcard.h>

/* ------------------------------------------------------------------------ */
int wcrd2_wildcards_search (struct WCRD *wcrd)
{
  char *nm;                     /* filename currently processed             */
  int matches;                  /* 1 -> file matches with pattern           */
  int subdirs;                  /* 1 -> process subdirectories              */
  int files= 0;                 /* 1 -> process files                       */
  char *fnm;
  char *path;                   /* currently used path                      */
  char *pattern;                /* currently used filename pattern          */
  int actual_index;             /* positition where filenames are appended  */
  struct ARRAY_CONTROL *ac_files;
  struct ARRAY_CONTROL *ac_dirs;
  WCRD_processor *prc_file;
  void *cd_file= (void *) 0;
  int rc= 0;
  int is_dir;                   /* 1 -> entry refers to directory           */
#ifdef MSDOS
  struct dta_buff l_dta;        /* result of directory lookup               */
  int look;                     /* success indicator for directory lookup   */
#else
  DIR *dh;
  struct dirent *de;
  struct stat st;
#endif /* !MSDOS */

  path=         wcrd->actual_path;      /* Fixed buffer: WCRD_buffer_size   */
  fnm=          wcrd->actual_filenm;
  pattern=      wcrd->actual_pattern;
  actual_index= wcrd->actual_index;
  subdirs=      wcrd->subdirs;
  strcpy (fnm, path);

  if (actual_index > 0)
  {
#ifdef MSDOS
    fnm [actual_index]= '\\';
#else
    fnm [actual_index]= '/';
#endif /* !MSDOS */
    fnm [actual_index+1]= 0;
  }

  if ((prc_file= wcrd->file_processor) != (WCRD_processor *) 0)
  {
    files= 1;
    cd_file= wcrd->file_client_data;
  }

  ac_files= array_new ();
  ac_dirs= array_new ();

#ifdef MSDOS
  if (actual_index > 0)
      strcpy (path + actual_index, "\\*.*");
  else strcpy (path, "*.*");
#endif /* MSDOS */

#ifdef __wcrd_debug__
  printf ("search: actual_index=%d path='%s'\n", actual_index, path);
#endif

#ifdef MSDOS
  Fsetdta (&l_dta);
  for (look= Fsfirst (path, FA_ALL);
       !look;
       look= Fsnext ())
#else
  for (dh= opendir ((*path == 0) ? "." : path);
       dh != (DIR *) 0 && (de= readdir (dh)) != (struct dirent *) 0;
      )
#endif /* !MSDOS */
  {
#ifdef MSDOS
    nm= l_dta.name;
    is_dir= (l_dta.att & FA_DIRECTORY);
#else
    nm= de->d_name;

    /* T2D: check for buffer overflow */
    strcpy (fnm + ((actual_index > 0) ? actual_index+1 : 0), nm);

    rc= lstat (fnm, &st);       /* check for symlinks too                   */
    if (rc != 0) continue;      /* something fishy about that ...           */
    if (!(is_dir= S_ISDIR (st.st_mode)))
      if (!S_ISREG (st.st_mode)) continue;
#endif /* !MSDOS */

    if (is_dir)
    {
      if (subdirs
          && strcmp (nm, ".") != 0
          && strcmp (nm, "..") != 0
         ) array_push (ac_dirs, (void *) strdup (nm));
    }
    else
    {
      if (files)
      {
        matches= match (pattern, nm);

        if (matches) array_push (ac_files, (void *) strdup (nm));
      }
    }
  }

#ifdef MSDOS
  /* printf ("look=%d\n", look); */
#else
  if (dh != (DIR *) 0) closedir (dh);
#endif /* !MSDOS */

  while ((nm= (char *) array_shift (ac_files)) != (char *) 0)
  {
    /* T2D: check for buffer overflow */
    strcpy (fnm + ((actual_index > 0) ? actual_index+1 : 0), nm);
    free (nm);

#ifdef MSDOS
    xchange (fnm, '\\', '/');
    to_lower (fnm);
#endif /* MSDOS */

    rc= (*prc_file) (fnm, cd_file);
    if (wcrd->leave > 0) goto LEAVE;
  }

#ifdef __wcrd_debug__
printf ("  processing %ld dirs\n", array_elements (ac_dirs));
#endif

  if (subdirs)
  {
    WCRD_processor *prc_pre;
    void *cd_pre= (void *) 0;
    WCRD_processor *prc_post;
    void *cd_post= (void *) 0;

    if ((prc_pre= wcrd->dir_pre_processor) != (WCRD_processor *) 0)
      cd_pre= wcrd->dir_pre_client_data;
    if ((prc_post= wcrd->dir_post_processor) != (WCRD_processor *) 0)
      cd_post= wcrd->dir_post_client_data;

    while ((nm= (char *) array_shift (ac_dirs)) != (char *) 0)
    {
#ifdef __wcrd_debug__
      printf ("  process dir '%s'\n", nm);
#endif

      if (actual_index > 0)
      {
#ifdef MSDOS
        path [actual_index]= '\\';
#else
        path [actual_index]= '/';
#endif /* !MSDOS */
        strcpy (path + actual_index+1, nm);
        wcrd->actual_index= actual_index + strlen (nm) + 1;
      }
      else
      {
        strcpy (path, nm);
        wcrd->actual_index= strlen (nm);
      }
      free (nm);

      if (prc_pre != (WCRD_processor *) 0)
      {
        strcpy (fnm, path);
#ifdef MSDOS
        /* under MSDOS we see the pattern as part of the path!!!            */
        /* strip that off now, we are not interested in that here!          */
        if (actual_index > 0) fnm [actual_index]= 0;
        xchange (fnm, '\\', '/');
        to_lower (fnm);
#endif /* MSDOS */
        (*prc_pre) (fnm, cd_pre);
      }

      wcrd2_wildcards_search (wcrd);

      if (wcrd->leave > 0) goto LEAVE;

      if (prc_post != (WCRD_processor *) 0)
      {
        strcpy (fnm, path);
#ifdef MSDOS
        /* under MSDOS we see the pattern as part of the path!!!            */
        /* strip that off now, we are not interested in that here!          */
        if (actual_index > 0) fnm [actual_index]= 0;
        xchange (fnm, '\\', '/');
        to_lower (fnm);
#endif /* MSDOS */
        (*prc_post) (fnm, cd_post);
      }
    }
  }

LEAVE:
  ac_files->element_destructor=
   ac_dirs->element_destructor= free;

  array_dispose (ac_files);
  array_dispose (ac_dirs);

  return rc;
}
