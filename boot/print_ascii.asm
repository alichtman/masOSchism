; External code can call print, print_newline or print_with_newline
; String args should be passed in bx

print:
    pusha
    jmp print_ascii_start

print_with_newline:
    pusha
    call print
    call print_newline
    popa
    ret

; while (str[x] != 0) {
;   print(str[x]);
;   x++;
; }

; bx holds the base address of the string passed in
print_ascii_start:
    ; Compare the next letter with 0 to see if we're at the end of the string
    mov al, [bx]
    cmp al, 0
    je print_ascii_done

    ; Print it
    mov ah, 0x0e
    int 0x10

    ; Advance pointer to next char and loop
    add bx, 1
    jmp print_ascii_start

print_ascii_done:
    popa
    ret

; Special function required for printing a newline since it's actually two
; characters
print_newline:
    pusha
    mov ah, 0x0e ; Tell BIOS to print things
    mov al, 0x0a ; Newline char
    int 0x10
    mov al, 0x0d ; Carriage return
    int 0x10
    jmp print_ascii_done


; vim: set ft=nasm  noet : /*
