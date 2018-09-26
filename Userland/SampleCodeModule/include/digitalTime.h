#ifndef DIGITAL_TIME_H
#define DIGITAL_TIME_H

#include <stdio.h>
#include <font.h>
#include <time.h>

void startDigitalTime();
void printMark();
void printHour(int time[7]);
void printMinute(int time[7]);
void printSecond(int time[7]);
void printBigChar(unsigned char c, unsigned int xPos, unsigned int yPos, unsigned char red, unsigned char green, unsigned char blue);
void printCharBlock(unsigned int fromX, unsigned int fromY, unsigned char red, unsigned char green, unsigned char blue);
void printCharBlockBackGround(unsigned int fromX, unsigned int fromY);
void changeColor();

#endif