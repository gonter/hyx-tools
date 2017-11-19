/*
 *  FILE %usr/mail/mail0003.c
 *
 *  check if the current line is a mail delimiter
 *
 *  written:       1995-01-29: aus DISTMAIL.C extrahiert
 *  latest update: 1997-01-25 19:38:00
 *
 */

#include <string.h>
#include <gg/strings.h>
#include <gg/rfc822.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
static char OLDMAIL_LOG_sep [] = "+++++++ +++++++ +++++++";

/* ------------------------------------------------------------------------ */
int message_delimiter (char *p, int delim_mode)
{
  int i;

  switch (delim_mode)
  {
    case DELIMIT_NOTEBOOK:
      for (i= 0;; i++) if (p [i] != '=') break;
      if (i >= 70) return 1;
      break;
    case DELIMIT_OCCAM_archive: /* OCCAM ARCHIVE */
      if (strncmp (p, "From daemonprgv", 16) == 0) return 1;
      break;
    case DELIMIT_LISTSERV_DB: /* LISTSERV Database Output */
      if (strncmp (p, ">>> Item number ", 16) == 0) return 1;
      break;
    case DELIMIT_3:
      for (i=1;; i++) if (p [i] != '=') break;
      if (i >= 64) return 1;
      break;
    case DELIMIT_Love_Hounds:
      for (i=0;; i+= 2)
        if (((int) (p[i]&0x00FF)) != 0x00D5
           || (((int) p[i+1]&0x00FF)) != 0x00FE) break;
      if (i >= 32) return 1;
      break;
    case DELIMIT_card_oldmail:
      if (strncmp (p, OLDMAIL_LOG_sep, 23) == 0) return 1;
      break;
    case DELIMIT_Unix:
      if (strncmp (p, "From ", 5) == 0) return 1;
      break;
    default:
      return -1;
  }

  return 0;
}
