/*
 *  include FILE <gg/syncfsh.h>
 *
 *  - constants: design, other
 *  - structures: SFS_RECORD, SFS_FILESYSTEM, SFS_GLOBAL
 *  - prototypes
 *
 *  written:       1994-02-12
 *  latest update: 1998-07-19 10:43:10
 *  $Id: syncfsh.h,v 1.2 2002/01/22 03:09:53 gonter Exp $
 *
 */

#ifndef __GG_syncfs__
#define __GG_syncfs__

#include <gg/floskel.h>
#include <gg/ytree.h>

/* design constants: ------------------------------------------------------ */
#define N_COMPDIRS          10  /* max number of HOST systems to compare    */
#define N_MATCH_TABLE       64  /* The maximum number of different match    */
                                /* patterns or regular expressions to test  */
                                /* filename against in order to find out if */
                                /* the file should actually be examined.    */
#define MAX_NUM_FS         128  /* number of different filesystems to be    */
                                /* specified for checking explicitly.       */

#define LINE_SIZE 1024
#ifdef MSDOS
#define FNM_SIZE   256
#else
#define FNM_SIZE  1024
#endif /* !MSDOS */

/* other constants: ------------------------------------------------------ */
#define SFS_TEST             1  /* just check files through                 */
#define SFS_COMPARE          2  /* also compare with other system           */

/* ------------------------------------------------------------------------ */
struct SFS_RECORD               /* description of a single file             */
{                               /* as currently found in the file system    */
  char *SFSR_name;              /* name of the file                         */
  char *SFSR_md5;               /* MD5 checksum, if known                   */
  char *SFSR_date;              /* last modification date                   */
  char *SFSR_time;              /* last modification time                   */
  long SFSR_size;               /* actual size of the file                  */

#define SFSF_undef              0x0000
#define SFSF_missing            0x0001
#define SFSF_md5_equal          0x0002
#define SFSF_size_larger        0x0010
#define SFSF_size_smaller       0x0020
#define SFSF_date_newer         0x0100
#define SFSF_date_older         0x0200
#define SFSF_checked            0x4000
  int SFSR_flags [N_COMPDIRS];

  char *SFSR_owner_name;
  char *SFSR_group_name;
  char *SFSR_permissions;
} ;

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
#define _SFS_GLOBAL_DEFINED
struct SFS_GLOBAL
{
  char *SFSG_masterdir;         /* directory where everything happens       */
  char *SFSG_fnm_table;         /* name of sync filesystem table            */
  char *SFSG_environment_id;    /* userid for whom this is happening        */
  char *SFSG_fs [MAX_NUM_FS];   /* name of file system to check             */
  int SFSG_fs_cnt;              /* number of file systems to check (0==all) */

  char *SFSG_compdirs [N_COMPDIRS];
  char *SFSG_systems [N_COMPDIRS];
  int SFSG_compdir_cnt;

  char *SFSG_offer_batch_name;
  char *SFSG_order_batch_name;
  FILE *SFSG_offer_batch_file;
  FILE *SFSG_order_batch_file;
  
  /* various flags:                                                         */
  int SFSG_do_md5;              /* also take MD5 finger prints [DEF: OFF]   */
  int SFSG_recursive;           /* also scan subdirectories [DEF: ON]       */
  int SFSG_verbose_level;       /* to chat or not to chat [DEF: 0]          */
  int SFSG_diagnose_level;      /* [DEF: 0]                                 */
  int SFSG_run_mode;            /* SFS_TEST | SFS_COMPARE                   */
  int SFSG_compact;             /* 1 -> compact table format                */

  /* counter'n'stuff */
  int SFSG_num_ordered;
  int SFSG_num_offered;
} ;

/* ------------------------------------------------------------------------ */
#define _SFS_FILESYSTEM_DEFINED
struct SFS_FILESYSTEM
{
  struct SFS_GLOBAL *SFSF_global;

  char *SFSF_file_system;
  char *SFSF_working_dir;
  int SFSF_path_length;

  char *SFSF_patterns [N_MATCH_TABLE];
  int SFSF_num_patterns;
  int SFSF_match_counter [N_MATCH_TABLE]; /* statistics ... */

  /* various flags: inherited from SFS_GLOBAL and subsequently adapted      */
  int SFSF_do_md5;              /* also take MD5 finger prints [DEF: OFF]   */
  int SFSF_recursive;           /* also scan subdirectories [DEF: ON]       */
  int SFSF_verbose_level;       /* to chat or not to chat [DEF: 0]          */
  int SFSF_diagnose_level;      /* [DEF: 0]                                 */
  int SFSF_run_mode;            /* SFS_TEST | SFS_COMPARE                   */

  char *SFSF_cks2;
  FILE *SFSF_Fcks2;

  /* counter'n'stuff */
  int SFSF_num_ordered;         /* number of files ordered in this fs       */
  int SFSF_num_offered;         /* number of files offered from this fs     */
  int SFSF_num;                 /* currently checked filesystem number      */
  char *SFSF_sysname;           /* not malloc'ed !!! */

  struct YTREE *SFSF_recs;
} ;
#endif /* _FILE_DEFINED */

/* prototypes ------------------------------------------------------------- */
#ifdef _SFS_GLOBAL_DEFINED
/* syncfsb.c  */ int cdecl syncfs_file_handler (char *fn, void *cd);
                 int cdecl syncfs_dir_enter (char *fn, void *cd);
                 int cdecl syncfs_dir_leave (char *fn, void *cd);
/* syncfs01.c */ int cdecl syncfs_table (struct SFS_GLOBAL *sfsg);
/* syncfs02.c */ int cdecl syncfs_check (struct SFS_FILESYSTEM *f, char *fn,
                   char *date_str, char *time_str, long file_size);
/* syncfs03.c */ int cdecl syncfs_record (struct SFS_FILESYSTEM *sfsf,
                   char *fn, long size,
                   char *f_date, char *f_time, char *md5_string);
/* syncfs04.c */ struct SFS_GLOBAL *cdecl sfs_new_global_descriptor (void);
/* syncfs05.c */ struct SFS_FILESYSTEM *cdecl sfs_new_filesystem_descriptor (
                   struct SFS_GLOBAL *gd);
/* syncfs06.c */ int cdecl sfs_free_filesystem_descriptor (
                   struct SFS_FILESYSTEM *fs);
/* syncfs07.c */ int cdecl syncfs_set_pattern (
                   struct SFS_FILESYSTEM *sfsf, char *p);
/* syncfs08.c */ int cdecl syncfs_offer_batch (
                   struct SFS_FILESYSTEM *sfsf, char *fn);
/* syncfs09.c */ int cdecl syncfs_order_batch (
                   struct SFS_FILESYSTEM *sfsf, char *fn);
/* syncfs10.c */ int cdecl syncfs_set_workdir (struct SFS_FILESYSTEM *sfsf,
                   char *wd, char *fsnm);
/* syncfs11.c */ int cdecl syncfs_close_workdir (struct SFS_FILESYSTEM *sfsf);
/* syncfs12.c */ int syncfs_set_system (struct SFS_GLOBAL *sfsg,
                   char *sys, char *compdir);
/* syncfs13.c */ int cdecl syncfs_free_all_records (
                   struct SFS_FILESYSTEM *sfsf);
/* syncfs14.c */ struct SFS_RECORD *cdecl syncfs_find_record (
                   struct SFS_FILESYSTEM *sfsf, char *fn);
/* syncfs15.c */ int cdecl syncfs_compare_records (
                   struct SFS_FILESYSTEM *sfsf);
/* syncfs16.c */ int cdecl syncfs_compare (struct SFS_FILESYSTEM *sfsf,
                   char *fsnm, int num);
/* syncfs17.c */ int cdecl syncfs_free_one_record (struct YTREE *yt,
                   void *client_data);
/* syncfs18.c */ int cdecl syncfs_offer_remaining_files (struct YTREE *yt,
                   void *ct);

/* DEBUGGING: ------------------------------------------------------------- */
#define DEB_FREE() /* { fprintf (stderr, "%s %d\n", __FILE__, __LINE__); } */

#endif /* _SFS_GLOBAL_DEFINED */

#endif /* __GG_syncfs__ */
