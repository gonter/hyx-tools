/*
 *  FILE ~/usr/ned/00/ned0031c
 *
 *  Sprungtabelle fuer Editor ned.c
 *  bzw. ned[0-7].c
 *
 *  written:       1987 03 21
 *                 1988 ?? ??: Kommando System (fuer Setup)
 *                 1989 04 23: Maus Menu System
 *                 1991 02 07: Revision
 *                 1991 06 01: Revision; Aenderung des Table Layouts
 *                 1993-08-01: include table for vi mode
 *                 1994-10-16: cloned from ned0001.c
 *  latest update: 1995-04-30
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif
#endif

#include "ed.h"

#include "ned0009.c"    /* Deklaration der primitiven Funktionen            */

static int cdecl xx (void);
static int xx () { return 0; }          /* Dummyfunktion */

#ifdef MSDOS
#define TBL_SIZE 0x0480
#define DOSPRIM(x)  (x)                 /* use dummy primitive              */
#else
#define TBL_SIZE 0x0400
#define DOSPRIM(x)  (xx)                /* use dummy primitive              */
#endif

/* ------------------------------------------------------------------------ */
int (*P_TBL [TBL_SIZE]) () =
{
#include "ned0031a.c"   /* * prefix group a: no prefix                      */
,
#include "ned0001x.c"   /* * prefix group q: ^Q                             */
,
#include "ned0001x.c"   /* * prefix group k: ^K                             */
,
#include "ned0001x.c"   /* * prefix group o: ^O                             */
,
#include "ned0001x.c"   /* * prefix group u: ^U                             */
,
#include "ned0031v.c"   /* * vi command table                               */
#ifdef MSDOS
,
#include "ned0031f.c"   /* * prefix group f: function keys                  */
#else
,
#include "ned0001x.c"   /* * prefix group x: dummy group                    */
#endif
} ;
