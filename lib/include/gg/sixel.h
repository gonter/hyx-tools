/*
 *  include FILE <gg/sixel.h>
 *
 *  written:       1992 02 01
 *  latest update: 1995-03-11
 *
 */

#ifndef __GG_sixel__
#define __GG_sixel__

#include <gg/floskel.h>

#define BASE64_ENCODING

/* ------------------------------------------------------------------------ */
struct SIXEL_TAG_bin_f
{
  int STbf_initialized;         /* 1 -> filled in */
  char *STbf_fn;
  char *STbf_url;
  char *STbf_doi;
  long STbf_size;
  long STbf_parts;
} ;

/* ------------------------------------------------------------------------ */
struct SIXEL_TAG_bin_d
{
  int STbd_initialized;         /* 1 -> filled in */
  char *STbd_doi;
  long STbd_beg;
  long STbd_lng;
  long STbd_part;
  int STbd_ws;
  int STbd_cont;
} ;

/* ------------------------------------------------------------------------ */
struct SIXEL_SEGMENT_desc
{
  char *SSd_filename;
  long SSd_beg;
  int SSd_ok;                   /* 1 -> segment is part of the full list    */

  struct SIXEL_SEGMENT_desc *SSd_next;
  struct SIXEL_TAG_bin_f *SSd_bin_f;
  struct SIXEL_TAG_bin_d *SSd_bin_d;
} ;

/* sixel encoder split modes ---------------------------------------------- */
#define SIXEL_OM_stream 0       /* output to a (FILE *)                     */
#define SIXEL_OM_1afile 1       /* file name for output is given (append)   */
#define SIXEL_OM_1ofile 2       /* file name for output is given (overwrite)*/
#define SIXEL_OM_files  3       /* pattern for file name is given:          */
                                /* example: "sp%06lX.spl" or "xyz.%03lX"    */
                                /* out_count must be set!!!!                */
#define SIXEL_OM_system 4       /* call program for processing of file      */

/* sixel encoder split modes ---------------------------------------------- */
#define SIXEL_SM_none   0       /* no splitting                             */
#define SIXEL_SM_parts  1       /* number of parts specified                */
#define SIXEL_SM_words  2       /* number of source words per segment       */
#define SIXEL_SM_lines  3       /* number of encoded lines per segment      */

/* bitmsk32.c ------------------------------------------------------------- */
extern unsigned long bitmask_32bit [33];

/* sixeltab.c ------------------------------------------------------------- */
extern unsigned char *sixel_table;
extern unsigned char *sixel_table_name;

/* sixelenc.c ------------------------------------------------------------- */
int cdecl sixel_encode (long wrd, char *sixel_buffer);
int cdecl sixel_encode_setup (int wordsize);
int cdecl sixel_encode_bits (void);

/* sixeldec.c ------------------------------------------------------------- */
int cdecl sixel_decode (int ch, long *word_buffer);
int cdecl sixel_decode_setup (int wordsize);
int cdecl sixel_decode_bits (void);

/* sixelval.c ------------------------------------------------------------- */
int cdecl sixel_value (int ch);

/* sfileenc.c ------------------------------------------------------------- */
int cdecl sixel_file_encode (char *fn, int word_size,
  char *enc_fn, char *enc_url, char *enc_doi, char *enc_ty,  
  int out_mode, void *out_pointer,
  long *out_count, int split_mode, long split_value,
  int line_length);

/* ssegmdec.c ------------------------------------------------------------- */
#ifdef _FILE_DEFINED
int cdecl sixel_segment_decode (FILE *fi, FILE *fo,
  long word_count, int first_char);
/* return values: 0x00 .. 0xFF = last character read and not processed      */
/* negative values:                                                         */
#endif
#define SIXEL_SD_error          -1      /* can't read or write stream       */
#define SIXEL_SD_eof            -2      /* input stream's EOF reached       */
#define SIXEL_SD_counted_down   -3      /* word_count is down to 0          */

/* ssegmana.c ------------------------------------------------------------- */
#ifdef _FILE_DEFINED
int cdecl sixel_analyze_segment (FILE *fi,
  FILE *((*fo_proc) (struct SIXEL_TAG_bin_f *stbf,
                     struct SIXEL_TAG_bin_d *stbd)),
  struct SIXEL_SEGMENT_desc **ssd,
  struct SIXEL_TAG_bin_f *stbf_preset,
  int word_size, int pass);

int cdecl sixel_analyze_bin_tags (FILE *fi, int write_data,
  struct SIXEL_TAG_bin_f *stbf, struct SIXEL_TAG_bin_d *stbd);
/* return values: SIXEL_AT_xxxx */
#endif

/* stagiden.c ------------------------------------------------------------- */
int cdecl sixel_identify_tag (char *buffer);

#define SIXEL_AT_error         -1
#define SIXEL_AT_junk           0
#define SIXEL_AT_bin_f          1
#define SIXEL_AT__bin_f         2
#define SIXEL_AT_bin_d          3
#define SIXEL_AT__bin_d         4
#define SIXEL_AT_bin            5
#define SIXEL_AT__bin           6
#define SIXEL_AT_tag            7
#define SIXEL_AT__tag           8

/* sattiden.c ------------------------------------------------------------- */
int cdecl sixel_identify_attribute (char *buffer);

#define SIXEL_AA_error         -1
#define SIXEL_AA_junk           0
#define SIXEL_AA_doi            1
#define SIXEL_AA_fn             2
#define SIXEL_AA_size           3
#define SIXEL_AA_lng            4
#define SIXEL_AA_beg            5
#define SIXEL_AA_part           6
#define SIXEL_AA_parts          7
#define SIXEL_AA_cont           8
#define SIXEL_AA_ws             9

/* sixdeb01.c ------------------------------------------------------------- */
#ifdef _FILE_DEFINED
void cdecl print_bin_f (FILE *fo, struct SIXEL_TAG_bin_f *stbf);
#endif

/* sixdeb02.c ------------------------------------------------------------- */
#ifdef _FILE_DEFINED
void cdecl print_bin_d (FILE *fo, struct SIXEL_TAG_bin_d *stbd);
#endif

/* sdec.c ----------------------------------------------------------------- */
int cdecl sixel_segment_processor (char *fn, long begin_offset,
  int word_size, int processing_mode, int options);

#define SIXEL_PRC_linear        0
#define SIXEL_PRC_pass1         1       /* pass 1: scan for segments        */
#define SIXEL_PRC_pass2         2       /* pass 2: decode the segments      */
#define SIXEL_PRC_segmlib       3       /* manage a segment library         */

#define SIXEL_OPT_none     0x0000       /* no options (bit field)           */
#define SIXEL_OPT_ack_name 0x0001       /* acknowledge a files name         */

/* ssegmsrt.c ------------------------------------------------------------- */
int cdecl sixel_segment_sort (struct SIXEL_SEGMENT_desc *ssd);
#ifdef _FILE_DEFINED
int cdecl sixel_segment_list (FILE *fo);
#endif
int cdecl sixel_segment_pass2 (int word_size, int opts);
int cdecl sixel_segment_completeness (void);

/* encoding scheme -------------------------------------------------------- */
#ifdef __COMMENT__
Sixel encoding repacks 6 bits of information in a source data stream
into 64 ASCII characters in the sixel encoded data stream:

base64 encoding:
characters 'A'..'Z' = values  0..25
characters 'a'..'z' = values 26..51
characters '0'..'9' = values 52..61
character  '+'      = value 62
character  '/'      = value 63

old encoding scheme (base64 encoding):
characters 'a'..'z' = values  9..25
characters 'A'..'Z' = values 26..51
characters '0'..'9' = values 52..61
character  '+'      = value 62
character  '-'      = value 63

new encoding scheme:
character  '+'      = value 0
character  '-'      = value 1
characters '0'..'9' = values  2..11
characters 'A'..'Z' = values 12..37
characters 'a'..'z' = values 38..63

The bits are numbered from word #0, bit #0 to bit #(word_size-1) and
mapped into sixel values in the same order. The ordering of the bits
is fully preserved.
(Bit[i] in the source data stream is also bit[i] in the sixel data stream.)
#endif /* __COMMENT__ */

/* usage notes ------------------------------------------------------------ */
#ifdef __COMMENT__
sixel_encode_bits and sixel_decode_bits return the number of valid bits
still contained in the buffers of the respective modules. To avoid data
loss it is necessary to 'flush' out any valid data bits from the encoder.

This means, after the encoder has processed all words from the source
data stream, the function sixel_encode_bits must be called to obtain the
number of bits still contained in the encoders buffer. Call the function
sixel_encode ((long) 0, buffer) until it returns a value > 0 and
then write only the character in buffer [0] to the sixel data stream.

Remaining bits in the decoders buffer are meaningless and can be ignored.

If the word size is smaller that 6, the encoder might deliver more
words from the sixel data stream than there were in the beginning.
Example: word size is 5 bits, 5 words to encode, makes 25 bits.
         25 bits need 5 sixels, but 5 sixels can hold 30 bits which
         is also enough for 6 words.
#endif /* __COMMENT__ */

#endif /* __GG_sixel__ */
