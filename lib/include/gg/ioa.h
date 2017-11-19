/*
 *  include FILE <gg/ioa.h>
 *
 *  IOA: 
 *
 *  written:       1993-02-10
 *  latest update: 1994-11-05
 *
 */

#ifndef __GG_ioa__
#define __GG_ioa__

/* ------------------------------------------------------------------------ */
/* ioa001.c */ int find_info (char *buffer, char *attr_n[], char *attr_v[],
                 int n_attr);
/* ioa002.c */ int analyze_fields (char *line, int delimiter, char *items[],
                 int max_items);

#endif /* __GG_ioa__ */
