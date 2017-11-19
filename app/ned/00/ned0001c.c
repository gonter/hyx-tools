/*
 *  FILE %ned/00/ned0001c.c
 *
 *  jump table for editor NED: 
 *  group c: curses keypad codes (256!)
 *
 *  written:       1994-12-25
 *  latest update: 2001-02-12  0:50:06
 *  $Id: ned0001c.c,v 1.2 2001/02/12 00:03:14 gonter Exp $
 *
 */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/* 00 */  xx,          /* 0400 KEY_0000: */
/* 01 */  xx,          /* 0401 KEY_BREAK: break key (unreliable) */
/* 02 */  ned_cursor_down,      /* 0402 KEY_DOWN: The four arrow keys ... */
/* 03 */  ned_cursor_up,        /* 0403 KEY_UP: */
/* 04 */  ned_cursor_left,      /* 0404 KEY_LEFT: */
/* 05 */  ned_cursor_right,     /* 0405 KEY_RIGHT: ... */
/* 06 */  ned_jmp_boln,/* 0406 KEY_HOME: Home key (upward+left arrow) */
/* 07 */  ned_del_char_left,    /* 0407 KEY_BACKSPACE: (unreliable)         */
/* 08 */  xx,          /* 0410 KEY_F0: Function keys. Space for 64 */
/* 09 */  xx,          /* 0411 KEY_F1:  F1  */
/* 0A */  xx,          /* 0411 KEY_F2:  F2  */
/* 0B */  xx,          /* 0411 KEY_F3:  F3  */
/* 0C */  xx,          /* 0411 KEY_F4:  F4  */
/* 0D */  xx,          /* 0411 KEY_F5:  F5  */
/* 0E */  xx,          /* 0411 KEY_F6:  F6  */
/* 0F */  xx,          /* 0411 KEY_F7:  F7  */
/* 10 */  p_ssave,              /* 0411 KEY_F8:  F8  */
/* 11 */  ned_set_lookup_tag,   /* 0411 KEY_F9:  F9  */
/* 12 */  p_activate_cl1,       /* 0411 KEY_F10: F10 */
/* 13 */  xx,          /* 0411 KEY_F11: F11 */
/* 14 */  xx,          /* 0411 KEY_F12: F12 */
/* 15 */  xx,          /* 0411 KEY_F13: F13 */
/* 16 */  xx,          /* 0411 KEY_F14: F14 */
/* 17 */  xx,          /* 0411 KEY_F15: F15 */
/* 18 */  xx,          /* 0411 KEY_F16: F16 */
/* 19 */  xx,          /* 0411 KEY_F17: F17 */
/* 1A */  xx,          /* 0411 KEY_F18: F18 */
/* 1B */  xx,          /* 0411 KEY_F19: F19 */
/* 1C */  xx,          /* 0411 KEY_F20: F20 */
/* 1D */  xx,          /* 0411 KEY_F21: F21 */
/* 1E */  xx,          /* 0411 KEY_F22: F22 */
/* 1F */  xx,          /* 0411 KEY_F23: F23 */
/* 20 */  xx,          /* 0411 KEY_F24: F24 */
/* 21 */  xx,          /* 0411 KEY_F25: F25 */
/* 22 */  xx,          /* 0411 KEY_F26: F26 */
/* 23 */  xx,          /* 0411 KEY_F27: F27 */
/* 24 */  xx,          /* 0411 KEY_F28: F28 */
/* 25 */  xx,          /* 0411 KEY_F29: F29 */
/* 26 */  xx,          /* 0411 KEY_F30: F30 */
/* 27 */  xx,          /* 0411 KEY_F31: F31 */
/* 28 */  xx,          /* 0411 KEY_F32: F32 */
/* 29 */  xx,          /* 0411 KEY_F33: F33 */
/* 2A */  xx,          /* 0411 KEY_F34: F34 */
/* 2B */  xx,          /* 0411 KEY_F35: F35 */
/* 2C */  xx,          /* 0411 KEY_F36: F36 */
/* 2D */  xx,          /* 0411 KEY_F37: F37 */
/* 2E */  xx,          /* 0411 KEY_F38: F38 */
/* 2F */  xx,          /* 0411 KEY_F39: F39 */
/* 30 */  xx,          /* 0411 KEY_F40: F40 */
/* 31 */  xx,          /* 0411 KEY_F41: F41 */
/* 32 */  xx,          /* 0411 KEY_F42: F42 */
/* 33 */  xx,          /* 0411 KEY_F43: F43 */
/* 34 */  xx,          /* 0411 KEY_F44: F44 */
/* 35 */  xx,          /* 0411 KEY_F45: F45 */
/* 36 */  xx,          /* 0411 KEY_F46: F46 */
/* 37 */  xx,          /* 0411 KEY_F47: F47 */
/* 38 */  xx,          /* 0411 KEY_F48: F48 */
/* 39 */  xx,          /* 0411 KEY_F49: F49 */
/* 3A */  xx,          /* 0411 KEY_F50: F50 */
/* 3B */  xx,          /* 0411 KEY_F51: F51 */
/* 3C */  xx,          /* 0411 KEY_F52: F52 */
/* 3D */  xx,          /* 0411 KEY_F53: F53 */
/* 3E */  xx,          /* 0411 KEY_F54: F54 */
/* 3F */  xx,          /* 0411 KEY_F55: F55 */
/* 40 */  xx,          /* 0411 KEY_F56: F56 */
/* 41 */  xx,          /* 0411 KEY_F57: F57 */
/* 42 */  xx,          /* 0411 KEY_F58: F58 */
/* 43 */  xx,          /* 0411 KEY_F59: F59 */
/* 44 */  xx,          /* 0411 KEY_F60: F60 */
/* 45 */  xx,          /* 0411 KEY_F61: F61 */
/* 46 */  xx,          /* 0411 KEY_F62: F62 */
/* 47 */  xx,          /* 0411 KEY_F63: F63 */
/* 48 */  xx,          /* 0510 KEY_DL: Delete line */
/* 49 */  xx,          /* 0511 KEY_IL: Insert line */
/* 4A */  ned_del_char_right,   /* 0512 KEY_DC: Delete character            */
/* 4B */  p_ovins,     /* 0513 KEY_IC: Insert char or enter insert mode */
/* 4C */  xx,          /* 0514 KEY_EIC: Exit insert char mode */
/* 4D */  xx,          /* 0515 KEY_CLEAR: Clear screen */
/* 4E */  xx,          /* 0516 KEY_EOS: Clear to end of screen */
/* 4F */  xx,          /* 0517 KEY_EOL: Clear to end of line */
/* 50 */  xx,          /* 0520 KEY_SF: Scroll 1 line forward */
/* 51 */  xx,          /* 0521 KEY_SR: Scroll 1 line backwards (reverse) */
/* 52 */  ned_page_down, /* 0522 KEY_NPAGE: Next page */
/* 53 */  ned_page_up, /* 0523 KEY_PPAGE: Previous page */
/* 54 */  xx,          /* 0524 KEY_STAB: Set tab */
/* 55 */  xx,          /* 0525 KEY_CTAB: Clear tab */
/* 56 */  xx,          /* 0526 KEY_CATAB: Clear all tabs */
/* 57 */  xx,          /* 0527 KEY_ENTER: Enter or send (unreliable) */
/* 58 */  xx,          /* 0530 KEY_SRESET: soft (partial) reset (unreliable) */
/* 59 */  xx,          /* 0531 KEY_RESET: reset or hard reset (unreliable) */
/* 5A */  xx,          /* 0532 KEY_PRINT: print or copy */
/* 5B */  xx,          /* 0533 KEY_LL: home down or bottom (lower left) */
/* 5C */  xx,          /* 0534 KEY_A1: Upper left of keypad */
/* 5D */  xx,          /* 0535 KEY_A3: Upper right of keypad */
/* 5E */  xx,          /* 0536 KEY_B2: Center of keypad */
/* 5F */  xx,          /* 0537 KEY_C1: Lower left of keypad */
/* 60 */  xx,          /* 0540 KEY_C3: Lower right of keypad */
/* 61 */  xx,          /* 0541 KEY_BTAB: Back tab key */
/* 62 */  xx,          /* 0542 KEY_BEG: beg(inning) key */
/* 63 */  xx,          /* 0543 KEY_CANCEL: cancel key */
/* 64 */  xx,          /* 0544 KEY_CLOSE: close key */
/* 65 */  xx,          /* 0545 KEY_COMMAND: cmd (command) key */
/* 66 */  xx,          /* 0546 KEY_COPY: copy key */
/* 67 */  xx,          /* 0547 KEY_CREATE: create key */
/* 68 */  ned_jmp_eoln,/* 0550 KEY_END: end key */
/* 69 */  xx,          /* 0551 KEY_EXIT: exit key */
/* 6A */  xx,          /* 0552 KEY_FIND: find key */
/* 6B */  xx,          /* 0553 KEY_HELP: help key */
/* 6C */  xx,          /* 0554 KEY_MARK: mark key */
/* 6D */  xx,          /* 0555 KEY_MESSAGE: message key */
/* 6E */  xx,          /* 0556 KEY_MOVE: move key */
/* 6F */  xx,          /* 0557 KEY_NEXT: next object key */
/* 70 */  xx,          /* 0560 KEY_OPEN: open key */
/* 71 */  xx,          /* 0561 KEY_OPTIONS: options key */
/* 72 */  xx,          /* 0562 KEY_PREVIOUS: previous object key */
/* 73 */  xx,          /* 0563 KEY_REDO: redo key */
/* 74 */  xx,          /* 0564 KEY_REFERENCE: ref(erence) key */
/* 75 */  xx,          /* 0565 KEY_REFRESH: refresh key */
/* 76 */  xx,          /* 0566 KEY_REPLACE: replace key */
/* 77 */  xx,          /* 0567 KEY_RESTART: restart key */
/* 78 */  xx,          /* 0570 KEY_RESUME: resume key */
/* 79 */  xx,          /* 0571 KEY_SAVE: save key */
/* 7A */  xx,          /* 0572 KEY_SBEG: shifted beginning key */
/* 7B */  xx,          /* 0573 KEY_SCANCEL: shifted cancel key */
/* 7C */  xx,          /* 0574 KEY_SCOMMAND: shifted command key */
/* 7D */  xx,          /* 0575 KEY_SCOPY: shifted copy key */
/* 7E */  xx,          /* 0576 KEY_SCREATE: shifted create key */
/* 7F */  xx,          /* 0577 KEY_SDC: shifted delete char key */
/* 80 */  xx,          /* 0600 KEY_SDL: shifted delete line key */
/* 81 */  xx,          /* 0601 KEY_SELECT: select key */
/* 82 */  xx,          /* 0602 KEY_SEND: shifted end key */
/* 83 */  xx,          /* 0603 KEY_SEOL: shifted clear line key */
/* 84 */  xx,          /* 0604 KEY_SEXIT: shifted exit key */
/* 85 */  xx,          /* 0605 KEY_SFIND: shifted find key */
/* 86 */  xx,          /* 0606 KEY_SHELP: shifted help key */
/* 87 */  xx,          /* 0607 KEY_SHOME: shifted home key */
/* 88 */  xx,          /* 0610 KEY_SIC: shifted input key */
/* 89 */  xx,          /* 0611 KEY_SLEFT: shifted left arrow key */
/* 8A */  xx,          /* 0612 KEY_SMESSAGE: shifted message key */
/* 8B */  xx,          /* 0613 KEY_SMOVE: shifted move key */
/* 8C */  xx,          /* 0614 KEY_SNEXT: shifted next key */
/* 8D */  xx,          /* 0615 KEY_SOPTIONS: shifted options key */
/* 8E */  xx,          /* 0616 KEY_SPREVIOUS: shifted prev key */
/* 8F */  xx,          /* 0617 KEY_SPRINT: shifted print key */
/* 90 */  xx,          /* 0620 KEY_SREDO: shifted redo key */
/* 91 */  xx,          /* 0621 KEY_SREPLACE: shifted replace key */
/* 92 */  xx,          /* 0622 KEY_SRIGHT: shifted right arrow */
/* 93 */  xx,          /* 0623 KEY_SRSUME: shifted resume key */
/* 94 */  xx,          /* 0624 KEY_SSAVE: shifted save key */
/* 95 */  xx,          /* 0625 KEY_SSUSPEND: shifted suspend key */
/* 96 */  xx,          /* 0626 KEY_SUNDO: shifted undo key */
/* 97 */  xx,          /* 0627 KEY_SUSPEND: suspend key */
/* 98 */  xx,          /* 0630 KEY_UNDO: undo key */
/* 99 */  xx,          /* 0631 KEY_UNKN: */
/* 9A */  xx,          /* 0631 KEY_UNKN: */
/* 9B */  xx,          /* 0631 KEY_UNKN: */
/* 9C */  xx,          /* 0631 KEY_UNKN: */
/* 9D */  xx,          /* 0631 KEY_UNKN: */
/* 9E */  xx,          /* 0631 KEY_UNKN: */
/* 9F */  xx,          /* 0631 KEY_UNKN: */
/* A0 */  xx,          /* 0631 KEY_UNKN: */
/* A1 */  xx,          /* 0631 KEY_UNKN: */
/* A2 */  xx,          /* 0631 KEY_UNKN: */
/* A3 */  xx,          /* 0631 KEY_UNKN: */
/* A4 */  xx,          /* 0631 KEY_UNKN: */
/* A5 */  xx,          /* 0631 KEY_UNKN: */
/* A6 */  xx,          /* 0631 KEY_UNKN: */
/* A7 */  xx,          /* 0631 KEY_UNKN: */
/* A8 */  xx,          /* 0631 KEY_UNKN: */
/* A9 */  xx,          /* 0631 KEY_UNKN: */
/* AA */  xx,          /* 0631 KEY_UNKN: */
/* AB */  xx,          /* 0631 KEY_UNKN: */
/* AC */  xx,          /* 0631 KEY_UNKN: */
/* AD */  xx,          /* 0631 KEY_UNKN: */
/* AE */  xx,          /* 0631 KEY_UNKN: */
/* AF */  xx,          /* 0631 KEY_UNKN: */
/* B0 */  xx,          /* 0631 KEY_UNKN: */
/* B1 */  xx,          /* 0631 KEY_UNKN: */
/* B2 */  xx,          /* 0631 KEY_UNKN: */
/* B3 */  xx,          /* 0631 KEY_UNKN: */
/* B4 */  xx,          /* 0631 KEY_UNKN: */
/* B5 */  xx,          /* 0631 KEY_UNKN: */
/* B6 */  xx,          /* 0631 KEY_UNKN: */
/* B7 */  xx,          /* 0631 KEY_UNKN: */
/* B8 */  xx,          /* 0631 KEY_UNKN: */
/* B9 */  xx,          /* 0631 KEY_UNKN: */
/* BA */  xx,          /* 0631 KEY_UNKN: */
/* BB */  xx,          /* 0631 KEY_UNKN: */
/* BC */  xx,          /* 0631 KEY_UNKN: */
/* BD */  xx,          /* 0631 KEY_UNKN: */
/* BE */  xx,          /* 0631 KEY_UNKN: */
/* BF */  xx,          /* 0631 KEY_UNKN: */
/* C0 */  xx,          /* 0631 KEY_UNKN: */
/* C1 */  xx,          /* 0631 KEY_UNKN: */
/* C2 */  xx,          /* 0631 KEY_UNKN: */
/* C3 */  xx,          /* 0631 KEY_UNKN: */
/* C4 */  xx,          /* 0631 KEY_UNKN: */
/* C5 */  xx,          /* 0631 KEY_UNKN: */
/* C6 */  xx,          /* 0631 KEY_UNKN: */
/* C7 */  xx,          /* 0631 KEY_UNKN: */
/* C8 */  xx,          /* 0631 KEY_UNKN: */
/* C9 */  xx,          /* 0631 KEY_UNKN: */
/* CA */  xx,          /* 0631 KEY_UNKN: */
/* CB */  xx,          /* 0631 KEY_UNKN: */
/* CC */  xx,          /* 0631 KEY_UNKN: */
/* CD */  xx,          /* 0631 KEY_UNKN: */
/* CE */  xx,          /* 0631 KEY_UNKN: */
/* CF */  xx,          /* 0631 KEY_UNKN: */
/* D0 */  xx,          /* 0631 KEY_UNKN: */
/* D1 */  xx,          /* 0631 KEY_UNKN: */
/* D2 */  xx,          /* 0631 KEY_UNKN: */
/* D3 */  xx,          /* 0631 KEY_UNKN: */
/* D4 */  xx,          /* 0631 KEY_UNKN: */
/* D5 */  xx,          /* 0631 KEY_UNKN: */
/* D6 */  xx,          /* 0631 KEY_UNKN: */
/* D7 */  xx,          /* 0631 KEY_UNKN: */
/* D8 */  xx,          /* 0631 KEY_UNKN: */
/* D9 */  xx,          /* 0631 KEY_UNKN: */
/* DA */  xx,          /* 0631 KEY_UNKN: */
/* DB */  xx,          /* 0631 KEY_UNKN: */
/* DC */  xx,          /* 0631 KEY_UNKN: */
/* DD */  xx,          /* 0631 KEY_UNKN: */
/* DE */  xx,          /* 0631 KEY_UNKN: */
/* DF */  xx,          /* 0631 KEY_UNKN: */
/* E0 */  xx,          /* 0631 KEY_UNKN: */
/* E1 */  xx,          /* 0631 KEY_UNKN: */
/* E2 */  xx,          /* 0631 KEY_UNKN: */
/* E3 */  xx,          /* 0631 KEY_UNKN: */
/* E4 */  xx,          /* 0631 KEY_UNKN: */
/* E5 */  xx,          /* 0631 KEY_UNKN: */
/* E6 */  xx,          /* 0631 KEY_UNKN: */
/* E7 */  xx,          /* 0631 KEY_UNKN: */
/* E8 */  xx,          /* 0631 KEY_UNKN: */
/* E9 */  xx,          /* 0631 KEY_UNKN: */
/* EA */  xx,          /* 0631 KEY_UNKN: */
/* EB */  xx,          /* 0631 KEY_UNKN: */
/* EC */  xx,          /* 0631 KEY_UNKN: */
/* ED */  xx,          /* 0631 KEY_UNKN: */
/* EE */  xx,          /* 0631 KEY_UNKN: */
/* EF */  xx,          /* 0631 KEY_UNKN: */
/* F0 */  xx,          /* 0631 KEY_UNKN: */
/* F1 */  xx,          /* 0631 KEY_UNKN: */
/* F2 */  xx,          /* 0631 KEY_UNKN: */
/* F3 */  xx,          /* 0631 KEY_UNKN: */
/* F4 */  xx,          /* 0631 KEY_UNKN: */
/* F5 */  xx,          /* 0631 KEY_UNKN: */
/* F6 */  xx,          /* 0631 KEY_UNKN: */
/* F7 */  xx,          /* 0631 KEY_UNKN: */
/* F8 */  xx,          /* 0631 KEY_UNKN: */
/* F9 */  xx,          /* 0631 KEY_UNKN: */
/* FA */  xx,          /* 0631 KEY_UNKN: */
/* FB */  xx,          /* 0631 KEY_UNKN: */
/* FC */  xx,          /* 0631 KEY_UNKN: */
/* FD */  xx,          /* 0631 KEY_UNKN: */
/* FE */  xx,          /* 0631 KEY_UNKN: */
/* FF */  xx           /* 0777 KEY_MAX: Maximum curses key */
