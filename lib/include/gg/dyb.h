/*
 *  include FILE <gg/dyb.h>
 *
 *  dynamic block management
 *  - constants
 *  - structures:
 *    DYB_SEGMENT, DYNAMIC_BLOCK
 *  - prototypes
 *
 *  written:       1995-08-19
 *  latest update: 1996-06-22  9:20:43
 *
 */

#ifndef __GG_dyb__
#define __GG_dyb__

#include <gg/floskel.h>

/* constants: ------------------------------------------------------------- */
#ifdef MSDOS
#define DYB_SEGMENT_SIZE 256
#else
#define DYB_SEGMENT_SIZE 1024
#endif

/* ------------------------------------------------------------------------ */
struct DYB_SEGMENT
{
  struct DYB_SEGMENT *DYBS_next;        /* the next element of a block      */
  long DYBS_size;                       /* number of bytes allocated        */
  long DYBS_free;                       /* number of bytes still free       */
  char *DYBS_append;                    /* next position to insert chars    */
  char DYBS_block [2];                  /* dynamically allocated block      */
} ;

/* ------------------------------------------------------------------------ */
#define _DYNAMIC_BLOCK_DEFINED
struct DYNAMIC_BLOCK
{
  long DYB_reference_counter;
  long DYB_total_size;
  int DYB_segment_size;

  struct DYB_SEGMENT
    *DYB_begin,
    *DYB_last,
   **DYB_append;
} ;

/* prototypes: ------------------------------------------------------------ */
/* dyb_0001.c */ struct DYB_SEGMENT *cdecl dyb_new_segment (int segment_size);
/* dyb_0002.c */ struct DYNAMIC_BLOCK *cdecl dyb_new_block (int segment_size);
/* dyb_0003.c */ int cdecl dyb_append_block (struct DYNAMIC_BLOCK *dyb,
                   char *block, long block_size);
/* dyb_0004.c */ int cdecl dyb_append_string (struct DYNAMIC_BLOCK *dyb,
                   char *string);
/* dyb_0005.c */ int cdecl dyb_destroy_block (struct DYNAMIC_BLOCK *dyb);
/* dyb_0006.c */ int cdecl dyb_reference (struct DYNAMIC_BLOCK *dyb);
/* dyb_0007.c */ long cdecl dyb_truncate (struct DYNAMIC_BLOCK *dyb,
                   long size);

#ifdef _GG_CRYPT_defined
/* dyb_0008.c */ int cdecl dyb_encrypt_ecb (struct GG_CRYPT *ggc,
                   struct DYNAMIC_BLOCK *dyb);
/* dyb_0008.c */ int cdecl dyb_encrypt_cfb (struct GG_CRYPT *ggc,
                   struct DYNAMIC_BLOCK *dyb);
#endif /* _GG_CRYPT_defined */

/* dyb_0010.c */ int cdecl dyb_write (int fd, struct DYNAMIC_BLOCK *dyb);
/* dyb_0011.c */ int cdecl dyb_append_blanks (struct DYNAMIC_BLOCK *dyb,
                   long num_blanks);

#ifdef __COMMENT__
additional functions:
struct DYNAMIC_BLOCK *dyb_copy (struct DYNAMIC_BLOCK *src);
int dyb_concat (struct DYNAMIC_BLOCK *dst, struct DYNAMIC_BLOCK *b2)
/* append b2 at the end of dst, destroying b2 */
int dyb_concat_copy (struct DYNAMIC_BLOCK *dst, struct DYNAMIC_BLOCK *b2)
/* append b2 at the end of dst, NOT destroying b2 */
#endif /* __COMMENT__ */

#endif /* __GG_dyb__ */
