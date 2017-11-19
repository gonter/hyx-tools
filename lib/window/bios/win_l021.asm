;       Static Name Aliases
;
        TITLE   win_0021.c
        NAME    win_0021

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

EXTRN   _W_TEXT_MAX_Y:WORD
EXTRN   _W_TEXT_MAX_X:WORD

CONST      SEGMENT
$T20000 DW SEG _W_TEXT_MAX_X 
        ORG     $+2
$T20001 DW SEG _W_TEXT_MAX_Y 
CONST      ENDS

WINDOW_TEXT      SEGMENT
        ASSUME  CS: WINDOW_TEXT

        PUBLIC  _bios_scrblk_up
_bios_scrblk_up PROC FAR
        push    bp
        mov     bp,sp

;       ax = 6
;       ay = 8
;       bx = 10
;       by = 12
;       attr = 14
;       cnt = 16

        cmp     WORD PTR [bp+10],0      ;bx
        jl      $EX200
        mov     es,$T20000
        mov     ax,WORD PTR [bp+6]      ;ax
        cmp     es:_W_TEXT_MAX_X,ax
        jle     $EX200
        cmp     WORD PTR [bp+12],0      ;by
        jl      $EX200
        mov     es,$T20001
        mov     ax,WORD PTR [bp+8]      ;ay
        cmp     es:_W_TEXT_MAX_Y,ax
        jl      $EX200

        cmp     WORD PTR [bp+6],0       ;ax
        jge     $I205
        mov     WORD PTR [bp+6],0       ;ax

$I205:
        cmp     WORD PTR [bp+8],0       ;ay
        jge     $I206
        mov     WORD PTR [bp+8],0       ;ay

$I206:
        mov     es,$T20000
        mov     ax,WORD PTR [bp+10]     ;bx
        cmp     es:_W_TEXT_MAX_X,ax
        jg      $I207
        mov     ax,es:_W_TEXT_MAX_X
        dec     ax
        mov     WORD PTR [bp+10],ax     ;bx

$I207:
        mov     es,$T20001
        mov     ax,WORD PTR [bp+12]     ;by
        cmp     es:_W_TEXT_MAX_Y,ax
        jg      $I208
        mov     ax,es:_W_TEXT_MAX_Y
        dec     ax
        mov     WORD PTR [bp+12],ax     ;by

$I208:
        mov     ah,6
        mov     al,BYTE PTR [bp+16]     ;cnt
        mov     ch,BYTE PTR [bp+8]      ;ay
        mov     cl,BYTE PTR [bp+6]      ;ax
        mov     dh,BYTE PTR [bp+12]     ;by
        mov     dl,BYTE PTR [bp+10]     ;bx
        mov     bh,BYTE PTR [bp+14]     ;attr

        int     10h

$EX200:
        mov     sp,bp
        pop     bp
        ret     

_bios_scrblk_up ENDP
WINDOW_TEXT   ENDS
END
