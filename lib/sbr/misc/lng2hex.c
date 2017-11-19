/*
 *  FILE %sbr/lng2hex.c
 *
 *  convert a long (32bit) integer into a printable string
 *  see also:
 *  - hex2bin.c int cdecl hex_to_bin (char *hex, char *bin, int lng);
 *              convert a printable hex string into a binary data block
 *
 *  written:       1995-07-31
 *  latest update: 1999-11-28 12:17:57
 *
 */

#include <gg/dpp.h>

#define UNKNOWN_MODEL

/* ------------------------------------------------------------------------ */
int long_to_hex (long bin, char *hex)
{
#ifdef __IS_BIG_ENDIAN__
#undef UNKNOWN_MODEL
#ifdef __OLD__ /* 1996-07-21 15:41:06 */
  char *p;
  char bin_buffer [4];

  p= (char *) &bin;
  bin_buffer [0]= p [3];
  bin_buffer [1]= p [2];
  bin_buffer [2]= p [1];
  bin_buffer [3]= p [0];
#endif /* __OLD__ 1996-07-21 15:41:06 */
  return bin_to_hex_rev ((char *) &bin, hex, 4);
#endif

#ifdef __IS_LITTLE_ENDIAN__
#undef UNKNOWN_MODEL
  return bin_to_hex ((char *) &bin, hex, 4);
#endif

#ifdef UNKNOWN_MODEL
  NOTE: if you have a compilation error at this point, find out which
  hardware architecture you have and which preprocessor symbols your
  compiler defines by default, then create a #ifdef construct similar
  to the one for AIX and let me know. (g.gonter@ieee.org)
#endif /* UNKNOWN_MODEL */
}
