#ifndef MESSAGES_H
#define MESSAGES_H

void send(int pid, char* msg, int length);
void receive(int pid, char* dest, int length);

#endif
