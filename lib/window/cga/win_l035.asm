;
;  FILE C:\usr\window\win0bios.arc [WIN_L035.ASM]
;
;  1989 09 17
;
;       Static Name Aliases
;
        TITLE   win_0034.c
        NAME    win_0034

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

        PUBLIC  _cga_scrblk_right
_cga_scrblk_right       PROC FAR
        push    bp
        mov     bp,sp
        sub     sp,10
        push    di
        push    si
; Line 13
;       page = 6
;       ax = 8
;       ay = 10
;       bx = 12
;       by = 14
;       attr = 16
;       cnt = 18
;       register si = x
;       register di = y
;       ch = -6
;       zm = -8
;       lines = -10
; Line 19
        cmp     WORD PTR [bp+18],0      ;cnt
        jle     $ERR
        mov     ax,WORD PTR [bp+12]     ;bx
        sub     ax,WORD PTR [bp+8]      ;ax
        cmp     ax,WORD PTR [bp+18]     ;cnt
        jge     $I115
$ERR:
        mov     ax,-1
        pop     si
        pop     di
        mov     sp,bp
        pop     bp
        ret     
$I115:
;
;         cmp     WORD PTR [bp+12],0      ;bx
;         jl      $ERR
;         mov     es,$T20000
;         mov     ax,WORD PTR [bp+8]      ;ax
;         cmp     es:_W_TEXT_MAX_X,ax
;         jle     $ERR
;         cmp     WORD PTR [bp+14],0      ;by
;         jl      $ERR
;         mov     es,$T20001
;         mov     ax,WORD PTR [bp+10]     ;ay
;         cmp     es:_W_TEXT_MAX_Y,ax
;         jle     $ERR
; 
;         cmp     WORD PTR [bp+8],0       ;ax
;         jge     c1
;         mov     WORD PTR [bp+8],0
; c1:     mov     es,$T20000
;         mov     ax,WORD PTR [bp+12]     ;bx
;         cmp     es:_W_TEXT_MAX_X,ax
;         jg      c2
;         mov     ax,es:_W_TEXT_MAX_X
;         mov     WORD_PTR [bp+12],ax
; c2:     cmp     WORD PTR [bp+10],0      ;ay
;         jge     c3
;         mov     WORD PTR [bp+10],0
; c3:     mov     es,$T20001
;         mov     ax,WORD PTR [bp+14]     ;by
;         cmp     es:_W_TEXT_MAX_Y,ax
;         jg      c4
;         mov     ax,es:_W_TEXT_MAX_X
;         mov     WORD_PTR [bp+14],ax
; c4:
;
; Kontroll Variablen einrichten
        mov     es,$T20003
        mov     ax, es:_W_TEXT_AKT_MULT ; Zeilenmultiplikator
        mov     WORD PTR [bp-8], ax     ; zm
        mov     dx, ax
        mov     al, BYTE PTR [bp+10]    ; ay
        mul     dx                      ; ax = y * Zeilenmultiplikator
        mov     bx, ax

        mov     es,$T20002
        mov     ax, es:_W_TEXT_AKT_MEM  ; Adresse der Bildschirmseite
        mov     es, ax
        mov     ax, WORD PTR [bp+8]     ; ax *= 2
        add     ax, ax
        mov     WORD PTR [bp+8], ax
        mov     ax, WORD PTR [bp+12]    ; bx *= 2
        add     ax, ax
        mov     WORD PTR [bp+12], ax
        mov     ax, WORD PTR [bp+18]    ; cnt *= 2
        add     ax, ax
        mov     WORD PTR [bp+18], ax

        mov     ax,WORD PTR [bp+14]     ; by
        sub     ax,WORD PTR [bp+10]     ; ay
        inc     ax
        mov     WORD PTR [bp-10], ax    ; lines = by - ay
Loop1:  ; Zeilen
        cmp     ax, 0
        jle     Over1
        mov     di,WORD PTR [bp+12]     ; bx
        mov     si,di
        sub     si,WORD PTR [bp+18]     ; cnt

Loop2:  cmp     WORD PTR [bp+8], si     ; ax
        jg      Over2
        mov     ax, es:[bx+si]
        mov     es:[bx+di], ax
        dec     si
        dec     si
        dec     di
        dec     di
        jmp     Loop2
Over2:
        mov     ax, WORD PTR [bp-8]     ; zm
        add     bx, ax
        mov     ax, WORD PTR [bp-10]    ; lines
        dec     ax
        mov     WORD PTR [bp-10], ax    ; lines
        jmp     Loop1

Over1:
        pop     si
        pop     di
        mov     sp,bp
        pop     bp
        ret     

_cga_scrblk_right       ENDP
WINDOW_TEXT   ENDS
END
