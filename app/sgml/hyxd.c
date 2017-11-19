/*
 *  FILE %sgml/hyxd.c
 *
 *  Hypertext daemon
 *
 *  written:       1992 12 08
 *  latest update: 1997-06-10 16:47:24
 *
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef MSDOS
#include <conio.h>
#define _KREDENZ_TFB "_kredenz.tfb"
#else
#define _KREDENZ_TFB ".kredenz.tfb"
#endif
#include <gg/hyxd.h>

/* ------------------------------------------------------------------------ */
#define STDHLP stdout
static char *HELP [] =
{
  "USAGE: hyxd [options] [cluster]\n",
  "OPTIONS:\n",
  "  -c<cluster> ... name cluster to use\n",
  "  -X<fnm> ... CHEX credential file, authentication implicitly required\n",
  "\n",
  "(@)Ahyxd.c 1.04 #D$1997-06-10 16:47:31\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv []);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  int i, j;
  char *arg;
  char *cluster= (char *) 0;
  char *credential_file= (char *) 0;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
      switch (arg [1])
      {
        case 'c': case 'C':
          cluster= arg+2;
          break;

        case 'X':
          credential_file= (arg[2]) ? arg+2 : _KREDENZ_TFB;
          break;

#include <gg/help.inc>
      }
    else cluster= arg;
  }

  return hyx_d_daemon (stdin, stdout, cluster, credential_file);
}
