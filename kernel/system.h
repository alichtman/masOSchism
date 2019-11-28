#ifndef __SYSTEM_H
#define __SYSTEM_H

extern void *memcpy(char *dest, const char *src, int count);
extern void *memset(char *dest, char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb(unsigned short _port);
extern void outportb(unsigned short _port, unsigned char _data);

#endif
