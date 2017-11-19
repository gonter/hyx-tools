/*
 *  FILE %sbr/logicfpt.c
 *
 *  print contents of the virtual file translation table
 *
 *  written:       2000-12-09
 *  latest update: 2000-12-09 16:32:51
 *  $Id: logicfpt.c,v 1.1 2000/12/09 17:35:39 gonter Exp $
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
int print_virtual_filename_table (FILE *fo)
{
  struct VIRTUAL_FILENAME *p1;
  int count= 0;

  fprintf (fo, "virtual filename table:\n");
  for (p1= get_virtual_filename_table ();
       p1 != (struct VIRTUAL_FILENAME *) 0;
       p1= p1->VFN_next)
  {
    fprintf (fo, "%3d: %s -> %s\n", count, p1->VFN_virtual, p1->VFN_real);
    count++;
  }

  return count;
}
