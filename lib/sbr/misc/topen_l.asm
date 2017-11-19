;
; FILE ~/usr/sbr/topen_l.asm
;
; ***********
; LARGE MODEL
; ***********
;
; Eroeffnen eines temporaeren Files (unique filename)
;
; written:       1990 06 02
; latest update: 1994-10-02
;

        TITLE   topen


TOPEN_TEXT   SEGMENT  BYTE PUBLIC 'CODE'
TOPEN_TEXT   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
DGROUP  GROUP   CONST,  _BSS,   _DATA
        ASSUME  CS: TOPEN_TEXT, DS: DGROUP, SS: DGROUP, ES: DGROUP

TOPEN_TEXT      SEGMENT  ; ---------------------------------------------------
;  LARGE MODEL:
;       a=6     Offset  Path Name
;       b=8     Segment Path Name
;       c=10    Attributes

        PUBLIC  _topen
_topen PROC far
        push    bp
        mov     bp,sp
        push    ds

        mov     dx, [bp+6]    ; Path Name
        mov     ds, [bp+8]
        mov     cx, [bp+10]   ; Attributes
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

TOPEN_TEXT   ENDS
END
