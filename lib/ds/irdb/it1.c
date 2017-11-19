/*
 *  FILE %ds/irdb/it1.c
 *
 *  written:        1996-04-06
 *  lateslt update: 1996-04-06  8:28:55
 *
 */

#include <stdio.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv []);
int lmd2_cnt (struct IRDB_HANDLE *hnd, char *word, char *docid);
int lmd2_meta (struct IRDB_HANDLE *hnd, char *slot, char *value);
int irdb_t1 (void);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv [])
{
  irdb_t1 ();

#ifdef MSDOS
  argc;
  argv;
#endif /* MSDOS */

  return 0;
}

/* ------------------------------------------------------------------------ */
#define LMD1_CNT 2
static char *LMD1 [LMD1_CNT] =
{
  "wordcount",
  (char *) 0
} ;

#define LMD1b_CNT 2
static char *LMD1b [LMD1b_CNT] =
{
  "docs",
  (char *) 0
} ;

/* ------------------------------------------------------------------------ */
int lmd2_cnt (
struct IRDB_HANDLE *hnd,
char *word,
char *docid)
/* wordcount.<word>.docs.<docid>++ */
{
  struct IRDB_HANDLE *wi;
  long *inf;

  LMD1 [1]= word;
  LMD1b [1]= docid;

printf ("\n****************\n** wordcount.%s.docs.%s++\n", word, docid);

  if ((wi= irdb_locate_handle (hnd, LMD1, LMD1_CNT, 1, (long) IRDBty_struct))
           == (struct IRDB_HANDLE *) 0
      || (inf= irdb_locate_info (wi, LMD1b, LMD1b_CNT, 1, (long) IRDBty_int))
               == (long *) 0
     ) return -1;

  (*inf)++;

  return 0;
}

/* ------------------------------------------------------------------------ */
#define LMD2_CNT 2
static char *LMD2 [LMD2_CNT]=
{
  "meta",
  (char *) 0
} ;

/* ------------------------------------------------------------------------ */
int lmd2_meta (
struct IRDB_HANDLE *hnd,
char *slot,
char *value)
{
  LMD2 [1]= slot;

  irdb_dbg_replace_string (hnd, LMD2, LMD2_CNT, value);

  return 0;
}

/* ------------------------------------------------------------------------ */
#define LMD3_CNT 3
static char *LMD3 [LMD3_CNT]=
{
  "zcounter",
  (char *) 0,
  (char *) 0
} ;

/* ------------------------------------------------------------------------ */
int irdb_t1 ()
{
  struct IRDB_HANDLE *hnd;
  char *docid;

  if ((hnd= irdb_new_struct_handle ("lmd3_test", (long) IRDBty_struct))
      == (struct IRDB_HANDLE *) 0)
  {
    printf ("can't get struct handle!\n");
    return -1;
  }

  lmd2_meta (hnd, "urxn",  "urxn_value");
  lmd2_meta (hnd, "urxn2", "urxn_2value");
  lmd2_meta (hnd, "junk",  "maier");

  docid= "01";
  lmd2_cnt (hnd, "franz", docid);
  lmd2_cnt (hnd, "iris", docid);
  lmd2_cnt (hnd, "iris", docid); lmd2_cnt (hnd, "iris", docid);
  lmd2_cnt (hnd, "iris", docid); lmd2_cnt (hnd, "iris", docid);
  lmd2_cnt (hnd, "irina", docid);
  lmd2_cnt (hnd, "gerhard", docid);
  lmd2_cnt (hnd, "karl", docid);

  printf ("\n*********************** TEST *********************\n");
  LMD1 [1]= "iris";
  irdb_set_long (hnd, LMD1, LMD1_CNT, 4711L);
  LMD1 [1]= "gerhard";
  irdb_pre_increment_long (hnd, LMD1, LMD1_CNT, 4711L);
  LMD1 [1]= "gerald";
  irdb_post_increment_long (hnd, LMD1, LMD1_CNT, 4711L);

  printf ("\n*********************** TEST *********************\n");
  LMD3 [1]= "iris";
  irdb_set_long (hnd, LMD3, 2, 4711L);
  LMD3 [1]= "gerhard";
  irdb_pre_increment_long (hnd, LMD3, 2, 4711L);
  LMD3 [2]= "gerhard";
  irdb_pre_increment_long (hnd, LMD3, 3, 4711L);
  LMD3 [1]= "gerald";
  irdb_post_increment_long (hnd, LMD3, 2, 4711L);

  printf ("-----------------\ndumping\n");
  irdb_dump_to_file ("@@irdb.dmp", hnd);

  return 0;
}
