/*
 *  FILE ~/usr/sgml/sgml0012.c
 *
 *  written:       1991 03 03
 *  latest update: 1999-04-25 16:41:08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/sgml.h>

static int recursion_level= 0;

/* ------------------------------------------------------------------------ */
void sgml_report_list (struct SGML_LIST *sl)
{
  char *cp;
  int signature;
  int run;

  do
  {
    run= 0;
    signature= sl->sig;

    switch (signature)
    {
      case 0x0001: cp = "LIST"; break;
      case 0x0011: cp = "BYTE"; break;
      case 0x0021: cp = "TAG"; break;
      case 0x0022: cp = "ATTRIBUTE"; break;
    }

    blanks (stdout, recursion_level*2);
    printf ("list signature: 0x%04X \'%s\'\n", signature, cp);

    switch (signature)
    {
      case 0x0001:
        recursion_level++;
        sgml_report_list (sl->car);
        recursion_level--;
        sl=sl->cdr;
        run=1;
        break;

      case 0x0011:
      case 0x0021:
      case 0x0022:
        {
          struct SGML_INFO_BYTE *ib;

          ib = (struct SGML_INFO_BYTE *) sl;
          dump (stdout, ib->info, ib->size);
        }
        break;
    }
  } while (run);
}
