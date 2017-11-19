;
; FILE C:\usr\window\cga\win0cga.arc [WIN_L033.asm]
;
; int cga_getpage (void)
; RETURN: aktuelle Bildschirm Seite
;
; 1989 08 20
;
        TITLE   WIN_S033.asm
        NAME    WIN_S033

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

        PUBLIC  _cga_getpage

_cga_getpage proc near
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

_TEXT ENDS
END
