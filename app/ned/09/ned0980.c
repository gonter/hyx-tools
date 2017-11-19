/*
 *  FILE %ned/09/ned0980.c
 *
 *  dump the macro buffer
 *
 *  written:       1987 04 08
 *  latest update: 1996-02-01 10:45:05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dirty.h>
#include "ed.h"
#include "proto.h"

#ifdef __JUNK__ /* 1996-02-01 10:44:48 */
extern char MP  [];
extern int  MPo [];
extern int  MPs [];
extern int  MPwp;
#endif /* __JUNK__ 1996-02-01 10:44:48 */

/* ------------------------------------------------------------------------ */
void p_dump_macro ()
{
#ifdef __JUNK__ /* 1996-02-01 10:44:48 */
  FILE *f;
  struct NED_MACRO *mp;
  int i, j;

  if ((f= fopen ("MACRO.$$$", "w")) == (FILE *) 0) return;

  dump (f, MP, MPwp);

  for (i= 0; i < N_MACRO; i++)
  {
    mp= ned_main_context->NED_macro_table [i]; ...
    fprintf (f, "macro [%2d]: off=%4d lng=%4d\n",
             i, MPo [i], MPs [i]);
    for (j= 0; j < MPs [i]; j++)
         fprintf (f, "%02x ", MP [MPo[i]+j] & 0xFF);
    fprintf (f, "\n");
  }

  fclose (f);
#endif /* __JUNK__ 1996-02-01 10:44:48 */
}
