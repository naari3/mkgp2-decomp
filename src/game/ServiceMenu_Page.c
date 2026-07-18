/*
 * ServiceMenu page object (GameMode page, vtable lbl_803FDE64).
 *
 *   ServiceMenu_Draw @ 0x80073B00 (size 0x38)
 *   ServiceMenu_Tick @ 0x80073B38 (size 0x78)
 *   ServiceMenu_Dtor @ 0x80073BB0 (size 0xC0)
 *   ServiceMenu_Init @ 0x80073C70 (size 0x1B0)
 *
 * The sibling TU game/ServiceMenu.c holds OpenFullServiceMenu (0x80073E7C),
 * the allocator wrapper that news up this object. The wedge fn
 * SmallObj_Dtor_VtableA (0x80073E20) sits between Init and
 * OpenFullServiceMenu, so the two TUs stay separate.
 *
 * All four functions carry extab/extabindex entries in the target. The TU is
 * built with the default -Cpp_exceptions off, so every entry is emitted
 * manually via the .extab_user/.extabindex_user + postprocess_extab_user.py
 * rename hook (same pattern as game/ServiceMenu.c).
 */

typedef struct ServiceMenu {
    void *vtbl;                  /* 0x000 - lbl_803FDE64 */
    int isJapanese;              /* 0x004 */
    int blinkTimer;              /* 0x008 - wraps at 0x32 */
    int clockTimer;              /* 0x00C - commits OperationClock at 0x258 */
    int pageId;                  /* 0x010 */
    int pageState;               /* 0x014 - 10 on boot-in path, 1 otherwise */
    int field_0x18;              /* 0x018 */
    int field_0x1C;              /* 0x01C */
    char pad_0x20[0x34 - 0x20];
    int field_0x34;              /* 0x034 - sign-extended byte lbl_80598A60[0x20] */
    int field_0x38;              /* 0x038 - set to -2 */
    char pad_0x3C[0x50 - 0x3C];
    unsigned char openedByExtra; /* 0x050 - 0 on boot-in (-1) path */
    char pad_0x51[0x5C - 0x51];
    unsigned char field_0x5C;    /* 0x05C - set when !(fn_8028B090() & 1) */
    char pad_0x5D[0x270 - 0x5D];
    void *displayCtx;            /* 0x270 - lbl_806D1880 */
    void *cfg;                   /* 0x274 - &lbl_80598A60 */
    char pad_0x278[0x288 - 0x278];
    int field_0x288;             /* 0x288 - set to 1 */
} ServiceMenu; /* size 0x28C */

/* --- callees --- */
extern void UI_PageDispatcher(ServiceMenu *self, int mode);
extern void DisplayContext_Flush(void *ctx);
extern void OperationClock_Commit(void);
extern void Sprite_Destroy(void *sprite, int flag);
extern void fn_801A0B70(int);
extern void SpriteSystem_EnsureInit(void);
extern void fn_80120A08(int resId);
extern void fn_801DB68C(void *ctx, int flag);
extern void PcbComm_Shutdown(void);
extern void FreeMediaBuffers(void);
extern void *dtor_8002CDF4(void *self, short freeFlag); /* ObjectBase_Dtor */
extern void MemoryManager_TimedFree(void *p);
extern void GameMode_BaseInit(void *self);
extern void InitGlobalTimer(void);
extern void PCBComm_Init(void);
extern void fn_801920D4(void);
extern void fn_801908F0(void);
extern void fn_8002CFB8(int, int, int, int);
extern int isJapanese(void);
extern void *Alloc(int size);
extern void DisplayContext_Init(void *ctx);
extern unsigned int fn_8028B090(void);
extern void PreloadResource(int resId);
extern void Backup_PublishShadowCopy_Inline(void);
extern void *StrPcb_GetInstance(void);
extern void StrPcb_ResetCommands_NeutralDefault(void *self);
extern void fn_801A0BB4(void);
extern void fn_801A08B8(void *spr, int id, int flag, float a, float b);

/* --- data --- */
extern char lbl_803FDE64[];          /* .data  - ServiceMenu vtable */
extern char lbl_80598A60[0x2A];      /* .bss   - config block */
extern void *g_pInputState;          /* .sbss */
extern void *lbl_806D1100;           /* .sbss  - banner sprite */
extern unsigned char lbl_806D117D;   /* .sbss */
extern void *lbl_806D1880;           /* .sbss  - display context */
extern float lbl_806D2E24;           /* .sdata2 */
extern float lbl_806D2E9C;           /* .sdata2 */

/* --- forward decls (for extabindex fn refs) --- */
void ServiceMenu_Draw(ServiceMenu *self);
int ServiceMenu_Tick(ServiceMenu *self);
void *ServiceMenu_Dtor(ServiceMenu *self, short freeFlag);
asm void ServiceMenu_Init(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) ---
 * Target layout @ 0x80008238..0x800082A0, address order Draw/Tick/Dtor/Init.
 */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
} extab_ServiceMenu_Draw = {
    /* r31 saved-GPR range, large frame, no actions */
    0x08080000, 0x00000000
};

__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
} extab_ServiceMenu_Tick = {
    /* r31 saved-GPR range, large frame, no actions */
    0x08080000, 0x00000000
};

__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
} extab_ServiceMenu_Dtor = {
    /* r30-r31 saved-GPR range, large frame, no actions */
    0x10080000, 0x00000000
};

__declspec(section ".extab_user") static const struct {
    unsigned int w0;   /* 0x180A0000 header (r29-r31, elf vector) */
    unsigned int w1;   /* PC range 0x3C..0x78 */
    unsigned int w2;   /* action 0x30 */
    unsigned int w3;   /* PC 0x84 */
    unsigned int w4;   /* action 0x28 */
    unsigned int w5;   /* PC range 0xD4..0x170 */
    unsigned int w6;   /* action 0x30 */
    unsigned int w7;   /* PC 0x18C */
    unsigned int w8;   /* action 0x3C */
    unsigned int w9;   /* terminator */
    unsigned int w10;  /* 0x0A80001D DELETEPOINTER r29 */
    void *d0;          /* dtor: MemoryManager_TimedFree */
    unsigned int w12;  /* 0x8680001E DESTROYBASE 0x0(r30), end bit */
    unsigned int w13;  /* member offset 0 */
    void *d1;          /* dtor: dtor_8002CDF4 */
    unsigned int w15;  /* 0x0A80001D DELETEPOINTER r29 */
    void *d2;          /* dtor: MemoryManager_TimedFree */
    unsigned int w17;  /* 0x8680001E DESTROYBASE 0x0(r30), end bit */
    unsigned int w18;  /* member offset 0 */
    void *d3;          /* dtor: dtor_8002CDF4 */
} extab_ServiceMenu_Init = {
    0x180A0000, 0x0000003C, 0x000F0030, 0x00000084, 0x00000028,
    0x000000D4, 0x00270030, 0x0000018C, 0x0000003C, 0x00000000,
    0x0A80001D, (void *)&MemoryManager_TimedFree,
    0x8680001E, 0x00000000, (void *)&dtor_8002CDF4,
    0x0A80001D, (void *)&MemoryManager_TimedFree,
    0x8680001E, 0x00000000, (void *)&dtor_8002CDF4
};

/* --- extabindex (manual emit) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_ServiceMenu_Draw = {
    (void *)&ServiceMenu_Draw, 0x00000038, (void *)&extab_ServiceMenu_Draw
};

__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_ServiceMenu_Tick = {
    (void *)&ServiceMenu_Tick, 0x00000078, (void *)&extab_ServiceMenu_Tick
};

__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_ServiceMenu_Dtor = {
    (void *)&ServiceMenu_Dtor, 0x000000C0, (void *)&extab_ServiceMenu_Dtor
};

__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_ServiceMenu_Init = {
    (void *)&ServiceMenu_Init, 0x000001B0, (void *)&extab_ServiceMenu_Init
};

/* vtable draw entry: dispatch UI page draw pass then flush the display
 * context. */
void ServiceMenu_Draw(ServiceMenu *self) {
    UI_PageDispatcher(self, 2);
    DisplayContext_Flush(self->displayCtx);
}

/* vtable tick entry: commit the operation clock every 600 frames, run the UI
 * page update pass, advance the 0..50 blink counter. Always returns -2 (stay
 * on page). */
int ServiceMenu_Tick(ServiceMenu *self) {
    int t;

    t = self->clockTimer + 1;
    self->clockTimer = t;
    if (t >= 0x258) {
        OperationClock_Commit();
        self->clockTimer = 0;
    }
    UI_PageDispatcher(self, 1);
    self->blinkTimer = self->blinkTimer + 1;
    if (self->blinkTimer > 0x32) {
        self->blinkTimer = 0;
    }
    return -2;
}

/* deleting destructor: tear down banner sprite / display context / PCB comm,
 * run base dtor, optionally free self. */
void *ServiceMenu_Dtor(ServiceMenu *self, short freeFlag) {
    void *ctx;

    if (self) {
        self->vtbl = lbl_803FDE64;
        Sprite_Destroy(lbl_806D1100, 1);
        lbl_806D1100 = 0;
        fn_801A0B70(0);
        SpriteSystem_EnsureInit();
        OperationClock_Commit();
        if (self->openedByExtra == 0) {
            fn_80120A08(0x55C);
        }
        ctx = lbl_806D1880;
        if (ctx == 0) {
            fn_801DB68C(ctx, 1);
            lbl_806D1880 = 0;
        }
        PcbComm_Shutdown();
        FreeMediaBuffers();
        dtor_8002CDF4(self, 0);
        if (freeFlag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

/*
 * ServiceMenu_Init @ 0x80073C70 - asm_fn park (register-identity residue).
 *
 * C reimplementation reached 99.35% (108/108 instructions, all content
 * matched): the only residue was the callee-saved home of the tail sprite
 * pointer (target r29, CW picks r31) plus the C++ virtual dispatch r12
 * routing (pinnable with opwords, Game_Shutdown.c idiom). The target is a
 * C++ constructor compiled with -Cpp_exceptions on: the 0x50-byte extab
 * carries live DELETEPOINTER(r29 -> MemoryManager_TimedFree) and
 * DESTROYBASE(0x0(r30) -> dtor_8002CDF4) actions, i.e. real scoped-guard /
 * partially-constructed-object cleanup semantics. Under the default
 * -Cpp_exceptions off the late fresh callee-saved web takes the highest
 * free register (r31) - the documented approachB-exceptions-off-regalloc
 * hard-block class (docs/notes/approachB-exceptions-off-regalloc-hardblock.md).
 * Decl-order (RULE 2) permutations and static-inline tail splice were
 * probed and are no-ops; symbolic inline asm poisons the fn-wide allocator
 * (CW reserves asm-touched regs, shifting webs to r28/r6-r8).
 * Unlock would need a .cpp + class retrofit (ctor with EH guards) so that
 * -Cpp_exceptions on both drives the allocator and auto-emits the complex
 * extab. Out of scope for this batch.
 *
 * Near-match C body (99.35%), for the retry:
 *
 *   ServiceMenu *ServiceMenu_Init(ServiceMenu *self, int pageId) {
 *       void *p;
 *       GameMode_BaseInit(self);
 *       self->vtbl = lbl_803FDE64;
 *       lbl_806D117D = 1;
 *       InitGlobalTimer();
 *       PCBComm_Init();
 *       fn_801920D4();
 *       fn_801908F0();
 *       fn_8002CFB8(0, 0, 0, 0);
 *       self->isJapanese = isJapanese();
 *       if (lbl_806D1880 == 0) {
 *           p = Alloc(0xD8);
 *           if (p != 0) {
 *               DisplayContext_Init(p);
 *           }
 *           lbl_806D1880 = p;
 *       }
 *       self->displayCtx = lbl_806D1880;
 *       self->blinkTimer = 0;
 *       self->clockTimer = 0;
 *       self->field_0x18 = 0;
 *       self->field_0x1C = 0;
 *       self->cfg = lbl_80598A60;
 *       self->field_0x34 = lbl_80598A60[0x20];
 *       self->field_0x38 = -2;
 *       self->field_0x5C = 0;
 *       self->field_0x288 = 1;
 *       if ((~fn_8028B090() & 1) != 0) {
 *           self->field_0x5C = 1;
 *       }
 *       if (pageId == -1) {
 *           self->pageState = 10;
 *           self->pageId = 0;
 *           self->openedByExtra = 0;
 *           PreloadResource(0x55C);
 *       } else {
 *           self->pageState = 1;
 *           self->pageId = pageId;
 *           self->openedByExtra = 1;
 *           UI_PageDispatcher(self, 0);
 *           Backup_PublishShadowCopy_Inline();
 *           // virtual shutdown call, needs opword pinning (r12 routing):
 *           //   if (g_pInputState) g_pInputState->vt[2](g_pInputState, 1);
 *           g_pInputState = 0;
 *           StrPcb_ResetCommands_NeutralDefault(StrPcb_GetInstance());
 *       }
 *       SpriteSystem_EnsureInit();
 *       fn_801A0BB4();
 *       p = Alloc(0x30);            // <- this web: target r29, CW emits r31
 *       if (p != 0) {
 *           fn_801A08B8(p, 0x1AE, 1, lbl_806D2E24, lbl_806D2E9C);
 *       }
 *       lbl_806D1100 = p;
 *       return self;
 *   }
 */
asm void ServiceMenu_Init(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    mr r30, r3
    stw r29, 0x14(r1)
    bl GameMode_BaseInit
    lis r3, lbl_803FDE64@ha
    li r0, 0x1
    addi r3, r3, lbl_803FDE64@l
    stw r3, 0x0(r30)
    stb r0, lbl_806D117D(r2)
    bl InitGlobalTimer
    bl PCBComm_Init
    bl fn_801920D4
    bl fn_801908F0
    li r3, 0x0
    li r4, 0x0
    li r5, 0x0
    li r6, 0x0
    bl fn_8002CFB8
    bl isJapanese
    stw r3, 0x4(r30)
    lwz r0, lbl_806D1880(r2)
    cmplwi r0, 0x0
    bne initL_80073CF8
    li r3, 0xd8
    bl Alloc
    mr. r29, r3
    beq initL_80073CF4
    bl DisplayContext_Init
initL_80073CF4:
    stw r29, lbl_806D1880(r2)
initL_80073CF8:
    lwz r0, lbl_806D1880(r2)
    lis r4, lbl_80598A60@ha
    li r5, 0x0
    li r3, -0x2
    stw r0, 0x270(r30)
    addi r4, r4, lbl_80598A60@l
    li r0, 0x1
    stw r5, 0x8(r30)
    stw r5, 0xc(r30)
    stw r5, 0x18(r30)
    stw r5, 0x1c(r30)
    stw r4, 0x274(r30)
    lbz r4, 0x20(r4)
    extsb r4, r4
    stw r4, 0x34(r30)
    stw r3, 0x38(r30)
    stb r5, 0x5c(r30)
    stw r0, 0x288(r30)
    bl fn_8028B090
    nor r0, r3, r3
    clrlwi. r0, r0, 31
    beq initL_80073D58
    li r0, 0x1
    stb r0, 0x5c(r30)
initL_80073D58:
    cmpwi r31, -0x1
    bne initL_80073D80
    li r3, 0xa
    li r0, 0x0
    stw r3, 0x14(r30)
    li r3, 0x55c
    stw r0, 0x10(r30)
    stb r0, 0x50(r30)
    bl PreloadResource
    b initL_80073DD0
initL_80073D80:
    li r0, 0x1
    mr r3, r30
    stw r0, 0x14(r30)
    li r4, 0x0
    stw r31, 0x10(r30)
    stb r0, 0x50(r30)
    bl UI_PageDispatcher
    bl Backup_PublishShadowCopy_Inline
    lwz r3, g_pInputState(r2)
    cmplwi r3, 0x0
    beq initL_80073DC0
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
initL_80073DC0:
    li r0, 0x0
    stw r0, g_pInputState(r2)
    bl StrPcb_GetInstance
    bl StrPcb_ResetCommands_NeutralDefault
initL_80073DD0:
    bl SpriteSystem_EnsureInit
    bl fn_801A0BB4
    li r3, 0x30
    bl Alloc
    mr. r29, r3
    beq initL_80073DFC
    lfs f1, lbl_806D2E24(r2)
    li r4, 0x1ae
    lfs f2, lbl_806D2E9C(r2)
    li r5, 0x1
    bl fn_801A08B8
initL_80073DFC:
    stw r29, lbl_806D1100(r2)
    mr r3, r30
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
