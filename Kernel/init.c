#include "init.h"
#include "scheduler.h"
#include "videoDriver.h"
#include "processes.h"
#include "lib.h"

static void *const sampleCodeModuleAddress = (void *)0x400000;

void init()
{
	process *shell = createProcess((uint64_t)sampleCodeModuleAddress, 0,0, "shell");
	setProcessForeground(shell->pid);
	runProcess(shell);

	while (1)
	{
		_hlt();
	}
}
