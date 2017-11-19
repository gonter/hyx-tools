/*
 *  include FILE <gg/convent.h>
 *
 *  Convert Characters to Entities
 *
 *  written:       1991 07 03
 *  latest update: 1995-12-10
 *  $Id: convent.h,v 1.2 2005/09/04 20:27:37 gonter Exp $
 *
 */

#ifndef __GG_convent__
#define __GG_convent__

#include <gg/floskel.h>

/* conversion flags ------------------------------------------------------- */
#define CONVENT_amp             0x0001
#define CONVENT_lt_gt           0x0002
#define CONVENT_8bit            0x0004
#define CONVENT_pc_8bit         0x0004
#define CONVENT_mac_8bit        0x0008
#define CONVENT_pc_text         0x0007

/* prototypes ------------------------------------------------------------- */
/* convent1.c */ int cdecl sgml_entity_conversion (char *fni, char *fno,
                   int level);
/* convent2.c */ char *cdecl get_pc_sgml_entity (int ch);
                 int cdecl find_pc_sgml_entity (const char *s);
/* convent4.c */ char *cdecl get_typographic_sgml_entity (int ch);
                 int cdecl find_typographic_sgml_entity (char *s);

#ifdef _FILE_DEFINED
/* convent5.c */ int cdecl fputc_entity (int ch, FILE *fo, int level);
/* convent6.c */ int cdecl fputs_entity (char *s, FILE *fo, int level);
#endif /* _FILE_DEFINED */

#endif /* __GG_convent__ */
