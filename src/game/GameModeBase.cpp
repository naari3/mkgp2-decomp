/*
 * GameModeBase TU @ 0x800A07EC..0x800A0950 (size 0x164). NonMatching.
 *
 * Two virtual methods of the GameModeBase class:
 *   - GameModeBase_FrameUpdate  (0x800A07EC, size 0x80) — virtual int (this)
 *     dispatched at vtable[+0x8]; invokes scene->f1() at vtable[+0xC].
 *     Best objdiff: 93.44 % (8 cycles). Same instruction count, body
 *     diverges by CW 1.3.2 register-allocator choice for the intermediate
 *     `dat` variable: target homes it in r0, mwcc here homes it in r3,
 *     producing an early `mr r3, r0` + `cmpwi`/`li r3` pair instead of
 *     target's `cmplwi`/`li r0` + late `mr r3, r0` shape. No source
 *     formulation tried (int / unsigned / void* type; `register` keyword;
 *     block-local declaration; declaration-order swap; ternary; double-if;
 *     direct `if (lbl_806D10A0) RankLog(lbl_806D10A0)`) coalesces `dat`
 *     onto r0 while keeping the 9-instr 2-cmp shape mwcc emits for the
 *     target's `int dat = lbl; if (lbl==0) dat=0; if (dat) f(dat);`. Likely
 *     same family as `docs/notes/cw132-fp-decl-order-regalloc.md`'s GPR
 *     allocator quirk.
 *
 *   - GameModeBase_Dtor         (0x800A086C, size 0xE4) — virtual GameModeBase*
 *     (this, freeFlag); dispatched at vtable[+0x10]. Invokes scene->f0(1) at
 *     vtable[+0x8], clears self->scene + g_objCollChecker + lbl_806D10AC,
 *     calls fn_80190660 + Backup_PublishShadowCopy_Inline + lbl_806D10AC->f0(1) + fn_802C8B48(0),
 *     decrements g_playerData[0x198] (clamped at 0), then chains
 *     ObjectBase_Dtor (= dtor_8002CDF4) and optional MemoryManager_TimedFree
 *     (= dtor_8003AFB8) under the `freeFlag > 0` delete-self gate.
 *     Best objdiff: 99.47 % (same 8 cycles). Same instruction count; only
 *     diff is the GPR pair chosen for `g_playerData` base/value during the
 *     decrement: target uses base=r4, value=r3 (`addi r4, r3, @l; lbz r3,
 *     0x198(r4)`); mwcc here picks base=r3, value=r4. Tried pointer-local
 *     intermediate (`unsigned char *p = g_playerData; v = p[0x198]`),
 *     intermediate-value-only, and direct-array forms — all settle on the
 *     same allocator shape. Same CW register-allocator quirk family.
 *
 * TU shape: C++ source mirroring GameModeBase_FrameUpdate2.cpp (immediately
 * preceding entry @ 0x800A07B4) with `#pragma exceptions on` so CW 1.3.2
 * auto-emits the per-function extab/extabindex pair. Scene's method
 * declaration order (`f0`, `f1`, `f2`) keeps vtable offsets aligned with
 * FrameUpdate2's source: vtable[+0x8]=f0, [+0xC]=f1, [+0x10]=f2.
 *
 * Object configured as NonMatching: dtk falls back to the auto-split text
 * blob (`auto_GameModeBase_FrameUp_text.s` + `auto_GameModeBase_Dtor_text.s`)
 * so SHA-1 stays OK. This .cpp is the base for a future 100 % match attempt
 * once the CW 1.3.2 register-allocator shape is reproduced.
 */

struct Scene {
    virtual void f0(int);
    virtual int f1();
    virtual void f2();
};

struct GameModeBase {
    void *vtable;
    Scene *scene;
};

extern "C" {
extern void CardRegister_Session_Tick(void);
extern void fn_801A1280(void);
extern void RankLog_UpdatePerFrame(void *);
extern void *lbl_806D10A0;
extern int  g_objCollChecker;
extern void Backup_PublishShadowCopy_Inline(void);
extern void fn_80190660(void);
extern void fn_802C8B48(int);
extern void *dtor_8002CDF4(void *self, short freeFlag);  /* ObjectBase_Dtor */
extern void  dtor_8003AFB8(void *self);                  /* MemoryManager_TimedFree */
extern unsigned char g_playerData[0x1DC];
extern void *g_GameModeBaseVtable[5];
}

extern Scene *lbl_806D10AC;

#pragma exceptions on

extern "C" int GameModeBase_FrameUpdate(GameModeBase *self) {
    int ret;
    void *dat;
    if (self->scene == 0) {
        return 0;
    }
    CardRegister_Session_Tick();
    fn_801A1280();
    ret = self->scene->f1();
    dat = lbl_806D10A0;
    if (lbl_806D10A0 == 0) {
        dat = 0;
    }
    if (dat != 0) {
        RankLog_UpdatePerFrame(dat);
    }
    return ret;
}

extern "C" GameModeBase *GameModeBase_Dtor(GameModeBase *self, short freeFlag) {
    if (self != 0) {
        self->vtable = g_GameModeBaseVtable;
        if (self->scene != 0) {
            self->scene->f0(1);
        }
        self->scene = 0;
        g_objCollChecker = 0;
        fn_80190660();
        Backup_PublishShadowCopy_Inline();
        if (lbl_806D10AC != 0) {
            lbl_806D10AC->f0(1);
        }
        lbl_806D10AC = 0;
        fn_802C8B48(0);
        {
            unsigned char *p = g_playerData;
            unsigned char v = p[0x198];
            if ((signed char)v > 0) {
                p[0x198] = v - 1;
            }
        }
        dtor_8002CDF4(self, 0);
        if (freeFlag > 0) {
            dtor_8003AFB8(self);
        }
    }
    return self;
}

#pragma exceptions reset
