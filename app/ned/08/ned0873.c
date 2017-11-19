/*
 *  FILE %ned/08/ned0873.c
 *
 *  Bookmark Subsystem
 *
 *  written:       1997-08-30
 *  latest update: 1999-04-25 16:33:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <gg/ytree.h>
#include <gg/strings.h>
#include <gg/sbr.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct NED_BOOKMARK
{
  struct NED_BOOKMARK *bmk_next;
  struct NED_BOOKMARK *bmk_next_in_section;

  char *bmk_symbolic_name;
  char *bmk_title;
  char *bmk_section;
  char *bmk_tag_string;
};

/* ------------------------------------------------------------------------ */
struct NED_BOOKMARK_SECTION
{
  struct NED_BOOKMARK *bmk_list;
  struct NED_BOOKMARK **bmk_append;

  char *bmk_section;
};

/* ------------------------------------------------------------------------ */
static struct YTREE *sym_bmk= (struct YTREE *) 0;
static struct YTREE *sections= (struct YTREE *) 0;
static struct NED_BOOKMARK *all_bmk= (struct NED_BOOKMARK *) 0;
static struct NED_BOOKMARK **app_bmk= &all_bmk;

/* ------------------------------------------------------------------------ */
int ned_register_bookmark (
char *symbolic_name,
char *title,
char *section,
char *tag_string)
{
  struct NED_BOOKMARK *bmk;

  if (tag_string == (char *) 0 || *tag_string == 0
      || (bmk= (struct NED_BOOKMARK *)
               calloc (sizeof (struct NED_BOOKMARK), 1))
             == (struct NED_BOOKMARK *) 0
     ) return -1;

  str_assign (&bmk->bmk_symbolic_name, symbolic_name);
  str_assign (&bmk->bmk_title,      title);
  str_assign (&bmk->bmk_section,    section);
  str_assign (&bmk->bmk_tag_string, tag_string);

  *app_bmk= bmk;
  app_bmk= &bmk->bmk_next;

  if (section != (char *) 0 && *section)
  {
    struct NED_BOOKMARK_SECTION *sec_bmk;

    if ((sec_bmk= (struct NED_BOOKMARK_SECTION *)
                  ytree_get_value (sections, (unsigned char *) section))
             == (struct NED_BOOKMARK_SECTION *) 0)
    {
      if ((sec_bmk= (struct NED_BOOKMARK_SECTION *)
                     calloc (sizeof (struct NED_BOOKMARK_SECTION), 1))
           != (struct NED_BOOKMARK_SECTION *) 0)
        sec_bmk->bmk_append= &sec_bmk->bmk_list;
    }

    if (sec_bmk != (struct NED_BOOKMARK_SECTION *) 0)
    {
      *(sec_bmk->bmk_append)= bmk;
      sec_bmk->bmk_append= &bmk->bmk_next_in_section;
    }
  }

  if (symbolic_name != (char *) 0 && *symbolic_name)
    ytree_set_value (&sym_bmk, (unsigned char *) symbolic_name, (long) bmk);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_load_bookmarks (char *filename, char *section)
{
  FILE *fi;
  char *bu;
  int rc;
#define bu_siz 1024
#define N_FIELDS 3
  char *fields [N_FIELDS];

  if (filename == (char *) 0
      || *filename == (char) 0
      || (fi= fopen (filename, "rb")) == (FILE *) 0
      || (bu= malloc (bu_siz)) == (char *) 0
     )
    return -1;

  for (;;)
  {
    rc= fread_line (fi, bu, bu_siz);
    if (rc < 0 && feof (fi)) break;

    /* T2D: format should be defined */
    rc= split_string (bu, ':', fields, N_FIELDS);
    ned_register_bookmark (fields [0], fields [1], section, fields [2]);
  }
  fclose (fi);
  free (bu);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_save_bookmarks (char *filename, char *section)
{
  fprintf (stderr, "0873: T2D saving bookmarks not yet implemented!\n");
  fprintf (stderr, "  bookmarks for %s not saved to %s\n", section, filename);
  return -1;
}

/* ------------------------------------------------------------------------ */
int ned_symbolic_bookmark (char *name, int option)
{
  struct NED_BOOKMARK *bmk;

  if (name != (char *) 0 && *name
      && (bmk= (struct NED_BOOKMARK *)
           ytree_get_value (sym_bmk, (unsigned char *) name))
      && ned_eval_string (bmk->bmk_tag_string, option) == 0
     )
    return 0;

  return -1;
}
