/*
 *  FILE c:/usr/sbr/archead.c
 *
 *  Verarbeiten von Archiv Files
 *
 *  1989 01 20
 *  1989 07 02: aus ARCFILES.C abgewandelt
 *  1990 02 03: Revision
 *
 */

# include <stdio.h>
# include <gg/archead.h>

# pragma check_stack(off)

/* ------------------------------------------------------------------------ */
int get_arc_head (
FILE *fi,               /* Archiv File, bin„r er”ffnet  */
struct heads *head)     /* ARC-Header                   */
/* RETURN: Compression Method:                          */
/*          -1 Error or no Archive                      */
/*           0 EOF: no more files in archive            */
/*          >0 Archiv File gefunden; head gltig        */
{ int ch;

  if (head == (struct heads *) 0) return -1;
  if (feof (fi)) return -1;             /* EOF ??? kommt berraschend */
  ch =fgetc (fi);
  if (ch != 0x01A) return -1;           /* no Archive */
  ch =fgetc (fi);
  if (ch == 0x00) return 0;             /* EOF */
  fread ((char *) head, 27, 1, fi);
  fseek (fi, head->size, 1);
  return ch;
}
