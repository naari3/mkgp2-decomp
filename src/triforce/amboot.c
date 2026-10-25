/* Triforce boot helpers: disk ID, render modes, reset with a save region. */
#include <dolphin.h>
#include <dolphin/dvd.h>
#include <string.h>

extern s32 fn_80286A74(DVDCommandBlock* block, u32 arg);
extern void fn_80286774(void);

static const GXRenderModeObj Mode0 = {
    24, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_DF, GX_FALSE, GX_FALSE,
    {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
    {0, 0, 21, 22, 21, 0, 0},
};

static const GXRenderModeObj Mode1 = {
    26, 640, 480, 480, 40, 0, 640, 480, VI_XFBMODE_SF, GX_FALSE, GX_FALSE,
    {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
    {0, 0, 21, 22, 21, 0, 0},
};

static const GXRenderModeObj* Modes[2] = {&Mode0, &Mode1};

BOOL fn_80287E34(void) {
    DVDCommandBlock block;
    DVDDiskID* id = DVDGetCurrentDiskID();

    memset(&block, 0, sizeof(block));
    memset(id, 0, sizeof(DVDDiskID));
    if (!DVDReadAbsAsyncPrio(&block, id, sizeof(DVDDiskID), 0, NULL, 2)) {
        return TRUE;
    }
    while (DVDGetCommandBlockStatus(&block)) {
    }
    return FALSE;
}

const GXRenderModeObj* fn_80287EC4(u32 i) {
    if (i >= 2) {
        return NULL;
    }
    return Modes[i];
}

s32 fn_80287EE4(u32 mode, void* save) {
    DVDCommandBlock block;
    s32 ret;
    void* end;
    void* src;

    memset(&block, 0, sizeof(block));
    if (mode == 1) {
        fn_80286A74(&block, 1);
    } else {
        fn_80286A74(&block, 0);
    }
    fn_80286774();
    GXAbortFrame();
    VISetBlack(TRUE);
    VIFlush();
    VIWaitForRetrace();
    if (save == NULL) {
        ret = 2;
    } else {
        end = (u8*)save + 0x100;
        if ((u32)save < 0x80700000 || (u32)save > 0x811FFF00) {
            end = (void*)0x81200000;
            src = save;
            save = (u8*)end - 0x100;
            memcpy(save, src, 0x100);
        }
        OSSetSaveRegion(save, end);
        ret = 0;
    }
    if (ret != 0) {
        return ret;
    }
    OSResetSystem(0, 0, 0);
    return 1;
}

s32 fn_80287FDC(void* buf) {
    void* start;
    void* end;

    if (buf == NULL) {
        return 2;
    }
    memset(buf, 0, 0x100);
    OSGetSavedRegion(&start, &end);
    if ((s32)end - (s32)start > 0) {
        memcpy(buf, start, 0x100);
    }
    return 0;
}
