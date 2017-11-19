/*
 *  include FILE <gg/ebcasc.h>
 *
 *  written:       1992 08 30
 *  latest update: 1994-11-11
 *
 */

#ifndef __GG_ebcasc__
#define __GG_ebcasc__

#define TABLE_NAME "ebc--asc.cod"

int cdecl EBCDIC_ASCII_INIT (void);
int cdecl EBCDIC_ASCII_convert (char p[], int start, int lng);
int cdecl EBCDIC_ASCII_char_convert (int ch);
#endif /* __GG_ebcasc__ */
