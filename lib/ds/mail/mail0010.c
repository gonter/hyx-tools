/*
 *  FILE ~/usr/mail/mail0010.c
 *
 *  convert a date string into a filename
 *
 *  written:       1995-01-29: variation of mail0002.c
 *  latest update: 1995-01-29
 *
 */

#include <gg/strings.h>
#include <gg/rfc822.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int normalize_date (char *fnm_string, char *date_string, int normalize)
{
  int jahr, mon, tag;
  int std, min, sek;
  int tz;
  int rrc;

  analyze_date (date_string, &jahr, &mon, &tag, &std, &min, &sek, &tz);

  if (normalize)
  {
    std -= tz;                  /* -0400 means it's already 4 hours later   */
    if (std < 0) std= 0;        /* :(( well.. something to be solved..      */
  }

  rrc  = enter_value (fnm_string,  0, jahr, 2);
  rrc += enter_value (fnm_string,  3, mon, 2);
  rrc += enter_value (fnm_string,  6, tag, 2);
  rrc += enter_value (fnm_string,  9, std, 2);
  rrc += enter_value (fnm_string, 12, min, 2);

  fnm_string [ 2]=
  fnm_string [ 5]= '-';
  fnm_string [ 8]= ' ';
  fnm_string [11]= ':';
  fnm_string [14]= 0;

  return rrc;
}
