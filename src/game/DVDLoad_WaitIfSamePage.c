/* If the read lands on the same 1 KiB page as the previous one, spin until
 * 66 us have passed since it. Returns the number of spins. */
extern unsigned int g_dvdLastReadPage;
extern unsigned int g_dvdLastReadTick;
extern unsigned int OSGetTick(void);

#define OS_BUS_CLOCK (*(unsigned int *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMicroseconds(ticks) (((ticks) * 8) / (OS_TIMER_CLOCK / 125000))

int DVDLoad_WaitIfSamePage(unsigned int offset)
{
    int spins = 0;

    if (g_dvdLastReadPage == (offset >> 10)) {
        while (1) {
            if (OSTicksToMicroseconds(OSGetTick() - g_dvdLastReadTick) >= 0x42) {
                break;
            }
            spins++;
        }
    }
    return spins;
}
