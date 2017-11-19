;
;  FILE C:\usr\window\win0bios.arc [WIN_L040.ASM]
;
;  VGA Palette Block lesen
;
;  1990 03 04
;
;
;       Static Name Aliases
;
        TITLE   WIN_L040.ASM
        NAME    win_0040

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

        PUBLIC  _vga_palette_block_grey

_vga_palette_block_grey   PROC FAR
        push    bp
        mov     bp,sp

;       palette color nr start      =  6
;       palette color count         =  8

        mov     bx, word ptr [bp+6]     ; nr start
        mov     cx, word ptr [bp+8]     ; color count (table size)
        mov     es, ax
        mov     ax, 101Bh
        int     10h

$EX199:
        mov     sp,bp
        pop     bp
        ret     

_vga_palette_block_grey   ENDP
WINDOW_TEXT   ENDS
END

; ----------------------------------------------------------------------------
