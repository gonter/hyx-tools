/*
 *  FILE %inc/gg/lutctl.h
 *
 *  written:       2001-11-20
 *  latest update: 2001-11-20 19:09:54
 *  $Id: lutctl.h,v 1.1 2001/11/20 19:32:45 gonter Exp $
 *
 */

#ifndef __GG_lutctl__
#define __GG_lutctl__

#include <stdio.h>
#include <gg/lookup.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
struct LUTCTL
{
  int state;            /* indicates where the lookup table is stored       */
#define LUTCTL_state_undef 0    /* not yet defined                          */
#define LUTCTL_state_file  1    /* LUT structure in opened file             */
#define LUTCTL_state_mem   2    /* LUT structure in memory                  */
#define LUTCTL_state_ytree 3    /* YTREE in memory                          */

  int updated;

  /* file based lookup table */
  char *filename;
  FILE *fp;

  /* memory cached lookup table */
  char *mem;
  long size;     
  long limit;

  /* structured as YTREE */
  struct YTREE *yt;
};
typedef struct LUTCTL LUTCTL;

/* methods: --------------------------------------------------------------- */
LUTCTL *lutctl_alloc ();
int lutctl_free (LUTCTL *lutct);

int lutctl_set_filename (LUTCTL *lutct, char *fnm);
int lutctl_open (LUTCTL *lutctl);
int lutctl_close (LUTCTL *lutctl);

int lutctl_load (LUTCTL *lutctl, long limit);


#endif /* __GG_lutctl__ */

