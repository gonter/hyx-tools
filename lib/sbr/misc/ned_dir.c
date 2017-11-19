/*
 *  FILE %sbr/ned_dir.c
 *
 *  written:       1996-03-16
 *  latest update: 1996-03-16 18:15:31
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
char *NED_DIR= "_bak_ftr.ned";
