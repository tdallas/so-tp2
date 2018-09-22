#ifndef LIB_H
#define LIB_H

#include <stdint.h>
// C functions
// void *memset(void *destination, int32_t character, uint64_t length);
// void *memcpy(void *destination, const void *source, uint64_t length);

#define NULL 0

void *malloc(uint64_t lenght);
void free(void* adress);

//ASM functions
char *cpuVendor(char *result);
uint64_t getTimeRTC(uint64_t value);
void speakerOn(uint64_t freq);
void speakerOff(void);
void speakerBeep(void);
void delayLoop(uint64_t times);


#endif
