[org 0x7c00] ; Set global offset for memory access in boot sector

; Set up stack in a safe spot
mov bp, 0x8000
mov sp, bp

print_boot_msg:
    call print_newline
    mov bx, BOOT_MSG
    call print_with_newline

; read from disk
mov bx, 0x9000 ; es:bx = 0x0000:0x9000 = 0x09000
mov dh, 2      ; Read two sectors
; the bios sets 'dl' for our boot disk number (requires nasm -fda flag)
call read_disk_sectors

mov dx, [0x9000] ; Get first word in first loaded section. Should be 0xcafe
call print_hex
call print_newline

mov dx, [0x9000 + 512] ; Get first word in second loaded section. Should be 0xbabe
call print_hex_with_newline

mov bx, OUTRO
call print_with_newline

jmp $  ; Hang

; Includes
%include "print_ascii.asm"
%include "print_hex.asm"
%include "boot_sect_disk.asm"

; data section
BOOT_MSG: db ' --> Booting masOSchism...', 0
OUTRO: db " --> And that's the show, folks.", 0

; Fill with 510 zeros minus the size of the previous code and append magic number
times 510-($-$$) db 0
dw 0xaa55

; boot sector = sector 1 of cyl 0 of head 0 of hdd 0
; from now on = sector 2 ...
times 256 dw 0xcafe ; sector 2 = 512 bytes
times 256 dw 0xbabe ; sector 3 = 512 bytes

; vim: set ft=nasm noet : /*
