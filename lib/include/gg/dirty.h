/*
 *  include FILE <gg/dirty.h>
 *
 *  written:       1991 10 03
 *  latest update: 1997-08-15 21:34:41
 *
 */

#ifndef __GG_dirty__
#define __GG_dirty__

#include <gg/floskel.h>

#define char_or_dot(x)  (((x) >= 0x20 && (x) <= 0x7e) ? (x) : '.')


/* ------------------------------------------------------------------------ */
#ifdef MSDOS
/* dirt_001.c   */ void cdecl patch (void (*fp)(), void (*fx)());
/* dirt_002.c   */ void cdecl patch_str (void (*p)(), char *s);
/* dirt_003.c   */ void cdecl get_patch (void (*p)(), char *s);
/* dirt_004.c   */ int cdecl peekb (char far *p);
/* dirt_005.c   */ void cdecl pokeb (char far *p, char b);
#endif
#ifdef _FILE_DEFINED
/* dirt_006.c   */ void cdecl dump (FILE *fo, char *cp, int cnt);
#endif
/* dirt_007.c   */ void set_cp (char **c1, unsigned int c2, unsigned int c3);
#ifdef MSDOS
/* dirt_008.c   */ void cdecl flip_int (int  *iv);
/* dirt_009.c   */ void cdecl flip_long (long *lv);
/* dirt_010.c   */ void cdecl flip_long_2 (long *lv);
#endif
/* dirt_011.c   */ int cdecl VAL (char *f, int s);
#ifdef _FILE_DEFINED
/* dirt_012.c   */ void cdecl dump_file (FILE *fo, FILE *fi, long cnt,
                     int do_flush);
                   void cdecl dump_file_tlti (FILE *fo, FILE *fi, long cnt,
                     int do_flush, int *tbl);
                   void cdecl dump_file_tltl (FILE *fo, FILE *fi, long cnt,
                     int do_flush, long *tbl);
/* dirt_013.c   */ void cdecl dump_str  (FILE *fo, char *x, int cnt);
                   void cdecl dump_str_tlti (FILE *fo, char *x, int cnt, int *tbl);
                   void cdecl dump_str_tltl (FILE *fo, char *x, int cnt, long *tbl);
/* dirt_014.c   */ int cdecl print_int_table (FILE *fo, int *cpi, int num);
/* dirt_014.c   */ int cdecl print_long_table (FILE *fo, long *cpi, int num);
/* dirt_016.c   */ int cdecl print_int_table2 (FILE *fo, int write_mode, int *converter_table, int num);
/* dirt_016.c   */ int cdecl print_long_table2 (FILE *fo, int write_mode, long *converter_table, int num);
#define WRITE_MODE_undef        0
#define WRITE_MODE_C            1
#define WRITE_MODE_binary       2
#define WRITE_MODE_rexx         4
#define WRITE_MODE_REXX         5
#define WRITE_MODE_ASSEMBLE     6
#define WRITE_MODE_C_ARRAY      7
#define WRITE_MODE_PERL         8
#endif /* _FILE_DEFINED */

#ifdef MSDOS
/* int24.asm    */ void cdecl int24ign_install (void);
#endif /* MSDOS */

#endif /* __GG_dirty__ */
