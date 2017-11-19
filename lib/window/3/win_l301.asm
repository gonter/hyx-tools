;
;  FILE /usr/window/3/win_l301.asm
;
;  1989 08 16: aus WIN0.SAR Åbernommen
;              Revision
;
;
;       Static Name Aliases
;
        TITLE   WIN_L301.ASM
        NAME    win_0301

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

        PUBLIC  _mirror_byte

_mirror_byte   PROC FAR
        push    bp
        mov     bp,sp

;       p = 6

        mov bx, word ptr [bp+6]
        ror bl, 1
        rcl al, 1
        ror bl, 1
        rcl al, 1

        ror bl, 1
        rcl al, 1
        ror bl, 1
        rcl al, 1

        ror bl, 1
        rcl al, 1
        ror bl, 1
        rcl al, 1

        ror bl, 1
        rcl al, 1
        ror bl, 1
        rcl al, 1
        mov ah, 0

$EX199:
        mov     sp,bp
        pop     bp
        ret     

_mirror_byte   ENDP
WINDOW_TEXT   ENDS
END

; ----------------------------------------------------------------------------
