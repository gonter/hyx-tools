/*
 *  FILE %ds/vieos/vieos103.c
 *
 *  destroy a markup object and all it's associated memory
 *
 *  written:       1995-03-19
 *  latest update: 1997-01-15 11:27:36
 *
 */

#include <stdlib.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/parse.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
void vieos_destroy_markup (ClientData clientData)
{
  struct VIEOS_MARKUP *vm;

  if ((vm= (struct VIEOS_MARKUP *) clientData) != (struct VIEOS_MARKUP *) 0
      && vm->VIEM_signature == SIG_VIEOS_MARKUP
     )
  {
    hyx_frtx_elem_list (vm->VIEM_te);
    free_or_what (vm->VIEM_name);
    free (vm);
  }
}
