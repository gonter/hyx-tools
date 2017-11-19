/*
 *  FILE ~/usr/window/utl/setpal.c
 *
 *  written:       1991 07 23
 *  latest udpate: 1994-08-20
 *
 */


#include <stdio.h>
#include <bios.h>
#define W_MODEL_CGA
#include <gg/window.h>
#include <gg/keys.h>
#include <gg/filename.h>

#define CURSOR_COL 10
#define NAME_SIZE 16

static char xxlin []=
"컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";

static char d_fnm [66];
static char d_tmp [66];
static char d_bak [66];

/* ------------------------------------------------------------------------ */
int cdecl main (int argc, char *argv[]);
int cdecl setpal (void);
long cdecl get_parameter_value (char *s);

struct COLOR_PALETTE
{
  int cp_num;
  int cp_r, cp_g, cp_b;
  int flags;
} ;

static struct COLOR_PALETTE color_palette [16];

static char VALUES [66] = "c:/etc/setpal.v";

/* ------------------------------------------------------------------------ */
static char *HELP [] =
{
  "USAGE: setpal [options]\n",
  "OPTIONS:\n",
  "  -f<fnm> ... settings file [DEF: c:/etc/setpal.v]\n",
  "  -l<set> ... load setting\n",
  "EXAMPLES:\n",
  "\n",
  "(@)Asetpal.c 1.01 #D$1994-08-20 19:00:00\n",
  "\n",
#include <gg/public.inc>
} ;

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  int i, j;
  char *setting= (char *) 0;
  int setting_num;

  for (i = 1; i < argc; i++)
      if (argv [i][0] == '-')
         switch (argv [i][1])
         {
           case 'f': case 'F':
             strcpy (VALUES, &argv[i][2]);
             break;
           case 'l': case 'L':
             setting= &argv[i][2];
             break;

HLP:
#include <gg/help.inc>
         }

  w_init (0x0000);
  if (setting != (char *) 0)
  {
    if (*setting >= '0' && *setting <= '9')
    {
      setting_num= (int) get_parameter_value (setting);
    }
    else
    {
      /* ... unfinished ... */
    }
    return;
  }

  setpal ();
  return 0;
}

/* ------------------------------------------------------------------------ */
int setpal ()
{
  int i;
  int er, r,g,b;
  int key;
  int col=0;
  int dc=1;
  int dp=1;
  union REGS ra, rb;
  char palette_name [40];
  int palette_number=-1;
  char tmp [40];

  palette_name[0]=0;
  w_prntcol (0,0,1, WV_WEISS|W_HELL, xxlin);
  w_prntcol (0,0,2, WV_WEISS|W_HELL,
"Color        [Nr]  ER   R  G  B   R  G  B");
  w_prntcol (0,0,3, WV_WEISS|W_HELL, xxlin);
  for (i=0;i<16;i++)
  {
    ra.x.ax= 0x1007;
    ra.h.bl= i;
    int86 (0x10, &ra, &rb);
    color_palette[i].cp_num = er = rb.h.bh;

    vga_getpalette (er, &r, &g, &b);
    show_values (i, er, r, g, b);
    color_palette[i].cp_r   = r;
    color_palette[i].cp_g   = g;
    color_palette[i].cp_b   = b;
  }
  w_prntcol (0,0,20, WV_WEISS|W_HELL, xxlin);
  w_prntcol (0,0,24, WV_WEISS|W_HELL, xxlin);
  w_prntcol (0,44,17, WV_WEISS|W_HELL, "ESC to exit");
  w_prntcol (0,44,18, WV_WEISS|W_HELL, 
    "F10: dump values to c:/etc/fm.stp");
  w_prntcol (0,44,4, WV_WEISS|W_HELL, "F1: name:");
  w_prntcol (0,54,4, WV_WEISS|W_HELL, palette_name);
  sprintf (tmp, "%4d", palette_number);
  w_prntcol (0,44,5, WV_WEISS|W_HELL, "    num:");
  w_prntcol (0,54,5, WV_WEISS|W_HELL, tmp);

  for (;;)
  {
    if (dp)
    {
      vga_setpalette (
        color_palette[col].cp_num,
        color_palette[col].cp_r,
        color_palette[col].cp_g,
        color_palette[col].cp_b);
      show_values (
        col,
        color_palette[col].cp_num,
        color_palette[col].cp_r,
        color_palette[col].cp_g,
        color_palette[col].cp_b);
      show_palette ("red  ", 21, color_palette[col].cp_r);
      show_palette ("green", 22, color_palette[col].cp_g);
      show_palette ("blue ", 23, color_palette[col].cp_b);
      dp=0;
    }

    if (dc=1)
    {
      w_setchar (0,CURSOR_COL,col+4,WV_WEISS|W_HELL,0x11);
      w_setchar (0,CURSOR_COL+1,col+4,WV_WEISS|W_HELL,0x10);
      dc=0;
    }

    switch (key=kbin())
    {
      case K_CDOWN:
        if (col>=15) break;
        w_setchar (0,CURSOR_COL,col+4,WV_WEISS|W_HELL,0x20);
        w_setchar (0,CURSOR_COL+1,col+4,WV_WEISS|W_HELL,0x20);
        col++;
        dc=1;
        dp=1;
        break;
      case K_CUP:
        if (col<=0) break;
        w_setchar (0,CURSOR_COL,col+4,WV_WEISS|W_HELL,0x20);
        w_setchar (0,CURSOR_COL+1,col+4,WV_WEISS|W_HELL,0x20);
        col--;
        dc=1;
        dp=1;
        break;

      case 'R':
        color_palette [col].cp_r++;
        if (color_palette [col].cp_r >= 64) 
          color_palette [col].cp_r = 0;
        dp=1;
        break;
      case 'G':
        color_palette [col].cp_g++;
        if (color_palette [col].cp_g >= 64) 
          color_palette [col].cp_g = 0;
        dp=1;
        break;
      case 'B':
        color_palette [col].cp_b++;
        if (color_palette [col].cp_b >= 64) 
          color_palette [col].cp_b = 0;
        dp=1;
        break;

      case 'r':
        color_palette [col].cp_r--;
        if (color_palette [col].cp_r < 0) 
          color_palette [col].cp_r = 63;
        dp=1;
        break;
      case 'g':
        color_palette [col].cp_g--;
        if (color_palette [col].cp_g < 0) 
          color_palette [col].cp_g = 63;
        dp=1;
        break;
      case 'b':
        color_palette [col].cp_b--;
        if (color_palette [col].cp_b < 0) 
          color_palette [col].cp_b = 63;
        dp=1;
        break;

      case 'E':
        if (color_palette [col].cp_num >= 63) break;
        color_palette [col].cp_num++;
        goto SET_EGA_POINTER;
      case 'e':
        if (color_palette [col].cp_num <= 0) break;
        color_palette [col].cp_num--;
SET_EGA_POINTER:
        ra.x.ax= 0x1000;
        ra.h.bl= col;
        ra.h.bh= er= color_palette [col].cp_num;
        int86 (0x10, &ra, &rb);
        vga_getpalette (er, &r, &g, &b);
        show_values (col, er, r, g, b);
        color_palette[col].cp_r = r;
        color_palette[col].cp_g = g;
        color_palette[col].cp_b = b;
        dp=1;
        break;

      case K_PF1:
        w_setcup (0, 54, 4);
        scanf ("%s", palette_name);
        break;

      case K_PF10:
        set_etc_filename (d_fnm, "fm.stp");
        set_etc_filename (d_tmp, "fm.$");
        set_etc_filename (d_bak, "fm.bak");
        if (dump_values (d_fnm, d_tmp, d_bak, color_palette) == -1)
        {
          w_prntcol (0,44,19, WV_WEISS|W_HELL, "error writing file");
        }
        else
        {
          w_prntcol (0,44,19, WV_WEISS|W_HELL, "file written ok :)");
        }
        break;
    }
    if (key==0x1B || key == K_PF7) break;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int show_palette (char *s, int lin, int val)
{
  if (val > 63 || val < 0) return -1;

  w_prntcol (0, 0, lin, WV_WEISS|W_HELL,s);
  w_setchar (0, 6, lin, WV_WEISS|W_HELL, ':');
  w_setnchar (0, 7, lin, WV_WEISS|W_HELL, 0x08, val);
  w_setnchar (0, 7+val, lin, WV_SCHWARZ, 0x08, 63-val);
  w_setchar (0, 70, lin, WV_WEISS|W_HELL, ':');

  return 0;
}

/* ------------------------------------------------------------------------ */
int show_values (int col, int er, int r, int g, int b)
{
  char lin [100];

  sprintf (lin,
           "   [%2d]  %2d  %2d %2d %2d  #%02X%02X%02X",
           col, er, r, g, b, r<<2, g<<2, b<<2);
  w_prntcol (0, 10, col+4, WV_WEISS|W_HELL, lin);
  w_setnchar (0, 0, col+4, col, 0x08, 9);

  return 0;
}

/* ------------------------------------------------------------------------ */
int dump_values (
char *fnm,
char *tmp,
char *bak,
struct COLOR_PALETTE cp[16])
{
  FILE *fi;
  FILE *fo;
  int i;
  int num;
  int ch;
  int stat= 0;
  char lin [100];
  int in_default= 0;
  int written= 0;

  for (i= 0; i < 16; i++) cp[i].flags= 0;

  if ((fo= fopen (tmp, "wb")) == (FILE *) 0) return -1;
  if ((fi= fopen (fnm, "rb")) == (FILE *) 0)
  {
    fclose (fo);
    return -1;
  }

  for (;;)
  {
    ch = fgetc (fi) & 0x00FF;
    if (feof (fi)) goto STOP;
    switch (stat)
    {
      case 0:
        switch (ch)
        {
          case '@':
            in_default=0;
            stat=99;
            fscanf (fi, "%s", lin);
            if (strcmp (lin, "default") == 0) in_default=1;
            if (strcmp (lin, "default-end") == 0)
            {
              for (i=0;i<16;i++)
              {
                if (cp[i].flags==0)
                {
                  fprintf (fo, "palette %2d %2d %2d %2d\n",
                    cp[i].cp_num, cp[i].cp_r, cp[i].cp_g, cp[i].cp_b);
                  written=1;
                }
              }
              fprintf (fo, "@%s", lin);
              ftransfer (fi, fo, 0x7FFFFFFF);
              goto STOP;
            }
            fprintf (fo, "@%s", lin);
            break;
          case 'p':
            if (in_default)
            {
              fscanf (fi, "%s", lin);
              if (strcmp (lin, "alette") == 0)
              {
                fscanf (fi, "%d", &num);
                for (i=0;i<16;i++)
                  if (cp[i].cp_num==num) break;
                if (i<16 && cp[i].cp_num==num)
                {
                  fprintf (fo, "palette %2d %2d %2d %2d\n",
                    cp[i].cp_num, cp[i].cp_r, cp[i].cp_g, cp[i].cp_b);
                  cp[i].flags=1;
                  written=1;
                  stat=98;
                }
                else
                {
                  fprintf (fo, "palette %d", num);
                  stat=99;
                }
              }
              else
              {
                fprintf (fo, "%c%s", ch, lin);
                stat=99;
              }
              break;
            }
          default:
            stat=99;
          case 0x0A:
            fputc (ch, fo);
            break;
        }
        break;
      default:
        fputc (ch, fo);
      case 98:
        if (ch == 0x0A) stat=0;
        break;
    }
  }

STOP:
  fclose (fi);
  fclose (fo);
  if (written)
  {
    unlink (bak);
    rename (fnm, bak);
    rename (tmp, fnm);
  }
  return 0;
}
