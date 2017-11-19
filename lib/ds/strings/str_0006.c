/*
 *  FILE %ds/strings/str_0006.c
 *
 *  written:       1989 10 14: (from STRINGS.SAR)
 *                 1992 09 13: revision
 *                 1992 09 13: revision
 *  latest update: 1997-08-28 13:27:41
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int match (                     /* match strings (e.g: filenames)           */
char  *pattern,                 /* matching pattern                         */
char  *string)                  /* string to match                          */
/* RETURN: 0 .. no match                                                    */
/*         1 ..    match without wildcard                                   */
/*         2 ..    match with    wildcard                                   */
{
#define STAT_start           0
#define STAT_wild_string     1
#define STAT_wild_char       3
  int stat= STAT_start;         /* state of the automato                    */
  int wild= MATCH_no_wildcard;  /* ... used as return value                 */
  int ch_p= 0;                  /* letztes Zeichen von pattern              */
  int p_ch_p= 0;                /* Pattern Backtracking Char                */
  char *p_pattern= (char *) 0;  /* Pattern Backtracking Puffer              */
  char *p_string= (char *) 0;   /* String  .            .                   */

  for (;;)
  {
    switch (stat)
    {
      case STAT_start:
        switch (ch_p= *pattern++)
        {
          case   0: stat= 4;          break;
          case '?': stat= STAT_wild_char;   wild= MATCH_wildcard; break;
          case '*': stat= STAT_wild_string; wild= MATCH_wildcard; break;
          default : stat= 5;          break;
        }
        break;

      case STAT_wild_string:
        switch (ch_p= *pattern++)
        {
          case   0: return wild;        /* * at end of string, match all    */
          case '*':                     /* skip over all other wild chars   */
          case '?': break;              /* including single char matches    */
          default : stat = 2; break;
        }
        break;

      case 2:
        if (!*string) /* Sonderfall: *.(te) soll auch gematcht werden */
          return MATCH_no;
        if (*string++ == (char) ch_p)
        { 
          p_string= string;
          p_pattern= pattern;
          p_ch_p= ch_p;
          stat= STAT_start;
        }
        break;

      case STAT_wild_char:
        stat= (!*string++) ? 6 : STAT_start;
        break;

      case 4:
        if (*string) stat= 6;
        else return wild;
        /* *NO* break here! */

      case 5:
        stat= (*string++ != (char) ch_p) ? stat= 6 : STAT_start;
        break;

      case 6: /* Kein Match; Backtracking versuchen */
        if (p_pattern == (char *) 0
          ||p_string  == (char *) 0) return MATCH_no;
        string= p_string;
        pattern= p_pattern;
        ch_p= p_ch_p;
        stat= 2; /* Zurueck zur Wildcard */
        break;
    }
  }
}
