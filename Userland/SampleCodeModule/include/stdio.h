#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <systemCall.h>

#define EOF 0
#define NULL 0
#define BUFFER_SIZE 128
#define INT_BUFFER_SIZE 12

void beepSound();
int abs(int a);
int getchar();
void setPixel(unsigned int x, unsigned int y);
void printPixelBackGroundColor(unsigned int x, unsigned int y);
void setBackGroundColor(unsigned int red, unsigned int blue, unsigned int green);
void setCharColor(unsigned int red, unsigned int blue, unsigned int green);
void putPixel(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue);
void putchar(unsigned char c);
void *malloc(long unsigned int size);
void free(void *pointer);
int printf(const char *str, ...);
int sscanf(const char *str, const char *format, ...);
int scanf(const char *format, ...);
int readLine(char buffer[BUFFER_SIZE]);
void clearWorkSpace();

#endif