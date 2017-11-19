/*
 *  include FILE <gg/rfc822.h>
 *
 *  constants, etc., for RFC822 mail processing
 *
 *  written:       1990 12 01
 *                 1991 09 16: revision
 *  latest update: 1997-11-27 19:57:38
 *
 */

#ifndef __GG_rfc822__
#define __GG_rfc822__

/* ------------------------------------------------------------------------ */
#define RFC822_unknown          0
#define RFC822_From             1
#define RFC822_To               2
#define RFC822_Date             3
#define RFC822_Subject          4
#define RFC822_Received         5
#define RFC822_Via              6
#define RFC822_Keywords         7
#define RFC822_Summary          8
#define RFC822_Path             9
#define RFC822_Approved        10
#define RFC822_Approved_By     11
#define RFC822_Newsgroups      12
#define RFC822_Control         13

#define RFC822_continue       101
#define RFC822_blank          102
#define RFC822_sep1           103
#define RFC822_sep2           104
#define RFC822_sep_elm        105

/* delimiter string between messages -------------------------------------- */
#define DELIMIT_NOTEBOOK        0
#define DELIMIT_OCCAM_archive   1
#define DELIMIT_LISTSERV_DB     2
#define DELIMIT_3               3
#define DELIMIT_Love_Hounds     4
#define DELIMIT_card_oldmail    5
#define DELIMIT_Unix            6

/* ------------------------------------------------------------------------ */
struct MAIL_DESCRIPTION
{
  struct MAIL_DESCRIPTION *MD_next;

  struct MAIL_DESCRIPTION *MD_by_addr;
  struct MAIL_DESCRIPTION *MD_by_date;
  struct MAIL_DESCRIPTION *MD_by_subj;

  char *MD_frame;
  char *MD_addr;
  char *MD_date;
  char *MD_subj;
  int MD_cnt;
} ;

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
typedef int BC_REPORT_MAIL (struct BREAKUP_CONTROL *bc, char *fnm, char *s1,
  char *s2, char *s3, int cnt);

#define _BREAKUP_CONTROL_DEFINED
struct BREAKUP_CONTROL
{
  FILE *BC_log;
  FILE *BC_hyx;

  int BC_is_hyx;

  char *BC_fo_name;
  char *BC_new_name;
  char *BC_f_name;
  char *BC_f_type;

  int BC_f_rename_file;
  int BC_delimiter_mode;
  int BC_counter;
  int BC_dummy_lines;
  int BC_remove_lines;

  int BC_use_addr;
  BC_REPORT_MAIL *BC_report_mail;

  struct MAIL_DESCRIPTION *BC_MD_list;
  struct MAIL_DESCRIPTION **BC_MD_append;

  struct YTREE *BC_yt_addr;
  struct YTREE *BC_yt_date;
  struct YTREE *BC_yt_subj;
  char *BC_format;
} ;
#endif

/* ------------------------------------------------------------------------ */
struct RFC822_KEYWORD
{
  unsigned char *kw;
  long code;
} ;

/* ------------------------------------------------------------------------ */
typedef int DB_lookup (char *s, void *cd);

/* ------------------------------------------------------------------------ */
struct MAIL_VERIFY_DB
{
  DB_lookup *spamsites, *spammers, *goodaddr;
  void *cd_spamsites, *cd_spammers, *cd_goodaddr;
} ;

/* prototypes: ------------------------------------------------------------ */
/* mail0001.c */ long RFC822_chk_keyword (char *s, int lng);
                 int RFC822_reg_keyword_table (struct RFC822_KEYWORD *tbl);
                 int RFC822_reg_keyword (unsigned char *kw, long code);
/* mail0002.c */ int cdecl mk_fnm_from_date (char *fnm_string,
                   char *date_string, int normalize);
/* mail0003.c */ int cdecl message_delimiter (char *p, int delim_mode);

#ifdef _FILE_DEFINED
/* mail0004.c */ int cdecl breakup (char *fn, struct BREAKUP_CONTROL *bc);
                 int cdecl close_current_file (struct BREAKUP_CONTROL *bc);
                 int cdecl new_file (struct BREAKUP_CONTROL *bc);
#endif /* _FILE_DEFINED */

/* mail0005.c */ int cdecl record_mails (struct BREAKUP_CONTROL *bc,
                   char *frame, char *addr, char *date, char *subj, int cnt);

#ifdef _YTREE_DEFINED
/* mail0006.c */ int cdecl sort_mail (struct YTREE **ytr,
                   struct MAIL_DESCRIPTION *md,
                   struct MAIL_DESCRIPTION **md_app, char *str);
#endif /* _YTREE_DEFINED */

#ifdef _BREAKUP_CONTROL_DEFINED
/* mail0007.c */ struct BREAKUP_CONTROL *cdecl create_breakup_control (void);
#endif /* _BREAKUP_CONTROL_DEFINED */

#ifdef _FILE_DEFINED
/* mail0008.c */ int cdecl print_mail_description_link (FILE *fo,
                   struct MAIL_DESCRIPTION *md);
/* mail0009.c */ int cdecl print_mail_description_list (FILE *fo,
                   struct MAIL_DESCRIPTION *md, int sort_mode);
#endif /* _FILE_DEFINED */

/* mail0010.c */ int cdecl normalize_date (char *fnm_string,
                    char *date_string, int normalize);

/* spam fight package ----------------------------------------------------- */
/* mail0011.c */ int mail_verify_address (char *addr, int dup,
                   struct MAIL_VERIFY_DB *db);
#define ADDR_ERROR     -1
#define ADDR_OK         0
#define ADDR_SYNTAX     1
#define ADDR_SPAMMER    2
#define ADDR_SPAMSITE   3
#define ADDR_INVALID    4

/* mail0012.c */ int mail_verify_domain_name (char *addr, int dup,
                   struct MAIL_VERIFY_DB *db);
/* mail0013.c */ int mail_valid_tld (char *tld);
/* mail0014.c */ int mail_verify_message_id (char *msgid, int dup,
                   int defocus, struct MAIL_VERIFY_DB *db);

#endif /* __GG_rfc822__ */
