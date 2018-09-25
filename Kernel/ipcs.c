#include <processes.h>
#include <ipcs.h>
#include <message.h>


void send(int pid, char * msg, int lenght){
  struct msg newMsg = {pid, msg, lenght};

}
