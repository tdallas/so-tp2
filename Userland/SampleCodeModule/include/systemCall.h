#ifndef SYSTEM_CALL_H
#define SYSTEM_CALL_H

#include <stdint.h>

uint64_t systemCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

#endif