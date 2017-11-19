/*
 *  File c:/usr/sbr/keynames.c
 *
 *  1991 09 30
 *
 */

#include <stdio.h>
#include <gg/keys.h>

static char TMP[10];

/* ------------------------------------------------------------------------ */
char *key_name (unsigned int kc)                    /* Key Code */
{
       if (kc >= K_PF1  && kc <= K_PF10)
          sprintf (TMP, "F%d", (kc-K_PF1 + 1));
  else if (kc >= K_SPF1 && kc <= K_SPF10)
          sprintf (TMP, "SF%d", (kc-K_SPF1 + 1));
  else if (kc >= K_APF1 && kc <= K_APF10)
          sprintf (TMP, "AF%d", (kc-K_APF1 + 1));
  else if (kc >= K_CPF1 && kc <= K_CPF10)
          sprintf (TMP, "CF%d", (kc-K_CPF1 + 1));
  else if (kc >= 0x21   && kc <= 0x7E)
          sprintf (TMP, "%c", kc);
  else if (kc >= 0x01   && kc <= 0x1A)
          sprintf (TMP, "^%c", kc+'A'-1);
  else {
         switch (kc)
         {
           case K_CUP:            return "CUP";
           case K_CDOWN:          return "CDN";
           case K_CLEFT:          return "CLT";
           case K_CRIGHT:         return "CRT";
           case K_DEL:            return "DEL";
           case K_INS:            return "INS";
           case K_END:            return "END";
           case K_HOME:           return "HOME";
           case K_PGUP:           return "PGUP";
           case K_PGDN:           return "PGDN";
           case 0x1B:             return "ESC";
           case 0x20:             return "BLNK";
           case 0x0D:             return "CR";
           case K_CTRLLEFT:       return "^CLT";
           case K_CTRLRIGHT:      return "^CRT";
           case K_CTRLEND:        return "^END";
           case K_CTRLHOME:       return "^HOM";
           case K_CTRLPGUP:       return "^PUP";
           case K_CTRLPGDN:       return "^PDN";
           case K_CTRLPRTSCR:     return "^PSC";
           case K_PF11:           return "F11";
           case K_PF12:           return "F12";
           case K_SPF11:          return "SF11";
           case K_SPF12:          return "SF12";
           case K_CPF11:          return "CF11";
           case K_CPF12:          return "CF12";
           case K_APF11:          return "AF11";
           case K_APF12:          return "AF12";
           default: sprintf (TMP, "0x%04X", kc);
         }
       }

  return TMP;
}
