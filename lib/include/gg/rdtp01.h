/*
 *  include FILE <gg/rdtp01.h>
 *
 *  restructured dynamic text parser: state table generator
 *  - methods
 *  - structures
 *  - prototypes
 *
 *  written:       1996-04-01
 *  latest update: 1996-08-08 17:15:59
 *
 */

#ifndef __GG_rdtp01__
#define __GG_rdtp01__

#include <gg/ytree.h>

#define MAX_STATE_CLASSES 256
#define RDTP_MAX_CLASSES 256

/* ------------------------------------------------------------------------ */
struct RDTP_STATE_TRANSITION
{
  struct RDTP_STATE_TRANSITION *next;

  /* definition */
  char *state_to;                       /* next state name                  */
  RDTP_state_transition *method;        /* action to be performed           */
  char *method_info;                    /* description about action         */

  long range_begin;                     /* character ranges; ISO 10646      */
  long range_end;

  /* derivations */
  int class_code;
} ;

/* ------------------------------------------------------------------------ */
struct RDTP_STATE_DEFINITION
{
  char *state_name;
  struct RDTP_STATE_TRANSITION *trans;
  struct RDTP_STATE *state;             /* runtime table for the definiton  */

  int state_used;                       /* 0 .. ignore                      */
                                        /* 1 .. dzt. in Verwendung          */
} ;

/* ------------------------------------------------------------------------ */
struct RDTP_GENERATOR
{
  char *generator_name;
  char *start_state;
  struct RDTP_CLASS *class;             /* parser class definition          */

  struct YTREE *state_names;
/*******  int used; *******/

  int generator_ok;

  int defined_classes;
  int class_table [RDTP_MAX_CLASSES];

  RDTP_state_transition *method_for_undefined_state;
  struct RDTP_STATE     * state_for_undefined_state;

  RDTP_state_transition *method_for_undefined_input;
  struct RDTP_STATE     * state_for_undefined_input;
} ;

/* ------------------------------------------------------------------------ */
struct RDTP_STATIC_STATE_TABLE          /* static description of states     */
{                                       /* and transitions                  */
  char *state_from;
  char *state_to;

  long range_begin;                     /* character ranges; ISO 10646      */
  long range_end;

  char *method_info;                    /* description about action         */
  RDTP_state_transition *method;        /* action to be performed           */
} ;

/* prototypes: ------------------------------------------------------------ */
/* 0101 */ int rdtp_define_transition (struct RDTP_GENERATOR *gen,
             char *from, char *to, long begin, long end,
             RDTP_state_transition *method, char *info);
/* 0102 */ int rdtp_load_static_table (struct RDTP_GENERATOR *gen,
             struct RDTP_STATIC_STATE_TABLE state_table []);
/* 0103 */ struct RDTP_STATE_DEFINITION *rdtp_find_state_definition (
             struct RDTP_GENERATOR *gen, char *state_name);
#ifdef _FILE_DEFINED
/* 0104 */ int rdtp_print_generator (struct RDTP_GENERATOR *gen, FILE *fo);
#endif /* _FILE_DEFINED */

/* 0105 */ int rdtp_print_states (struct YTREE *yt, void *cd);
/* 0104 */ int rdtp_generate_transition_table (struct RDTP_GENERATOR *gen);
/* 0107 */ int rdtp_drop_tables (struct YTREE *yt, void *cd);
/* 0108 */ int rdtp_unmark_states (struct YTREE *yt, void *cd);
/* 0109 */ int rdtp_mark_states (
             struct RDTP_GENERATOR *gen,
             char *start, int verbosity);
/* 0110 */ int rdtp_process1_state_table (
             struct RDTP_GENERATOR *gen,
             struct RDTP_STATE_DEFINITION *st);
/* 0111 */ int rdtp_process2_state_table (
             struct RDTP_GENERATOR *gen,
             struct RDTP_STATE_DEFINITION *st);
/* 0112 */ int rdtp_process3_state_table (
             struct RDTP_GENERATOR *gen,
             struct RDTP_STATE_DEFINITION *st);
/* 0113 */ int rdtp_pass2_transformation (struct YTREE *yt, void *cd);
/* 0114 */ int rdtp_pass3_transformation (struct YTREE *yt, void *cd);
/* 0115 */ int rdtp_drop_state_table (
             struct RDTP_GENERATOR *gen,
             struct RDTP_STATE_DEFINITION *st);
#ifdef _FILE_DEFINED
/* 0116 */ int rdtp_print_state_entry (FILE *fo,
             struct RDTP_STATE_TRANSITION *tr, char *pfx);
#endif /* _FILE_DEFINED */

#endif /* __GG_rdtp01__ */
