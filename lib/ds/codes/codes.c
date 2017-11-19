/*
 *  FILE %dpp/codes/codes.c
 *
 *  pre-process code table for various purposes
 *  - HELP
 *  - prototypes
 *  - filenames
 *
 *  written:       1992 02 19
 *  latest update: 1995-12-09
 *  $Id: codes.c,v 1.2 2011/05/31 16:43:41 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <conio.h>
#endif
#include <gg/dpp.h>
#include <gg/filename.h>
#include <gg/codes.h>

#define STDHLP stderr

/* ------------------------------------------------------------------------ */
static int verbose_mode = 0;
static int include_all = 0;

/* ------------------------------------------------------------------------ */
#define N_PC_FIELDS     3
#define N_MAC_FIELDS    1
#define N_FIELDS       11
#define POS_ISO_FIELD   7

/* ------------------------------------------------------------------------ */
static char *FIELDS [N_FIELDS] =
{
/*  0 */  "pc",
/*  1 */  "pc437",
/*  2 */  "ascii",
/*  3 */  "pc850",
/*  4 */  "mac",

/*  5 */  "ebcdic",
/*  6 */  "iso8859",
/*  7 */  "iso8859_1",
/*  8 */  "iso10646",
/*  9 */  "tex",
/* 10 */  "latex"
} ;

/* ------------------------------------------------------------------------ */
static long TAGS [N_FIELDS] =
{
  CSfid_pc,
  CSfid_pc437,
  CSfid_ascii,
  CSfid_pc850,
  CSfid_mac,

  CSfid_ebcdic,
  CSfid_iso8859,
  CSfid_iso8859_1,
  CSfid_iso10646,
  CSfid_tex,
  CSfid_latex
} ;

/* ------------------------------------------------------------------------ */
#define N_MATCH_FIELDS 256
static char *match_fields[N_MATCH_FIELDS] = { "iso8859*" };
static int cnt_match_fields= 1;
static int filter_mode= 1;
static int max_warnings= 10;

/* filenames: ------------------------------------------------------------- */
static char *PC_LUT_FILE=       "entity.lut";
static char *DATA_FILE=         "entity.dat";
static char *PC_INDEX_FILE=     "entpc437.idx";
static char *PC_STRING_FILE=    "entpc437.str";
static char *MAC_INDEX_FILE=    "entmac.idx";
static char *MAC_STRING_FILE=   "entmac.str";
static char *ISO_INDEX_FILE=    "ent88591.idx";
static char *ISO_STRING_FILE=   "ent88591.str";

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: codes [options] {file name}\n",
  "  process code table /etc/codes/table in various ways...\n",
  "OPTIONS:\n",
  "  -a ... write all entities to LUT and DATA file\n",
  "  -d<fnm> ... data file to write to\n",
  "  -i<fnm> ... index file for pc code page 437\n",
  "  -l<fnm> ... lut file name to write to\n",
  "  -s<fnm> ... string file name\n",
  "  -m<n> ... mode; [DEF: 0]\n",
  "    0  ... diagnostic\n",
  "    1  ... compact LUT\n",
  "    2  ... LUT and entity DATA\n",
  "    3  ... PC index file\n",
  "    4  ... MAC index file\n",
  "    5  ... ISO 8859-1 index file\n",
  "    6  ... ISO 8859-1 lut file\n",
  "    98 ... -> 0, all data\n",
  "    99 ... -> 2, 3, 4\n"
  "  -v ... verbose mode\n",
  "\n",
  "(@)Acodes.c 1.05 #D$1996-02-24 11:01:43\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  int mode= 0;
  struct CS_record *records;
  char *table_name= (char *) 0;

  for (i= 1; i < argc; i++)
    if (argv [i][0] == '-')
      switch (argv [i][1])
      {
        case 'a': case 'A':
          include_all= 1;
          break;
        case 'd': case 'D':
          DATA_FILE= &argv[i][2];
          break;
        case 'i': case 'I':
          PC_INDEX_FILE= &argv[i][2];
          MAC_INDEX_FILE= &argv[i][2];
          ISO_INDEX_FILE= &argv[i][2];
          break;
        case 'l': case 'L':
          PC_LUT_FILE= &argv[i][2];
          break;
        case 'm': case 'M':
          mode= (int) get_parameter_value (&argv[i][2]);
          break;
        case 's': case 'S':
          PC_STRING_FILE  = &argv [i][2];
          MAC_STRING_FILE = &argv [i][2];
          ISO_STRING_FILE = &argv [i][2];
          break;
        case 'v': case 'V':
          for (j= 1; argv [i][j]; j++)
            switch (argv [i][j])
            {
              case 'v': case 'V':
                verbose_mode= 1;
                break;
            }
          break;

HLP:
#include <gg/help.inc>
      }
    else table_name= argv [i];

  if (table_name == (char *) 0)
    table_name= set_etc_filename ((char *) 0, CSF_TABLE);

  if (mode != 0)
  { /* this should be optimized sometime in the future,         */
    /* but for now it's more important to have the program      */
    /* operational for the purpose of creating specialized      */
    /* tables, indexes, luts etc....                            */
    match_fields [0]= "*";
    cnt_match_fields= 1;
    filter_mode= 0;
  }

  records= cs_parse_code_table (table_name, match_fields,
             cnt_match_fields, filter_mode, max_warnings);

  if (records == (struct CS_record *) 0)
  {
    fprintf (stderr, "error parsing table %s!\n", table_name);
    goto HLP;
  }

  cs_print_statistics (stderr);

  switch (mode)
  {
    case 0:
      cs_print_records (stdout, records);
      break;
    case 1: /* compact lut */
    case 2: /* lut and data file */
      cs_records2ytree (records, FIELDS, TAGS, N_PC_FIELDS,
        PC_LUT_FILE, DATA_FILE,
        verbose_mode, (mode == 1) /* -> compact */, include_all);
      break;
    case 3:
      cs_records2index (records, FIELDS, N_PC_FIELDS,
        PC_INDEX_FILE, PC_STRING_FILE, verbose_mode);
      break;
    case 4:
      cs_records2index (records, &FIELDS [N_PC_FIELDS], N_MAC_FIELDS,
        MAC_INDEX_FILE, MAC_STRING_FILE, verbose_mode);
      break;
    case 5:
      cs_records2index (records, &FIELDS [N_PC_FIELDS], N_FIELDS,
        ISO_INDEX_FILE, ISO_STRING_FILE, verbose_mode);
      break;
    case 6: /* lut and data file */
      cs_records2ytree (records, FIELDS + POS_ISO_FIELD, TAGS, 1,
        PC_LUT_FILE, DATA_FILE,
        verbose_mode, (mode == 6) /* -> compact */, include_all);
      break;
    case 98:
      cs_print_frames (stdout, records);
      break;
    case 99:
      cs_records2ytree (records, FIELDS, TAGS, N_FIELDS,
        PC_LUT_FILE, DATA_FILE,
        verbose_mode, 0, include_all);
      cs_records2index (records, FIELDS, N_PC_FIELDS,
        PC_INDEX_FILE, PC_STRING_FILE, verbose_mode);
      cs_records2index (records, &FIELDS [N_PC_FIELDS], N_MAC_FIELDS,
        MAC_INDEX_FILE, MAC_STRING_FILE, verbose_mode);
      cs_records2index (records, &FIELDS [POS_ISO_FIELD], 1,
        ISO_INDEX_FILE, ISO_STRING_FILE, verbose_mode);
      break;
  }

  return 0;
}
