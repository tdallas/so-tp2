#ifndef IPCS_H
#define IPCS_H

void send(int pid, char * msg, int lenght);

struct msg * receive(int pid);

#endif
