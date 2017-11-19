/*
 *  FILE %sbr/getcdir0.c
 *
 *  written:       1994-08-12
 *  latest update: 1999-04-25 17:00:40
 *  $Id: getcdir0.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif /* !MSDOS */

#include <string.h>
#include <stdlib.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *_get_current_directory (char *buffer)
{
#ifndef MSDOS
  char *pwd;
#endif /* !MSDOS */

  if (buffer == (char *) 0
      && (buffer= malloc (MAX_FNM_LENGTH + DEF_FNM_EXTRA)) == (char *) 0
     ) return (char *) 0;

#ifdef MSDOS
  /* 2. Path ermittlen */
  buffer [0]= (char) get_current_disk () + 'A';
  buffer [1]= ':';
  buffer [2]= '\\';
  getpwd (buffer+3, 0);
#else
  pwd= getenv ("PWD");

  strcpy (buffer, (pwd == (char *) 0) ? "." : pwd);
#endif

  return buffer;
}
