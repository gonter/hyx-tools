/*
 *  FILE %ned/06/ned0610.c
 *
 *  open a window and prompt for the file name
 *
 *  test read: file://localhost/autoexec.bat
 *
 *  written:       1987 04 08
 *                 1993-02-21: take history notes
 *  latest update: 1999-04-25 16:32:03
 *  $Id: ned0610.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

extern int oper_level;

/* ------------------------------------------------------------------------ */
int q_ofile (int flags)         /* NED_OPENF_*                              */
{
  char fnm [MAX_FNM_LENGTH];

  if (oper_level >= LEV_FNM) return -1;

  fnm [0]= 0;
  if (flags & NED_OPENF_CONTEXT)
    q_isolate_word (fnm, MAX_FNM_LENGTH-1, CHARSET_filename, 1);

  return ned_open_file (fnm, (char *) 0, (char *) 0, flags);
}
