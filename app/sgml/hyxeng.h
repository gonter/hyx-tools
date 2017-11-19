/*
 *  FILE E:\usr\sgml\hyxeng.h
 *
 *  Prototypes fÅr die HyperText Engine
 *
 *  1990 07 01
 *  1991 02 03: Revision
 *
 */

#ifndef __GG_hyxeng__
#define __GG_hyxeng__

int  cdecl hyx_engine_command (char *command);
void cdecl hyx_engine_opcode (int *command);
int  cdecl hy_purge (char *fn, int verbose_mode);
int  cdecl hyx_engine_list (FILE *fo, char *fn,
                            struct HYTXT_FRAME **hytxt_frame,
                            int list_mode, int scan_mode, int sort_mode,
                            int prnt_mode);
int  cdecl hyx_engine_export (FILE *fo, char *fn,
                            struct HYTXT_FRAME **hytxt_frame,
                            int list_mode, char *frame,
                            void (*export_function) (int ch));

#endif
