/*
 *  FILE %sbr/genbaknm.c
 *
 *  File I/O: Backup File Name erzeugen
 *
 *  written:       1990 05 20
 *                 1991 02 03: Revision
 *  latest update: 1996-03-18 12:02:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/filename.h>

#ifdef __HPUX__
@@@
#define S_IFDIR _S_IFDIR
#endif

static char *NED_DIR= "_bak_ftr.ned";

/* ------------------------------------------------------------------------ */
char *generate_ned_name (char *fnm, char *ext, int check_subdir)
{
  int ii, jj;
  int idx;
  int ch;
  struct stat st;
  char *used_ned_name;

  if (fnm == (char *) 0 || *fnm == 0) return (char *) 0;

#ifdef DEBUG
  printf ("generate_ned_name (fnm='%s', ext='%s')\n", fnm, ext);
#endif /* DEBUG */

  ii= isolate_path (fnm);

  used_ned_name= malloc (strlen (fnm) + strlen (NED_DIR) + strlen (ext) + 5);

  strncpy (used_ned_name, fnm, ii+1);
  strcpy (used_ned_name +ii+1, NED_DIR);

#ifdef DEBUG
  printf ("ned_dir='%s'\n", used_ned_name);
#endif /* DEBUG */

  if ((stat (used_ned_name, &st) == 0 && (st.st_mode & S_IFDIR))
      || !check_subdir
     )
  {
#ifdef DEBUG
    printf ("ned_dir exists\n");
#endif /* DEBUG */
    idx= strlen (used_ned_name);
    used_ned_name [idx++]= '/';
    strcpy (used_ned_name + idx, fnm +ii+1);
  }
  else
  {
#ifdef DEBUG
    printf ("ned_dir does not exist\n");
#endif /* DEBUG */
    strcpy (used_ned_name,  fnm);
  }

#ifdef DEBUG
  printf ("used_ned_name='%s'\n", used_ned_name);
#endif /* DEBUG */

  for (ii= (jj= strlen (used_ned_name))-1; ii >= 0; ii--)
    switch (used_ned_name [ii])
    {
      case '.':
        /* check if filename has the form .cshrc or so */
        if (ii > 0
            && ((ch= used_ned_name [ii-1] & 0x00FF) == '/'
#ifdef MSDOS
                || ch == '\\'
                || ch == ':'
#endif /* MSDOS */
               )
           ) goto BREAK;

        jj= ii;
        break;
      case '/':
#ifdef MSDOS
      case ':':
      case '\\':
#endif /* MSDOS */
        goto BREAK;
    }

BREAK:
  strcpy (used_ned_name + jj, ext);

  return used_ned_name;
}

#ifdef DEBUG
static char line [100];

int main (void);
int main ()
{
  char *ftr_name, *bak_name;

  for (;;)
  {
    printf ("Filename: ");
    scanf  ("%s", line);
    ftr_name= generate_ned_name (line, ".ftr", 1);
    bak_name= generate_ned_name (line, ".bak", 1);
    printf ("ftr:      %s\n", ftr_name);
    printf ("bak:      %s\n", bak_name);
    printf ("-----------------------\n");
  }

  return 0;
}

#endif /* DEBUG */
