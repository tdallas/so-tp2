#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <constantPrints.h>
#include <stdlib.h>
#include <blobsFront.h>
#include <digitalTime.h>
#include <processExec.h>
#include <instructions.h>
#include <messageTest.h>

#define MAX_WORD_LENGTH 124
#define MAX_WORDS 32
#define BUFFERSIZE 1024

void shell();
int managingCases(char *option);
int changeTextColor(char *color);
int changeBackGroundColor(char *color);
int wichColor(char *color);
void exit();

extern int opCode();
extern int zeroDiv();

#endif
