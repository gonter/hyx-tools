/*
 *  FILE ~/usr/sgml/sf05.c
 *
 *  tables for frame name to url translation
 *
 *  see also:
 *  sf03.c int cdecl frame_name2url (char *frame, char *url, int max_url);
 *  sf04.c int cdecl    url2frame_name (char *url, char *frame, int max_frame);
 *
 *  written:       1994-08-06
 *  latest update: 1994-09-10
 *
 */

#include <stdio.h>
#include <gg/hytxt.h>

char *SFCHR_FRAME= "#& :_/{}[]()|\"\\";
char *SFCHR_URL=   "nabcusQRSTUVPqB";
