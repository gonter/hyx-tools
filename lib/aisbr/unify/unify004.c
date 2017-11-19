/*
 *  FILE ~/usr/aisbr/unify/unify004.c
 *
 *  written:       1991 05 01
 *  latest update: 1994-08-12
 *
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <gg/unify.h>

#define MAX_STR 256
static char str [MAX_STR];

static long value;
static int value_signum;

/* ------------------------------------------------------------------------ */
int fs_scan (
FILE *fi,
FILE *err,
struct FEATURE_STRUCTURE **act,
int act_mode,                   /* 0 ... allocate *act                      */
                                /* 1 ... (*act)->head to scan               */
                                /* 2 ... (*act)->tail to scan               */
int list_mode)                  /* 1 ... scan list of feature pairs         */
                                /* 2 ... scan list of values                */
{
  int ch;
  int pushback=-1;
#define STATUS_start            0
#define STATUS_name             1
#define STATUS_expect_colon     2
#define STATUS_option           3
#define STATUS_number           4
  int status=STATUS_start;
  int str_size=0;
  int option=0;

  if (fi == (FILE *) 0) return SCAN_error;
  if (feof (fi)) return SCAN_EOF;

  for (;;)
  {
    if (pushback == -1)
    {
      ch = fgetc (fi) & 0x00FF;
      if (feof (fi)) ch = -1;

      if (ch == '#')
      {
        for (;;)
        {
          ch=fgetc (fi) & 0x00FF;
          if (feof (fi) || ch == 0x0A) break;
        }
        continue;
      }

      if (ch == '®')
      {
        for (;;)
        {
          ch=fgetc (fi) & 0x00FF;
          if (feof (fi) || ch == '¯') break;
        }
        continue;
      }
    }
    else
    {
      ch=pushback;
      pushback=-1;
    }

    /**************************************************
    printf ("FS: st=%d  act_mode=%d  ch='%c'\n",
            status, act_mode, (ch >= 0x20) ? ch : '.');
    **************************************************/

    switch (status)
    {
      case STATUS_start:
        switch (ch)
        {
          case 0x20:
          case 0x09:
          case 0x0D:
          case 0x0A:
          case -1:
            break;
          case '$':
            status=STATUS_option;
            break;
          case '-':
            value_signum=1;
            value=0L;
            status=STATUS_number;
            break;
          case '+':
            value_signum=0;
            value=0L;
            status=STATUS_number;
            break;
          case '0': case '1': case '2': case '3': case '4':
          case '5': case '6': case '7': case '8': case '9':
            value_signum= 0;
            value= (long) (ch - '0');
            status= STATUS_number;
            break;
          case ']':
          case '}':
            return SCAN_EOS;
          case '[':
          case '{':
X1:
            switch (act_mode)
            {
              case 0:
                *act= fs_allocate_FEATURE_STRUCTURE ();
                if (*act == (void *) 0)
                {
                  fprintf (err, "out of memory\n");
                  return SCAN_error;
                }
                (*act)->fs_next = (void *) 0;
                act_mode = list_mode;
                goto X1;
              case 1:
                (*act)->fs_head_type = (ch == '[')
                                        ? FS_type_feature
                                        : FS_type_set;
                fs_scan (fi, err, &(*act)->fs_head, 0, (ch=='[')?1:2);
                act_mode=2;
                status=STATUS_expect_colon;
                break;
              case 2:
                (*act)->fs_tail_type = (ch == '[')
                                        ? FS_type_feature
                                        : FS_type_set;
                fs_scan (fi, err, &(*act)->fs_tail, 0, (ch=='[')?1:2);
                act = &(*act)->fs_next;
                act_mode=0;
                break;
              default:
                fprintf (err, "unknown act_mode in status 0: %d\n",
                         act_mode);
                return SCAN_error;
            }
            break;
          default:
START_default:
            if ((ch >= 'a' && ch <= 'z')
              ||(ch >= 'A' && ch <= 'Z')
              || ch == '_'
              || ch == '@')
            {
              switch (act_mode)
              {
                case 0:
                  *act= fs_allocate_FEATURE_STRUCTURE ();
                  if (*act == (void *) 0)
                  {
                    fprintf (err, "out of memory\n");
                    return SCAN_error;
                  }
                  act_mode = list_mode;
                  goto START_default;
                case 1:
                  (*act)->fs_head_type = (ch == '@')
                                         ? FS_type_pointer
                                         : FS_type_string;
                  break;
                case 2:
                  (*act)->fs_tail_type = (ch == '@')
                                         ? FS_type_pointer
                                         : FS_type_string;
                  break;
                default:
                  fprintf (err, "unknown act_mode in status 0: %d\n",
                           act_mode);
                  return SCAN_error;
              }
              status = STATUS_name;
              str [0] = (char) ch;
              str_size=1;
              str [str_size]=0;
            } else
            {
              fprintf (err,
                "feature scan: invalid character in status 0: 0x%02X\n",
                ch);
              return SCAN_error;
            }
            break;
        }
        break;

      case STATUS_name:
        switch (ch)
        {
          case 0x20:
          case 0x09:
          case 0x0D:
          case 0x0A:
          case -1:
            switch (act_mode)
            {
              case 1:
                status = STATUS_expect_colon;
ATTACH_HEAD:
                if (((*act)->fs_head= (struct FEATURE_STRUCTURE *) strdup (str))
                    == (char *) 0) return SCAN_error;
                break;
              case 2:
                status=STATUS_start;
                option=0;
                if (((*act)->fs_tail= (void *) strdup (str))
                    == (char *) 0) return SCAN_error;
                act = &(*act)->fs_next;
                act_mode=0;
                break;
              default:
                fprintf (err,
            "feature scan: internal error in status 1: act_mode != 1,2\n");
                return SCAN_error;
            }
            break;
          case ':':
            switch (act_mode)
            {
              case 1:
                status = STATUS_start;
                option=0;
                act_mode=2;
                goto ATTACH_HEAD;
              default:
                fprintf (err,
                  "feature scan: error in status 1: act_mode != 1\n");
                return SCAN_error;
            }
            break;
          case ']':
          case '}':
            switch (act_mode)
            {
              case 1:
                status = STATUS_start;
                option=0;
                act_mode=2;
                if (((*act)->fs_head= (void *) strdup (str))
                    == (char *) 0) return SCAN_error;
                return SCAN_EOS;
              case 2:
                status = STATUS_start;
                option=0;
                if (((*act)->fs_tail= (void *) strdup (str))
                    == (char *) 0) return SCAN_error;
                strcpy ((char *) (*act)->fs_tail, str);
                act = &(*act)->fs_next;
                act_mode=0;
                return SCAN_EOS;
              default:
                fprintf (err,
                  "feature scan: error in STATUS_name: act_mode != 1\n");
                return SCAN_error;
            }
            break;
          default:
            if ((ch >= 'a' && ch <= 'z')
              ||(ch >= 'A' && ch <= 'Z')
              ||(ch >= '0' && ch <= '9')
              || ch == '_'
              || ch == '@')
            {
              if (str_size >= MAX_STR) return SCAN_error;
              str [str_size++] = (char) ch;
              str [str_size]=0;
            } else
            {
              fprintf (err,
                 "feature scan: invalid character in status 1: 0x%02X\n",
                 ch);
              return SCAN_error;
            }
            break;
        }
        break;

      case STATUS_expect_colon:
        switch (ch)
        {
          case 0x20:
          case 0x09:
          case 0x0D:
          case 0x0A:
          case -1:
            break;
          case ':':
            status=STATUS_start;
            option=0;
            act_mode=2;
            break;
          default:
            if (act_mode)
            {
              act_mode=0;
              act = &(*act)->fs_next;
            }
            goto START_default;
        }
        break;

      case STATUS_option:
        switch (ch)
        {
          default:
            option=0;
            break;
        }
        status=STATUS_start;
        break;

      case STATUS_number:
        if (ch >= '0' && ch <= '9')
             {
               value=value*10L + ((long) (ch - '0'));
             }
        else {
               if (value_signum==1) value = -value;
X2:
               switch (act_mode)
               {
                 case 0:
                   *act= fs_allocate_FEATURE_STRUCTURE ();
                   if (*act == (void *) 0)
                   {
                     fprintf (err, "out of memory\n");
                     return SCAN_error;
                   }
                   (*act)->fs_next = (void *) 0;
                   act_mode = list_mode;
                   goto X2;
                 case 1:
                   (*act)->fs_head_type = FS_type_number;
                   (*act)->fs_head = (void *) value;
                   status=STATUS_expect_colon;
                   break;
                 case 2:
                   (*act)->fs_tail_type = FS_type_number;
                   (*act)->fs_tail = (void *) value;
                   act = &(*act)->fs_next;
                   act_mode=0;
                   status=STATUS_start;
                   option=0;
                   break;
                 default:
                   fprintf (err,
                 "feature scan: error in STATUS_number: act_mode != 0,1,2\n");
                   return SCAN_error;
               }
               pushback=ch;
             }
        break;

      default:
        fprintf (err, "feature scan: invalid scanner state %d\n", status);
        return SCAN_error;
    }
    if (feof (fi)) return SCAN_EOF;
  }
}
