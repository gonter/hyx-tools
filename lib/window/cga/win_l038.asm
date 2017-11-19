;
;  FILE C:\usr\window\win0bios.arc [WIN_L038.ASM]
;
;  VGA Palette setzen
;
;  1989 11 21
;
;
;       Static Name Aliases
;
        TITLE   WIN_L038.ASM
        NAME    win_0038

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

        PUBLIC  _vga_getpalette

_vga_getpalette   PROC FAR
        push    bp
        mov     bp,sp

;       palette color  nr        =  6
;       palette color *red       =  8
;       palette color *green     = 12
;       palette color *blue      = 16

        mov     bx, word ptr [bp+6]     ; nr
        mov     ax, 1015h
        int     10h

        xor     ah, ah
        mov     al, dh
        les     bx,DWORD PTR [bp+8]     ; *red
        mov     WORD PTR es:[bx],ax

        mov     al, ch
        les     bx,DWORD PTR [bp+12]    ; *green
        mov     WORD PTR es:[bx],ax

        mov     al, cl
        les     bx,DWORD PTR [bp+16]    ; *blue
        mov     WORD PTR es:[bx],ax


$EX199:
        mov     sp,bp
        pop     bp
        ret     

_vga_getpalette   ENDP
WINDOW_TEXT   ENDS
END

; ----------------------------------------------------------------------------
