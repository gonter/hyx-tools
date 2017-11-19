/*
 *  FILE E:\usr\sgml\hyxx.c
 *
 *  HyperText Extract - fÅr FM
 *
 *  1990 04 13
 *
 */

# include <stdio.h>
# include <string.h>
# include <io.h>

void cdecl main (int, char *[]);

static char aut [66];

void main (int argc, char *argv [])
{

  FILE *fi,
       *fo;
  int  i,
       c;
  long pos_from=0L,
       pos_to=0L;

  for (i=0;i<6;i++)
      {
        c= argv [2][i];
        if (c >= 'a' && c <= 'f') c = c-'a'+10; else
        if (c >= 'A' && c <= 'F') c = c-'A'+10; else
        if (c >= '0' || c <= '9') c = c-'0'; else return;
        pos_from = pos_from*16L + (long) c;
      }
  for (i=7;i<12;i++)
      {
        c= argv [2][i];
        if (c >= 'a' && c <= 'f') c = c-'a'+10; else
        if (c >= 'A' && c <= 'F') c = c-'A'+10; else
        if (c >= '0' || c <= '9') c = c-'0'; else return;
        pos_to = pos_to*16L + (long) c;
      }

  if (argc < 3) return;

  if (argc > 3)
       {
         if (argv [3][strlen (argv [3])-1] == '\\')
              sprintf (aut, "%s%s", argv [3], argv [2]);
         else sprintf (aut, "%s\\%s", argv [3], argv [2]);
       }
  else {
         strcpy (aut, argv [2]);
       }

/******************
printf ("arc=%s pos_from=%lx pos_to=%lx out=%s\n",
  argv [1], pos_from, pos_to, aut);
getch ();
******************/

  if (access (argv [1], 0) != 0) return;
  fi = fopen (argv [1], "rb");
  if (fi == (FILE *) 0) return;
  fo = fopen (aut, "wb");
  if (fo == (FILE *) 0) goto ST;

  fseek (fi, pos_from, 0);
  for (; pos_from <= pos_to && ! feof (fi); pos_from++)
      fputc (fgetc (fi), fo);
  fclose (fo);
ST:
  fclose (fi);
}
