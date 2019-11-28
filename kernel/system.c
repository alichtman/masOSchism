#include "system.h"

/**
 * Copies 'count' bytes of data from 'src' to 'dest'
 * @param dest  Destination address
 * @param src   Source adddress
 * @param count Number of bytes to copy
 * @return Starting address of destination.
 */
void *memcpy(char *dest, const char *src, int count) {
    char *dest_cpy = dest;
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
void *memset(char *dest, char val, int count) {
    char *dest_orig = dest;
    for (int i = 0; i < count; i++) {
        *dest = val;
        dest++;
    }
    return dest_orig;
}

/**
 * Same as above, but this time, we're working with a 16-bit 'val' and dest pointer.
 * @param dest
 * @param val
 * @param count
 * @return
 */
void *memsetw(unsigned short *dest, unsigned short val, int count) {
    unsigned short *dest_orig = dest;
    for (int i = 0; i < count; i++) {
        *dest = val;
        dest++;
    }
    return dest_orig;
}

/**
 * Returns the length of a string in bytes.
 * @param str
 * @return
 */
int strlen(const char *str) {
    int len = 0;
    while (*str) {
        len++;
        str++;
    }
    return len;
}
