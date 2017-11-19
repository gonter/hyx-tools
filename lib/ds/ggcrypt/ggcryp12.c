/*
 *  FILE %ds/ggcrypt/ggcryp12.c
 *
 *  AFS shortcut authentication
 *
 *  written:       1995-05-10
 *  latest update: 1999-05-30 18:33:29
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/* ------------------------------------------------------------------------ */
int sca_check_signature (char *sca_sig_file, char *sca_signature)
{
  struct stat st;
#define SIG_SIZE 34
  char stored_signature [SIG_SIZE];
  FILE *fs;
  int rv= 0;
  time_t now;

  now= time((time_t *) 0);

  if (stat (sca_sig_file, &st) != 0
      || now - st.st_mtime > 86400      /* max 1 day */
      || now - st.st_mtime < 0          /* file will be written in future! */
      || (fs= fopen (sca_sig_file, "rb")) == (FILE *) 0
     )
    return -1;

  if (fread (stored_signature, 1, 32, fs) == 32)
  {
    stored_signature[32]= 0;
    if (strcmp (stored_signature, sca_signature) == 0) rv= 1;
  }

  fclose (fs);

  return rv;
}
