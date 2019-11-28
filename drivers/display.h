#ifndef __DISPLAY_H
#define __DISPLAY_H

extern void set_text_color(unsigned char foreground_color, unsigned char background_color);
extern unsigned short *index_into_VGA_mem(int x, int y);
extern void update_cursor(void);
extern void scroll(void);
extern void putch(char c);
extern void puts(unsigned char *string);
extern void clear_screen();
extern void init_video(void);
extern void write_to_video_memory(char *str, int color, int row, int col);
extern void print_string_top_left(char *str);

#endif
