/*
 *  FILE %sbr/fnmsep4.c
 *
 *  return the part of p2 that is relative to p1 if p2 is a file
 *  in or subdirectory or the same directory as p1, otherwise p2
 *  is returned.
 *
 *  Examples:
 *    p1                        p2                      result
 *    "/usr/tmp/x1.c"           "/usr/tmp/x2.c")        "x2.c"
 *
 *  written:       1996-11-03
 *  latest update: 1996-12-29 17:10:11
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *get_relative_path (char *p1, char *p2)
{
  int ml;

  for (ml= match_lng (p1, p2, 9999)-1; ml >= 0; ml--)
  {
    if (p1 [ml] == '/') break;
  }

  if (
#ifdef MSDOS
      ml <= 3
#else
      ml <= 1
#endif /* !MSDOS */
      || p1 [ml] != '/'
     )
    return p2;

  ml++;
  if (strchr (p1 + ml, '/') == (char *) 0)
  {
    return p2+ml;
  }

  return p2;
}

/* ------------------------------------------------------------------------ */
#ifdef DEBUG
#include <stdio.h>
#include <stdio.h>

struct EXAMPLE
{
  char *e_p1;
  char *e_p2;
  char *e_result;
} ;

struct EXAMPLE Examples [] =
{
/*  p1                          p2                      result              */
  { "/usr/tmp/x1.c",            "/usr/tmp/x2.c",        "x2.c"              },
  { "/usr/tmp/x1.c",            "/usr/x2.c",            "/usr/x2.c"         },
  { "/usr/x1.c",                "/usr/tmp/x2.c",        "tmp/x2.c"          },

  { (char *) 0,                 (char *) 0,             (char *) 0          }
} ;

int main (int argc, char *argv []);
int main (int argc, char *argv [])
{
  char *res;
  int i;
  int ok;
  int ERRORS= 0;
  struct EXAMPLE *example;

#ifdef MSDOS
  argc; argv;
#endif

  for (i= 0;; i++)
  {
    example= &Examples[i];
    if (example->e_p1 == (char *) 0) break;
    res= get_relative_path (example->e_p1, example->e_p2);
    ok= (strcmp (example->e_result, res) == 0);

    fputc ('\n', stdout);
    fputs ((ok) ? "-- OK -------------------" : "** ERROR ****************",
           stdout);
    fputc ('\n', stdout);

    printf ("p1:       '%s'\n", example->e_p1);
    printf ("p2:       '%s'\n", example->e_p2);
    printf ("expected: '%s'\n", example->e_result);
    printf ("returned: '%s'\n", res);

    fputs ("-------------------------\n\n", stdout);

    if (!ok) ERRORS++;
  }

  return ERRORS;
}
#endif /* DEBUG */
