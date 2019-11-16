; External code can call print_hex
; Hex value should be passed in dx register

print_hex:
    pusha
    mov cx, 0 ; loop index variable
    jmp print_hex_loop

print_hex_with_newline:
    pusha
    call print_hex
    call print_newline
    popa
    ret

; Implementation: Extract last byte. ASCII 0-9 has hex values of 0x30 - 0x39.
; ASCII A-F has hex values of 0x41 - 0x46. Start off by adding 0x30. If the result
; is greater than 0x39, add another 7 to get the A - F range. Then place the result
; in the right spot in the string.
print_hex_loop:
    cmp cx, 4 ; Loop 4 times (because dx has a capacity of 4 bytes)
    je print_hex_done

    ; Use ax as scratch register. Mask out first three bytes (leaving only the last one.
    mov ax, dx
    and ax, 0x000f
    add ax, 0x30 ; Add 0x30 to convert 0x0 - 0x9 into ASCII 0 - 9
    cmp al, 0x39
    jle place_ascii_val_in_str
    add ax, 7    ; Add 7 to get to the A - F range

place_ascii_val_in_str:
    ; Get base addr of string + length minus current index
    mov bx, HEX_OUTPUT + 5
    sub bx, cx
    mov [bx], al ; Copy character in
    shr dx, 4

    ; Increment loop index and loop
    add cx, 1
    jmp print_hex_loop


print_hex_done:
    ; Print output
    mov bx, HEX_OUTPUT
    call print
    popa
    ret

; Reserving space for output
HEX_OUTPUT:
    db "0x0000", 0

; vim: set ft=nasm et :
