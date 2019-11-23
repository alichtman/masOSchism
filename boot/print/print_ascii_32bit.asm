[bits 32]

VIDEO_MEMORY equ 0xb8000 ; Video Memory location
WHITE_ON_BLACK equ 0x0f  ; color byte for each character

print_string_32b:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    mov al, [ebx]           ; Copy character into al
    mov ah, WHITE_ON_BLACK  ; Copy color code into ah

    cmp al, 0               ; Check for end of string
    je print_string_pm_done

    mov [edx], ax ; store character + color in video memory
    add ebx, 1    ; Advance char pointer to next char
    add edx, 2    ; Advance video memory pointer to next space

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret

; vim: set ft=nasm ts=4 sw=4 tw=0 et :
