;       Static Name Aliases
;
        TITLE   win_l043.asm
        NAME    win_l043

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

EXTRN   _W_TEXT_MAX_X:WORD
EXTRN   _W_TEXT_MAX_Y:WORD

CONST      SEGMENT
$T20001 DW SEG _W_TEXT_MAX_Y 
        ORG     $+2
$T20002 DW SEG _W_TEXT_MAX_X 
CONST      ENDS

WINDOW_TEXT      SEGMENT
        ASSUME  CS: WINDOW_TEXT

        PUBLIC  _cga_get_screen_max
_cga_get_screen_max     PROC FAR

        push    ds
        mov     ax, 040h
        mov     ds, ax
        mov     al, ds:[084h]
        mov     ah,0
        cmp     ax, 15
        jge     Y_OK
        mov     ax, 24
Y_OK:
        inc     ax
        pop     ds
        mov     es,$T20001
        mov     WORD PTR es:_W_TEXT_MAX_Y, ax

        push    ds
        mov     ax, 040h
        mov     ds, ax
        mov     ax, ds:[04Ah]
        pop     ds
        mov     es,$T20002
        mov     WORD PTR es:_W_TEXT_MAX_X, ax

        ret     

_cga_get_screen_max     ENDP
WINDOW_TEXT  ENDS
END
