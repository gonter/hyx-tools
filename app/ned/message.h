/*
 *  FILE %ned/message.h
 *
 *  Fehlermeldungen und Mitteilungen
 *
 *  written:       1989 02 21
 *                 1991 01 29: Revision
 *  latest update: 1997-01-05 17:05:57
 *
 */

#ifndef __NED_message__
#define __NED_message__

#define ERR_OPEN_WDW    "MEM: can't open window"
#define ERR_OPEN_FILE   "can't open file"
#define ERR_WDW_SIZE    "WDW: window size not ok"
#define ERR_MEMORY      "MEM: file truncated!"
#define ERR_SGML_READ   "error reading SGML tagging sequence"

#define QST_MAC_NUM     "macro #: "
#define QST_MAC_TXT     "macro text: "
#define QST_MAC_TYPE    "macro type: t)cl  k)eys "

#define CNF_old_version "load old version? (Y|N) "                  /* 0314 */
#define CNF_abandon     "abandon changed file? (Y|N) "              /* 0411 */
#define CNF_panic       "immediately abort NED? (Y|N) "             /* 0413 */

#define CNF_pico_exit   "Save modified buffer (ANSWERING 'No' WILL DESTROY CHANGES) ? (Y|N)"

#endif /* __NED_message__ */
