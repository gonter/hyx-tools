/*
 *  include FILE <gg/ggcms.h>
 *
 *  redefine some things for use with CMS in order to avoid
 *  those nasty name conflicts
 *  HYX: no_links
 *
 *  written:       1992 02 06
 *  latest update: 1995-08-11
 *
 */


#ifndef __GG_CMS__
#define __GG_CMS__
#define __CMS__

/* renamed library functions: --------------------------------------------- */
#define unlink                  remove

/* renamed functions: ----------------------------------------------------- */
#define sixel_encode            se_01_sd
#define sixel_encode_setup      se_02_sd
#define sixel_encode_bits       se_03_sd
#define sixel_decode            se_04_sd
#define sixel_decode_setup      se_05_sd
#define sixel_decode_bits       se_06_sd
#define sixel_segment_decode    se_07_sd
#define sixel_segment_processor se_08_sd
#define sixel_analyze_segment   se_09_sd
#define sixel_analyze_bin_tags  se_10_sd
#define sixel_segment_sort      se_11_sd
#define sixel_segment_list      se_12_sd
#define sixel_segment_completeness se_13_sd
#define sixel_segment_pass2     se_14_sd
#define sixel_identify_tag      se_15_sd
#define sixel_identify_attribute se_16_sd
#define print_bin_f             se_17_sd
#define print_bin_d             se_18_sd

/* from <gg/strings.h> */
#define strcmp_c                st_01cms
#define strcmp_ebcdic           st_02cms
#define strcmp_us               st_03cms
#define strcmp_weighted         st_04cms
#define strcmp_cweighted        st_05cms
#define strcmp_cre              st_06cms
#define translate               st202cms
#define isolate_words           isowrds
#define isolate_tokens          isotoks
#define isolate2words           iso2wrds

/* from <gg/sbr.h> */
#define string_pull             strpl
#define string_push             strps
#define actual_datim            actd
#define actual_datim_int        actdi
#define ftransfer               sbr01
#define f2transfer              sbr02
#define f3transfer              sbr03
#define ftransfer_to_shar       sbr04
#define f5transfer_to_shar      sbr05
#define ftransfer_line          sbr06

/* from <gg/hyx.h> */
#define get_attr_value          getav
#define find_attr_name          fndan
#define find_attr_value         fndav

/* from <gg/dpp.h> */
#define _get_parameter_value    gpmv0001

#define bitmask_32bit           bm32bit
#define put_chartable           pcht

/* from <gg/filename.h> */
#define fmt_dta_date            fmtdta1
#define fmt_dta_time            fmtdta2

/* nl_kr package: --------------------------------------------------------- */
#define discard_document_info   dsdif
#define discard_document_id     dsdid

#define lookup_file                     lut01
#define lookup_file_xfn                 lut02
#define lut_char_get_word_buffer        lut03
#define lut_char_get_dump_beg           lut04
#define lut_char_get_dump_end           lut05
#define lut_file_get_word_buffer        lut06
#define lut_file_get_dump_beg           lut07
#define lut_file_get_dump_end           lut08
#define lut_print                       lut09
#define lut_print_block                 lut10
#define lut_process                     lut11
#define lut_process_block               lut12
#define deref_word                      lut13
#define deref_word_ref                  lut14
#define read_word_ref_list              lut15
#define read_word_ref                   lut16
#define discard_doc_info                lut17
#define discard_doc_id                  lut18
#define print_veronica_hit_list         lut19
#define print_veronica_docinfo_list     lut20
#define print_gopher_hit_list           lut22a
#define print_doc_hit_list              lut22b
#define print_document_info_list        lut22c
#define print_docdir_hyx                lut22d
#define print_docdir_gopher             lut22e
#define read_document_info_list         lut23
#define read_docdir_info                lut24
#define luttest                         lut25a
#define luttest_manual                  lut25m
#define deref_set_match_pattern         sxmp

#define YTREE_ALLOC_SIZE        ytals
#define YTREE_ALLOCATED         ytalc
#define read_words              rw007
#define ytree_free              ytfr
#define ytree_print_node        ytpn
#define ytree_process           ytpr
#define get_word_ref_list       wrx1a
#define get_word_ref            wrx1b

#define ytree_wr_ptr2idx        ytwp2i
#define ytree_wr_idx2ptr        ytwi2p

/* reprogrammed functions: ------------------------------------------------ */
char *strdup (char *str);

/* simulated stat() ------------------------------------------------------- */
struct stat
{
  long st_size;
  int mode;
} ;

int stat (char *fn, struct stat *st);
int access (char *fn, int mode);

#endif /* __GG_CMS__ */
