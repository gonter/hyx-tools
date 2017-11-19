;
;  FILE C:\usr\window\win0bios.arc [WIN_L024.ASM]
;
;  1989 08 16: aus WIN0.SAR Åbernommen
;              Revision
;

;       Static Name Aliases
;
        TITLE   WIN_L024.c
        NAME    win_0024

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

EXTRN   _W_GRAPH_MAX_Y:WORD
EXTRN   _W_GRAPH_MAX_X:WORD

CONST      SEGMENT
$T20000 DW SEG _W_GRAPH_MAX_X 
        ORG     $+2
$T20001 DW SEG _W_GRAPH_MAX_Y 
CONST      ENDS

WINDOW_TEXT      SEGMENT
        ASSUME  CS: WINDOW_TEXT

        PUBLIC  _bios_wr_dot

_bios_wr_dot   PROC FAR
        push    bp
        mov     bp,sp

;       x   = 6
;       y   = 8
;       col = 10

        cmp     WORD PTR [bp+6],0       ;x
        jl      $EX199
        mov     es,$T20000
        mov     ax,WORD PTR [bp+6]      ;x
        cmp     es:_W_GRAPH_MAX_X,ax
        jle     $EX199
        cmp     WORD PTR [bp+8],0       ;y
        jl      $EX199
        mov     es,$T20001
        mov     ax,WORD PTR [bp+8]      ;y
        cmp     es:_W_GRAPH_MAX_Y,ax
        jle     $EX199

        mov     ah, 12
        mov     al, BYTE PTR [bp+10]      ;col
        mov     bx, 0
        mov     cx, WORD PTR [bp+6]      ;x
        mov     dx, WORD PTR [bp+8]      ;y
        int     010h

$EX199:
        mov     sp,bp
        pop     bp
        ret     
        nop     

_bios_wr_dot    ENDP
WINDOW_TEXT   ENDS
END
