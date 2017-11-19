/*
 *  FILE %sbr/getcdir1.c
 *
 *  written:       1994-08-12
 *  latest update: 1995-12-30
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#include <gg/strings.h>
#endif
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *get_current_directory (char *buffer)
{
#ifdef MSDOS
  if ((buffer= _get_current_directory (buffer)) == (char *) 0)
    return (char *) 0;

  xchange (buffer, '\\', '/');
  to_lower (buffer);

  return buffer;
#else
  return _get_current_directory (buffer);
#endif /* !MSDOS */
}
