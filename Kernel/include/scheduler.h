#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "processes.h"
#include "genericQueue.h"
#include "defs.h"

#define MAX_PROCESSES 32
#define QUANTUM 1

typedef struct node
{
	int quantum;
	process *p;
	struct node *next;
} nodeList;

typedef struct blockedProcess
{
	process* process;
	int semId;
	int isMutex;
	struct blockedProcess *next;
} blockedProcess;

typedef struct blockedProcess* blockedProcessADT;
void printBlockedProcessesList();

uint64_t nextProcess(uint64_t current_rsp);

uint64_t runProcess(process * new_process);
void killProcess();
void yieldProcess();

void _changeProcess(uint64_t rsp);
void _yieldProcess();

process * getCurrentProcess();

void increaseQuantum();
void decreaseQuantum();

void block(queueADT queue);
void unblock(queueADT queue);


#endif
