/*
 *  include FILE <gg/floskel.h>
 *
 *  general clauses for header files
 *
 *  written:       1994-12-03
 *  latest update: 2001-02-11 16:43:26
 *  $Id: floskel.h,v 1.3 2005/03/11 23:42:45 gonter Exp $
 *
 */

#ifndef __GG_floskel__
#define __GG_floskel__

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif
#endif

#if defined (_STDIO_H) || defined (_STDIO_H_) || defined (_H_STDIO)
#ifndef _FILE_DEFINED
#define _FILE_DEFINED
#endif
#endif

#ifdef stdout
#ifndef _FILE_DEFINED
#define _FILE_DEFINED
#endif
#endif

#ifdef _TIME_H_
#ifndef _TM_DEFINED
#define _TM_DEFINED
#endif
#endif

/* used for checking the correct assignment of function parameters */
#define PAR(name,value) (value)

#endif /* __GG_floskel__ */
