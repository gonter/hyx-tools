/*
 *  include FILE <gg/wildcard.h>
 * 
 *  wildcard processing
 *  - constants
 *  - methods
 *  - structures
 *  - macros
 *  - generic and system specific prototypes
 * 
 *  written:       1996-08-10
 *  latest update: 1999-05-08  9:29:21
 *
 */

#ifndef __GG_wildcard__
#define __GG_wildcard__

#include <gg/floskel.h>

#ifndef __GG_filename__
#include <gg/filename.h>
#endif /* __GG_filename__ */

/* #define __wcrd_debug__ */

/* constants: ------------------------------------------------------------- */
#ifdef __OLD__ /* 1998-07-19 11:13:36 */
#define WCRD_buffer_size        128
#else
#define WCRD_buffer_size       4096
#endif

#define WCRD_drive_buffer         2
#define WCRD_pattern_size        30

#ifndef DEF_FNM_LENGTH
#ifdef MSDOS
#define DEF_FNM_LENGTH 66
#else
#define DEF_FNM_LENGTH 1026
#endif
#define DEF_FNM_EXTRA 24

#ifndef MAX_FNM_LENGTH
#ifdef MSDOS
#define MAX_FNM_LENGTH 66
#else
#define MAX_FNM_LENGTH 1026
#endif
#endif

#endif /* !DEF_FNM_LENGTH */

/* methods: --------------------------------------------------------------- */
typedef int WCRD_processor (char *fnm, void *client_data);

/* structures: ------------------------------------------------------------ */
struct WCRD
{
  /* setup */
  int subdirs;                          /* 1 -> follow subdirectories       */
  int match_mode;                       /* 0 -> use MSDOS's matching mode   */
                                        /* 1 -> use or own matchin mode     */

  /* processors */
  WCRD_processor *dir_pre_processor;    /* called when entering a directory */
  void *dir_pre_client_data;

  WCRD_processor *file_processor;       /* foreach file in a directory      */
  void *file_client_data;

  WCRD_processor *dir_post_processor;   /* called when leaving a directory  */
  void *dir_post_client_data;

  /* runtime data */
  char actual_filenm  [WCRD_buffer_size];
  char actual_path    [WCRD_buffer_size];
  char actual_drive   [WCRD_drive_buffer];
  char actual_pattern [WCRD_pattern_size];
  int actual_index;

  int leave;                            /* number of recursions to leave    */
  int current_level;

} ;

/* macros: ---------------------------------------------------------------- */
#define wcrd2_get_match_mode(wcrd)      (wcrd->match_mode)
#define wcrd2_get_subdirs(wcrd)         (wcrd->subdirs)
#define wcrd2_get_current_level(wcrd)   (wcrd->current_level)
#define wcrd2_new() \
  ((struct WCRD *) calloc (sizeof (struct WCRD), 1))

/* generic prototypes: ---------------------------------------------------- */
int wcrd2_set_match_mode (struct WCRD *wcrd, int mode);
int wcrd2_set_subdirs (struct WCRD *wcrd, int mode);
int wcrd2_leave (struct WCRD *wcrd, int levels);
struct WCRD *wcrd2_initialize (void);
int wcrd2_dispose (struct WCRD *wcrd);
int wcrd2_set_processor (struct WCRD *wcrd, int what,
      WCRD_processor *prc, void *client_data);

#define WCRD_set_file_processor         1
#define WCRD_set_dir_pre_processor      2
#define WCRD_set_dir_post_processor     3

#ifdef __GG_array__
int wcrd2_arguments (struct WCRD *wcrd, struct ARRAY_CONTROL *arguments);
#endif

/* system specific prototypes: (MSDOS and UNIX) --------------------------- */
int wcrd2_rec_wildcards (struct WCRD *wcrd, int lev);
int wcrd2_wildcards_or_rec (struct WCRD *wcrd, char *fn);
int wcrd2_wildcards (struct WCRD *wcrd, char *fn);
int wcrd2_wildcards_search (struct WCRD *wcrd);

#endif /* __GG_wildcard__ */
