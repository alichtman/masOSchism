// /**
//  * VGA Display Library
//  */

// #include "display.h"
// #include "ports.h"

// #define VIDEO_MEM_ADDR 0xb8000
// #define SCREEN_ROWS 25
// #define SCREEN_COLS 80

// #define BLACK 0x00
// #define BLUE 0x01
// #define GREEN 0x02
// #define CYAN 0x03
// #define RED 0x04
// #define MAGENTA 0x05
// #define BROWN 0x06
// #define LIGHT_GREY 0x07
// #define DARK_GREY 0x08
// #define LIGHT_BLUE 0x09
// #define LIGHT_GREEN 0x0A
// #define LIGHT_CYAN 0x0B
// #define LIGHT_RED 0x0C
// #define LIGHT_MAGENTA 0x0D
// #define LIGHT_BROWN 0X0E
// #define WHITE 0X0F

// /**
//  * Globals for pointer to attribute (foreground color in
//  * lowest 4 bits and background color in highest 3 bits), and cursor x and y coords.
//  */
// int attribute = WHITE;
// unsigned short *vga_mem = 0;
// int csr_x = 0, csr_y = 0;

// /**
//  * Set foreground and background color. The top 4 bytes are the background and
//  * the lower 4 bytes are the foreground color.
//  * @param foreground_color
//  * @param background_color
//  */
// void set_text_color(unsigned char foreground_color, unsigned char background_color) {
//     attribute = (background_color << 4) | (foreground_color & 0x0F);
// }

// /**
//  * Returns a pointer to the specified x,y index in VGA memory.
//  */
// unsigned short *index_into_VGA_mem(int x, int y) {
//     return vga_mem + x + (y * SCREEN_COLS);
// }

// /**
//  * Updates the hardware cursor (the blinking line on the screen) by sending a
//  * command to indices 14 and 15 in the CRT Control Register of the VGA controller.
//  * These are the high and low bytes of the index that control where the hardware
//  * cursor is to be 'blinking'. http://www.brackeen.com/home/vga
//  */
// void update_cursor(void) {
//     unsigned target_idx = csr_y * 80 + csr_x;
//     port_byte_out(0x3D4, 14);
//     port_byte_out(0x3D5, target_idx >> 8);
//     port_byte_out(0x3D4, 15);
//     port_byte_out(0x3D5, target_idx);
// }

// /**
//  * Scrolls the screen down a line by copying the data from lines 1-25 into rows
//  * 0-24 and then clearing row 25.
//  */
// void scroll(void) {
//     unsigned blank = 0x20 | (attribute << 8);
//     // If we're beyond the screen, we need to scroll up.
//     if (csr_y >= SCREEN_ROWS) {
//         // Move screen up by one line.
//         int new_start_screen_row = csr_y - SCREEN_ROWS + 1;
//         memcpy((unsigned char *)vga_mem, (unsigned char *)vga_mem + new_start_screen_row * SCREEN_COLS, (SCREEN_ROWS - new_start_screen_row) * SCREEN_COLS * 2);
//         // Clear last line.
//         memsetw(vga_mem + (SCREEN_ROWS - new_start_screen_row) * SCREEN_COLS, blank, SCREEN_COLS);
//         // Set cursor to last row.
//         csr_y = SCREEN_ROWS - 1;
//     }
// }

// /**
//  * Prints a single character to the screen.
//  * @param c
//  */
// void putch(char c) {
//     // Handle a backspace, by moving the cursor back one space
//     if (c == 0x08) {
//         if (csr_x != 0) {
//             csr_x--;
//         }
//     }
//     // Handle a tab by incrementing the cursor's x, but only
//     // to a point that will make it divisible by 8.
//     else if (c == 0x09) {
//         csr_x = (csr_x + 8) & ~(8 - 1);
//     }
//     // Handles a 'Carriage Return', which simply brings the
//     // cursor back to the left side.
//     else if (c == '\r') {
//         csr_x = 0;
//     }
//     // Handle a newline. Add line below and set the cursor at the left margin.
//     else if (c == '\n') {
//         csr_x = 0;
//         csr_y++;
//     }
//     // Any character greater than and including a space is a printable character.
//     else if (c >= ' ') {
//         *index_into_VGA_mem(csr_x, csr_y) = c | (attribute << 8); /* Character AND attributes: color */
//         csr_x++;
//     }

//     /* If the cursor has reached the edge of the screen's width, we
//     *  insert a new line in there */
//     if (csr_x >= 80) {
//         csr_x = 0;
//         csr_y++;
//     }

//     /* Scroll the screen if needed, and finally move the cursor */
//     scroll();
//     update_cursor();
// }

// /**
//  * Prints a string to the screen.
//  * @param string
//  */
// void puts(unsigned char *string) {
//     for (int i = 0; i < strlen(string); i++) {
//         putch(string[i]);
//     }
// }

// void clear_screen() {
//     // Sets the entire screen to spaces in our current color
//     for (int i = 0; i < SCREEN_ROWS; i++) {
//         memsetw(vga_mem + (i * SCREEN_COLS), 0x20 | (attribute << 8), SCREEN_COLS);
//     }
//     // Update virtual cursor, and then move the hardware cursor
//     csr_x = 0;
//     csr_y = 0;
//     update_cursor();
// }

// void init_video(void) {
//     vga_mem = (unsigned short *)VIDEO_MEM_ADDR;
//     clear_screen();
// }

// void write_to_video_memory(char *str, int color, int row, int col) {
//     volatile char *destination = (char *)VIDEO_MEM_ADDR + row + (25 * col);
//     int counter = 0;
//     while (*str) {
//         *(destination + counter) = *str;
//         *(destination + counter + 1) = color;
//         counter += 2;
//         str++;
//     }
// }

// void print_string_top_left(char *str) {
//     write_to_video_memory(str, 0x04, 0, 0);
// }
