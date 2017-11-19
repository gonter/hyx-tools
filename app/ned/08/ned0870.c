/*
 *  FILE %ned/08/ned0870.c
 *
 *  note cluster: used to contain frames related to a thematic complex
 *  examples: start, help and notes cluster
 *
 *  T2D:
 *  1. DEF_SYMS and DEF_CLUSTER could be slashed into one structure
 *     a. freeing the complete note-tree with statically allocated
 *        nodes
 *
 *  written:       1991 09 25
 *  latest update: 1999-04-25 16:33:51
 *  $Id: ned0870.c,v 1.3 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct DEF_SYMS
{
  char *symbolic;
  char *cluster;
  char *tag;
  int create_mode;
  int memorize;
} ;

/* ------------------------------------------------------------------------ */
struct DEF_CLUSTER
{
  char *symbolic;
  char *cluster;
  int create_mode;
  int memorize;
} ;

/* ------------------------------------------------------------------------ */
/* predefined note clusters */
#define N_DEF_SYMS 8
static struct DEF_SYMS def_syms [N_DEF_SYMS]=
{
  { "start",    "%cl0", "hyx.l cl=\"%cl0\"", 0, 0 },
  { "help",     "%cl1", "hyx.l cl=\"%cl1\"", 0, 0 },
  { "manuals",  "%cl2", "hyx.l cl=\"%cl2\"", 0, 0 },
  { "docs",     "%cl3", "hyx.l cl=\"%cl3\"", 0, 0 },
  { "notes",    "%cl4", "hyx.l cl=\"%cl4\"", 1, 1 },
  { "cal",      "%cal", "hyx.l cl=\"%cal\"", 0, 0 },

  { "today",    "%cal", "hyx.l cl=\"%cal\" fr=\"$$today\"", 0, 0 },
  /* NOTE: pico_help must be the last entry */
  { "pico_help","%cl1", "hyx.l cl=\"%cl1\" fr=\"pico_help\"", 0, 0 },
} ;

/* ------------------------------------------------------------------------ */
static struct YTREE *yt_clusters= (struct YTREE *) 0;

/* ------------------------------------------------------------------------ */
void p_activate_cl0 ()
{
  ned_symbolic_bookmark (def_syms [0].symbolic, 0);
}

void p_activate_cl1 ()
{
  ned_symbolic_bookmark (def_syms [1].symbolic, 0);
}

void p_activate_cl2 ()
{
  ned_symbolic_bookmark (def_syms [2].symbolic, 0);
}

void p_activate_cl3 ()
{
  ned_symbolic_bookmark (def_syms [3].symbolic, 0);
}

void p_activate_cl4 ()
{
  ned_symbolic_bookmark (def_syms [4].symbolic, 0);
}

void pico_help ()
{
  ned_symbolic_bookmark (def_syms [N_DEF_SYMS-1].symbolic, 0);
}

/* ------------------------------------------------------------------------ */
int ned_activate_note_cluster (char *buffer)
{
  char *b2;
  char *fields[2];

  if ((b2= strdup (buffer)) != (char *) 0)
  {
    fields [1]= (char *) 0; /* who knows, maybe it is 0xdeadbeef */

    if (isolate_tokens (buffer, fields, 2) >= 1)
    {
      char *cluster;
      int i;
      int create_mode= -1;
      int memorize= 0;

      cluster= fields [0];

      for (i= strlen (cluster)-1; i>=0; i--)
      { /* interpret note options */
        switch (cluster [i])
        {
          case '!': create_mode= 1; break;
          case '?': memorize= 1;    break;
          default: goto DONE;
        }
        cluster [i]= 0;
      }

DONE:
      if (ned_find_note_cluster (cluster, fields [1], create_mode, memorize)
          == 0) return 0;
    }
  }
  return -1;
}

/* ------------------------------------------------------------------------ */
int ned_find_note_cluster (
const char *sym_cluster,
const char *frame,
int create_mode,
int memorize)
{
  struct DEF_CLUSTER *dc;

  if (sym_cluster == (char *) 0
      || (dc= (struct DEF_CLUSTER *) ytree_get_value (yt_clusters,
            (unsigned char *) sym_cluster)
         ) == (struct DEF_CLUSTER *) 0
     ) return -1;

  if (memorize || dc->memorize) ned_memorize_location ();

  if (create_mode == -1) create_mode= dc->create_mode;

  if (ned_activate_special (dc->cluster, frame, create_mode)
         == (struct FRAMECTRL *) 0
     ) return -1;

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_define_note_cluster (
const char *symbolic,
const char *cluster,
int create_mode,
int memorize)
{
  struct DEF_CLUSTER *dc;

  if ((dc= (struct DEF_CLUSTER *) calloc (sizeof (struct DEF_CLUSTER), 1))
           == (struct DEF_CLUSTER *) 0
       || (dc->symbolic= strdup (symbolic)) == (char *) 0
       || (dc->cluster=  strdup (cluster))  == (char *) 0
      ) return -1;

  dc->create_mode= create_mode;
  dc->memorize= memorize;

  ytree_set_value (&yt_clusters, (unsigned char *) symbolic, (long) dc);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_init_sym_bookmarks ()
{
  int i;

  for (i= 0; i < N_DEF_SYMS; i++)
  {
    ned_register_bookmark (def_syms[i].symbolic, (char *) 0, "_INTERNAL",
                           def_syms[i].tag);

    /* T2D: Register Frame als Command */
    ned_define_note_cluster (def_syms[i].symbolic, def_syms[i].cluster,
                             def_syms[i].create_mode, def_syms[i].memorize);
  }

  return 0;
}
