/*
 *  FILE %ned/00/ned0006.c
 *
 *  global ds: console, input, macro, setup
 *
 *  written:       1987 09 09
 *  latest update: 1997-09-07 12:56:54
 *  $Id: ned0006.c,v 1.2 2005/09/04 19:03:16 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/filename.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int pfx= 0;                     /* Kommand Key Praefix                      */
int key= 0;                     /* betaetigte Taste                         */
int ptbl_offset= 0;             /* offset in the primitives tables          */
int repeat= 0;                  /* repeat factor for commands               */

/* ------------------------------------------------------------------------ */
FILE *jou= (FILE *) 0;
int jou_flag= 0;                /* 0 -> Jour File geschlossen               */
                                /* 1 -> .    .    beschreiben               */
                                /* 2 -> .    .    lesen                     */
char jou_name [MAX_FNM_LENGTH]= "ned.jou";      /* Name des Journal Files   */
char stp_fnm [MAX_FNM_LENGTH]= "ned.stp";       /* Name des SETUP Files     */

int maus_angeschlossen= 0;      /*  0 .. keine Maus                         */
                                /* >0 .. Maustyp                            */
                                /*       (siehe File MAUS.H)                */

/* macro processing ------------------------------------------------------- */
int  MPflag= 0;                 /* 1 -> macro is currently expanded         */

int oper_level= 0;              /* Operations Level:                        */
                                /* 0     -> Alle Privilegien                */
                                /* 32000 -> nur mehr Read Only              */

int ned_werr_dont_complain= 0;  /* 1 -> dont complain if file cant be       */
                                /*      opened for writing                  */

/* something needs to be performed outside the event handler */
ned_primitive_function *special_event= (ned_primitive_function *) 0;
