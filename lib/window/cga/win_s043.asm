;       Static Name Aliases
;
        TITLE   win_s043.asm
        NAME    win_s043

        .8087
_TEXT   SEGMENT  WORD PUBLIC 'CODE'
_TEXT   ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS
DGROUP  GROUP   CONST, _BSS, _DATA
        ASSUME  CS: _TEXT, DS: DGROUP, SS: DGROUP

EXTRN   _W_TEXT_MAX_X:WORD
EXTRN   _W_TEXT_MAX_Y:WORD

_TEXT      SEGMENT
        ASSUME  CS: _TEXT

        PUBLIC  _cga_get_screen_max
_cga_get_screen_max     PROC NEAR

        push    ds
        mov     ax, 040h
        mov     ds, ax
        mov     al, ds:[084h]
        mov     ah, 0
        inc     ax
        pop     ds
        mov     WORD PTR _W_TEXT_MAX_Y, ax

        push    ds
        mov     ax, 040h
        mov     ds, ax
        mov     ax, ds:[04Ah]
        pop     ds
        mov     WORD PTR _W_TEXT_MAX_X, ax

        ret     

_cga_get_screen_max     ENDP
_TEXT   ENDS
END
