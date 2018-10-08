#include "stdlib.h"
#include "shell.h"
#include "systemCall.h"
#include <exitProcess.h>

typedef void (*entry_point)(int, char **);
int sysExec(void *function, int argc, char **argv, char *name);
void sysSetForeground(int pid);

int execProcess(void *function, int argc, char **argv, char *name, int foreground)
{
	int pid = sysExec(function, argc, argv, name);
	if (foreground == 1)
	{
		sysSetForeground(pid);
	}
	return pid;
}

int sysExec(void *function, int argc, char **argv, char *name)
{
  return (uint64_t)systemCall(13, (uint64_t)function, argc, (uint64_t)argv, (uint64_t)name, 0);
}

void sysSetForeground(int pid)
{
  systemCall(19, (uint64_t)pid, 0, 0, 0, 0);
}

void sysKillProcess(){
	systemCall(14, 0, 0, 0, 0, 0);
}

int getPid(){
	return systemCall(20,0,0,0,0,0);
}

void printPids() {
	systemCall(15,0,0,0,0,0);
	exitProcess();
}
