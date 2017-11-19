/*
 *  FILE ~/usr/sbr/lzhhead.c
 *
 *  processing of LZH-archives
 *
 *  written:       1990 05 26
 *  latest update: 1994-11-12
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/lzhhead.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int get_lzh_head (
FILE *fi,                       /* archive file, binary opened              */
struct LZH_HEAD *head)          /* LZH-Header                               */
/* RETURN:                                                                  */
/*          -1 error or no archive                                          */
/*           0 EOF: no more files in archive                                */
/*          >0 archived file found; head is valid                           */
{
  int size;
  long skip;

  if (head == (struct LZH_HEAD *) 0) return -1;

  if (feof (fi)) return -1;             /* EOF ??? this is unexpected !!    */

  fread ((char *) head, 1, LZH_FIX_HEAD_SIZE, fi);
  if (head->LZH_header_size == 0)
     return 0;                          /* EOA: End-Of-Archive              */

  if (strncmp (head->LZH_header_sign, LZH_SIGN_1, 5) != 0)
     return -1;

  size = head->LZH_name_length;
  skip = head->LZH_size_compressed+2L;  /* looks like a 16 bit checksum     */
                                        /* we don't check this              */

  if (size > 64)
     {
       skip += (long) size-64;
       size  = 64;                      /* truncate file name,              */
                                        /* this is very dangerous           */
     }

  if (feof (fi)) return -1;             /* EOF ??? this is unexpected !!    */
  fread (head->LZH_name, 1, size, fi);
  fseek (fi, skip, 1);                  /* jump to next file header         */

  return 1;
}
