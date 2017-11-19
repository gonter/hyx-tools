/*
 *  FILE ~/usr/sgml/msrvh.h
 *
 *  datastructures and constants for the HYX mail server
 *  -  t2d
 *
 *  written:       1994-06-19
 *  latest update: 1995-06-25
 *
 */

#ifndef __GG_msrvh__
#define __GG_msrvh__

/* ------------------------------------------------------------------------ */
struct MSRV_request             /* description of a request                 */
{
  char *MR_From;                /* originator of the request                */
  char *MR_Date;                /* date found in the mail header            */
  char *MR_Subject;             /* sender's subject line                    */
  char *MR_Reply_To;            /* reply-to address, if given               */

  char *MR_reply_address;       /* address where reply goes to              */
  char *MR_action;              /* currently processed action               */

  int MR_transformation;        /* type of output processing                */
#define MRtr_none       0       /* no transformation at all                 */
#define MRtr_simple     1       /* simply use chksgml, remove tags          */

  int MR_authorization_status;  /* authorization flag                       */
#define MRas_anonymous  0       /* no authorization done                    */
#define MRas_ok         1       /* authorization done ok                    */
#define MRas_wrong      2       /* authorization done but no ok             */
} ;

/* ------------------------------------------------------------------------ */
struct MSRV_authorization
{
  struct MSRV_authorization *MA_next;   /* next auth record for this base   */
  char *MA_user;                        /* authorized user name             */
  char *MA_key;                         /* encrypted user key               */
} ;

/* ------------------------------------------------------------------------ */
struct MSRV_defaults
{
  char *MD_database;            /* database file name                       */
  char *MD_name;                /* descriptive name of the database         */
  char *MD_sender;              /* email address of database results        */
  char *MD_errors_to;           /* email address for error processing       */
  char *MD_cc;                  /* email address for carbon copy            */

  struct MSRV_authorization *MD_authorization;  /* list of auth records     */
} ;

/* constants used in the modules: ----------------------------------------- */
#define LINE_SIZE 1024
#define FIELD_SIZE 256

/* prototypes: ------------------------------------------------------------ */
/* msrv01.c */ int msrv_process_requests (FILE *fi, struct MSRV_defaults *msrv_def);
/* msrv02.c */ int msrv_send_dbentry (FILE *f_transcript,
                 struct MSRV_defaults *msrv_def,
                 struct MSRV_request *mrq, char *frame_name);
/* msrv03.c */ struct MSRV_defaults *msrv_get_defaults (char *fnm);
/* msrv04.c */ char *msrv_pick_reply_address (char *from, char *reply_to);
/* msrv05.c */ struct MSRV_authorization *msrv_make_authorization (
                 char *user, char *key);
/* msrv06.c */ int msrv_check_authorization (FILE *f_transcript,
                 struct MSRV_defaults *msd, char *auth);
/* msrv07.c */ int msrv_prepare_reply_header (FILE *fo,
                  struct MSRV_defaults *mdef, struct MSRV_request *mrq);

#endif /* __GG_msrvh__ */
