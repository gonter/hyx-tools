/*
 *  FILE %sgml/chksgml4.c
 *
 *  Identify (analyze) tags and entities, count them and report
 *
 *  written:       1991 07 14
 *                 1992 12 08: revision
 *  latest update: 1999-04-24 11:59:38
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int analyze_tag (
char *tag,
int *tag_code,
struct HYX_OBJECT_COUNTER **x_app,
int *frame_state)
{
  struct HYX_OBJECT_COUNTER *x;
  char *cp;
  int rv= 0;
  int tagl= 0;
  int rc;

  *tag_code= 0;
  for (cp= tag;; cp++, tagl++)
    if (*cp == 0 || *cp == ' ' || *cp == 0x09 || *cp == 0x0A || *cp == 0x0D)
      break;

  /* check if it's a frame open */
  if ((strncmp (tag, "Frame", tagl) == 0 && tagl == 5)
    ||(strncmp (tag, "hyx.f", tagl) == 0 && tagl == 5)
    ||tag [0] == ':')
  {
    rv= (*frame_state == 1) ? 1 : 3;
    *frame_state= 1;
    *tag_code= (tag [0] == ':') ? TAGso_Frame : TAGo_Frame;
  }

  /* check if it's a frame close */
  if ((strncmp (tag, "/Frame", tagl) == 0 && tagl == 6)
    ||(strncmp (tag, "/hyx.f", tagl) == 0 && tagl == 6)
    ||tag [0] == ';')
  {
    if (*frame_state == 0) rv= 2;
    *frame_state= 0;
    *tag_code= (tag [0] == ';') ? TAGsc_Frame : TAGc_Frame;
  }

  /* increment counters for that tag */
  for (;
       (x= *x_app) != (struct HYX_OBJECT_COUNTER *) 0;
       x_app= &x->HOC_next)
  {
    rc= strncmp (x->HOC_str, tag, tagl);
    if ((rc == 0 && x->HOC_str[tagl] == 0)
      ||(x->HOC_str[0] == ':' && tag[0] == ':')
      ||(x->HOC_str[0] == ';' && tag[0] == ';'))
    {
      x->HOC_cnt1++;
      x->HOC_cnt2++;
      return rv;
    }
    if (rc > 0) break;
  }

  /* create a new counter record for the tag */
  if (tag [0] == ':' || tag [0] == ';') tagl= 1;

  if ((x= (struct HYX_OBJECT_COUNTER *)
          calloc (sizeof (struct HYX_OBJECT_COUNTER), 1))
      == (struct HYX_OBJECT_COUNTER *) 0) return -1;

#ifdef _OLD_
  if ((x->HOC_str= malloc (tagl+1)) == (char *) 0) return -1;
  memcpy (x->HOC_str, tag, tagl);           /* strdup() is not appropriate      */
  x->HOC_str[tagl]= 0;
#else
  if ((x->HOC_str= strndup (tag, tagl)) == (char *) 0) return -1;
#endif

  x->HOC_cnt1= 1L;
  x->HOC_cnt2= 1L;
  x->HOC_next= *x_app;
  *x_app= x;

  return rv;
}
