/*
 *  $Id: ned0863.c,v 1.4 2002/06/15 04:35:21 gonter Exp $
 *  FILE %ned/08/ned0863.c
 *
 *  preset a feature
 *  see also:  ned0884.c  void ned_set_lookup_tag ()
 *             ned0867.c  void ned_memorize_location ()
 *
 *  T2D: sprintf (str, ..., int); sgml_add_attribute (name, str)
 *       umbauen!
 *
 *  written:       1991 07 05
 *  latest update: 2000-06-05 13:39:41
 *  $Id: ned0863.c,v 1.4 2002/06/15 04:35:21 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/tfb.h>

#include <gg/rdtp.h>
#include <gg/rdtp03.h>

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern char *default_start_frame;

int ned_cb_feature_create (char *str, int size, int malloced, void *cb_data);

/* ------------------------------------------------------------------------ */
extern char *mem_file;
extern char *mem_frame;
extern char *mem_cluster;
extern char *mem_mark;
extern int mem_line;
extern int mem_column;

extern char *default_help_cluster;
extern char *default_help_prompt_attrib;

static char *_hyx_l= "hyx.l";
static char *_tdc=   "tdc";
static char *_tdp=   "tdp";
static char *_mark=  "mark";

/* ------------------------------------------------------------------------ */
struct NED_CF_CB
{
  struct WINDOWCTRL *wc;
  struct LINE *lp;
  int idx;

  int what;
  int rc;
  int ftr_edit_mode;

  int mode;
#define CB_MODE_str     0               /* use str */
#define CB_MODE_ot      1               /* use ot */

  char *name;
  char *str;

  struct SGML_BUILDUP *sgml_build;
  struct SGML_OPENING_TAG *ot;
} ;

/* ------------------------------------------------------------------------ */
int ned_wc_feature_create (
struct WINDOWCTRL *wc,
int what,                               /* type of tag to create            */
int ftr_edit_mode,                      /* FTR_EDIT_*                       */
char *attribute)                        /* if FTR_EDIT_ATTRIBUTE            */
{
  struct LINE *lp;
  void *ptr;
  int ftr_segment_cnt= 0;               /* number of feature parts          */
#define MAX_BUFFER1 160
#define MAX_BUFFER2 16
  char *buffer1a;
  char buffer1b [MAX_BUFFER1];
  char buffer2a [MAX_BUFFER2];
  char *feature_string= (char *) 0;
  char *feature_type= (char *) 0;
  char *hyx_l_attr= _mark;
  struct NED_CF_CB *cb= (struct NED_CF_CB *) 0;
  struct SGML_BUILDUP *sgml_build= (struct SGML_BUILDUP *) 0;
  struct SGML_OPENING_TAG *ot= (struct SGML_OPENING_TAG *) 0;
  struct SGML_ATTRIBUTE_LIST *attr;
  int max_buffer1a;
  int off_buffer1a;

  if (wc == (struct WINDOWCTRL *) 0
      || (lp= wc->WC_act) == (struct LINE *) 0
      || (cb= calloc (sizeof (struct NED_CF_CB), 1)) == (struct NED_CF_CB *) 0
      || (cb->str= buffer1a= malloc (MAX_BUFFER1)) == (char *) 0
      || (cb->sgml_build= sgml_build= sgml_initialize_buildup ())
           == (struct SGML_BUILDUP *) 0
      || (cb->ot= ot= sgml_new_opening_tag (sgml_build, _hyx_l))
           == (struct SGML_OPENING_TAG *) 0
     ) goto ERROR;

  cb->wc= wc;
  cb->lp= lp;

  if (wc->file_type == FTY_FTRWDW)
  {
    ned_message_1 ("no features in feature window!");
    goto ERROR;
  }

  switch (what)
  {
    /* T2D: Ftype_SGML_TAG + ENTITY wieder reinnehmen und als   */
    /* string Type implementieren; siehe lookup                 */
    case Ftype_SGML_ENTITY:
      strcpy (buffer1a, "&;");
      cb->mode= CB_MODE_str;
      what= Ftype_SGML_entity_string;
      break;

    case Ftype_SGML_TAG:
      strcpy (buffer1a, "<>");
      cb->mode= CB_MODE_str;
      what= Ftype_SGML_tag_string;
      break;


    case Ftype_hyx_l:   /* set complete hyx.l, if possible with memorized   */
                        /* frame name, cluster name and frame coordinates   */
MAKE_HYX_L_TAG:
      what= Ftype_SGML_tag_string;
      cb->mode= CB_MODE_ot;

      /* insert link coordinates of a memorized frame or file */
      if (mem_file != (char *) 0)
      {
        if ((ptr= wc->file_or_frame) == (void *) 0) ptr= wc->WC_title_short;

        if (wc->file_type != FTY_PLAIN
            || (wc->file_type == FTY_PLAIN
                && ptr != (char *) 0
                && strcmp ((char *) ptr, mem_file) != 0
               )
           )
        { /* ommit the file= parameter if the filenames are the same */
          if ((attr= sgml_add_attribute (ot,
                         "file",
                         get_relative_path ((char *) ptr, mem_file)))
              == (struct SGML_ATTRIBUTE_LIST *) 0)
             goto ERROR;
        }
        cb->rc= 1;
      }
      else
      if (mem_frame != (char *) 0)
      {
        if (mem_cluster != (char *) 0
            && (wc->file_type != FTY_HYPER
                || (ptr= wc->file_or_frame) == (void *) 0
                || (ptr= ((struct FRAMECTRL *) ptr)->cluster) == (void *) 0
                || (ptr= ((struct CLUSTERCTRL *) ptr)->cluster_name_hyx)
                    == (struct CLUSTERCTRL *) 0
                || strcmp_c ((char *) ptr, mem_cluster) != 0
               )
           )
        {
          if ((attr= sgml_add_attribute (ot,
                     "cl",
                     find_logic_filename (mem_cluster, buffer1a, MAX_BUFFER1)
                        ? buffer1a : mem_cluster))
                == (struct SGML_ATTRIBUTE_LIST *) 0)
             goto ERROR;
        }

        if ((attr= sgml_add_attribute (ot, "fr", mem_frame))
                == (struct SGML_ATTRIBUTE_LIST *) 0)
             goto ERROR;
        cb->rc= 1;
      }
      else
      {
        if ((attr= sgml_add_attribute (ot, "fr", default_start_frame))
                == (struct SGML_ATTRIBUTE_LIST *) 0)
             goto ERROR;
      }

      /* highlighting for the word at the character position */
      if (q_isolate_word (buffer1a, MAX_BUFFER1, CHARSET_token, 1) != 0)
      {
        if ((attr= sgml_add_attribute (ot, _tdc, _hyx_l))
                == (struct SGML_ATTRIBUTE_LIST *) 0
            || (attr= sgml_add_long_attribute (ot, _tdp,
                        (long) strlen (buffer1a)))
                == (struct SGML_ATTRIBUTE_LIST *) 0
           ) goto ERROR;
      }

      /* set the destination marker id or a line/colum number */
      if (mem_mark != (char *) 0)
      {
        if ((attr= sgml_add_attribute (ot, _mark, mem_mark))
                == (struct SGML_ATTRIBUTE_LIST *) 0)
             goto ERROR;
      }
      else
      {
        if (mem_line > 1)
        {
          sprintf (buffer2a, "%d", mem_line);
          if ((attr= sgml_add_attribute (ot, "ln", buffer2a))
                 == (struct SGML_ATTRIBUTE_LIST *) 0)
             goto ERROR;
          if (mem_column > 0)
          {
            sprintf (buffer2a, "%d", mem_column);
            if ((attr= sgml_add_attribute (ot, "cn", buffer2a))
                 == (struct SGML_ATTRIBUTE_LIST *) 0)
             goto ERROR;
          }
        }
      }

      break;

    case Ftype_mark:    /* SHIFT-TAB: set mark tag */
      what= Ftype_SGML_tag_string;
      cb->mode= CB_MODE_ot;
      if (q_isolate_word (buffer1a, MAX_BUFFER1, CHARSET_token, 1) == 0)
        return -1;

      sprintf (buffer2a, "%d", strlen (buffer1a));
      cb->name= "name";
      if ((attr= sgml_add_attribute (ot, _tdc, _mark))
                 == (struct SGML_ATTRIBUTE_LIST *) 0
          || (attr= sgml_add_attribute (ot, _tdp, buffer2a))
                 == (struct SGML_ATTRIBUTE_LIST *) 0
         ) goto ERROR;
      break;

    case Ftype_lookup_fr2: /* set hyx.l after *successful* lookup; use current frame  */
      hyx_l_attr= "fr";
      what= Ftype_SGML_tag_string;

      max_buffer1a= MAX_BUFFER1;
      off_buffer1a= 0;

      if (wc->file_type == FTY_HYPER
          && (ptr= (struct FRAMECTRL *) wc->file_or_frame) != (void *) 0)
      {
        char *fn= ((struct FRAMECTRL *) ptr)->frame_name;

        strncpy (buffer1a, fn, MAX_BUFFER1);
        off_buffer1a= strlen (fn);
        buffer1a [off_buffer1a++]= ' ';
        buffer1a [off_buffer1a]= 0;
        max_buffer1a= MAX_BUFFER1 - off_buffer1a;
      }

      if (q_isolate_word (buffer1a + off_buffer1a, max_buffer1a,
                          CHARSET_token, 1) == 0) goto MAKE_HYX_L_TAG;
      sprintf (buffer2a, "%d", strlen (buffer1a + off_buffer1a));
fprintf (stderr, "%s %d tdp=%s buffer1a='%s'\n", __FILE__, __LINE__, buffer2a, buffer1a);
      goto MAKE_HYX_L_MARK2;

    case Ftype_lookup_fr: /* CTRL-TAB: set hyx.l after *successful* lookup  */
      hyx_l_attr= "fr";

    case Ftype_hyx_l_mark: /* SHIFT-TAB: set hyx.l after unsuccessful lookup */
      what= Ftype_SGML_tag_string;
      if (q_isolate_word (buffer1a, MAX_BUFFER1, CHARSET_token, 1) == 0)
        goto MAKE_HYX_L_TAG;

MAKE_HYX_L_MARK:
      sprintf (buffer2a, "%d", strlen (buffer1a));
      /* T2D: this length depends on buffer1a which can be edited later! */

MAKE_HYX_L_MARK2:
      cb->mode= CB_MODE_ot;
      cb->name= hyx_l_attr;
      if ((attr= sgml_add_attribute (ot, _tdc, _hyx_l))
                 == (struct SGML_ATTRIBUTE_LIST *) 0
          || (attr= sgml_add_attribute (ot, _tdp, buffer2a))
                 == (struct SGML_ATTRIBUTE_LIST *) 0
         ) goto ERROR;
      break;

    case Ftype_lookup:    /* ALT-TAB: set hyx.l after *successful* lookup   */
      what= Ftype_SGML_tag_string;
      cb->mode= CB_MODE_str;

      switch (ned_lookup_current_feature (buffer1a, buffer1b,
                &feature_string, &feature_type, MAX_BUFFER1, MAX_BUFFER1))
      {
        case 0:
          if (feature_string == (char *) 0
              || feature_type == (char *) 0
              || strcmp (feature_type, "F") != 0
             ) goto MAKE_HYX_L_MARK;
          break;
        case 1:
          goto MAKE_HYX_L_MARK;
        default:
          /* case 2: */
          return -1;
      }

      switch (feature_string [0])
      {
        case '<':
          what= Ftype_SGML_tag_string;
          break;
        case '&':
          what= Ftype_SGML_entity_string;
          break;
        default:
          what= Ftype_SGML_tag_string2;
          break;
      }

      strcpy_max (buffer1a, feature_string, MAX_BUFFER1);
      break;

    default:
      goto DISPOSE;
  }

  cb->what= what;
  cb->idx= wc->cx + wc->hv - wc->ax;
  cb->ftr_edit_mode= ftr_edit_mode;

  if (ftr_edit_mode == FTR_EDIT_ATTRIBUTE)
  /* T2D: 1997-06-15 10:18:50 REDISIGN !! */
  { /* T2D: this edits just a predefined attribute! */
    if (attribute == (char *) 0) attribute= "attr=";

    ned_prompt_string (attribute, buffer1a, MAX_BUFFER1,
                       default_help_cluster, default_help_prompt_attrib,
                       ned_cb_feature_create, (void *) cb);

    return 0;
  }

  return ned_cb_feature_create (strdup (buffer1a), 0, 1, (void *) cb);

ERROR:
  /* T2D: free what's malloced */
  return -1;

DISPOSE:
  /* T2D: free what's malloced */
  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_cb_feature_create (char *str, int size, int malloced, void *cb_data)
{
  struct WINDOWCTRL *wc;
  struct LINE *lp;
  int ftr_edit_mode;
  int rc;
  struct NED_CF_CB *cb;

#ifdef MSDOS
  str; size; malloced;
#endif

  if ((cb= (struct NED_CF_CB *) cb_data) == (struct NED_CF_CB *) 0
      || (wc= cb->wc) == (struct WINDOWCTRL *) 0
      || (lp= cb->lp) == (struct LINE *) 0
     )
   return 0;

  ftr_edit_mode= cb->ftr_edit_mode;
  rc= cb->rc;

  if (cb->mode == CB_MODE_str)
  {
    ned_wc_simple_feature_create (wc, lp, cb->idx, cb->what, cb->str);
  }
  else /** if (cb->mode == CB_MODE_ot) **/
  {
    char *xstr;

    if (cb->name != (char *) 0)
      sgml_add_attribute (cb->ot, cb->name, str);

    if ((xstr= sgml_tag_to_string (cb->ot, (char *) 0, 0, 0)) != (char *) 0)
    {
      ned_wc_simple_feature_create (wc, lp, cb->idx, cb->what, xstr);
      free (xstr);
    }
  }

  /* T2D: wc does not have to be on display at this point any more */
  wd_displine (wc, lp, wc->cy, wc->ax, wc->bx);

  if (ftr_edit_mode == FTR_EDIT_ALL
      || (ftr_edit_mode == FTR_EDIT_ALL_COND && !rc)
      || ftr_edit_mode == FTR_EDIT_STRING               /* not yet finished */
      || ftr_edit_mode == FTR_EDIT_STRUCTURED           /* not yet finished */
     )
    p_link_feature ();

  if (malloced) free_or_what (str);

  sgml_destroy_tag (cb->ot);
  free (cb->sgml_build);
  free (cb->str);
  /* NOTE: cb->name: static, not malloced!! */

  free (cb);

  return rc;
}
