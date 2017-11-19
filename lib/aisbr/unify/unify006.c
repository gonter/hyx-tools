/*
 *  FILE ~/usr/aisbr/unify/unify006.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-08-12
 *
 */

#include <gg/unify.h>

/* ------------------------------------------------------------------------ */
struct FEATURE_STRUCTURE *fs_trace_path (
struct FEATURE_STRUCTURE *fs,
char *path)
{
  char *cp1, *cp2;

  if (path == (char *) 0 || *path != '@')
    return (struct FEATURE_STRUCTURE *) 0;

  if (path[1] == 0) return fs;          /* @ -> root */

  for (; fs != (void *) 0; fs=fs->fs_next)
  {
TOP:
    if (fs->fs_head_type == FS_type_string)
    {
      cp1 = (char *) fs->fs_head;
      cp2 = &path [1];
      for (;;)
      {
        if (*cp1 == 0)
        {
          switch (*cp2)
          {
            case 0: return fs;  /* complete path walked down */
            case '@':           /* just a part of the path walked down */
              path=cp2;
              if (fs->fs_tail_type == FS_type_feature
                ||fs->fs_tail_type == FS_type_set)
              {
                fs = fs->fs_tail;
                goto TOP;
              }
              /* otherwise walk_down fails */
            default: return (struct FEATURE_STRUCTURE *) 0;
          }
        }
        if (*cp1 != *cp2) break;
        cp1++;
        cp2++;
      }
    }
  }
  return (struct FEATURE_STRUCTURE *) 0;
}
