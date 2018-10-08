#ifndef MUTEX_H
#define MUTEX_H

void * mutexInit(char *name);

int mutexLock(void * mutex);

int mutexUnlock(void * mutex);

int mutexClose(void* mutex);

#endif
