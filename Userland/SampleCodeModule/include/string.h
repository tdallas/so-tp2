#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdio.h>

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, long unsigned int n);
int lowstrcmp(const char *s1, const char *s2);
void *memcpy(void *destination, const void *source, long unsigned int length);
void *memset(void *destiation, int c, long unsigned int length);
long unsigned int strlen(const char *str);
const char *strchr(const char *s, int c);
char *strncpy(char *destination, const char *source, long unsigned int n);
char *strcpy(char *destination, const char *source);


#endif