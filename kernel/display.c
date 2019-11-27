/**
 * Display Library for VGA.
 */

#include "system.h"

#define VIDEO_MEM_ADDR 0xb8000
#define SCREEN_ROWS 25
#define SCREEN_COLS 80

#define BLACK 0x00
#define BLUE 0x01
#define GREEN 0x02
#define CYAN 0x03
#define RED 0x04
#define MAGENTA 0x05
#define BROWN 0x06
#define LIGHT_GREY 0x07
#define DARK_GREY 0x08
#define LIGHT_BLUE 0x09
#define LIGHT_GREEN 0x0A
#define LIGHT_CYAN 0x0B
#define LIGHT_RED 0x0C
#define LIGHT_MAGENTA 0x0D
#define LIGHT_BROWN 0X0E
#define WHITE 0X0F


/**
 * Globals for pointer to current text space, attribute (foreground color in
 * lowest 4 bits and background color in highest 3 bits), and cursor x and y coords.
 */
unsigned short *text_mem_ptr;
int attribute = LIGHT_BLUE;
int csr_x = 0, csr_y = 0;

/**
 * Writes a string to the screen starting at x, y with a background and foreground
 * color. The lowest 4 bits are the foreground color, and the highest 3 bits
 * are for the background color. Color table available here: https://wiki.osdev.org/Printing_To_Screen
 */
void write_to_video_memory(char *str, int color, int row, int col) {
	volatile char *destination = (char *) VIDEO_MEM_ADDR + row + (SCREEN_COLS * col);
	int counter = 0;
	while (*str) {
		*(destination + counter) = *str;
		*(destination + counter + 1) = color;
		counter += 2;
		str++;
	}
}

void print_string_top_left(char *str) {
	write_to_video_memory(str, 4, 0, 0);
}

void clear_screen() {
	// Sets the entire screen to spaces in our current color
	for (int i = 0; i < SCREEN_ROWS; i++) {
		memsetw(text_mem_ptr + i * SCREEN_COLS, 0x20 | (attribute << 8), SCREEN_COLS);
	}
	// Update out virtual cursor, and then move the hardware cursor
	csr_x = 0;
	csr_y = 0;
}

/**
 * Set text pointer to VGA memory and then clears the screen.
 */
void init_video(void) {
	text_mem_ptr = (unsigned short *) VIDEO_MEM_ADDR;
	clear_screen();
}
