;
; FILE ~/usr/sbr/sectrd_l.asm
;
; ***********
; LARGE MODEL
; ***********
;
; Lesen eines Sectors
;
; written:       1991 06 22
; latest update: 1994-10-02
;

        TITLE   sector_read


DISK_TEXT   SEGMENT  BYTE PUBLIC 'CODE'
DISK_TEXT   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
DGROUP  GROUP   CONST,  _BSS,   _DATA
        ASSUME  CS: DISK_TEXT, DS: DGROUP, SS: DGROUP, ES: DGROUP
PUBLIC  _sector_read

DISK_TEXT      SEGMENT
;  LARGE MODEL:
;        6 ... Offset Puffer
;        8 ... Segment Puffer
;       10 ... Drive Number
;       12 ... Head Number
;       14 ... Track Number
;       16 ... Sector Number
        PUBLIC  _sector_read
_sector_read PROC far
        push    bp
        mov     bp,sp
        push    es
        push    cx
        push    bx
        push    dx

        mov     bx, [bp+6]      ; data buffer
        mov     es, [bp+8]
        mov     ax, [bp+10]     ; drive number
        mov     dl, al
        mov     ax, [bp+12]     ; head number
        mov     dh, al
        mov     ax, [bp+16]     ; sector number
        mov     cl, al
        mov     ax, [bp+14]     ; track number
        mov     ch, al
        shr     ax, 1
        shr     ax, 1
        and     al, 0C0h
        or      cl, al          ; upper 2 bits of track number
        mov     ax, 0201h       ; command: read one sector
        int     013h

        pop     dx
        pop     bx
        pop     cx
        pop     es
        mov     sp,bp
        pop     bp
        ret
_sector_read ENDP

DISK_TEXT   ENDS
END
