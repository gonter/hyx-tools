/*
 *  include File <gg/fields.h>
 *
 *  Datenstrukturen
 *
 *  written:       1989 09 23
 *  latest update: 1995-02-19
 *
 */

#ifndef __GG_fields__
#define __GG_fields__

#pragma pack(1)

/* Definition f. Fielddescriptor ------------------------------------------ */
#define FLD_size           14  /* Laenge eines Field Desc. Records         */
#define FDo_x               0  /* 1. Variante: Offset in String            */
#define FDo_y               1  /* Koordinaten am Text Screen               */
#define FDo_l               2  /* L„nge des Feldes                         */
#define FDo_attr1           3  /* Farb Attribut 1: ohne Edit               */
#define FDo_attr2           4  /* Farb Attribut 2: bei Edit (siehe unten)  */
#define FDo_rpt             5  /* Repeat Counter: 1..255; 0 -> ERROR   N/A */
#define FDo_fmt             6  /* Format Code: #des Input Format Pgms N/A */
#define FDo_help_num        7  /* Help Code                     ######N/A */
#define FDo_off1            8  /* Â Offset der Daten des Feldes in FORM-   */
#define FDo_off2            9  /* Ù Datenstruktur; (im VAL-Format)         */
                                /*   Offset muss extra errechnet werden     */
#define FDo_flg1           10  /* Flags #1; siehe unten                   */
#define FDo_typ            11  /* Typ des Datenfeldes (Flags #2)      N/A */
#define FDo_flg3           12  /* Flags #3;                           N/A */
#define FDo_flg4           13  /* Flags #4;                           N/A */

struct FIELD_DESC                  /* 2. Variante: Struktur */
{
  unsigned char
       FLD_x,
       FLD_y,
       FLD_l,
       FLD_attr1,
       FLD_attr2,
       FLD_rpt,
       FLD_fmt,
       FLD_help_num,
       FLD_off1,         /* Offset im VAL-Format   */
       FLD_off2,
       FLD_flg1,
       FLD_typ,          /* == flg2                */
       FLD_flg3,
       FLD_flg4;
};

/*****************************************************************************
ANM: Bei Aktivierung eines Feldes wird der Attribut Code 1 invertiert
     verwendet. Falls das Bit 7 in flg1 (flg | 0x80) gesetzt ist, wird
     der Attribut Code 2 (nicht invertiert) verwendet.

ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
flg1: (altes F1)
ÄÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
 Bit 0 ³ 0x01 ³ Forward Link (N/A)
     1 ³ 0x02 ³ Backward Link (N/A)
     2 ³ 0x04 ³ (reserved)
     3 ³ 0x08 ³ Return after 1 Character Input
     4 ³ 0x10 ³ Type Ahead: 1 -> Autoenter wenn Feld voll ist
     5 ³ 0x20 ³ No Reedit: 1 -> Field nur 1 x editieren
     6 ³ 0x40 ³ CLEAR: 1 -> Feld l”schen vor Edit
     7 ³ 0x80 ³ ATTR2: 1 -> bei Attr2 statt inversertierung von Attr1 
ÄÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
*****************************************************************************/

/* Definition f. Button Descriptor ---------------------------------------- */
#define BUT_size      16
#define BUTo_ax        0
#define BUTo_ay        2
#define BUTo_bx        4
#define BUTo_by        6
#define BUTo_key       8
#define BUTo_color1   10
#define BUTo_value    12

struct BUTTON_DESC
{
  int  BUT_ax, BUT_ay;                  /* Button Koordinaten   */
  int  BUT_bx, BUT_by;
  int  BUT_key;                         /* quivalenter Key     */
  int  BUT_color1;                      /* Farbe bei Anzeige    */
                                        /* Button-Anzeige       */
  long BUT_value;
} ;

/* Field Funktionen: ------------------------------------------------------ */
int  cdecl mm_field_locate   (char  field_descriptors [],
                              int   field_count,
                              int   x,
                              int   y,
                              int  *field_number);

int  cdecl mm_field_allocate (char  field_descriptors [],
                              int   field_count,
                              char *data []);

void cdecl mm_field_jump (char field_descriptor [],
                          int  field_count,
                          int  t,
                          int *f,
                          int *new_off);

/* Button Funktionen: ----------------------------------------------------- */
int cdecl mm_button_locate (char  button_descriptor [],
                            int   button_count,
                            int   x,
                            int   y,
                            int  *button_number);

#endif /* __GG_fields__ */
