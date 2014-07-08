/* 
 * File:   keyboard.h
 * Author: Jason
 *
 * Created on July 7, 2014, 2:10 PM
 *
 *
    BACKSPACE = 0x08
    TAB = 0x09
    CAP = 0x1c
    SHIFT = 0x1d
    ENTER = 0x0D
    SPACE = 0x20
 *
 * 
 */
#ifndef KEYBOARD_H
#define	KEYBOARD_H

#include "ft5206.h"

typedef struct _KB_KEY_ {
    unsigned int top;
    unsigned int left;
    unsigned int width;
    unsigned int height;
    char ascii;
} KB_Key;

typedef struct _Keyboard_ {
    unsigned int top;
    unsigned int left;
    unsigned int width;
    unsigned int text_color;
    unsigned int back_color;
    unsigned int edge_color;
    unsigned int key_width;
    unsigned int key_height;
    unsigned int height;
    char caps;
    char shift;
    KB_Key keys[128];
} Keyboard;

#define CAPS 2
#define SHIFT 1
#define NOSHIFT 0

Keyboard draw_kb(char isShift, unsigned int left, unsigned int top, unsigned int width, unsigned int ecolor, unsigned int bcolor, unsigned int tcolor);
Keyboard draw_no_shift(unsigned int left, unsigned int top, unsigned int width, unsigned int ecolor, unsigned int bcolor, unsigned int tcolor);
Keyboard draw_shift(unsigned int left, unsigned int top, unsigned int width, unsigned int ecolor, unsigned int bcolor, unsigned int tcolor);
unsigned int draw_keys(unsigned int top, unsigned int left, char key_scale, char *text);
unsigned int getLen (char *text);

char isKey(Keyboard kb, unsigned int left, unsigned int top);
#endif	/* KEYBOARD_H */

