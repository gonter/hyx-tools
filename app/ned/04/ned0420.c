/*
 *  FILE %ned/04/ned0420.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1996-05-27 19:09:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "ed.h"
#include "proto.h"

extern int errno;

#ifndef MAX_FILESIZE
#define MAX_FILESIZE 350000L
#endif

/* ------------------------------------------------------------------------ */
int editable_file (char *fnm)
/* RETURN:                                                      */
/* 0 -> File can't be edited                                    */
/* 1 -> File does not exist but can be possibly edited          */
/* 2 -> File exists and can also possibly be edited             */
{
  struct stat buf;
  int ch;

  if (fnm == (char *) 0 || (ch= *fnm) == 0) return 0;

  if (ch == '%' || ch == '~' || ch == '$') return 1;

  if (stat (fnm, &buf) == -1)
  { /* File nicht zugreifbar: Ursache? */
    if (errno == ENOENT) return 1;
    return 0;
  }
  else
  { /* File vorhanden; Directory ????? */
    if (buf.st_mode & S_IFDIR) return 0;
#ifdef MSDOS
    if (buf.st_size > (off_t) MAX_FILESIZE) return 0;
#endif /* MSDOS */
    return 2;
  }
}
