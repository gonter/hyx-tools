/*
 *  include FILE <gg/lexutil.h>
 *
 *  lexicon utilities
 *
 *  written:       1991 04 27
 *  latest update: 1994-07-17
 *
 */

#ifndef __GG_lexutil__
#define __GG_lexutil__

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif
#endif

int cdecl ISPELL_derive (char *orig, int flag, char *deriv);

#endif /* __GG_lexutil__ */
