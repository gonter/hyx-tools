/*
 *  FILE %lexicon/dictmod.c
 *
 *  general sequential lexicon processor for modification and filtering
 *  -  HELP
 *
 *  processors: are used to modify the contents of the lexicon
 *  filters: are used to extract certain information of the lexicon
 *
 *  installed processors:
 *  1. purge (don't process, only write sequentially)
 *  2. extract some frames
 *
 *  installed filters:
 *  (none sofar)
 *
 *  written:       1991 04 14
 *  latest update: 1996-02-17 13:51:56
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/parse.h>
#include <gg/sgml.h>
#include <gg/lookup.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/hytxt.h>
#ifdef MSDOS
#include <io.h>
#include <dos.h>
#include <conio.h>
#include <gg/fnames.h>
#else
#include <unistd.h>
#endif
#include "lexproc.h"

#define  STDHLP stdout
#define  ARG_C_max       24
static char *arg_v [ARG_C_max];
static int   arg_c = 0;

/* extern int errno; ... defined in <stdlib.h> */

/* ------------------------------------------------------------------------ */
static int verbose_mode = 0;

#ifdef MSDOS
#define FILENAME_SIZE 66
static char tag_definition [FILENAME_SIZE] = "c:/etc/lexicon.tag";
#else
#define FILENAME_SIZE 256
static char tag_definition [FILENAME_SIZE] = "/home/gonter/etc/lexicon.tags";
#endif

static int  setup_readin=0;
static char lexicon_setup  [FILENAME_SIZE] = "alexicon.stp";
static char lexicon_file   [FILENAME_SIZE] = "alexicon.hyx";
static char lexicon_temp   [FILENAME_SIZE] = "alexicon.hy$";
static char lexicon_back   [FILENAME_SIZE] = "alexicon.$hy";
static char index_file     [FILENAME_SIZE] = "alexicon.idx";
static char index_temp     [FILENAME_SIZE] = "alexicon.ix$";
static char index_back     [FILENAME_SIZE] = "alexicon.$ix";
static char main_lut_file  [FILENAME_SIZE] = "alexicon.lut";

static char line [256];

static long end_tags[1] = { (long) SGML_TAG_endframe } ;

/* processing done over the lexicon --------------------------------------- */
static int processing_mode=0;
#define FILTER_LEXICON 0        /* -> don't modify lexicon (filter) */
#define MODIFY_LEXICON 1        /* -> modify lexicon                */

static int read_mode=1;
#define NOREAD_LEXICON 0
#define READ_LEXICON 1

static int processor=0;
#define PROCESSOR_UNDEFINED 0
#define PROCESSOR_PURGE     1
#define PROCESSOR_BY_SIZE   2
#define PROCESSOR_NTH       3

static long extract_nth;

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: dictmod [options] {file name}\n",
  "  modify lexicon files\n",
  "\n",
  "OPTIONS:\n",
  "  -f<filename> ... List of Files\n",
  "  -t<filename> ... tag definition file\n",
  "  -s<filename> ... lexicon setup file\n",
  "  -v           ... Verbose Mode\n",
  "\n",
  "PROCESSING:\n",
  "  -p ... purge\n",
  "  -l ... extract the largest entry\n",
  "  -n<n> ... extract every n-th entry\n",
  "\n",
  "(@)Adictmod.c 1.19 #D$1995-01-20  9:30:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);
static int cdecl read_setup_file (char *fn);
static int modify_dictionary (struct HYX_PARSER_CLASS *hpc);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  struct HYX_PARSER_CLASS *hpc;

  if (argc <= 1
      || (hpc= hyx_new_parser_class ()) == (struct HYX_PARSER_CLASS *) 0
     ) goto HLP;

  for (i= 1; i < argc; i++)
    if (argv [i][0] == '-' ||  argv [i][0] == '/')
      switch (argv [i][1])
      {
           case 'f': case 'F':
             if (argv [i][2] == 0) break;
               if (arg_c+1 < ARG_C_max)
                 arg_v [arg_c++] = argv [i];
             break;
           case 's': case 'S':
             strcpy (lexicon_setup, &argv[i][2]);
             read_setup_file (lexicon_setup);
             setup_readin=1;
             break;
           case 't': case 'T':
             strcpy (tag_definition, &argv[i][2]);
             break;
           case 'p': case 'P':
             processor       = PROCESSOR_PURGE;
             processing_mode = MODIFY_LEXICON;
             read_mode       = READ_LEXICON;
             break;
           case 'l': case 'L':
             processor       = PROCESSOR_BY_SIZE;
             processing_mode = FILTER_LEXICON;
             read_mode       = NOREAD_LEXICON;
             break;
           case 'n': case 'N':
             processor       = PROCESSOR_NTH;
             processing_mode = FILTER_LEXICON;
             read_mode       = NOREAD_LEXICON;
             sscanf (&argv [i][2], "%ld", &extract_nth);
             break;

           case 'v': case 'V':
                     for (j=1; argv [i][j]; j++)
                        switch (argv [i][j])
                        {
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

  if (PROCESSOR_UNDEFINED)
    fprintf (stdout, "no processor defined!\n");
  else
  {
    if (!setup_readin) read_setup_file (lexicon_setup);
    hyx_read_tag_definition (hpc, tag_definition);
    modify_dictionary (hpc);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
static int read_setup_file (char *fn)
{
  FILE *fi;

  if (fn == (void *) 0 || *fn == 0) return 0;

  /* read lexicon setup file */
  if ((fi= fopen (fn, "rt")) == (FILE *) 0)
  {
    /********
    fprintf (stdout, "error opening setup file \'%s\'\n", fn);
    fprintf (stdout, "... using default values\n");
    ********/
    return 0;
  }
  for (;;)
  {
    fscanf (fi, "%s", line);
    if (feof (fi)) break;
    if (line [0] == '#')
    {
READ_NEXT:
      trash_until_eol (fi);
      continue;
    }
    if (strncmp (line, "lex", 3)==0)
    {
      fscanf (fi, "%s", lexicon_file);
    } else
    if (strncmp (line, "tlex", 4)==0)
    {
      fscanf (fi, "%s", lexicon_temp);
    } else
    if (strncmp (line, "blex", 4)==0)
    {
      fscanf (fi, "%s", lexicon_back);
    } else
    if (strncmp (line, "idx", 3)==0)
    {
      fscanf (fi, "%s", index_file);
    } else
    if (strncmp (line, "tidx", 4)==0)
    {
      fscanf (fi, "%s", index_temp);
    } else
    if (strncmp (line, "bidx", 4)==0)
    {
      fscanf (fi, "%s", index_back);
    } else
    if (strncmp (line, "main", 4)==0)
    {
      fscanf (fi, "%s", main_lut_file);
    } else
    if (strncmp (line, "tag", 3)==0)
    {
      fscanf (fi, "%s", tag_definition);
    } else goto READ_NEXT;
  }
  fclose (fi);
  return 0;
}

/* ------------------------------------------------------------------------ */
static int modify_dictionary (struct HYX_PARSER_CLASS *hpc)
{
  FILE *fi_hyx;                 /* lexicon file input                       */
  FILE *fo_hyx= (FILE *) 0;     /* lexicon file output                      */
  FILE *fi_idx;                 /* lndex file input                         */
  FILE *fo_idx= (FILE *) 0;     /* index file output                        */
  struct stat st;               /* index file status and size               */
  struct LEXICON_INDEX idx_in;  /* index record read from fi_idx            */
  struct LEXICON_INDEX idx_out; /* index record to write to fo_idx          */
  struct TEXT_ELEMENT *tx_entry;        /* raw form of lexicon entry                */
  long next_index;              /* next valid index possible                */
  long current_index;           /* currently processed index number         */
  long fo_hyx_position= 0L;     /* current write address in lexicon file    */
  long chars_read;              /* characters read from the lexicon file    */
  int flag_write_frame_tags= 0; /* 1 -> write frame information too...      */
  int rc;

  if (stat (index_file, &st) && errno == ENOENT)
  {
    fprintf (stdout, "error: index file is empty; nothing to do...\n");
    return -1;
  }
  next_index = st.st_size / sizeof (struct LEXICON_INDEX);

  /* opening files ... */
  if ((fi_idx= fopen (index_file, "rb")) == (FILE *) 0)
  {
    fprintf (stdout, "error opening index file for input!\n");
    return -1;
  }

  if ((fi_hyx= fopen (lexicon_file, "rb")) == (FILE *) 0)
  {
    fprintf (stdout, "error opening lexicon file for input!\n");
    fclose (fi_idx);
    return -1;
  }

  if (processing_mode == MODIFY_LEXICON)
  {
    if ((fo_idx= fopen (index_temp, "wb")) == (FILE *) 0)
    {
      fprintf (stdout, "error opening temporary index file for output!\n");
      fclose (fi_idx);
      fclose (fi_hyx);
      return -1;
    }

    if ((fo_hyx= fopen (lexicon_temp, "wb")) == (FILE *) 0)
    {
      fprintf (stdout, "error opening temporary lexicon file for output!\n");
      fclose (fi_idx);
      fclose (fi_hyx);
      fclose (fo_idx);
      return -1;
    }

    /* preparing files: dummy index 0 and lexicon signature */
    fprintf (fo_hyx, "<ned.sgml enc=\"LEX\">\n");
    hyx_write_stamp (fo_hyx, "pgm=dictmod");
    fputc ('\n', fo_hyx);
    fo_hyx_position= ftell (fo_hyx);
  }

  switch (processor)
  {
    case PROCESSOR_BY_SIZE:
      init_by_size (0, 0); /* #### */
      break;
  }

  /* process all records */
  for (current_index = 0L;
       current_index < next_index;
       current_index++)
  {
    idx_in.LEXI_begin          = dpp_fread_long (fi_idx, 4);
    idx_in.LEXI_end            = dpp_fread_long (fi_idx, 4);
    idx_in.LEXI_cluster_number = dpp_fread_long (fi_idx, 4);

    if (idx_in.LEXI_begin == -1L || idx_in.LEXI_begin == 0L)
    { /* dummy, empty, deleted or invalid index */
      fprintf (stdout,
               "[0x%08lX] *dummy* begin=0x%08lX end=0x%08lX cluster=0x%lX\n",
                current_index, idx_in.LEXI_begin, idx_in.LEXI_end,
                idx_in.LEXI_cluster_number);
      if (processing_mode == MODIFY_LEXICON)
      {
        dpp_fwrite_long (fo_idx, idx_in.LEXI_begin,          4);
        dpp_fwrite_long (fo_idx, idx_in.LEXI_end,            4);
        dpp_fwrite_long (fo_idx, idx_in.LEXI_cluster_number, 4);
      }
      continue;
    }

    if (read_mode == READ_LEXICON)
    {
      fseek (fi_hyx, idx_in.LEXI_begin, 0);
      rc= hyx_parse1_file (hpc, fi_hyx, &tx_entry, end_tags, 1,
                             0x7FFFFFFFL, &chars_read);
      if (rc != 0 || chars_read == 0L)
      {
        fprintf (stdout,
          "[0x%08lX] *empty entry* rc=%d chars_read=%ld\n",
          current_index, rc, chars_read);
        fprintf (stdout,
          "[0x%08lX] *empty entry* begin=0x%08lX end=0x%08lX cluster=%lX\n",
          current_index,
          idx_in.LEXI_begin, idx_in.LEXI_end, idx_in.LEXI_cluster_number);

        if (processing_mode == MODIFY_LEXICON)
        {
          printf ("             ... reset to -1L\n");
          dpp_fwrite_long (fo_idx, -1L, 4);
          dpp_fwrite_long (fo_idx, -1L, 4);
          dpp_fwrite_long (fo_idx, -1L, 4);
        }
        continue;
      }
    }

    switch (processor)
    {
#ifdef __COMMENT__
      /* this shows how a processor function should be called   */
      /* flags are to be set if necesseray ...                  */
      case PROCESSOR_XXXX:
        process_XXXX (&tx_entry, additional parameters, etc...);
        flag_write_frame_tags = 0 .. 1;
        break;
#endif
      case PROCESSOR_PURGE:
        /* do nothing ... */
        flag_write_frame_tags= 0;
        break;
      case PROCESSOR_BY_SIZE:
        process_by_size (&idx_in);
        break;
      case PROCESSOR_NTH:
        if (((current_index+1) % extract_nth) == 0L)
        {
          fseek (fi_hyx, idx_in.LEXI_begin, 0);
          ftransfer (fi_hyx, stdout, idx_in.LEXI_end-idx_in.LEXI_begin+1L);
          printf ("\n");
        }
        break;
    }

    if (processing_mode == MODIFY_LEXICON)
    {
      /* write entry */
      idx_out.LEXI_begin = ftell (fo_hyx);
      if (flag_write_frame_tags) fprintf (fo_hyx,"<:LX%08lX>",current_index);
      write_lexicon_text (fo_hyx, tx_entry, 1);
      if (flag_write_frame_tags) fprintf (fo_hyx, "<;>");
      idx_out.LEXI_end = ftell (fo_hyx) - 1L;
      idx_out.LEXI_cluster_number = idx_in.LEXI_cluster_number;
      fputc ('\n', fo_hyx); /* just for a bit readability ... */

      /* write index */
      dpp_fwrite_long (fo_idx, idx_out.LEXI_begin,          4);
      dpp_fwrite_long (fo_idx, idx_out.LEXI_end,            4);
      dpp_fwrite_long (fo_idx, idx_out.LEXI_cluster_number, 4);
    }

    hyx_frtx_elem_list (tx_entry);
  }

  switch (processor)
  {
    case PROCESSOR_BY_SIZE:
      finish_by_size (fi_hyx, stdout);
      break;
  }

  fclose (fi_idx);
  fclose (fi_hyx);
  if (processing_mode == MODIFY_LEXICON)
  {
    fclose (fo_idx);
    fclose (fo_hyx);
    unlink (lexicon_back);
    rename (lexicon_file, lexicon_back);
    rename (lexicon_temp, lexicon_file);
    unlink (index_back);
    rename (index_file, index_back);
    rename (index_temp, index_file);
  }

  return 0;
}
