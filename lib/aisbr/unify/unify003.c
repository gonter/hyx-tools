/*
 *  FILE ~/usr/aisbr/unify/unify003.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-08-12
 *
 */

#include <stdio.h>
#include <gg/strings.h>
#include <gg/unify.h>

/* ------------------------------------------------------------------------ */
int fs_print_feature_element (
FILE *fo,
int fe_type,
struct FEATURE_STRUCTURE *fe,
struct FEATURE_STRUCTURE *root,
int indent,
int flags)
{
  int indent_plus= 0;
  int mbqf;

  if (fe_type == FS_type_unknown)
    fprintf (fo, "[]", fe); else
  if (fe_type == FS_type_atomic)
    fprintf (fo, "%08X", fe); else
  if (fe_type == FS_type_string
    ||fe_type == FS_type_pointer)
  {
    if (mbqf= fs_mbq ((char *) fe)) fputc ('\"', fo);
    indent_plus= fprintf (fo, "%s", fe);
    if (mbqf) fputc ('\"', fo);
  } else
  if (fe_type == FS_type_feature)
  {
    fputc ('[', fo);
    fs_print_feature_structure (fo, fe, root, indent+1, flags, 1);
    fputc (']', fo);
  } else
  if (fe_type == FS_type_set)
  {
    fputc ('{', fo);
    fs_print_feature_structure (fo, fe, root, indent+1, flags, 1);
    fputc ('}', fo);
  } else
  if (fe_type == FS_type_number)
  {
    fprintf (fo, "%ld", (long) fe);
  } else fprintf (fo, "????????");
  return indent_plus;
}

/* ------------------------------------------------------------------------ */
int fs_print_feature_structure (
FILE *fo,
struct FEATURE_STRUCTURE *xfs,
struct FEATURE_STRUCTURE *root,
int indent,
int flags,
int list)
{
  int item=0;
  struct FEATURE_STRUCTURE *fsd;
  struct FEATURE_STRUCTURE *fs;
  int indent_plus=0;
  int newline_flag=0;

  for (fs=xfs; fs != (struct FEATURE_STRUCTURE *) 0; fs = fs->fs_next)
  if (fs->fs_tail_type == FS_type_feature
    ||fs->fs_tail_type == FS_type_set) newline_flag=1;

  for (fs=xfs; fs != (struct FEATURE_STRUCTURE *) 0; fs = fs->fs_next)
  {
    if (item++)
    {
      if (newline_flag)
      {
        fputc ('\n', fo);
        blanks (fo, indent);
      }
      else fputc (' ', fo);
    }

    if ((flags & 0x0100) && fs->fs_sub1 > 0)
      fprintf (fo, "®1:%d¯", fs->fs_sub1);
    /**** if ((flags & 0x0200) && fs->fs_sub2 > 0)
      fprintf (fo, "®2:%d¯", fs->fs_sub2); ****/

    if (fs->fs_head_type != FS_type_unknown)
    {
      indent_plus= fs_print_feature_element (fo, fs->fs_head_type,
                     fs->fs_head, root, indent, flags);
      fprintf (fo, ":");
    }

    if (fs->fs_tail_type == FS_type_pointer
        && (flags & 0x0001))
    {
      fsd= fs_trace_path (root, (char *) fs->fs_tail);
      if (fsd == (void *) 0)
        fprintf (fo, "[]");
      else fs_print_feature_element (fo, fsd->fs_tail_type,
                                  fsd->fs_tail, root,
                                  indent+indent_plus+1, flags);
    } else
    fs_print_feature_element (fo, fs->fs_tail_type, fs->fs_tail,
                           root, indent+indent_plus+1, flags);
    if (!list) break;
  }

  return 0;
}
