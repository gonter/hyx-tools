/*
 *  include FILE <gg/help2.inc>
 *
 *  Ausgabe von HELP-Klauseln /// Variante 2
 *
 *  Voraussetzung:  static char *HELP []
 *                  STDHLP
 *
 *  written:       1989 04 12
 *  latest update: 1995-02-19
 *
 */

#ifndef STDHLP
#define STDHLP  stdout
#endif

HELP_function ()
{
  int j;

  for (j= 0; j < (sizeof (HELP) / sizeof (char *)); j++)
  {
    fprintf (STDHLP, HELP [j]);
    if ((j % 23) == 22 || (j+1 >= (sizeof (HELP) / sizeof (char *)) ))
    switch (getch ())
    {
      case    0: getch (); break;
      case  'b': case 'B': j = -1; break;
      case 0x1b: exit (0);
    }
    if (j+1 >= (sizeof (HELP) / sizeof (char *))) break;
  }

  exit (0);
}
