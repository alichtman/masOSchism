; the GDT starts with an 8-byte NULL sequence
gdt_start:
    dd 0x0
    dd 0x0

; the code segment descriptor
; base=0x0, limit=0xfffff,
; 1st   flags : (present)1 (privilege)00 (descriptor type)1 -> 1001b
; type  flags : (code)1 (conforming)0 (readable)1 (accessed)0 -> 1010b
; 2nd   flags : (granularity 1 (32-bit  default)1 (64-bit  seg)0 (AVL)0 -> 1100b
gdt_code:
    dw 0xffff     ; Limit (bits  0-15)
    dw 0x0        ; Base  (bits  0-15)
    db 0x0        ; Base  (bits  16-23)
    db 10011010b  ; 1st flags, type  flags
    db 11001111b  ; 2nd flags, Limit (bits  16-19)
    db 0x0        ; Base (bits  24-31)

; GDT for data segment. base and length identical to code segment
; Same as code  segment  except  for  the  type  flags:
; type  flags: (code)0 (expand  down)0 (writable)1 (accessed)0 -> 0010b
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end: ; Label here so the assembler can calculate the size of the GDT

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16 bit), always one less than its true size
    dd gdt_start ; address (32 bit)

; Define some constants for the GDT segment descriptor offsets, which
; are what segment registers must contain when in protected mode. For example,
; when we set DS = 0x10 in protected mode, the CPU knows that we mean it to use the
; segment described at offset 0x10 (i.e. 16 bytes) in our GDT, which in our
; case is the DATA segment (0x0 -> NULL; 0x08 -> CODE; 0x10 -> DATA)
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

; vim: set ft=nasm ts=4 sw=4 tw=0 et :
