/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() { }

void write_to_video_memory(char* str, char *video_mem_addr) {
	while (*str) {
		*video_mem_addr = *str;
		str++;
		video_mem_addr += 2;
	}
	return;
}

void main() {
	char* str = "HELLO FROM THE KERNEL";
	write_to_video_memory(str, (char*) 0xb8000);
}


