/*
 *  include FILE <gg/unify.h>
 *
 *  written:       1991 05 01
 *  latest update: 1994-12-12
 *
 */

#ifndef __GG_unify__
#define __GG_unify__

#include <gg/floskel.h>

/****************************************************************************/
/**                                                                        **/
/**   datastructures and constants                                         **/
/**                                                                        **/
/****************************************************************************/

/* ------------------------------------------------------------------------ */
struct FEATURE_STRUCTURE
{
  struct FEATURE_STRUCTURE *fs_next;
  short fs_sub1;                        /* subsumption flag                 */

  struct FEATURE_STRUCTURE *fs_head;    /* == feature name                  */
  short fs_head_type;                   /* type code for head structure     */
  long  fs_head_prop;
  long  fs_head_weight;

  struct FEATURE_STRUCTURE *fs_tail;    /* == feature value                 */
  short fs_tail_type;                   /* type code for tail structure     */
  long  fs_tail_prop;
  long  fs_tail_weight;
} ;

/* subsumption flags ------------------------------------------------------ */
#define FS_sub_holds            0  /* subsumption relation holds            */
#define FS_sub_feature          1  /* feature not in both structures        */
#define FS_sub_value            2  /* conflicting value                     */
#define FS_sub_type             4  /* unimplented or invalid type           */

/* type codes ------------------------------------------------------------- */
#define FS_type_unknown         0  /* unbound variable                      */
#define FS_type_atomic          1  /* (not used)                            */
#define FS_type_string          2  /* == atomic                             */
#define FS_type_feature         3  /* feature structure                     */
#define FS_type_set             4  /* conjunctive feature structure (set)   */
#define FS_type_pointer         5  /* path in form @name(*)                 */
#define FS_type_number          6  /* additive long integer                 */


/****************************************************************************/
/**                                                                        **/
/**   prototypes for library functions                                     **/
/**                                                                        **/
/****************************************************************************/

/* unify001.c ------------------------------------------------------------- */
struct FEATURE_STRUCTURE *cdecl fs_unify (struct FEATURE_STRUCTURE *fs1,
                                          struct FEATURE_STRUCTURE *fs2);

/* unify002.c ------------------------------------------------------------- */
int cdecl fs_subsumption (struct FEATURE_STRUCTURE *fs1,
                          struct FEATURE_STRUCTURE *fs2);

/* unify003.c ------------------------------------------------------------- */
#ifdef _FILE_DEFINED
int cdecl fs_print_feature_structure (FILE *fo, struct FEATURE_STRUCTURE *fs,
                                   struct FEATURE_STRUCTURE *root,
                                   int indent, int flags, int list);
int cdecl fs_print_feature_element (FILE *fo, int fe_type,
      struct FEATURE_STRUCTURE *fe, struct FEATURE_STRUCTURE *root,
      int indent, int flags);
#endif

/* unify004.c ------------------------------------------------------------- */
#ifdef _FILE_DEFINED
int cdecl fs_scan (FILE *fi, FILE *err, struct FEATURE_STRUCTURE **act,
                   int act_mode, int list_mode);
#define SCAN_error   -1
#define SCAN_EOS      0         /* End-of-Structure */
#define SCAN_EOF      1
#endif

/* unify005.c ------------------------------------------------------------- */
struct FEATURE_STRUCTURE *cdecl fs_allocate_FEATURE_STRUCTURE (void);

/* unify006.c ------------------------------------------------------------- */
struct FEATURE_STRUCTURE *cdecl fs_trace_path (struct FEATURE_STRUCTURE *fs,
                                            char *path);

/* unify007.c ------------------------------------------------------------- */
int cdecl fs_mbq (char *s);

/* unify008.c ------------------------------------------------------------- */
struct FEATURE_STRUCTURE *cdecl fs_merge (struct FEATURE_STRUCTURE *fs1,
                                          struct FEATURE_STRUCTURE *fs2);

#endif /* __GG_unify__ */
