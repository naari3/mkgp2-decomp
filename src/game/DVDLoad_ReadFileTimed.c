/*
 * FUN_8007dfe4, 0x8007DFE4..0x8007E178: opens a DVD file, reads a range of
 * it with priority 2 while polling the callback, and records how long the
 * read took (DVDLoad_GetLastReadSec / DVDLoad_GetMaxReadSec).
 */

typedef unsigned long u32;
typedef long long s64;

typedef struct DVDFileInfo {
    unsigned char cb[0x30];
    u32 startAddr; /* 0x30 */
    u32 length;    /* 0x34 */
    unsigned char pad38[0x3C - 0x38];
} DVDFileInfo;

#define OS_BUS_CLOCK (*(u32 *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))
#define OSTicksToMicroseconds(ticks) ((ticks) * 8 / (OS_TIMER_CLOCK / 125000))

extern int DVDOpen(const char *path, DVDFileInfo *info);
extern int DVDClose(DVDFileInfo *info);
extern int DVDReadAsyncPrio(DVDFileInfo *info, void *buf, long len, long offset, void *cb, long prio);
extern long DVDGetCommandBlockStatus(void *block);
extern u32 OSGetTick(void);
extern s64 OSGetTime(void);

extern u32 g_dvdLastReadPage; /* last read end sector (>> 10) */
extern u32 g_dvdLastReadTick; /* tick of the last read */
extern float g_dvdLastReadSec; /* last read seconds */
extern float g_dvdMaxReadSec; /* max read seconds */
extern void (*g_dvdLoadCallback)(void *arg); /* idle callback while reading */

#pragma exceptions on

int FUN_8007dfe4(const char *path, void *buf, long len, long offset, void *arg)
{
    DVDFileInfo info;
    u32 end;
    int count;
    s64 start;

    if (DVDOpen(path, &info) == 0) {
        return 0;
    }
    end = info.startAddr + info.length - 1;
    if (g_dvdLastReadPage == info.startAddr >> 10) {
        while (OSTicksToMicroseconds(OSGetTick() - g_dvdLastReadTick) < 66) {
        }
    }
    if (DVDReadAsyncPrio(&info, buf, len, offset, 0, 2) == 0) {
        return 0;
    }
    count = 16;
    start = OSGetTime();
    while (DVDGetCommandBlockStatus(&info) == 1) {
        if (--count < 0) {
            g_dvdLoadCallback(arg);
            count = 16;
        }
    }
    g_dvdLastReadSec = (float)OSTicksToMilliseconds(OSGetTime() - start) / 1000.0f;
    g_dvdLoadCallback(arg);
    g_dvdLastReadPage = end >> 10;
    g_dvdLastReadTick = OSGetTick();
    DVDClose(&info);
    if (g_dvdMaxReadSec <= g_dvdLastReadSec) {
        g_dvdMaxReadSec = g_dvdLastReadSec;
    }
    return 1;
}

#pragma exceptions reset
