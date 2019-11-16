;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Read kernel from disk and boot it
; load 'dh' sectors from drive 'dl' into ES:BX
; External code should only call read_disk_sectors
;
; ARGS
; dh -> the number of sectors to read
; dl -> drive to read from
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

read_disk_sectors:
    pusha
    ; dx will be overwritten during the "setting options for loading from disk"
    ; process, so we push it to the stack to be popped off later
    push dx

    mov ah, 0x02 ; tell BIOS to read from disk
    mov al, dh   ; read 'dh' sectors
    mov cl, 0x02 ; read 2nd sector
                 ; 0x01 is our boot sector, 0x02 is the first 'available' sector
    mov ch, 0x00 ; read cylinder 0
    ; dl is the drive number, which is passed in the args
    mov dh, 0x00 ; set drive head to 0

    ; [es:bx] is the location where whatever is read will be stored
    ; In this case, we're reading to the standard int 0x13 location
    ; http://stanislavs.org/helppc/int_13-2.html
    int 0x13           ; BIOS interrupt
    jc disk_read_error ; Handle error (detectable by checking carry bit)

    pop dx
    cmp al, dh   ; Check if we read the correct number of sectors
    jne incorrect_sectors_read_error

    popa
    ret

disk_read_error:
    mov bx, DISK_READ_ERROR_MSG
    call print_with_newline
    mov bx, ERROR_CODE_STR
    call print
    mov dh, ah
    call print_hex
    call print_newline
    jmp disk_error_loop

incorrect_sectors_read_error:
    mov bx, INCORRECT_SECTOR_COUNT_READ_MSG
    call print_with_newline
    jmp disk_error_loop


disk_error_loop:
    jmp $

DISK_READ_ERROR_MSG: db "ERROR ON DISK READ.", 0
INCORRECT_SECTOR_COUNT_READ_MSG: db "INCORRECT NUMBER OF SECTORS READ", 0
ERROR_CODE_STR: db "ERROR CODE: ", 0



; vim: set ft=nasm ts=4 sw=4 tw=0 et :
