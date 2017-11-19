/*
 *  File %dpp/codes/cs101.c
 *
 *  *** OBSOLOETE ***
 *
 *  entity translation
 *
 *  written:       1992-12-27: g.gonter@ieee.org
 *  latest update: 1995-12-09
 *
 */

#include <stdlib.h>
#include <gg/fileio.h>
#include <gg/filename.h>
#include <gg/codes.h>

/* #define DEBUG */
#ifdef DEBUG
#include <stdio.h>
#include <gg/diagnose.h>
#endif

/* ------------------------------------------------------------------------ */
static int module_uninitialized= 1;
static long *index= (long *) 0;
static char *strings= (char *) 0;
static long string_size;

/* ------------------------------------------------------------------------ */
struct LIST
{
  struct LIST *next;
  char *str;
} ;

static struct LIST *buffer_list= (struct LIST *) 0;

/* ------------------------------------------------------------------------ */
int INIT_get_sgml_entity (char *fnm_idx, char *fnm_str)
{
  long rc;

  if (!module_uninitialized)
  { /* The module had initialized its data objects before.  The */
    /* re-initialization can only be called explicitly, so this */
    /* must be on purpose.  The string table might still be     */
    /* referenced from outside, so this object will be kept.    */

    struct LIST *nl;

    if ((nl= (struct LIST *) calloc (sizeof (struct LIST), 1))
        != (struct LIST *) 0)
    {
      nl->next= buffer_list;
      nl->str= strings;
      buffer_list= nl;
    }

    strings= (char *) 0;  /* a new buffer will be allocated     */
  }

  rc= read_file2buffer ((char **) &index, fnm_idx, 1024L);
#ifdef DEBUG
fprintf (stderr, ">>> reading %s -> %ld diag=%d\n", fnm_idx, rc, gg_diagnose);
#endif
  if (rc == -1L) return -1;
  string_size= read_file2buffer (&strings, fnm_str, 32000L);
#ifdef DEBUG
fprintf (stderr, ">>> reading %s -> %ld diag=%d\n", fnm_str, rc, gg_diagnose);
#endif
  if (string_size == -1L) return -1;

  module_uninitialized= 0;

  return 0;
}

/* ------------------------------------------------------------------------ */
int KILL_get_sgml_entity ()
{
  struct LIST *l;

  if (module_uninitialized) return 0;

  if (index != (long *) 0) free (index);
  if (strings != (char *) 0) free (strings);
  index= (long *) 0;
  strings= (char *) 0;

  while ((l= buffer_list) != (struct LIST *) 0)
  {
    buffer_list= buffer_list->next;
    free (l->str);
    free (l);
  }

  module_uninitialized= 1;

  return 0;
}

/* ------------------------------------------------------------------------ */
char *get_sgml_entity (int ch)
{
  int rc;
  long offset;

  if (ch < 0 || ch > 255) return (char *) 0;
#ifdef DEBUG
fprintf (stderr, ">> convert: 0x%02X %c\n", ch, ch);
#endif

  if (module_uninitialized)
  {
    rc= INIT_get_sgml_entity (
          set_etc_filename ((char *) 0, CSF_PC_INDEX),
          set_etc_filename ((char *) 0, CSF_PC_STRINGS));
    if (rc == -1) return (char *) 0;
  }

  offset= index [ch];
#ifdef DEBUG
fprintf (stderr, ">> offset= 0x%08lX\n", offset);
#endif
  if (offset < 0L || offset >= string_size) return (char *) 0;

#ifdef DEBUG
fprintf (stderr, ">> is %c->%s\n", ch, &strings [offset]);
#endif
  return &strings [offset];
}
