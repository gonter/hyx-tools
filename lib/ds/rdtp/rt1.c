/*
 *  FILE %ds/rdtp/rt1.c
 *
 *  written:       1996-04-01
 *  latest update: 1996-06-22  9:25:52
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

#ifdef RTF
#include <gg/rdtp02.h>
#endif /* RTF */

#ifdef SGML
#include <gg/rdtp03.h>
#endif /* SGML */

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv []);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  struct RDTP_GENERATOR *gen= (struct RDTP_GENERATOR *) 0;
  struct RDTP_THREAD *thread;
#ifdef RTF
  struct RTF_BUILDUP *rtf_build;
#endif /* RTF */
#ifdef SGML
  struct SGML_BUILDUP *sgml_build;
#endif /* SGML */
  int i;
  long rc;
  char *arg;
#ifdef DEBUG
  int g;
#endif /* DEBUG */

#ifdef RTF
  gen= rtf_setup_parser ("RTF");
#endif /* RTF */

#ifdef SGML
  gen= sgml_setup_parser ("SGML");
#endif /* SGML */

  rdtp_print_generator (gen, stdout);
  rdtp_generate_transition_table (gen);

#ifdef DEBUG
  for (i= 0; i < 256; i++)
  {
    g= gen->class_table [i];
    printf ("0x%02X: %c %4d\n", i, (i > 0x20 && i < 0x7f) ? i : '.', g);
  }
#endif /* DEBUG */

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    printf ("**********************************************\n");
    printf ("generating thread for file %s\n", arg);

    thread= rdtp_new_thread (gen->class);

#ifdef RTF
    rtf_build= (struct RTF_BUILDUP *) calloc (sizeof (struct RTF_BUILDUP), 1);
    thread->payload= (void *) rtf_build;
#endif /* RTF */

#ifdef SGML
    sgml_build= sgml_initialize_buildup ();
    thread->payload= (void *) sgml_build;
#endif /* SGML */

    rc= rdtp_parse_file (thread, arg, 0L, 0x7FFFFFFFL);
    printf ("file '%s': %ld (0x%04lX) bytes processed\n", arg, rc, rc);

#ifdef RTF
    rtf_print_statistics (thread);
#endif /* RTF */
#ifdef SGML
    sgml_print_statistics (thread);
#endif /* SGML */
  }

  return 0;
}
