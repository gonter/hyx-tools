/*
 *  FILE %ned/07/ned0705.c
 *
 *  return pointer to buffer control structure
 *
 *  written:       1997-03-31
 *  latest update: 1999-12-19 15:16:19
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

#define NUM_NED_BUFFER 128
static struct NED_BUFFER **buffer_list= (struct NED_BUFFER **) 0;

/* ------------------------------------------------------------------------ */
struct NED_BUFFER *ned_get_buffer (int buffer_id, int alloc)
/* heavily based on ned_get_marker (...) */
{
  if (buffer_id <= 0x00 || buffer_id >= NUM_NED_BUFFER) buffer_id= 0;
  if (buffer_id == 0x00) alloc= 1;

  if (buffer_list == (struct NED_BUFFER **) 0 && alloc)
    buffer_list= calloc (sizeof (struct NED_BUFFER *), NUM_NED_BUFFER);

  if (buffer_list != (struct NED_BUFFER **) 0)
  {
    struct NED_BUFFER *bu;

    if ((bu= buffer_list [buffer_id]) == (struct NED_BUFFER *) 0 && alloc)
      bu= buffer_list [buffer_id]= calloc (sizeof (struct NED_BUFFER), 1);

    return bu;
  }

  return (struct NED_BUFFER *) 0;
}
