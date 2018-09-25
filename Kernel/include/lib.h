#ifndef LIB_H
#define LIB_H

#include <stdint.h>

#define NULL 0
// C functions
void *memset(void *destination, int32_t character, uint64_t length);
void *memcpy(void *destination, const void *source, uint64_t length);
int strcmpKernel(const char *s1, const char *s2);
int strlenKernel(const char *s);
void strcpyKernel(char *d, const char *s);
void strcatKernel(char *d, const char *s);

#define NULL 0

void *malloc(uint64_t length);
void free(void* adress);

//ASM functions
char *cpuVendor(char *result);
uint64_t getTimeRTC(uint64_t value);
void speakerOn(uint64_t freq);
void speakerOff(void);
void speakerBeep(void);
void delayLoop(uint64_t times);


#endif
