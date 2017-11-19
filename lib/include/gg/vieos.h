/*
 *  include FILE <gg/vieos.h>
 *
 *  Vienna Objective SGML
 *  see also: VIEOS, TCL HYX SGML objects
 *
 *  written:       1995-12-14
 *  latest update: 1997-01-15 11:27:03
 *
 */

#ifndef __GG_hyxtcl__
#define __GG_hyxtcl__

/* #include <tcl.h> */
#include <gg/floskel.h>
#include <gg/signatur.h>
#include <gg/dyb.h>
#include <gg/hytxt.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
typedef int VIEOS_DESTRUCTOR (ClientData object);

/* ------------------------------------------------------------------------ */
struct VIEOS_GENERIC                    /* common structural elements       */
{                                       /* for all objects                  */
  long VIEG_signature;                  /* any signature of SIG_VIEOS_*     */
  char *VIEG_name;                      /* the name of the object           */
  Tcl_Interp *VIEG_interp;
  void *VIEG_context;                   /* pointer back to the creating     */
                                        /* context                          */
} ;

/* ------------------------------------------------------------------------ */
struct VIEOS_MARKUP
{
  long VIEM_signature;                  /* SIG_VIEOS_MARKUP                 */
  char *VIEM_name;
  Tcl_Interp *VIEM_interp;
  void *VIEM_context;                   /* pointer back to the creating     */
                                        /* context                          */

  struct TEXT_ELEMENT *VIEM_te;
} ;

/* ------------------------------------------------------------------------ */
struct VIEOS_INDEX
{
  long VIEI_signature;                  /* SIG_VIEOS_INDEX                  */
  char *VIEI_name;
  Tcl_Interp *VIEI_interp;
  void *VIEI_context;                   /* pointer back to the creating     */
                                        /* context                          */

  struct LMDC_CONTROL *VIEI_lmdc;
} ;

/* ------------------------------------------------------------------------ */
struct VIEOS_BLOCK                      /* common structural elements       */
{                                       /* for all objects                  */
  long VIEB_signature;                  /* SIG_VIEOS_BLOCK                  */
  char *VIEB_name;                      /* the name of the object           */
  Tcl_Interp *VIEB_interp;
  void *VIEB_context;                   /* pointer back to the creating     */
                                        /* context                          */

  struct DYNAMIC_BLOCK *VIEB_dyb;
} ;

/* ------------------------------------------------------------------------ */
struct VIEOS_CLUSTER                    /* common structural elements       */
{                                       /* for all objects                  */
  long VCL_signature;                   /* SIG_VIEOS_CLUSTER                */
  char *VCL_name;                       /* the name of the object           */
  Tcl_Interp *VCL_interp;
  void *VCL_context;                    /* pointer back to the creating     */
                                        /* context                          */

  struct HYX_CLUSTER_CONTROL *VCL_hcc;
} ;

/* ------------------------------------------------------------------------ */
struct VIEOS_CONTEXT
{
  long VC_signature;                    /* SIG_VIEOS_CONTEXT                */
  char *VC_name;
  Tcl_Interp *VC_interp;
  void *VC_context;                     /* pointer back to the creating     */
                                        /* context                          */

                                        /* list of ... objects              */
  struct YTREE *VC_SUB_CONTEXT;         /* ... subordinate context          */
  struct YTREE *VC_INDEX;               /* ... index                        */
  struct YTREE *VC_MARKUP;              /* ... markup                       */
  struct YTREE *VC_BLOCK;               /* ... named block                  */
  struct YTREE *VC_CLUSTER;             /* ... cluster                      */
  struct YTREE *VC_GENERIC;             /* ... generic (template)           */
} ;

/* prototypes: ------------------------------------------------------------ */
/* vieos001.c */ struct VIEOS_CONTEXT *vieos_create_context (
                   Tcl_Interp *interp, struct VIEOS_CONTEXT *vc, char *nm);
/* vieos002.c */ int vieos_context_object (ClientData clientData,
                   Tcl_Interp *interp, int argc, char *argv []);
/* vieos003.c */ void vieos_destroy_context (ClientData clientData);

/* vieos101.c */ struct VIEOS_MARKUP *vieos_create_markup (
                   Tcl_Interp *interp, struct VIEOS_CONTEXT *vc, char *nm);
/* vieos102.c */ int vieos_markup_object (ClientData clientData,
                   Tcl_Interp *interp, int argc, char *argv []);
/* vieos103.c */ void vieos_destroy_markup (ClientData clientData);

/* vieos201.c */ struct VIEOS_INDEX *vieos_create_index (
                   Tcl_Interp *interp, struct VIEOS_CONTEXT *vc, char *nm);
/* vieos202.c */ int vieos_index_object (ClientData clientData,
                   Tcl_Interp *interp, int argc, char *argv []);
/* vieos203.c */ void vieos_destroy_index (ClientData clientData);

/* vieos301.c */ struct VIEOS_BLOCK *vieos_create_block (
                   Tcl_Interp *interp, struct VIEOS_CONTEXT *vc, char *nm);
/* vieos302.c */ int vieos_block_object (ClientData clientData,
                   Tcl_Interp *interp, int argc, char *argv []);
/* vieos303.c */ void vieos_destroy_block (ClientData clientData);

/* vieos401.c */ struct VIEOS_CLUSTER *vieos_create_cluster (
                   Tcl_Interp *interp, struct VIEOS_CONTEXT *vc, char *nm);
/* vieos402.c */ int vieos_cluster_object (ClientData clientData,
                   Tcl_Interp *interp, int argc, char *argv []);
/* vieos403.c */ void vieos_destroy_cluster (ClientData clientData);

/* vieosg01.c */ struct VIEOS_GENERIC *vieos_create_generic (
                   Tcl_Interp *interp, struct VIEOS_CONTEXT *vc, char *nm);
/* vieosg02.c */ int vieos_generic_object (ClientData clientData,
                   Tcl_Interp *interp, int argc, char *argv []);
/* vieosg03.c */ void vieos_destroy_generic (ClientData clientData);
/* vieosg04.c */ int vieos_destructor_generic (struct YTREE *yt, void *cd);

#endif /* __GG_hyxtcl__ */
