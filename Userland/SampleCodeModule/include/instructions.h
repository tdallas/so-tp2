#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define CMD_SIZE 13

typedef struct
{
	char *name;
	void (*function)(int argc, char *argv[]);
} instruction;

#endif