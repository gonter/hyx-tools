/*
 *  FILE ~/usr/aisbr/unify/unify001.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-12-24
 *
 */

#include <gg/unify.h>

/* ------------------------------------------------------------------------ */
struct FEATURE_STRUCTURE *fs_unify (
struct FEATURE_STRUCTURE *fs1,
struct FEATURE_STRUCTURE *fs2)
{
  int sub1, sub2;

  if (fs1 == (struct FEATURE_STRUCTURE *) 0
      || fs2 == (struct FEATURE_STRUCTURE *) 0)
    return (struct FEATURE_STRUCTURE *) 0;

  sub1= fs_subsumption (fs1, fs2);
  sub2= fs_subsumption (fs2, fs1);

/****************************************************************************/
/* possible cases:                                                          */
/* a) error                                                                 */
/*    -> return empty structure                                             */
/* b) unimplemented types                                                   */
/*    -> return empty structure                                             */
/* c) conflicting values                                                    */
/*    -> return empty structure                                             */
/*                                                                          */
/* d) remaining forms can be unified                                        */
/* da) both subsumption relations hold                                      */
/*     -> both structures are equivalent                                    */
/*        -> return first one                                               */
/* db) one subsumption relation holds                                       */
/*     -> one structure contains all information of the other one           */
/*        -> return the one with all information                            */
/* dc) no subsumption relation holds                                        */
/*     -> either structure contains information which can't be found        */
/*        in the other one                                                  */
/*        -> match both structures and return the matched structure         */
/****************************************************************************/

  if ((sub1 & FS_sub_type)  || (sub2 & FS_sub_type)
    ||(sub1 & FS_sub_value) || (sub2 & FS_sub_value))
    return (struct FEATURE_STRUCTURE *) 0;

  if (sub1 == FS_sub_holds && sub2 == FS_sub_holds)
     return fs1;

  if (sub1 == FS_sub_holds) return fs2;
  if (sub2 == FS_sub_holds) return fs1;

  return fs_merge (fs1, fs2);
}

