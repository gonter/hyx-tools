/*
 *  FILE %ned/01/ned0142.c
 *
 *  check if a character belongs to a given(?) set of characters
 *  NOTE: currently there are only two charset,
 *        check if this could be enhanced by the new charset functions
 *
 *  CHARSET_blank:      white space characters
 *  CHARSET_non_blank:  not white space characters
 *  CHARSET_token:      default
 *  CHARSET_filename:   for filenames
 *  CHARSET_include:    for include filenames
 *
 *  written:       1991 10 23
 *  latest update: 1999-05-01  9:12:16
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int in_charset (int ch, int charset)
{
  switch (charset)
  {
    case CHARSET_blank:
      switch (ch)
      {
        case ' ':
        case '\t':
          return 1;
        default:
          return 0;
      }
      break;

    case CHARSET_non_blank:
      switch (ch)
      {
        case ' ':
        case '\t':
          return 0;
        default:
          return 1;
      }
      break;

    case CHARSET_filename: /* used for filenames */
      switch (ch)
      {
        case '%':       /* for logic file names */
        case '.':
        case ':':       /* drive letters and URLs */
        case '\\':
        case '/':
        case '-':
        case '_':
        case '(':
        case ')':
          return 1;
        default: goto DEFAULT;
      }
      break;

    case CHARSET_include: /* used for include filenames */
      switch (ch)
      {
        case '%': /* for logic file names */
        case '.':
        case ':':
        case '\\':
        case '/':
        case '<':
        case '>':
        /* case '\"': */
          return 1;
        default: goto DEFAULT;
      }
      break;

    case CHARSET_token:
    default:
DEFAULT:
      switch (ch)
      {
        case 0x20:
        case 0x09:
        case ',':
        case '<':
        case '>':
        case '&':
        case '$':
        case '@':
          return 0;
        case '~':
        case '_':
        case 225:
          return 1;
        default:
          if ((ch >= 'A' && ch <= 'Z')
              ||(ch >= 'a' && ch <= 'z')
              ||(ch >= '0' && ch <= '9')
#ifdef MSDOS
              ||(ch >= 128 && ch <= 154)
              ||(ch >= 160 && ch <= 165)
#endif
             ) return 1;
          return 0;
      }
  }

  return 0;
}
