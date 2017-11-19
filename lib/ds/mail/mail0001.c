/*
 *  FILE %usr/mail/mail0001.c
 *
 *  RFC822 Keywords aus einer Zeile extrahieren
 *
 *  written:       1990 12 01: aus DISTMAIL.C extrahiert
 *  latest update: 1997-01-25 18:48:19
 *
 */

#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/rfc822.h>

/* ------------------------------------------------------------------------ */
struct RFC822_KEYWORD RFC822_keywords [] =
{
  { "Approved:",          RFC822_Approved       },
  { "Approved-By:",       RFC822_Approved_By    },
  { "Control:",           RFC822_Control        },
  { "Date:",              RFC822_Date           },
  { "From:",              RFC822_From           },
  { "Keywords:",          RFC822_Keywords       },
  { "Newsgroups",         RFC822_Newsgroups     },
  { "Path:",              RFC822_Path           },
  { "Received:",          RFC822_Received       },
  { "Subject:",           RFC822_Subject        },
  { "Subj:",              RFC822_Subject        },
  { "Summary:",           RFC822_Summary        },
  { "To:",                RFC822_To             },
  { "Via:",               RFC822_Via            },
  { (char *) 0,           0                     }
 } ;

/* ------------------------------------------------------------------------ */
static struct YTREE *keywords= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
int RFC822_reg_keyword_table (struct RFC822_KEYWORD *tbl)
{
  int i;

  for (i= 0;; i++)
  {
    if (tbl [i].kw == (unsigned char *) 0) break;
    ytree_set_value (&keywords, tbl [i].kw, tbl [i].code);
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int RFC822_reg_keyword (unsigned char *kw, long code)
{
  if (kw != (unsigned char *) 0)
    ytree_set_value (&keywords, kw, code);

  return 0;
}

/* Keywords suchen: ------------------------------------------------------- */
long RFC822_chk_keyword (char *s, int lng)
/* Return Values:                                                           */
/* RFC822_unknown       ... unidentifzierter Inhalt                         */
/* RFC822_continue      ... Zeile beginnt mit Blank;                        */
/*                          -> Fortsetzung des letzten Records              */
/* RFC822_blank         ... Leerzeile oder Zeile aus Blanks und Tabs;       */
/*                          -> Ende des RFC822 Headers                      */
/* RFC822_sep1          ... Zeile aus ======= bestehend;                    */
/*                          -> NOTEBOOK seperator                           */
/* RFC822_sep2          ... Zeile aus ------- bestehend;                    */
/*                          -> NOTEBOOK seperator                           */
{
  int i;
#define MAX_TMP 20
  unsigned char line3 [MAX_TMP+1];
  int ch;

  switch (s [0])
  {
    case    0:  return (long) RFC822_blank;

    case  ' ':
    case '\t':
      for (i= 1; (ch= s [i] & 0x00FF); i++)
        if (ch != ' ' && ch != '\t') return (long) RFC822_continue;
      return (long) RFC822_blank;

    case  '=':
      for (i= 0; (ch= s [i] & 0x00FF); i++)
        if (ch != '=') break;
      if (i > 60) return (long) RFC822_sep1;
      return (long) RFC822_unknown;

    case  '-':
      for (i= 0; (ch= s [i] & 0x00FF); i++)
        if (ch != '-') break;
      if (i > 60) return (long) RFC822_sep2;
      return (long) RFC822_unknown;

    case 'F':
      if (strncmp (s, "From ", 5) == 0) return (long) RFC822_sep_elm;

    default:
      if (keywords == (struct YTREE *) 0)
        RFC822_reg_keyword_table (RFC822_keywords);

      for (i= 0; i < MAX_TMP && i < lng && (ch= s [i] & 0x00FF); i++)
      {
        if (ch == ' ' || ch == '\t') break;
        if (ch >= 'A' && ch <= 'Z') ch= ch - 'a' + 'A';
        line3 [i]= (unsigned char) ch;
      }
      line3 [i]= 0;

      return ytree_get_value (keywords, line3);
  }
}
