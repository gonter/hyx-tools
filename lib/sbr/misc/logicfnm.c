/*
 *  FILE %sbr/logicfnm.c
 *
 *  map a logic filename to a physical filename
 *
 *  written:       1991 09 18: as: %ned/12/ned1202.c)
 *                 1991 12 12: moved to %sbr as locicfnm.c
 *  latest update: 2001-02-11 10:05:55
 *  $Id: logicfnm.c,v 1.6 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#ifdef DEBUG
#define DFILE stdout
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MSDOS
#include <pwd.h>
#endif /* !MSDOS */

#include <gg/ytree.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
static struct VIRTUAL_FILENAME *vfn= (struct VIRTUAL_FILENAME *) 0;
static struct VIRTUAL_FILENAME **vfnp= &vfn;

#ifdef MSDOS
#define L_LNG 66
#define T_LNG 160
#define NED_LP_LNG 256
#else
#define L_LNG 1024
#define T_LNG 1024
#define NED_LP_LNG 1024
#endif

static char ned_lp [NED_LP_LNG];
static int all_has_been_read= 0;

static struct YTREE *yt_real_to_virtual= (struct YTREE *) 0;
static struct YTREE *yt_virtual_to_real= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
char *translate_logic_filename (const char *fnm)
{
  char *vfnv;

  return _translate_logic_filename (fnm, &vfnv);
}

/* ------------------------------------------------------------------------ */
char *_translate_logic_filename (const char *fnm, char **vfnv)
{
  char l1 [L_LNG];
  char *rv;
  char *env;
  int ch;
  int i;
  int env_l;
  struct VIRTUAL_FILENAME *a;
  int contains_logic_path= 0;
  int contains_drive_name= 0;
  const char *full_fnm;
  struct YTREE *yt;
#ifndef MSDOS
  struct passwd *pwd;
#endif /* !MSDOS */

  if ((full_fnm= fnm) == (char *) 0) return (char *) 0;

  switch (*fnm)
  {
    case '~':                   /* user or old way to describe a logic path */
      if (fnm [1] == '/'        /* ~/something                              */
         || fnm [1] == 0)       /* simply ~ to indicate the home directory  */
      {
#ifdef DEBUG
        fprintf (DFILE, ">> searching environment 'HOME'\n", l1+1);
#endif /* DEBUG */
        if ((env= getenv ("HOME")) == (char *) 0) goto NEXT1;
        fnm++;
        goto IS_HOME;
      }
      break;

    case '%':                   /* new way to describe a logic path         */
      break;

    case '$':                   /* environment variable                     */
      if (fnm [1] == '$')
      {
        fnm++;                  /* $$ means file begins with 1 $            */
        goto XNIL;
      }
      break;

/*********
    default:
      goto XNIL;
*********/
  }

NEXT1:
  /* copy the beginning of the filename string into l1 which then contains  */
  /* something like:                                                        */
  /*   %virtual_path                                                        */
  /*   $environment                                                         */
  /*   ~user                                                                */
  /*   drive:                                                               */
  for (i= 0; (ch= *fnm & 0x00FF) != 0; i++, fnm++)
  {
    if (ch == '/'
#ifdef MSDOS
        || ch == '\\'
#endif
       ) break;

    if (i+1 >= L_LNG) goto XNIL;
    l1 [i]= (char) ch;

    if (ch == ':')
    {
      i++;
      fnm++;
      contains_drive_name= 1;
      break;
    }
  }
  l1 [i]= 0;
  /* NOTE: *fnm can be empty now!!! (--> logic filename)                    */
  /*       usually it points now to the rest of the path beginning          */
  /*       after the SLASH or BACKSLASH.                                    */

#ifdef DEBUG
  fprintf (DFILE, ">> l1='%s'\n", l1);
#endif /* DEBUG */

  switch (l1 [0])
  {
    case '$':
      contains_logic_path= 1;
#ifdef MSDOS
      to_upper (l1);
#endif
#ifdef DEBUG
      fprintf (DFILE, ">> searching environment '%s'\n", l1+1);
#endif /* DEBUG */
      if ((env= getenv (l1+1)) == (char *) 0) goto XNIL;

IS_HOME:
      /* reserve enough space to combine the expanded environment and the   */
      /* filename and return the combination.                               */
      env_l= strlen (env);

      if ((rv= strdup_extra (env, DEF_FNM_EXTRA + strlen (fnm)))
          == (char *) 0) goto XNIL;

      if (env_l > 0
          && (env [env_l-1] == '/'
#ifdef MSDOS
              || env [env_l-1] == '\\'
#endif
             )
         ) env_l--;

      strcpy (&rv [env_l], fnm);
      goto END;

    case '~':
      contains_logic_path= 1;
#ifdef DEBUG
      fprintf (DFILE, ">> searching user '%s'\n", l1+1);
#endif /* DEBUG */
#ifndef MSDOS
      if ((pwd= getpwnam (l1+1)) != (struct passwd *) 0)
      {
#ifdef DEBUG
        fprintf (DFILE, ">> home is '%s'\n", pwd->pw_dir);
#endif /* DEBUG */
        if ((env= pwd->pw_dir) != (char *) 0) goto IS_HOME;
      }
      goto XNIL;
#else /* !MSDOS */
      break; /* in dos this will be translated ! */
#endif /* MSDOS */

    case '%':
      contains_logic_path= 1;
      break;
  }

  if ((yt= ytree_lookup_word (yt_virtual_to_real, (unsigned char *) l1))
           != (struct YTREE *) 0
      && (yt->YT_flags & YTflag_EOW)
      && (a= (struct VIRTUAL_FILENAME *) yt->YT_info)
          != (struct VIRTUAL_FILENAME *) 0
     )
  {
FOUND:
    /* reserve enough space to combine the expanded virtual path and the    */
    /* filename and return the combination.                                 */
    if (vfnv != (char **) 0) *vfnv= a->VFN_virtual;
    env_l= strlen (a->VFN_real);

    if ((rv= strdup_extra (a->VFN_real, DEF_FNM_EXTRA + strlen (fnm)))
        == (char *) 0) goto XNIL;

    if (contains_drive_name == 1
        && *fnm != '/'
#ifdef MSDOS
        && *fnm != '\\'
#endif
        && *fnm
       )
    {
      rv [env_l++]= '/';
      rv [env_l]= 0;
    }

    strcpy (&rv [env_l], fnm);
    goto END;
  }

  if (!all_has_been_read
      && (a= read_logic_filename_table (l1, 0))
          != (struct VIRTUAL_FILENAME *) 0)
    goto FOUND;

  if (!contains_logic_path) fnm= full_fnm;

XNIL:
  rv= strdup_extra (fnm, DEF_FNM_EXTRA);

END:
#ifdef MSDOS
  xchange (rv, '\\', '/');
  to_lower (rv);
#endif

  return rv;
}

/* ------------------------------------------------------------------------ */
struct VIRTUAL_FILENAME *read_logic_filename_table (
char *path_entry,
int read_all)
{
  struct VIRTUAL_FILENAME *a;

#ifdef DEBUG
  fprintf (DFILE, ">> read_logic_filename_table: path_entry=%s read_all=%d all_has_been_read=%d\n",
           path_entry, read_all, all_has_been_read);
#endif /* DEBUG */

  if (all_has_been_read) return (struct VIRTUAL_FILENAME *) 0;

  set_etc_filename (ned_lp, "ned.lp");

#ifdef DEBUG
  fprintf (DFILE, ">> read_logic_filename_table: ned_lp=%s\n", ned_lp);
#endif /* DEBUG */

  a= _read_logic_filename_table (ned_lp, path_entry, read_all);
  if (read_all) all_has_been_read= 1;

  return a;
}

/* ------------------------------------------------------------------------ */
struct VIRTUAL_FILENAME *_read_logic_filename_table (
char *lp_file,
char *path_entry,
int read_all)
{
  struct VIRTUAL_FILENAME *a;
  struct VIRTUAL_FILENAME *b= (struct VIRTUAL_FILENAME *) 0;
  FILE *fi;
  char tmp [T_LNG];
  char *fields [2];
  int rc;
  int they_match= 0;

#ifdef DEBUG
  fprintf (DFILE, 
    ">> _read_logic_filename_table: lp_file=%s path_entry=%s read_all=%d\n",
    lp_file, path_entry, read_all);
#endif /* DEBUG */

  if ((fi= fopen (lp_file, "rt")) == (FILE *) 0)
    return (struct VIRTUAL_FILENAME *) 0;

  for (;;)
  {
    rc= fread_line (fi, tmp, T_LNG);
    if (rc <= 0 && feof (fi)) break;
    if (tmp [0] == '#')
    { /* comment of course... */
      continue;
    }

    rc= isolate_tokens (tmp, fields, 2);
    if (rc > 2) rc= 2;
    if (rc < 2) continue;

    if (read_all
        || (they_match= (path_entry != (char *) 0
                          && strcmp (fields [0], path_entry) == 0
                        )
           )
       )
    {
      if ((a= _define_logic_filename (fields [0], fields [1]))
          == (struct VIRTUAL_FILENAME *) 0)
        return (struct VIRTUAL_FILENAME *) 0;

      if (they_match) b= a;
      if (!read_all) break;
    }
  }
  fclose (fi);

  return b;
}

/* ------------------------------------------------------------------------ */
struct VIRTUAL_FILENAME *_define_logic_filename (
char *fn_virtual,
char *fn_real)
{
  struct VIRTUAL_FILENAME *a;

  if ((a= (struct VIRTUAL_FILENAME *)
          calloc (sizeof (struct VIRTUAL_FILENAME), 1))
      == (struct VIRTUAL_FILENAME *) 0)
    return (struct VIRTUAL_FILENAME *) 0;

  *vfnp= a;
  vfnp= &a->VFN_next;

  a->VFN_virtual= strdup (fn_virtual);
  a->VFN_real= strdup (fn_real);

  ytree_set_value (&yt_virtual_to_real, (unsigned char *) fn_virtual, (long) a);
  ytree_set_value (&yt_real_to_virtual, (unsigned char *) fn_real,    (long) a);

  return a;
}

/* ------------------------------------------------------------------------ */
int find_logic_filename (
char *actual_path,
char *vp_buffer,
int vp_lng)
{
  struct VIRTUAL_FILENAME *a;
  char *x;
  char *examined_path;
  char *next_examined_path;
  int l_v;                      /* length of virtual path component         */
  int l_r;                      /* length of real path component            */
  int l_r_prev;                 /* ... previously found                     */
  int rc= 0;

#ifdef DEBUG
  fprintf (DFILE, ">> find_logic_filename: ap=%s\n", actual_path);
#endif /* DEBUG */

  for (examined_path= actual_path;
       examined_path != (char *) 0;
       examined_path= next_examined_path)
  {
    next_examined_path= (char *) 0;
    l_r_prev= 0;

#ifdef DEBUG
    fprintf (DFILE, ">> find_logic_filename: examined=%s\n", examined_path);
#endif /* DEBUG */

    for (a= vfn; a != (struct VIRTUAL_FILENAME *) 0; a= a->VFN_next)
    {
      x= a->VFN_real;
      l_r= strlen (x);

      if (strncmp (x, examined_path, l_r) == 0 && l_r > l_r_prev)
      {
        rc= 1;
        l_r_prev= l_r;
        l_v= strlen (a->VFN_virtual);

        if (vp_buffer != (char *) 0
            && vp_lng > l_v + strlen (examined_path) - l_r + 2
           )
        {
          strcpy (vp_buffer, a->VFN_virtual);
          strcpy (vp_buffer + l_v, examined_path + l_r);
          next_examined_path= vp_buffer;
        }
      }
    }
  }

  return rc;
}

/* ------------------------------------------------------------------------ */
int flush_virtual_filename_table (void)
{
  struct VIRTUAL_FILENAME *p1, *p2;

#ifdef DEBUG
    fprintf (DFILE, ">> flush_virtual_filename_table\n");
#endif /* DEBUG */

  ytree_free (yt_virtual_to_real);
  ytree_free (yt_real_to_virtual);

  yt_virtual_to_real= yt_real_to_virtual= (struct YTREE *) 0;

  for (p1= vfn; p1 != (struct VIRTUAL_FILENAME *) 0; p1= p2)
  {
    p2= p1->VFN_next;
    free (p1->VFN_virtual);
    free (p1->VFN_real);
    free (p1);
  }

  vfn= (struct VIRTUAL_FILENAME *) 0;
  vfnp= &vfn;
  all_has_been_read= 0;

  return 0;
}

/* ------------------------------------------------------------------------ */
int vfn_set_read_flag (int val)
{
  int rc= all_has_been_read;
  all_has_been_read= val;
  return rc;
}

/* ------------------------------------------------------------------------ */
struct VIRTUAL_FILENAME *get_virtual_filename_table ()
{
  return vfn;
}
