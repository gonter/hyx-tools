/*
 *  FILE %ned/09/ned0921.c
 *
 *  macro functions:
 *  this module is a template that is used to generate the function
 *  modules for each macro.
 *
 *  written:       1987 09 10
 *                 1991 11 10: Revision
 *  latest update: 1994-07-09
 *  $Id: ned0921.c,v 1.2 2005/04/01 16:46:20 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#ifndef cdecl
#define cdecl
#endif
#endif

void cdecl MACRO_PRIM (void);
void cdecl p_macro (int);

void MACRO_PRIM ()  { p_macro (MACRO_NUM); }
