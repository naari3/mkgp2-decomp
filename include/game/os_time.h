#ifndef GAME_OS_TIME_H
#define GAME_OS_TIME_H

typedef long long OSTime;

#ifdef __cplusplus
extern "C" {
#endif

extern OSTime OSGetTime(void);

#ifdef __cplusplus
}
#endif

#define OS_BUS_CLOCK (*(unsigned long *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))

#endif
