/*
 *  File ~/usr/aisbr/unify/ut1.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-08-11
 *
 */

#include <stdio.h>
#include <gg/unify.h>

int cdecl main (int argc, char *argv[]);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  int i;
  FILE *fi;
  struct FEATURE_STRUCTURE *fs;

  for (i=1; i<argc; i++)
  {
    fi= fopen (argv[i], "rb");
    fs_scan (fi, stdout, &fs, 0, 1);
    fclose (fi);

    printf ("#\n# ------------------\n");
    fs_print_feature_structure (stdout, fs, fs, 0, 0x0001, 1);
  }
  return 0;
}
