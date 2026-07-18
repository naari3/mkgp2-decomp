/*
 * Frame per-frame service block @ 0x8002D7DC..0x8002DC7C (4 fns, 1 TU).
 *
 *   0x8002D7DC Frame_UpdatePerFrameState  (size 0x19C)
 *   0x8002D978 Frame_PostDrawOverlay      (size 0xC4)
 *   0x8002DA3C Frame_PostDraw_BackupBuffer (size 0x200)
 *   0x8002DC3C Frame_Begin                (size 0x40)
 *
 * Each fn is its own singleton dtk reversed-extab group; contiguous, so one
 * TU covers all four plus their extab (0x80005740..0x80005780) and
 * extabindex (0x8001F448..0x8001F478) ranges.
 *
 * Compiled with -lang=c++ (Vtable_CallSlot2 / SeqMenuScene precedent): the
 * pre/post-frame hook dispatch is a real virtual call (both vtable loads
 * through r12), which the CW 1.3.2 C front end never emits.
 *
 * Exceptions stay off (cflags default); all extab/extabindex entries are
 * manual .extab_user emits (auto_ONKARTHIT_block.c approach-B pattern),
 * because Frame_PostDraw_BackupBuffer needs the inline-expanded ScopedTimer
 * DESTROYLOCAL extab which CW only auto-emits from real scoped C++ objects.
 * The ScopedTimer (slot 0x15) dtor tail uses the Phase 2d one-expression
 * recipe (docs/notes/cw132-scopedtimer-phase2d-research.md): the ticks->us
 * conversion must stay nested in the Profiler_RecordFrame argument (an
 * `unsigned int us` temp flips the scheduler to lwz-before-subi).
 */

struct FrameHook {
    virtual void vf08();
    virtual void vf0c(); /* +0x0C: per-frame hook entry */
};

extern "C" {

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* 0x14-byte stat block; Frame_PostDrawOverlay prints two of them. */
typedef struct FrameStatBlock {
    u32 w0, w4, w8, wC, w10;
} FrameStatBlock;

/* 0x60-byte I/O snapshot @ .bss:0x80594080, copied from fn_80293BBC's
 * result every frame. */
typedef struct FrameIOSnapshot {
    u16 h0, h2, h4, h6;   /* 0x00 */
    u32 w8[2];            /* 0x08 */
    u8 b10, b11;          /* 0x10 */
    u16 h12, h14, h16;    /* 0x12 */
    FrameStatBlock statA; /* 0x18 */
    FrameStatBlock statB; /* 0x2C */
    u32 w40[7];           /* 0x40 */
    u32 w5C;              /* 0x5C */
} FrameIOSnapshot;

typedef struct Color4 {
    u8 r, g, b, a;
} Color4;

/* 0x200 draw context @ .bss:0x806CD140 (fade/clear color at +0x48). */
typedef struct DrawCtx {
    char pad0[0x48];
    Color4 color48; /* 0x48 */
} DrawCtx;

/* Two frame-hook objects @ .sdata:0x806CED28. */
typedef struct FrameHookPair {
    FrameHook *begin; /* +0: called by Frame_Begin */
    FrameHook *post;  /* +4: called by Frame_PostDraw_BackupBuffer */
} FrameHookPair;

extern void *Sci2Card_Singleton_Get(void);
extern void Sci2Card_Tick(void *card);
extern void fn_802554DC(void);
extern FrameIOSnapshot *fn_80293BBC(void);
extern u32 OSGetTick(void);
extern void **GetInputManager(void);
extern void InputObj_TickAndDispatch(void **mgr);
extern void *StrPcb_GetInstance(void);
extern void StrPcb_OutputTick(void *pcb);
extern void fn_80193624(void);
extern void FrameUpdate(void);
extern void CreditMgr_PollInsertAndPlay(int arg);
extern void OverlayText(int, int, int, const char *, ...);
extern void GX_DrawDoneAndWait(void);
extern void fn_8018F14C(void);
extern void fn_802D5228(int arg);
extern void fn_802D53A4(void);
extern void fn_8025EF58(void);
extern void fn_802687F8(void);
extern void fn_802D47E8(void);
extern void SpriteHandlePool_GC(void);
extern void DebugPrintf(const char *, ...);
extern u32 fn_80267DF0(int w, int h, int fmt, int a, int b);
extern void fn_80266F04(int x, int y, int w, int h);
extern void fn_80266FB4(int w, int h, int fmt, int a);
extern void fn_80267628(unsigned char *buf, int arg);
extern void Profiler_RecordFrame(int slot, float ms);
extern void fn_802D4748(int arg);
extern void __dt__11ScopedTimerFv(void);

extern u8 lbl_806D0F8E;
extern u8 lbl_806D0F94;
extern u8 lbl_806D0F98;
extern u32 *lbl_806D0F9C;
extern FrameIOSnapshot lbl_80594080;
extern DrawCtx lbl_806CD140;
extern FrameHookPair lbl_806CED28;
extern u8 lbl_806CED30;
extern u32 lbl_806CED34;
extern unsigned char lbl_804FE080[0x1F748]; /* backup framebuffer */
extern const char lbl_802E950C[]; /* "not aligned" debug string */
extern const char lbl_802E9538[]; /* "too large" debug string */
extern const char lbl_802E9568[]; /* overlay fmt A */
extern const char lbl_802E9578[]; /* overlay fmt B */
extern const float lbl_806D2294;  /* ticks->ms divisor */

/* --- manual extab emit (.extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Frame_UpdatePerFrameState[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_Frame_PostDrawOverlay[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const struct {
    u32 f0; u32 f1; u32 f2; u32 f3; u32 f4; u32 f5; u32 f6; u32 f7; u32 f8; void *f9;
} extab_Frame_PostDraw_BackupBuffer = {
    0x000A0000, 0x00000070, 0x00000020, 0x000000E4, 0x00080020,
    0x00000174, 0x00090020, 0x00000000, 0x82000008,
    (void *)&__dt__11ScopedTimerFv
};
__declspec(section ".extab_user") static const unsigned char extab_Frame_Begin[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- manual extabindex emit (.extabindex_user -> extabindex via objcopy) --- */
void Frame_UpdatePerFrameState(void);
void Frame_PostDrawOverlay(void);
void Frame_PostDraw_BackupBuffer(void);
void Frame_Begin(void);

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; u32 fn_size; void *extab; } extabindex_Frame_UpdatePerFrameState = {
    (void *)&Frame_UpdatePerFrameState, 0x0000019C, (void *)extab_Frame_UpdatePerFrameState
};
__declspec(section ".extabindex_user") static const struct { void *fn; u32 fn_size; void *extab; } extabindex_Frame_PostDrawOverlay = {
    (void *)&Frame_PostDrawOverlay, 0x000000C4, (void *)extab_Frame_PostDrawOverlay
};
__declspec(section ".extabindex_user") static const struct { void *fn; u32 fn_size; void *extab; } extabindex_Frame_PostDraw_BackupBuffer = {
    (void *)&Frame_PostDraw_BackupBuffer, 0x00000200, (void *)&extab_Frame_PostDraw_BackupBuffer
};
__declspec(section ".extabindex_user") static const struct { void *fn; u32 fn_size; void *extab; } extabindex_Frame_Begin = {
    (void *)&Frame_Begin, 0x00000040, (void *)extab_Frame_Begin
};

/* --- function bodies (.text order = fn address order) --- */

void Frame_UpdatePerFrameState(void) { /* 0x8002D7DC size:0x19C */
    void *card;
    u32 *tickDst;
    u8 doTick;

    card = Sci2Card_Singleton_Get();
    if (card != 0) {
        if (lbl_806D0F94 == 0) {
            doTick = 0;
        } else if (lbl_806D0F98 == 1) {
            doTick = 0;
        } else {
            doTick = 1;
        }
        if (doTick == 1) {
            Sci2Card_Tick(card);
        }
    }
    fn_802554DC();
    lbl_80594080 = *fn_80293BBC();
    tickDst = lbl_806D0F9C;
    *tickDst = OSGetTick();
    {
        void **mgr = GetInputManager();
        if (mgr != 0) {
            InputObj_TickAndDispatch(mgr);
        }
    }
    {
        void *pcb = StrPcb_GetInstance();
        if (pcb != 0) {
            StrPcb_OutputTick(pcb);
        }
    }
    fn_80193624();
    FrameUpdate();
    CreditMgr_PollInsertAndPlay(0);
}

void Frame_PostDrawOverlay(void) { /* 0x8002D978 size:0xC4 */
    if (lbl_806D0F8E == 1) {
        OverlayText(1, 12, 0x1C, lbl_802E9568, &lbl_80594080.statA);
        OverlayText(1, 12, 0x1D, lbl_802E9578, &lbl_80594080.statB);
    }
    GX_DrawDoneAndWait();
    fn_8018F14C();
    {
        u32 v = lbl_806CED34;
        lbl_806CD140.color48 = *(Color4 *)&v;
    }
    fn_802D5228(0);
    fn_802D53A4();
    fn_8025EF58();
    fn_802687F8();
}

void Frame_PostDraw_BackupBuffer(void) { /* 0x8002DA3C size:0x200 */
    struct {
        u32 start;       /* sp+0x8 */
        volatile u32 id; /* sp+0xC */
    } tm;
    FrameHook *hook;

    fn_802D47E8();
    SpriteHandlePool_GC();
    hook = lbl_806CED28.post;
    if (hook != 0) {
        hook->vf0c();
    }
    if (lbl_806CED30 == 1) {
        tm.id = 0x15;
        tm.start = OSGetTick();
        if (((u32)lbl_804FE080 & 0x1F) != 0) {
            DebugPrintf(lbl_802E950C);
            Profiler_RecordFrame(
                tm.id,
                (float)(((OSGetTick() - tm.start) * 8) /
                        ((*(u32 *)0x800000F8 / 4) / 125000)) /
                    lbl_806D2294);
        } else if (fn_80267DF0(0x280, 0x1E0, 4, 0, 0) > 0x96000) {
            DebugPrintf(lbl_802E9538);
            Profiler_RecordFrame(
                tm.id,
                (float)(((OSGetTick() - tm.start) * 8) /
                        ((*(u32 *)0x800000F8 / 4) / 125000)) /
                    lbl_806D2294);
        } else {
            fn_80266F04(0, 0, 0x280, 0x1E0);
            fn_80266FB4(0x280, 0x1E0, 4, 0);
            fn_80267628(lbl_804FE080, 0);
            Profiler_RecordFrame(
                tm.id,
                (float)(((OSGetTick() - tm.start) * 8) /
                        ((*(u32 *)0x800000F8 / 4) / 125000)) /
                    lbl_806D2294);
        }
    }
}

void Frame_Begin(void) { /* 0x8002DC3C size:0x40 */
    FrameHook *hook;

    hook = lbl_806CED28.begin;
    if (hook != 0) {
        hook->vf0c();
    }
    fn_802D4748(0);
}

} /* extern "C" */
