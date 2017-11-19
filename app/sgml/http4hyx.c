/*
 *  FILE %sgml/http4hyx.c
 *
 *  HTTP server for HYX
 *
 *  written:       1994-04-09
 *  latest update: 1997-09-14 19:17:55
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <io.h>
#include <conio.h>
#endif
#include <gg/filename.h>
#include <gg/hyxd.h>

#define STDHLP stderr

/* ------------------------------------------------------------------------ */
static int verbose_mode= 0;
static char *hostname= "";
static char *portnumber= "";

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: http4hyx [options] {file name}\n",
  "OPTIONS:\n",
  "  -d<dir> ... directory prefix\n",
  "  -h<name> ... set host name\n",
  "  -p<port> ... set port number\n",
  "  -s ... single transaction mode\n",
  "  -t ... ticket mode\n",
  "  -md5 ... turn on MD5 transformation of request strings\n",
  "  -l ... lexicon server mode\n",
  "  -v ... verbose level\n",
  "  -x ... preformatted\n",
  "EXAMPLES:  \n",
  "\n",
  "(@)Ahttp4hyx.c 0.04 #D$1997-09-14 19:17:52\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);

/* ------------------------------------------------------------------------ */
int main (int  argc, char *argv [])
{
  int i, j;
  int http_flags= 0;

  if (argc <= 1) goto HLP;

  for (i= 1; i < argc; i++)
    if (argv [i][0] == '-')
      switch (argv [i][1])
      {
        case 'd': case 'D':
          http4hyx_set_path (&argv[i][2]);
          break;
        case 'h': case 'H':
          hostname= &argv[i][2];
          break;
        case 'p': case 'P':
          portnumber= &argv[i][2];
          break;

        case 'v': case 'V':
        case 'l': case 'L':
        case 'm': case 'M':
        case 's': case 'S':
        case 't': case 'T':
        case 'x': case 'X':
          for (j= 1; argv [i][j]; j++)
            switch (argv [i][j])
            {
              case 'v': case 'V':
                verbose_mode++;
                http_flags |= HYXD_verbose;
                break;
              case 'd': case 'D': case '5':
                break;
              case 'l': case 'L':
                http_flags |= HYXD_lexicon_server;
                break;
              case 'm': case 'M':
                http_flags |= HYXD_md5_transformation;
                break;
              case 's': case 'S':
                http_flags |= HYXD_single_transaction;
                break;
              case 't': case 'T':
                http_flags |= HYXD_ticket_required;
                break;
              case 'x': case 'X':
                http_flags |= HYXD_preformatted;
                break;
              default:
                fprintf (stderr, "unknown option %c\n", argv[i][j]);
                goto HLP;
            }
          break;

HLP:
#include <gg/help.inc>
      }

  http4hyx_daemon (stdin, stdout, http_flags);

  return 0;
}
