;
; FILE C:\usr\window\cga\win0cga.arc [win_l031.asm]
;
; int cga_get_mode (void)
; RETURN: aktuelle Bildschirm Modus
;
; 1989 08 20
;
        TITLE   WIN_L031.asm
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

        PUBLIC  __cga_get_mode

__cga_get_mode proc far
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

WINDOW_TEXT ENDS
END
