;
; FILE C:\usr\window\cga\win0cga.arc [win_l032.asm]
;
; int cga_get_cols (void)
; RETURN: Zahl der Spalten am Bildschirm
;
; 1989 08 20
;
        TITLE   WIN_S032.asm
        NAME    win_s031
        .MODEL  Small

        .8087
_TEXT  SEGMENT  WORD PUBLIC 'CODE'
_TEXT  ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS
DGROUP  GROUP   CONST, _BSS, _DATA
        ASSUME  CS: _TEXT, DS: DGROUP, SS: DGROUP
_TEXT      SEGMENT
        ASSUME  CS: _TEXT
; Line 4
        PUBLIC  _cga_get_cols

_cga_get_cols proc near
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

_TEXT ENDS
END
