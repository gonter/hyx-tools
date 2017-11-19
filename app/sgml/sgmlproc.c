/*
 *  FILE ~/usr/sgml/sgml_process.c
 *
 *  general (old) SGML processor
 *
 *  written:       1990 05 26
 *  latest update: 1996-07-17
 *
 */

#include <stdio.h>
#include <gg/fnames.h>

#define  STDHLP stderr
#define  ARG_C_max       24
static char *arg_v [ARG_C_max];
static int   arg_c = 0;

/* Quick Hack: ------------------------------------------------------------ */
#define SUBDIRS                         /* Rekursive Suche durch das        */
                                        /* Filesystem moeglich              */
#define BETTER_FILENAME_MATCH           /* eigene Match Funktion            */
                                        /* sonst DOS Match Funktion         */

static char filenm [66];

#ifdef SUBDIRS
/* Where to search: recursion through directory tree: --------------------- */
static char actual_filenm  [128];
static char actual_drive   [  2];
static char actual_path    [128];
static char actual_pattern [ 30];
static int  subdirs = 0;
#endif

/* ------------------------------------------------------------------------ */
static int verbose_mode = 0;

static FILE *out_file = (FILE *) 0;
static int   out_open = 0;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE:     sgmlproc [options] {file name}\n",
  "OPTIONS:   -f<filename> ... List of Files\n",
#ifdef SUBDIRS
  "           -s -r        ... Subdirs\n",
#endif
  "           -v           ... Verbose Mode\n",
  "EXAMPLES:  \n",
  "\n",
  "(@)Asgmlproc.c 1.11 #D$1994-06-04 16:00:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int main (int  argc, char *argv [])
{
  FILE *fi2;
  int i, j;

  if (argc <= 1) goto HLP;

  for (i = 1; i < argc; i++)
      if (argv [i][0] == '-' ||  argv [i][0] == '/')
         switch (argv [i][1])
         {
           case 'f': case 'F':
                     if (argv [i][2] == 0) break;
                     if (arg_c+1 < ARG_C_max)
                        arg_v [arg_c++] = argv [i];
                     break;

#ifdef SUBDIRS
           case 'r': case 'R':
           case 's': case 'S':
#endif
           case 'v': case 'V':
                     for (j=1; argv [i][j]; j++)
                        switch (argv [i][j])
                        {
#ifdef SUBDIRS
                          case 'r': case 'R':
                          case 's': case 'S':
                            subdirs = 1;
                            break;
#endif
                          case 'v': case 'V':
                            verbose_mode = 1;
                            break;
                        }
                     break;

HLP:
#include <gg/help.inc>
         }
      else if (arg_c+1 < ARG_C_max)
              arg_v [arg_c++] = argv [i];

  if ((out_file= fopen ("SGML.@@", "wb")) != (FILE *) 0) out_open = 1;

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
#ifdef SUBDIRS
                       if (wildcards_or_rec (filenm) == -1)
                          {
                            fclose (fi2);
                            goto STOP;
                          }
#else
                       wildcards (filenm);
#endif
                     }
                     fclose (fi2);
           }
#ifdef SUBDIRS
       else { if (wildcards_or_rec (arg_v [i]) == -1) goto STOP; }
  else wildcards_or_rec ("*.*");
#else
       else wildcards (arg_v [i]);
  else sgml_process ("Default.fil");
#endif

  flush_segments ();

STOP:
  if (out_open) fclose (out_file);
  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef SUBDIRS
static rec_wildcards (int lev)
{
  struct dta_buff l_dta;
  int actual_path_length;
  int look;

  Fsetdta (&l_dta);

/* fprintf (stderr, "%2d RC1: actual_path=%s\n", lev, actual_path); */
  actual_path_length = strlen (actual_path);
  if (actual_path_length)
       sprintf (actual_filenm, "%s\\%s", actual_path, actual_pattern);
  else sprintf (actual_filenm,     "%s",              actual_pattern);
  if (wildcards (actual_filenm) == -1) return -1;

  if (actual_path_length)
       sprintf (actual_filenm, "%s\\*.*", actual_path);
  else strcpy  (actual_filenm, "*.*");

  Fsetdta (&l_dta);
  for (look=Fsfirst (actual_filenm, 0x10);
       !look;
       look=Fsnext ())
  {
    if ((l_dta.att & 0x10) == 0 ||
        strcmp (l_dta.name, ".")  == 0 ||
        strcmp (l_dta.name, "..") == 0)
       continue;
    if (actual_path_length)
         sprintf (& actual_path [actual_path_length], "\\%s", l_dta.name);
    else sprintf (& actual_path [actual_path_length],   "%s", l_dta.name);
    if (rec_wildcards (lev+1) == -1) return -1;
    Fsetdta (&l_dta);
  }
  return 0;
}

/* ------------------------------------------------------------------------ */
wildcards_or_rec (char *fn)
{
  int i;
  int drive_letter, path_length;

  if (subdirs)
       {
         for (i=strlen (fn) -1; i >= 0; i--)
             if (fn [i] == '\\' || fn [i] == ':') break;
         strcpy (actual_path, fn);
         if (i>=0)
            if (actual_path [i] == ':')
                  actual_path [i+1]= 0;
            else  actual_path [i  ]= 0;
         else     actual_path [  0]= 0;
         strcpy (actual_pattern, &fn [i+1]);
         if (actual_pattern [0] == 0)
            strcpy (actual_pattern, "*.*");
         path_length = strlen (actual_path);
         if (actual_path [1] == ':' && actual_path [0] == '*')
              {
                i = bdos (0x19, 0x00, 0x00);   /* aktuelles Drive ermitteln */
                drive_letter = bdos (0x0E, i, 0x00) & 0x00FF;
                drive_letter += 'A'; i &= 0x00FF;
                for (i = (i >= 2) ? 'C' : i+'A' ;
                     i < drive_letter;
                     i++)
                {
                  actual_path [0] = i;
                  if (rec_wildcards (1) == -1) return -1;
                  actual_path [path_length] = 0;
                }
              }
         else {
                if (rec_wildcards (1) == -1) return -1;
              }
       }
  else {
         path_length = strlen (fn);
         if (fn [1] == ':' && fn [0] == '*')
              {
                i = bdos (0x19, 0x00, 0x00);   /* aktuelles Drive ermitteln */
                drive_letter = bdos (0x0E, i, 0x00) & 0x00FF;
                drive_letter += 'A'; i &= 0x00FF;
                for (i = (i >= 2) ? 'C' : i+'A' ;
                     i < drive_letter;
                     i++)
                {
                  fn [0] = i;
                  if (wildcards (fn) == -1) return -1;
                  fn [path_length] = 0;
                }
              }
         else {
                if (wildcards (fn) == -1) return -1;
              }
       }
  return 0;
}
#endif

/* ------------------------------------------------------------------------ */
wildcards (char *fn)
{
  char *nm;
  int wild=0;

  for (nm=fn; *nm && !wild; nm++)
      if (*nm == '*' || *nm == '?') wild=1;

  if (wild)
     {
#ifdef BETTER_FILENAME_MATCH
       to_upper (fn);
       while ((nm=Fname_find ("*.*", FA_FILE)) != (char *) 0)
             if (match (fn, nm) > 0) sgml_process (nm);
#else
       while ((nm=Fname_find (fn, FA_FILE)) != (char *) 0)
              sgml_process (nm);
#endif
     }
  else sgml_process (fn);
}

/* ------------------------------------------------------------------------ */
sgml_process (char *fn)
{
  FILE *fi;
  int  ch;

  if (access (fn, 0) != 0)
     {
       fprintf (stderr, "File %s not found!\n", fn);
       return -2;
     }

  sgml_to_list (fn);
}

/* ------------------------------------------------------------------------ */
sgml_fputs (char *s) { if (out_open) fputs (s, out_file); }
sgml_fputc (int   c) { if (out_open) fputc (c, out_file); }
