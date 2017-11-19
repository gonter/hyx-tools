;
;  FILE C:\usr\window\win0bios.arc [WIN_L037.ASM]
;
;  VGA Palette Block setzen
;
;  1990 03 04
;
;
;       Static Name Aliases
;
        TITLE   WIN_L037.ASM
        NAME    win_0037

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

        PUBLIC  _vga_setpalette_block

_vga_setpalette_block   PROC FAR
        push    bp
        mov     bp,sp

;       palette color nr start      =  6
;       palette color count         =  8
;       palette color table offset  = 10
;       palette color table segment = 12

        mov     bx, word ptr [bp+6]     ; nr start
        mov     cx, word ptr [bp+8]     ; color count (table size)
        mov     dx, word ptr [bp+10]    ; table offset
        mov     ax, word ptr [bp+12]    ; table segment
        mov     es, ax
        mov     ax, 1012h
        int     10h

$EX199:
        mov     sp,bp
        pop     bp
        ret     

_vga_setpalette_block   ENDP
WINDOW_TEXT   ENDS
END

; ----------------------------------------------------------------------------
