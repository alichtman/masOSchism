// #include "../drivers/display.h"
#include "../drivers/ports.h"

#define VIDEO_MEM_ADDR 0xb8000
#define SCREEN_ROWS 25
#define SCREEN_COLS 80

void write_to_video_memory(char *str, int color, int row, int col) {
    volatile char *destination = (char *)VIDEO_MEM_ADDR + row + (25 * col);
    int counter = 0;
    while (*str) {
        *(destination + counter) = *str;
        *(destination + counter + 1) = color;
        counter += 2;
        str++;
    }
}
#define WHITE 0X0F
int attribute = WHITE;
unsigned short *vga_mem = 0;
int csr_x = 0, csr_y = 0;

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count) {
    unsigned short *dest_orig = dest;
    for (int i = 0; i < count; i++) {
        *dest = val;
        dest++;
    }
    return dest_orig;
}

void clear_screen() {
    // Sets the entire screen to spaces in our current color
    for (int i = 0; i < SCREEN_ROWS; i++) {
        memsetw(vga_mem + (i * SCREEN_COLS), 0x20 | (attribute << 8), SCREEN_COLS);
    }
    // Update virtual cursor, and then move the hardware cursor
    csr_x = 0;
    csr_y = 0;
    // update_cursor();
}

void init_video(void) {
    vga_mem = (unsigned short *)VIDEO_MEM_ADDR;
    clear_screen();
}

void print_string_top_left(char *str) {
    write_to_video_memory(str, 0x04, 0, 0);
}

int main() {
    /* Screen cursor position: ask VGA control register (0x3d4) for bytes
     * 14 = high byte of cursor and 15 = low byte of cursor. */
    port_byte_out(0x3d4, 14); /* Requesting byte 14: high byte of cursor pos */
    /* Data is returned in VGA data register (0x3d5) */
    int position = port_byte_in(0x3d5);
    position = position << 8; /* high byte */

    port_byte_out(0x3d4, 15); /* requesting low byte */
    position += port_byte_in(0x3d5);

    /* VGA 'cells' consist of the character and its control data
     * e.g. 'white on black background', 'red text on white bg', etc */
    int offset_from_vga = position * 2;

    /* Now you can examine both variables using gdb, since we still
     * don't know how to print strings on screen. Run 'make debug' and
     * on the gdb console:
     * breakpoint kernel.c:21
     * continue
     * print position
     * print offset_from_vga
     */

    /* Let's write on the current cursor position, we already know how
     * to do that */
    char *vga = 0xb8000;
    vga[offset_from_vga] = 'X';
    vga[offset_from_vga + 1] = 0x0f; /* White text on black background */
    init_video();
    char *boot_success_msg = "masOSchism kernel v0.01 booted successfully.";
    print_string_top_left(boot_success_msg);
    // // putch('A');
    // // puts(boot_success_msg);
    // return 0; // If this line of code ever runs, we have a huge issue.
}

/* vim: set ts=4 sw=4 tw=0 noet : */
