#ifndef PROCESSES_H
#define PROCESSES_H

#include <stdint.h>

#include "defs.h"
#include "mutex.h"
#include "messageQueueADT.h"

#define RUNNING 0
#define READY 1
#define BLOCKED 2
#define DELETE 3

#define MAX_DATA_PAGES 64
#define MAX_PROCESS_NAME 64

typedef struct
{
  char status;
  char name[MAX_PROCESS_NAME];
  uint64_t rsp;
  uint64_t stackPage;
  uint64_t dataPageCount;
  void *dataPage[MAX_DATA_PAGES];
  uint64_t pid;
  uint64_t ppid;
  messageQueueADT messageQueue;
} process;

typedef char status;

/* Tomado de
** https://bitbucket.org/RowDaBoat/wyrm
*/
typedef struct
{
  // Registers restore context
  uint64_t gs;
  uint64_t fs;
  uint64_t r15;
  uint64_t r14;
  uint64_t r13;
  uint64_t r12;
  uint64_t r11;
  uint64_t r10;
  uint64_t r9;
  uint64_t r8;
  uint64_t rsi;
  uint64_t rdi;
  uint64_t rbp;
  uint64_t rdx;
  uint64_t rcx;
  uint64_t rbx;
  uint64_t rax;

  // iretq hook
  uint64_t rip;
  uint64_t cs;
  uint64_t eflags;
  uint64_t rsp;
  uint64_t ss;
  uint64_t base;
} stackFrame;

messageQueueADT getMessageQueue(int pid);

process *createProcess(uint64_t rip, uint64_t argc, uint64_t argv, const char *name);
void removeProcess(process *p);

void setProcessRsp(process *p, uint64_t rsp);
uint64_t getProcessRsp(process *p);

void blockProcess(process *p);
void unblockProcess(process *p);
int isProcessBlocked(process *p);
uint64_t getProcessPid(process *p);
uint64_t getProcessPpid(process *p);
uint64_t getProcessesNumber();
mutexADT getTableMutexSingleton();
void lockTable();
void unlockTable();
uint64_t getProcessesNumber();
int insertProcess(process *p);
void setNullAllProcessPages(process *process);
uint64_t createNewProcessStack(uint64_t rip, uint64_t stackPage, uint64_t argc, uint64_t argv);
void exitShell();
process *getProcessByPid(uint64_t pid);
int isProcessRunningInForeground();

void setProcessForeground(int pid);
process *getProcessForeground();

int deleteThisProcess(int pid);
int deleteProcess(process *p);
int isProcessDeleted(process *p);

void addDataPage(process *p, void *page);

void printPIDS();
void whileTrue();
void _hlt();

#endif
