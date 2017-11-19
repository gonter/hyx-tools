;
;  FILE C:\usr\window\win0bios.arc [WIN_L039.ASM]
;
;  VGA Palette Block lesen
;
;  1990 03 04
;
;
;       Static Name Aliases
;
        TITLE   WIN_L039.ASM
        NAME    win_0039

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

        PUBLIC  _vga_getpalette_block

_vga_getpalette_block   PROC FAR
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
        mov     ax, 1017h
        int     10h

$EX199:
        mov     sp,bp
        pop     bp
        ret     

_vga_getpalette_block   ENDP
WINDOW_TEXT   ENDS
END

; ----------------------------------------------------------------------------
