#include <systemCall.h>

void send(int pid, char* msg, int length){
  systemCall(11, pid, msg, length,0,0);
}

void receive(int pid, char* msg, int length){
  systemCall(12, pid, msg, length,0,0);
}
