/*
 *  include FILE <gg/ckslib.h>
 *
 *  Datenstrukturern fuer Pruefsummen Generator und Pruefer
 *
 *  written:       1989 12 26
 *  latest update: 1999-04-25 11:04:54
 *
 */

#ifndef __GG_ckslib__
#define __GG_ckslib__

#include <gg/floskel.h>
#pragma pack(1)

#define ALLOW_MD5

/* ------------------------------------------------------------------------ */
#define CKS_VERSION                     0x0000
#define FNLEN                           66
#define COMMENT_LENGTH                  50
#define MD5_DIGEST_LENGTH               16
/* Note: COMMENT_LENGTH+MD5_DIGEST_LENGTH == 66 */

#define OPERATION_MODES                 0x0003
#define OPERATION_CHECK_ENTRY           0x0000
#define OPERATION_NEW_ENTRY             0x0001
#define OPERATION_DISPLAY_ENTRY         0x0002
#define OPERATION_DONT_EDIT             0x0010

/* ------------------------------------------------------------------------ */
struct CKSLIB_HEADER                    /* Beginn eines Library Files       */
{                                       /* wird z.Z. nicht geprueft !!!!!!! */
  char ckslib_v1 [4];                   /* CKS-Signature                    */
  int  ckslib_version;                  /* CKS-Version Nummer               */
  char ckslib_dummy [10];               /* reserved                         */
} ;

/* ------------------------------------------------------------------------ */
struct CKSLIB                           /* Eintrag fuer ein geprueftes File */
{                                       /* in der Checksum-Library          */
  char ckslib_path [FNLEN];             /* Pfad des geprueften Files        */
                                        /* Das *sollte* der *vollstaendige* */
                                        /* Pfad inklusive Laufwerks-        */
                                        /* bezeichnung sein!                */
  char ckslib_comment [COMMENT_LENGTH]; /* Freier Kommentar String          */
  char ckslib_md5 [MD5_DIGEST_LENGTH];  /* MD5 message digest block         */

  long ckslib_c0;                       /* CKS: Anfang des Files (4 Bytes)  */
  long ckslib_c1;                       /* CKS: Laenge des Files            */
  long ckslib_c2;                       /* CKS:                             */
  long ckslib_c3;                       /* CKS:                             */
  int  ckslib_c4;                       /* CKS:                             */

  int  ckslib_flags;
#define CKSLF_update    0x01            /* bit 0: update                    */
#define CKSLF_multi     0x02            /* bit 1: multiple entry            */
#define CKSLF_md5       0x04            /* bit 2: md5 string present        */

  int  ckslib_class;                    /*     0: normal                    */
                                        /*     1: Text (Bsp. Config.SYS     */
                                        /*     2: Autopatch (Laenge gleich) */
                                        /*     3: WATCH OUT                 */
} ;

/* ------------------------------------------------------------------------ */
struct VIRUS_TYPES
{
  struct VIRUS_TYPES *next;     /* Listenverkettung                         */
  int   vir_match;              /* Bei Uebereinstimmung gesetzt wenn ...    */
                                /* Bit  0: Laenge exakt                     */
                                /* Bit  1: Laenge im gueltigen Bereich      */
                                /* Bit  2: Filename matcht Typ              */
                                /* Bit  3: (reserved)                       */
                                /* Bit  4: Sequenz matcht                   */
  int   vir_seq_match_count;    /* Zaehler fuer die Anzahl der SEQ-Matches  */
  char *vir_name;               /* Bezeichnung des Virus                    */
  char *vir_type;               /* Befallene Files: *.COM, *.EXE, ..        */
                                /* Virus-Laenge: Zahl der Bytes, um die ein */
                                /*              durch den Virus befallenes  */
                                /*              File verlaengert wird.      */
  long  vir_length1,            /* V-Laenge: exakt oder minimal             */
        vir_length2;            /*          0  oder maximal                 */
  char *vir_action [6];         /* Actions to perform on (infected) file    */
} ;

/* ------------------------------------------------------------------------ */
struct CKS_SEQUENCE
{
  int seq_code;                         /* Virus Code: -1 -> undefiniert    */
  struct CKS_SEQUENCE *seq_next;        /* anderer Code in gleicher Ebene   */
  struct CKS_SEQUENCE *seq_follow;      /* folgender Code der Sequenz       */
  struct VIRUS_TYPES *seq_virus;        /* betroffener Virus                */
  int seq_virus_number;                 /* Nummer der matchend Sequenz      */
} ;

/* prototypes cks.c ------------------------------------------------------- */
void cdecl reset_verbose_mode (void);

/* prototypes ckscomm.c --------------------------------------------------- */
void cdecl comment_reset (void);
void cdecl comment_generate (char *fn, int mode, struct CKSLIB *entry,
                             long check_0, long check_1, long check_2,
                             long check_3, int check_4,
                             unsigned char *md5_digest,
                             char *entry_comment []);
char *cdecl prepare_command_line (int nr, char *action, char *fn);
void cdecl comment_virus_report (FILE *fp, char *fn);
void cdecl comment_init (char *fn);

/* prototypes cksdiag.c --------------------------------------------------- */
int cdecl cks_check_file (char *fnm, char *c0, long *c1, long *c2, long *c3,
                      int *c4, unsigned char *md5_digest);
void cdecl cks_seq_start (void);
void cdecl cks_seq_append_code (int code);
void cdecl cks_seq_last_code (struct VIRUS_TYPES *vt, int seq_cnt);
void cdecl cks_set_rotor_call (long rc, void (*fun)(long));

/* prototypes cksi01.c ---------------------------------------------------- */
void cdecl cks_screen_init (void);
int cdecl edit_entry (int mode, struct CKSLIB *ckslib, long check_0,
                      long check_1, long check_2, long check_3, int check_4,
                      unsigned char *md5_digest,
                      char *comment []);
void cdecl install_menues (void);
void cdecl interactive_wait (long total_size);
void cdecl interactive_rotor (long act_size);
void cdecl interactive_text (char *txt);
void cdecl print_long (int p, int x, int y, int c, char *fmt, long val);

/* prototypes ckslib.c ---------------------------------------------------- */
void cdecl ckslib_reset (void);
int cdecl ckslib_finis (void);
int cdecl ckslib_newlib (char *libname);
int cdecl cks_lookup (char *fn, struct CKSLIB *ckslib);
int cdecl cks_new (struct CKSLIB *ckslib);
int cdecl cks_update (struct CKSLIB *ckslib);
int cdecl open_library (void);

#endif /* __GG_ckslib__ */
