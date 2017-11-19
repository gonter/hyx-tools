/*
 *  FILE %sbr/fnames.c
 *
 *  Suchen von Files ueber DOS
 *
 *  written:       1987 10 21
 *                 1990 02 03: Revision
 *  latest update: 1996-08-11 10:24:38
 *
 */

#include <dos.h>
#include <gg/fnames.h>

/* DTA - Operationen ------------------------------------------------------ */
void Fsetdta (struct dta_buff *dta)
{
#ifdef LARGE_MODEL
  bdos (Setdta, FP_OFF (dta), FP_SEG (dta));
#else
  bdos (Setdta, FP_OFF (dta), 0);
#endif
}

/* DTA - Operationen ------------------------------------------------------ */
int Fsfirst (char *name, int att)
{
  union REGS inregs, outregs;
  struct SREGS sregs;

  inregs.h.ah= First;
  sregs.ds= FP_SEG (name);
  inregs.x.dx= FP_OFF (name);
  inregs.x.cx= att;

  intdosx (&inregs, &outregs, &sregs);
  return ((outregs.x.cflag) ? outregs.x.ax : 0);
}

/* DTA - Operationen ------------------------------------------------------ */
int Fsnext (void)
{
  union REGS inregs, outregs;
  inregs.h.ah= Next;

  intdos (&inregs, &outregs);
  return ((outregs.x.cflag) ? outregs.x.ax : 0);
}
