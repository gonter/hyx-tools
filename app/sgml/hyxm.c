/*
 *  FILE E:\usr\sgml\hyxx.c
 *
 *  HyperText Extract - fÅr FM
 *
 *  1990 04 13
 *
 */

# include <stdio.h>
# include <io.h>

void cdecl main (int argc, char *argv []);

/* ------------------------------------------------------------------------ */
void main (int argc, char *argv [])
{

  FILE *fi,
       *fo;
  int  i, ch;
  long pos_from=0L,
       pos_to=0L;

  if (access (argv [1], 0) != 0) return;
  fo = fopen (argv [1], "ab");
  if (fo == (FILE *) 0) return;

  for (i=2;i<argc; i++)
  {
    fi = fopen (argv [i], "rb");
    if (fi == (FILE *) 0) goto ST;

    for (;;)
    {
      ch = fgetc (fi) & 0x00FF;
      if (feof (fi)) break;
      fputc (ch, fo);
    }
    fclose (fi);
  }

ST:
  fclose (fo);
}
