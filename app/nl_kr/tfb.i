// %gg/work/fbsd/gg/swig/misc/tfb.i
// $Id: tfb.i,v 1.2 2002/07/17 07:03:52 gonter Exp $
%module tfb
%{
#include <gg/tfb.h>
#include <gg/ytree.h>
#include <gg/hytxt.h>
#include <gg/lookup.h>
%}
TFB_HANDLE *new_TFB_HANDLE (char *INPUT, char *INPUT);
char *tfb_fetch_entry2 (TFB_HANDLE *INPUT, char *key);

HYX_CLUSTER_CONTROL *new_HYX_CLUSTER_CONTROL (char *fnm_hyx);

LMDQS *new_LMDQS (char *INPUT);
WRL *lmd_deref1 (LMDQS *INPUT, char *INPUT, int wl_min, int wl_max);
lmd_print_doc_hit_list_stdout (WRL *INPUT, int print_dil);
lmd_print_document_info_list_stdout (DIL *INPUT);
char *WRL_string (WRL *INPUT);
long WRL_index (WRL *INPUT);
long WRL_count (WRL *INPUT);
long WRL_docs (WRL *INPUT);
long WRL_offset (WRL *INPUT);
DIL *WRL_DIL (WRL *INPUT);

DIL *DIL_next (DIL *INPUT);
long DIL_document_id (DIL *INPUT);
long DIL_hit_count (DIL *INPUT);
long DIL_document_ptr (DIL *INPUT);
long DIL_pos (DIL *INPUT, int INPUT);

