/*
 *  include FILE <gg/sgml.h>
 *
 *  declaration of datastructures for SGML tagged text
 *
 *  written:       1990 09 27
 *                 1991 02 03: Revision
 *  latest update: 1994-12-12
 *
 */

#ifndef __GG_sgml__
#define __GG_sgml__

#include <gg/floskel.h>
#include <gg/signatur.h>        /* signatures must be defined!              */

#define TeX_VERSION            /* #################### */

/* ------------------------------------------------------------------------ */
struct SGML_LIST
{
  int sig; 
  void                  *car;
  struct SGML_LIST      *cdr;
} ;

/* ------------------------------------------------------------------------ */
struct SGML_INFO_BYTE
{
  int sig; 
  int size;
  char info [2];
} ;

/* ------------------------------------------------------------------------ */
struct SGML_INFO_LONG
{
  int sig; 
  int size;
  long info [2];
} ;

/* ------------------------------------------------------------------------ */
struct SGML_TAG
{
  int sig; 
  int  sgml_tag_id;
  char *sgml_tag_name;
#ifdef JUNK
  int sgml_tag_flags;           /* Bit 1: can be purged                     */
                                /*        TAG braucht nicht mehr aufgel”st  */
                                /*        zu werden, bzw. Protokollierung   */
                                /*        ist nicht mehr notwendig          */
#endif
  /* usw. usw. usw. */
} ;

/* ------------------------------------------------------------------------ */
struct SGML_VARIABLE
{
  int sig; 
  void *sgml_variable_name;
  void *sgml_variable_value;
  struct SGML_VARIABLE *sgml_variable_next;
} ;

/* SGML TAG Codes: -------------------------------------------------------- */
#define SGML_TAG_undefined             0x0000
#define SGML_TAG_frame                 0x0001
#define SGML_TAG_endframe              0x0002
#define SGML_TAG_Sframe                0x0003
#define SGML_TAG_Sendframe             0x0004
#define SGML_TAG_if                    0x0005
#define SGML_TAG_else                  0x0006
#define SGML_TAG_endif                 0x0007
#define SGML_TAG_switch                0x0008
#define SGML_TAG_case                  0x0009
#define SGML_TAG_default               0x000A
#define SGML_TAG_break                 0x000B
#define SGML_TAG_endswitch             0x000C
#define SGML_TAG_set                   0x000D
#define SGML_TAG_paragraph             0x000E
#define SGML_TAG_endparagraph          0x000F
#define SGML_TAG_Link                  0x0010
#define SGML_TAG_endLink               0x0011
#define SGML_TAG_Ref                   0x0012
#define SGML_TAG_endRef                0x0013
#define SGML_TAG_verbatim              0x0014
#define SGML_TAG_endverbatim           0x0015
#define SGML_TAG_FrAttr                0x0016
#define SGML_TAG_SIG1                  0x0017
#define SGML_TAG_SIG2                  0x0018
#define SGML_TAG_typographic           0x0019
#define SGML_TAG_link                  0x001A
#define SGML_TAG_endlink               0x001B
#define SGML_TAG_name                  0x001C
#define SGML_TAG_endname               0x001D
#define SGML_TAG_reference             0x001E
#define SGML_TAG_endreference          0x001F

#define SGML_TAG_ned_sgml              0x0020
#define SGML_TAG_hyx_stamp             0x0021

#ifdef TeX_VERSION
#define SGML_TAG_Titel                 0x0101
#define SGML_TAG_endTitel              0x0102
#define SGML_TAG_Hervorhebung          0x0103
#define SGML_TAG_endHervorhebung       0x0104
#define SGML_TAG_OverheadText          0x0105
#define SGML_TAG_endOverheadText       0x0106
#define SGML_TAG_Definition            0x0107
#define SGML_TAG_endDefinition         0x0108
#define SGML_TAG_Formel                0x0109
#define SGML_TAG_endFormel             0x010A
#define SGML_TAG_Gleichung             0x010B
#define SGML_TAG_endGleichung          0x010C
#define SGML_TAG_Tabelle               0x010D
#define SGML_TAG_endTabelle            0x010E
#define SGML_TAG_BodyText              0x010F
#define SGML_TAG_endBodyText           0x0110 
#define SGML_TAG_Tex                   0x0111
#define SGML_TAG_slant                 0x0114
#define SGML_TAG_endslant              0x0115 
#define SGML_TAG_quote                 0x0116
#define SGML_TAG_endquote              0x0117
#define SGML_TAG_note                  0x0118
#define SGML_TAG_endnote               0x0119
#endif

/* SGML Prozessor Codes: -------------------------------------------------- */
#define SGML_PROC_verbatim             0
#define SGML_PROC_text                 1
#define SGML_PROC_title_1              2
#define SGML_PROC_title_2              3

/* prototypes: ------------------------------------------------------------ */

/* sgml0008.c */ void sgml_transmit_2segment (void *segment);
/* sgml0008.c */ void flush_segments (void);

#endif /* __GG_sgml__ */
