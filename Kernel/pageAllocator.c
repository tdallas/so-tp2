#include <stdint.h>
#include <stdio.h>
#include "videoDriver.h"
#include "pageAllocator.h"

static uint64_t size = 1;

static uint64_t pageStack[PAGE_QTY];
static uint64_t availablePage = 0;
static int indexInStack = 0;

static uint64_t megasStack[MAX_PROCESSES];
static uint64_t stackPageIndex = 0;
static uint64_t availableStackPage = 0;

static uint64_t reserved = 0;
static uint64_t reservedStack = 0;

extern uint8_t endOfKernel;

void restorePages();

void initializePageAllocator()
{
	uint64_t ram = *((uint64_t *)SYSTEM_RAM_ADDRESS);
	size = (ram * MB) / PAGE_SIZE;
	reserved = (uint64_t)&endOfKernel / (PAGE_SIZE);
	availablePage = (reserved + 2);
	reservedStack = (availablePage + PAGE_QTY) * PAGE_SIZE;
	availableStackPage = reservedStack;
}

uint64_t getStackPage()
{
	if (stackPageIndex != 0)
	{
		uint64_t stackpage = megasStack[stackPageIndex];
		stackPageIndex--;
		return stackpage;
	}
	else if (availableStackPage < (MAX_PROCESSES * MB + reservedStack))
	{
		uint64_t stackpage = availableStackPage;
		availableStackPage += MB;
		return stackpage;
	}
	else
	{
		//out of 2mb pages
		printString("OUT OF MEMORY\n", 0, 155, 255);
		while (1);
	}
}

void releaseStackPage(uint64_t stackpage)
{
	stackPageIndex++;
	if (stackPageIndex < MAX_PROCESSES)
	{
		megasStack[stackPageIndex] = stackpage;
	}
}

uint64_t peekAvailableStackPage()
{
	if (stackPageIndex != 0)
	{
		uint64_t stackpage = megasStack[stackPageIndex];
		return stackpage;
	}
	else if (availableStackPage < (MAX_PROCESSES + reservedStack))
	{
		uint64_t stackpage = availableStackPage * MB;
		return stackpage;
	}
	else
	{
		printString("OUT OF MEMORY\n", 0, 155, 255);
		while (1);
	}
}
uint64_t getAvailablePage()
{
	if (indexInStack != 0)
	{
		uint64_t page = pageStack[indexInStack];
		indexInStack--;
		return page;
	}
	else if (availablePage < (PAGE_QTY + reserved + 1))
	{
		uint64_t page = availablePage * PAGE_SIZE;
		availablePage++;
		return page;
	}
	else
	{
		//out of 4k pages
		printString("OUT OF MEMORY\n", 0, 155, 255);
		while (1);
	}
}
uint64_t peekAvailablePage()
{
	if (indexInStack != 0)
	{
		uint64_t page = pageStack[indexInStack];
		return page;
	}
	else if (availablePage < (PAGE_QTY + reserved + 1))
	{
		uint64_t page = availablePage * PAGE_SIZE;
		return page;
	}
	else
	{
		printString("OUT OF MEMORY\n", 0, 155, 255);
		while (1);
	}
}
void releasePage(uint64_t page)
{
	indexInStack++;
	if (indexInStack < PAGE_QTY)
	{
		pageStack[indexInStack] = page;
	}
}

int getIndexInStack()
{
	return indexInStack;
}

uint64_t getAvailableIndex()
{
	return availablePage;
}