/*
 *  include FILE <gg/taglst.h>
 *
 *  written:       1990 06 10
 *  latest update: 1995-10-26
 *
 */

#ifndef __GG_taglst__
#define __GG_taglst__

/* ------------------------------------------------------------------------ */
struct TAGGED_LIST
{
  struct TAGGED_LIST *TL_next;
  struct TAGGED_LIST *TL_prev;
  int TL_lng;
  int TL_tag;
  char TL[2];
} ;

#define TAG_SCREEN 1
#define TAG_FIELD  2

/* ------------------------------------------------------------------------ */
struct TAGGED_LIST *tl_generate_tagged_list (struct TAGGED_LIST *tl,
                      char *array, int array_size, int tag, int typ);
struct TAGGED_LIST *tl_allocate (int data_size);
void tl_rueckverkettung (struct TAGGED_LIST *tl);
void tl_dump (FILE *fo, struct TAGGED_LIST *tl);
void tl_dump_list (FILE *fo, struct TAGGED_LIST *tl);

#endif /* __GG_taglst__ */
