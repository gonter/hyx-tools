/*
 *  FILE E:\usr\sgml\sgmlt1.c
 *
 *  Convert SGML-Document into Text and NED-Feature files
 *
 *  1990 01 28
 *
 */

# include <stdio.h>
# include <gg/fnames.h>


# define  STDHLP stderr
# define  ARG_C_max       24
static char *arg_v [ARG_C_max];
static int   arg_c = 0;

static char filenm [64];

static int line_nr=1, column=0;

static FILE *f_out;
static long f_position=0L;


/* ------------------------------------------------------------------------ */
static char *HELP [] =
{ "USAGE:     SGMLT1 [options] {file name}\n",
  "OPTIONS:   -f<filename> ... List of Files\n",
  "EXAMPLES:  \n",
  "\n",
  "Converts SGML Document into Text with NED-Feature Files\n",
  "\n",
  "(@)ASGML2NED.c 0.0 #D$1989-02-14 15:45:00\n",
  "\n",
# include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
main (argc, argv)
int  argc;
char *argv [];
{ FILE *fi2;
  int i, j;
  int sgml_filter_tag_beg (),  x_tag_beg (),
      sgml_filter_tag_end (),  x_tag_end (),
      sgml_filter_tag_chr (),  x_tag_chr (),
      sgml_filter_com_beg (),
      sgml_filter_com_end (),
      sgml_filter_com_chr (),
      sgml_filter_chr     (),  x_out_char();

  patch (sgml_filter_tag_beg, x_tag_beg);
  patch (sgml_filter_tag_end, x_tag_end);
  patch (sgml_filter_tag_chr, x_tag_chr);
/*patch (sgml_filter_com_beg, x_tag_beg);
  patch (sgml_filter_com_end, x_tag_end);
  patch (sgml_filter_com_chr, x_tag_chr);*/
  patch (sgml_filter_chr,     x_out_char);
  sgml_filter_reset ();

  if (argc <= 1) goto HLP;
  for (i = 1; i < argc; i++)
      if (argv [i][0] == '-' ||  argv [i][0] == '/')
         switch (argv [i][1])
         { case 'f': case 'F':
                     if (argv [i][2] == 0) break;
                     if (arg_c+1 < ARG_C_max)
                        arg_v [arg_c++] = argv [i];
                     break;

           case 'a': case 'A':
HLP:
# include <gg/help.inc>
         }
      else if (arg_c+1 < ARG_C_max)
              arg_v [arg_c++] = argv [i];

  f_out = stdout;

  if (arg_c)
     for (i = 0; i < arg_c; i++)
         if (arg_v [i][0] == '-')
            {
                     if (access  (& arg_v [i][2], 0) != 0)
                        { fprintf (stderr, "File %s not found!\n",
                                   &arg_v [i][2]);
                          break;
                        }
                     fi2 = fopen (& arg_v [i][2], "rt");
                     for (;;)
                     { fscanf (fi2, "%s", filenm);
                       if (feof (fi2)) break;
                       wildcards (filenm);
                     }
                     fclose (fi2);
           }
       else wildcards (arg_v [i]);

  return 0;
}

/* ------------------------------------------------------------------------ */
wildcards (fn)
char *fn;
{ char *nm; int wild=0;
  for (nm=fn; *nm && !wild; nm++)
      if (*nm == '*' || *nm == '?') wild=1;
  if (wild)
     while ((nm=Fname_find (fn, FA_FILE)) != (char *) 0)
           sgml_to_ned (nm);
  else sgml_to_ned (fn);
}

/* ------------------------------------------------------------------------ */
sgml_to_ned (fn)
char *fn;
{ FILE *fi;
  int  ch;

  f_position=0L;

  if (access (fn, 0) != 0)
     { fprintf (stderr, "File %s not found!\n", fn);
       return -1;
     }
  fi = fopen (fn, "rb");
  for (;;)
  {
    ch = fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    sgml_filter (ch);
    f_position++;
  }
  fclose (fi);
}

/* ------------------------------------------------------------------------ */
x_out_char (ch)
int ch;
{
  if (ch == 0x0D) return;
  fputc (ch, f_out); column++;
  if (ch == 0x0A)
     {
       line_nr++;
       column = 0;
     }
}

/* ------------------------------------------------------------------------ */
static char tag_name [40];
static int  tag_lng;
static int  tag_type;

x_tag_beg ()
{
  fprintf (f_out, "[%d %d tag beg]\n", line_nr, column);
  column++;
  tag_lng=0;
  tag_type=0;
}

x_tag_end ()
{
  fprintf (f_out,
           "[%d %d tag end; type=%d lng=%d]\n",
           line_nr, column, tag_type, tag_lng);
}

x_tag_chr (ch)
int ch;
{
  if (tag_lng == 0)
     switch (ch)
     {
       case '/': tag_type = 1; break;
       case '!': tag_type = 2; break;
       default : tag_lng++;    break;
     }
  else tag_lng++;

  switch (ch)
  {
    case 0x0D: fputc ('\\', f_out); fputc ('D',  f_out); break;
    case 0x0A: fputc ('\\', f_out); fputc ('A',  f_out); break;
    case '\\': fputc ('\\', f_out); fputc ('\\', f_out); break;
    default  : fputc (ch, f_out);                        break;
  }
}
