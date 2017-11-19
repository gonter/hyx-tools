/*
 *  include File <gg/diagnose.h>
 *
 *  This file contains definitions for diagnostic codes used in
 *  GG's library functions.
 *
 *  written:       1992-12-27: <Gerhard.Gonter@wu-wien.ac.at>
 *  latest update: 1995-12-14
 *
 */

#ifndef __GG_diagnose__
#define __GG_diagnose__

/* ------------------------------------------------------------------------ */
extern long gg_diagnose;         /* variable to hold diagnose codes          */

/* file names and general file handling: ---------------------------------- */
#define EF_not_found            0x00000101L
#define EF_couldnt_stat         0x00000102L     /* stat() returned an error */

/* management of buffers: ------------------------------------------------- */
#define EB_size_exceeded        0x00000201L

/* memory management: (client) -------------------------------------------- */
#define EM_no_memory            0x00000301L

/* tfb file processing: --------------------------------------------------- */
#define TFB_ge_no_lut           0x00000401L
#define TFB_ge_no_tfb           0x00000402L
#define TFB_ge_tfb_bad          0x00000403L

/* lexicon processing: ---------------------------------------------------- */
#define LEX_RT_init_error       0x00000501L     /* initialization of        */
                                                /* read_lexicon_text        */
                                                /* failed                   */
#define LEX_RT_no_frame_close   0x00000502L     /* no frame close found     */


#endif /* __GG_diagnose__ */
