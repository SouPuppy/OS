; haribote-os boot asm
; TAB=4

BOTPAK    EQU        0x00280000        ; bootpack address
DSKCAC    EQU        0x00100000        ;         disk cache address
DSKCAC0   EQU        0x00008000        ; disk cache load area

; BOOT_INFO offsets
CYLS      EQU        0x0ff0            ; Cylinder count
LEDS      EQU        0x0ff1            ; LED status
VMODE     EQU        0x0ff2            ; Video mode
SCRNX     EQU        0x0ff4            ; Screen width
SCRNY     EQU        0x0ff6            ; Screen height
VRAM      EQU        0x0ff8            ; VRAM start address

        ORG        0xc200            ; Program start address

;; Set VGA video mode 320 x 200
;
;        MOV        AL,0x13            ; VGA graphics mode 320x200x8bit
;        MOV        AH,0x00
;        INT        0x10
;        MOV        BYTE [VMODE],8    ; Set video mode flag
;        MOV        WORD [SCRNX],320
;        MOV        WORD [SCRNY],200
;        MOV        DWORD [VRAM],0x000a0000

;; Set VBE video mode 640 x 480

        ;MOV        AX,0x4f02
        ;MOV        BX,0x101
        ;INT        0x10
        ;MOV        BYTE [VMODE],8    ; Set video mode flag
        ;MOV        WORD [SCRNX],640
        ;MOV        WORD [SCRNY],480
        ;MOV        DWORD [VRAM],0xe0000000

; Set VBE video mode 1024 x 768

        MOV        AX,0x4f02
        MOV        BX,0x105
        INT        0x10
        MOV        BYTE [VMODE],8    ; Set video mode flag
        MOV        WORD [SCRNX],1024 
        MOV        WORD [SCRNY],768
        MOV        DWORD [VRAM],0xe0000000 
        
; Read keyboard LED status

        MOV        AH,0x02
        INT        0x16              ; keyboard BIOS
        MOV        [LEDS],AL

; Mask PIC interrupts
        MOV        AL,0xff
        OUT        0x21,AL
        NOP                          ; Small delay
        OUT        0xa1,AL

        CLI                          ; Disable further CPU interrupts

; Enable A20 line

        CALL    waitkbdout
        MOV        AL,0xd1
        OUT        0x64,AL
        CALL    waitkbdout
        MOV        AL,0xdf            ; enable A20
        OUT        0x60,AL
        CALL    waitkbdout

; Enter Protected Mode

[INSTRSET "i486p"]                ; Use 486 instructions

        LGDT    [GDTR0]            ; Load GDT
        MOV        EAX,CR0
        AND        EAX,0x7fffffff    ; Clear PG bit
        OR        EAX,0x00000001    ; Set PE bit
        MOV        CR0,EAX
        JMP        pipelineflush
pipelineflush:
        MOV        AX,1*8            ; Set data segment
        MOV        DS,AX
        MOV        ES,AX
        MOV        FS,AX
        MOV        GS,AX
        MOV        SS,AX

; Copy bootpack

        MOV        ESI,bootpack    ; Source
        MOV        EDI,BOTPAK        ; Destination
        MOV        ECX,512*1024/4
        CALL    memcpy

; Copy initial disk data

        MOV        ESI,0x7c00        ; Source
        MOV        EDI,DSKCAC        ; Destination
        MOV        ECX,512/4
        CALL    memcpy

; Copy remaining disk data

        MOV        ESI,DSKCAC0+512    ; Source
        MOV        EDI,DSKCAC+512    ; Destination
        MOV        ECX,0
        MOV        CL,BYTE [CYLS]
        IMUL    ECX,512*18*2/4    ; Convert to bytes
        SUB        ECX,512/4        ; Exclude boot sector
        CALL    memcpy

; Load bootpack

        MOV        EBX,BOTPAK
        MOV        ECX,[EBX+16]
        ADD        ECX,3            ; ECX += 3;
        SHR        ECX,2            ; ECX /= 4;
        JZ        skip            ; Skip if zero
        MOV        ESI,[EBX+20]    ; Source
        ADD        ESI,EBX
        MOV        EDI,[EBX+12]    ; Destination
        CALL    memcpy
skip:
        MOV        ESP,[EBX+12]    ; Set stack pointer
        JMP        DWORD 2*8:0x0000001b

waitkbdout:
        IN        AL,0x64
        AND        AL,0x02
        JNZ        waitkbdout        ; Loop until ready
        RET

memcpy:
        MOV        EAX,[ESI]
        ADD        ESI,4
        MOV        [EDI],EAX
        ADD        EDI,4
        SUB        ECX,1
        JNZ        memcpy            ; Loop until done
        RET
; memcpy is optimized for alignment

        ALIGNB    16
GDT0:
        RESB    8                ; Null descriptor
        DW        0xffff,0x0000,0x9200,0x00cf    ; Data segment
        DW        0xffff,0x0000,0x9a28,0x0047    ; Code segment

        DW        0
GDTR0:
        DW        8*3-1
        DD        GDT0

        ALIGNB    16
bootpack:
