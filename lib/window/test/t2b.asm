;
;  FILE C:\usr\window\win0bios.arc [WIN_L014.ASM]
;
;  1989 08 16: aus WIN0.SAR Åbernommen
;              Revision
;


;       Static Name Aliases
;
        TITLE   WIN_L014.asm
        NAME    win_0014

        .8087
WIN_L014_TEXT   SEGMENT  WORD PUBLIC 'CODE'
WIN_L014_TEXT   ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS

DGROUP  GROUP   CONST, _BSS, _DATA
        ASSUME  CS: WIN_L014_TEXT, DS: DGROUP, SS: DGROUP

WIN_L014_TEXT      SEGMENT
        ASSUME  CS: WIN_L014_TEXT

        PUBLIC  _get_info

_get_info   PROC FAR
        push    bp
        mov     bp,sp

;       info_num  = 6
;       info_mode = 8

        mov     cs:merke, sp
        mov     ax, 01130h
        mov     bh, BYTE PTR [bp+6]      ;info_num
        cmp     byte PTR [bp+8], 1
        je      hopp
        int     010h
        mov     ax, bp
        mov     dx, es
        jmp     tropp

hopp:
        int     010h
        mov     ax,cx

tropp:
        mov     sp,cs:merke
        pop     bp
        ret

merke  dw 0

_get_info   ENDP
WIN_L014_TEXT   ENDS
END

; ----------------------------------------------------------------------------
