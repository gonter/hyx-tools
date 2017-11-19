/*
 *  FILE %ned/01/ned0141.c
 *
 *  written:       1991 05 27
 *  latest update: 1999-04-25 16:29:37
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#ifndef MSDOS
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif
#include <stdlib.h>
#include "ed.h"
#include "proto.h"

extern struct FILECTRL *files;

/* ------------------------------------------------------------------------ */
void file_free (struct FILECTRL *fc)
{
  struct FILECTRL **fcp;

  for (fcp= &files; *fcp != (struct FILECTRL *) 0; fcp= &(*fcp)->next)
    if (*fcp == fc)
    {
      *fcp= fc->next;
      free (fc);
      return;
    }
}
