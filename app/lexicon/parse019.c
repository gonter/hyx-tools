/*
 *  FILE ~/usr/lexicon/parse019.c
 *
 *  written:       1991 04 28
 *  latest update: 1995-07-16
 *
 */

#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int parse_tag_sequence (
char *tag_str,                  /* initial tag string to parse (without <>) */
char *parse_string_array,       /* character string to get parse array from */
char *pt_array [],
int   pt_type [],
int   pt_max)
/* Return                                                                   */
/*  < 0 ... error                                                           */
/*   -1 ... null-string to be parsed or null-string for parsing output      */
/*   -2 ... parse_array to small                                            */
/*  -99 ... internal parser error                                           */
/*    0 ... nothing parsed;                                                 */
/*  > 0 ... number of items found                                           */
{
  int parse_index, ch;
  int items_found= 0;
  int status= 0;
#define STATUS_start            0
#define STATUS_tag_found        1
#define STATUS_parameters       2
#define STATUS_2parameter       3
#define STATUS_attr_value       4
  int is_space;

  if (tag_str == (char *) 0) return -1;

  for (parse_index= 0;
       (ch= tag_str [parse_index] & 0x00FF) != 0;
       parse_index++)
  {
    is_space= (ch == 0x20 || ch == 0x09 || ch == 0x0A || ch == 0x0D);
    switch (status)
    {
      case STATUS_start:
        if (!is_space)
        {
          if (items_found >= pt_max) return -2;
          status= STATUS_tag_found;
          pt_array [items_found]= parse_string_array;
          pt_type [items_found]= TAG_ITEM_TAG;
          *parse_string_array++= (char) ch;
          *parse_string_array= 0;
          items_found++;
        }
        break;

      case STATUS_tag_found:
        if (is_space)
        {
          parse_string_array++;
          status= STATUS_parameters;
        } else
        {
          *parse_string_array++= (char) ch;
          *parse_string_array= 0;
        }
        break;

      case STATUS_parameters:
        if (!is_space)
        {
          if (items_found >= pt_max) return -2;
          status= STATUS_2parameter;
          pt_array [items_found]= parse_string_array;
          pt_type [items_found]= TAG_ITEM_PARAMETER;
          *parse_string_array++= (char) ch;
          *parse_string_array= 0;
          items_found++;
        }
        break;

      case STATUS_2parameter:
        if (is_space)
        {
          parse_string_array++;
          status= STATUS_parameters;
        } else
        if (ch == '=')
        {
          *++parse_string_array= 0;
          status= STATUS_attr_value;
          pt_type  [items_found-1]= TAG_ITEM_ATTR_NAME;
          pt_array [items_found  ]= parse_string_array;
          pt_type  [items_found  ]= TAG_ITEM_ATTR_VALUE;
          items_found++;
        } else
        {
          *parse_string_array++= (char) ch;
          *parse_string_array= 0;
        }
        break;

      case STATUS_attr_value:
        if (is_space)
        {
          parse_string_array++;
          status= STATUS_parameters;
        } else
        {
          *parse_string_array++= (char) ch;
          *parse_string_array= 0;
        }
        break;

      default: return -99;
    }
  }

  return items_found;
}
