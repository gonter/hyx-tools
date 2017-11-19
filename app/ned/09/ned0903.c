/*
 *  FILE %ned/09/ned0903.c
 *
 *  Operationen mit dem SETUP-File
 *  o  Installation von Tastenkommandos
 *  o  Installation von Makros
 *  o  Installation von Maus Menu Eintraegen
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *                 1991 02 07: Revision
 *                 1991 05 26: Revision
 *                 1992 04 04: buttons
 *                 1992 07 12: p_rdsetup() -> q_rdsetup
 *                 1996-12-04: q_rdsetup() -> ned_read_setup; rearangements
 *  latest update: 1998-08-16 12:40:19
 *  $Id: ned0903.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

extern struct NED_CONTEXT *ned_main_context;

/* --- SETUP -------------------------------------------------------------- */
#define STP_stdtbl     0
#define STP_pfxq       1
#define STP_pfxk       2
#define STP_pfxo       3
#define STP_func       4
#define STP_end        5
#define STP_macro      6
#define STP_window     7
#define STP_ax         8
#define STP_ay         9
#define STP_bx        10
#define STP_by        11
#define STP_attr      12
#define STP_btyp      13
#define STP_page      14        /* Bildschirmseite              */
#define STP_maus      15
#define STP_menu      15        /* new name vor STP_maus        */
#define STP_button    16
#define STP_tcl       17        /* definition for tcl macros                */
#define STP_tag       18        /* definition for tag macros                */
#define STP_feature   19        /* definition for feature macros            */
#define STP_nobell    20
#define STP_context   21
#define STP_ned_main  22
#define N_STP_CMD     23        /* number of known setup commadns           */

/* ------------------------------------------------------------------------ */
char *STP_CMD [N_STP_CMD] =     /* Kommando Tabelle fuer SETUP              */
{
  "@stdtbl",  "@pfx:q",   "@pfx:k",    "@pfx:o",   "@func",
  "@end",     "@macro",   "@window",   "ax",       "ay",
  "bx",       "by",       "@attr",     "btyp",     "page",
  "@menu",    "@button",  "@tcl",      "@tag",     "@feature",
  "nobell",   "context",  "ned_main"
} ;

/* ------------------------------------------------------------------------ */
int ned_what_stp_cmd (char *s)
{
  int i;

  for (i= 0; i < N_STP_CMD; i++)
    if (strcmp (STP_CMD [i], s) == 0)
      return i;

  return -1;
}

/* ------------------------------------------------------------------------ */
int ned_read_setup (char *fnm)
{
  FILE *fi;
  int rc;
  int cmd_num;

#define MAX_LINE 120
#define MAX_FIELDS 3

  char line [MAX_LINE];
  char *fields [MAX_FIELDS];
  char *token;
  int num_fields;

  if ((fi= fopen (fnm, "rt")) == (FILE *) 0) return -1;

  ned_message_2 ("Reading Setup File ", fnm);
/*  rst_button (); */ /* ##### dunno... shall we??  ... guess not! */

  for (;;)
  {
    rc= fread_line (fi, line, MAX_LINE);
RETRY:
    if (rc <= 0 && feof (fi)) break;
    if (line [0] == '#') continue;

    num_fields= isolate_tokens (line, fields, MAX_FIELDS);
    if (num_fields <= 0) continue;

    token= fields [0];
    if (token [0] == '#') continue;

    cmd_num= ned_what_stp_cmd (token);
    switch (cmd_num)
    {
      case STP_end:
        goto ENDE;
      case STP_macro:
        stp_macro (fi, line, MAX_LINE, MPt_key_sequence);
        goto RETRY;
      case STP_tcl:
        stp_macro (fi, line, MAX_LINE, MPt_tcl);
        goto RETRY;
      case STP_tag:
        stp_macro (fi, line, MAX_LINE, MPt_tag);
        goto RETRY;
      case STP_feature:
        stp_macro (fi, line, MAX_LINE, MPt_feature);
        goto RETRY;
      case STP_button:
        stp_button (fi, line, MAX_LINE);
        goto RETRY;
      case STP_menu:
        stp_mm_item (fi, line, MAX_LINE);
        goto RETRY;
      case STP_attr:
        stp_attr (fi, line, MAX_LINE);
        goto RETRY;

      case STP_nobell:
        vi_set_bell_mode (0);
        break;

      case STP_context:
      case STP_ned_main:
        ned_add_context_list (ned_main_context,
                              (const char **) fields+1,
                              num_fields-1);
        break;

#ifdef USE_FULL_SETUP
      case STP_stdtbl:
        stp_rtbl (fi, 0, 0);
        goto RETRY;
      case STP_pfxq:
        stp_rtbl (fi, 1, 0);
        goto RETRY;
      case STP_pfxk:
        stp_rtbl (fi, 2, 0);
        goto RETRY;
      case STP_pfxo:
        stp_rtbl (fi, 3, 0);
        goto RETRY;
      case STP_func:
        stp_func (fi, 4, 0);
        goto RETRY;

      case STP_window:
        if (windows != (struct WINDOWCTRL *) 0)
        {
          stp_window (fi);
          goto RETRY;
        }

      case STP_ax:
      case STP_ay:
      case STP_bx:
      case STP_by:
      case STP_btyp:
      case STP_page:
        for (;;)   /* Parameter ueberlesen */
        {
          /* ### FIX THIS ### */
          if (line [0] == '#') continue;
          break;
        }
        break;

      case STP_maus:
        if (stp_maus (fi)==-1) goto ENDE;
        goto RETRY;
#endif /* USE_FULL_SETUP */
      default:
        break;
    }
  }

ENDE:
  fclose (fi);

  return 0;
}
