/*
 *  include FILE <gg/cctable.h>
 *
 *  written:       1987 11 15
 *                 1990 07 22: Revision
 *  latest update: 1995-08-30
 *
 */

#ifndef __GG_cctable__
#define __GG_cctable__

/* ------------------------------------------------------------------------ */
#define ID_LNG          24      /* signif. Laenge eines Identifiers   */
#define ID_Tsize       100      /* Groesse der Symbol-Tabelle         */
#define FL_Tsize        40      /* .       .   Float-Konst-Tabelle    */
#define ST_Tsize        50      /* .       .   String-Konst-Tabelle   */
#define ST_Psize       400      /* .       des String Puffers         */

/* ------------------------------------------------------------------------ */
struct IDENT
{
  int atyp;
  char *name;
} ;


/* ------------------------------------------------------------------------ */
struct FLOAT_CONST
{
  long fv1;
  int  fv2, fv3, evz, mvz;
} ;

/* ------------------------------------------------------------------------ */
struct ppFLOAT_CONST
{
  struct ppFLOAT_CONST *fl_nxt;
  struct   FLOAT_CONST  fl_flt;
} ;

/* ------------------------------------------------------------------------ */
struct ppSTRING
{
  struct ppSTRING *st_nxt;
  char strv [4];
} ;

/* ------------------------------------------------------------------------ */
#ifndef NIL
#define NIL     (char *) 0
#endif

/* ------------------------------------------------------------------------ */
void cc_table_init (void);
struct IDENT *cc_inst_id (char *s);
char *cc_str_const (char *s);
struct FLOAT_CONST *cc_fl_const (long v1, int v2, int v3, int vz);
struct IDENT *cc_rsvd_id (char *s, unsigned int num);
void cc_in_rsvd (void);

#endif /* __GG_cctable__ */
