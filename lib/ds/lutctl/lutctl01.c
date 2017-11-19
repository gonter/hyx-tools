/*
 *  FILE %gg/work/gg/lib/ds/lutctl/lutctl01.c
 *
 *  written:       2001-11-20
 *  latest update: 2001-11-20 19:33:18
 *  $Id: lutctl01.c,v 1.1 2001/11/20 19:32:40 gonter Exp $
 *
 */

#include <stdlib.h>
#include <gg/lutctl.h>

/* ------------------------------------------------------------------------ */
LUTCTL *lutctl_alloc (void)
{
  LUTCTL *p;
  p= calloc (sizeof (LUTCTL), 1);
  return p;
}

/* ------------------------------------------------------------------------ */
int lutctl_free (LUTCTL *p)
{
  if (p == (LUTCTL *) 0) return 0;

  if (p->filename != (char *) 0) free (p->filename);
  if (p->fp != (FILE *) 0) fclose (p->fp);

  if (p->mem != (char *) 0) free (p->mem);
  if (p->yt != (struct YTREE *) 0) ytree_free (p->yt);

  free (p);

  return 0;
}
