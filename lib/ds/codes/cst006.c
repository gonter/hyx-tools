/*
 *  File %dpp/codes/cst006.c
 *
 *  test module for cs006.c
 *
 *  written:       1992-12-29: <Gerhard.Gonter@wu-wien.ac.at>
 *  latest update: 1995-12-10
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
#ifdef TEST1
#define JUNK_CNT 1
static char *junk_list [JUNK_CNT] = { "junk" };

#define NONSENSE_CNT 1
static char *nonsense_list [NONSENSE_CNT] = { "nonsense" };

#define EBCDIC_CNT 1
static char *ebcdic_list [EBCDIC_CNT] = { "ebcdic" };
#endif

#define PC_CNT 2
static char *pc_list [PC_CNT] = { "pc", "ascii" };

#define MAC_CNT 2
static char *mac_list [MAC_CNT] = { "mac", "ascii" };

#define ENTITY_CNT 1
static char *entity_list [ENTITY_CNT] = { "entity" };

/* ------------------------------------------------------------------------ */
static long table[256];
static struct CS_record *recs;

#define N_MATCH_TABLE 1
static char *MATCH_TABLE [N_MATCH_TABLE] =
{
  "*"
} ;

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv[]);
int cdecl test_table (char *src[], int sc, char *dst[], int dc, int ttype);

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  argc= argv[0][0];

  recs= cs_parse_code_table ("c:/etc/codes/table", MATCH_TABLE,
                             N_MATCH_TABLE, 1, 0, 10);

  if (recs == (struct CS_record *) 0)
  {
    printf ("error parsing table!\n");
    exit(0);
  }

#ifdef TEST1
  test_table (junk_list, JUNK_CNT, nonsense_list, NONSENSE_CNT, CSft_number);
  test_table (junk_list, JUNK_CNT, junk_list, JUNK_CNT, CSft_number);
  test_table (pc_list, PC_CNT, mac_list, MAC_CNT, CSft_number);
  test_table (pc_list, 1,        mac_list, 1       , CSft_number);
  test_table (mac_list, MAC_CNT, pc_list, PC_CNT, CSft_number);
#endif /* TEST1 */

  test_table (mac_list, 1,        pc_list, 1       , CSft_number);
  test_table (mac_list, MAC_CNT, entity_list, ENTITY_CNT, CSft_string);

#ifdef TEST1
  test_table (pc_list, PC_CNT, ebcdic_list, EBCDIC_CNT, CSft_number);
#endif /* TEST1 */

  return 0;
}

/* ------------------------------------------------------------------------ */
int test_table (char *src[], int sc, char *dst[], int dc, int ttype)
{
  int rc;
  int i;

  printf ("testing: (");
  for (i=0; i<sc; i++) printf (" %s", src[i]);
  printf (" )  to  (");
  for (i=0; i<dc; i++) printf (" %s", dst[i]);
  printf (" ):\n");

  rc= cs_records2table (recs, src, sc, dst, dc, ttype, table);
  printf ("records2table: rc=%d\n", rc);

  if (ttype == CSft_number)
  {
    for (i= 0; i < 256; i++)
      printf ("table[0x%02X]=0x%02lX%s\n", i, table[i],
      ((table[i] == -1L) ? " <----" : ""));
  }
  else if (ttype == CSft_string)
  {
    for (i= 0; i < 256; i++)
      printf ("table[0x%02X]=%s%s\n", i,
      ((((char *) table[i]) == ((char *) 0)) ? "" : ((char *) table[i])),
      ((((char *) table[i]) == ((char *) 0)) ? " <----" : ""));
  }
  else
  {
    fprintf (stderr, "invalid table type %d\n", ttype);
  }

  return 0;
}
