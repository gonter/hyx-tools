/*
 *  include FILE <gg/rdtp.h>
 *
 *  restructured dynamic text parser: runtime engine
 *  - methods
 *  - structures
 *  - prototypes
 *
 *  written:       1996-04-01
 *  latest update: 1997-01-15 10:43:01
 *
 */

#ifndef __GG_rdtp__
#define __GG_rdtp__

/** #define RDTP_DEBUG **/
#define TMP_BL_SIZE 256                 /* size of temporary blocks         */

/* methods: --------------------------------------------------------------- */
typedef int RDTP_state_transition (void *thrp, int ch);
/* there should be some kind of forward declaration somewhere around here.  */

/* structures: ------------------------------------------------------------ */
struct RDTP_STATE
{
  struct RDTP_STATE **new_states;
  RDTP_state_transition **transitions;

#ifdef RDTP_DEBUG
  char *state_name;
  char **transition_info;
#endif /* RDTP_DEBUG */
} ;

/* ------------------------------------------------------------------------ */
struct RDTP_CLASS
{
  int char_classes [256];
  int max_classes;
  struct RDTP_STATE *start_state;

  RDTP_state_transition *method_for_undefined_state;
  struct RDTP_STATE     *state_for_undefined_state;

  RDTP_state_transition *method_for_undefined_input;
  struct RDTP_STATE     *state_for_undefined_input;
} ;

/* ------------------------------------------------------------------------ */
struct RDTP_THREAD
{
  struct RDTP_CLASS *class;
  struct RDTP_STATE *current_state;

  void *payload;
} ;

/* prototypes: ------------------------------------------------------------ */
/* 0001 */ int rdtp_parse_char (struct RDTP_THREAD *thread, int ch);
/* 0002 */ struct RDTP_THREAD *rdtp_new_thread (struct RDTP_CLASS *cl);
/* 0003 */ long rdtp_parse_file (struct RDTP_THREAD *thread,
             char *fnm, long beg, long size);
#ifdef _FILE_DEFINED
/* 0004 */ long rdtp_parse_stream (struct RDTP_THREAD *thread,
             FILE *fi, long size);
#endif /* _FILE_DEFINED */
/* 0005 */ void rdtp_bad_thread (char *id);

#endif /* __GG_rdtp__ */
