;
;  FILE /usr/window/3/win_l302.asm
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

        PUBLIC  _mirror_word

_mirror_word   PROC FAR
        push    bp
        mov     bp,sp

;       p = 6

        mov bx, word ptr [bp+6]
        ror bx, 1
        rcl ax, 1
        ror bx, 1
        rcl ax, 1

        ror bx, 1
        rcl ax, 1
        ror bx, 1
        rcl ax, 1

        ror bx, 1
        rcl ax, 1
        ror bx, 1
        rcl ax, 1

        ror bx, 1
        rcl ax, 1
        ror bx, 1
        rcl ax, 1

        ror bx, 1
        rcl ax, 1
        ror bx, 1
        rcl ax, 1

        ror bx, 1
        rcl ax, 1
        ror bx, 1
        rcl ax, 1

        ror bx, 1
        rcl ax, 1
        ror bx, 1
        rcl ax, 1

        ror bx, 1
        rcl ax, 1
        ror bx, 1
        rcl ax, 1

$EX199:
        mov     sp,bp
        pop     bp
        ret     

_mirror_word   ENDP
WINDOW_TEXT   ENDS
END

; ----------------------------------------------------------------------------
