#ifndef TIME_H_
#define TIME_H_

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void seconds_delay(int seconds);
void ticks_delay(int ticks);

#endif