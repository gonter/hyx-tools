/*
 *  FILE E:\usr\sgml\sgml0004.c
 *
 *  NED-File in File mit SGML-Tags umwandeln
 *
 *  1990 04 07
 *
 */

# include <stdio.h>
# pragma check_stack(off)

extern long ftell ();

static int line_nr, column;

static FILE    *f_txt,  /* Text    des SGML-Dokuments   */
               *f_ftr;  /* Feature                      */

/* ------------------------------------------------------------------------ */
text_to_sgml (
char *fn_out,           /* Name des Output-Hyptertext-Files     */
char *fn_txt,           /* Name des Input-Text-Files            */
char *fn_ftr,           /* Name des Input-Feature-Files         */
int   out_mode,         /* 0 .. write new, 1 .. append          */
long *pos_from,         /* Teil des Frames                      */
long *pos_to)
{
  FILE *f_out,
       *f_txt,
       *f_ftr;

  int cht, chf, dummy,
      return_value=0,
      ftr_line=-1,
      ftr_col=-1,
      txt_line=1,
      txt_col=0;

  long pos,
       fchar ();

  if (fn_txt == (char *) 0) return -1;
  if ((f_txt = fopen (fn_txt, "rb")) == (FILE *) 0) return -1;
  if (fn_ftr != (char *) 0)
       {
         if ((f_ftr = fopen (fn_ftr, "rb")) == (FILE *) 0)
         {
           fclose (f_txt);
           return -1;
         }
         while ((fgetc (f_ftr) & 0x00FF) != 0x0A); /* Status-Zeile Åberlesen */
         fscanf (f_ftr, "%d%d%d", &ftr_line, &ftr_col, &dummy);
         fgetc (f_ftr);
       }

  if (out_mode)
       {
         if ((f_out = fopen (fn_out, "ab")) == (FILE *) 0)
            {
              return_value=-1;
              goto STOP1;
            }
         fseek (f_out, (long) 0, 2);
         *pos_from = pos = ftell (f_out);
       }
  else {
         if ((f_out = fopen (fn_out, "wb")) == (FILE *) 0) return -1;
            {
              return_value=-1;
              goto STOP1;
            }
         *pos_from = pos = 0L;
       }

  for (;;)
  {
    cht = fgetc (f_txt) & 0x00FF;
    if (feof (f_txt)) break;
    if (ftr_line == txt_line && ftr_col == txt_col)
         { /* Feature gefunden; umwandeln in ein Tag */
           if (cht != 0x04) pos += fchar (cht, f_out);
           fputc ('<', f_out);
           pos++;
           while ((chf=fgetc (f_ftr) & 0x00FF) != 0x0A)
              if (chf != 0x0D)
                 {
                   fputc (chf, f_out);
                   pos++;
                 }
           fputc ('>', f_out);
           pos++;
           fscanf (f_ftr, "%d%d%d", &ftr_line, &ftr_col, &dummy);
           if (feof (f_ftr)) ftr_line=-1;
           else fgetc (f_ftr);
         }
    else {
           pos += fchar (cht, f_out);
         }
    txt_col++;
    if (cht==0x0A)
       {
         txt_col=0;
         txt_line++;
       }
  }

  *pos_to = pos-1L;

  fclose (f_out);
STOP1:
  if (fn_ftr != (char *) 0) fclose (f_ftr);
  fclose (f_txt);
  return 0;
}

/* ------------------------------------------------------------------------ */
long fchar (int character, FILE *file_out)
{
  switch (character)
  {
    case '<':
      fputs ("<0x3C>", file_out);
      return 6L;
    case '>':
      fputs ("<0x3E>", file_out);
      return 6L;
    default:
      fputc (character, file_out);
      return 1L;
  }
}





