/*
 *  FILE ~/usr/lexicon/lex00001.c
 *
 *  - Prototypes
 *
 *  written:       1990 11 13
 *                 1991 03 16: Revision; AIX
 *  latest update: 1995-07-16
 *
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#ifdef MSDOS
#include <gg/fnames.h>
#endif
#include <gg/lexicon.h>
#include <gg/sbr.h>

#define LEX_DESCS      20
#define CACHE_FILES    10       /* Zahl der Files, die `gecachet'           */
                                /* geoeffnet werden duerfen.                */

static struct LEXICON_DESCRIPTION lexdesc [LEX_DESCS];
static int lexdesc_inited= 0;
static int cache_counter= 0;

/* Prototypes statischer Funktionen: -------------------------------------- */
#ifdef MSDOS
static long cdecl get_counter (char *s, int idx);
#endif /* MSDOS */
static int cdecl get_files (char *path, char *pattern,
                            int mode, struct LEXICON_FILE **lfp);
static void cdecl release_files (struct LEXICON_FILE *lfp);
static void cdecl cache_close_all (void);
static void cdecl cached_close (struct LEXICON_FILE *lf);
static void cache_close_some (struct LEXICON_FILE *lf, int cnt);
static FILE *cdecl cached_open (struct LEXICON_DESCRIPTION *ld,
                                struct LEXICON_FILE *lf, char *open_mode);
static struct LEXICON_FILE *cdecl cached_open_cluster (
  struct LEXICON_DESCRIPTION *ld,
  long cluster_number,
  char *open_mode);
static void cdecl lex_prnt_files (FILE *fo, struct LEXICON_FILE *lf, int typ);

/* ------------------------------------------------------------------------ */
struct LEXICON_DESCRIPTION *LEXICON_get_description (int lexicon_handle)
{
  struct LEXICON_DESCRIPTION *ld;

  if (lexicon_handle < 0 || lexicon_handle > LEX_DESCS) return (void *) 0;
  ld= & lexdesc [lexicon_handle];
  if (!ld->LEX_used) return (void *) 0;
  return ld;
}

/* ------------------------------------------------------------------------ */
int LEXICON_init (int lexicon_handle, char *lexicon_path)
{
  register struct LEXICON_DESCRIPTION *ld;
  int i;
  char *cp;

  if (lexdesc_inited == 0)
  {
    for (i= 0; i < LEX_DESCS; i++)
      lexdesc [i].LEX_used=0;
    lexdesc_inited= 1;
  }

  if (lexicon_handle < 0 || lexicon_handle > LEX_DESCS) return -1;
  ld= & lexdesc [lexicon_handle];

  if (ld->LEX_used)
  {
    release_files (ld->LEX_main_luts);
    release_files (ld->LEX_clusters);
    release_files (ld->LEX_index_tables);
    ld->LEX_main_luts    = (void *) 0;
    ld->LEX_clusters     = (void *) 0;
    ld->LEX_index_tables = (void *) 0;
  }

  cp= lexdesc [lexicon_handle].LEX_path;
  strcpy (cp, lexicon_path);

  if (lexicon_path == (char *) 0) return 0;

  get_files (cp, "*.LUT", 1, &ld->LEX_main_luts);
  get_files (cp, "*.HYX", 2, &ld->LEX_clusters);
  get_files (cp, "*.IDX", 3, &ld->LEX_index_tables);

  ld->LEX_used=1;

  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef MSDOS
static long get_counter (char *s, int idx)
{
  int ch;
  long val= 0L;

  for (; ch = s[idx] & 0x00FF; idx++)
  {
    if (ch >= '0' && ch <= '9') val = 16*val + ((long) (ch - '0'));      else
    if (ch >= 'A' && ch <= 'F') val = 16*val + ((long) (ch - 'A' + 10)); else
    if (ch >= 'a' && ch <= 'f') val = 16*val + ((long) (ch - 'a' + 10));
    else break;
  }
  return val;
}
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
static int get_files (
char *path,
char *pattern,
int mode,
struct LEXICON_FILE **lfp)
{
  int size;
#ifdef MSDOS
  char *fnd, *cp;
  struct LEXICON_FILE *lf;
  struct dta_buff *dta;
  long l;
#endif /* MSDOS */

  size= strlen (path);
  strcpy (&path[size], pattern);

  *lfp= (void *) 0;

#ifdef MSDOS
  while ((fnd= Fname_find (path, FA_FILE)) != (char *) 0)
  {
    lf = calloc (sizeof (struct LEXICON_FILE), 1);
    if (lf==(void *) 0)
    {
MEMORY:
      fprintf (stderr, "LEXICON_INIT: out of memory!!!\n");
      return -1;
    }
    if ((cp= strdup (fnd)) == (void *) 0) goto MEMORY;
    dta= Fget_dta ();
    lf->LEXF_fnm= cp;
    switch (mode)
    {
      case 1: /* LUT */
        lf->LEXF_p1= get_counter (dta->name, 4);
        lf->LEXF_p2= dta->size;
        lf->LEXF_p3= (lf->LEXF_p2 < LEXICON_LUT_SIZE);
        break;
      case 2: /* HYX */
        lf->LEXF_p1= get_counter (dta->name, 3);
        lf->LEXF_p2= dta->size;
        lf->LEXF_p3= (lf->LEXF_p2 < LEXICON_LUT_SIZE);
        break;
      case 3: /* IDX */
        lf->LEXF_p1= get_counter (dta->name, 3) * LEXICON_INDEX_SIZE;
        l= dta->size / ((long) sizeof (struct LEXICON_INDEX));
        lf->LEXF_p2= lf->LEXF_p1 + l;
        lf->LEXF_p3= (l < LEXICON_INDEX_SIZE);
        break;
    }

    *lfp=lf;
     lfp=&(lf->LEXF_next);
  }
#endif

  path [size] = 0;
  return 0;
}

/* ------------------------------------------------------------------------ */
static void release_files (struct LEXICON_FILE *lfp)
{
  struct LEXICON_FILE *lfp2;

  while ((lfp2= lfp) != (void *) 0) 
  {
    lfp= lfp->LEXF_next;
    if (lfp2->LEXF_open_mode [0])
    {
      cache_counter--;
      fclose (lfp2->LEXF_fp);
    }
    free (lfp2->LEXF_fnm);
    free (lfp2);
  }
}

/* ------------------------------------------------------------------------ */
static void cached_close (struct LEXICON_FILE *lf)
{
  if (lf->LEXF_open_mode[0] == 0) return;
  fclose (lf->LEXF_fp);
  lf->LEXF_open_mode[0]=0;
  cache_counter--;
}

/* ------------------------------------------------------------------------ */
static void cache_close_all ()          /* *alle* geoeffneten Files *aller* */
                                        /* verwendeten Lexica schliessen    */
{
  int i;

  for (i= 0; i < LEX_DESCS; i++)
  {
    if (lexdesc[i].LEX_used)
    {
      cache_close_some (lexdesc [i].LEX_main_luts,    32000);
      cache_close_some (lexdesc [i].LEX_clusters,     32000);
      cache_close_some (lexdesc [i].LEX_index_tables, 32000);
    }
  }
}

/* close a few open files ------------------------------------------------- */
static void cache_close_some (struct LEXICON_FILE *lf, int cnt)
{
  for (; lf != (struct LEXICON_FILE *) 0; lf= lf->LEXF_next)
    if (lf->LEXF_open_mode[0])
    {
      fclose (lf->LEXF_fp);
      lf->LEXF_open_mode[0]= 0;
      cache_counter--;
      cnt--;
      if (cnt <= 0) return;
    }
}

/* ------------------------------------------------------------------------ */
static FILE *cached_open (
struct LEXICON_DESCRIPTION *ld,
struct LEXICON_FILE *lf,
char *open_mode)
{
  FILE *f;

  if (strcmp (lf->LEXF_open_mode, open_mode) == 0) return lf->LEXF_fp;
  if (lf->LEXF_open_mode[0] != 0)
  {
    cached_close (lf);
  }
  else
  {
    if (cache_counter >= CACHE_FILES) cache_close_some (ld->LEX_main_luts,    1);
    if (cache_counter >= CACHE_FILES) cache_close_some (ld->LEX_clusters,     1);
    if (cache_counter >= CACHE_FILES) cache_close_some (ld->LEX_index_tables, 1);
    if (cache_counter >= CACHE_FILES) cache_close_all ();
    if (cache_counter >= CACHE_FILES) return (FILE *) 0;
  }

  if ((lf->LEXF_fp= f= fopen (lf->LEXF_fnm, open_mode)) == (FILE *) 0)
      return (FILE *) 0;
  strcpy (lf->LEXF_open_mode, open_mode);
  cache_counter++;

  return f;
}

/* ------------------------------------------------------------------------ */
static struct LEXICON_FILE *cached_open_cluster (
struct LEXICON_DESCRIPTION *ld,
long cluster_number,
char *open_mode)
{
  FILE *fp;
  struct LEXICON_FILE *lf;
  char *cp;

  for (lf= ld->LEX_clusters;
       lf != (struct LEXICON_FILE *) 0;
       lf= lf->LEXF_next)
  {
    if (lf->LEXF_p1 == cluster_number)
    {
      if ((fp= cached_open (ld, lf, open_mode))== (FILE *) 0)
        return (void *) 0;
      return lf;
    }
  }

  if (strcmp (open_mode, fopen_APPEND) != 0) return (void *) 0;

  /* Zum Schreiben auf einen Cluster kann auch ein      */
  /* bislang unbenutzter Cluster herangezogen werden.   */
  /* Geschrieben wird normalerweise mit "ab"            */

  if ((lf= (struct LEXICON_FILE *) calloc (sizeof (struct LEXICON_FILE), 1))
      == (struct LEXICON_FILE *) 0)
  {
MEMORY:
    fprintf (stderr, "OPEN new CLUSTER MC-%04lX (%s): out of memory!!!\n",
             cluster_number, open_mode);
    return (void *) 0;
  }

  if ((cp= malloc (strlen (ld->LEX_path)+16)) == (void *) 0) goto MEMORY;
  sprintf (cp, "%sMC-%04lX.HYX", ld->LEX_path, cluster_number);
  lf->LEXF_fnm= cp;
  lf->LEXF_p1= cluster_number;
  lf->LEXF_p2= 0L;
  lf->LEXF_p3= 1;

  lf->LEXF_next= ld->LEX_clusters;
  ld->LEX_clusters= lf;

  if ((lf->LEXF_fp= fopen (cp, open_mode)) == (FILE *) 0)
    return (struct LEXICON_FILE *) 0;
  strcpy (lf->LEXF_open_mode, open_mode);
  cache_counter++;

  return lf;
}

/* ------------------------------------------------------------------------ */
int LEXICON_get_entry (
int lexicon_handle,
long frame_index,
char *puffer,
long puffer_size)
{
  struct LEXICON_DESCRIPTION *ld;

  if ((ld= LEXICON_get_description (lexicon_handle)) == (void *) 0) return -1;

  return _LEXICON_get_entry (ld, frame_index, puffer, puffer_size,
                             (FILE *) 0, 1);
}

/* ------------------------------------------------------------------------ */
int _LEXICON_get_entry (
struct LEXICON_DESCRIPTION *ld,
long frame_index,
char *puffer,
long puffer_size,
FILE *fo,
int out_mode)
{
  struct LEXICON_FILE *lfidx;
  struct LEXICON_FILE *lfhyx;
  struct LEXICON_INDEX li;
  long offset;
  FILE *fi;
  int rc;

  lfidx= ld->LEX_index_tables;

  while (lfidx != (void *) 0)
  {
    if (frame_index >= lfidx->LEXF_p1 && frame_index < lfidx->LEXF_p2)
    {
      if ((fi= cached_open (ld, lfidx, fopen_READ)) == (FILE *) 0) return -1;
      offset= frame_index - lfidx->LEXF_p1;
      offset *= (long) sizeof (struct LEXICON_INDEX);
      fseek (fi, offset, 0);
      rc= fread ((char *) &li, sizeof (struct LEXICON_INDEX), 1, fi);
      if (rc < 1) return -1;

      if ((lfhyx= cached_open_cluster (ld, li.LEXI_cluster_number,
                                       fopen_READ))
        == (void *) 0) return -1;

      fi= lfhyx->LEXF_fp;
      fseek (fi, li.LEXI_begin, 0);
      offset= li.LEXI_end - li.LEXI_begin + 1L;

      switch (out_mode)
      {
        case 1:
          if (puffer_size-- <= 0L) return -1;
          while (offset-- > 0L) *puffer++ = (char) (fgetc (fi) & 0x00FF);
          break;
        case 2:
          ftransfer (fi, fo, offset);
          break;
      }
      return 0;
    }
  }

  return -1;
}

/* ------------------------------------------------------------------------ */
/* Bestimmung eines Clusters, der zur Aufnahme von Daten herangezogen       */
/* werden kann.                                                             */
long get_usable_cluster (struct LEXICON_DESCRIPTION *ld)
{
  struct LEXICON_FILE *lf;
  long max= 0;

  for (lf=ld->LEX_clusters; lf!=(struct LEXICON_FILE *) 0; lf=lf->LEXF_next)
  {
    if (lf->LEXF_p2 >= max) max= lf->LEXF_p2+1L;
    if (lf->LEXF_p3) return lf->LEXF_p2;
  }

  return max;
}

/* ------------------------------------------------------------------------ */
int LEXICON_add_entry (
int lexicon_handle,
long frame_index,
char *puffer,
long siz)
{
  struct LEXICON_DESCRIPTION *ld;

  ld = LEXICON_get_description (lexicon_handle);
  if (ld == (void *) 0) return -1;

  return _LEXICON_add_entry (ld, frame_index, puffer, siz);
}

/* ------------------------------------------------------------------------ */
int _LEXICON_add_entry (
struct LEXICON_DESCRIPTION *ld,
long frame_index,
char *puffer,
long siz)
{
  struct LEXICON_FILE *lfidx;
  struct LEXICON_FILE *lfhyx;
  struct LEXICON_INDEX li;
  long offset;
  FILE *fo;
  int rc;

  lfidx= ld->LEX_index_tables;

  while (lfidx != (void *) 0)
  {
    if (frame_index >= lfidx->LEXF_p1 && frame_index < lfidx->LEXF_p1 + LEXICON_INDEX_SIZE)
    {
      if ((lfhyx= cached_open_cluster (ld,
                    li.LEXI_cluster_number= get_usable_cluster (ld),
                    fopen_APPEND))
        == (struct LEXICON_FILE *) 0) return -1;

      fo= lfhyx->LEXF_fp;
      fseek (fo, (long) 0, 2);
      li.LEXI_begin= ftell(fo);
      li.LEXI_end= li.LEXI_begin - 1L + (long) siz;

      lfhyx->LEXF_p2 += (long) siz;
      lfhyx->LEXF_p3= (lfhyx->LEXF_p2 < LEXICON_LUT_SIZE);

      while (siz-- > 0L) fputc (*puffer++, fo);

      if (frame_index < lfidx->LEXF_p2)
      {
        if ((fo= cached_open (ld, lfidx, fopen_READ_WRITE)) == (FILE *) 0)
          return -1;
        offset= frame_index - lfidx->LEXF_p1;
        offset *= (long) sizeof (struct LEXICON_INDEX);
        fseek (fo, offset, 0);
        rc= fwrite ((char *) &li, sizeof (struct LEXICON_INDEX), 1, fo);
        if (rc < 1) return -1;
      }
      else
      {
        struct LEXICON_INDEX li2;

        fo = cached_open (ld, lfidx, fopen_APPEND);
        if (fo == (FILE *) 0) return -1;
        li2.LEXI_begin          = -1L;
        li2.LEXI_end            = -1L;
        li2.LEXI_cluster_number = -1L;
        while (lfidx->LEXF_p2 < frame_index)
        {
          rc= fwrite ((char *) &li2, sizeof (struct LEXICON_INDEX), 1, fo);
          if (rc < 1) return -1;
          (lfidx->LEXF_p2)++;
        }
        rc=fwrite ((char *) &li, sizeof (struct LEXICON_INDEX), 1, fo);
        if (rc < 1) return -1;
        (lfidx->LEXF_p2)++;
      }

      return 0;
    }
  }

  return -1;
}

/* ------------------------------------------------------------------------ */
long LEXICON_new_entry (int lexicon_handle)
{
  struct LEXICON_DESCRIPTION *ld;
  struct LEXICON_FILE *lf;

  if ((ld= LEXICON_get_description (lexicon_handle)) == (void *) 0)
    return -1L;

  for (lf= ld->LEX_index_tables;
       lf != (struct LEXICON_FILE *) 0;
       lf= lf->LEXF_next)
      if (lf->LEXF_p3) return lf->LEXF_p2;

  return -1L;
}

/* ------------------------------------------------------------------------ */
int LEXICON_print (FILE *fo)
{
  int i;

  for (i= 0; i<LEX_DESCS; i++) LEXICON_print_entry (fo, i);

  return 0;
}

/* ------------------------------------------------------------------------ */
int LEXICON_print_entry (FILE *fo, int nr)
{
  struct LEXICON_DESCRIPTION *ld;

  fprintf (fo, "Lexicon Entry %d \n", nr);
  ld= &lexdesc [nr];
  if (!ld->LEX_used)
  {
    fprintf (fo, "unused\n");
    return 0;
  }

  fprintf (fo, "--------------------\n");

  fprintf (fo, "Path: %s\n", ld->LEX_path);
  fprintf (fo, "LUT-Files:\n"); lex_prnt_files (fo, ld->LEX_main_luts, 1);
  fprintf (fo, "HYX-Files:\n"); lex_prnt_files (fo, ld->LEX_clusters, 2);
  fprintf (fo, "IDX-Files:\n"); lex_prnt_files (fo, ld->LEX_index_tables, 3);

  return 0;
}

/* ------------------------------------------------------------------------ */
static void lex_prnt_files (FILE *fo, struct LEXICON_FILE *lf, int typ)
{
  while (lf != (void *) 0)
  {
    switch (typ)
    {
      case 1:   /* spaeter genauer .... */
      case 2:
      case 3:
        fprintf (fo, "*  %s %08lX %08lX %ld\n",
                 lf->LEXF_fnm, lf->LEXF_p1, lf->LEXF_p2, lf->LEXF_p3);
        break;
    }
    lf= lf->LEXF_next;
  }
}

/* ------------------------------------------------------------------------ */
int LEXICON_flush (void)
{
  cache_close_all ();
  return 0;
}
