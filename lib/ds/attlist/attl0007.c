/*
 *  FILE %ds/attlist/attl0007.c
 *
 *  manipulation of attribute lists
 *  + parse an SGML like stream and produce a attribute list
 *
 *  written:       1994-10-30
 *  latest update: 1997-11-02 12:54:50
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/attlist.h>

#define DEFAULT_BUFFER 2048
#define TAGO '<'
#define TAGC '>'

/* ------------------------------------------------------------------------ */
struct ATTRIBUTE_LIST *al_parse_sgml_stream (
FILE *fi,
long size,
char *buffer,
int buffer_size)
{
  struct ATTRIBUTE_LIST *al_rv= (struct ATTRIBUTE_LIST *) 0;
  struct ATTRIBUTE_LIST *al_new;
  int ba= 0;
  int ch;
  int idx;
#define STATE_START 0
#define STATE_TAGO  1
#define STATE_TAGCH 2
#define STATE_ATTL1 3
#define STATE_ATTL2 4
#define STATE_TAGCL 5
#define STATE_TEXT  6
  int state= STATE_START;

  char *name= (char *) 0;
  char *attl= (char *) 0;

  if (buffer == (char *) 0 || buffer_size <= 0)
  {
    if ((buffer= malloc (buffer_size= DEFAULT_BUFFER)) == (char *) 0)
      goto END;
    ba= 1;
  }

  for (;;)
  {
    if (size > 0L)
    {
      ch= fgetc (fi) & 0x00FF;
      if (feof (fi)) ch= -1;
      size--;
      if (ch == '\015') continue;
    }
    else ch= -1;

    if (ch == -1)
    {
      /***************************
      if (state != STATE_START && state != STATE_TAGCL
          && state != STATE_TEXT)
       -> ERROR
      ***************************/

      goto END;
    }

    switch (state)
    {
      case STATE_START:
        switch (ch)
        {
          case ' ': case '\t': case '\n': break;
          case TAGO: state= STATE_TAGO; break;
          default: /* text before the first tag! */ break;
        }
        break;

      case STATE_TAGO:
        switch (ch)
        {
          case ' ': case '\t': case '\n':
            /* this should not really happen; TAGO as part of text! */
            break;
          case TAGC: /* empty tag like m#< *># */
            state= STATE_TAGCL;
            break;
          default:
            buffer [idx= 0]= (char) ch;
            state= STATE_TAGCH;
            break;
        }
        break;

      case STATE_TAGCH:
        switch (ch)
        {
          case ' ': case '\t': case '\n':
            state= STATE_ATTL1;
            buffer [idx]= 0;
            name= strdup (buffer);
            break;
          case TAGC:
            state= STATE_TAGCL;
            buffer [idx]= 0;
            name= strdup (buffer);
            break;
          default:
            buffer [idx++]= (char) ch;
            break;
        }
        break;

      case STATE_ATTL1:
        switch (ch)
        {
          case ' ': case '\t': case '\n': break;
          case TAGC: /* no attribute list, like m#<xyz +># */
            state= STATE_TAGCL;
            break;
          default:
            buffer [idx= 0]= (char) ch;
            state= STATE_ATTL2;
            break;
        }
        break;

      case STATE_TAGCH:
        switch (ch)
        {
          case TAGC:
            state= STATE_TAGCL;
            buffer [idx]= 0;
            attl= strdup (buffer);
            break;
          default:
            buffer [idx++]= (char) ch;
            break;
        }
        break;

      case STATE_TAGCL:
        switch (ch)
        {
          default:
            state= STATE_TEXT;
            buffer [idx= 0]= (char) ch;
            break;
        }
        break;

            al_new= al_create_attribute (
    }

    if (ch == -1) break;
  }

END:
  if (ba) free (buffer);

  return al_rv;
}
