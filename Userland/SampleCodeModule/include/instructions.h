#ifndef FUNCTIONS_H
#define FUNCTIONS_H



typedef struct
{
	char *name;
	void (*function)(int argc, char *argv[]);
} instruction;

#endif
