/*
 *  This module is intended to test how getcwd behaves on
 *  differen operating systems.
 *
 *  The synopsis for this function is:
 *  char *getcwd (char *buffer, size_t size);
 *
 *  AIX allowd buffer to be NULL, however size must be specified
 *  FreeBSD allows buffer= NULL and size= 0
 *
 *  $Id: t_getcwd.c,v 1.3 2004/05/08 15:43:20 gonter Exp $
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/param.h>

int main (int argc, char *argv [])
{
  char *buffer= (char *) 0;

  buffer= getcwd (NULL, 0);
  fprintf (stderr, "size=0 :: buffer=%08lX '%s' errno=%d\n", buffer, buffer, errno);
  buffer= getcwd (NULL, MAXPATHLEN);
  fprintf (stderr, "size=MAXPATHLEN :: buffer=%08lX '%s' errno=%d\n", buffer, buffer, errno);

  return 0;
}
