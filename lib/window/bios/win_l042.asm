;       Static Name Aliases
;
        TITLE   win_l042.asm
        NAME    win_0042

        .8087
WINDOW_TEXT   SEGMENT  WORD PUBLIC 'CODE'
WINDOW_TEXT   ENDS
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

        PUBLIC  _bios_getcup
_bios_getcup    PROC FAR
        push    bp
        mov     bp,sp

;       x = 8
;       y = 12
;       p = 6

        mov     BYTE PTR [bp-27],3
        mov     bh,BYTE PTR [bp+6]      ;p
        mov     ah,3
        int     010h

        les     bx,DWORD PTR [bp+8]     ;x
        mov     al, dl
        sub     ah, ah
        mov     WORD PTR es:[bx],ax
        les     bx,DWORD PTR [bp+12]    ;y
        mov     al, dh
        mov     WORD PTR es:[bx],ax

        mov     sp,bp
        pop     bp
        ret     
        nop     

_bios_getcup    ENDP
WINDOW_TEXT   ENDS
END
