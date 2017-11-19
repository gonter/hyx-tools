/*
 *  include FILE <gg/fileio.h>
 *
 *  written:       1988 03 19
 *                 1991 01 28: revision
 *  latest update: 1997-10-24 12:04:02
 *
 */

#ifndef __GG_fileio__
#define __GG_fileio__

#include <gg/floskel.h>

/* diagnostic values: (*OLD*) --------------------------------------------- */
#define ERR_file_not_found     17     /* f4read */
#define ERR_name_not_found     18     /* .      */
#define ERR_version_not_found  19     /* .      */
#define ERR_eof                20     /* .      */

#define TEMPFILE "tmptmp.tmp"

#define FXOPEN(fn,fh,dfh,m,f) \
 {if ((fn) == (char *) 0 || *fn == 0 || (fn[0] == '-' && fn[1] == 0)) \
  { fh= dfh; f= 0;} else { fh= fopen (fn, m); f= 1; }}

#define FXCLOSE(fh,f) {if (f && fh != (FILE *) 0) fclose (fh);}

/* %sbr/fileio.c: --------------------------------------------------------- */
void cdecl set_filemode (int num, int nid, char *ident [], int slng);
int cdecl get_identifier (char *n);
int cdecl get_Sid (void);

#ifdef _FILE_DEFINED
int cdecl f4fscan (FILE *fi, FILE *fo, int *objekttyp, char *objekt,
            int flags);
#endif /* _FILE_DEFINED */

int cdecl f4f_read (char *filename, char *k_name, int *k_version, int flags,
            char *daten1 [], int daten1_zahl,
            char *daten2 [], int daten2_zahl,
            char *daten3 [], int daten3_zahl,
            char *daten4 [], int daten4_zahl);
int cdecl f4f_write (char *filename, char *k_name, int *k_version, int flags,
            char *daten1 [], int daten1_zahl,
            char *daten2 [], int daten2_zahl,
            char *daten3 [], int daten3_zahl,
            char *daten4 [], int daten4_zahl);

#ifdef _FILE_DEFINED
void cdecl f4f_wds (FILE *fo,
             char *daten1 [], int daten1_zahl,
             char *daten2 [], int daten2_zahl,
             char *daten3 [], int daten3_zahl,
             char *daten4 [], int daten4_zahl);
#endif /* _FILE_DEFINED */

/* %sbr/file2buf.c: ------------------------------------------------------- */
long cdecl read_file2buffer (char **buffer, char *fnm, long limit);

#ifdef _FILE_DEFINED
/* file2low.c */ int cdecl file_to_lower (char *fn, FILE *fo);
/* file2low.c */ int cdecl file_to_upper (char *fn, FILE *fo);
/* fclosec.c  */ int cdecl fclose_or_what (FILE *f);
#endif /* _FILE_DEFINED */

#endif
