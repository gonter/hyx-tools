/*
 *  FILE %nl_kr/deref.c
 *
 *  lookup word reference tables and generate a 'hit list'
 *  - prototypes
 *  - HELP
 *  - T2D
 *
 *  written:       1993-02-28
 *                 1995-12-05 (angeblich letztes Update per 2001-08-03)
 *  latest update: 2001-08-03 16:59:11
 *  $Id: deref.c,v 1.5 2002/07/04 18:08:49 gonter Exp $
 *
 */

/* #define PRINT_CONTACT_INFORMATION */       /* Who is to blame... */
#define REAL_AUTHOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef MSDOS
#include <io.h>
#include <conio.h>
#endif
#include <gg/lookup.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/array.h>
#include <gg/wildcard.h>
#include <gg/filename.h>

#define STDHLP stdout

/* ------------------------------------------------------------------------ */
static int verbose_mode=                0;
#define OM_min                          0
#define OM_gopher                       1
#define OM_hyx                          2
#define OM_veronica                     3
#define OM_cluster                      4
static int output_mode=                 OM_min;
static int print_dil=                   1;

static struct ARRAY_CONTROL *arguments;

/* filenames: ------------------------------------------------------------- */
#ifndef __CMS__
static char *docdir_file=               "docdir.dd";
static char *veronica_file=             "gophscan.out";
static char *VERONICA_NOT_FOUND=        "veronica.not.found";
#define DOCDIR_DD "docdir.dd"
#else
static char *docdir_file=               "docdir.dd.a";
static char *veronica_file=             "gophscan.out.a";
static char *VERONICA_NOT_FOUND=        "veronica.notfound.a";
#define DOCDIR_DD "docdir.dd.a"
#endif

/* ------------------------------------------------------------------------ */
#define MAX_LINE 8192
static char line [MAX_LINE];
static char *hostname=                  "gopher.wu-wien.ac.at";
static char *path_prefix=               "";
static long portnumber=                 (long) 70;
static char *outfile_name=              (char *) 0;
static FILE *outfile=                   (FILE *) 0;
static int stdin_mode=                  0;
static int min_wordlength=              1;
static int max_wordlength=              100;
static char *cluster_name=              (char *) 0;

/* ------------------------------------------------------------------------ */
struct TERM_EVAL *term_list= (struct TERM_EVAL *) 0;
struct TERM_EVAL **term_append= &term_list;
static int term_evaluation= 0;
static long opcode_term_eval= WRint_logic_or;

/* ------------------------------------------------------------------------ */
static char *HELP [] =  /* see also: [%nl_kr/lmd.hyx] deref usage */
{
  "USAGE: deref [options] {file name}\n",
  "OPTIONS:\n",
#ifndef __CMS__
  "  - ... read words from stdin\n",
#endif
  "  -f<fnm> ... parameter file\n",
  "  -o<fnm> ... write output to file\n",
  "  -l<lut> ... name of the LUT file; .wr and .di file follow\n",
  "  -t[<fnm>] ... docdir table [DEF: docdir.dd]\n",
  "  -e[<opr>] ... evaluate results and interpret word sequences\n",
  "                as implicit 'and' or 'or' expression\n",
  "  -mh ... hyx mode\n",
  "  -mc<cl> ... hyx cluster mode; <cl> .. cluster name\n",
  "  -mg ... gopher mode\n",
  "  -mv<fnm> ... veronica mode\n",
  "  -min<n> ... minimal word length; [DEF: 1]\n",
  "              shorter words are ignored\n",
  "  -max<n> ... maximal word length; [DEF: 100]\n",
  "              longer words are truncated\n",
  "  -h<host> ... host name\n",
  "  -p<port> ... port number\n",
  "  -q<pfx> ... path prefix\n",
  "  -v ... verbose mode\n",
  "  -zvnf=<fnm> ... define file name for 'veronica not found' info\n",
  "  -zd ... dont read document info\n",
  "\n",
  "(@)Aderef.c 3.11 #D$2002-07-04 20:07:51\n",
  "\n",
#include <gg/public.inc>
} ;

/* prototypes: ------------------------------------------------------------ */
#ifdef __CMS__
#define interpret_parameter ipa_
#define interpret_parfile   ipf_
#endif

int cdecl main (int argc, char *argv []);
int cdecl print_term_list (struct TERM_EVAL *te);
int cdecl write_deref_results (char *str, struct WORD_REF_LIST *wrl);
int cdecl interpret_parameter (struct LMD_QUERY_SET *lmdqs, char *par);
int cdecl interpret_parfile (struct LMD_QUERY_SET *lmdqs, char *fn,
            char *section);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  char *area;                   /* part of line that holds area definition  */
  char *xline;                  /* part of line that holds search words     */
#define N_WORDS 40              /* maximum number of words allowed          */
  char *words [N_WORDS];        /* individual words in the line             */
  int wc;                       /* number of words acutally found           */
  int i, j;
  int rc;
  struct WORD_REF_LIST *wrl;
  struct TERM_EVAL *te;
  struct LMD_QUERY_SET *lmdqs;
  char *arg;

  if (argc <= 1) goto HLP;

  if ((arguments= array_new ()) == (struct ARRAY_CONTROL *) 0
      || (lmdqs= lmd_new_query_set ()) == (struct LMD_QUERY_SET *) 0
     )
  {
    fprintf (stderr, "fatal error: can't create control structure!\n");
    return 1;
  }

#ifndef __CMS__
  lmd_qs_setup_table_names (lmdqs, "xxx.lt");
#else
  lmd_qs_setup_table_names (lmdqs, "xxx.lt.a");
#endif /* ! __CMS__ */

  for (i= 1; i < argc; i++)
    switch (interpret_parameter (lmdqs, argv [i]))
    {
      case 0:
        break;
HLP:
#include <gg/help.inc>
    }

  if (stdin_mode)
  {
    fclose (stderr);
    fopen ("deref.log", "a");
  }

  lmd_deref_init (lmdqs);

  if (stdin_mode)
  {
    for (;;)
    {
      rc= fread_line (stdin, line, MAX_LINE);
      if ((rc <= 0 && feof (stdin)) || strcmp (line, ".") == 0)
      {
        term_list= ((struct TERM_EVAL *) 0);
        break;
      }

      xline= line;
      area= "";
      for (i= 0; line [i]; i++)
        if (line [i] == '\t')
        {
          xline= &line[i+1];
          area= line;
          break;
        }

      fprintf (stderr, "** area=%s\n", area);
      fprintf (stderr, "** xline=%s\n", xline);

      if ((wc= isolate_words (xline, words, N_WORDS)) > N_WORDS) wc= N_WORDS;

      for (i= 0; i < wc; i++)
      {
        wrl= lmd_deref1 (lmdqs, words [i], min_wordlength, max_wordlength);
        if ((te= lmd_build_term_eval (words [i], wrl))
            != (struct TERM_EVAL *) 0)
        {
          *term_append= te;
          term_append= &te->TE_right;
          print_term_list (te);
        }
      }

      if (output_mode == OM_veronica || output_mode == OM_gopher) break;
    }
  }
  else
  {
    while ((arg= (char *) array_shift (arguments)) != (char *) 0)
    {
      if (arg [0] == '-')
      {
        switch (arg [1])
        {
          case 'f': case 'F':
            interpret_parfile (lmdqs, arg+2, "");
            break;
          default:
            break;
        }
      }
      else
      {
        wrl= lmd_deref1 (lmdqs, arg, min_wordlength, max_wordlength);

#ifdef DEBUG
printf ("Versuch 1, wrl=...\n");
write_deref_results (arg_v [i], wrl);
#endif /* DEBUG */

        if ((te= lmd_build_term_eval (arg, wrl))
            != (struct TERM_EVAL *) 0)
        {
          *term_append= te;
          term_append= &te->TE_right;
        }
      }
    }
  }

  lmd_deref_finish (lmdqs);
  print_term_list (term_list);

  switch (output_mode)
  {
    case OM_gopher:
    case OM_veronica:
      fputs (".\n", outfile);
      break;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int print_term_list (struct TERM_EVAL *te)
{
  if (term_evaluation)
  {
    struct TERM_EVAL *te_evaluated;
    struct WORD_REF_LIST *wrl;

    te_evaluated= lmd_evaluate_terms (te, opcode_term_eval);
    if ((wrl= lmd_new_word_ref_list ()) != (struct WORD_REF_LIST *) 0)
    {
      wrl->WRL_dil= te_evaluated->TE_dil;
      write_deref_results (/* te_evaluated->TE_string */ "eval'd", wrl);
    }
  }
  else
  {
    for (; te != (struct TERM_EVAL *) 0; te= te->TE_right)
      write_deref_results (te->TE_string, te->TE_wrl);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int write_deref_results (char *str, struct WORD_REF_LIST *wrl)
{
  if (outfile_name != (char *) 0)
  {
    fprintf (stderr, "opening output file %s\n", outfile_name);
    outfile= fopen (outfile_name, "w");
  }

  if (outfile == (FILE *) 0)
  {
    /************
    fprintf (stderr, "writing output to stdout\n");
    ************/
    outfile= stdout;
  }

  switch (output_mode)
  {
    case OM_gopher:
      if (lmd_print_gopher_hit_list (outfile, docdir_file, wrl, path_prefix,
                                 "0", hostname, portnumber) <= 0)
        goto VNF;
      break;

    case OM_hyx:
      lmd_print_hyx_hit_list (outfile, docdir_file, wrl);
      break;

    case OM_cluster:
      lmd_print_hyx_cluster_hit_list (outfile, wrl, cluster_name);
      break;

    case OM_veronica:
      if (lmd_print_veronica_hit_list (outfile, veronica_file, wrl) <= 0)
      {
VNF:
        if (f2transfer (VERONICA_NOT_FOUND, outfile, 0L, 0x7FFFFFFFL) == -1)
        {
          fprintf (outfile,
  "0sorry, your search for '%s' didn't produce any result.\t\terr.host\t0\n",
  str);
          if (wrl != (struct WORD_REF_LIST *) 0)
            fprintf (outfile,
  "0'%s' was dropped from the index because it appeared too frequently.\t\terr.host\t0\n",
  str);
#ifdef PRINT_CONTACT_INFORMATION
          fprintf (outfile,
  "0report bugs to Gerhard.Gonter@wu-wien.ac.at\t\terr.host\t0\n");
#endif
        }
      }
      break;

    default:
      lmd_print_doc_hit_list (outfile, wrl, print_dil);
      break;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int interpret_parameter (struct LMD_QUERY_SET *lmdqs, char *par)
{
  int j;
  int ch;

  if (par[0] == '-')
    switch (par[1])
    {
      case 'e': case 'E':
        term_evaluation= 1;
        opcode_term_eval= WRint_logic_or;
        if (par+2 == 0) break;
        if (strcmp (par+2, "and") == 0
            || strcmp (par+2, "und") == 0)
          opcode_term_eval= WRint_logic_and;
        break;

      case 'f': case 'F':
        if (par[2] == 0) break;
        array_push (arguments, (void *) par);
        break;

      case 'h': case 'H':
        hostname= strdup (par+2);
        break;

      case 'l': case 'L':
        lmd_qs_setup_table_names (lmdqs, par+2);
        break;

      case 'm': case 'M':
        switch (par[2])
        {
          case 'g': case 'G':
            output_mode= OM_gopher;
            break;
          case 'h': case 'H':
            output_mode= OM_hyx;
            break;
          case 'c': case 'C':
            output_mode= OM_cluster;
            cluster_name= par+3;
            lmd_qs_setup_table_names (lmdqs, cluster_name);
            fnmcpy3 (&lmdqs->LMDQS_fn_lut, cluster_name, ".lt");
            break;
          case 'v': case 'V':
            output_mode= OM_veronica;
            if (par[3]) veronica_file= strdup (par+3);
            break;
          case 'a': case 'A':
            ch= par[3];
            if (ch == 'x' || ch == 'X')
              max_wordlength= (int) get_parameter_value (par+4);
            break;
          case 'i': case 'I':
            ch= par[3];
            if (ch == 'n' || ch == 'N')
              min_wordlength= (int) get_parameter_value (par+4);
            break;
          default:
            output_mode= OM_min;
            break;
        }
        break;

      case 'o': case 'O':
        outfile_name= strdup (&par[2]);
        break;

      case 'p': case 'P':
        portnumber= get_parameter_value (par+2);
        break;

      case 'q': case 'Q':
        path_prefix= strdup (&par[2]);
        break;

      case 't': case 'T':
        docdir_file= strdup ((par[2] == 0) ? DOCDIR_DD : (par+2));
        break;

      case 'v': case 'V':
        for (j= 1; par[j]; j++)
          switch (par[j])
          {
            case 'v': case 'V':
              verbose_mode= 1;
              break;
            default:
              fprintf (stderr, "unknown option %c\n", par[j]);
              return -1;
          }
        break;

      case 'z': case 'Z':
        if (strncmp (par, "-zvnf=", 6) == 0)
          VERONICA_NOT_FOUND= strdup (par+6);
        else if (strncmp (par, "-zd", 3) == 0) print_dil= 0;
        break;

      case 0:
        stdin_mode= 1;
        break;

      default:
        return -1;
  }
  else array_push (arguments, (void *) par);

  return 0;
}

/* ------------------------------------------------------------------------ */
int interpret_parfile (struct LMD_QUERY_SET *lmdqs, char *fn, char *section)
{
  FILE *parfile;
  int j;
  int readit= 0;

  if (section == (char *) 0) section= "";
  if (*section == 0) readit= 1;

  if ((parfile= fopen (fn, "r")) == (FILE *) 0) return -1;
  fprintf (stderr, ">> reading par file %s, section %s\n", fn, section);

  for (;;)
  {
    j= fread_line (parfile, line, 100);
    if (j <= 0 && feof (parfile)) break;

    if (*line == '#') continue;
    if (*line == '[')
    {
      readit= 0;
      if (strncmp (line, section, strlen (section)) == 0) readit= 1;
      continue;
    }

    if (readit) interpret_parameter (lmdqs, line);
  }
  fclose (parfile);

  return 0;
}
