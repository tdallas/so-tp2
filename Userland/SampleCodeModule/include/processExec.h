
#ifndef EXECPROCESS_H_
#define EXECPROCESS_H_
int execProcess(void* function,int argc, char** argv, char* name, int foreground);
void sysSetForeground(int pid);
void sysKillProcess();
void printPids();
#endif
