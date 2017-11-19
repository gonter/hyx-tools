;
; FILE %sbr/getpwd_s.asm
;
; ***********
; SMALL MODEL
; ***********
;
; Ermittlung des Current Work Directories
; Wechseln des Current Work Directories
;
; written:       1987 11 25
;                1989 07 10: Anpassung fuer SMALL Modell
; latest update: 1995-09-10
;

        TITLE   getpwd


_TEXT   SEGMENT  BYTE PUBLIC 'CODE'
_TEXT   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
DGROUP  GROUP   CONST,  _BSS,   _DATA
        ASSUME  CS: _TEXT, DS: DGROUP, SS: DGROUP, ES: DGROUP

_TEXT      SEGMENT
;  SMALL MODEL:
;       a=4     Offset Puffer
;       c=6    Drive Number

        PUBLIC  _getpwd
_getpwd PROC near
        push    bp
        mov     bp,sp
        push    si
        push    ds

        mov     si, [bp+4]    ; Data Buffer
                              ; DS vom rufenden Process
        mov     dx, [bp+6]
        mov     ax, 04700h    ; getpwd
        int     021h

        pop     ds
        pop     si
        mov     sp,bp
        pop     bp
        ret
_getpwd ENDP

;         a=4
;         PUBLIC  _CDIR
; _CDIR PROC near
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

_TEXT   ENDS
END
