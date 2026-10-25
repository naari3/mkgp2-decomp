/*
 * PCB link debug overlay and link-error screen, 0x80085E3C..0x80086170.
 *
 * This TU owns the .rodata pool at 0x80311E38..0x803123B0. Both functions
 * address their strings off one section base, so the pool is defined here
 * in its original order (the leading float tables and lbl_80312234 are
 * used by other units).
 *
 * NonMatching: DebugOverlay_DumpPcbState keeps the listener in r27 where the
 * target reuses r25; everything else, including DrawLinkErrorOverlay, matches.
 */

typedef union PcbLinkFlags {
    struct {
        unsigned char disabled : 1, reserved6 : 1, ready : 1, flag4 : 1;
        unsigned char reserved3 : 4;
    } byte;
    struct {
        unsigned short upper : 6, id : 3, lower : 7;
    } half;
} PcbLinkFlags;

typedef struct PcbConnView {
    unsigned char pad_00[0x20];
    int field20;
    unsigned char pad_24[0x10];
    int portCycle;
    int closeCount;
} PcbConnView;

typedef struct PcbLinkSlot {
    union {
        unsigned int word;
        struct {
            unsigned char unused7 : 1;
            unsigned char team : 3;
            unsigned char unusedLow : 4;
        } bits;
    } hdr;
    unsigned char pad_04[0xA28];
    PcbConnView *primary;
    PcbConnView *secondary;
    PcbLinkFlags flags;
    unsigned char pad_A36[2];
    signed char readIndex;
    signed char writeIndex;
    unsigned char pad_A3A[2];
} PcbLinkSlot;

typedef struct PcbListenerView {
    unsigned char pad_00[0x18];
    int port;
} PcbListenerView;

typedef struct FKTex {
    unsigned char pad_00[0x18];
    int field18;
    int pad_1C;
    int field20;
    unsigned char pad_24[0x200];
} FKTex;

extern PcbLinkSlot lbl_805A6154[4];
extern unsigned char g_pcbCommEnabled;
extern unsigned char lbl_806D1191;
extern PcbListenerView *g_pcbListener;
extern int g_myPcbId;
extern const float lbl_806D3180;
extern const float lbl_806D3184;
extern const float lbl_806D3188;
extern const float lbl_806D318C;
extern const float lbl_806D3190;
extern const float lbl_806D3194;

extern void OverlayText(int layer, int x, int y, const char *fmt, ...);
extern const char *PcbListener_GetStateName(PcbListenerView *listener);
extern const char *PcbConn_GetStateName(PcbConnView *conn);
extern float DVDLoad_GetLastReadSec(void);
extern float DVDLoad_GetMaxReadSec(void);
extern void TexMgr_Init(FKTex *tex);
extern void TexMgr_SetTexture(FKTex *tex, const char *name, ...);
extern void fn_801F93EC(FKTex *tex, float x, float y);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *list, FKTex *tex, int flags);
extern int isJapanese(void);
extern void fn_8011F994(int arg);

const unsigned int lbl_80311E38[255] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
};
const unsigned int lbl_80312234[4] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
const char lbl_80312244[15] = "PCB ID : %d OK";
const char lbl_80312254[24] = "PCB ID : %d CHECKING...";
const char lbl_8031226C[23] = "S PCB %d : %s (port%d)";
const char lbl_80312284[35] = "C PCB %d : MY      %d : %02d (%2d)";
const char lbl_803122A8[49] = "C PCB %d : %s (P%d:O%d) %s %d:%02d (%02d) E%+04d";
const char lbl_803122DC[44] = "C PCB %d : %s (P%d:O%02d) NO recv socket %d";
const char lbl_80312308[23] = "ROM READ TIME : %f sec";
const char lbl_80312320[23] = "ROM READ MAX  : %f sec";
const char lbl_80312338[21] = "\x8C" "W" "\x88" "\xF5" "\x82" "\xF0" "\x8C" "\xC4" "\x82" "\xF1" "\x82" "\xC5" "\x82" "\xAD" "\x82" "\xBE" "\x82" "\xB3" "\x82" "\xA2";
const char lbl_80312350[26] = "Please call an attendant.";
const char lbl_8031236C[25] = "\x92" "\xCA" "\x90" "M" "\x83" "G" "\x83" "\x89" "\x81" "[" "\x82" "\xAA" "\x94" "\xAD" "\x90" "\xB6" "\x82" "\xB5" "\x82" "\xDC" "\x82" "\xB5" "\x82" "\xBD";
const char lbl_80312388[24] = "   Link error occurred.";
const char lbl_803123A0[14] = "PROCESS_ERROR";

#define PCB_CHAR_ID(s) (((s)->hdr.word >> 15) & 0xFF)

#pragma exceptions on
void DebugOverlay_DumpPcbState(void)
{
    PcbListenerView *listener;
    const char *secondaryName;
    int closeCount;
    int portCycle;
    PcbConnView *primary;
    PcbConnView *secondary;
    int i;
    int pending;
    int r;
    int w;

    if (g_pcbCommEnabled == 0) {
        return;
    }
    listener = g_pcbListener;
    if (listener != 0) {
        OverlayText(1, 0, 1, lbl_8031226C, g_myPcbId, PcbListener_GetStateName(listener), listener->port);
    }
    for (i = 0; i < 4; i++) {
        r = lbl_805A6154[i].readIndex;
        w = lbl_805A6154[i].writeIndex;
        for (pending = 0; w != r % 64; r++, pending++) {
        }
        if (lbl_805A6154[i].flags.byte.disabled == 1) {
            OverlayText(1, 0, i + 2, lbl_80312284, lbl_805A6154[i].flags.half.id,
                        lbl_805A6154[i].hdr.bits.team, PCB_CHAR_ID(&lbl_805A6154[i]), pending);
        } else {
            primary = lbl_805A6154[i].primary;
            if (primary != 0 && (secondary = lbl_805A6154[i].secondary) != 0) {
                closeCount = primary->closeCount;
                portCycle = primary->portCycle;
                secondaryName = PcbConn_GetStateName(secondary);
                OverlayText(1, 0, i + 2, lbl_803122A8, lbl_805A6154[i].flags.half.id,
                            PcbConn_GetStateName(lbl_805A6154[i].primary), portCycle, closeCount,
                            secondaryName, lbl_805A6154[i].hdr.bits.team,
                            PCB_CHAR_ID(&lbl_805A6154[i]), pending, secondary->field20);
            } else {
                OverlayText(1, 0, i + 2, lbl_803122DC, lbl_805A6154[i].flags.half.id,
                            PcbConn_GetStateName(primary), primary->portCycle,
                            primary->closeCount, lbl_805A6154[i].secondary);
            }
        }
    }
    OverlayText(1, 0, 7, lbl_80312308, DVDLoad_GetLastReadSec());
    OverlayText(1, 0, 8, lbl_80312320, DVDLoad_GetMaxReadSec());
}

int DrawLinkErrorOverlay(void)
{
    FKTex tex;

    if (lbl_806D1191 == 0) {
        return 0;
    }
    TexMgr_Init(&tex);
    tex.field18 = 1;
    tex.field20 = -1;
    fn_801F93EC(&tex, lbl_806D3180, lbl_806D3184);
    if (isJapanese() == 0) {
        TexMgr_SetTexture(&tex, lbl_80312338);
    } else {
        TexMgr_SetTexture(&tex, lbl_80312350);
        fn_801F93EC(&tex, lbl_806D3188, lbl_806D3184);
    }
    fn_801F8A34(fn_801F8E58(), &tex, 0);
    fn_801F93EC(&tex, lbl_806D318C, lbl_806D3190);
    if (isJapanese() == 0) {
        TexMgr_SetTexture(&tex, lbl_8031236C);
    } else {
        TexMgr_SetTexture(&tex, lbl_80312388);
        fn_801F93EC(&tex, lbl_806D3194, lbl_806D3190);
    }
    fn_801F8A34(fn_801F8E58(), &tex, 0);
    fn_8011F994(0);
    return 1;
}
#pragma exceptions reset
