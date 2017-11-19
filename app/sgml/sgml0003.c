/*
 *  FILE E:\usr\sgml\sgml0003.c
 *
 *  File mit SGML-Tags in NED-File umwandeln
 *
 *  1990 04 07: aus File SGML2NED.C isoliert
 *
 */

# include <stdio.h>
# pragma check_stack(off)

static int line_nr, column;

static FILE    *f_txt,  /* Text    des SGML-Dokuments   */
               *f_ftr;  /* Feature                      */

/* ------------------------------------------------------------------------ */
static do_nothing () {}

/* ------------------------------------------------------------------------ */
sgml_to_text (
char *fn_in,            /* Name des Input-Files                 */
char *fn_txt,           /* Name des Output-Text-Files           */
char *fn_ftr,           /* Name des Output-Feature-Files        */
int   out_mode,         /* 0 .. write new, 1 .. append          */
long  pos_from,         /* Teil des Frames                      */
long  pos_to)
{
  FILE *fi;
  int  ch;
  int  f_ftr_mode=0;   /* closed */
  int  return_value=0;
  long lng;

  /* */
  int sgml_filter_tag_beg (),  x_tag_beg (),
      sgml_filter_tag_end (),  x_tag_end (),
      sgml_filter_tag_chr (),  x_tag_chr (),
      sgml_filter_com_beg (),
      sgml_filter_com_end (),
      sgml_filter_com_chr (),
      sgml_filter_chr     (),  x_out_char();

  if (fn_txt == (char *) 0) return -1;
  if ((f_txt = fopen (fn_txt, (out_mode)?"ab":"wb")) == (FILE *) 0) return -1;
  if (fn_ftr == (char *) 0)
       {
         patch (sgml_filter_tag_beg, do_nothing);
         patch (sgml_filter_tag_end, do_nothing);
         patch (sgml_filter_tag_chr, do_nothing);
         patch (sgml_filter_com_beg, do_nothing);
         patch (sgml_filter_com_end, do_nothing);
         patch (sgml_filter_com_chr, do_nothing);
       }
  else {
         patch (sgml_filter_tag_beg, x_tag_beg);
         patch (sgml_filter_tag_end, x_tag_end);
         patch (sgml_filter_tag_chr, x_tag_chr);
         patch (sgml_filter_com_beg, x_tag_beg);
         patch (sgml_filter_com_end, x_tag_end);
         patch (sgml_filter_com_chr, x_tag_chr);

         if ((f_ftr = fopen (fn_ftr, (out_mode)?"ab":"wb")) == (FILE *) 0)
         {
           fclose (f_txt);
           return -1;
         }
         f_ftr_mode = 1;
         fprintf (f_ftr, "0 0 0 0 10 1 1 0\n");
         line_nr=1;
         column=0;
       }

  patch (sgml_filter_chr,     x_out_char);
  sgml_filter_reset ();

  if (access (fn_in, 0) != 0
      || (fi = fopen (fn_in, "rb")) == (FILE *) 0)
  {
    return_value = -1;
    goto STOP2;
  }

  fseek (fi, pos_from, 0);
  for (lng = pos_to-pos_from+1L; lng > 0L; lng--)
  {
    ch = fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    sgml_filter (ch);
  }

  fclose (fi);
STOP2:
  if (f_ftr_mode > 0) fclose (f_ftr);
  fclose (f_txt);
  return return_value;
}

/* ------------------------------------------------------------------------ */
static x_out_char (long ch)
{
  int chr;

  chr = (int) ch;

  fputc (chr, f_txt);
  column++;
  if (ch == 0x0A)
  {
    line_nr++;
    column = 0;
  }
}

/* ------------------------------------------------------------------------ */
static x_tag_beg ()
{
  fprintf (f_ftr, "%d %d 0 ", line_nr, column);
  fputc (0x04, f_txt); column++;
}

/* ------------------------------------------------------------------------ */
static x_tag_end ()
{
  fputc (0x0D, f_ftr);
  fputc (0x0A, f_ftr);
}

/* ------------------------------------------------------------------------ */
static x_tag_chr (long ch)
{
  switch ((int) ch)
  {
    case 0x0D: fputc ('\\', f_ftr); fputc ('D',  f_ftr); break;
    case 0x0A: fputc ('\\', f_ftr); fputc ('A',  f_ftr); break;
    case '\\': fputc ('\\', f_ftr); fputc ('\\', f_ftr); break;
    default  : fputc (ch,   f_ftr);                      break;
  }
}
