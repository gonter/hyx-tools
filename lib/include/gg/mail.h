/*
 *  include FILE <gg/mail.h>
 *
 *  see also: %ds/mime
 *
 *  written:       1996-02-23
 *  latest update: 1997-01-25 19:18:23
 *  $Id: mail.h,v 1.3 2002/01/29 19:21:10 gonter Exp $
 *
 */

#ifndef __GG_mail__
#define __GG_mail__

/* ------------------------------------------------------------------------ */
#define MIME_none               0
#define MIME_quoted_printable   1
#define MIME_base64             2
#define MIME_url_encoded        3

/* prototypes: ------------------------------------------------------------ */
int mime_convert_line (char *line, char *line2, int MAX_LINE, int mime_mode);
int mime_convert_url (char *line, char *line2, int MAX_LINE);
int mime_convert_xurl (char *line, char *line2, int MAX_LINE, int escape);

#endif /* __GG_mail__ */
