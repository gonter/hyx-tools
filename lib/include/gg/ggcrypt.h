/*
 *  include FILE <gg/ggcrypt.h>
 *
 *  simple encryption routines
 *
 *  written:       1994-09-18
 *  latest update: 1997-10-05  9:41:24
 *  $Id: ggcrypt.h,v 1.4 2009/09/24 12:21:08 gonter Exp $
 *
 */

#ifndef __GG_ggcrypt__
#define __GG_ggcrypt__

#include <gg/floskel.h>

/* ------------------------------------------------------------------------ */
#define _GG_CRYPT_defined
struct GG_CRYPT
{
  char *GGC_challenge;
  char *GGC_key;
  char *GGC_key_str;
  int GGC_index;
} ;

#define KEYED_MD5_SIZE 20

/* ------------------------------------------------------------------------ */
#ifdef MODE_CFB
/* cipher feedback mode */
#define ggc_file_encrypt        ggc_file_cfb
#define ggc_stream_encrypt      ggc_stream_cfb
#define ggc_block_encrypt       ggc_block_cfb
#define ggc_pad                 ggc_pad_cfb
#define ggc_pad_md5             ggc_pad_md5_cfb
#endif

#ifdef MODE_ECB
/* electronic coodebook mode */
#define ggc_file_encrypt        ggc_file_ecb
#define ggc_stream_encrypt      ggc_stream_ecb
#define ggc_block_encrypt       ggc_block_ecb
#define ggc_pad                 ggc_pad_ecb
#define ggc_pad_md5             ggc_pad_md5_ecb
#endif
/** #define GGC_BUFFER_SIZE 8192 **/
#define GGC_BUFFER_SIZE 524288

/* ------------------------------------------------------------------------ */
#define ggcrypt_new() \
  ((struct GG_CRYPT *) calloc (sizeof (struct GG_CRYPT), 1))

#define ggcrypt_free(x) free (x)

/* ------------------------------------------------------------------------ */
/* ggcryp01.c */ int cdecl ggcrypt_very_simple (char *fn,
                   char *crypt_code, int crypt_length, char *crypt_tmp,
                   char *buffer1, char *buffer2, int BUFFER_SIZE);
/* ggcryp02.c */ int cdecl gg_encrypt (char *fn,
                   int crypt_length, char *crypt_tmp,
                   char *buffer1, char *buffer2, int BUFFER_SIZE);

/* ggcryp03.c */ int cdecl gg_decrypt (char *fn,
                   int crypt_length, char *crypt_tmp,
                   char *buffer1, char *buffer2, int BUFFER_SIZE);

/* /ggcryp04.c */ int cdecl ggcrypt_set_code (char *cp);
#ifdef _FILE_DEFINED
                  int cdecl ggcrypt_fputc_code (int c, FILE *f);
                  int cdecl ggcrypt_fgetc_code (FILE *f);
                  int cdecl ggcrypt_flush_last (FILE *f);
#endif /* _FILE_DEFINED */
                  int cdecl ggcrypt_encode (int c);

/* ggcryp05.c */ int cdecl ggcrypt_block (unsigned char *block, int block_lng,
                   unsigned char *key, int key_lng);

/* ggcryp06.c */ int cdecl ggcrypt_string (unsigned char *string,
                   unsigned char *key, int key_lng);

/* ggcryp07.c */ char *cdecl sec_generate_key (char *principal,
                   char *resource, char *identifier, char *secret);

/* ggcryp08.c */ int cdecl agettok_get_hash_key (char *user_from,
                   char *user_to, char *resourc_name, char *hash, char *key,
                   int hash_size);
                 char *cdecl agettok_get_resource_password (char *file_name,
                   char *user_from, char *user_to, char *resourc_name,
                   int get_flags);
                 char *cdecl agettok_get_resource_entry (char *file_name,
                   char *user_from, char *user_to, char *resource_name);
                 int cdecl agettok_set_resource_password (char *file_name,
                   char *user_from, char *user_to, char *resourc_name,
                   char *resource_password, int set_flags);
#define AGETTOK_clear_password  0x0001
#define AGETTOK_write_entry     0x0002

/* ggcryp09.c */ char *cdecl agettok_get_challenge (char *password_file,
                   char *user_from, char *user_to, char *resource_name,
                   char *challenge);
/* ggcryp10.c */ char *cdecl sca_get_sigfile (char *username);
/* ggcryp11.c */ char *cdecl sca_get_signature (char *username,
                   char *password);
/* ggcryp12.c */ int cdecl sca_check_signature (char *sca_sig_file,
                   char *sca_signature);
/* ggcryp13.c -- ggc_block_encrypt () */
                 int cdecl ggc_block_ecb (struct GG_CRYPT *ggc,
                   char *buffer, int size);
                 int cdecl ggc_block_cfb (struct GG_CRYPT *ggc,
                   char *buffer, int size);
/* ggcryp14.c */ int cdecl ggc_set_session_key (struct GG_CRYPT *ggc,
                   char *key_file, char *from, char *to, char *resource);
/* ggcryp15.c -- ggc_file_encrypt () */ 
                 int ggc_file_ecb (struct GG_CRYPT *ggc, char *fn,
                   char *crypt_tmp, long padding);
                 int ggc_file_cfb (struct GG_CRYPT *ggc, char *fn,
                   char *crypt_tmp, long padding);
/* ggcryp16.c */ struct GG_CRYPT *ggc_set_key (struct GG_CRYPT *ggc,
                   char *key);
/* ggcryp17.c */ int ggc_dispose_key (struct GG_CRYPT *ggc);
/* ggcryp18.c */ int ggc_dispose_block (char **cpp, int lng);
/* ggcryp19.c */ int ggc_dispose (struct GG_CRYPT *ggc);
#ifdef _FILE_DEFINED
/* ggcryp20.c -- ggc_stream_encrypt () */ 
                 int ggc_stream_ecb (struct GG_CRYPT *ggc,
                   FILE *fi, FILE *fo, long padding);
                 int ggc_stream_cfb (struct GG_CRYPT *ggc,
                   FILE *fi, FILE *fo, long padding);
/* ggcryp23.c */
void ggc_pad (struct GG_CRYPT *ggc, FILE *fo, char *buffer,
                long padding, long BS);
#endif /* _FILE_DEFINED */
/* ggcryp24.c */ int ggc_file_2enc (struct GG_CRYPT *ggc, char *fn,
                   char *crypt_tmp, long padding1, long padding2);
/* ggcryp25.c */ int ggc_file_2dec (struct GG_CRYPT *ggc, char *fn,
                   char *crypt_tmp);

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
#ifdef __GG_attlist__
/* ggcryp21.c */
int ggc_stream_2encrypt (struct GG_CRYPT *ggc, FILE *fi, FILE *fo,
      ATTLIST *al_pre, ATTLIST *al_post, long padding1, long padding2);
/* ggcryp22.c */
int ggc_stream_2decrypt (struct GG_CRYPT *ggc, FILE *fi, FILE *fo);

/* ggcryp26.c */
int ggc_wr_tag_block (struct GG_CRYPT *ggc, FILE *fo, char *tag_name,
      ATTLIST *al, char *buffer);
#endif /* __GG_attlist__ */

#ifdef __contrib_md5gg__
/* ggcryp27.c */
long ggc_pad_md5 (struct GG_CRYPT *ggc, MD5_CTX *md5,
                  FILE *fo, char *buffer, long padding, long BS);
#endif /* __contrib_md5gg__ */

#endif /* _FILE_DEFINED */

#endif /* __GG_ggcrypt__ */
