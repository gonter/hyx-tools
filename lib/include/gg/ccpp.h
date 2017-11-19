/*
 *  include FILE <gg/ccpp.h>
 *
 *  C Preprocessor Definitions
 *
 *  !!!!!! <gg/scanr.h> muss vorher includiert werden !!!!!1
 *
 *  written:       1988 02 14
 *                 1990 07 21: Revision
 *  latest update: 1995-08-30
 *
 */

#ifndef __GG_ccpp__
#define __GG_ccpp__

#include <gg/floskel.h>

typedef int CPP_OUTPUT (int tv, long val);

/* ------------------------------------------------------------------------ */
struct FILESTACK                /* Verschachtelte INCLUDEs      */
{
  long position;
  int  znr;
  char fname [32];
  struct FILESTACK *fs_nxt;
} ;

/* ------------------------------------------------------------------------ */
struct SKIPSTACK                /* Verschachtelte IFDEFs usw.   */
{
  struct SKIPSTACK *sk_nxt;
  int sk_mode;                  /* SKM_xxxx */
} ;

/* ------------------------------------------------------------------------ */
struct T_NODE                   /* Liste von Tokens + Tokenvalues           */
{
  int            TN_tok;
  long           TN_val;
  struct T_NODE *TN_nxt;
} ;

/* ------------------------------------------------------------------------ */
struct DEFINELIST
{
  int pars;                     /* # der Parameter: -1 ohne Parameter       */
  struct DEFINELIST *dl_nxt;    /* Verkettung                               */
  struct IDENT  *id;            /* Name fuer Ersetzung                      */
  struct T_NODE *parlist;       /* formale Parameterliste                   */
  struct T_NODE *replace;       /* Ersetzungstext                           */
} ;

/* ------------------------------------------------------------------------ */
#define SKM_r           1       /* alles      lesen                         */
#define SKM_rif         2       /* IF   Zweig lesen                         */
#define SKM_selse       3       /* ELSE Zweig skippen                       */
#define SKM_sif         4       /* IF   Zweig skippen                       */
#define SKM_relse       5       /* ELSE Zweig lesen                         */
#define SKM_s           6       /* alles      skippen                       */

/* ------------------------------------------------------------------------ */
/* Uebergaenge:                                                             */
/* #ifXdef: PUSH; bei Skipxx in Skip gehen                                  */
/*                sonst entscheiden und in readif oder skipif gehen         */
/* #else:   readif -> skipelse; skipif -> readelse; skip -> skip            */
/* #endif:  POP;                                                            */

/* ------------------------------------------------------------------------ */
int cpp_define_output (CPP_OUTPUT *op, struct CC_C_SCANNER *xx,
                       struct CC_SCANNER *cc, struct CC_SCANNER *cpp);
int cpp_init (void);
struct DEFINELIST *cpp_find_define (struct IDENT *ip);
int cpp_define (struct IDENT *ip);
int cpp_undefine (struct IDENT *ip);
int cpp_input (int tv, long val);
int cpp_process2 (int tv, long val);
int cpp_print_defines (void);
int cpp_set_znr (int z, char *f, int flg);

#endif /* __GG_ccpp__ */
