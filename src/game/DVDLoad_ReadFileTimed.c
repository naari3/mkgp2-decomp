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

extern u32 lbl_806D1140; /* last read end sector (>> 10) */
extern u32 lbl_806D1144; /* tick of the last read */
extern float lbl_806D1148; /* last read seconds */
extern float lbl_806D114C; /* max read seconds */
extern void (*lbl_806D2238)(void *arg); /* idle callback while reading */

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
    if (lbl_806D1140 == info.startAddr >> 10) {
        while (OSTicksToMicroseconds(OSGetTick() - lbl_806D1144) < 66) {
        }
    }
    if (DVDReadAsyncPrio(&info, buf, len, offset, 0, 2) == 0) {
        return 0;
    }
    count = 16;
    start = OSGetTime();
    while (DVDGetCommandBlockStatus(&info) == 1) {
        if (--count < 0) {
            lbl_806D2238(arg);
            count = 16;
        }
    }
    lbl_806D1148 = (float)OSTicksToMilliseconds(OSGetTime() - start) / 1000.0f;
    lbl_806D2238(arg);
    lbl_806D1140 = end >> 10;
    lbl_806D1144 = OSGetTick();
    DVDClose(&info);
    if (lbl_806D114C <= lbl_806D1148) {
        lbl_806D114C = lbl_806D1148;
    }
    return 1;
}

#pragma exceptions reset
