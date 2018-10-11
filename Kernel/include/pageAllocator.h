#ifndef PAGEALLOCATOR_H_
#define PAGEALLOCATOR_H_

/*Address for size of ram*/
#define SYSTEM_RAM_ADDRESS 0x1000000

/*Paginas de 4k*/
#define PAGE_SIZE 0x1000

/*Stacks de 2MB*/
#define MB 0x100000

/*Size of 4k-pages stack*/
#define PAGE_QTY 511

#define DATA_ADDRESS 0x500000
/*Ending address for 4k pages*/
#define MEMORY_PAGES_END ((PAGE_QTY + 1) * PAGE_SIZE + DATA_ADDRESS)

/*Amount of 1mb processes given*/
#define MAX_PROCESSES 256

void initializePageAllocator();
uint64_t getAvailablePage();
void releasePage(uint64_t page);
uint64_t peekAvailablePage();
int getIndexInStack();
uint64_t getAvailableIndex();
uint64_t getStackPage();
void releaseStackPage(uint64_t stackpage);
uint64_t peekAvailableStackPage();

#endif