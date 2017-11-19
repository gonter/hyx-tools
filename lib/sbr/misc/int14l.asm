;
; FILE %sbr/int14l.asm
;
; RS 232 Puffer fuer die Verwendung unter C
;
; ----------------------------------------------------------------------------
; angepasst fuer das MEDIUM und LARGE Modell:
; alle RETs wurden als FAR RET - Konstanten eingesetzt
; ----------------------------------------------------------------------------
;
; written:       1985 08 01
;                1989 10 29: Revision
; latest update: 1995-09-10
;

        NAME  int14

public  _INIT           ; Initialisierung der ganzen Aenderung
public  _STOP           ; Pufferung wieder ausklinken

public  _RS_GETCH       ; lesen aus dem Puffer
public  _RS_PUTCH       ; Ausgabe eines Zeichens auf der Schnittstelle

puffsize equ 2000       ; Groesse des Ringpuffers
                        ; Bei Bedarf anpassen !!!

; ----------------------------------------------------------------------------
; ANM: 1. Dieses Modul wird zum Programmsystem dazugelinkt
;      2. Vor der Verwendung der Schnittstelle muss unbedingt
;         _INIT aufgerufen werden!
;      3. Vor verlassen des Programms muss unbeding
;         _STOP aufgerufen werden!
;         Andernfalls wuerden die Interrupt Vektoren nicht
;         wieder hergestellt werden !!!!!!!!!!!!
;         (-> Systemabsturz zu spaeteren Zeitpunkt)
;
;
; ----------------------------------------------------------------------------
_DATA segment word public 'DATA'
_DATA ends
DGROUP  group _DATA

_TEXT   segment byte public 'CODE'
        assume cs:_TEXT, ds:DGROUP


dssave  dw 0
nxtrd   dw 0
nxtwr   dw 0
rdcnt   dw 0
wrcnt   dw 0
temp    dw 0
p_end   dw 0

s_hw1   dw 0
s_hw2   dw 0
s_sw1   dw 0
s_sw2   dw 0

; ----------------------------------------------------------------------------
; Input:  --
; Output: Return (AX): Groesse des Puffers
;
_INIT   proc far
        push es
        push ax
        push dx
        push bp

        ; Pointer und Zaehler initialisieren
        mov [dssave], cs        ; Segment des Puffers
        mov ax, offset p_base
        mov [nxtrd], ax
        mov [nxtwr], ax
        add ax, puffsize
        mov [p_end], ax
        mov [rdcnt], 0        ; noch nichts vom Puffer gelesen
        mov [wrcnt], 0        ; .    .      in den Puffer geschrieben

        ; Interrupt Vektoren scharfmachen
        push ds
        mov ax, 0
        mov ds, ax
        mov es, ax
        mov bp, ax
        mov ax, es: [bp+30h]  ; HW int Vektor retten, Offset
        mov [s_hw1], ax       ; HW int Vektor retten, Offset
        mov ax, es: [bp+32h]  ; .  .   .      .     , Segment
        mov [s_hw2], ax       ; .  .   .      .     , Segment
        mov ax, es: [bp+50h]  ; INT 14 .      .     , Offset
        mov [s_sw1], ax       ; INT 14 .      .     , Offset
        mov ax, es: [bp+52h]  ; .   .  .      .     , Segment
        mov [s_sw2], ax       ; .   .  .      .     , Segment
        mov ax, offset int_server
        mov es: [bp+30h], ax
        mov es: [bp+32h], cs
        mov ax, offset int_14
        mov es: [bp+50h], ax
        mov es: [bp+52h], cs
        pop ds

        ; Interrupt Controller und Masken klarmachen
        mov dx, 03f9H        ; IER
        mov al, 01H          ; Interrupt nur bei Data Available
        out dx, al

        mov dx, 03fch        ; MCR
        in al, dx
        or  al, 008H         ; out 2 == 0 -> Interrupt enabled
        out dx, al

        mov dx, 021H         ; 8259: Masken Register
        in al, dx
        and al, 0EFH         ; bit 4 == 0 -> Interrupt enabled
        out dx, al

        mov ax, puffsize
        pop bp
        pop dx
        pop ax
        pop es
        ret
_INIT   endp

; ----------------------------------------------------------------------------
_RS_GETCH  proc far
        ; Return: ax > 255 ->  buffer underflow
        ;         sonst: al == gelesenes Zeichen
        push bx
        push dx
        push ds

        mov ds, word ptr cs: [dssave]

        mov dx, [rdcnt]
        mov bx, [nxtrd]         ; if ((nxtrd ==
        cmp bx, [nxtwr]         ;                nxtwr)
        jne r_doit
        cmp dx, [wrcnt]         ; && (rdcnt == wrcnt))
        jne r_doit
        ; buffer underflow
        mov ax, 0100H
        jmp r_ready             ; return (256);   -> buffer empty

r_doit: mov al, [bx]
        mov ah, 0
        cmp bx, [p_end]         ; if (nxtrd == buffer_end)
        jne rbxin
        mov bx, offset p_base   ; wieder an den anfang des puffers
        jmp r_doit2
rbxin:  inc bx                  ; else nxtrd++;
r_doit2:
        mov [nxtrd], bx
        inc dx                  ; rdcnt++;
        mov [rdcnt], dx
r_ready:
        pop ds
        pop dx
        pop bx
        ret
_RS_GETCH  endp

; ============================================================================
; Interruptbedienung

; 1. Behandlung des Software Interrupt 0x14
; maskierung fuer die rs232 bios routine
int_14  proc far
        sti
        cmp ah, 2               ; read from COM-line
        je read
        mov [temp], dx
        mov dx, [s_sw2]
        push dx
        mov dx, [s_sw1]         ; eventuell zuerst Segment!!!
        push dx
        mov dx, [temp]
        ret                     ; immer Wert fuer RET FAR  !!

read:   ; Ausfuehren des Befehls # 2
        call _RS_GETCH
        iret
int_14  endp

; ----------------------------------------------------------------------------
; 2. Behandlung des von der RS232-Hardware ausgeloesten Interrupts
int_server:  ; von der Hardware ausgeloeste Routine
             ; zum Einlesen in den Puffer
        sti
        push ax
        push bx
        push dx
        push ds

        mov ds, word ptr cs: [dssave]

        mov dx, 03f8h           ; Empfangs-Register des 8250 Chip
        in al, dx               ; lesen auf alle Faelle
        mov bx, [nxtwr]
        cmp bx, [nxtrd]         ; if ((nxtwr == nxtrd)
        jne w_doit
        mov dx, [wrcnt]
        cmp dx, [rdcnt]         ; && (rdcnt != wrcnt)) /* vgl. oben!! */
        je w_doit               ; bei read genau das Gegenteil!!
        jmp w_ready

w_doit: mov [bx], al            ; nur speichern wenn Platz da ist!
        mov dx, [wrcnt]
        cmp bx, [p_end]         ; if (nxtwr == puffer end)
        jne w_inc_bx
        mov bx, offset p_base   ; wieder an den Anfang
        jmp w_doit2
w_inc_bx: inc bx
w_doit2:
        mov [nxtwr], bx
        inc dx
        mov [wrcnt], dx

w_ready:
        mov dx, 0020H
        mov al, 020h
        out dx, al              ; Interrupt CRRL zuruecksetzen

        pop ds
        pop dx
        pop bx
        pop ax
        iret

; ============================================================================
_STOP   proc far
        push es
        push ax
        push dx
        push bp

        ; Interrupt Vektoren von vorher
        push ds
        mov ax, 0
        mov ds, ax
        mov es, ax
        mov bp, ax
        mov ax, [s_hw1]       ; HW int Vektor retten, Offset
        mov es: [bp+30h], ax  ; HW int Vektor retten, Offset
        mov ax, [s_hw2]       ; .  .   .      .     , Segment
        mov es: [bp+32h], ax  ; .  .   .      .     , Segment
        mov ax, [s_sw1]       ; INT 14 .      .     , Offset
        mov es: [bp+50h], ax  ; INT 14 .      .     , Offset
        mov ax, [s_sw2]       ; .   .  .      .     , Segment
        mov es: [bp+52h], ax  ; .   .  .      .     , Segment
        pop ds

        ; Interrupt Controller und Masken / sperren
        mov dx, 03f9H        ; IER
        mov al, 00H          ; keine Interrupts
        out dx, al

        mov dx, 03fch        ; MCR
        in al, dx
        and al, 0F7H         ; out 2 == 0 -> Interrupt disabled
        out dx, al

        mov dx, 021H         ; 8259: Masken Register
        in al, dx
        or  al, 010H         ; bit 4 == 0 -> Interrupt enabled
        out dx, al

        pop bp
        pop dx
        pop ax
        pop es
        ret
_STOP   endp

; Ausgabe: -------------------------------------------------------------------
_RS_PUTCH  proc far  ; ohne leitungsbedienung!!!
        push bp
        mov bp,sp
        push ax
        push dx
        mov dx, 03fdH
loo:    in al, dx
        and al, 020h       ; Sende Halte Register leer?
        jz loo
        mov dx, 03f8H
        mov ax, [bp+6]     ; MEDIUM: 6;  SMALL: 4
        out dx, al
        pop dx
        pop ax
        pop bp
        ret
_RS_PUTCH  endp

; Ringpuffer: ----------------------------------------------------------------
p_base  DB puffsize Dup (?) ; Puffer Speicher
        DB 2 Dup (?)

_TEXT   ends
        end

