/*
 *  File %dpp/codes/cs105.c
 *
 *  CS_ET8: entity translation functions
 *
 *  written:       1995-12-10: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdlib.h>
#include <gg/fileio.h>
#include <gg/strings.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
char *cs_et8_code2entity (struct CS_ET8 *et8, int ch)
{
  long rc;
  long offset;
  long *index;
  char *strings;
  long string_size;
  char *entity_name= (char *) 0;

  if (et8 == (struct CS_ET8 *) 0
      || et8->CS_et8_error_flag != 0    /* table can't be used!             */
      || ch < 0x00
      || ch > 0xFF
     )
    goto END;

  /* load translation tables now if they are not already loaded */
  if ((index= et8->CS_et8_index) == (long *) 0)
  {
    rc= read_file2buffer ((char **) &et8->CS_et8_index,
                          et8->CS_et8_index_fnm, 1024L);

#ifdef DEBUG
    fprintf (stderr, ">>> reading %s -> %ld diag=%d\n",
             et8->CS_et8_index_fnm, rc, gg_diagnose);
#endif

    if (rc == -1L)
    {
      et8->CS_et8_error_flag= 1;
      goto END;
    }
    index= et8->CS_et8_index;
  }

  if ((strings= et8->CS_et8_string_buffer) == (char *) 0)
  {
    string_size= read_file2buffer (&et8->CS_et8_string_buffer,
                                   et8->CS_et8_string_fnm, MAX_CS_ET8_SIZE);

#ifdef DEBUG
    fprintf (stderr, ">>> reading %s -> %ld diag=%d\n", fnm_str, rc, gg_diagnose);
#endif
    if (string_size == -1L)
    {
      et8->CS_et8_error_flag= 2;
      goto END;
    }

    strings= et8->CS_et8_string_buffer;
    et8->CS_et8_string_size= string_size;
  }
  else string_size= et8->CS_et8_string_size;

  offset= index [ch];
#ifdef DEBUG
  fprintf (stderr, ">> offset= 0x%08lX\n", offset);
#endif
  if (offset < 0L || offset >= string_size) goto END;

#ifdef DEBUG
  fprintf (stderr, ">> is %c->%s\n", ch, &strings [offset]);
#endif

  entity_name= &strings [offset];

END:
  if (entity_name == (char *) 0)
  {
    switch (ch)
    {
      case   0: entity_name= "null"; break;
      case '&': entity_name= "amp";  break;
      case '<': entity_name= "lt";   break;
      case '>': entity_name= "gt";   break;
    }
  }

  return entity_name;
}
