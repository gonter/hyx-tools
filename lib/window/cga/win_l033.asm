;
; FILE C:\usr\window\cga\win0cga.arc [WIN_L033.asm]
;
; int cga_getpage (void)
; RETURN: aktuelle Bildschirm Seite
;
; 1989 08 20
;
        TITLE   WIN_L033.asm
        NAME    WIN_L033

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

        PUBLIC  _cga_getpage

_cga_getpage proc far
        push    bp
        mov     bp, sp
        push    ds

        mov     ax, 040h
        mov     ds, ax
        mov     al, byte ptr ds:[062h]
        mov     ah, 0

        pop     ds
        mov     sp, bp
        pop     bp
        ret

_cga_getpage endp

WINDOW_TEXT ENDS
END
