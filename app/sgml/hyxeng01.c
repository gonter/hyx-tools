/*
 *  FILE ~/usr/sgml/hyxeng01.c
 *
 *  HyperText Engine
 *
 *  written:       1990 04 12
 *  latest update: 1994-12-11
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/hytxt.h>
#include <gg/lookup.h>
#include <gg/ztree.h>
#include "hyxeng.h"

#include "hyxeng01.inc"

static char hyx_cmd [256];

/* ------------------------------------------------------------------------ */
int hyx_engine_command (char *command)
{
  int rv;               /* erhaltener Funktionswert                         */
  int ret_val= 0;       /* gelieferter Funktionswert                        */
  int lng;              /* Laenge des gefundenen Worts, nicht ausgewertet   */
  int cmd= 0;           /* Beginn des zu ueberpruefenden Eintrags (=Command)*/
  int pars;             /* Beginn der Parameter (ev. weitere Parameter)     */
  int check;            /* Zahl der zu ueberpruefenden Eintraege            */
  int cp= 2;            /* Code Pointer: Eintragung fuer weiteren Layer     */
                        /*               der HyperEngine                    */
  struct WORD_INFO wi;  /* wi.word_number    ... HyperEngine OpCode         */
                        /* wi.word_frequency ... Mindestzahl der Parameter  */

  for (check= 1; check > 0; check--)
  {
    for (; command [cmd]; cmd++)
        if (command [cmd] != ' ') break;
    if (command [cmd] == 0) return -1;

    for (pars= cmd; command [pars]; pars++)
        if (command [pars] == ' ') { command [pars++] = 0; break; }

    for (; command [pars]; pars++)
        if (command [pars] != ' ') break;

    rv= lookup_char (hyxeng_cmd, &command [cmd],
                     (long *) &wi,             /* ################## */
                     &lng);
    check += (wi.word_frequency / 256);

/*******************************
    printf (">> check=%d cmd=`%s' pars=`%s'\n",
            check, &command [cmd], &command [pars]);
    printf ("<< rv=%d  lng=%d OpCode=%d Parameter: checked=%d unchecked=%d\n",
            rv, lng, wi.word_number,
            wi.word_frequency / 256, wi.word_frequency % 256);
*******************************/

    if (!(rv & 0x0007)) return -1;
    if (cp == 2) ret_val= wi.word_number;
    hyx_cmd [cp++]= (char) (wi.word_number / 256);   /* OpCode abspeichern */
    hyx_cmd [cp++]= (char) (wi.word_number % 256);   /* OpCode abspeichern */
    cmd= pars;
  }
  
  /* Unchecked Parameter werden nur auf Vorhandensein geprueft */
  if ((wi.word_frequency % 256) > 0 && command [pars] == 0) return -1;
  strcpy (&hyx_cmd [cp], &command [pars]);
  cp += strlen (&command [pars]);
  hyx_cmd [0]= (char) (cp / 256);
  hyx_cmd [1]= (char) (cp % 256);

/*************************
  printf (">>");
  if (rv & LOOKUP_found)     printf (" exakt");
  if (rv & LOOKUP_prefix)   printf (" zu lang");
  if (rv & LOOKUP_prefix_3)  printf (" Abkuerzung");
  printf ("\n");
*************************/

  hyx_engine_opcode ((int *) hyx_cmd);

  return ret_val;
}
