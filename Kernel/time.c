#include <time.h>

static unsigned long ticks = 0;

void timer_handler()
{
	ticks++;
}

int ticks_elapsed()
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / 18;
}

void seconds_delay(int seconds){
	int finalSecond = seconds_elapsed() + seconds;
	int actualSeconds;
	do{
		actualSeconds = seconds_elapsed();
	}while(actualSeconds<finalSecond);
}

void ticks_delay(int ticks){
	int finalTick = ticks_elapsed() + ticks;
	int actualTicks;
	do{
		actualTicks = ticks_elapsed();
	}while(actualTicks<finalTick);
}