#ifndef MUTEX_H_
#define MUTEX_H_



typedef struct mutex_t* mutexADT;

mutexADT mutexInit(char *name);
int mutexLock(mutexADT mut);
int mutexUnlock(mutexADT mut);
int mutexListSize();
int mutexClose(mutexADT mut);
void closeAllMutex();
void freeMutexList();

#endif
