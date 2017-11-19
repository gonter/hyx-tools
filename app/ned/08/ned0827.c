/*
 *  FILE %ned/08/ned0827.c
 *
 *  written:       1991 06 25
 *  latest update: 1997-12-05 11:42:55
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/hyx.h>
#include "ed.h"
#include "proto.h"

#define LIN_SIZ 1024

/* ------------------------------------------------------------------------ */
int find_feature_with_attribute (
struct LINE *lp,                /* line to start from                       */
int direction,                  /* Bit 0==0: up                             */
                                /*     0==1: down                           */
                                /*     1==0: Start @lp                      */
                                /*     1==1: Start @(top|bottom)            */
char *feature_name,             /* name of the SGML tag to search           */
char *attribute_name,           /* name of the attribute to search          */
char *attribute_value,          /* value of the attribute to search         */
                                /* ? ... accept any value                   */
struct LINE **found_line,       /* line of found feature                    */
int *nr_found_line,             /* number of found feature (preset!!!)      */
struct FEATURE **found_feature) /* found feature record                     */
/* Return: -1 ... error                                                     */
/*          0 ... feature not found                                         */
/*          1 ... feature found                                             */
{
  struct LINE *fl;
  int rc;
  char lin [LIN_SIZ];
  char *id;
  int avl;

  if (lp == (struct LINE *) 0) return -1;

  avl= strlen (attribute_value);

  while (lp != (struct LINE *) 0)
  {
    *found_feature= (struct FEATURE *) 0;
NEXT_IN_LINE:
    rc= find_feature (lp, direction, feature_name,
                      found_line, nr_found_line, found_feature);
    direction &= 0xFFFD;

    switch (rc)
    {
      case -1:
        return -1;

      case 1:
        fl= (struct LINE *) (*found_feature)->ftr_text_line;
        if (ned_line_2_string (fl, 1, fl, fl->lng-1, lin, LIN_SIZ,
                           0L, 0x0000) == (char *) 0)
          break;

        id= find_attr_name (lin, attribute_name);
        if (id != (char *) 0
            &&(strcmp (attribute_value, "?") == 0
               ||(strncmp (id, attribute_value, avl) == 0
                  && ((rc=id[avl]) == ' ' || rc == 0)
                 )
               ||(*id=='\"'
                  && strncmp (id+1, attribute_value, avl) == 0
                  && id[avl+1] == '\"'
                 )
              )
           )
          return 1;

        lp= *found_line;

        if (*found_feature != (struct FEATURE *) 0
            && (*found_feature= (*found_feature)->ftr_next)
                != (struct FEATURE *) 0
           )
          goto NEXT_IN_LINE;

        if (direction & 0x01)
        {
          lp= lp->next;
          (*nr_found_line)++;
        }
        else
        {
          lp= lp->prev;
          (*nr_found_line)--;
        }
        break;

      case 0:
        return 0; 
    }
  }

  return 0;
}
