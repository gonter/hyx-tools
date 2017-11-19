/*
 *  FILE %usr/utl/translit.c
 *
 *  Zeichensatzumwandlung und Textdecodierung (Umlaute usw.)
 *  -  prototypes
 *  -  VERSION
 *  -  HELP
 *
 *  written:       1987 12 01
 *                 1990 01 25: Wildcards
 *                 1991 02 12: Revision
 *                 1992 08 30: revision
 *  latest update: 1999-04-25 16:41:22
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/dpp.h>
#include <gg/filename.h>
#include <gg/convent.h>
#include <gg/codes.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/sbr.h>

#ifdef MSDOS
#include <conio.h>
#include <io.h>
#define EXTRA_BUFFERS
#define FNM_LENGTH 66
#else
#include <unistd.h>
#define FNM_LENGTH  4096
#endif

#define REAL_AUTHOR
#define STDHLP stderr
#define TMP "tmptmp.tmp"

static char TEMP   [FNM_LENGTH];
static char filenm [FNM_LENGTH];

#ifdef EXTRA_BUFFERS
#define BUF_SIZE 0x7000
static char *buf1= (char *) 0, *buf2= (char *) 0;
#endif

/* ------------------------------------------------------------------------ */
#define mSTR          8196      /* Groesse des Stringpuffers                */

#define MAP_copy         0      /* -> Zeichen kopieren                      */
#define MAP_delete       1      /* -> Zeichen loeschen                      */
#define MAP_translate    2      /* -> Zeichen umwandeln                     */
#define MAP_string       3      /* -> Zeichen durch String ersetzen         */
#define MAP_rle          4      /* Zaehler */
#define MAP_rle2         5      /* Zaehler */

/* ------------------------------------------------------------------------ */
static char maptable     [ 256];
static char transtable   [ 256];
static char stringlng    [ 256];
static char stringpuffer [mSTR];
static int  stringptr= 0;
static int  escape_char= ':';    /* Decodierung */
static int  output_file= 0;      /* 1 -> Output File umbenennen */
static char *output;             /* Name des Output Files */

static int kroemer_code= 0x07;

/* ------------------------------------------------------------------------ */
static int verbose_mode= 0;
static int mode= 0;

/* SGML entity transaltion level */
static int entity_level= CONVENT_amp|CONVENT_lt_gt;
static char *code_set_files= CSF_PC_STRINGS;
static struct CS_ET8 *et8= (struct CS_ET8 *) 0;

/* ------------------------------------------------------------------------ */
static char VERSION []= "(@)Atranslit.c 1.24 #D$1997-10-24 13:57:47\n";

static char *HELP [] =
{
  "USAGE: translit [-Opt] <Filename>\n",
  "OPTIONS:\n",
  "  -f<fnm>   ... list of files\n",
  "  -o<fnm>   ... output to file\n",
  "  -d<n>     ... default table <n> (see below)\n",
  "  -k<x>     ... kroemer code [DEF: 0x08] (implies -d4)\n",
  "  -v        ... verbose mode\n",
  "  -t[<fnm>] ... specify translation table (DEF: translit.tbl)\n",
  "  -e[<c>]   ... escape: <c> as escape character for decoding\n",
#ifdef MSDOS
  "  -r        ... recursion through subdirectories\n",
#endif
  "  -s[<x>*]  ... apply SGML entity conversion; [DEF: &<>]\n",
  "    &       ... convert &\n",
  "    !       ... convert < and >\n",
  "    8       ... convert chars >= 128 according to the codes set (flag -c)\n",
  "  -c<set>   ... setup codes set\n",
  "    i       ... ISO 8859-1\n",
  "    p       ... PC Code Page 437 [DEFAULT]\n",
  "\n",
  "Commands in TRANSLIT.TBL:\n",
  "  @translate ... translate code-pairs\n",
  "  @delete    ... codes to delete\n",
  "  @string    ... translate code to codes sequences\n",
  "  @default0  ... default table 0: don't change anything [Default-Default :-) ]\n",
  "  @default1  ... default table 1\n",
  "  @default2  ... default table 2: mask bit 7 + delete control chars\n",
  "  @default3  ... default table 3: mask bit 7\n",
  "  @end       ... end of translit table\n",
  "  -d4        ... kroemer\n",
  "  #          ... comment\n",
  "\n",
  VERSION,
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
int  cdecl main (int argc, char *argv []);
int  cdecl translit_or_escape (char *fn, void *cd);
int  cdecl translit (char *fnm);
int  cdecl escape (char *fnm);
int  cdecl entities (char *fnm);
int  cdecl read_table (char *fnm);
int  cdecl get_keyval (char *s, int *i);
void cdecl default0 (void);
void cdecl default1 (void);
void cdecl default2 (void);
void cdecl default3 (void);
void cdecl kroemer (void);
void cdecl default_escape (void);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  char *arg;
  struct WCRD *wcrd;
  struct ARRAY_CONTROL *arguments;

  if ((wcrd= wcrd2_new ()) == (struct WCRD *) 0
      || (arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) return 1;

  wcrd2_set_processor (wcrd, WCRD_set_file_processor,
                       translit_or_escape, (void *) 0);

  default0 ();

  if (strstr (argv [0], "iso2html") == (char *) 0)
  {
    mode= 3;
    output= "-";
    output_file= 1;
    code_set_files= CSF_8859_1_STRINGS;
    entity_level |= CONVENT_8bit;
  }

#ifdef JUNK
  if (strstr (argv [0], "translit") == (char *) 0)
  {
    read_table (argv [0]);
    mode= 1;
  }
#endif

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
      switch (arg [1])
      {
        case 'c': case 'C':
          switch (arg [2])
          {
            case 'i': case 'I':
              code_set_files= CSF_8859_1_STRINGS;
              break;
            default:
              code_set_files= CSF_PC_STRINGS;
              break;
          }
          break;

        case 'd': case 'D':
          switch (arg [2])
          {
            case '0': default0 (); break;
            case '1': default1 (); break;
            case '2': default2 (); break;
            case '3': default3 (); break;
            case '4': kroemer (); break;
          }
          mode= 1;
          break;

        case 'e': case 'E':
          mode= 2;
          if (arg [2]) escape_char = arg [2];
          break;

        case 'f': case 'F':
          if (arg [2] == 0) break;
          array_push (arguments, (void *) arg);
          break;

        case 'k': case 'K':
          kroemer_code= (int) get_parameter_value (arg +2);
          kroemer ();
          break;

        case 's': case 'S':
          mode= 3;
          if (!arg [2]) break;
          entity_level= 0;
          for (j= 2; arg [j]; j++)
          {
            switch (arg [j])
            {
              case '&': entity_level |= CONVENT_amp;   break;
              case '!': entity_level |= CONVENT_lt_gt; break;
              case '8': entity_level |= CONVENT_8bit;  break;
            }
          }
          break;

        case 'o': case 'O':
          output_file= 0;
          if (arg [2] == 0) break;
          output= arg+2;
          output_file= 1;
          break;

        case 't': case 'T': /* Translation Table */
          if (arg [2] == 0) arg= argv [++i];
          read_table (arg+2);
          mode= 1;
          break;

        case 'v': case 'V':
        case 'r': case 'R':
          for (j= 1; arg [j]; j++)
            switch (arg [j])
            {
              case 'r': case 'R':
                wcrd2_set_subdirs (wcrd, 1);
                break;
              case 'v': case 'V':
                verbose_mode++;
                break;
            }
          break;

#include <gg/help.inc>
      }
      else array_push (arguments, (void *) arg);
  }

#ifdef EXTRA_BUFFERS
  buf1= malloc (BUF_SIZE);
  buf2= malloc (BUF_SIZE);
#endif

  fprintf (stderr, VERSION);

  wcrd2_arguments (wcrd, arguments);

  cs_et8_destroy_table (et8);  /* JFF */

  return 0;
}

/* ------------------------------------------------------------------------ */
int translit_or_escape (char *fn, void *cd)
{
  int rv= 0;

#ifdef MSDOS
  cd;
#endif

  if (fn [1] == ':')
       sprintf (TEMP, "%c:%s", fn [0], TMP);
  else strcpy  (TEMP, TMP);

  switch (mode)
  {
    case  1: rv= translit (fn); break;
    case  2: rv= escape   (fn); break;
    case  3: rv= entities (fn); break;
    default: fprintf (stderr, "Huh?? What shall I do with %s?\n", fn); break;
  }

  return rv;
}

/* ------------------------------------------------------------------------ */
int translit (char *fnm)
{
  int i;
  int ch= 0;
  long cnt1, cnt2, cnt3;
  FILE *fi, *fo;
  int rle_counter= 0;
  int to_read= 1;

  if ((fi= fopen (fnm, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not opened!\n", fnm);
    return -1;
  }

  if (output_file && strcmp (output, "-") == 0)
  {
    fo= stdout;
  }
  else
  {
    if ((fo= fopen ((output_file) ? output : TEMP, "wb")) == (FILE *) 0)
    {
      fprintf (stderr, "Output file %s not opened!\n",
               (output_file) ? output : TEMP);
    }
  }
  fprintf (stderr, "%s -> %s\n", fnm, (output_file) ? output : TEMP);

#ifdef EXTRA_BUFFERS
  setvbuf (fi, buf1, _IOFBF, BUF_SIZE);
  setvbuf (fo, buf2, _IOFBF, BUF_SIZE);
  fprintf (stderr, "setvbuf: %d bytes each\n", BUF_SIZE);
#endif

  cnt1= cnt2= cnt3= (long) 0;
  for (;;)
  {
    if (to_read)
    {
      ch= fgetc (fi) & 0x00FF;
      if (feof (fi)) break;
      ch &= 0x00FF;
    }
    else
    {
      if (--rle_counter == 0) to_read= 1;
    }
    if (rle_counter > 0) to_read= 0;

    cnt1++;
    if (verbose_mode > 0 && (cnt1%1000) == 0)
      fprintf (stderr, "%ld\r", cnt1);

    switch (maptable [ch])
    {
      case MAP_copy:
        fputc (ch, fo);
        cnt3++;
        break;
      case MAP_translate:
        fputc (transtable [ch], fo);
        cnt3++;
      case MAP_delete:
        break;
      case MAP_string:
        for (i= 0; i < stringlng [ch]; i++)
        {
          fputc (stringpuffer [transtable [ch] + i], fo);
          cnt3++;
        }
        break;

      case MAP_rle:
        rle_counter= ch-1;
        to_read= 1;
        break;
      case MAP_rle2:
        ch= fgetc (fi) & 0x00FF;
        if (feof (fi)) break;
        ch &= 0x00FF;
        rle_counter= transtable [ch];
        to_read= 1;
        break;
      default:
        break;
    }
  }
  fclose  (fi);
  if (!(output_file && strcmp (output, "-") == 0)) fclose  (fo);
  if (verbose_mode > 0) fprintf (stderr, "%ld\r", cnt1);

  if (output_file)
  {
    output_file = 0;
    fprintf (stderr, "File %s -> %s Translit: %8ld Char -> %8ld Char\n",
             fnm, output, cnt1, cnt3);
  }
  else
  {
    unlink  (fnm);
    rename  (TEMP, fnm);
    fprintf (stderr, "File %s Translit: %8ld Char -> %8ld Char\n",
             fnm, cnt1, cnt3);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int escape (char *fnm)
{
  int ch;
  int esc_mode= 0;
  int code_value= 0;
  long cnt1, cnt2, cnt3;
  FILE *fi, *fo;

  if ((fi= fopen (fnm, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not opened!\n", fnm);
    return -1;
  }

  if ((fo= fopen ((output_file) ? output : TEMP, "wb")) == (FILE *) 0)
  {
    fprintf (stderr, "Output file %s not opened!\n",
             (output_file) ? output : TEMP);
  }

  cnt1= cnt2= cnt3= (long) 0;
  for (;;)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    ch &= 0x00FF;
    cnt1++;

    switch (esc_mode)
    {
      case  0:
        if (ch == escape_char) esc_mode = 1;
        else
        {
          fputc (ch, fo);
          cnt3++;
        }
        break;
      case  1:
        esc_mode = 0;
        switch (ch)
        {
          /* x45 */ case 'E': ch = 0x1B; break;
          /* x4C */ case 'L': ch = 0x0C; break;
          /* x5A */ case 'Z': ch = 0x1A; break;
          /* x73 */ case 's': ch = 0xE1; break;
          /* x61 */ case 'a': ch = 0x84; break;
          /* x41 */ case 'A': ch = 0x8E; break;
          /* x6F */ case 'o': ch = 0x94; break;
          /* x4F */ case 'O': ch = 0x99; break;
          /* x75 */ case 'u': ch = 0x81; break;
          /* x55 */ case 'U': ch = 0x9A; break;
          /* x52 */ case 'R': ch = 0x21; break;
          /* x78 */ case 'x':
                      ch= -1;
                      code_value= 0;
                      esc_mode= 2;    /* Zeichencode */
                      break;
        }
        if (ch < 0) break;
        fputc (ch, fo);
        cnt3++;
        break;
      case  2: /* Zeichencode: genau 2 HEX-Ziffern */
        esc_mode = 3;
        if (ch >= '0' && ch <= '9') code_value= ch -'0';    else
        if (ch >= 'a' && ch <= 'f') code_value= ch -'a'+10; else
        if (ch >= 'A' && ch <= 'F') code_value= ch -'A'+10; else
        esc_mode = 0;
        break;
      case  3: /* Zeichencode: letzte HEX-Ziffer */
        esc_mode= 0;
        if (ch >= '0' && ch <= '9')
          code_value= 16*code_value + ch -'0';    else
        if (ch >= 'a' && ch <= 'f')
          code_value= 16*code_value + ch -'a'+10; else
        if (ch >= 'A' && ch <= 'F')
          code_value= 16*code_value + ch -'A'+10; else break;
        fputc (code_value, fo);
        cnt3++;
        break;
    }
  }
  fclose  (fi);
  fclose  (fo);
  if (output_file)
  {
    output_file = 0;
    fprintf (stderr, "File %s -> %s Escape: %8ld Char -> %8ld Char\n",
             fnm, output, cnt1, cnt3);
  }
  else
  {
    unlink  (fnm);
    rename  (TEMP, fnm);
    fprintf (stderr, "File %s Escape: %8ld Char -> %8ld Char\n",
             fnm, cnt1, cnt3);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int entities (char *fnm)
{
  int rc;
  char *out_name;

  out_name= (output_file) ? output : TEMP;

  if (entity_level & CONVENT_8bit)
  {
    char *csfnm;

    if (et8 == (struct CS_ET8 *) 0)
    {
      fprintf (stderr, "creating entity translation table '%s'\n",
               code_set_files);

      if ((et8= cs_et8_create_table (0L,
                                     csfnm= set_etc_filename ((char *) 0,
                                                       code_set_files),
                                     (char *) 0, (char *) 0))
            == (struct CS_ET8 *) 0)
      {
        fprintf (stderr, "could not create entity translation table!\n");
        return -1;
      }

      free (csfnm);
    }

    rc= (cs_et8_encode (et8, fnm, out_name, 0x7FFFFFFFL) < 0L) ? -1 : 0;
  }
  else
  {
    rc= sgml_entity_conversion (fnm, out_name, entity_level);
  }

  if (rc == -1)
  {
    fprintf (stderr, "Error processing file %s!\n", fnm);
    return -1;
  }

  if (output_file)
  {
    output_file = 0;
    fprintf (stderr, "File %s -> %s SGML Entities\n", fnm, output);
  }
  else
  {
    unlink  (fnm);
    rename  (TEMP, fnm);
    fprintf (stderr, "File %s SGML Entities\n", fnm);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int read_table (char *fnm)
{
  FILE *fi;
  int state= 0;
  int val1= 0;
  int val2;
  int i;
  int j;
  int j2;
  char puffer [80];
  char *app;
  char *tmp;

  tmp= getenv ("TMP");

  if (access (fnm, 0) == 0)
  {
    app= fnm;
    goto DOIT;
  }

  if (fnm [0] == '%' || fnm [0] == '~')
  {
    app= translate_logic_filename (fnm);
    goto DOIT;
  }

  if ((app= env_file_search (fnm, "APPEND")) != (char *) 0
      || (app= env_file_search (fnm, "AWK")) != (char *) 0
      || (app= env_file_search (fnm, "PATH")) != (char *) 0
     ) goto DOIT;

  return 0;

DOIT: 
  printf ("table=%s\n", app);
  if ((fi= fopen (app, "rt")) == (FILE *) 0) 
  {
    fprintf (stderr, "Translit Table %s not found!\n", fnm);
    return -1;
  }

  for (;;)
  {
    fscanf (fi, "%s", puffer);
    if (feof (fi)) break;

    j= 0;
    if (strncmp (puffer, "#", 1) == 0)
    {
      for (;;)
      {
        i= fgetc (fi) & 0x00FF;
        if (i == '\n') break;
      }
      continue;
    }

    if (strcmp (puffer, "@translate") == 0) state= 1; else
    if (strcmp (puffer, "@delete") == 0)    state= 3; else
    if (strcmp (puffer, "@string") == 0)    state= 4; else
    if (strcmp (puffer, "@end") == 0)       break;    else
    if (strcmp (puffer, "@default0") == 0)  default0 (); else
    if (strcmp (puffer, "@default1") == 0)  default1 (); else
    if (strcmp (puffer, "@default2") == 0)  default2 (); else
    if (strcmp (puffer, "@default3") == 0)  default3 (); else
    if (strcmp (puffer, "@kroemer") == 0)   kroemer ();
    else
    switch (state)
    {
      case 1:
        val1= get_keyval (puffer, &j);
        state= 2;
        break;
      case 2:
        val2= get_keyval (puffer, &j);
        state= 1;
        maptable   [val1] = MAP_translate;
        transtable [val1] = (char) val2;
        break;

      case  3:
        val1= get_keyval (puffer, &j);
        maptable [val1] = MAP_delete;
        break;

      case 4:
        val1= get_keyval (puffer, &j);
        state= 5;
        break;

      case 5:
        state= 4;
        maptable   [val1] = MAP_string;
        transtable [val1] = (char) stringptr;
        j2= 0;
        for (i= 0;; i++)
        {
          val2= get_keyval (puffer, &j);
          if (j == j2) break; j2 = j;
          stringpuffer [stringptr++] = (char) val2;
        }
        stringlng [val1] = (char) i;
        break;
    }
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int get_keyval (char *s, int *i)
{
  int v= 0;
  int b= 10;
  int si;

  for (; (si= s [*i] & 0x00FF) != 0; (*i)++)
  {
    switch (si)
    {
      case '\'':
        if (!v)
        {
          (*i)++;
          return s [(*i)++];
        }
        return v;
      case 'x' :
      case 'X' :
        if (v == 0) b= 16;
        else return v;
        break;
/*      case ',' : (*i)++; return v; */
      default  :
        /* if (cf) return si; */
        if (si >= '0' && si <= '9')             v= v*b + si - '0'     ; else
        if (si >= 'a'  && si <= 'f' && b == 16) v= v*b + si - 'a' + 10; else
        if (si >= 'A'  && si <= 'F' && b == 16) v= v*b + si - 'A' + 10; else
        return v;
    }
  }
  return v;
}

/* Default 0: do not change anything -------------------------------------- */
void default0 ()
{
  int i;

  for (i = 0; i < 256; i++) maptable [i] = MAP_copy;
}

/* Default 1: Characters ber 127 und Control Chars l”schen --------------- */
void default1 ()
{
  int i;

  for (i = 0; i < 32; i++)
      maptable   [i] = MAP_delete;
  for (     ; i < 127; i++)
      maptable   [i] = MAP_copy;
  for (     ; i < 256; i++)
      maptable   [i] = MAP_delete;
  maptable [0x0A] =
  maptable [0x0D] = MAP_copy;
}

/* Default 2: Bit 7 l”schen und Control Chars l”schen --------------------- */
void default2 ()
{
  int i;

  for (i = 0; i <  32; i++) maptable   [i] = MAP_delete;
  for (     ; i < 127; i++) maptable   [i] = MAP_copy;
  for (     ; i < 160; i++) maptable   [i] = MAP_delete;
  for (     ; i < 256; i++)
  {
    maptable   [i] = MAP_translate;
    transtable [i] = (char) (i - 128);
  }
  maptable [0x0A] =
  maptable [0x0D] = MAP_copy;
}

/* Default 3: mask bit 7 -------------------------------------------------- */
void default3 ()
{
  int i;

  for (i = 0; i < 128; i++) maptable [i] = MAP_copy;
  for (     ; i < 256; i++)
  {
    maptable   [i] = MAP_translate;
    transtable [i] = (char) i - 128;
  }
}

/* kroemer: --------------------------------------------------------------- */
void kroemer ()
{
  int i;

  for (i= 0x00; i < 0x20; i++) maptable [i]= MAP_rle;

  for (i= 0x20; i <  256; i++)
  {
    maptable   [i] = MAP_translate;
    transtable [i] = (char) (kroemer_code - i) & 0x00FF;
  }
  maptable   [0x0002]= MAP_rle2;
  maptable   [0x00FF]= MAP_translate;
  transtable [0x00FF]= 0x0A;
}

/* ------------------------------------------------------------------------ */
void default_escape ()
{
}
