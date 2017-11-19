/*
 *  FILE %ds/codes/codeconv.c
 *
 *  universal characterset converter
 *  - HELP
 *  - prototypes
 *  - see also codetbl.c
 *
 *  LINKS:
 *    man page $codeconv
 *
 *  written:       1992-12-30
 *  latest update: 1997-10-24 11:12:37
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <time.h>
#include <gg/filename.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/codes.h>
#include <gg/sbr.h>
#include <gg/dirty.h>
#include <gg/dpp.h>

#define STDHLP stdout

/* ------------------------------------------------------------------------ */
struct CONVERTER
{
  char *fno;
  long *table;
};

/* ------------------------------------------------------------------------ */
static long init_value= 0L;
static long converter_table [256];
static char *table_name= (char *) 0;
static char *C_array_name= "static long TLT [256]";

#define MAX_LIST 40
static char *src [MAX_LIST] = { "pc",        "ascii" };
static char *dst [MAX_LIST] = { "iso8859_1", "ascii" };
static int src_cnt= 2;
static int dst_cnt= 2;
static int src_predef= 1;       /* 1 -> table is predefined                 */
static int dst_predef= 1;

#define MAX_ALL_FIELDS 100
static char *all_fields [MAX_ALL_FIELDS] =
{
  "def", "val"                  /* we also need definitions!                */
} ;
static int all_fields_cnt= 2;
static struct ARRAY_CONTROL *arguments;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: codeconv [options] {file name}\n",
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
#ifdef SUBDIRS
  "  -r ... recursive into sub directories\n",
#endif
  "  -t<fnm> ... name of the file containing the code tables\n",
  "  -s<id> ... source code [Def: pc, ascii]\n",
  "  -d<id> ... destination code [Def: iso8859_1, ascii]\n",
  "  -o<fnm> ... outfile\n",
  "  -w<m><fnm> ... write table to file\n",
  "    m=b ... binary\n",
/*"    m=p ... portable binary\n", */
  "    m=c ... C, C ... C Array\n",
  "    m=r ... REXX expression\n",
  "    m=R ... REXX translate expression\n",
  "    m=A ... IBM/370 ASSEMBLE\n",
  "    m=P ... Perl\n",
  "  -a<name> ... C array declaration, e.g. \"-along TLT_PC2ISO [256]\"\n",
  "  -i<val> ... initial value for the converter table\n",
  "NOTES:\n",
  "  Several -s and/or -d options might be present.\n",
  "\n",
  "(@)Acodeconv.c 1.06 #D$1996-02-23 11:11:08\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
int cdecl write_comment (FILE *fo, int mode, char *lsrc[], int lsrc_cnt,
                         char *ldst[], int ldst_cnt);
int cdecl main_cvt (char *fn, void *cd);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  char *outfile= (char *) 0;
  int rc;
  char *arg;
  struct CS_record *records;
  int write_mode= WRITE_MODE_undef;
  char *write_to_file= (char *) 0;
  struct CONVERTER cvt;
  struct WCRD *wcrd;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                       main_cvt, (void *) &cvt);
  if (argc <= 1) goto HLP;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
      switch (arg [1])
      {
        case 'a': case 'A':
          if (arg [2] == 0) break;
          C_array_name= arg+2;
          break;

        case 'd': case 'D':
          if (arg [2] == 0) break;
          if (dst_predef)
          {
            dst_predef= 0;
            dst_cnt= 0;
          }
          dst [dst_cnt++]= arg+2;
          break;

        case 'f': case 'F':
          if (arg [2] == 0) break;
          array_push (arguments, (void *) arg);
          break;

        case 'i': case 'I':
          init_value= get_parameter_value (arg+2);
          break;

        case 'o': case 'O':
          outfile= arg+2;
          break;

        case 's': case 'S':
          if (arg [2] == 0) break;
          if (src_predef)
          {
            src_predef= 0;
            src_cnt= 0;
          }
          src [src_cnt++]= arg+2;
          break;

        case 't': case 'T':
          if (arg [2] == 0) break;
          table_name= arg+2;
          break;

        case 'w': case 'W':
          switch (arg [2])
          {
            case 'b': case 'B':
              write_mode= WRITE_MODE_binary;
              break;
            case 'c':
              write_mode= WRITE_MODE_C;
              break;
            case 'C':
              write_mode= WRITE_MODE_C_ARRAY;
              break;
            case 'r':
              write_mode= WRITE_MODE_rexx;
              break;
            case 'R':
              write_mode= WRITE_MODE_REXX;
              break;
            case 'A':
              write_mode= WRITE_MODE_ASSEMBLE;
              break;
            case 'P':
              write_mode= WRITE_MODE_PERL;
              break;
            default:
              goto HLP;
          }
          write_to_file= arg+3;
          if (*write_to_file == 0) goto HLP;
          break;

#ifdef SUBDIRS
        case 'r': case 'R':
#endif
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
#ifdef SUBDIRS
              case 'r': case 'R':
                wcrd_set_subdirs (1);
                break;
#endif
            }
          break;

HLP:
#include <gg/help.inc>
      }
    else array_push (arguments, (void *) arg);
  }

  /* setup converter tables */
  if (table_name == (char *) 0)
    table_name= set_etc_filename ((char *) 0, CSF_TABLE);

  /* initialize table */
  for (i= 0; i < 256; i++) converter_table [i]= init_value;

  for (i= 0; i < src_cnt; i++) all_fields [all_fields_cnt++] = src [i];
  for (i= 0; i < dst_cnt; i++) all_fields [all_fields_cnt++] = dst [i];
  if ((records= cs_parse_code_table (table_name, all_fields, all_fields_cnt,
                                     1, 25))
      == (struct CS_record *) 0)
  {
    fprintf (stderr, "error parsing table %s!\n", table_name);
    goto HLP;
  }

  if ((rc= cs_records2table (records, src, src_cnt, dst, dst_cnt,
                        CSft_number, converter_table)) == -1)
  {
    fprintf (stderr,
      "couldn\'t setup converter table from information in %s",
      table_name);
    fprintf (stderr, "for conversion (%s", src[0]);
    for (i= 1; i < src_cnt; i++) fprintf (stderr, ",%s", src[i]);
    fprintf (stderr, ") -> (%s", dst[0]);
    for (i= 1; i < dst_cnt; i++) fprintf (stderr, ",%s", dst[i]);
    fprintf (stderr, ")\n");
    goto HLP;
  }

  if (write_mode)
  {
    FILE *ft;

    if (strcmp (write_to_file, "-") == 0)
         ft= stdout;
    else ft= fopen (write_to_file, "wb");

    if (ft == (FILE *) 0)
    {
      fprintf (stderr, "error: couldnt write to: %s\n", write_to_file);
      return 1;
    }

    write_comment (ft, write_mode, src, src_cnt, dst, dst_cnt);

    switch (write_mode)
    {
      case WRITE_MODE_C_ARRAY:
        fprintf (ft, "%s =\n", C_array_name);
        break;

      case WRITE_MODE_REXX:
        fprintf (ft, "return(translate(arg(1), ,\n");
        break;
    }

    print_long_table2 (ft, write_mode, converter_table, 256);

    if (ft != stdout) fclose (ft);
  }

  cvt.table= converter_table;
  cvt.fno= outfile;
  wcrd2_arguments (wcrd, arguments);

  return 0;
}

/* ------------------------------------------------------------------------ */
int write_comment (
FILE *fo,
int mode,
char *lsrc[],
int lsrc_cnt,
char *ldst[],
int ldst_cnt)
{
  struct tm *tm_s;
  long tt;
  char prefix [20];
  int i;

  if (lsrc_cnt < 1 || ldst_cnt < 1) return -1;

  tt= time ((long *) 0);
  tm_s= localtime (&tt);

  switch (mode)
  {
    case WRITE_MODE_C_ARRAY:
    case WRITE_MODE_C:
    case WRITE_MODE_REXX:
    case WRITE_MODE_rexx:
    case WRITE_MODE_PERL:
      fprintf (fo, "/*\n");
      strcpy (prefix, " *  ");
      break;
    case WRITE_MODE_ASSEMBLE:
      fprintf (fo, "*\n");
      strcpy (prefix, "* ");
      break;
    default:
      return 0;
  }

  fprintf (fo, "%sconversion table\n%sfrom: %s",
           prefix, prefix, lsrc [0]);
  for (i= 1; i < lsrc_cnt; i++)
    fprintf (fo, ", %s", lsrc[i]);
  fprintf (fo, "\n%s  to: %s", prefix, ldst [0]);
  for (i= 1; i < ldst_cnt; i++)
    fprintf (fo, ", %s", ldst[i]);

  fprintf (fo, "\n%sas generated on 19%02d-%02d-%02d/%02d:%02d:%02d\n%s\n",
           prefix,
           tm_s->tm_year, tm_s->tm_mon+1, tm_s->tm_mday,
           tm_s->tm_hour, tm_s->tm_min,   tm_s->tm_sec,
           prefix);

  switch (mode)
  {
    case WRITE_MODE_C_ARRAY:
    case WRITE_MODE_C:
    case WRITE_MODE_REXX:
    case WRITE_MODE_rexx:
    case WRITE_MODE_PERL:
      fprintf (fo, " */\n");
      break;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int main_cvt (char *fn, void *cd)
{
  struct CONVERTER *cnv;

  if ((cnv= (struct CONVERTER *) cd) == (struct CONVERTER *) 0) return -1;

  return cs_convert_file (fn, cnv->fno, cnv->table);
}
