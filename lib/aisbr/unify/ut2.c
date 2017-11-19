/*
 *  File ~/usr/aisbr/unify/ut1.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-08-12
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
  struct FEATURE_STRUCTURE *fs1;
  struct FEATURE_STRUCTURE *fs2;
  struct FEATURE_STRUCTURE *fs_unified;
  int sr1_2, sr2_1;

  for (i= 1; i<argc; i++)
  {
    fi = fopen (argv[i], "rb");
    fs_scan (fi, stdout, &fs, 0, 1);
    fclose (fi);

    fs1= fs_trace_path (fs, "@fs1");
    fs2= fs_trace_path (fs, "@fs2");
    if (fs1 == (void *) 0) printf ("@fs1=[]\n");
    if (fs2 == (void *) 0) printf ("@fs2=[]\n");
    if (fs1 == (void *) 0 || fs2 == (void *) 0) continue;

    printf ("test unification for file %s\n", argv[i]);

    fs1=fs1->fs_tail;
    fs2=fs2->fs_tail;

    printf ("fs1 := [");
    fs_print_feature_structure (stdout, fs1, fs1, 8, 0x0300, 1);
    printf ("]\n");
    printf ("fs2 := [");
    fs_print_feature_structure (stdout, fs2, fs2, 8, 0x0300, 1);
    printf ("]\n");

    sr1_2= fs_subsumption (fs1, fs2);
    sr2_1= fs_subsumption (fs2, fs1);

    printf ("sr1_2=%d  sr2_1=%d\n", sr1_2, sr2_1);

    printf ("result -----------\n");
    print_feature_structure (stdout, fs, fs, 0, 0x0300, 1);
    printf ("\nunified ------------\n");

    fs_unified= fs_unify (fs1, fs2);
    if (fs_unified == (void *) 0) printf ("*FAIL*"); else
    fs_print_feature_structure (stdout, fs_unified, fs_unified, 0, 0x0300, 1);
  }
  return 0;
}
