/*
 *  FILE %ds/dbx/dbx_1001.c
 *
 *  database processing: open a DBF file
 *
 *  Machine Specifics: Only for MSDOS!
 *
 *  written:       1996-11-26
 *  latest update: 1996-11-26 17:53:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/dirty.h>
#include <gg/dpp.h>
#include <gg/dbx.h>

#define DEBUG

/* ------------------------------------------------------------------------ */
struct DBX_FILE_DESCRIPTOR *dbx_open_dbf (char *fnm, char *name)
{
  FILE *fi;
  struct DBX_FILE_DESCRIPTOR *dbxf;
  struct DBX_SCHEMA *schema;
  struct DBX_FIELD_DESCRIPTOR *dbx_fdesc;
  char pfx [DBX_DBF_PFX_SIZE];
  char dbf_fdesc [DBX_DBF_FDESC_SIZE];
  int hdr_size;
  int fld_cnt;
  int i, ch;

  if ((fi= fopen (fnm, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "dbx/dbf: cant read '%s'\n", fnm);
    return (struct DBX_FILE_DESCRIPTOR *) 0;
  }

  if ((dbxf= dbx_new_file_descriptor()) == (struct DBX_FILE_DESCRIPTOR *) 0)
  {
NO_MEM:
    fclose (fi);
    fprintf (stderr, "dbx/dbf: no memory\n", fnm);
    return (struct DBX_FILE_DESCRIPTOR *) 0;
  }

  dbxf->fi1= (void *) fi;

  fread (pfx, 1, DBX_DBF_PFX_SIZE, fi);

  hdr_size= msdos_get_int (pfx + DBX_DBF_off_hdr_size);
  dbxf->header_size= (long) (hdr_size+1);
  dbxf->record_size= (long) msdos_get_int (pfx + DBX_DBF_off_rec_size);
  dbxf->is_fixed_record_size= 1;
  fld_cnt= hdr_size / 32 - 1;

#ifdef DEBUG
  printf (">> hdr_size= %d  n_rec= %d\n", hdr_size, fld_cnt);
  dump (stdout, pfx, DBX_DBF_PFX_SIZE);
#endif /* DEBUG */

  schema= dbx_new_schema (fld_cnt, name);
  dbxf->schema= schema;

  for (i= 0; i < fld_cnt; i++)
  {
    fread (dbf_fdesc, 1, DBX_DBF_FDESC_SIZE, fi);

    if ((dbx_fdesc= dbx_new_field_descriptor())
        == (struct DBX_FIELD_DESCRIPTOR *) 0) goto NO_MEM;

    schema->fields [i]= dbx_fdesc;
    dbx_fdesc->size= msdos_get_int (dbf_fdesc + DBX_DBF_off_fld_size);
    dbx_fdesc->name= strdup_max (dbf_fdesc, DBX_DBF_NAME_SIZE);

    switch (ch= dbf_fdesc [DBX_DBF_off_fld_type])
    {
      case 'C':
        dbx_fdesc->type= DBX_Fty_long;
        break;
      case 'N':
        dbx_fdesc->type= DBX_Fty_string;
        break;
      default:
        printf ("dbx/dbf: unknown field type '%c' (0x%02X)\n", ch, ch);
        break;
    }

    /**** T2D: all data elements are strings! *****/
    dbx_fdesc->type= DBX_Fty_string;

#ifdef DEBUG
    printf (">> field [%d]; name='%s' size=%d type=%c\n",
            i, dbx_fdesc->name, dbx_fdesc->size,
            dbf_fdesc [DBX_DBF_off_fld_type]);
    dump (stdout, dbf_fdesc, DBX_DBF_FDESC_SIZE);
#endif /* DEBUG */
  }

printf (">> return dbxf\n");
  return dbxf;
}
