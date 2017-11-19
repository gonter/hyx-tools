/*
 *  FILE ~/usr/aisbr/unify/unify002.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-08-12
 *
 */

#include <string.h>
#include <gg/unify.h>

/* ------------------------------------------------------------------------ */
int fs_subsumption (
struct FEATURE_STRUCTURE *fs1,
struct FEATURE_STRUCTURE *fs2)
/* RETURN:                                                                  */
/*   bit 0 ... fs1 contains features which are not contained in fs2         */
/*   bit 1 ... fs1 and fs2 contain features which are not compatible        */
{
  struct FEATURE_STRUCTURE *fs1a;
  struct FEATURE_STRUCTURE *fs2a;
  int fs1a_in_fs2;
  int rv=0;
  int rc;

  for (fs1a  = fs1;
       fs1a != (struct FEATURE_STRUCTURE *) 0;
       fs1a  = fs1a->fs_next)
  {
    fs1a_in_fs2=0;
    fs1a->fs_sub1=FS_sub_holds;

    for (fs2a  = fs2;
         fs2a != (struct FEATURE_STRUCTURE *) 0;
         fs2a  = fs2a->fs_next)
    {
      if ((fs1a->fs_head_type == FS_type_atomic
          && fs2a->fs_head_type == FS_type_atomic
          && fs1a->fs_head == fs2a->fs_head)
         ||(fs1a->fs_head_type == FS_type_string
           && fs2a->fs_head_type == FS_type_string
           && strcmp ((char *) fs1a->fs_head, (char *) fs2a->fs_head) == 0))
      {
        fs1a_in_fs2=1;
        /* both sturctures contain the same feature     */
        /* now compare values                           */
        if (fs1a->fs_tail_type == FS_type_atomic
           && fs2a->fs_tail_type == FS_type_atomic)
        {
          if (fs1a->fs_tail != fs2a->fs_tail)
            fs1a->fs_sub1 = FS_sub_value;
          break;
        } else
        if (fs1a->fs_tail_type == FS_type_string
           && fs2a->fs_tail_type == FS_type_string)
        {
          if (strcmp ((char *) fs1a->fs_tail, (char *) fs2a->fs_tail) != 0)
          {
            fs1a->fs_sub1 = FS_sub_value;
            rv |= FS_sub_value;
          }
          break;
        } else
        if (fs1a->fs_tail_type == FS_type_feature
           && fs2a->fs_tail_type == FS_type_feature)
        {
          rc= fs_subsumption (fs1a->fs_tail, fs2a->fs_tail);
          rv |= rc;
          fs1a->fs_sub1 = rc;
          break;
        } else
        if (fs1a->fs_tail_type == FS_type_number
          && fs2a->fs_tail_type == FS_type_number)
        { /* numbers can be subsumed */
          break;
        } else
        {
          rv |= FS_sub_type;
          fs1a->fs_sub1 = FS_sub_type;
          break;
        }
      }
    }

    if (fs1a_in_fs2 == 0)
    { /* a feature in fs1 was never found in fs2        */
      /* thus the subsumption relation does not hold    */
      rv |= FS_sub_feature;
      fs1a->fs_sub1= FS_sub_feature;
    }
  }

  return rv;
}
