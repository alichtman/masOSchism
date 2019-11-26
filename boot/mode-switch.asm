[bits 16]
; To switch to protected mode, we:
; 1. Disable all interrupts
; 2. Set the "protected mode" flag to 1
; 3. Make a far jump to flush the pipeline
switch_to_32bit_protected_mode:
    cli ; Disable interrupts
    lgdt [gdt_descriptor] ; Load GDT
    ; Set "Protected Mode" flag to 1
    mov eax, cr0
    or  eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:initialize_32bit_protected_mode


[bits 32]
; Once we're in 32-bit protected mode, we need to update the segment registers,
; the stack pointer, and then jump back to code
initialize_32bit_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ;  update the stack right at the top of the free space
    mov ebp, 0x90000
    mov esp, ebp

    call begin_protected_mode_routine ; Jump to a main routine

; vim: set ft=nasm ts=4 sw=4 tw=0 et :
