/*
 *  include FILE <gg/ccscanr.h>
 *
 *  Allgemeine Defintionen fuer den Scanner
 *  see: cc and scanner module
 *
 *  written:       1987 11 14
 *  latest update: 1995-09-01
 *
 */

#ifndef __GG_ccscanr__
#define __GG_ccscanr__

/* ------------------------------------------------------------------------ */
typedef void CC_SCAN_ACTION (void *_sc, int ch, void *client_data);
typedef long CC_SCANNER_POSITION (void *_sc);

/* ------------------------------------------------------------------------ */
struct CC_SCANNER
{
  int CCSC_PS_S;
  int CCSC_status;              /* Zustand des Scanners:                    */
                                /*   gueltig *bei* Ausfuehrung der          */
                                /*   Scanner-Action                         */
  int CCSC_new_status;          /* neuer Zustand *nach* Zustandsuebergang:  */
                                /*   gueltig *nach* Ausfuehrung der         */
                                /*   Scanner-Action                         */
  int CCSC_ch;                  /* gelesener Character                      */
  int CCSC_ch_group;            /* Character Group des gelesenen Characters */
  int CCSC_nCLASS;

  int *CCSC_class_table;
  int *CCSC_mx_status;
  int *CCSC_mx_action;
  CC_SCAN_ACTION **CCSC_action;

  CC_SCANNER_POSITION *CCSC_get_position;
} ;

/* ------------------------------------------------------------------------ */
int cc_classify (int class_table [], int chr);
int cc_scanner_init (struct CC_SCANNER *sc, int st);
int cc_scanner (struct CC_SCANNER *sc, int xch, void *client_data);

#endif /* __GG_ccscanr__ */
