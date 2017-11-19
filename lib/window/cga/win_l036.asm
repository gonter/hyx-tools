;
;  FILE C:\usr\window\win0bios.arc [WIN_L036.ASM]
;
;  VGA Palette setzen
;
;  1989 11 21
;
;
;       Static Name Aliases
;
        TITLE   WIN_L036.ASM
        NAME    win_0036

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

        PUBLIC  _vga_setpalette

_vga_setpalette   PROC FAR
        push    bp
        mov     bp,sp

;       palette color nr        =  6
;       palette color red       =  8
;       palette color green     = 10
;       palette color blue      = 12

        mov     bx, word ptr [bp+6]     ; nr
        mov     ax, word ptr [bp+8]     ; red
        mov     dh, al
        mov     ax, word ptr [bp+10]    ; green
        mov     ch, al
        mov     ax, word ptr [bp+12]    ; blue
        mov     cl, al
        mov     ax, 1010h
        int     10h

$EX199:
        mov     sp,bp
        pop     bp
        ret     

_vga_setpalette   ENDP
WINDOW_TEXT   ENDS
END

; ----------------------------------------------------------------------------
