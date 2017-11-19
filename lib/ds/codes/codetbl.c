/*
 *  FILE %dpp/codes/codetbl.c
 *
 *  write code translation tables or so
 *
 *  - HELP
 *  - prototypes
 *  - see also codeconv.c
 *
 *  NOTE: this program can not be portet to CMS,
 *        because explicit references to &amp; &lt; and &gt; exist.
 *
 *  written:       1993-06-10
 *  latest update: 1995-12-10
 *  $Id: codetbl.c,v 1.2 2011/05/31 16:43:41 gonter Exp $
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
#include <gg/codes.h>
#include <gg/sbr.h>
#include <gg/dpp.h>

#define MODE2

#define STDHLP stdout
#ifdef MSDOS
#define ARG_C_max       24
#else
#define ARG_C_max      240
#endif
static char *arg_v [ARG_C_max];
static int arg_c= 0;

/* Quick Hack: ------------------------------------------------------------ */
#ifdef MSDOS
#define SUBDIRS                         /* recursive walk through the       */
                                        /* filesystem is possible           */
#define BETTER_FILENAME_MATCH           /* own match function               */
                                        /* otherwise DOS match function     */
#endif

/* ------------------------------------------------------------------------ */
static char filenm [66];

static long init_value= 0L;
static long converter_table [256];
static long entity_table [256];
static char *table_name= (char *) 0;

static int verbose_mode= 0;

#define MAX_LIST 40
static char *src [MAX_LIST] = { "pc",        "ascii" };
static char *dst [MAX_LIST] = { "iso8859_1", "ascii" };
static char *dst_ent []= { "entity" };
static int src_cnt= 2;
static int dst_cnt= 2;
static int dst_ent_cnt= 1;
static int src_predef= 1;       /* 1 -> table is predefined                 */
static int dst_predef= 1;

#define MAX_ALL_FIELDS 100
static char *all_fields [MAX_ALL_FIELDS] =
{
  "def", "val"                  /* we also need definitions!                */
} ;

static int all_fields_cnt= 2;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: codetbl [options] {file name}\n",
  "  write code translation tables or so\n",
  "OPTIONS:\n",
  "  -f<fnm> ... list of files\n",
  "  -t<fnm> ... name of the file containing the code tables\n",
  "  -s<id> ... source code [Def: pc, ascii]\n",
  "  -d<id> ... destination code [Def: mac, ascii]\n",
  "  -o<fnm> ... outfile\n",
  "  -w<m><fnm> ... write table to file\n",
  "    m=b ... binary\n",
/*"    m=p ... portable binary\n", */
  "    m=c ... C\n",
  "    m=r ... REXX expression\n",
  "    m=R ... REXX translate expression\n",
  "    m=A ... IBM/370 ASSEMBLE\n",
  "  -i<val> ... initial value for the converter table\n",
  "NOTES:\n",
  "  Several -s and/or -d options might be present.\n",
  "\n",
  "(@)Acodetbl.c 1.03 #D$1995-12-10  0:16:40\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);

/* ------------------------------------------------------------------------ */
int main (int  argc, char *argv [])
{
  FILE *fi2;
  FILE *ft;
  int i, j;
  char *outfile= (char *) 0;
  int rc;
#ifdef MODE1
  long table_idx;
  long entry_size;
#endif
  struct CS_record *records;
#define WRITE_MODE_undef        0
#define WRITE_MODE_C            1
#define WRITE_MODE_binary       2
#define WRITE_MODE_rexx         4
#define WRITE_MODE_REXX         5
#define WRITE_MODE_ASSEMBLE     6
  int write_mode= WRITE_MODE_C;
  char *write_to_file= "trans.bin";

  for (i= 1; i < argc; i++)
    if (argv [i][0] == '-')
      switch (argv [i][1])
      {
        case 'f': case 'F':
          if (argv [i][2] == 0) break;
          if (arg_c+1 < ARG_C_max) arg_v [arg_c++] = argv [i];
          break;

        case 'd': case 'D':
          if (argv [i][2] == 0) break;
          if (dst_predef)
          {
            dst_predef= 0;
            dst_cnt= 0;
          }
          dst [dst_cnt++]= &argv[i][2];
          break;

        case 'i': case 'I':
          init_value= get_parameter_value (&argv[i][2]);
          break;

        case 'o': case 'O':
          outfile= &argv [i][2];
          break;

        case 's': case 'S':
          if (argv [i][2] == 0) break;
          if (src_predef)
          {
            src_predef= 0;
            src_cnt= 0;
          }
          src [src_cnt++]= &argv[i][2];
          break;

        case 't': case 'T':
          if (argv[i][2] == 0) break;
          table_name= &argv [i][2];
          break;

        case 'w': case 'W':
          switch (argv [i][2])
          {
            case 'b': case 'B':
              write_mode= WRITE_MODE_binary;
              break;
            case 'c': case 'C':
              write_mode= WRITE_MODE_C;
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
            default:
              goto HLP;
          }
          write_to_file= &argv[i][3];
          if (*write_to_file == 0) goto HLP;
          break;

        case 'v': case 'V':
          verbose_mode++;
          break;

HLP:
#include <gg/help.inc>
      }
    else if (arg_c+1 < ARG_C_max) arg_v [arg_c++] = argv [i];

  if (arg_c)
  {
    for (i= 0; i < arg_c; i++)
      if (arg_v [i][0] == '-')
      {
        if ((fi2= fopen (& arg_v [i][2], "rt")) == (FILE *) 0)
        {
          fprintf (stderr, "File %s not found!\n", &arg_v [i][2]);
          break;
        }
        for (;;)
        {
          fscanf (fi2, "%s", filenm);
          if (feof (fi2)) break;
        }
        fclose (fi2);
      }
  }

  /* setup converter tables */
  if (table_name == (char *) 0)
    table_name= set_etc_filename ((char *) 0, CSF_TABLE);

  /* initialize table */
  for (i= 0; i<256; i++)
  {
    converter_table[i]= init_value;
    entity_table[i]= 0L;
  }

  for (i=0; i<src_cnt; i++) all_fields [all_fields_cnt++] = src [i];
  for (i=0; i<dst_cnt; i++) all_fields [all_fields_cnt++] = dst [i];
  for (i=0; i<dst_ent_cnt; i++) all_fields [all_fields_cnt++] = dst_ent [i];
  records= cs_parse_code_table (table_name, all_fields, all_fields_cnt,
                                1, 25);
  if (records == (struct CS_record *) 0)
  {
    fprintf (stderr, "error parsing table %s!\n", table_name);
    goto HLP;
  }

  set_common_base (0);
  rc= cs_records2table (records, src, src_cnt, dst, dst_cnt,
                        CSft_number, converter_table);
  rc= cs_records2table (records, src, src_cnt, dst_ent, dst_ent_cnt,
                        CSft_string, entity_table);

  if (rc == -1)
  {
    fprintf (stderr,
      "couldn\'t setup converter table from information in %s",
      table_name);

    fprintf (stderr, "for conversion (%s", src[0]);
    for (i=1; i<src_cnt; i++) fprintf (stderr, ",%s", src[i]);
    fprintf (stderr, ") -> (%s", dst[0]);
    for (i=1; i<dst_cnt; i++) fprintf (stderr, ",%s", dst[i]);
    fprintf (stderr, ")\n");

    goto HLP;
  }

  ft= fopen (write_to_file, "wb");
  if (ft == (FILE *) 0)
  {
    fprintf (stderr, "error: couldnt write to: %s\n", write_to_file);
    return 1;
  }

#ifdef MODE1
  /* generate transfer table */
  table_idx= 0L;

  /* part 1: write index into string table */
  for (i= 0; i<256; i++)
  {
    entry_size= 0L;
    if (converter_table [i] != init_value)
    {
      entry_size= 2L;
    }
    else
    {
      if (entity_table [i] != 0L)
        entry_size= 1 + strlen ((char *) entity_table[i]);
    }
    if (entry_size > 0L)
    {
      dpp_fwrite_long (ft, table_idx, 2);
      table_idx += entry_size;
    }
    else
      dpp_fwrite_long (ft, -1L, 2);
  }

  /* part 2: write strings */
  for (i= 0; i<256; i++)
  {
    if (converter_table [i] != init_value)
    {
      fputc ((char) converter_table [i], ft);
      fputc (0, ft);
    }
    else
    {
      if (entity_table [i] != 0L)
      {
        fputs ((char *) entity_table[i], ft);
        fputc (0, ft);
      }
    }
  }
#endif

#ifdef MODE2
  for (i= 0; i < 256; i++)
  {
    if (converter_table [i] != init_value)
    {
      switch ((int) converter_table [i])
      { /* ASCII ONLY !!!, not portable to EBCDIC */
        case 0x26: /* &; ampersand      */
        case 0x3C: /* <; less than      */
        case 0x3E: /* >; greater than   */
          if ((char *) entity_table[i] != (char *) 0)
          {
            fprintf (stdout, "0x%02X (0x%02X) -> &%s;\n",
              i,
              (int) converter_table [i],
              (char *) entity_table[i]);
            fprintf (ft, "&%s;", (char *) entity_table[i]);
          }
          else
          {
            fprintf (stderr, "can\'t convert entity!\n");
            fprintf (stderr,
              "0x%02X (0x%02X) -> &%s;\n",
              i,
              (int) converter_table [i],
              (char *) entity_table[i]);
            fprintf (ft, "&0x%02lX;", converter_table[i]);
          }
          break;
        default:
          fputc ((char) converter_table [i], ft);
          break;
      }
    }
    else
    {
      if (entity_table [i] != 0L)
      { /* ASCII ONLY !!!, not portable to EBCDIC */
        fprintf (ft, "&%s;", (char *) entity_table[i]);
      }
    }
    fputc (0, ft);
  }
#endif

  fclose (ft);

  if (verbose_mode > 0)
    cs_print_tlate_table (stdout, write_to_file, "tlate");

  return 0;
}
