/*
 *  include FILE <gg/varspace.h>
 *
 *  variable space management
 *  - prototypes
 *  - VAR_SPACE
 *
 *  written:       1994-12-11
 *  latest update: 1995-11-25
 *
 */

#ifndef __GG_varspace__
#define __GG_varspace__

#include <gg/floskel.h>
#include <gg/signatur.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
#define MAX_VAR_SPACE_LEVELS 100        /* only where splitting is done     */

/* ------------------------------------------------------------------------ */
struct VAR_SPACE
{
  long VS_signature;                    /* SIG_VS_NODE */
  long VS_type;
  void *VS_value;
  struct YTREE *VS_array;
} ;

/* prototypes: ------------------------------------------------------------ */
/* varsp001.c */ struct VAR_SPACE *cdecl vs_get_record (
                   struct YTREE **yt_root, char *vsp_name [], int vsp_cnt);
/* varsp002.c */ struct VAR_SPACE *cdecl vs_get (
                   struct YTREE *yt_root, char *vsp_name [], int vsp_cnt);
/* varsp003.c */ struct VAR_SPACE *cdecl vs_set (
                   struct YTREE **yt_root, char *vsp_name [], int vsp_cnt,
                   long vsp_type, long vsp_value);
/* varsp004.c */ struct VAR_SPACE *cdecl vs_set_array (
                   struct YTREE **yt_root, char *vsp_name [], int vsp_cnt,
                   struct YTREE *vsp_array);
/* varsp005.c */ int cdecl vs_assign (struct YTREE **yt_root, char *var_name,
                    long value, long var_type, int split_char);
/* varsp006.c */ long cdecl vs_increment (struct YTREE **yt_root,
                   char *var_name, long value, int pre_post, int split_char);
#ifdef _FILE_DEFINED
/* varsp007.c */ int cdecl vs_operations (struct YTREE **ytpp,
                   FILE *fi, FILE *fo);
#endif /* _FILE_DEFINED */
/* varsp008.c */ struct VAR_SPACE *cdecl vs_query (struct YTREE *yt_root,
                   char *var_name, int split_char);

#endif /* __GG_varspace__ */
