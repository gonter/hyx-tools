/*
 *  FILE %ds/rdtp/rdtp0110.c
 *
 *  restructured dynamic text parser
 *  analyze state table to create a global character class mapping table
 *
 *  written:       1996-04-02
 *  latest update: 1997-01-15 10:47:27
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

/**** #define DEBUG ****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>

/* ------------------------------------------------------------------------ */
int rdtp_process1_state_table (
struct RDTP_GENERATOR *gen,
struct RDTP_STATE_DEFINITION *st)
{
  struct RDTP_STATE_TRANSITION *t1, *t2;
  int defined_classes= 1;
  int found_class;
  int *local_class_table;
  int i;
  int g, g2, l;
  int class_count= 0;                   /* new number of global classes     */
  struct YTREE *yt_map= (struct YTREE *) 0;
  struct YTREE *yt;
  char pair [20];

  if (gen == (struct RDTP_GENERATOR *) 0
      || st == (struct RDTP_STATE_DEFINITION *) 0
      || !(st->state_used) /* otherwise dont care */
     )
    return 0;

#ifdef DEBUG
  printf (">> GEN state: %s (pass 1)\n", st->state_name);
#endif /* DEBUG */
  
  /* step 1: identify different classes in this state */
  for (t1= st->trans;
       t1 != (struct RDTP_STATE_TRANSITION *) 0;
       t1= t1->next)
  {
#ifdef DEBUG
    rdtp_print_state_entry (stdout, t1, "P1: ");
#endif /* DEBUG */

    /* search for the identical combination of (method,state_to,info) */
    found_class= -1;
    for (t2= st->trans;
         t2 != t1 && t2 != (struct RDTP_STATE_TRANSITION *) 0;
         t2= t2->next)
    {
#ifdef DEBUG
      rdtp_print_state_entry (stdout, t2, "  compare: ");
#endif /* DEBUG */

      if (t1->method == t2->method
          && strcmp (t1->state_to,    t2->state_to)    == 0
          && strcmp (t1->method_info, t2->method_info) == 0 /* TEST */
         )
      {
        found_class= t2->class_code;
        break;
      }
    }

    if (found_class == -1)
    { /* a new class */
#ifdef DEBUG
      printf ("  >> new class %d\n", defined_classes);
#endif /* DEBUG */

      t1->class_code= defined_classes++;
    }
    else
    { /* the same as something before */
#ifdef DEBUG
      printf ("  >> old class %d\n", found_class);
#endif /* DEBUG */

      t1->class_code= found_class;
    }
  }

#ifdef DEBUG
  printf (">> GEN %d classes in total\n", defined_classes);
#endif /* DEBUG */
  if ((local_class_table= calloc (sizeof (int), 256)) == (int *) 0)
  {
    printf (">> GEN can't create temp mapping tables (1)\n");
    return -1;
  }

  /* step 2: colorize full character table */
  for (t1= st->trans;
       t1 != (struct RDTP_STATE_TRANSITION *) 0;
       t1= t1->next)
  {
#ifdef DEBUG
    rdtp_print_state_entry (stdout, t1, "P2: ");
    printf ("  >>> class_code=%d\n", t1->class_code);
#endif /* DEBUG */

    for (i= (int) t1->range_begin; i <= (int) t1->range_end; i++)
    { /* table is arranged from more specific to less specific,             */
      /* if ranges are ambigious                                            */
      if (local_class_table [i] == 0) local_class_table [i]= t1->class_code;
    }
  }

  /* step 3: map local classes onto global class table */
#ifdef DEBUG
  printf ("defined_classes= %d\n", gen->defined_classes);
  printf ("index: . GLOB  LOC\n");
#endif /* DEBUG */

  class_count= 0;
  for (i= 0; i < 256; i++)
  {
    g= gen->class_table [i];
    l= local_class_table [i];
    sprintf (pair, "%02X:%02X", g, l);

#ifdef DEBUG
    printf (" 0x%02X: %c %4d %4d '%s'",
            i,
            (i > 0x20 && i < 0x7f) ? i : '.',
            g, l, pair);
#endif /* DEBUG */

    if ((yt= ytree_insert_word (&yt_map, (unsigned char *) pair))
             == (struct YTREE *) 0)
    {
      printf (">> GEN can't create temp hash table\n");
      ytree_free (yt_map);
      free (local_class_table);
      return -1;
    }

    if (yt->YT_flags & YTflag_EOW)
    {
#ifdef DEBUG
      printf (" ** known combination");
#endif /* DEBUG */
      g2= (int) yt->YT_info;
      gen->class_table [i]= g2;
    }
    else
    { /* new entry */
      g= class_count++;
      gen->class_table [i]= g;

      yt->YT_info= (long) g;
      yt->YT_flags |= YTflag_EOW;

#ifdef DEBUG
      printf (" ** new combination g=%d", g);
#endif /* DEBUG */
    }

#ifdef DEBUG
    printf (" -> g=%d\n", gen->class_table [i]);
#endif /* DEBUG */
  }

  gen->defined_classes= class_count;
  ytree_free (yt_map);
  free (local_class_table);

  return 0;
}
