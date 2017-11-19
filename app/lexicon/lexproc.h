/*
 *  FILE ~/usr/lexicon/lexproc.h
 *
 *  written:       1991 04 19
 *  latest update: 1995-07-16
 *
 */

int cdecl init_by_size (int sort_mode, int sort_cnt);
int cdecl process_by_size (struct LEXICON_INDEX *idx);
int cdecl finish_by_size (FILE *fhyx, FILE *fo);
