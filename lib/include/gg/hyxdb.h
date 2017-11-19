/*
 *  include FILE <gg/hyxdb.h>
 *
 *  declaration of HYX database structures
 *
 *  written:       1996-01-23
 *  latest update: 1997-11-09 11:21:55
 *
 */

#ifndef __GG_hyxdb__
#define __GG_hyxdb__

#include <gg/floskel.h>
#include <gg/array.h>
#include <gg/ytree.h>
#include <gg/hytxt.h>
#include <gg/dyb.h>

/* limits: ---------------------------------------------------------------- */
#define FRAME_NAME_LNG 1024     /* maximum length of a frame name           */
#define HYXDB_BUFFER_SIZE 2048  /* typical size of a HYXDB buffer           */

/* ------------------------------------------------------------------------ */
struct HYXDB_CONTROL
{
  struct HYX_CLUSTER_CONTROL *HYXDB_clc;
  char *HYXDB_database_control;
  long HYXDB_highest_oid;

  struct YTREE *write_cache;
  struct YTREE *read_cache;
  array_element_destructor *element_destructor;

  int buffer_size;
  char *buffer;
} ;

/* ------------------------------------------------------------------------ */
struct HYXDB_OBJECT
{
  char *frame_name;
  long OID;

  struct YTREE *attr;
  array_element_destructor *element_destructor;
} ;

/* ------------------------------------------------------------------------ */
struct HYXDB_VALUE
{
  int format;
#define HYXDB_undef     0
#define HYXDB_string    1
#define HYXDB_binary    2
#define HYXDB_dyb       3
  long size;
  void *value;
} ;

/* prototypes: ------------------------------------------------------------ */
struct HYXDB_CONTROL *hyxdb_new_handle (char *cluster_name, int open_mode);
struct HYXDB_OBJECT *hyxdb_new_object (struct HYXDB_CONTROL *ctrl,
  char *frame_name, long id);
long hyxdb_insert_attribute (struct HYXDB_OBJECT *obj, char *attr_name,
  void *attr_value, int insert_mode);
#define HYXDB_insert  0
#define HYXDB_update  1
#define HYXDB_replace 2

struct ARRAY_CONTROL *hyxdb_get_attribute_values (struct HYXDB_OBJECT *obj,
  char *attr_name);
struct HYXDB_OBJECT *hyxdb_load_object_frame (struct HYXDB_CONTROL *ctrl,
  char *frame_name);
struct HYXDB_OBJECT *hyxdb_parse_stream (struct HYXDB_CONTROL *ctrl,
  FILE *fi, long size, char *frame_name);
struct HYXDB_VALUE *hyxdb_new_value (int format, void *value, long size);

#endif /* __GG_hyxdb__ */
