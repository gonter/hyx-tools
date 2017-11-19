/*
 *  FILE %ds/bbc/bbc12.c
 *
 *  written:       1995-08-14
 *  latest update: 1995-08-22
 *  $Id: bbc12.c,v 1.2 2003/06/25 10:11:44 gonter Exp $
 *
 */

#include <unistd.h>
#include <gg/bbch.h>

/* ------------------------------------------------------------------------ */
int bbc_to_stdout (
void *client_data,
char *buffer,
int buffer_size)
{
  struct BBC_CONNECTION *bbcc;

  if ((bbcc= (struct BBC_CONNECTION *) client_data)
       == (struct BBC_CONNECTION *) 0) return -1;

  if (write (1, buffer, buffer_size) <= 0)
    bbcc->BBCC_t2d= BBCCt2d_shutdown;

  return 0;
}
