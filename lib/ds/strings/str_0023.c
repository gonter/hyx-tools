/*
 *  FILE %ds/strings/str_0023.c
 *
 *  split a string into fields.
 *  the string has the form:  <field1>,<field2>,...,<fieldn>
 *  where fields are: "text" | text
 *  if flg_esc is true, fields may contain escapes of the form: \"
 *
 *  written:       1993-09-03
 *  latest update: 1995-12-03
 *  $Id: str_0023.c,v 1.2 2001/09/10 06:58:44 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int str2fld (
char *src,                      /* original string to be splitted           */
char *flds [],                  /* pointers to individual fields            */
int n_flds,                     /* number of fields possible                */
int delimiter,                  /* delimiter between fields                 */
int open_quote,                 /* opening quoting character                */
int close_quote,                /* closing quote character                  */
int escape_char)                /* escape character                         */
{
  int cnt= 0;                   /* number of fields identified              */
  int flg= 0;                   /* 1 .. searching for new field begin       */
  int ch;                       /* currently processed character            */

#define STAT_text       0       /* normal text without quotes               */
#define STAT_qtext      1       /* text is quoted                           */
#define STAT_qescape    2       /* next character is escaped in quote       */
#define STAT_tescape    3       /* next character is escaped in text        */
  int stat= STAT_text;          /* parser automaton status                  */

  if (src == (char *) 0) return 0;

  for (; (ch= *src) != 0; src++)
  {
    if (flg == 0)
    {
      if (!(delimiter == -1 && (ch == ' ' || ch == '\t')))
      {
        if (n_flds > 0)
        {
          flds [cnt]= src;
          n_flds--;
        }
        cnt++;
        flg= 1;
      }
    }

    switch (stat)
    {
      case STAT_text:
        if (ch == delimiter
            || (delimiter == -1 && (ch == ' ' || ch == '\t'))
           )
        {
          *src= 0;
          flg= 0;
        }
        if (ch == open_quote) stat= STAT_qtext;
        if (ch == escape_char) stat= STAT_tescape;
        break;

      case STAT_qtext:
        if (ch == close_quote) stat= STAT_text;
        if (ch == escape_char) stat= STAT_qescape;
        break;

      case STAT_qescape:
        stat= STAT_qtext;
        break;

      case STAT_tescape:
        stat= STAT_text;
        break;
    }
  }

  return cnt;
}
