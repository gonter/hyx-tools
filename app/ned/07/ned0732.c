/*
 *  FILE %ned/07/ned0732.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *                 1991 05 17: Revision
 *  latest update: 1997-08-03 15:46:48
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/filename.h>
#include "ed.h"
#include "proto.h"

extern int oper_level;
extern struct WINDOWCTRL *aw;
extern struct MARKER b_beg, b_end;

/* ------------------------------------------------------------------------ */
void q_wablk (int mode)       /* 0: write; 1: append Block to File  */
{
  char fnm [MAX_FNM_LENGTH];
  char xfnm_ftr [MAX_FNM_LENGTH];
  char *pfnm;
  char *pfnm_ftr;
  long la_offset;
  long lz_offset;
  int f_write_mode= FLG2_block_mode;

  if (oper_level >= LEV_FBLK) return;
  if (ned_blk_invalid ()) return;

  pfnm= fnm;
  pfnm_ftr= xfnm_ftr;

  if (mode == 2)
  {
    pfnm= "/dev/prn";
    pfnm_ftr= (char *) 0;
    if (aw->file_format == FMT_SGML) f_write_mode |= FLG2_format_change;
    f_write_mode |= FLG2_write_crlf;
  }
  else
  {
    fnm [0]= 0;
    if (rd_str ((mode == 1) ? "Append Block: " : "Write Block: ",
                fnm, MAX_FNM_LENGTH) == -1) return;
    fnmcpy (xfnm_ftr, fnm, ".ftr");
    if (mode == 1) f_write_mode |= FLG2_append_mode;
  }

  ned_f_write (aw, pfnm, pfnm_ftr, 0, 0,
           b_beg.ptr, b_end.ptr,
           &la_offset, &lz_offset,
           f_write_mode);
}
