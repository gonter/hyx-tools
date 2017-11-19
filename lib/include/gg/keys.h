/*
 *  include FILE <gg/keys.h>
 *
 *  Tastencodes (lt. kbin) fuer PC-Funktionstasten
 *
 *  written:       1986-07-20
 *  latest update: 1995-12-16
 *
 */

#ifndef __GG_keys__
#define __GG_keys__

#include <gg/floskel.h>

#define K_CUP           0x0148  /* Cursorblock         */
#define K_CDOWN         0x0150
#define K_CLEFT         0x014B
#define K_CRIGHT        0x014D
#define K_DEL           0x0153
#define K_INS           0x0152
#define K_END           0x014F
#define K_HOME          0x0147
#define K_PGUP          0x0149
#define K_PGDN          0x0151

#define K_CTRLPRTSCR    0x0172
#define K_CTRLLEFT      0x0173
#define K_CTRLRIGHT     0x0174
#define K_CTRLEND       0x0175
#define K_CTRLHOME      0x0177
#define K_CPGDN         0x0176  /* Ctrl-PGDN    */
#define K_CTRLPGDN      0x0176
#define K_CPGUP         0x0184  /* Ctrl-PGUP    */
#define K_CTRLPGUP      0x0184

#define K_PF1           0x013B  /* Funktions Tasten    */
#define K_PF2           0x013C
#define K_PF3           0x013D
#define K_PF4           0x013E
#define K_PF5           0x013F
#define K_PF6           0x0140
#define K_PF7           0x0141
#define K_PF8           0x0142
#define K_PF9           0x0143
#define K_PF10          0x0144
#define K_SPF1          0x0154  /* Shift-PF1    */
#define K_SPF2          0x0155
#define K_SPF3          0x0156
#define K_SPF4          0x0157
#define K_SPF5          0x0158
#define K_SPF6          0x0159
#define K_SPF7          0x015A
#define K_SPF8          0x015B
#define K_SPF9          0x015C
#define K_SPF10         0x015D
#define K_CPF1          0x015E  /* Ctrl-PF1     */
#define K_CPF2          0x015F
#define K_CPF3          0x0160
#define K_CPF4          0x0161
#define K_CPF5          0x0162
#define K_CPF6          0x0163
#define K_CPF7          0x0164
#define K_CPF8          0x0165
#define K_CPF9          0x0166
#define K_CPF10         0x0167
#define K_APF1          0x0168  /* Alt-PF1      */
#define K_APF2          0x0169
#define K_APF3          0x016A
#define K_APF4          0x016B
#define K_APF5          0x016C
#define K_APF6          0x016D
#define K_APF7          0x016E
#define K_APF8          0x016F
#define K_APF9          0x0170
#define K_APF10         0x0171

#define K_PF11          0x0185  /* Extended Funktion Keys */
#define K_PF12          0x0186
#define K_SPF11         0x0187
#define K_SPF12         0x0188
#define K_CPF11         0x0189
#define K_CPF12         0x018A
#define K_APF11         0x018B
#define K_APF12         0x018C

#define K_ALT_A         0x011E
#define K_ALT_B         0x0130
#define K_ALT_C         0x012E
#define K_ALT_D         0x0120
#define K_ALT_E         0x0112
#define K_ALT_F         0x0121
#define K_ALT_G         0x0122
#define K_ALT_H         0x0123
#define K_ALT_I         0x0117
#define K_ALT_J         0x0124
#define K_ALT_K         0x0125
#define K_ALT_L         0x0126
#define K_ALT_M         0x0132
#define K_ALT_N         0x0131
#define K_ALT_O         0x0118
#define K_ALT_P         0x0119
#define K_ALT_Q         0x0110
#define K_ALT_R         0x0113
#define K_ALT_S         0x011F
#define K_ALT_T         0x0114
#define K_ALT_U         0x0116
#define K_ALT_V         0x012F
#define K_ALT_W         0x0111
#define K_ALT_X         0x012D
#define K_ALT_Y         0x0115
#define K_ALT_Z         0x012C
#define K_ALT_1         0x0178
#define K_ALT_2         0x0179
#define K_ALT_3         0x017A
#define K_ALT_4         0x017B
#define K_ALT_5         0x017C
#define K_ALT_6         0x017D
#define K_ALT_7         0x017E
#define K_ALT_8         0x017F
#define K_ALT_9         0x0180
#define K_ALT_0         0x0181
#define K_ALT_MINUS     0x0182
#define K_ALT_GLEICH    0x0183

#define K_ALT_CDOWN     0x01A0  /* ALT + Cursor Down    */
#define K_ALT_CUP       0x0198
#define K_ALT_CLEFT     0x019B
#define K_ALT_CRIGHT    0x019D

#define K_CTRL_CUP      0x018D  /* Ctrl + Cursor Down   */
#define K_CTRL_CDOWN    0x0191
#define K_CTRL_CLEFT    0x0173
#define K_CTRL_CRIGHT   0x0174

/* Tastencodes fuer Shift Keys (Funktion kbshift) ------------------------- */
#define K_SHIFT_LEFT    0x0001
#define K_SHIFT_RIGHT   0x0002
#define K_SHIFT         0x0003
#define K_CTRL          0x0004
#define K_ALT           0x0008
#define K_SCROLL_LOCK   0x0010        /* Scroll Lock aktiviert              */
#define K_NUM_LOCK      0x0020        /* Num Lock aktiviert                 */
#define K_CAPS_LOCK     0x0040        /* Caps Lock aktiviert                */
#define K_CTRL_LEFT     0x0100
#define K_ALT_LEFT      0x0200
#define K_CTRL_RIGHT    0x0400
#define K_ALT_RIGHT     0x0800
#define K_H_SCROLL_LOCK 0x1000        /* Scroll Lock Key gerade gedrueckt   */
#define K_H_NUM_LOCK    0x2000        /* Num Lock Key gerade gedrueckt      */
#define K_H_CAPS_LOCK   0x4000        /* Caps Lock Key gerade gedrueckt     */

/* Function Prototypes KEYBOARD.ARC --------------------------------------- */
int  cdecl kbin         (void);
void cdecl kbin_set_AT  (void);
int  cdecl kbhit        (void);
void cdecl kbhit_set_AT (void);
int  cdecl kbshift      (void);
void cdecl kbclick      (int);
int  cdecl kbqueue      (int key);
int  cdecl kbtype       (void);
void cdecl kbnumoff     (void);
void cdecl kbnumon      (void);
void cdecl kbmfon       (void);

/* Modul c:/usr/sbr/identkey.c -------------------------------------------- */
unsigned int cdecl identify_key (char *key_name);

/* Modul c:/usr/sbr/keynames.c -------------------------------------------- */
char *cdecl key_name (unsigned int kc);                 /* Key Code         */

#endif /* __GG_keys__ */
