/*
 *  include FILE <gg/signatur.h>
 *
 *  signatures of various data structures
 *
 *  written:       1994-11-12
 *  latest update: 1996-12-11 12:51:39
 *
 */

#ifndef __GG_signature__
#define __GG_signature__

/* <gg/sgml.h> SGML_signatures -- (int) ----------------------------------- */
#define SIG_LIST                0x0101
#define SIG_INFO_BYTE           0x0111
#define SIG_INFO_LONG           0x0112
#define SIG_TAG                 0x0121
#define SIG_PARAMETER           0x0122

/* <gg/parse.h> -- (long) ------------------------------------------------- */
#define SIG_epsilon             0x0200
#define SIG_TEXT_SEGMENT        0x0201
#define SIG_TEXT_ELEMENT        0x0202  /* formerly: SIG_TEXT */
#define SIG_TAG_DEFINITION      0x0203
#define SIG_MARKUP              0x0204
#define SIG_ENTRY               0x0205
#define SIG_OUTPUT_DESCRIPTOR   0x0206

/* <gg/ta.h> -- (ilong) --------------------------------------------------- */
#define SIG_TA_TAG              0x0301
#define SIG_TA_TEXT             0x0302
#define SIG_TA_OBJECT           0x0303

/* <gg/varspace.h> -- (long) ---------------------------------------------- */
#define SIG_VS_NODE             0x0401

/* <gg/vieos.h> -- (long) ------------------------------------------------- */
#define SIG_VIEOS_CONTEXT       0x0500
#define SIG_VIEOS_MARKUP        0x0501
#define SIG_VIEOS_INDEX         0x0502
#define SIG_VIEOS_BLOCK         0x0503
#define SIG_VIEOS_CLUSTER       0x0504
#define SIG_VIEOS_GENERIC       0x05FF

/* <gg/hyxtcl.h> -- (long) ------------------------------------------------ */
#define SIG_BBC_SESSION         0x0601
#define SIG_BBC_LISTEN          0x0602
#define SIG_BBC_CONNECTION      0x0603

/* <gg/ytree.h> -- (long) ------------------------------------------------- */
#define SIG_YTREE_CONTROL       0x0701

#endif /* __GG_signature__ */
