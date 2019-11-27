#include "system.h"

/**
 * Copies 'count' bytes of data from 'src' to 'dest'
 * @param dest  Destination address
 * @param src   Source adddress
 * @param count Number of bytes to copy
 * @return dest
 */
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count) {
	unsigned char *dest_cpy = dest;
	for (int i = 0; i < count; i++) {
		*dest_cpy = *src;
		src++;
		dest_cpy++;
	}
	return dest;
}

/**
 * Sets 'count' bytes from 'dest' to 'val'
 * @param dest
 * @param val
 * @param count
 * @return dest
 */
unsigned char *memset(unsigned char *dest, unsigned char val, int count) {
	char *dest_cpy = dest;
	for (int i = 0; i < count; i++) {
		*dest_cpy = val;
		dest_cpy++;
	}
	return dest;
}

/**
 * Same as above, but this time, we're working with a 16-bit 'val' and dest pointer.
 * @param dest
 * @param val
 * @param count
 * @return
 */
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count) {
	unsigned short *dest_cpy = dest;
	for (int i = 0; i < count; i++) {
		*dest_cpy = val;
		dest_cpy++;
	}
	return dest;
}

/**
 * Returns the length of a string in bytes.
 * @param str
 * @return
 */
int strlen(const char *str) {
	int len = 0;
	char* str_cpy = str;
	while (*str_cpy) {
		len++;
		str_cpy++;
	}
	return len;
}

/**
 * Read from I/O port to get data from devices, such as the the keyboard.
 * @param _port
 * @return
 */
unsigned char inportb(unsigned short _port) {
	unsigned char rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

/**
 * Write to I/O port to send data to devices.
 * @param _port
 * @param _data
 * @return
 */
void outportb(unsigned short _port, unsigned char _data) {
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}