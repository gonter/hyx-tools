/*
 *  FILE /usr/sbr/fsopen.c
 *
 *  File Open in Shared Mode
 *
 *  1988 03 07
 *
 *  Include Files:   <stdio.h>
 *                   <share.h>
 *                   <fcntl.h>
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/sbr.h>

# pragma check_stack(off)

# define PMODE   S_IREAD | S_IWRITE   /* Archive File */

extern int _doserrno;

/* ------------------------------------------------------------------------ */
FILE *fsopen (
char *file_name,        /* Filename des zu ”ffnenden Files      */
char *file_mode,        /* fopen (file_name, file_mode);        */
unsigned int open_mode, /* open (file_name, open_mode);         */
int   share_mode,       /* Share Codes                          */
int   retry,            /* Zahl der Versuche                    */
int  *err)              /* DOS Error Code; Fehlercode           */
/* RETURN: file_pointer (Stream); err := 0                      */
/*         (FILE *) 0 --> File not opened; err := Fehlercode    */
{
  int fp;

  for (;;)
  {
RETRY:
    fp = sopen (file_name, open_mode, share_mode);
    if (fp >= 0) break;

/************************
printf ("sopen: _doserrno = %04x %3d\n", _doserrno, _doserrno);
getch ();
************************/

    if (_doserrno == 2)  /* File not found: */
       if ((open_mode & 0x000F) == O_RDONLY)
       {
         return (FILE *) 0;
         *err = _doserrno;
       }
       else
       {
         fp = creat (file_name, PMODE);
         close (fp);
         goto RETRY;
       }

    if (--retry <= 0)
    {
      return (FILE *) 0;
      *err = _doserrno;
    }
  }
  *err = 0;

  return fdopen (fp, file_mode);
}
