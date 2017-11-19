/*
 *  include FILE <gg/rdtp02.h>
 *
 *  restructured dynamic text parser: RTF runtime
 *  - methods
 *  - structures
 *  - prototypes
 *
 *  written:       1996-04-01
 *  latest update: 1997-06-17 14:14:14
 *
 */

#ifndef __GG_rdtp02__
#define __GG_rdtp02__

#include <gg/dyb.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
struct RTF_NODE
{
  struct RTF_NODE *next;
  int node_type;
} ;

/* ------------------------------------------------------------------------ */
struct RTF_GROUP
{
  struct RTF_NODE *next;
  int node_type;

  struct RTF_NODE *down;                /* element held by stack element    */
} ;

/* ------------------------------------------------------------------------ */
struct RTF_COMMAND
{
  struct RTF_NODE *next;
  int node_type;

  char *command;
  char *parameter;
} ;

/* ------------------------------------------------------------------------ */
struct RTF_TEXT
{
  struct RTF_NODE *next;
  int node_type;

  int size;
  int flags;
  char *block;
} ;

/* ------------------------------------------------------------------------ */
struct RTF_STACK
{
  struct RTF_NODE *prev;
  int node_type;

  struct RTF_NODE **hold;               /* element held by stack element    */
} ;

/* ------------------------------------------------------------------------ */
struct RTF_COMMAND_NAME
{
  char *cmd_name;
  long counter;
} ;

/* ------------------------------------------------------------------------ */
struct RTF_BUILDUP
{
  struct RTF_NODE *next;
  int node_type;

  struct RTF_STACK *stack;
  struct RTF_NODE *top;
  struct RTF_NODE **append;

  char bl1 [TMP_BL_SIZE];               /* temporary block                  */
  int bl1_cnt;

  struct YTREE *names;
} ;

/* prototypes: ------------------------------------------------------------ */
/* 0201 */ struct RDTP_GENERATOR *rtf_setup_parser (char *name);
/* 0202 */ int rtf_nop (void *thrp, int ch);
/* 0203 */ int rtf_error (void *thrp, int ch);
/* 0204 */ int rtf_cmd_name_begin (void *thrp, int ch);
/* 0205 */ int rtf_cmd_name (void *thrp, int ch);
/* 0206 */ int rtf_cmd_name_end (void *thrp, int ch);
/* 0207 */ int rtf_print_statistics (struct RDTP_THREAD *thr);
/* 0208 */ int rtf_print_name_statistics (long cmd_info, void *thr_info);

#endif /* __GG_rdtp02__ */
