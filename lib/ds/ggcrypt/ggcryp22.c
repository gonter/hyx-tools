/*
 *  FILE %ds/ggcrypt/ggcryp22.c
 *
 *  simple file encryption algorithms
 *  see: ggc_block_cfb
 *
 *  written:       1997-10-05
 *  latest update: 1997-10-05  9:36:36
 *  $Id: ggcryp22.c,v 1.4 2006/11/08 06:40:09 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gg/fileio.h>
#include <gg/strings.h>
#include <gg/attlist.h>
#include <gg/dpp.h>
#include <gg/ggcrypt.h>

#define BS GGC_BUFFER_SIZE

static int analyze_block (char *c, char *tag, int size, long *fs);

/* ------------------------------------------------------------------------ */
int ggc_stream_2decrypt (
struct GG_CRYPT *ggc,
FILE *fi,                       /* input stream                             */
FILE *fo)                       /* output stream                            */
{
  char *buffer= (char *) 0;
#define ST_pre  0
#define ST_file 1
#define ST_post 2
  int state= ST_pre;
  int rv= -2;
  int rc;
  int i;
  char *cp;
  long file_size= -1;

  if ((buffer= malloc (BS)) == (char *) 0)
  {
    fprintf (stderr, "can't allocate buffer!\n");
    goto STOP;
  }

  for (;;)
  {
    rc= fread (buffer, 1, BS, fi);
    if (rc <= 0) break;

    ggc_block_encrypt (ggc, buffer, rc);

    switch (state)
    {
      case ST_pre:
        cp= buffer;
        for (i= 0; i < rc; i++)
        {
          if (   cp [0] == '<' && i+3 < rc /* uh, this is ugly! */
              && cp [1] == 'C'
              && cp [2] == 'H'
              && cp [3] == '>'
             )
          {
            int skip;
            int block_size;

            skip= analyze_block (cp, "CH", rc-i, &file_size);
/** fprintf (stderr, "skip='%d' file_size=%ld\n", skip, file_size); **/
            block_size= rc-i-skip;
            if (block_size > file_size) block_size= file_size;
            file_size -= block_size;
            fwrite (cp+skip, 1, block_size, fo);
            state= ST_file;

            break;
          }

          cp++;
        }
        break;

      case ST_file:
        if (rc > file_size) rc= file_size;
        fwrite (buffer, 1, rc, fo);
        file_size -= rc;
        if (file_size <= 0L) goto DONE;
        break;

        cp= buffer;
        for (i= 0; i < rc; i++)
        {
          if (*cp == '<' && strncmp (cp+1, "CT>", 3) == 0)
          {
            int skip;
            long fs;
            fwrite (buffer, 1, rc-i, fo);
            analyze_block (cp, "CT", rc-i, &fs);
fprintf (stderr, "skip='%d'\n", skip);
            goto DONE;
          }

          cp++;
        }

        fwrite (buffer, 1, rc, fo);
        break;
    }
  }

DONE:
  if (state == ST_file)
  {
    rv= 0;  /* all went fine, set OK result code */
  }
  else
  {
    fprintf (stderr, "decoder did not find data!\n");
    rv= -2;
  }

STOP:
  free_or_what (buffer);

  return rv;
}

/* ------------------------------------------------------------------------ */
static int analyze_block (char *c, char *tag, int size, long *fs)
{
  int i= 0;
  char *cp;
  int l;

  l= strlen (tag);
  cp= c;
  for (i= 0; i < size; i++)
  {
    if (strncmp (cp, "<size>", 6) == 0)
    {
      int y;
      for (y= 6;; y++)
      {
        if (cp[y] == '\n') { cp[y]= 0; break; }
      }
      *fs= get_parameter_value (cp+6);
      /*** fprintf (stderr, ">>> size: %ld\n", *fs); ***/
    }

    if (cp[0] == '<' && cp[1] == '/'
        && strncmp (cp+2, tag, l) == 0
        && cp[l+2] == '>'
       )
      return i+l+3;
    cp++;
  }

  fprintf (stderr, "ERROR: did not find end tag '%s'\n", tag);

  return -1;
}
