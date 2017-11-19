/*
 *  FILE ~/usr/ned/04/ned0406.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1990 01 12: Isolation
 *                 1991 01 03: Revision
 *  latest update: 1994-12-28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/dirty.h>
#include "ed.h"
#include "proto.h"

static void cdecl xx_fputc_code (int c, FILE *f);
static int cdecl xx_fgetc_code (FILE *f);
static int cdecl encode (int c);

/* ------------------------------------------------------------------------ */
static char G_CODE [30];
static int  G_PTR;
static int  G_LAST=-1;          /* letztes Zeichen Run Length encoded   */
static int  G_CNT;              /* Run Length Counter                   */

/* Patches: --------------------------------------------------------------- */
void fputc_code (int ch, FILE *fo) { int x; ch; fo; x;           }
int  fgetc_code (FILE *fi)         { int x;     fi; x; return 0; }

/* ------------------------------------------------------------------------ */
static void xx_fputc_code (int c, FILE *f)
{
  if (!G_CODE [0])
  {
    fputc (c, f);
    return;
  }
  if (G_LAST != c || G_CNT==254)
  {
    flush_last (f);
    G_LAST = c;
    G_CNT  = 1;
  }
  else G_CNT++;
}

/* ------------------------------------------------------------------------ */
static int xx_fgetc_code (FILE *f)
{
  int c;

  if (!G_CODE [0]) return fgetc (f) & 0x00FF;
RE_DO:
  if (G_CNT > 0)
  {
    G_CNT--;
    return G_LAST;
  }
  c =  encode (fgetc (f) & 0x00FF);
  if (c == 0x01)
  {
    G_LAST = encode (fgetc (f) & 0x00FF);
    G_CNT  = encode (fgetc (f) & 0x00FF);
    goto RE_DO;
  }
  else return c;
}

/* ------------------------------------------------------------------------ */
void set_code (char *cp)             /* set encryption code  */
{
  G_CODE [0] = 0;
  G_PTR = 0;
  G_LAST = -1; G_CNT = 0;

  if (cp == (char *) 0 || *cp == 0)
  {
    patch (fputc_code, fputc);
    patch (fgetc_code, fgetc);
    return;
  }

  strncpy (G_CODE, cp, 28);
  patch (fputc_code, xx_fputc_code);
  patch (fgetc_code, xx_fgetc_code);
}

/* ------------------------------------------------------------------------ */
void flush_last (FILE *f)
{
  if (!G_CODE [0]) return;
  switch (G_LAST)
  {
    default: if (G_CNT==1)
             {
               fputc (encode (G_LAST), f);
               break;
             }
    case  1: fputc (encode (0x01),   f);
             fputc (encode (G_LAST), f);
             fputc (encode (G_CNT),  f);
    case -1: break;
  }
}

/* ------------------------------------------------------------------------ */
static int encode (int c)
{
  c= (c ^ (G_CODE [G_PTR++] & 0x00FF)) & 0x00FF;
  if (G_CODE [G_PTR] == 0) G_PTR=0;
  return c;
}
