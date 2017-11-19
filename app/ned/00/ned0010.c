/*
 *  FILE %ned/00/ned0010.c
 *
 *  additional screen control
 *
 *  written:       1992 04 04
 *  latest update: 1997-01-12 16:37:31
 *  $Id: ned0010.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include "ed.h"

/* ------------------------------------------------------------------------ */
struct BUTTON_DESCRIPTOR *buttons= (struct BUTTON_DESCRIPTOR *) 0;

int NED_TEXT_NIM_X= 0;
int NED_TEXT_MIN_Y= 0;
int NED_TEXT_MAX_X= 80;
int NED_TEXT_MAX_Y= 25;
