#include "processes.h"
#include "defs.h"
#include "lib.h"
#include "pageAllocator.h"
#include "mutex.h"
#include "scheduler.h"
#include "videoDriver.h"
#include "messageQueueADT.h"

static void freeDataPages(process *p);

static process *processesTable[MAX_PROCESSES] = {NULL};
static process *foreground = NULL;

static uint64_t processesNumber = 0;

messageQueueADT getMessageQueue(int pid){
  return getProcessByPid(pid)->messageQueue;
}

int insertProcess(process *p)
{
  int i;

  for (i = 0; i < MAX_PROCESSES; i++)
  {
    if (processesTable[i] == NULL)
    {
      processesNumber++;
      p->pid = i;
      processesTable[i] = p;
      return i;
    }
  }

  return -1;
}

process *createProcess(uint64_t newProcessRIP, uint64_t argc, uint64_t argv, const char *name)
{
  process *newProcess = (process *)malloc(sizeof(*newProcess));
  strcpyKernel(newProcess->name, name);
  newProcess->stackPage = getStackPage();
  newProcess->status = READY;
  newProcess->rsp = createNewProcessStack(newProcessRIP, newProcess->stackPage, argc, argv);
  setNullAllProcessPages(newProcess);
  insertProcess(newProcess);
  newProcess->messageQueue = newMessageQueue(newProcess->pid);

  if (newProcess->pid != 0)
  {
    newProcess->ppid = getProcessPid(getCurrentProcess());
  }
  else
  {
    /* Pone en foreground al primer proceso */
    foreground = newProcess;
    newProcess->ppid = 0;
  }

  return newProcess;
}

process *getProcessByPid(uint64_t pid)
{
  if (pid < MAX_PROCESSES && processesTable[pid] != NULL && !isProcessDeleted(processesTable[pid]))
  {
    return processesTable[pid];
  }

  return NULL;
}

void setNullAllProcessPages(process *process)
{
  int i;

  for (i = 0; i < MAX_DATA_PAGES; i++)
  {
    process->dataPage[i] = NULL;
  }

  process->dataPageCount = 0;
}

void removeProcess(process *p)
{

  if (p != NULL)
  {
    processesNumber--;
    freeDataPages(p);
    if (foreground == p){
      setProcessForeground(processesTable[p->ppid]->pid);

    }
    processesTable[p->pid] = NULL;
    free((void *)p->stackPage);
    free((void *)p);
    free((void *)p->messageQueue);

  }
}

/* Libera las páginas de datos usadas por el proceso. */
static void freeDataPages(process *p)
{
  int i;

  for (i = 0; i < MAX_DATA_PAGES && p->dataPageCount > 0; i++)
  {
    if (p->dataPage[i] != NULL)
    {
      free((void *)p->dataPage[i]);
      p->dataPageCount -= 1;
    }
  }
}

void addDataPage(process *p, void *page)
{
  int i = 0;

  while (i < MAX_DATA_PAGES && p->dataPage[i] != NULL)
    i++;

  if (i < MAX_DATA_PAGES)
  {
    p->dataPageCount += 1;
    p->dataPage[i] = page;
  }
}

void exitShell()
{
  process *shell = getProcessByPid(1);
  shell->status = DELETE;
}

int deleteThisProcess(int pid)
{
  if (pid != 0 && pid != 1)
  {
    return deleteProcess(getProcessByPid(pid));
  }
  return 0;
}

int deleteProcess(process *p)
{
  if (p != NULL && p->pid != 1 && p->pid != 0)
    p->status = DELETE;

  return p != NULL;
}

int isProcessDeleted(process *p)
{
  if (p != NULL)
    return p->status == DELETE;
  return 0;
}

void setProcessRsp(process *p, uint64_t rsp)
{
  if (p != NULL)
    p->rsp = rsp;
}

uint64_t getProcessRsp(process *p)
{
  if (p != NULL)
    return p->rsp;
  return -1;
}

uint64_t getProcessPid(process *p)
{
  if (p != NULL)
    return p->pid;
  return -1;
}

uint64_t getProcessPpid(process *p)
{
  if (p != NULL)
    return p->ppid;
  return -1;
}

void blockProcess(process *p)
{
  if (p != NULL && p->status != DELETE)
  {
    p->status = BLOCKED;
  }
}

void unblockProcess(process *p)
{
  if (p != NULL && p->status != DELETE)
    p->status = READY;
}

int isProcessBlocked(process *p)
{
  if (p != NULL)
    return p->status == BLOCKED;
  return 1;
}

void setProcessForeground(int pid)
{
  process *p = getProcessByPid(pid);
  if (p != NULL)
  {
    foreground = p;

  }
}

int isProcessRunningInForeground()
{
  process *currentProcessRunning = getCurrentProcess();
  if (currentProcessRunning != NULL && foreground != NULL)
  {
    return currentProcessRunning->pid == foreground->pid;
  }
  else if ((currentProcessRunning == NULL) && (foreground == NULL))
  {
    return 1;
  }
  return 0;
}

process *getProcessForeground()
{
  return foreground;
}

uint64_t getProcessesNumber()
{
  return processesNumber;
}

/* Llena el stack para que sea hookeado al cargar un nuevo proceso
** https://bitbucket.org/RowDaBoat/wyrm */

uint64_t createNewProcessStack(uint64_t rip, uint64_t stackPage, uint64_t argc, uint64_t argv)
{
  stackFrame *newStackFrame = (stackFrame *)stackPage - 1;

  newStackFrame->gs = 0x001;
  newStackFrame->fs = 0x002;
  newStackFrame->r15 = 0x003;
  newStackFrame->r14 = 0x004;
  newStackFrame->r13 = 0x005;
  newStackFrame->r12 = 0x006;
  newStackFrame->r11 = 0x007;
  newStackFrame->r10 = 0x008;
  newStackFrame->r9 = 0x009;
  newStackFrame->r8 = 0x00A;
  newStackFrame->rsi = argv;
  newStackFrame->rdi = argc;
  newStackFrame->rbp = 0x00D;
  newStackFrame->rdx = 0x00E;
  newStackFrame->rcx = 0x00F;
  newStackFrame->rbx = 0x010;
  newStackFrame->rax = 0x011;
  newStackFrame->rip = rip;
  newStackFrame->cs = 0x008;
  newStackFrame->eflags = 0x202;
  newStackFrame->rsp = (uint64_t) & (newStackFrame->base);
  newStackFrame->ss = 0x000;
  newStackFrame->base = 0x000;

  return (uint64_t)&newStackFrame->gs;
}

void printPIDS()
{
  int i;
  for (i = 0; i < processesNumber; i++)
  {
    printString("PID: ", 0, 155, 255);
    printDec(processesTable[i]->pid);
    printString("\n", 0, 155, 255);

    printString("PPID: ", 0, 155, 255);
    printDec(processesTable[i]->ppid);
    printString("\n", 0, 155, 255);

    printString("Name: ", 0, 155, 255);
    printString(processesTable[i]->name, 0, 155, 255);
    printString("\n", 0, 155, 255);

    printString("Status: ", 0, 155, 255);
    char printStatus = processesTable[i]->status;
    if (printStatus == RUNNING)
    {
      printString("Running", 0, 155, 255);
    }
    else if (printStatus == READY)
    {
      printString("Ready", 0, 155, 255);
    }
    else if (printStatus == BLOCKED)
    {
      printString("Blocked", 0, 155, 255);
    }
    else if (printStatus == DELETE)
    {
      printString("Awaiting Deletion", 0, 155, 255);
    }
    else
    {
      printString("Error", 0, 155, 255);
    }
    printString("\n", 0, 155, 255);

    printString("Data Page: ", 0, 155, 255);
    printDec((uint64_t)processesTable[i]->dataPage);
    printString("\n", 0, 155, 255);

    printString("-------------------------------\n", 0, 155, 255);
  }
}

void whileTrue()
{
  while (1)
  {
    _hlt();
  }
}
