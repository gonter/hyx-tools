/*
 *  FILE ~/usr/sbr/extcmp.c
 *
 *  compare two filenames by their extensions
 *  Zwei Files nach Extensions vergleichen
 *
 *  written:       1991 12 07: aus fmw.c isoliert
 *  latest update: 1994-08-13
 *
 */

#include <string.h>
#include <gg/filename.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int extcmp (char *s1, char *s2)
{
  int i1, i2;
  int p= 0;             /* flags: bit 0: s1 has an extension                */
                        /*        bit 1: s2 has an extension                */

  for (i1= 0; s1 [i1]; i1++)
    if (s1 [i1] == '.') 
    {
      p |= 0x01;
      break;
    }

  for (i2= 0; s2 [i2]; i2++)
    if (s2 [i2] == '.')
    {
      p |= 0x02;
      break;
    }

  /* Moeglichkeiten:  - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /* 0:    beide Filenamen ohne Extension: dann nach Filenamen              */
  /* 1, 2: Ein Filename von Ohne Extension: dann gelte                      */
  /*       (Filename OHNE Extension) > (Filename MIT Extension)             */
  /* 3:    beide Filenamen mit Extenstion                                   */
  /*       Falls Extenstions geleich, dann nach Filenamen                   */
  switch (p)
  {
    case 1: return  1;
    case 2: return -1;
    case 3:
      if ((p= strcmp (&s1 [i1], &s2 [i2])) != 0) return p;
  }

  /* case 0: */
  return strcmp (s1, s2);
}
