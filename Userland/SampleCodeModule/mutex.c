#include <systemCall.h>

void * mutexInit(char *name){
  return systemCall(16, name, 0,0,0,0);
}

int mutexLock(void * mutex){
  return systemCall(18, mutex, 0,0,0,0);
}

int mutexUnlock(void * mutex){
  return systemCall(17, mutex, 0,0,0,0);
}

int mutexClose(void * mutex){
  return systemCall(21, mutex, 0,0,0,0);
}
