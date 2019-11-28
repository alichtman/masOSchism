// /**
//  * Read from I/O port to get data from devices, such as the the keyboard.
//  * @param _port
//  * @return
//  */
// unsigned char inportb(unsigned short _port) {
//     unsigned char rv;
//     __asm__ __volatile__("inb %1, %0"
//                          : "=a"(rv)
//                          : "dN"(_port));
//     return rv;
// }

// /**
//  * Write to I/O port to send data to devices.
//  * @param _port
//  * @param _data
//  * @return
//  */
// void outportb(unsigned short _port, unsigned char _data) {
//     __asm__ __volatile__("outb %1, %0"
//                          :
//                          : "dN"(_port), "a"(_data));
// }

/**
 * Read a byte from the specified port
 */
unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    /* Inline assembler syntax. The source and destination registers are switched from NASM.
     * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
     * '"d" (port)': map the C variable '(port)' into e'd'x register
     *
     * Inputs and outputs are separated by colons
     */
    __asm__("in %%dx, %%al"
            : "=a"(result)
            : "d"(port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    /* Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    __asm__("out %%al, %%dx"
            :
            : "a"(data), "d"(port));
}

unsigned short port_word_in(unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax"
            : "=a"(result)
            : "d"(port));
    return result;
}

void port_word_out(unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx"
            :
            : "a"(data), "d"(port));
}
