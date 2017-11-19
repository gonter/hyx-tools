/*
 *  FILE %sbr/fnmdpath.c
 *
 *  duplicate assumed path or get current path and place that
 *  stuff in a "suitably" large buffer
 *  T2D: REDISIGN!  This could be abused with a buffer overflow if
 *       the calling method doesn't check!
 *
 *  written:       1996-03-17
 *  latest update: 2000-12-09 16:13:48
 *  $Id: fnmdpath.c,v 1.5 2004/05/08 15:43:20 gonter Exp $
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef MSDOS
#include <unistd.h>
#include <sys/param.h>
#endif

#include <gg/filename.h>

static int alloc_size;

/* ------------------------------------------------------------------------ */
char *duplicate_assumed_path (char *assumed_path)
{
  char *buffer;
  int ap_size;

  alloc_size= MAX_FNM_LENGTH + DEF_FNM_EXTRA;
  if (assumed_path != (char *) 0)
  {
    ap_size= strlen (assumed_path);
    if (ap_size+100 > alloc_size) alloc_size= ap_size+alloc_size;
  }

  if ((buffer= malloc (alloc_size)) != (char *) 0)
  {
    if (assumed_path == (char *) 0)

#ifdef MSDOS
      _get_current_directory (buffer);
#else
      /* see t_getcwd.c for additional information about getcwd () */
      buffer= getcwd (NULL, MAXPATHLEN);
#endif
    else strcpy (buffer, assumed_path);
  }
    
  return buffer;
}

/* ------------------------------------------------------------------------ */
int _duplicate_assumed_path_alloc_size (void)
{
  return alloc_size;
}
