/*
 *  FILE ~/usr/sgml/hytxt002.c
 *
 *  scan one frame entry from a file stream
 *
 *  written:       1990 02 14
 *                 1991 03 02: frame buffering
 *                 1992 12 14: revision
 *                 1994-06-23: MD5 checksum
 *  latest update: 1994-12-11
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef NO_MD5
#include <contrib/global.h>
#include <contrib/md5.h>
#include <contrib/md5gg.h>
#endif
#include <gg/hytxt.h>

static char FRAME_BEGIN [] = "Frame";
static char FRAME_END   [] = "/Frame";
static char FRAME_ATTR  [] = "FrAttr";

static char FRAME_NAME [FRAME_NAME_LNG];

static char *ERR_MSG= "hytxt_scan_entry: out of memory!\n";

/* STATUS_CODES: ---------------------------------------------------------- */
#define STAT_start           0  /* initial state of the scanner             */
#define STAT_tag_open      101  /* tag open found                           */
#define STAT_frame           1  /* scanning through a 'Frame' tag.          */
#define STAT_frame_ok        2  /* 'Frame' tag identified, scan rest of tag */
#define STAT_frame_name      3  /* reading the frame name                   */
#define STAT_frame_space     4  /* a white space within a frame name        */
#define STAT_frame_done      5  /* 'Frame' tag completetly scanned in       */
#define STAT_in_frame        6  /* text within a frame                      */
#define STAT_701           701
#define STAT_7               7
#define STAT_770           770
#define STAT_781           781
#define STAT_782           782
#define STAT_783           783
#define STAT_784           784
#define STAT_785           785
#define STAT_789           789
#define STAT_8               8
#define STAT_eframe_name     9  /* read over frame name in end tag          */
#define STAT_end_of_frame   10  /* end of frame found                       */

/* ------------------------------------------------------------------------ */
int hytxt_scan_entry (
FILE *fi,               /* hypertext file: opened binary                    */
long *fi_pos,           /* actual position in the file                      */
struct HYTXT_FRAME *fd, /* scanned frame entry                              */
int scan_mode,          /* HYXSM_no_attributes: don't scan frame attributes */
                        /* HYXSM_no_allocation: don't allocate string space */
char *md5_cks)          /* finger print of a frame, generated on the fly    */
{
  int ch;                       /* character just read                      */
  int ret_val= 0;               /* return value of this function            */
  long pos;                     /* actual position in the file              */
  long pos_beg= 0L;             /* position of the FRAME_BEGIN -tag         */
  long pos_end= 0L;             /* position of the FRAME_END   -tag         */
  int status= STAT_start;       /* state of the scanner automaton           */
  int cmp_idx= 0;               /* index in the compare-string              */
  int name_lng= 0;              /* length of frame name                     */
  struct HYTXT_ATTR *attr=      /* actual hypertext attribute               */
    (struct HYTXT_ATTR *) 0;
  char *buffer= (char *) 0;
  int buffer_size;
#ifndef NO_MD5
  MD5_CTX context;
  char md5_buf [2];
  unsigned char digest [16];    /* message digest                           */
#endif

  if ((buffer_size= fd->hytxt_frame_bsize) > 0)
    if ((buffer= fd->hytxt_frame_buffer) == (char *) 0)
      buffer_size= 0;
   
#ifndef NO_MD5
  if (md5_cks != (char *) 0) MD5Init (&context);
#else
  md5_cks;
#endif

  for (pos= *fi_pos;; pos++)
  {
    ch= fgetc (fi) & 0x00FF;
#ifndef NO_MD5
    if (md5_cks != (char *) 0)
    {
      md5_buf[0]= (char) ch;
      MD5Update (&context, (unsigned char *) md5_buf, 1);
    }
#endif


    if (feof (fi))
    {
      if (status == STAT_in_frame)      /* frame opened but not closed      */
        goto STATUS_10;
      ret_val= 1;
      break;
    }

    if (buffer_size > 0 && status != STAT_start)
    {
      *buffer++= (char) ch;
      buffer_size--;
    }

    switch (status)
    {
      case STAT_start:                  /* TEXT; looking for a TAG-start    */
        if (ch == '<')                  /* '<' */
        {
          pos_beg= pos;
          status= STAT_tag_open;
          if (buffer_size > 0)
          {
            *buffer++= (char) ch;
            buffer_size--;
          }
        }
        break;
      case STAT_tag_open:       /* TAG; suche nach Frame-Tag                */
        if (ch == ':')          /* das ist die Kurzform fuer das Frame-Tag  */
        {                       /* darauf folgt sofort der Frame Name       */
          name_lng= 0;
          status= STAT_frame_space;
          break;
        }
        if (ch == FRAME_BEGIN [0])      /* '<F' */
        {
          cmp_idx= 1;
          status= STAT_frame;
          break;
        }
        if (ch == ' ' || ch == '\t' || ch == 0x0D || ch == 0x0A) break;
        status= STAT_start;
        break;
      case STAT_frame:
        if (ch == FRAME_BEGIN [cmp_idx])
        {
          cmp_idx++;
          if (FRAME_BEGIN [cmp_idx] == 0) status= STAT_frame_ok;
        }
        else
        {
          cmp_idx=0;
          status= STAT_start;
        }
        break;
      case STAT_frame_ok:
        name_lng= 0;
        switch (ch)
        {
          case ' ' :
          case '\t':
          case 0x0D:
          case 0x0A:
            status= STAT_frame_name;
            break;
          case '>':
            goto STATUS_5;
          default :
            cmp_idx=0;
            status= STAT_start;
            break;
        }
        break;
      case STAT_frame_name:
        if (ch == '>') goto STATUS_5;
        if (ch != ' ' && ch != '\t' && ch != 0x0D && ch != 0x0A)
        {
          status= STAT_frame_space;
          if (name_lng+1 < FRAME_NAME_LNG)
            FRAME_NAME [name_lng++] = (char) ch;
        }
        break;
      case STAT_frame_space:
        if (ch == '>') goto STATUS_5;
        if (ch == '\t' || ch == 0x0D || ch == 0x0A) ch = ' ';
        if (ch == ' ') status= STAT_frame_name; /* store only one space */
        if (name_lng+1 < FRAME_NAME_LNG)
          FRAME_NAME [name_lng++]= (char) ch;
        break;
      case STAT_frame_done:     /* Frame Tag abgeschlossen;     */
STATUS_5:                       /* in Liste(n) eintragen        */
        status= STAT_in_frame;
        FRAME_NAME [name_lng]= 0;
        if (!(scan_mode & HYXSM_no_allocation))
          if ((fd->hytxt_frame_name= malloc (name_lng + 1)) == (char *) 0)
          {
            ret_val= -1;
            fprintf (stderr, ERR_MSG);
            goto STOP;
          }

        fd->hytxt_frame_next=
        fd->hytxt_frame_prev=
        fd->hytxt_frame_earlier=
        fd->hytxt_frame_newer= (struct HYTXT_FRAME *) 0;
        fd->hytxt_frame_pos_beg= pos_beg;
        fd->hytxt_attr_append= &(fd->hytxt_attr);
        if (fd->hytxt_frame_name != (char *) 0)
           strcpy (fd->hytxt_frame_name, FRAME_NAME);
/********************************************************************
printf ("SCAN (0): rc=%d %s\n", ret_val, fd->hytxt_frame_name);
printf ("          %08lX %08lX %08lX %08lX\n",
                   fd->hytxt_frame_prev,    fd->hytxt_frame_next,
                   fd->hytxt_frame_earlier, fd->hytxt_frame_newer);
printf ("          %08lX %08lX\n",
                   fd->hytxt_frame_pos_beg, fd->hytxt_frame_pos_end);
********************************************************************/
        break;

      case STAT_in_frame:       /* Frame Ende suchen */
        if (ch == '<')
        {
          pos_end= pos;
          status= STAT_701;
        }
        break;
      case STAT_701:
        if (ch == ';')          /* Kurzform fuer das Frame-End */
        {
          status= STAT_eframe_name;
          break;
        }
        if (ch == FRAME_END [0])
        {
          cmp_idx= 1;
          status= STAT_7;
          break;
        }
        if (ch == FRAME_ATTR [0])
        {
          cmp_idx= 1;
          status= STAT_770;
          break;
        }
        if (ch == ' ' || ch == '\t' || ch == 0x0D || ch == 0x0A) break;
        status= STAT_in_frame;
        break;
      case STAT_7:
        if (ch == FRAME_END [cmp_idx])
        {
          cmp_idx++;
          if (FRAME_END [cmp_idx] == 0) status= STAT_8;
        }
        else
        {
          cmp_idx= 0;
          status= STAT_in_frame;
        }
        break;
      case STAT_770:
        if (ch == FRAME_ATTR [cmp_idx])
        {
          cmp_idx++;
          if (FRAME_ATTR [cmp_idx] == 0) status= STAT_781;
        }
        else
        {
          cmp_idx= 0;
          status= STAT_in_frame;
        }
        break;
      case STAT_781:
        name_lng= 0;
        switch (ch)
        {
          case ' ':                     /* '<FrAttr '           */
            status= STAT_782;
            break;
          case '>':                     /* '<FrAttr>'           */
            status= STAT_in_frame;
            break;
          default :                     /* '<FrAttr?'           */
            cmp_idx= 0;
            status= STAT_in_frame;
            break;
        }
        break;
      case STAT_782:
        if (ch == '>')                  /* '<FrAttr >'          */
        {
          status= STAT_in_frame;
          break;
        }
        if (ch != ' ' && ch != '\t')    /* '<FrAttr n'          */
        {
          status= STAT_783;
          if (name_lng+1 < FRAME_NAME_LNG)
             FRAME_NAME [name_lng++] = (char) ch;
        }
        break;
      case STAT_783:                    /* '<FrAttr nam...'     */
        if (ch == '>')                  /* '<FrAttr name>'      */
        {
          status= STAT_in_frame;
          goto STATUS_783b;
        }
        if (ch == ' ' || ch == '\t' || ch == 0x0D || ch == 0x0A)
        {
          status= STAT_784;             /* '<FrAttr name '      */
STATUS_783b:
          if (!(scan_mode & HYXSM_no_attributes))
          {
            if ((attr= (struct HYTXT_ATTR *)
                       calloc (sizeof (struct HYTXT_ATTR),1))
                 == (struct HYTXT_ATTR *) 0)
            {
              ret_val= -1;
              fprintf (stderr, ERR_MSG);
              goto STOP;
            }
            *(fd->hytxt_attr_append)= attr;
              fd->hytxt_attr_append = &(attr->hytxt_attr_next);
            if ((attr->hytxt_attr_id= malloc (name_lng + 1)) == (char *) 0)
            {
              ret_val= -1;
              fprintf (stderr, ERR_MSG);
              goto STOP;
            }
            FRAME_NAME [name_lng]= 0;
            strcpy (attr->hytxt_attr_id, FRAME_NAME);
          }
          if (strcmp (FRAME_NAME, "Deleted") == 0)
             fd->hytxt_frame_flags |= HYTXT_FRFLAG_Deleted;
          if (strcmp (FRAME_NAME, "Rename") == 0)
             fd->hytxt_frame_flags |= HYTXT_FRFLAG_Rename;
          if (strcmp (FRAME_NAME, "Move") == 0)
             fd->hytxt_frame_flags |= HYTXT_FRFLAG_Move;
          name_lng= 0;
          break;
        }
        if (name_lng+1 < FRAME_NAME_LNG)
           FRAME_NAME [name_lng++] = (char) ch;
        break;
      case STAT_784:            /* Attribut Parameter einlesen              */
        if (ch == '>') goto STATUS_789;
        if (ch != ' ' && ch != '\t' && ch != 0x0D && ch != 0x0A)
        {
          status= STAT_785;
          if (name_lng+1 < FRAME_NAME_LNG)
             FRAME_NAME [name_lng++] = (char) ch;
        }
        break;
      case STAT_785:
        if (ch == '>') goto STATUS_789;
        if (ch == '\t' || ch == 0x0D || ch == 0x0A) ch= ' ';
        if (ch == ' ') status= STAT_784;        /* nur ein Blank aufnehmen  */
        if (name_lng+1 < FRAME_NAME_LNG)
           FRAME_NAME [name_lng++] = (char) ch;
        break;
      case STAT_789:
STATUS_789:
        if (!(scan_mode & HYXSM_no_attributes))
        {
          if ((attr->hytxt_attr_pars= malloc (name_lng + 1)) == (char *) 0)
          {
            ret_val= -1;
            fprintf (stderr, ERR_MSG);
            goto STOP;
          }
          FRAME_NAME [name_lng]= 0;
          strcpy (attr->hytxt_attr_pars, FRAME_NAME);
        }
        name_lng= 0;
        status= STAT_in_frame;
        break;

      case STAT_8:
        switch (ch)
        {
          case ' ' :
          case '\t':
          case 0x0D:
          case 0x0A:
            status= STAT_eframe_name;
            break;
          case '>':
            goto STATUS_10;
          default :
            cmp_idx= 0;
            status= STAT_in_frame;
            break;
        }
        break;
      case STAT_eframe_name:    /* Frame Name im Tag-End ueberlesen         */
        if (ch == '>') goto STATUS_10;
        break;
      case STAT_end_of_frame:   /* Ende des Frames gefunden                 */
STATUS_10:
        fd->hytxt_frame_pos_end= pos;
        goto STOP;
    }
  }

STOP:

#ifndef NO_MD5
  if (md5_cks != (char *) 0)
  {
    MD5Final (digest, &context);
    MD5Digest2String ((char *) digest, md5_cks);
  }
#endif

  *fi_pos= pos + 1L;
  return ret_val;
}
