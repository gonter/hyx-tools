/*
 *  FILE E:\usr\sgml\sgml0002.c
 *
 *  sgml_filter: SGML-Dokument in
 *               (a) eigentlichen Text
 *               (b) SGML-Tags mit Parametern
 *               (c) SGML-Kommentar
 *               aufsplitten.
 *
 *  1989 11 03
 *  1990 10 xx: >>>>> DIESE VERSION WIRD Z.Z. NICHT UNTERSTšTZT!!!! <<<<<
 *
 */

/* ------------------------------------------------------------------------ */
/* Schnittstellen:
/* sgml_filter_reset ()         Filtersystem zurcksetzen                   */
sgml_filter         () {}    /* gelesenes Zeichen                           */
sgml_filter_tag_chr () {}    /* Ausgabe eines gelesenen Tag-Zeichens        */
sgml_filter_tag_beg () {}    /* Beginn eines Tags festgestellt              */
sgml_filter_tag_end () {}    /* Ende eines Tags festgestellt                */
sgml_filter_com_chr () {}    /* Ausgabe eines gelesenen Kommentar-Zeichens  */
sgml_filter_com_beg () {}    /* Beginn eines Kommentars festgestellt        */
sgml_filter_com_end () {}    /* Ende eines Kommentars festgestellt          */
sgml_filter_chr     () {}    /* Ausgabe eines gelesenen Text-Zeichens       */

/* ------------------------------------------------------------------------ */

# pragma check_stack(off)

/* ------------------------------------------------------------------------ */
static int val;         /* Character Code in Oct, Dec, Hex      */

/* ------------------------------------------------------------------------ */
sgml_filter_reset ()
{
  int sgml_filter_00 ();

  patch (sgml_filter, sgml_filter_00);
}

/* ------------------------------------------------------------------------ */
static sgml_filter_00 (ch)
int ch;
{
  int sgml_filter_01 ();

  if (ch == '<')
       patch (sgml_filter, sgml_filter_01);
  else sgml_filter_chr (ch);
}

/* ------------------------------------------------------------------------ */
/* '<' gelesen; jetzt wird untersucht, um was es sich handelt               */
static sgml_filter_01 (ch)
int ch;
{
  int sgml_filter_02 (),
      sgml_filter_04 (),
      sgml_filter_06 (),
      sgml_filter_07 ();

  val = 0;

  switch (ch)
  {
    case '0': patch (sgml_filter, sgml_filter_02); break;
    case '1': case '2': case '3':
    case '4': case '5': case '6':
    case '7': case '8': case '9':
              val = ch - '0';
              patch (sgml_filter, sgml_filter_04); break;
    case '-': patch (sgml_filter, sgml_filter_07); break;
    case '>': patch (sgml_filter, sgml_filter_00); break;
    default:  sgml_filter_tag_beg ();
              sgml_filter_tag_chr (ch);
              patch (sgml_filter, sgml_filter_06); break;
  }
}

/* ------------------------------------------------------------------------ */
static sgml_filter_02 (ch)
int ch;
{
  int sgml_filter_03 (),
      sgml_filter_05 (),
      sgml_filter_06 ();
      
  switch (ch)
  {
    case 'x': case 'X': patch (sgml_filter, sgml_filter_03);
                        break;
    case '0': case '1':
    case '2': case '3':
    case '4': case '5':
    case '6': case '7':
                        val = ch - '0';
                        patch (sgml_filter, sgml_filter_05);
                        break;
    case '>':           patch (sgml_filter, sgml_filter_00);
                        sgml_filter_chr (0);
                        break;
    default :           patch (sgml_filter, sgml_filter_06);
                        sgml_filter_tag_beg ();
                        sgml_filter_tag_chr ('0');
                        break;
  }
}

/* ------------------------------------------------------------------------ */
static sgml_filter_03 (ch)
int ch;
{
  int sgml_filter_06 ();

  if (ch >= '0' && ch <= '9')      val = 16*val + ch - '0';
  else if (ch >= 'a' && ch <= 'f') val = 16*val + ch - 'a' + 10;
  else if (ch >= 'A' && ch <= 'F') val = 16*val + ch - 'A' + 10;
  else if (ch == '>')
       {
         sgml_filter_chr (val);
         patch (sgml_filter, sgml_filter_00);
       }
  else {
         sgml_filter_tag_beg ();
         sgml_filter_tag_chr (val);
         patch (sgml_filter, sgml_filter_06);
       }
}

/* ------------------------------------------------------------------------ */
static sgml_filter_04 (ch)
int ch;
{
  int sgml_filter_06 ();

  if (ch >= '0' && ch <= '9')      val = 10*val + ch - '0';
  else if (ch == '>')
       {
         sgml_filter_chr (val);
         patch (sgml_filter, sgml_filter_00);
       }
  else {
         sgml_filter_tag_beg ();
         sgml_filter_tag_chr (val);
         patch (sgml_filter, sgml_filter_06);
       }
}

/* ------------------------------------------------------------------------ */
static sgml_filter_05 (ch)
int ch;
{
  int sgml_filter_06 ();

  if (ch >= '0' && ch <= '7')      val = 8*val + ch - '0';
  else if (ch == '>')
       {
         sgml_filter_chr (val);
         patch (sgml_filter, sgml_filter_00);
       }
  else {
         sgml_filter_tag_beg ();
         sgml_filter_tag_chr (val);
         patch (sgml_filter, sgml_filter_06);
       }
}

/* ------------------------------------------------------------------------ */
static sgml_filter_06 (ch)
int ch;
{
  if (ch == '>')
       {
         patch (sgml_filter, sgml_filter_00);
         sgml_filter_tag_end ();
       }
  else sgml_filter_tag_chr (ch);
}

/* ------------------------------------------------------------------------ */
static sgml_filter_07 (ch)
int ch;
{
  int sgml_filter_08 ();

  switch (ch)
  {
    case '-': patch (sgml_filter, sgml_filter_08);
              sgml_filter_com_beg ();
              break;
    case '>': patch (sgml_filter, sgml_filter_00);
              sgml_filter_tag_beg ();
              sgml_filter_tag_chr ('-');
              sgml_filter_tag_end ();
              break;
    default:  patch (sgml_filter, sgml_filter_06);
              sgml_filter_tag_beg ();
              sgml_filter_tag_chr ('-');
              sgml_filter_tag_chr (ch);
              break;
  }
}

/* ------------------------------------------------------------------------ */
static sgml_filter_08 (ch)
int ch;
{
  int sgml_filter_09 ();

  if (ch == '-')
        {
          patch (sgml_filter, sgml_filter_09);
        }
  else  {
          sgml_filter_com_chr (ch);
        }
}

/* ------------------------------------------------------------------------ */
static sgml_filter_09 (ch)
int ch;
{
  if (ch == '-')
        {
          patch (sgml_filter, sgml_filter_01);
          sgml_filter_com_end ();
        }
  else  {
          sgml_filter_com_chr ('-');
          sgml_filter_com_chr (ch);
        }
}
