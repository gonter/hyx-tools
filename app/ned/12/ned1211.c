/*
 *  FILE %ned/12/ned1211.c
 *
 *  written:       1996-07-07
 *  latest update: 1999-04-25 16:36:51
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct NED_FIELD_CONTEXT *ned_create_field_context (
char *buffer,
int buffer_size,
int buffer_mode)
{
  struct NED_FIELD_CONTEXT *fc;
  char *my_buffer;
  int i;

  if ((fc= (struct NED_FIELD_CONTEXT *)
           calloc (sizeof (struct NED_FIELD_CONTEXT), 1))
       != (struct NED_FIELD_CONTEXT *) 0
     )
  {
    if (buffer == (char *) 0) buffer_mode= FCbm_allocate;
    switch (buffer_mode)
    {
      case FCbm_allocate:
        if ((my_buffer= malloc (buffer_size + 1)) != (char *) 0)
        {
          my_buffer [0]= 0;
          buffer_mode= FCbm_dynamic;
        }
        break;

      case FCbm_volatile:
        if ((i= strlen (buffer)) > buffer_size) buffer_size= i;
        if ((my_buffer= malloc (buffer_size + 1)) != (char *) 0)
        {
          strcpy (my_buffer, buffer);
          buffer_mode= FCbm_dynamic;
        }
        break;

      case FCbm_static:
        my_buffer= buffer;
        break;

      case FCbm_dynamic:
        my_buffer= buffer;
        break;

      default:
        return (struct NED_FIELD_CONTEXT *) 0;
    }

    if (my_buffer == (char *) 0)
      return (struct NED_FIELD_CONTEXT *) 0;

    fc->buffer= my_buffer;
    fc->buffer_size= buffer_size;
    fc->buffer_mode= buffer_mode;
  }

  return fc;
}
