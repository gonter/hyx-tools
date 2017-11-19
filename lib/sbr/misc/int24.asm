;
;  FILE ~/usr/sbr/int24.asm
;
;  Ignore Interrupt 0x24 (critical error)
;
;  written:       1991 02 17
;  latest update: 1994-10-02
;
;  ---------------------------------------------------------------------------
;
        TITLE   int24.asm
        NAME    int24
        .MODEL  Large

DIRTY_TEXT  SEGMENT  WORD PUBLIC 'CODE'
DIRTY_TEXT  ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS

DGROUP  GROUP   CONST, _BSS, _DATA
        ASSUME  CS: DIRTY_TEXT, DS: DGROUP, SS: DGROUP

DIRTY_TEXT      SEGMENT
        ASSUME  CS: DIRTY_TEXT

        PUBLIC  _int24ign_install

_int24ign_install proc far
        push  ds
        push  dx
        push  cs
        pop   ds
        call  next
next:   pop   dx
        add   dx,12
        mov   ax,2524h
        int   021h
        pop   dx
        pop   ds
        ret

int24ign:
        mov al,0
        iret

_int24ign_install endp

DIRTY_TEXT ENDS
END
