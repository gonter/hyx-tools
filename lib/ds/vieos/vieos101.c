/*
 *  FILE %ds/vieos/vieos101.c
 *
 *  call evaluation of a TCL script
 *
 *  written:       1995-03-19
 *  latest update: 1997-01-15 11:27:56
 *
 */

#include <stdlib.h>
#include <string.h>
#include <tcl.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
struct VIEOS_MARKUP *vieos_create_markup (
Tcl_Interp *interp,
struct VIEOS_CONTEXT *vc,
char *nm)
{
  struct VIEOS_MARKUP *vm;

  if ((vm= (struct VIEOS_MARKUP *)
            calloc (sizeof (struct VIEOS_MARKUP), 1))
      != (struct VIEOS_MARKUP *) 0)
  {
    vm->VIEM_name= strdup (nm);
    vm->VIEM_signature= SIG_VIEOS_MARKUP;
    vm->VIEM_interp= interp;
    vm->VIEM_context= vc;

    Tcl_CreateCommand (interp, nm,
                       vieos_markup_object,
                       (ClientData) vm,
                       vieos_destroy_markup);

    if (vc != (struct VIEOS_CONTEXT *) 0)
      ytree_set_value (&vc->VC_MARKUP, (unsigned char *) nm, (long) vm);
  }

  return vm;
}
