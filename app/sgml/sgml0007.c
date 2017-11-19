/*
 *  FILE ~/usr/sgml/sgml0007.c
 *
 *  written:       1990 09 28
 *  latest update: 1999-04-25 16:40:22
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/sgml.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
static struct SGML_VARIABLE *variable_list;

/* ------------------------------------------------------------------------ */
static struct SGML_INFO_BYTE *deref_ptr (void *ptr)
{
  struct SGML_INFO_BYTE *par;

  switch (((struct SGML_LIST *) ptr)->sig)
  {
    case SIG_LIST:
      par= ((struct SGML_LIST *) ptr)->car;
      if (par == (void *) 0
         || par->sig != SIG_PARAMETER)
        return (void *) 0;
      break;
    case SIG_PARAMETER:
      par=ptr;
      break;
    default: return (void *) 0;
  }
}

/* ------------------------------------------------------------------------ */
struct SGML_VARIABLE *sgml_get_variable (void *ptr)
{
  struct SGML_VARIABLE  *var;
  struct SGML_INFO_BYTE *par;

  par = deref_ptr (ptr);
  if (par == (void *) 0) return (void *) 0;

  for (var  = variable_list;
       var != (struct SGML_VARIABLE *) 0;
       var  = var->sgml_variable_next)
  {
    if (strcmp (((struct SGML_INFO_BYTE *) var->sgml_variable_name)->info,
                par->info) == 0)
       return var;
  }

  return (void *) 0;
}

/* ------------------------------------------------------------------------ */
struct SGML_INFO_BYTE *sgml_get_value (void *ptr)
{
  struct SGML_VARIABLE *var;

  var = sgml_get_variable (ptr);
  if (var == (void *) 0) return (void *) 0;
  return var->sgml_variable_value;
}

/* ------------------------------------------------------------------------ */
int sgml_test_variable (void *ptr)
{
  struct SGML_VARIABLE  *var;
  struct SGML_INFO_BYTE *par1, *par2;

  var = sgml_get_variable (ptr);
  if (var == (void *) 0) return 0;
  if ((par2=var->sgml_variable_value) == (void *) 0) return 0;

  if (((struct SGML_INFO_BYTE *) ptr)->sig
      == SIG_PARAMETER) return 1;
     /* ... nur variablen name angegeben? */
  if (((struct SGML_LIST *) ptr)->sig == SIG_LIST)
  {
    if (((struct SGML_LIST *) ptr)->cdr == (void *) 0) return 1;
       /* ... nur Test auf Vorhandensein der Variable   */
       /* das ist hiermit erfllt                       */

    par1= ((struct SGML_LIST *) ptr)->cdr->car;
    if (par1->sig != SIG_PARAMETER) return 0;
       /* ... der Parameter der Bedingung ist hier nicht interpretierbar */
    if (strcmp (par1->info, par2->info) == 0) return 1;
       /* ... der Parameter der Bedingung matcht mit dem Variablenwert  */
       /* dieser Test msste in Zukunft weiter ausgebaut werden! ###### */
  }
  return 0; /* ... kein match, oder Parameter nicht verst„ndlich. usw.  */
}

/* ------------------------------------------------------------------------ */
sgml_set_variable (void *ptr, int ptr_mode)
/* ptr_mode: 0 ... nichts                                                   */
/*           1 ... Pointer in der bergebenen Liste auf NIL setzen          */
/*           2 ... VAR & Value kopieren ###### NICHT IMPLEMENTIERT ######## */
{
  struct SGML_VARIABLE  *var;
  struct SGML_INFO_BYTE *val;

  if (((struct SGML_LIST *) ptr)->sig != SIG_LIST) return;
  var = sgml_get_variable (ptr);
  if (var == (void *) 0)
       {
         var = (struct SGML_VARIABLE *)
               calloc (sizeof (struct SGML_VARIABLE), 1);
         var->sgml_variable_next = variable_list;
         variable_list = var;
         var->sgml_variable_name = ((struct SGML_LIST *) ptr)->car;
         if (ptr_mode == 1) ((struct SGML_LIST *) ptr)->car = (void *) 0;
       }
  else {
         free_tag_list (var->sgml_variable_value);
       }

  if (((struct SGML_LIST *) ptr)->cdr == (void *) 0)
       {
         var->sgml_variable_value = (void *) 0;
       }
  else {
         var->sgml_variable_value = ((struct SGML_LIST *) ptr)->cdr->car;
         if (ptr_mode == 1) ((struct SGML_LIST *) ptr)->cdr->car = (void *) 0;
       }
}
