/*
 *  FILE usr/sbr/fnmcpyt.c
 *
 *  test:
 *  copy filename and replace its extension or filetype (under CMS)
 *
 *  latest update: 1993-04-25
 *
 */

#undef MSDOS
#define __CMS__
#include "fnmcpy.c"

static char dest[1024];

testit (char *t, char *e)
{
  fnmcpy (dest, t, e);
  printf ("t=%s  e=%s  d=%s\n", t, e, dest);
 
}

main ()
{
  testit ("abc.def.a",          ".bg");
  testit ("xyz..",              ".e7");
  testit ("blabla",             ".dra");
  testit ("blabla.x.y.z",       ".qua.adaf");
  testit ("blabla.x.y.z",       ".qua");
}
