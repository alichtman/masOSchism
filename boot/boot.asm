[org 0x7c00] ; Set global offset for memory access in boot sector
KERNEL_OFFSET equ 0x1000 ; The same offset used when linking the kernel

	; Set up stack in a safe spot
	mov [BOOT_DRIVE], dl ; BIOS sets us the boot drive in 'dl' on boot
	mov bp, 0x8000
	mov sp, bp

	; Say hello from 16-bit real mode
	call print_newline
	mov bx, BOOT_MSG
	call print_with_newline

	; Load kernel
	call load_kernel
	; Disable interrupts, load GDT. Finally jumps to 'begin_protected_mode_routine'
	call switch_to_32bit_protected_mode
	jmp $  ; Hang

;;;;;;;;;;;;
; INCLUDES ;
;;;;;;;;;;;;

%include "boot/print/print_ascii.asm"
%include "boot/print/print_ascii_32bit.asm"
%include "boot/print/print_hex.asm"
%include "boot/read_disk.asm"
%include "boot/32bit-gdt.asm"
%include "boot/mode-switch.asm"

[bits 16]
load_kernel:
	mov bx, LOADING_KERNEL_MSG
	call print_with_newline

	; Read from disk and store in 0x1000
	mov bx, KERNEL_OFFSET
	mov dh, 2
	mov dl, [BOOT_DRIVE]
	call read_disk_sectors
	ret

[bits 32]
begin_protected_mode_routine:
	mov ebx, HELLO_FROM_PROTECTED_MODE_MSG ; This will be printed at the top of the screen
	call print_string_32b
	; TODO: Here is where it all breaks
	; call KERNEL_OFFSET ; Give control to the kernel
	jmp $

;;;;;;;;;;;;;;;;
; DATA SECTION ;
;;;;;;;;;;;;;;;;

BOOT_DRIVE: db 0 ; Since 'dl' may be overwritten, this should be stored in memory

; Messages
BOOT_MSG: db 'Booting masOSchism in Real Mode', 0
HELLO_FROM_PROTECTED_MODE_MSG: db "Switched to Protected Mode", 0
LOADING_KERNEL_MSG: db "Loading kernel into memory", 0

; Fill with 510 zeros minus the size of the previous code and append magic number
times 510-($-$$) db 0
dw 0xaa55

; boot sector = sector 1 of cyl 0 of head 0 of hdd 0
; from now on = sector 2 ...
times 256 dw 0xcafe ; sector 2 = 512 bytes
times 256 dw 0xbabe ; sector 3 = 512 bytes

; vim: set ft=nasm noet : /*
