/*
 *  FILE %ds/ytree/ytt.c
 *
 *  written:       2003-06-25
 *  latest update: 2003-06-25
 *  $Id: ytt2.c,v 1.1 2003/06/25 14:38:29 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/*** #define TEST1 TOO BROKEN ***/
#define TEST2 /* broken! */
#define TEST3
/* ------------------------------------------------------------------------ */
static struct YTREE *yt1= (struct YTREE *) 0;
static struct YTREE *yt2= (struct YTREE *) 0;
static struct YTREE *yt3= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
static int ytree_dump_file (struct YTREE *yt, char *fnm)
{
  FILE *FO;
  FO= fopen (fnm, "wb");
  if (FO == (FILE *) 0)
  {
    printf ("cant write to %s\n", fnm);
    return -1;
  }
  ytree_size (yt);
  ytree_dump (FO, yt);
  fclose (FO);
  return 0;
}

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  char *fnm;
  FILE *FI;
  int rc1, rc2, rc3;

  if (argc <= 1)
  {
    printf ("not enough parameters\n");
    return 0;
  }

  fnm= argv[1];
  FI= fopen (fnm, "rb");
  if (FI == (FILE *) 0)
  {
    printf ("cant read %s\n", fnm);
    return 0;
  }

#ifdef TEST1
  fseek (FI, 0L, 0);
  rc1= ytree_scan (FI, &yt1);
  ytree_dump_file (yt1, "@yt1.lut");
#endif

#ifdef TEST2
  fseek (FI, 0L, 0);
  rc2= ytree_full_scan (FI, &yt2, (long *) 0, 0, (char **) 0, 0);
  ytree_dump_file (yt2, "@yt2.lut");
  close (FI);
#endif

#ifdef TEST3
  yt3= lut_scan_ytree (fnm, 0L);
  ytree_dump_file (yt3, "@yt3.lut");
#endif

  return 0;
}
