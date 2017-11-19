/*
 *  FILE %ds/attlist/attl0005.c
 *
 *  looking up info in a names file and convert it into a attribute list,
 *  but only attributes of a preset attribute list are filled in.
 *
 *  written:       1992 04 07: as ~/usr/pctcp/namefile.c
 *  latest update: 1999-04-25 16:57:14
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/attlist.h>

#define MAX_LINE 1024
static char line [MAX_LINE];
static char line2 [MAX_LINE];
static char line3 [MAX_LINE];

/* ------------------------------------------------------------------------ */
int al_find_name (
char *name_file,
char *first_attribute,
char *nick,
struct ATTRIBUTE_LIST *ntl)
{
  FILE *fi;
  int llng;
  int nick_found= 0;
  int items_found= 0;
  char *tag;
  int nick_length;
  struct ATTRIBUTE_LIST *ntl2;
  int AL_name_lng;
  int i, j, j1;

  nick_length= strlen (nick);
  if (nick_length <= 0) return -1;

  if ((fi= fopen (name_file, "rt")) == (FILE *) 0) return -1;

  for (;;)
  {
    fgets (line, MAX_LINE, fi);
    if (feof (fi)) break;
    if (line[0] == '*') continue;

    llng= strlen (line);
    if (llng > 0 && line [llng-1] == '\n') line[--llng]=0;
    strcpy (line2, line);
    to_lower (line2);

    if ((tag= strstr (line2, first_attribute)) != (char *) 0)
    {
      tag += 6;
      strcpy (line3, nick);
      to_lower (line3);
      nick_found= (strncmp (tag, line3, nick_length) == 0
                   && (tag[nick_length] == ' ' || tag[nick_length] == 0));
    }

    if (nick_found)
    {
      for (i= 0; i<llng; i++)
        if (line2[i] == ':')
        {
          for (ntl2  = ntl;
               ntl2 != (struct ATTRIBUTE_LIST *) 0;
               ntl2  = ntl2->AL_next)
          {
            AL_name_lng= strlen (ntl2->AL_name);
            if (strncmp (&line2[i+1], ntl2->AL_name, AL_name_lng) == 0
               && line2 [i+AL_name_lng+1] == '.')
            {
              for (j1= j= i+AL_name_lng+2; line2[j] && line2[j] != ':'; j++);
              for (j--; j>j1; j--) if (line2[j] != ' ') break;
              tag= (void *) calloc (j-j1+5, 1); /* +1 sould do it... */
              strncpy (tag, &line[j1], j-j1+1);
              tag [j-j1+1]= 0;
              if (ntl2->AL_type == ALty_string_dup)
              {
                free ((char *) ntl2->AL_value);
              }
              ntl2->AL_value= (void *) tag;
              ntl2->AL_type= ALty_string_dup;
              items_found++;
            }
          }
        }
    }
  }

  fclose (fi);

  return items_found;
}
