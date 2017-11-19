/*
 *  FILE ~/usr/sgml/sgml0005.c
 *
 *  written:       1990 09 27
 *  latest update: 1999-04-25 16:40:04
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/sgml.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

struct SGML_TAG *cdecl get_sgml_tag (char *);

/* HOOK: ------------------------------------------------------------------ */
sgml_list_element () { int i; } /* weitergereichtes SGML List-Element       */

/* ------------------------------------------------------------------------ */
# define BUFFER_SIZE 1024
static char buffer [BUFFER_SIZE];       /* collected tag und text string    */

static int buffer_lng=0;
static int mode=0;              /* 0 ... text; 1 ... tag        */
static int tag_state=0;         /* state of the tag scanner     */
static int tag_cnt=0;           /* count of tag elements        */

static struct SGML_LIST *list, **listptr;

/* ------------------------------------------------------------------------ */
x_out_char (long ch)
{
  buffer [buffer_lng++]=(char) ch;
  if (buffer_lng >= BUFFER_SIZE) swap_text ();
}

/* ------------------------------------------------------------------------ */
x_tag_beg ()
{
  if (buffer_lng) swap_text ();
  mode=1;
  tag_state=0;
  tag_cnt=0;
  buffer_lng=0;
  list=(struct SGML_LIST *) 0;
  listptr = &list;
}

/* ------------------------------------------------------------------------ */
x_tag_end ()
{
  swap_tag ();
  mode=0;
  buffer_lng=0;
  sgml_list_element (list);
}

/* ------------------------------------------------------------------------ */
x_tag_chr (long ch)
{
  int chr;
  chr = (int) ch;

  switch (tag_state)
  {
    case 0:
      switch (chr)
      {
        case '\"':
          tag_state=3;
          break;
        case '\\':
          tag_state=2;
          break;
        case ':':
        case ';':
          buffer[0]=chr;
          buffer_lng=1;
          swap_tag ();
          break;
        default:
          buffer[0]=chr;
          buffer_lng=1;
          tag_state=1;
          break;
      }
      break;
    case 1:
      switch (chr)
      {
        case '\"':
          if (buffer_lng < BUFFER_SIZE) buffer [buffer_lng++]=chr;
          tag_state=3;
          break;
        case '\\':
          tag_state=2;
          break;
        case ' ':
        case 0x09:
        case 0x0A:
        case 0x0D:
          swap_tag ();
          tag_state=0;
          break;
        default:
          if (buffer_lng < BUFFER_SIZE) buffer[buffer_lng++]=chr;
          tag_state=1;
          break;
      }
      break;
    case 2:
      if (buffer_lng < BUFFER_SIZE) buffer[buffer_lng++]=chr;
      tag_state=1;
      break;
    case 3:
      if (ch=='\\') tag_state=4; else
      {
        if (ch=='\"') tag_state=1;
        if (buffer_lng < BUFFER_SIZE) buffer[buffer_lng++]=chr;
      }
      break;
    case 4:
      if (buffer_lng < BUFFER_SIZE) buffer[buffer_lng++]=chr;
      tag_state=3;
      break;
  }
}

/* ------------------------------------------------------------------------ */
static swap_text ()
{
  struct SGML_INFO_BYTE *ib;

  if (buffer_lng==0) return;
  ib = (struct SGML_INFO_BYTE *)
       calloc (sizeof (struct SGML_INFO_BYTE) - 2 + buffer_lng, 1);
  ib->sig = SIG_INFO_BYTE;
  ib->size = buffer_lng;
  memcpy (ib->info, buffer, buffer_lng);
  buffer_lng=0;
  sgml_list_element (ib);
}

/* ------------------------------------------------------------------------ */
static swap_tag ()
{
  struct SGML_TAG  *t;
  struct SGML_INFO_BYTE *ib;
  struct SGML_LIST *ls;

  if (buffer_lng==0) return;
  buffer [buffer_lng]=0;

  ls = (struct SGML_LIST *) calloc (sizeof (struct SGML_LIST), 1);
  ls->sig = SIG_LIST;
  ls->cdr  = (struct SGML_LIST *) 0;
  *listptr = ls;
   listptr = &(ls->cdr);

  if (tag_cnt==0)
       {
         t=get_sgml_tag (buffer);
         ls->car=t;
       }
  else {
         ib = (struct SGML_INFO_BYTE *)
              calloc (sizeof (struct SGML_INFO_BYTE) - 1 + buffer_lng, 1);
         ib->sig = SIG_PARAMETER;
         ib->size = buffer_lng;
         ls->car  = ib;
         memcpy (ib->info, buffer, buffer_lng+1);
       }

  buffer_lng  = 0;
  tag_cnt++;
}
