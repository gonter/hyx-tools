/*
 *  FILE %ds/tcl/tcl_0009.c
 *
 *  TCL subroutine library
 *
 *  written:       1996-03-18
 *  latest update: 1996-03-18  8:07:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <tcl.h>
#include <gg/filename.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
struct XYZ
{
  Tcl_Interp *interp;
  char *cmd;
} ;

/* ------------------------------------------------------------------------ */
char *ggtcl_dirinf_generator (
char *dir_path,
void *client_data)
{
  struct XYZ *xyz;
  Tcl_Interp *interp;

  if ((xyz= (struct XYZ *) client_data) == (struct XYZ *) 0
      || (interp= xyz->interp) == (Tcl_Interp *) 0
      || xyz->cmd == (char *) 0
      || Tcl_VarEval (interp, xyz->cmd, " ", dir_path, (char *) 0) != TCL_OK
     ) return (char *) 0;

  return strdup (interp->result);  
}

/* ------------------------------------------------------------------------ */
int ggtcl_register_dirinf_generator (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  struct XYZ *xyz;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0
      || argc != 2
      || (xyz= (struct XYZ *) calloc (sizeof (struct XYZ), 1))
         == (struct XYZ *) 0
     )
    return TCL_ERROR;

  xyz->interp= interp;
  xyz->cmd= strdup (argv [1]);

  if (fvf_set_dirinf_callback (ggtcl_dirinf_generator, (void *) xyz) != 0)
    return TCL_ERROR;

  return TCL_OK;
}
