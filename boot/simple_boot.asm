[org 0x7c00] ; Set global offset for memory access in boot sector

mov bx, LIVE
call print

call print_newline

mov bx, OUTRO
call print

call print_newline

mov dx, 0x4142
call print_hex

call print_newline

jmp $  ; Hang

; Includes
%include "print_ascii.asm"
%include "print_hex.asm"

; data section
LIVE:
    db 'We are live.', 0

OUTRO:
    db "And that's the show, folks.", 0

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0

; Magic number
dw 0xaa55

; vim: set ft=nasm noet : /*
