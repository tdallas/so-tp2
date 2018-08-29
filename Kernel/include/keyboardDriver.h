#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#define BUFFER_SIZE 128
#define EOF 0

extern int getKeyCode();
int getChar();
void keyboard_handler();

#endif