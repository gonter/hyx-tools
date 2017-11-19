/*
 *  include FILE <gg/attlist.h>
 *
 *  attribute list management
 *
 *  written:       1994-03-26
 *  latest update: 1997-11-09 10:59:53
 *  $Id: attlist.h,v 1.2 2002/05/02 06:48:29 gonter Exp $
 *
 */

#ifndef __GG_attlist__
#define __GG_attlist__

#include <gg/floskel.h>

/* ------------------------------------------------------------------------ */
struct ATTRIBUTE_LIST
{
  struct ATTRIBUTE_LIST *AL_next;
  char *AL_name;                /* attribute name                           */
  char *AL_attl;                /* attribute list for an attribute          */
  long  AL_type;                /* ... maybe this should be a pointer too   */
  void *AL_value;               /* attribute value                          */
} ;

#define ALty_void       0       /* no AL_value                              */
#define ALty_attlist    1       /* AL_value points again to an ATTLIST      */
#define ALty_string     2       /* AL_value points to a string              */
#define ALty_string_dup 3       /* strdup'ed string                         */
#define ALty_opaque     4       /* points to any other value                */
#define ALty_long       5       /* numeric long value                       */

/* ------------------------------------------------------------------------ */
struct _ATTL_CTL
{
  struct ATTRIBUTE_LIST *AL_start;
  struct ATTRIBUTE_LIST **AL_append;
};

typedef struct _ATTL_CTL ATTLIST;

/* prototypes: ------------------------------------------------------------ */
/* attl0001.c */ struct ATTRIBUTE_LIST *cdecl al_create_attribute (
                   char *name, char *attl, long type, void *value);
/* attl0002.c */ struct ATTRIBUTE_LIST **cdecl al_getp_attribute (
                   struct ATTRIBUTE_LIST **alp, char *name);
/* attl0003.c */ struct ATTRIBUTE_LIST *cdecl al_set_attribute (
                   struct ATTRIBUTE_LIST **alp,
                   char *name, char *attl, long type, void *value);
/* attl0004.c */ struct ATTRIBUTE_LIST *cdecl al_find_attribute (
                   struct ATTRIBUTE_LIST *al, char *name);
/* attl0005.c */ int cdecl al_find_name (char *name_file, char *first_name,
                   char *nick, struct ATTRIBUTE_LIST *ntl);
/* attl0006.c */ void *cdecl al_find_attribute_value (
                   struct ATTRIBUTE_LIST *al, char *name);

/* attl0008.c */ int al_add_attribute (ATTLIST *al, char *name,
                   char *attl, long type, void *value);
/* attl0009.c */ ATTLIST *new_ATTLIST (void);

#endif /* __GG_attlist__ */
