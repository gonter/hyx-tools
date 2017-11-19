/*
 *  FILE %ds/hyxta/hyxta101.c
 *
 *  textual analysis with TA_OBJECT
 *  -  read the body of a SGML object
 *  -  this function can be calling itself recurively
 *
 *  written:       1994-05-31
 *  latest update: 1999-05-07 16:34:56
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/parse.h>
#include <gg/ta.h>

#define TB_Size 4096
static char txt_buffer [TB_Size];
static int TB_index= 0;

/* ------------------------------------------------------------------------ */
static struct TA_OBJECT *cdecl finishup (void);

/* ------------------------------------------------------------------------ */
static struct TA_OBJECT *finishup ()
{
  struct TA_OBJECT *ttao;

  ttao= tao_mk_string (txt_buffer, TB_index);
  if (ttao == (struct TA_OBJECT *) 0)
  {
    fprintf (stderr, "ta101: error: out memory!\n");
    return (struct TA_OBJECT *) 0;
  }
  TB_index= 0;

  return ttao;
}

/* ------------------------------------------------------------------------ */
struct TA_OBJECT *tao_rd_sgml_body (struct TA_SOURCE *source)
{
  struct TA_OBJECT *tao;
  struct TA_OBJECT *ttao;
  struct TA_OBJECT **tao_body;
  FILE *fi;
  int ch;

  TB_index= 0;
printf ("tao101: reading from %s\n", source->TAS_filename);

  if (source == (struct TA_SOURCE *) 0
      || (fi= source->TAS_file) == (FILE *) 0)
    return (struct TA_OBJECT *) 0;

printf ("tao101: reading from %s\n", source->TAS_filename);

  if ((tao= calloc (sizeof (struct TA_OBJECT), 1))
      == (struct TA_OBJECT *) 0) return (struct TA_OBJECT *) 0;

  tao_body= (struct TA_OBJECT **) &tao->TAO_body;

printf ("tao101: reading from %s\n", source->TAS_filename);

  for (;;)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi))
    {
printf ("EOF!!!!\n");
      source->TAS_is_eof= 1;
      goto FINISH;
    }

printf ("ch=0x%02X\n", ch);
    switch (ch)
    {
      case '<':
      case '&':
        break;
      default:
        txt_buffer [TB_index++]= (char) ch;
        if (TB_index >= TB_Size)
        {
FINISH:
printf ("Finish!!!!\n");
          ttao= finishup ();
          *tao_body= ttao;
          tao_body= &(ttao->TAO_next);
        }
        break;
    }
    if (feof (fi)) break;
  }

  return tao;
}
