/*
 *  FILE ~/usr/sgml/sgml0013.c
 *
 *  Identifikation von Tags
 *
 *  written:       1991 03 12: aus sgml0006.c isoliert
 *  latest update: 1999-04-25 16:41:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/sgml.h>

/* ------------------------------------------------------------------------ */
static struct SGML_LIST *built_in_tags = (struct SGML_LIST *) 0;
static struct SGML_LIST *new_tags = (struct SGML_LIST *) 0;

static int initialized=0;

/* ------------------------------------------------------------------------ */
#ifdef TeX_VERSION
#  define CNT_predefined_tags 54
#else
#  define CNT_predefined_tags 31
#endif

static struct SGML_TAG predefined_tags [CNT_predefined_tags] =
{
  { SIG_TAG, SGML_TAG_frame,      "Frame" } ,
  { SIG_TAG, SGML_TAG_endframe,   "/Frame" } ,
  { SIG_TAG, SGML_TAG_Sframe,     ":" } ,
  { SIG_TAG, SGML_TAG_Sendframe,  ";" } ,
  { SIG_TAG, SGML_TAG_if,         "if" } ,
  { SIG_TAG, SGML_TAG_else,       "else" } ,
  { SIG_TAG, SGML_TAG_endif,      "endif" } ,
  { SIG_TAG, SGML_TAG_switch,     "switch" } ,
  { SIG_TAG, SGML_TAG_case,       "case" } ,
  { SIG_TAG, SGML_TAG_default,    "default" } ,
  { SIG_TAG, SGML_TAG_break,      "break" } ,
  { SIG_TAG, SGML_TAG_endswitch,  "endswitch" } ,
  { SIG_TAG, SGML_TAG_set,        "set" } ,
  { SIG_TAG, SGML_TAG_paragraph,  "p" } ,
  { SIG_TAG, SGML_TAG_endparagraph,"/p" } ,
  { SIG_TAG, SGML_TAG_Link,       "Link" } ,
  { SIG_TAG, SGML_TAG_endLink,    "/Link" } ,
  { SIG_TAG, SGML_TAG_Ref,        "Ref" } ,
  { SIG_TAG, SGML_TAG_endRef,     "/Ref" } ,
  { SIG_TAG, SGML_TAG_verbatim,        "verbatim" } ,
  { SIG_TAG, SGML_TAG_endverbatim,     "/verbatim" } ,
  { SIG_TAG, SGML_TAG_FrAttr,     "FrAttr" } ,
  { SIG_TAG, SGML_TAG_SIG1,       "SGML/TS00" } ,
  { SIG_TAG, SGML_TAG_SIG2,       "SGML/TS00/HYX" } ,
  { SIG_TAG, SGML_TAG_typographic,"typographic" } ,
  { SIG_TAG, SGML_TAG_link,       "link" } ,
  { SIG_TAG, SGML_TAG_endlink,    "/link" } ,
  { SIG_TAG, SGML_TAG_name,       "name" } ,
  { SIG_TAG, SGML_TAG_endname,    "/name" } ,
  { SIG_TAG, SGML_TAG_reference,  "reference" } ,
  { SIG_TAG, SGML_TAG_endreference,"/reference" }
#ifdef TeX_VERSION
, { SIG_TAG, SGML_TAG_Titel,      "Titel" } ,
  { SIG_TAG, SGML_TAG_endTitel,   "/Titel" } ,
  { SIG_TAG, SGML_TAG_Hervorhebung,"Hervorhebung" } ,
  { SIG_TAG, SGML_TAG_endHervorhebung,"/Hervorhebung" } ,
  { SIG_TAG, SGML_TAG_OverheadText,           "Overhead-Text" } ,
  { SIG_TAG, SGML_TAG_endOverheadText,           "/Overhead-Text" } ,
  { SIG_TAG, SGML_TAG_Definition,   "Definition" } ,
  { SIG_TAG, SGML_TAG_endDefinition, "/Definition" } ,
  { SIG_TAG, SGML_TAG_Formel,     "Formel" } ,
  { SIG_TAG, SGML_TAG_endFormel,  "/Formel" } ,
  { SIG_TAG, SGML_TAG_Gleichung,  "Gleichung" } ,
  { SIG_TAG, SGML_TAG_endGleichung, "/Gleichung" } ,
  { SIG_TAG, SGML_TAG_Tabelle,    "Tabelle" } ,
  { SIG_TAG, SGML_TAG_endTabelle, "/Tabelle" } ,
  { SIG_TAG, SGML_TAG_BodyText,   "Body-Text" } ,
  { SIG_TAG, SGML_TAG_endBodyText,"/Body-Text" } ,
  { SIG_TAG, SGML_TAG_slant,   "slant" } ,
  { SIG_TAG, SGML_TAG_endslant,"/slant" } ,
  { SIG_TAG, SGML_TAG_Tex,        "Tex" } ,
  { SIG_TAG, SGML_TAG_quote,      "quote" } ,
  { SIG_TAG, SGML_TAG_endquote,   "/quote" } ,
  { SIG_TAG, SGML_TAG_note,       "note" } ,
  { SIG_TAG, SGML_TAG_endnote,    "/note" }
#endif
} ;

/* ------------------------------------------------------------------------ */
void initialize_sgml_0013 ()
{
  struct SGML_LIST *sl;
  int i;

  initialized=1;
  for (i=0;i<CNT_predefined_tags;i++)
  {
    sl= (struct SGML_LIST *) calloc (sizeof (struct SGML_LIST), 1);
    sl->sig = SIG_LIST;
    sl->car=&(predefined_tags[i]);
    sl->cdr=built_in_tags;
    built_in_tags=sl;
  }
}

/* ------------------------------------------------------------------------ */
struct SGML_TAG *get_sgml_tag (char *tag_name)
{
  struct SGML_TAG  *st;
  struct SGML_LIST *sl;
  char *nm;

  if (initialized==0) initialize_sgml_0013 ();

  for (sl  = built_in_tags;
       sl != (struct SGML_LIST *) 0;
       sl  = sl->cdr)
  {
    if (strcmp (((struct SGML_TAG *) sl->car)->sgml_tag_name, tag_name) == 0)
       return sl->car;
  }

  for (sl  = new_tags;
       sl != (struct SGML_LIST *) 0;
       sl  = sl->cdr)
  {
    if (strcmp (((struct SGML_TAG *) sl->car)->sgml_tag_name, tag_name) == 0)
       return sl->car;
  }

  if ((nm= calloc (strlen (tag_name) + 1, 1)) == (char *) 0)
    return (struct SGML_TAG *) 0;
  strcpy (nm, tag_name);

  st= (struct SGML_TAG *) calloc (sizeof (struct SGML_TAG), 1);
  st->sig= SIG_TAG;
  st->sgml_tag_name= nm;

  sl= (struct SGML_LIST *) calloc (sizeof (struct SGML_LIST), 1);
  sl->sig= SIG_LIST;
  sl->car= st;
  sl->cdr= new_tags;
  new_tags=sl;

  return st;
}
