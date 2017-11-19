/*
 *  FILE ~/usr/aisbr/unify/unify008.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-08-13
 *
 */

#include <string.h>
#include <malloc.h>
#include <gg/unify.h>

/* ------------------------------------------------------------------------ */
struct FEATURE_STRUCTURE *fs_merge (
struct FEATURE_STRUCTURE *fs1,
struct FEATURE_STRUCTURE *fs2)
{
  struct FEATURE_STRUCTURE *fs1a;
  struct FEATURE_STRUCTURE **fs2a;
  struct FEATURE_STRUCTURE *fs3;
  struct FEATURE_STRUCTURE *merged= (struct FEATURE_STRUCTURE *) 0;
  struct FEATURE_STRUCTURE **append= &merged;
  int fs1a_in_fs2;
  int rv= 0;

  for (fs1a= fs1; fs1a != (struct FEATURE_STRUCTURE *) 0;)
  {
    fs1a_in_fs2=0;

    for (fs2a= &fs2; *fs2a != (struct FEATURE_STRUCTURE *) 0;)
    {
      if ((fs1a->fs_head_type == FS_type_atomic
        && (*fs2a)->fs_head_type == FS_type_atomic
        && fs1a->fs_head == (*fs2a)->fs_head)
       ||(fs1a->fs_head_type == FS_type_string
         && (*fs2a)->fs_head_type == FS_type_string
        && strcmp ((char *) fs1a->fs_head, (char *) (*fs2a)->fs_head) == 0))
      {
        fs1a_in_fs2= 1;
        /* both sturctures contain the same feature     */
        /* now compare values                           */
        if (fs1a->fs_tail_type == FS_type_atomic
           && (*fs2a)->fs_tail_type == FS_type_atomic)
        {
          if (fs1a->fs_tail != (*fs2a)->fs_tail)
          {
TAKE_BOTH:
            /* different values; take both (### and make set! ###) */
            fs1a_in_fs2= 0;
            *append= *fs2a;
            *fs2a= (*fs2a)->fs_next;
             append=&(*append)->fs_next;
             *append = (struct FEATURE_STRUCTURE *) 0;
          } else
          {
DISCARD_EQUAL:
            fs3= *fs2a;
            *fs2a = fs3->fs_next;
            if (fs3->fs_head_type == FS_type_string) free (fs3->fs_head);
            free (fs3);
          }
          break;
        } else
        if (fs1a->fs_tail_type == FS_type_string
           && (*fs2a)->fs_tail_type == FS_type_string)
        {
          if (strcmp ((char *) fs1a->fs_tail, (char *) (*fs2a)->fs_tail) != 0)
          {
            goto TAKE_BOTH;
          } else
          {
            goto DISCARD_EQUAL;
          }
          break;
        } else
        if (fs1a->fs_tail_type == FS_type_feature
           && (*fs2a)->fs_tail_type == FS_type_feature)
        {
          fs3= *fs2a;
          fs1a->fs_tail= fs_merge (fs1a->fs_tail, fs3->fs_tail);
          *append = fs1a;
           append = &fs1a->fs_next;
           fs1a=fs1a->fs_next;
           *append = (struct FEATURE_STRUCTURE *) 0;
           *fs2a = fs3->fs_next;
           if (fs3->fs_head_type == FS_type_string) free (fs3->fs_head);
           free (fs3);
           break;
        } else
        if (fs1a->fs_tail_type == FS_type_number
           && (*fs2a)->fs_tail_type == FS_type_number)
        { /* add numbers */
          long tmpval;
          tmpval = (long) fs1a->fs_tail;
          tmpval += (long) (*fs2a)->fs_tail;
          fs1a->fs_tail = (struct FEATURE_STRUCTURE *) tmpval;
          fs1a_in_fs2=0;
          goto DISCARD_EQUAL;
        } else goto TAKE_BOTH;
      } else
      { /* head not matching, the next one.... */
        fs2a = &(*fs2a)->fs_next;
      }
    }

    if (fs1a_in_fs2 == 0)
    { /* a feature in fs1 was never found in fs2        */
      *append= fs1a;
       append= &fs1a->fs_next;
      fs1a= fs1a->fs_next;
      *append= (struct FEATURE_STRUCTURE *) 0;
    }
  }

  /* feature elements from second list, which are still not used */
  /* should be merged */
  while (fs2 != (struct FEATURE_STRUCTURE *) 0)
  {
    *append = fs2;
     append = &fs2->fs_next;
     fs2    =  fs2->fs_next;
    *append = (struct FEATURE_STRUCTURE *) 0;
  }

  return merged;
}
