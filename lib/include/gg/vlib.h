/*
 *  include FILE <gg/vlib.h>
 *
 *  functions etc for VLIB operations
 *
 *  written:       1993-02-07
 *  latest update: 1995-01-29
 *
 */

#ifndef __GG_vlib__
#define __GG_vlib__

#include <gg/floskel.h>

/* ------------------------------------------------------------------------ */
#define VLIBOP_GEN              1       /* generate */

/* ------------------------------------------------------------------------ */
/* vlibgen.c  */ int cdecl vlib_generate (char *fn, char *file_mode,
                   char *gen_uid,
                   char *gen_date, char *gen_time,
                   int overwrite, int verbose);

#endif /* __GG_vlib__ */
