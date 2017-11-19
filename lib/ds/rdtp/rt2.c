/*
 *  FILE %ds/rdtp/rt2.c
 *
 *  written:       1997-06-16
 *  latest update: 1997-06-16 14:52:06
 *
 */

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
#define MAX_BUFFER 256
static char b_n [MAX_BUFFER];
static char b_v [MAX_BUFFER];

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv []);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  struct SGML_BUILDUP *sgml_build;
  struct SGML_OPENING_TAG *ot;
  struct SGML_ATTRIBUTE_LIST *attr;
  int i;
  char *cp;

  if ((sgml_build= sgml_initialize_buildup ())
         == (struct SGML_BUILDUP *) 0
      || (ot= sgml_new_opening_tag (sgml_build, "hyx.l"))
         == (struct SGML_OPENING_TAG *) 0
     )
  {
    fprintf (stderr, "new ot failed\n");
    return 0;
  }

  for (i= 0; i < 10; i++)
  {
    sprintf (b_n, "a%03d", i);
    sprintf (b_v, "value %3d", i);
    if ((attr= sgml_add_attribute (ot, b_n, b_v))
         == (struct SGML_ATTRIBUTE_LIST *) 0)
    {
      fprintf (stderr, "new attribute failed\n");
      return 0;
    }
  }

  sgml_diag_tag (stdout, ot);
  if ((cp= sgml_tag_to_string (ot, (char *) 0, 0, 0)) == (char *) 0)
  {
    fprintf (stderr, "tag_to_string failed!\n");
    return 0;
  }

  printf ("[%s]\n", cp);

  return 0;
}
