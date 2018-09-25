#include <process.h>
#include <systemCall.h>

void execProcess(void * pointer, int argc, void * argv, char * name){
  systemCall(13, (uint64_t) pointer, (uint64_t)argc, (uint64_t)argv,
    (uint64_t)name, 0);
  }

void killProcess(){
  systemCall(14, 0, 0, 0, 0, 0);
}

void listProcesses(){
  systemCall(14, 0, 0, 0, 0, 0);
}
