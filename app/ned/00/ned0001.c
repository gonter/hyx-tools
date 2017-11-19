/*
 *  FILE %ned/00/ned0001.c
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
 *  latest update: 1997-02-20 12:44:14
 *  $Id: ned0001.c,v 1.2 2007/12/02 11:55:23 gonter Exp $
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

#define xx p_mac
#ifndef xx
static int cdecl xx (void);
static int xx () { return 0; }          /* Dummyfunktion                    */
#endif

#ifdef MSDOS
#define TBL_SIZE 0x0480
#define DOSPRIM(x)  (x)                 /* use dummy primitive              */
#else
#define TBL_SIZE 0x0500
#define DOSPRIM(x)  (xx)                /* use dummy primitive              */
#endif

#ifndef TBL_CTRL_SIZE
#define TBL_CTRL_SIZE 32
#endif /* TBL_CTRL_SIZE */

/* ------------------------------------------------------------------------ */
#ifdef USE_TK
#define TK(x)   (x)                     /* use stated primitive             */
#else
#define TK(x)   (xx)                    /* use dummy primitive              */
#endif

char *PFX_XX [] =
  { "WS", "1?", "^Q", "^K", "^O", "^U", "VI", "@@", "7?", "^P" } ;

char *PFX_QUOTE= "^P";

/* ------------------------------------------------------------------------ */
int (*P_TBL [TBL_SIZE]) () =
{
#include "ned0001a.c"   /* * prefix group a: no prefix                      */
,
#include "ned0001q.c"   /* * prefix group q: ^Q                             */
,
#include "ned0001k.c"   /* * prefix group k: ^K                             */
,
#include "ned0001o.c"   /* * prefix group o: ^O                             */
,
#include "ned0001u.c"   /* * prefix group u: ^U                             */
,
#include "ned0001v.c"   /* * vi command table                               */
,
#ifdef MSDOS
#include "ned0001f.c"   /* * prefix group f: function keys                  */
#else
#ifdef USE_TK
#include "ned0001t.c"   /* * prefix group x: dummy group                    */
#else
#include "ned0001c.c"   /* * prefix group x: dummy group                    */
#endif /* !USE_TK */
#endif /* !MSDOS */
} ;

/* ------------------------------------------------------------------------ */
int (*P_TBL_WordStar [TBL_CTRL_SIZE]) () =
{
#include "ned0016w.c"
} ;

/* ------------------------------------------------------------------------ */
int (*P_TBL_VI [TBL_CTRL_SIZE]) () =
{
#include "ned0016v.c"
} ;

/* ------------------------------------------------------------------------ */
int (*P_TBL_PICO [TBL_CTRL_SIZE]) () =
{
#include "ned0016p.c"
} ;
