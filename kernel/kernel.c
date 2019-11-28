#include "../drivers/display.h"
#include "system.h"

int main() {
    init_video();
    char *boot_success_msg = "masOSchism kernel v0.01 booted successfully.";
    print_string_top_left(boot_success_msg);
    // // putch('A');
    // // puts(boot_success_msg);
    // return 0; // If this line of code ever runs, we have a huge issue.
}

/* vim: set ts=4 sw=4 tw=0 noet : */
