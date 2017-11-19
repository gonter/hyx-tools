/*
 *  FILE ~/usr/mail/mail0002.c
 *
 *  convert a date string into a filename
 *
 *  written:       1994-05-20: aus DISTMAIL.C extrahiert
 *  latest update: 1995-01-29
 *
 */

#include <gg/strings.h>
#include <gg/rfc822.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int mk_fnm_from_date (char *fnm_string, char *date_string, int normalize)
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
  rrc += enter_value (fnm_string,  2, mon, 2);
  rrc += enter_value (fnm_string,  4, tag, 2);
  rrc += enter_value (fnm_string,  6, std, 2);
  rrc += enter_value (fnm_string,  9, min, 2);
  /* rrc += enter_value (fnm_string, 11, sek, 2); */
  fnm_string [ 8]= '.';
  fnm_string [11]= 0;

  return rrc;
}
