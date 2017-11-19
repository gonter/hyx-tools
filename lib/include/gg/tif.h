/*
 *  include FILE <gg/tif.h>
 *
 *  definitions for images in TIF-format
 *  (Tagged Image File Format)
 *
 *  written:       1989 10 16
 *                 1991 10 03: Revision
 *  latest update: 1994-11-11
 *
 */

#ifndef __GG_tif__
#define __GG_tif__

#ifndef MSDOS
#define cdecl
#endif

#define TIF_ORDER_INTEL        0x4949  /* II */
#define TIF_ORDER_MOTOROLA     0x4D4D  /* MM */

/* ------------------------------------------------------------------------ */
struct TIF_HEADER
{
  int   tif_order;
  int   tif_version;
  long  tif_directory_offset;
} ;

/* ------------------------------------------------------------------------ */
struct TIF_DIRECTORY
{
  int   tif_dir_count;
  long  tif_next_directory;
  int   tif_dir_size;                   /* doesnt come from the file!!      */
                                        /* size of puffer                   */
  struct TIF_DIR_ENTRY *tif_entry;
} ;

/* ------------------------------------------------------------------------ */
struct TIF_DIR_ENTRY
{
  int   tif_dir_tag;
  int   tif_dir_type;
  long  tif_dir_length;
  long  tif_dir_offset;
} ;

/* Tags -- Name ---------------------- Code ------------------------------- */
#define TT_NewSubfileType               254
#define TT_SubfileType                  255
#define TT_ImageWidth                   256
#define TT_ImageLength                  257
#define TT_BitsPerSample                258
#define TT_Compression                  259

#define TT_PhotometricInterpretation    262
#define TT_Threshholding                263
#define TT_CellWidth                    264
#define TT_CellLength                   265
#define TT_FillOrder                    266

#define TT_DocumentName                 269
#define TT_ImageDescription             270
#define TT_Make                         271
#define TT_Model                        272
#define TT_StripOffsets                 273
#define TT_Orientation                  274

#define TT_SamplesPerPixel              277
#define TT_RowsPerStrip                 278
#define TT_StripByteCounts              279
#define TT_MinSampleValue               280
#define TT_MaxSampleValue               281
#define TT_XResolution                  282
#define TT_YResolution                  283
#define TT_PlanarConfiguration          284
#define TT_PageName                     285
#define TT_XPosition                    286
#define TT_YPosition                    287
#define TT_FreeOffsets                  288
#define TT_FreeByteCounts               289
#define TT_GrayResponseUnit             290
#define TT_GrayResponseCurve            291
#define TT_Group3Options                292
#define TT_Group4Options                293

#define TT_ResolutionUnit               296
#define TT_PageNumber                   297

#define TT_ColorResponseCurves          301

#define TT_Software                     305
#define TT_DateTime                     306

#define TT_Artist                       315
#define TT_HostComputer                 316
#define TT_Predictor                    317
#define TT_WhitePoint                   318
#define TT_PrimaryChromaticities        319
#define TT_ColorMap                     320

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
/* tif00001.c */ int cdecl tif_read_directory (FILE *fi,
                   struct TIF_DIRECTORY *dir, int order);
#endif
/* tif00002.c */ char *cdecl tif_type (int type_code);
#ifdef _FILE_DEFINED
/* tif00003.c */ int cdecl tif_report_dir (FILE *fi, FILE *fo,
                   long relative_offset, struct TIF_DIRECTORY *tif_dir);
/* tif00004.c */ int cdecl tif_report_dir_entry (FILE *fi, FILE *fo,
                   long relative_offset, int nr, struct TIF_DIR_ENTRY *tp);
#endif

#endif /* __GG_tif__ */
