/*
 *  FILE %sbr/zip_0002.c
 *
 *  ZIP Quick Scanner: Beginn des CDE suchen
 *
 *  written:       1990 05 12
 *  latest update: 1995-12-25
 *  $Id: zip_0002.c,v 1.2 2009/10/13 12:59:25 gonter Exp $
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/zip.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long zip_find_cde_start (FILE *fi, long max_search)
{
  struct stat stb;
  int rc, ch, st;
  long search_pos;
  long chrs= 0L;

  rc= fstat (fileno (fi), &stb);
  if (rc != 0) return -1L;

  st= 0;
  for (search_pos  = stb.st_size-1L;
       search_pos >= 0L && max_search-- > 0L;
       search_pos --)
  {
    fseek (fi, search_pos, 0);
    ch= fgetc (fi) & 0x00FF;
    chrs++;
    switch (st)
    {
        case 0:
          if (ch == 0x06) st++;
          break;
        case 1:
          if (ch == 0x05) st++;
          else st= 0;
          break;
        case 2:
          if (ch == 'K') st++;
          else st= 0;
          break;
        case 3:
          if (ch == 'P')
          {
            /* Position sollte genauer untersucht werden ! */
            if (chrs >= 22L) return search_pos;
          }
          st= 0;
          break;
    }
  }

  return -1L;
}

