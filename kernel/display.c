/**
 * Writes a string to the screen starting at x, y with a background and foreground
 * color. The lowest 4 bits are the foreground color, and the highest 3 bits
 * are for the background color. Color table available here: https://wiki.osdev.org/Printing_To_Screen
 */
void write_to_video_memory(char* str, int color, int row, int col) {
	volatile char* video_mem_addr = (char*) 0xb8000;
	volatile char* destination = video_mem_addr + row + (25 * col);
	int counter = 0;
	while (*str) {
		*(destination + counter) = *str;
		*(destination + counter + 1) = color;
		counter += 2;
		str++;
	}
}


void print_string_top_left(char* str) {
	write_to_video_memory(str, 4, 0, 0);
}


void clear_screen() {
	for (int col = 0; col < 25; col++) {
		for (int row = 0; row < 80; row++) {
			write_to_video_memory(" ", (int) 0xAAA << 16, row, col);
		}
	}
}
