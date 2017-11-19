;
; FILE C:/usr/window/bios/win_l027.asm
;
; void bios_set_mode (int mode)
; RETURN: Zahl der Spalten am Bildschirm
;
; 1989 08 20
;
        TITLE   WIN_L027.asm
        NAME    win_l027

        .8087
WINDOW_TEXT  SEGMENT  WORD PUBLIC 'CODE'
WINDOW_TEXT  ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS

DGROUP  GROUP   CONST, _BSS, _DATA
        ASSUME  CS: WINDOW_TEXT, DS: DGROUP, SS: DGROUP

WINDOW_TEXT      SEGMENT
        ASSUME  CS: WINDOW_TEXT

        PUBLIC  _bios_set_mode

_bios_set_mode proc far
        push    bp
        mov     bp, sp

        mov     ax, word ptr [bp+6]
        mov     ah, 0
        int     10h

        mov     sp, bp
        pop     bp
        ret

_bios_set_mode endp

WINDOW_TEXT ENDS
END
