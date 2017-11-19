/*
 *  FILE ~/usr/sbr/ftopen.c
 *
 *  file open in shared mode
 *
 *  include files: <stdio.h>
 *                 <share.h>
 *                 <fcntl.h>
 *
 *  written:       1988 03 07
 *  latest update: 1994-07-31
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

#define PMODE   S_IREAD | S_IWRITE   /* Archive File */

extern int _doserrno;

/* ------------------------------------------------------------------------ */
FILE *ftopen (
char *file_name,        /* Filename des zu oeffnenden Files     */
char *file_mode,        /* fopen (file_name, file_mode);        */
int open_mode,          /* open (file_name, open_mode);         */
int share_mode,         /* Share Codes                          */
int *err)               /* DOS Error Code; Fehlercode           */
/* RETURN: file_pointer (Stream); err := 0                      */
/*         (FILE *) 0 --> File not opened; err := Fehlercode    */
{
  long rv;

  open_mode;
  share_mode;

  rv= topen (file_name, 0x20);          /* ###################### */
                                        /* open_mode umsetzen !!! */
                                        /* ###################### */
  if (rv & 0xFFFF0000L)
  {
    *err= (int) rv;
    return (FILE *) 0;
  }

  *err= 0;

  return fdopen ((int) (rv & 0x0000FFFFL), file_mode);
}
