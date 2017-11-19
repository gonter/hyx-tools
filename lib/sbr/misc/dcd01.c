/*
 *  FILE %sbr/dcd01.c
 *
 *  change the current working directory
 *  - process virtual paths and drive letters
 *
 *  TEST: This function may possibly not work under UNIX
 *
 *  written:       1995-12-03
 *  latest update: 1999-05-01 20:25:56
 *
 */

#include <string.h>
#include <stdlib.h>
#ifdef MSDOS
#include <direct.h>
#else
#include <stdio.h>
#endif /* MSDOS */
#include <gg/strings.h>
#include <gg/filename.h>

#ifdef MSDOS
#define DRIVE_OFFSET 2
#else
#define DRIVE_OFFSET 0
#endif /* !MSDOS */

/* #define DEBUG */

/* ------------------------------------------------------------------------ */
int dcd (char *dir_specified)
{
  char *dir_real;
  char *dir_virtual;
  int idx;

  if (dir_specified == (char *) 0 || *dir_specified == 0)
    dir_specified= getenv ("HOME");

  if (dir_specified == (char *) 0 || *dir_specified == 0
      || filename_definition (dir_specified, &dir_real, &dir_virtual,
                              (char *) 0) == -1
     )
   return -1;

#ifdef DEBUG
  printf ("dir_specified: '%s'\n", dir_specified);
  printf ("dir_real:      '%s'\n", dir_real);
  printf ("dir_virtual:   '%s'\n", dir_virtual);
#endif /* DEBUG */

  if (dir_real == (char *) 0 || *dir_real == 0) return -1;

  idx= strlen (dir_real)-1;
  if (idx > DRIVE_OFFSET && dir_real [idx] == '/') dir_real [idx]= 0;

#ifdef MSDOS
  {
    int current_drive;
    int wanted_drive;

    current_drive= get_current_disk (); /* 0 .. A and so on */
    wanted_drive= dir_real [0];
    if (wanted_drive >= 'a' && wanted_drive <= 'z')
      wanted_drive= wanted_drive - 'a';
    else
    if (wanted_drive >= 'A' && wanted_drive <= 'Z')
      wanted_drive= wanted_drive - 'A';
    else return -1;

    if (wanted_drive != current_drive) select_disk (wanted_drive);

    xchange (dir_real, '/', '\\');
  }
#endif /* MSDOS */

#ifdef MSDOS
  chdir (dir_real + DRIVE_OFFSET);
#else
  printf ("%s\n", dir_real + DRIVE_OFFSET);
#endif

  return 0;
}
