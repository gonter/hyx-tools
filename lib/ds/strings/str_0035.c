/*
 *  FILE %ds/strings/str_0035.c
 *
 *  decompose a gopher URL into its components
 *
 *  written:       1994-09-08
 *  latest update: 1996-10-29 16:10:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int gopher_url2components (
char *url,
char **host,
long *port,
int *type,
char **path,
int *tabs)
{
  char *cp;
  char *xport;
  int ch;
  long port_number;
  int tab_count;

  if (strncmp (url, "gopher://", 9) != 0) return -1;

  /* scanning over host name */
  *host= url+9;
  for (cp= *host; ch= *cp; cp++)
  {
    if (ch == 0) goto DONE;
    if (ch == ':')
    {
      *cp++= 0;
      xport= cp;
      break;
    }
    if (ch == '/')
    {
      *cp++= 0;
      goto GET_PATH;
    }
  }

  /* reading port number */
  port_number= 0L;
  for (; ch= *cp; cp++)
  {
    if (ch == 0)
    {
      *cp= 0;
      goto DONE;
    }
    if (ch == '/')
    {
      *cp++= 0;
      break;
    }

    if (ch >= '0' && ch <= '9')
      port_number= 10L*port_number + ((long) (ch - '0'));
    else
    {
ERROR_PORT:
      return -1;
    }
  }
  if (port_number <= 0L || port_number >= 0x00010000L) goto ERROR_PORT;
  *port= port_number;

GET_PATH:
  ch= *cp++;
  if (ch != 0)
  {
    *type= ch;
    ch= *cp;
    if (ch != 0) *path= cp;
  }

  /* cp now points to the first byte of the path string */

  /* analyze the request string only if we're doing cache stuff... */
  tab_count= 0;
  for (; ch= *cp; cp++)
  {
    if (ch == 0) break;               /* just a plain gopher request      */
    if (ch == '\t') tab_count++;      /* oh, oh...  gopher plus?          */
  }
  *tabs= tab_count;

DONE:
  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef DEBUG
#include <stdio.h>
#define LINE_SIZE 1024
static char url [LINE_SIZE];

int main (void);

int main ()
{
  int rc;
  char *host;
  long port;
  int gtype;
  char *path;
  int tabs;

  for (;;)
  {
    printf ("url: ");
    scanf ("%s", url);

    host= "host.do.main";
    port= 70;
    gtype= '1';
    path= "";
    tabs= 0;

    rc= gopher_url2components (url, &host, &port, &gtype, &path, &tabs);

    printf ("rc=%d\n", rc);
    printf ("host=%s\n", host);
    printf ("port=%ld\n", port);
    printf ("type=%c\n", gtype);
    printf ("path=%s\n", path);
    printf ("tabs=%d\n", tabs);
  }

  return 0;
}
#endif /* DEBUG */
