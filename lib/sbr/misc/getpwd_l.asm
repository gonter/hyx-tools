;
; FILE %sbr/getpwd_l.asm
;
; ***********
; LARGE MODEL
; ***********
;
; Ermittlung des Current Work Directories
; Wechseln des Current Work Directories
;
; written:       1987 11 25
;                1989 07 10: Revision
; latest update: 1996-03-17 16:08:23
;

        TITLE   getpwd


GETPWD_TEXT   SEGMENT  BYTE PUBLIC 'CODE'
GETPWD_TEXT   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
DGROUP  GROUP   CONST,  _BSS,   _DATA
        ASSUME  CS: GETPWD_TEXT, DS: DGROUP, SS: DGROUP, ES: DGROUP
PUBLIC  _getpwd
; PUBLIC  _CDIR

GETPWD_TEXT      SEGMENT
;  LARGE MODEL:
;       a=6     Offset Puffer
;       b=8     Segment Puffer
;       c=10    Drive Number
        PUBLIC  _getpwd
_getpwd PROC far
        push    bp
        mov     bp,sp
        push    si
        push    ds

        mov     si, [bp+6]      ; Data Buffer
        mov     ds, [bp+8]
        mov     dx, [bp+10]     ; drive number: 0..default
        mov     ax, 04700h      ; getpwd
        int     021h

        pop     ds
        pop     si
        mov     sp,bp
        pop     bp
        ret
_getpwd ENDP

;         a=4
;         PUBLIC  _CDIR
; _CDIR PROC far
;         push    bp
;         mov     bp,sp
;         push    di
;         push    si
; 
;         mov     DX, [bp+4]    ; Pointer to Pathname
;         mov     ah, 03Bh      ; CDIR
;         mov     al, 000h
;         int     021h
;         jc      cdir_error
;         mov     ax, 0
;         jmp     cdir_ende
; cdir_error: mov  ax, -1
; 
; cdir_ende:
;         pop     si
;         pop     di
;         mov     sp,bp
;         pop     bp
;         ret
; _CDIR ENDP

GETPWD_TEXT   ENDS
END
