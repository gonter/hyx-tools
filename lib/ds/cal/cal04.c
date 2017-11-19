/*
 *  FILE %ds/cal/cal04.c
 *
 *  written:       1994-10-20
 *  latest update: 1998-08-04 13:15:46
 *
 */

#include <gg/dates.h>

#ifdef NIL
#undef NIL
#endif
#define NIL ((struct DAY_INFO_EXTRA *) 0)

/* ------------------------------------------------------------------------ */
static char AT []= "AT";
static char DE []= "DE";
static char BE []= "BE";        /* Belgium              */

static char UK []= "UK";        /* United Kingdom       */
static char GB []= "GB";        /* Great Britain        */
static char SCOT []= "SCOT";    /* Schottland           */
static char IR []= "IR";      /* Irland               */

static char FR []= "FR";
static char ES []= "ES";
static char IT []= "IT";

static char US []= "US";
static char CA []= "CA";        /* Canada               */

struct DAY_INFO_EXTRA AT_holiday [] =
{
  { NIL, AT, "Neujahr",                 DAYIET_fixed, DAYIEC_holiday,  1,  1,    0, 9999 } ,
  { NIL, DE, "Neujahr",                 DAYIET_fixed, DAYIEC_holiday,  1,  1,    0, 9999 } ,
  { NIL, US, "New Year's Day",          DAYIET_fixed, DAYIEC_holiday,  1,  1,    0, 9999 } ,
  { NIL, UK, "New Year's Day",          DAYIET_fixed, DAYIEC_holiday,  1,  1,    0, 9999 } ,
  { NIL, IT, "Capodanno",               DAYIET_fixed, DAYIEC_holiday,  1,  1,    0, 9999 } ,
  { NIL, FR, "Jour de l'An",            DAYIET_fixed, DAYIEC_holiday,  1,  1,    0, 9999 } ,
  { NIL, ES, "?",                       DAYIET_fixed, DAYIEC_holiday,  1,  1,    0, 9999 } ,

  { NIL, GB, "Public Holiday",          DAYIET_fixed, DAYIEC_holiday,  1,  2,    0, 9999 } ,
/******** vermutlich nicht korrekt!
  { NIL, US, "Public Holiday",          DAYIET_fixed, DAYIEC_holiday,  1,  2,    0, 9999 } ,
**********************************/
  { NIL, IR, "Public Holiday",         DAYIET_fixed, DAYIEC_holiday,  1,  2,    0, 9999 } ,
  { NIL, SCOT, "Public Holiday",        DAYIET_fixed, DAYIEC_holiday,  1,  3,    0, 9999 } ,

  { NIL, AT, "Heilige Drei Koenige",    DAYIET_fixed, DAYIEC_holiday,  1,  6,    0, 9999 } ,
  { NIL, DE, "Heilige Drei Koenige",    DAYIET_fixed, DAYIEC_holiday,  1,  6,    0, 9999 } ,
  { NIL, UK, "Epiphany",                DAYIET_fixed, DAYIEC_holiday,  1,  6,    0, 9999 } ,
  { NIL, FR, "Epiphanie",               DAYIET_fixed, DAYIEC_holiday,  1,  6,    0, 9999 } ,
  { NIL, IT, "Epifania N.S.",           DAYIET_fixed, DAYIEC_holiday,  1,  6,    0, 9999 } ,
  { NIL, ES, "?",                       DAYIET_fixed, DAYIEC_holiday,  1,  6,    0, 9999 } ,

  { NIL, IR, "St. Patrick's Day",      DAYIET_fixed, DAYIEC_holiday,  3, 17,    0, 9999 } ,
  { NIL, ES, "?",                       DAYIET_fixed, DAYIEC_holiday,  3, 19,    0, 9999 } ,

  { NIL, IT, "Anniversario della Liberazione",  DAYIET_fixed, DAYIEC_holiday,  4, 25,    0, 9999 } ,

  { NIL, AT, "Staatsfeiertag",          DAYIET_fixed, DAYIEC_holiday,  5,  1,    0, 9999 } ,
  { NIL, DE, "Maifeiertag",             DAYIET_fixed, DAYIEC_holiday,  5,  1,    0, 9999 } ,
  { NIL, IT, "Festa del Lavoro",        DAYIET_fixed, DAYIEC_holiday,  5,  1,    0, 9999 } ,
  { NIL, FR, "Fete du Travail",         DAYIET_fixed, DAYIEC_holiday,  5,  1,    0, 9999 } ,
  { NIL, GB, "May Day",                 DAYIET_fixed, DAYIEC_holiday,  5,  1,    0, 9999 } ,
  { NIL, ES, "?",                       DAYIET_fixed, DAYIEC_holiday,  5,  1,    0, 9999 } ,

  { NIL, UK, "?",                       DAYIET_fixed, DAYIEC_holiday,  5,  2,    0, 9999 } ,

  { NIL, FR, "Fete de l'Armistice 1945",DAYIET_fixed, DAYIEC_holiday,  5,  8,    0, 9999 } , /* MO, 1995 */
  { NIL, FR, "?",                       DAYIET_fixed, DAYIEC_holiday,  5, 12,    0, 9999 } ,
#ifdef __T2_CHECK__
... vermutlich nicht korrekt!
  { NIL, US, "Armed Forces Day",        DAYIET_fixed, DAYIEC_holiday,  5, 20,    0, 9999 } , /* SA, 1995 */
#endif /* __T2_CHECK__ */
  { NIL, CA, "Victoria Day",            DAYIET_fixed, DAYIEC_holiday,  5, 22,    0, 9999 } , /* MO, 1995 */

  { NIL, IT, "Proclam. Republica",      DAYIET_fixed, DAYIEC_holiday,  6,  4,    0, 9999 } ,
  { NIL, IR, "June Holiday",           DAYIET_fixed, DAYIEC_holiday,  6,  5,    0, 9999 } , /* MO, 1995 */
#ifdef __T2_CHECK__
... vermutlich nicht korrekt!
  { NIL, US, "Flag Day",                DAYIET_fixed, DAYIEC_holiday,  6, 14,    0, 9999 } , /* MI, 1995 */
#endif /* __T2_CHECK__ */

  { NIL, CA, "Canada Day",              DAYIET_fixed, DAYIEC_holiday,  7,  1,    0, 9999 } ,
  { NIL, US, "Independence Day",        DAYIET_fixed, DAYIEC_holiday,  7,  4,    0, 9999 } , /* korrekt */
  { NIL, FR, "Fete Nationale",          DAYIET_fixed, DAYIEC_holiday,  7, 14,    0, 9999 } ,
  { NIL, BE, "Fete Nationale",          DAYIET_fixed, DAYIEC_holiday,  7, 21,    0, 9999 } ,

  { NIL, AT, "Maria Himmelfahrt",       DAYIET_fixed, DAYIEC_holiday,  8, 15,    0, 9999 } ,
  { NIL, DE, "Maria Himmelfahrt",       DAYIET_fixed, DAYIEC_holiday,  8, 15,    0, 9999 } ,
  { NIL, IT, "?",                       DAYIET_fixed, DAYIEC_holiday,  8, 15,    0, 9999 } ,
  { NIL, ES, "?",                       DAYIET_fixed, DAYIEC_holiday,  8, 15,    0, 9999 } ,
  { NIL, FR, "?",                       DAYIET_fixed, DAYIEC_holiday,  8, 15,    0, 9999 } ,

  { NIL, DE, "Tag der deutschen Einheit",DAYIET_fixed,DAYIEC_holiday, 10,  3, 1992, 9999 } ,
  /* Tag der deutschen Einheit seit 1992 ??? */
  { NIL, AT, "Nationalfeiertag",        DAYIET_fixed, DAYIEC_holiday, 10, 26, 1956, 9999 } ,

  { NIL, AT, "Allerheiligen",           DAYIET_fixed, DAYIEC_holiday, 11,  1,    0, 9999 } ,
  { NIL, DE, "Buss und Bettag",         DAYIET_fixed, DAYIEC_holiday, 11, 16,    0, 9999 } ,

  { NIL, AT, "Maria Empfaengnis",       DAYIET_fixed, DAYIEC_holiday, 12,  8,    0, 9999 } ,
  { NIL, IT, "?",                       DAYIET_fixed, DAYIEC_holiday, 12,  8,    0, 9999 } ,
  { NIL, ES, "?",                       DAYIET_fixed, DAYIEC_holiday, 12,  8,    0, 9999 } ,

  { NIL, AT, "Christtag",               DAYIET_fixed, DAYIEC_holiday, 12, 25,    0, 9999 } ,
  { NIL, DE, "Christtag",               DAYIET_fixed, DAYIEC_holiday, 12, 25,    0, 9999 } ,
  { NIL, US, "Christmas Day",           DAYIET_fixed, DAYIEC_holiday, 12, 25,    0, 9999 } ,
  { NIL, UK, "?",                       DAYIET_fixed, DAYIEC_holiday, 12, 25,    0, 9999 } ,
  { NIL, IT, "?",                       DAYIET_fixed, DAYIEC_holiday, 12, 25,    0, 9999 } ,
  { NIL, FR, "?",                       DAYIET_fixed, DAYIEC_holiday, 12, 25,    0, 9999 } ,
  { NIL, ES, "?",                       DAYIET_fixed, DAYIEC_holiday, 12, 25,    0, 9999 } ,

  { NIL, AT, "Stefanitag",              DAYIET_fixed, DAYIEC_holiday, 12, 26,    0, 9999 } ,
  { NIL, DE, "Stefanitag",              DAYIET_fixed, DAYIEC_holiday, 12, 26,    0, 9999 } ,
#ifdef __T2D_CHECK__
... vermutlich nicht korrekt!
  { NIL, US, "?",                       DAYIET_fixed, DAYIEC_holiday, 12, 26,    0, 9999 } ,
#endif /* __T2D_CHECK__ */
  { NIL, UK, "?",                       DAYIET_fixed, DAYIEC_holiday, 12, 26,    0, 9999 } ,
  { NIL, IT, "?",                       DAYIET_fixed, DAYIEC_holiday, 12, 26,    0, 9999 } ,

  { NIL, UK, "Boxing Day",              DAYIET_fixed, DAYIEC_holiday, 12, 27,    0, 9999 } ,
  { NIL, AT, "Sylvester",               DAYIET_fixed, DAYIEC_note,    12, 31,    0, 9999 } ,

  { NIL, (char *) 0, (char *) 0,                   0, DAYIEC_standard,  0,  0,    0,    0 }
} ;
