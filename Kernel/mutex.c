#include <stdint.h>
#include "mutex.h"
#include "lib.h"
#include "processes.h"
#include "scheduler.h"
#include "videoDriver.h"

static mutexADT *mutex;
static int id = 0;
static int numberOfMutexes = 0;

typedef struct mutex_t
{
	char* name;
	int value;
	int id;
	process* blockedProcesses[MAX_PROCESSES];
} mutex_t;

mutex_t *mutexInit(char *name)
{
	int i;
	for (i = 0; i < numberOfMutexes; i++)
	{
		if (strcmpKernel(name, mutex[i]->name) == 0)
		{
			return mutex[i];
		}
	}
	mutexADT newMutex = (mutexADT)malloc(sizeof(mutex_t));
	newMutex->name = (char *)malloc(strlenKernel(name) + 1);
	strcpyKernel(newMutex->name, name);
	newMutex->value = 1;
	newMutex->id = id;
	for(int i = 0; i < MAX_PROCESSES; i++)
	{
		newMutex->blockedProcesses[i] = NULL;
	}

	id++;
	numberOfMutexes++;
	mutex = (mutexADT *)malloc(numberOfMutexes * sizeof(mutexADT));
	mutex[numberOfMutexes - 1] = newMutex;
	return newMutex;
}

int mutexLock(mutex_t *mut)
{
	while(mut->value==0)
	{
		process *p = getCurrentProcess();
		blockProcess(p);
		mut->blockedProcesses[getProcessPid(p)]= p;
		yieldProcess();
	}
	mut->value = 0;
	return 0;
}

int mutexUnlock(mutex_t *mut)
{
	for(int i = 0; i < MAX_PROCESSES; i++){
		unblockProcess(mut->blockedProcesses[i]);
	}
	mut->value = 1;
	yieldProcess();
	return mut->value;
}

int mutexListSize()
{
	return numberOfMutexes;
}

int mutexClose(mutex_t *mut)
{
	int i;
	for (i = 0; i < numberOfMutexes; i++)
	{
		if (mutex[i]->id == mut->id)
		{
			free(mutex[i]->name);
			free(mutex[i]);

			int j;
			for (j = i; j < numberOfMutexes - 1; j++)
			{
				mutex[j] = mutex[j + 1];
			}

			numberOfMutexes--;

			return 0;
		}
	}
	return 1;
}

void closeAllMutex()
{
	int i;
	for (i = numberOfMutexes; i > 0; i--)
	{
		mutexClose(mutex[i]);
	}
}

void freeMutexList()
{
	free(mutex);
}
