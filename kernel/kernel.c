#include "display.c"

int main() {
    /* clear_screen(); */
    char* hello = "HELLO FROM THE KERNEL!";
	print_string_top_left(hello);
	return 0; // If this line of code ever runs, we have a huge issue.
}


/* vim: set ts=4 sw=4 tw=0 noet : */
