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
EXTRN   _W_TEXT_AKT_MEM:WORD
EXTRN   _W_TEXT_AKT_MULT:WORD

CONST      SEGMENT
$T20000 DW SEG _W_TEXT_MAX_X 
        ORG     $+2
$T20001 DW SEG _W_TEXT_MAX_Y 
         ORG     $+2
$T20002 DW SEG _W_TEXT_AKT_MEM
         ORG     $+2
$T20003 DW SEG _W_TEXT_AKT_MULT

CONST      ENDS

WINDOW_TEXT      SEGMENT
        ASSUME  CS: WINDOW_TEXT

        PUBLIC  _cga_getchar

_cga_getchar   PROC FAR
        push    bp
        mov     bp,sp

;       p = 6
;       x = 8
;       y = 10
;       a = 12
;       c = 14

        cmp     WORD PTR [bp+8],0       ;x
        jl      $EX199
        mov     es,$T20000
        mov     ax,WORD PTR [bp+8]      ;x
        cmp     es:_W_TEXT_MAX_X,ax
        jle     $EX199
        cmp     WORD PTR [bp+10],0      ;y
        jl      $EX199
        mov     es,$T20001
        mov     ax,WORD PTR [bp+10]     ;y
        cmp     es:_W_TEXT_MAX_Y,ax
        jle     $EX199

        mov     es,$T20003
        mov     ax, es:_W_TEXT_AKT_MULT ; Zeilenmultiplikator
        mov     dx, ax
        mov     al, BYTE PTR [bp+10]    ;y
        mul     dx                      ; ax = y * Zeilenmultiplikator
        mov     bl, BYTE PTR [bp+8]     ;x
        mov     bh, 0
        add     bx, bx                  ; bx = x * 2
        add     bx, ax

        mov     es,$T20002
        mov     ax, es:_W_TEXT_AKT_MEM  ; Adresse der Bildschirmseite
        mov     es, ax
        mov     cl, BYTE PTR [bp+14]     ;c
        mov     ch, BYTE PTR [bp+12]     ;a

        mov     dx, 03dah
y1:     in      al, dx
        test    al, 1
        jnz     y1
y2:     in      al, dx
        test    al, 1
        jz      y2

        mov     ax, es:word ptr [bx]

$EX199:
        mov     sp,bp
        pop     bp
        ret     

_cga_getchar   ENDP
WINDOW_TEXT   ENDS
END
