/*
 *  File %dpp/codes/cs001.c
 *
 *  parse the code set table
 *
 *  written:       1992-12-25: g.gonter@ieee.org
 *                 1993-01-06: GG, match fields, filter
 *  latest update: 1995-12-10
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/fileio.h>
#include <gg/dpp.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
static long tnum_records= 0L;
static long unum_records= 0L;
static long alloc_record= 0L;
static long alloc_field=  0L;
static char *out_of_memory= "out of memory!\n";

/* ------------------------------------------------------------------------ */
struct CS_record *cs_parse_code_table (
char *fn,
char *matching_field [],
int field_cnt,
int filter,
int max_warnings)
{
  FILE *fi= (FILE *) 0;
  struct CS_field **fapp;
  struct CS_field *csf= (struct CS_field *) 0;
  struct CS_record *csr= (struct CS_record *) 0;
  struct CS_record *first= (struct CS_record *) 0;
  struct CS_record **rapp= &first;
  char *lin;
  char *nam;
  int ch;
#define STAT_start      0
#define STAT_name       1
#define STAT_equal      2
#define STAT_number     3
#define STAT_string     4
#define STAT_backslash  5
#define STAT_endfield   6
#define STAT_endline    7
#define STAT_identifier 8
  int status= STAT_start;
  int idx= 0;
  int line_num= 1;
  int use_record= 0;
  int use_field= 0;

  if ((lin= malloc (1024)) == (char *) 0
      || (nam= malloc (1024)) == (char *) 0
      || (fi= fopen (fn, "rb")) == (FILE *) 0
     ) goto ERR;

  tnum_records= 0L;
  unum_records= 0L;

  if ((csr= calloc (sizeof (struct CS_record), 1)) == (struct CS_record *) 0)
    goto STOP;

  alloc_record++;
  fapp= &csr->CSr_fields;

  for (;;)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) ch= '\n';

    if (ch == '\r') continue;
    if (ch == '#')
    {
      while (ch != '\n' && !feof (fi)) ch= fgetc (fi) & 0x00FF;
      /* continue; */    /* note: the parser below must see the line feed!! */
      if (feof (fi)) ch= '\n';
    }

/** printf ("### status=%d ch=%c idx=%d\n", status, ch, idx); **/

    switch (status)
    {
      case STAT_start:
        if (ch == '\n' || ch == ' ' || ch == '\t') break;
NEW_RECORD:
        use_record= 0;
        tnum_records++;
NEW_FIELD:
        use_field= 0;
        status= STAT_name;
        idx= 0;

      case STAT_name:
        if (ch == ' ' || ch == '\t') break; /* ingore spaces here */
        if (ch == '=')
        {
          nam [idx]= (char) 0;
          status= STAT_equal;
          csf= (struct CS_field *) 0;
          idx= 0;

          /* find out if this field should be used at all.              */
          if (!filter)
          {
            use_field= 1;               /* if unfiltered, then          */
            use_record= 1;              /* use everything for now       */
          }
          else
          {
            if (match_array (matching_field, field_cnt, nam) >= 0)
            {
              use_field= 1;
              use_record= 1;
            }
          }
          if (!use_field) break;

          if ((csf= calloc (sizeof (struct CS_field), 1))
            == (struct CS_field *) 0) goto STOP;
          alloc_field++;
          csf->CSf_name= strdup (nam);
          *fapp=  csf;
           fapp= &csf->CSf_next;
          csr->CSr_count++;
          break;
        }
        nam [idx++]= (char) ch;
        break;

      case STAT_equal:
        if (ch == ' ' || ch == '\t') break;
        if (ch >= '0' && ch <= '9')
        {
          lin [idx++]= (char) ch;
          status= STAT_number;
          break;
        }
        if (ch == '\"')
        {
          status= STAT_string;
          break;
        }
        if ((ch >= 'A' && ch <= 'Z')
          ||(ch >= 'a' && ch <= 'z')
          || ch >= '_'
          || ch == '$' )
        {
          lin [idx++]= (char) ch;
          status= STAT_identifier;
          break;
        }
        break;

      case STAT_number:
        if (ch == ' ' || ch == '\t' || ch == '\n')
        {
          lin [idx]= 0;
          if (csf != (struct CS_field *) 0)
          {
            csf->CSf_type= CSft_number;
            csf->CSf_number= get_parameter_value (lin);
/*** printf ("## [%d] field: name=\'%s\' type=number number=%ld\n",
  line_num, csf->CSf_name, csf->CSf_number); ***/
          }
          cs_count_attribute (nam, CSft_number, csf != (void *) 0);
          status= (ch == '\n') ? STAT_endline : STAT_endfield;
          break;
        }

        if ((ch >= '0' && ch <= '9')
          ||(ch >= 'a' && ch <= 'f')
          ||(ch >= 'A' && ch <= 'F')
          || ch == 'x' || ch == 'X')
        {
          lin [idx++]= (char) ch;
        }
        /* else: syntax error! #### */
        break;

      case STAT_string:
        switch (ch)
        {
          case '\"':
          case '\n':
TREAT_AS_STRING:
            lin [idx]= 0;
            if (csf != (struct CS_field *) 0)
            {
              csf->CSf_type= CSft_string;
              csf->CSf_string= strdup (lin);
/*** printf ("## [%d] field: name=\'%s\' type=string string=\'%s\'\n",
  line_num, csf->CSf_name, csf->CSf_string); ***/
            }
            cs_count_attribute (nam, CSft_string, csf != (void *) 0);
            status= (ch == '\n') ? STAT_endline : STAT_endfield;
            break;
          case '\\':
            status=STAT_backslash;
            break;
          default:
            lin [idx++] = (char) ch;
            break;
        }
        break;

      case STAT_backslash:
        lin [idx++]= (char) ch;
        status= STAT_string;
        break;

      case STAT_identifier:
        if (ch == ' ' || ch == '\t' || ch == '\n')
        {
          struct CS_field *id_csf;

          lin [idx]= 0;
          status= (ch == '\n') ? STAT_endline : STAT_endfield;
          cs_count_attribute (nam, CSft_identifier, csf != (void *) 0);
          if (csf == (struct CS_field *) 0) break;

          if ((id_csf= cs_find_field (first, "def", CSft_string, lin,
                                      0L, "val")) == (struct CS_field *) 0)
          {
            if (max_warnings-- > 0)
            {
              fprintf (stderr,
  "warning: %s(%d) identifier \'%s\' undefined; treated as string!\n",
                fn, line_num, lin);
              if (max_warnings == 0)
                fprintf (stderr,
                  "warning: *** no further warnings are issued!\n");
            }
            goto TREAT_AS_STRING;
          }

          csf->CSf_type= id_csf->CSf_type;
          csf->CSf_number= id_csf->CSf_number;
          csf->CSf_string= id_csf->CSf_string;
/*** printf ("## [%d] field: name=\'%s\' type=number number=%ld\n",
  line_num, csf->CSf_name, csf->CSf_number); ***/
          break;
        }

        if ((ch >= '0' && ch <= '9')
          ||(ch >= 'a' && ch <= 'z')
          ||(ch >= 'A' && ch <= 'Z')
          || ch == '_' || ch == '$' )
        {
          lin [idx++]= (char) ch;
        }
        /* else: syntax error! #### */
        break;

      case STAT_endfield:
        if (ch == ' ' || ch == '\t') break;
        if (ch == '\n')
        {
          status= STAT_endline;
          break;
        }
        goto NEW_FIELD;
        break;

      case STAT_endline:
        if (ch == '\n') break;
        if (ch == ' ' || ch == '\t')
        {
          status = STAT_endfield;
          break;
        }
        if (use_record)
        {
          *rapp=  csr;
           rapp= &csr->CSr_next;
          unum_records++;
          csr= calloc (sizeof (struct CS_record), 1);
          alloc_record++;
          if (csr == (struct CS_record *) 0) goto STOP;
          fapp= &csr->CSr_fields;
        }
        else
        {
          cs_free_fields (csr->CSr_fields, /* ((void *)()), */ 1, 1);
          memset (csr, 0, sizeof (struct CS_record));
        }
        goto NEW_RECORD;
        break;
    }

    if (ch == '\n') line_num++;
    if (feof (fi))
    {
      if (use_record)
      {
        *rapp= csr;
        rapp= &csr->CSr_next;
        unum_records++;
      }
      break;
    }
  }

  free (csr);  /* last record structure was not used */
  if (0)
  {
STOP:
    fprintf (stderr, out_of_memory);
  }

ERR:
  fclose_or_what (fi);
  free_or_what (lin);
  free_or_what (nam);

  fprintf (stderr, "%ld records = %ld bytes\n",
    alloc_record, alloc_record*(sizeof (struct CS_record)) );
  fprintf (stderr, "%ld fields = %ld bytes\n",
    alloc_field, alloc_field*(sizeof (struct CS_field)) );

  return first;
}

/* ------------------------------------------------------------------------ */
long cs_tnum_records () { return tnum_records; }
long cs_unum_records () { return unum_records; }
