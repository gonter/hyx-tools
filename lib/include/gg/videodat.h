/*
 *  include FILE <gg/videodat.h>
 *
 *  written:       1993-09-25
 *  latest update: 1993-09-25
 *
 */

#ifndef __GG_videodat__
#define __GG_videodat__

/* ------------------------------------------------------------------------ */
struct VD_TTL_block
{
  char *vd_ttl_fname;           /* filename                     */
  char *vd_ttl_buffer;          /* unidentified contents        */
  char *vd_ttl_descr;           /* description                  */
} ;

/* ------------------------------------------------------------------------ */
struct VD_TTL_block *cdecl read_vd_ttl_block (FILE *fi);

#endif /* __GG_videodat__ */
