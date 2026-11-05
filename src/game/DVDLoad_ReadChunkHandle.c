/* Narrow DVD file ABI view: the SDK aggregate header imports unavailable MSL headers. */
typedef unsigned long u32;
typedef signed long s32;
#include "game/DVDLoad_ReadChunkHandle_private.h"
extern int DVDReadAsyncPrio(DVDLoadFile *, void *, s32, s32, void *, int);
extern int DVDGetCommandBlockStatus(void *);
extern u32 OSGetTick(void);
#define OS_TIMER_CLOCK (*(volatile u32 *)0x800000F8 / 4)
extern u32 lbl_806D1140, lbl_806D1144;
extern void (*lbl_806D2238)(void *);
#pragma exceptions on
#pragma use_lmw_stmw on
int DVDLoad_ReadChunkHandle(DVDLoadFile *file, void *dst, s32 length, s32 offset, void *arg)
{
    u32 end = file->startAddr + file->length - 1;
    int countdown;
    if (lbl_806D1140 == (file->startAddr >> 10)) {
        while (((OSGetTick() - lbl_806D1144) * 8 / (OS_TIMER_CLOCK / 125000)) < 66) {}
    }
    if (!DVDReadAsyncPrio(file, dst, length, offset, 0, 2)) return 0;
    countdown = 16;
    while (DVDGetCommandBlockStatus(file) == 1) {
        if (--countdown < 0) {
            lbl_806D2238(arg);
            countdown = 16;
        }
    }
    lbl_806D2238(arg);
    lbl_806D1140 = end >> 10;
    lbl_806D1144 = OSGetTick();
    return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
