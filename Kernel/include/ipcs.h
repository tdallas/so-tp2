#ifndef IPCS_H
#define IPCS_H

void send(int pid, char * msg, int length);

struct msg * receive(int pid);

#endif
