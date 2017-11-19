;
; FILE ~/usr/sbr/topen_s.asm
;
; ***********
; SMALL MODEL
; ***********
;
; Eroeffnen eines temporaeren Files (unique filename)
;
; written:       1990 06 02
; latest update: 1994-10-02
;

        TITLE   topen


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

_TEXT      SEGMENT  ; --------------------------------------------------------
;  LARGE MODEL:
;       a=4     Offset Path Name
;       c=6     Attributes

        PUBLIC  _topen
_topen PROC near
        push    bp
        mov     bp,sp
        push    ds

        mov     dx, [bp+4]    ; Path Name
                              ; DS vom rufenden Process
        mov     cx, [bp+6]    ; Attributes
        mov     ax, 05A00h    ; topen
        int     021h

        jnc     all_ok
        mov     dx, 0FFFFh

all_ok:
        sub     dx,dx
over:
        pop     ds
        mov     sp,bp
        pop     bp
        ret
_topen ENDP

_TEXT   ENDS
END
