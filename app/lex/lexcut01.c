/*
 *  FILE /usr/lex/lexcut01.c
 *
 *  find the appropriate file extension for a given key.
 *
 *  written:       1993-07-06
 *  latest update: 1993-07-06
 *
 */

/* ------------------------------------------------------------------------ */
static char EXTENSION[20];

/* ------------------------------------------------------------------------ */
char *get_extension (char *key)
{
  int ch;
  int key_1;
  int ext_1;

  if (key == (char *) 0) return "_";
  ch= *key & 0x00FF;
  if (ch == (char) 0 || ch < 'a' || ch > 'z') return "_";

  EXTENSION [0]= key[0];
  EXTENSION [2]= 0;
  ext_1= 0;
  key_1= key[1];

  switch (key[0])
  {
    case 'a':
    case 'i':
    case 'u':
      if (key_1 == 'n') ext_1= key_1;
      break;

    case 'b':
    case 'm':
      if (key_1 == 'a') ext_1= key_1;
      break;

    case 'r':
      if (key_1 == 'e') ext_1= key_1;
      break;

    case 's':
      switch (key_1)
      {
        case 't':
        case 'u':
        case 'e':
          ext_1= key_1;
          break;
      }
      break;

    case 't':
      if (key_1 == 'r') ext_1= key_1;
      break;

    case 'p':
      switch (key_1)
      {
        case 'r':
        case 'a':
          ext_1= key_1;
          break;
      }
      break;

    case 'd':
      switch (key_1)
      {
        case 'i':
        case 'e':
          ext_1= key_1;
          break;
      }
      break;

    case 'c':
      switch (key_1)
      {
        case 'o':
        case 'a':
          ext_1= key_1;
          break;
      }
      break;
  }
  EXTENSION [1]= (char) ext_1;

  return EXTENSION;
}
