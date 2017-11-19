/*
 *  FILE /usr/sbr/convent4.c
 *
 *  convert typographic characters to SGML entities
 *
 *  1991 11 13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/convent.h>

/* ------------------------------------------------------------------------ */
struct XX
{
  int v;
  char *nm;
} ;

/* ------------------------------------------------------------------------ */
#define xx_siz 5
static struct XX TY_ENTITY_xx [xx_siz] =
{
  { 0x00101, "TYcont" } ,
  { 0x00102, "TYdash" } ,
  { 0x00103, "TYhyph" } ,
  { 0x00104, "TYminus" } ,
  { 0x00105, "TYsp1" }
};

/* ------------------------------------------------------------------------ */
char *get_typographic_sgml_entity (int ch)
{
  int i;

  for (i=0; i<xx_siz; i++)
    if (TY_ENTITY_xx[i].v == ch)
      return TY_ENTITY_xx[i].nm;

  return (char *) 0;
}

/* ------------------------------------------------------------------------ */
int find_typographic_sgml_entity (char *s)
{
  int i;

  if (s == (char *) 0 || *s == 0) return -1;

  for (i=0; i<xx_siz; i++)
    if (strcmp (TY_ENTITY_xx[i].nm, s) == 0)
      return TY_ENTITY_xx[i].v;

  return -1;
}
