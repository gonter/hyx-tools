;
; FILE C:\usr\window\cga\win0cga.arc [win_l032.asm]
;
; int cga_get_cols (void)
; RETURN: Zahl der Spalten am Bildschirm
;
; 1989 08 20
;
        TITLE   WIN_L032.asm
        NAME    win_l031

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

        PUBLIC  _cga_get_cols

_cga_get_cols proc far
        push    bp
        mov     bp, sp
        push    ds

        mov     ax, 040h
        mov     ds, ax
        mov     ax, word ptr ds:[04Ah]

        pop     ds
        mov     sp, bp
        pop     bp
        ret

_cga_get_cols endp

WINDOW_TEXT ENDS
END
