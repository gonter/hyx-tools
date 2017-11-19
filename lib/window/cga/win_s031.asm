;
; FILE C:\usr\window\cga\win0cga.arc [win_l031.asm]
;
; int cga_get_mode (void)
; RETURN: aktuelle Bildschirm Modus
;
; 1989 08 20
;
        TITLE   WIN_S031.asm
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
        PUBLIC  __cga_get_mode

__cga_get_mode proc near
        push    bp
        mov     bp, sp
        push    ds

        mov     ax, 040h
        mov     ds, ax
        mov     al, byte ptr ds:[049h]
        mov     ah, 0

        pop     ds
        mov     sp, bp
        pop     bp
        ret

__cga_get_mode endp

_TEXT ENDS
END
