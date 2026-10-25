#ifndef GAME_OS_TIME_H
#define GAME_OS_TIME_H

typedef long long OSTime;

extern OSTime OSGetTime(void);

#define OS_BUS_CLOCK (*(unsigned long *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))

#endif
