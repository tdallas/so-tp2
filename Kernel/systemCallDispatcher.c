#include <stdint.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <lib.h>
#include <idtLoader.h>
#include <messageQueueADT.h>
#include <processes.h>
#include <scheduler.h>
#include <mutex.h>

static uint64_t _getTime(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _readChar(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _writeChar(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _beepSound(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _memalloc(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _clearBackGround(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _setBackGround(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _writePixel(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _setPixel(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _paintPixelBackGround(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _memFree(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _send(uint64_t pid, uint64_t msg, uint64_t length, uint64_t r8, uint64_t r9);
static uint64_t _receive(uint64_t pid, uint64_t dest, uint64_t length, uint64_t r8, uint64_t r9);
static uint64_t _execProcess(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _killProcess(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _listProcesses(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _setProcessForeground(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _mutexInit(uint64_t mutex, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _mutexUnlock(uint64_t mutex, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _mutexLock(uint64_t mutex, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _getPid(uint64_t mutex, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
static uint64_t _mutexClose(uint64_t mutex, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);


static uint64_t (*systemCall[])(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) = {_getTime,                         //0
																									   _readChar,                        //1
																									   _writeChar,                       //2
																									   _beepSound,                       //3
																									   _memalloc,                        //4
																									   _clearBackGround,                 //5
																									   _setBackGround,                   //6
																									   _writePixel,                      //7
																									   _setPixel,                        //8
																									   _paintPixelBackGround,             //9
																									   _memFree, // 10
																										 _send,	//11
																										 _receive, //12
																										 _execProcess, //13
																										 _killProcess, //14
																										 _listProcesses, //15
																										 _mutexInit, //16
																										 _mutexUnlock, //17
																										 _mutexLock, //18
																										 _setProcessForeground, //19
																										 _getPid, //20
																										 _mutexClose //21
																									   };


uint64_t systemCallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	return (*systemCall[rdi])(rsi, rdx, rcx, r8, r9);
}

static uint64_t _getTime(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	return getTimeRTC(rsi);
}

static uint64_t _readChar(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	if(!isProcessRunningInForeground())
		return 0;
	return getChar();
}

static uint64_t _writeChar(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	// if(!isProcessRunningInForeground())
	// 	return 0;
	printChar((unsigned char)rsi, (unsigned char)rdx, (unsigned char)rcx, (unsigned char)r8);
	return 1;
}

static uint64_t _beepSound(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	speakerBeep();
	return 1;
}

static uint64_t _memalloc(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	return (uint64_t)malloc(rsi);
}

static uint64_t _clearBackGround(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	if(!isProcessRunningInForeground())
		return 0;
	printBackGround();
	return 1;
}

static uint64_t _setBackGround(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	if(!isProcessRunningInForeground())
		return 0;
	setBackGroundColor((unsigned char)rsi, (unsigned char)rdx, (unsigned char)rcx);
	return 1;
}

static uint64_t _writePixel(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	if(!isProcessRunningInForeground())
		return 0;
	return printPixel((unsigned int)rsi, (unsigned int)rdx, (unsigned char)rcx, (unsigned char)r8, (unsigned char)r9);
}

static uint64_t _setPixel(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	if(!isProcessRunningInForeground())
		return 0;
	return setActualPixel((unsigned int)rsi, (unsigned int)rdx);
}

static uint64_t _paintPixelBackGround(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	if(!isProcessRunningInForeground())
		return 0;
	return paintPixelBackGroundColor((unsigned int)rsi, (unsigned int)rdx);
}

static uint64_t _memFree(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	free((void *)rsi);
	return 1;
}

static uint64_t _send(uint64_t pid, uint64_t msg, uint64_t length, uint64_t r8, uint64_t r9){
	int owner = getProcessPid(getCurrentProcess());
	sendMessage(getMessageQueue(pid), owner, (char*)msg, length);
	return 1;
}

static uint64_t _receive(uint64_t pid, uint64_t dest, uint64_t length, uint64_t r8, uint64_t r9){
	int owner = getProcessPid(getCurrentProcess());
	receiveMessage(getMessageQueue(owner), pid, (char*)dest, length);
	return 1;
}

static uint64_t _execProcess(uint64_t pointer, uint64_t argc, uint64_t argv, uint64_t name, uint64_t r9){
	process *p = createProcess(pointer, argc, argv, (char*)name);
	runProcess(p);
	return getProcessPid(p);
}

static uint64_t _killProcess(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	killProcess();
	return 1;
}

static uint64_t _listProcesses(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	printPIDS();
	return 1;
}

static uint64_t _setProcessForeground(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	setProcessForeground((int)rsi);
	return 1;
}

static uint64_t _mutexInit(uint64_t name, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	return mutexInit((void*)name);
}

static uint64_t _mutexLock(uint64_t mutex, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	return mutexLock((void*)mutex);
}

static uint64_t _mutexUnlock(uint64_t mutex, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	return mutexUnlock((void*)mutex);
}

static uint64_t _mutexClose(uint64_t mutex, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	return mutexClose((void*)mutex);
}

static uint64_t _getPid(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	process * p = getCurrentProcess();
	return getProcessPid(p);
}
