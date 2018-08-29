#include <videoDriver.h>
#include <stdint.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_EXCEPTION_ID 6

static const char * registers[16] = { "RSP: ", "RAX: ", "RBX: ", "RCX: ", "RDX: ", "RBP: ", "RDI: ", "RSI: ", "R8: ", "R9: ", "R10: ", "R11: ", "R12: ", "R13: ", "R14: ", "R15: "};

static void zero_division(uint64_t *states);
static void invalid_op_code(uint64_t *states);
void printRegisters(uint64_t *states);

void exceptionDispatcher(uint64_t exception, uint64_t *states)
{
	if (exception == ZERO_EXCEPTION_ID)
		zero_division(states);
	else if (exception == INVALID_OP_CODE_EXCEPTION_ID)
		invalid_op_code(states);
}

static void zero_division(uint64_t *states)
{
	printString("ERROR: Division by zero exception.", 255, 255, 255);
	printRegisters(states);
}

static void invalid_op_code(uint64_t *states)
{
	printString("ERROR: Invalid opcode exception.", 255, 255, 255);
	printRegisters(states);
}

void printRegisters(uint64_t *states)
{
	newLine();
	for (int i = 0; i < 16; i++)
	{
		printString(registers[i], 255, 255, 255);
		printDec(states[i]);
		newLine();
	}
}