/*
 * ServiceMenu page object (GameMode page, vtable lbl_803FDE64).
 *
 *   ServiceMenu_Draw @ 0x80073B00 (size 0x38)
 *   ServiceMenu_Tick @ 0x80073B38 (size 0x78)
 *   ServiceMenu_Dtor @ 0x80073BB0 (size 0xC0)
 *   ServiceMenu_Init @ 0x80073C70 (size 0x1B0) - real C++ ctor
 *
 * C++ class retrofit (2026-07-19): ServiceMenu_Init is a genuine constructor
 * compiled with -Cpp_exceptions on. The 0x50-byte target extab carries live
 * DELETEPOINTER(r29 -> operator delete) and DESTROYBASE(0x0(r30) -> base
 * dtor) actions: these come from the two new-expressions (DisplayContext,
 * Sprite) and the base-subobject cleanup region of a real ctor, and the EH
 * webs are also what pin the new'd pointer into r29 (the register-identity
 * residue that blocked the plain-C attempt at 99.35%).
 *
 * Mangled C++ references are bridged to the existing C symbol names with
 * llvm-objcopy --redefine-sym via tools/extab_user_renames.json:
 *   __ct__11ServiceMenuFi     -> ServiceMenu_Init      (our ctor definition)
 *   __ct__12GameModeBaseFv    -> GameMode_BaseInit     (base ctor call)
 *   __dt__12GameModeBaseFv    -> dtor_8002CDF4         (DESTROYBASE dtor ref)
 *   __vt__11ServiceMenu       -> lbl_803FDE64          (vtable store)
 *   __ct__14DisplayContextFv  -> DisplayContext_Init   (new DisplayContext)
 *   __ct__6SpriteFiiff        -> fn_801A08B8           (new Sprite)
 *   __nw__FUl                 -> Alloc                 (operator new)
 *   __dl__FPv                 -> MemoryManager_TimedFree (operator delete)
 * The vtable itself is never emitted here: ServiceMenu's key function
 * (vKeyFunction) is declared but defined nowhere, so the reference stays
 * external and resolves to the original .data vtable.
 *
 * The sibling TU game/ServiceMenu.c holds OpenFullServiceMenu (0x80073E7C),
 * the allocator wrapper that news up this object. The wedge fn
 * SmallObj_Dtor_VtableA (0x80073E20) sits between Init and
 * OpenFullServiceMenu, so the two TUs stay separate.
 *
 * All four functions carry extab/extabindex entries in the target; with
 * -Cpp_exceptions on CW auto-emits all of them in definition order
 * (Draw/Tick/Dtor/Init = address order), no manual .extab_user emission.
 */

/* ------------------------------------------------------------------ */
/* C view shared by the three plain (extern "C") member functions.    */
/* ------------------------------------------------------------------ */
typedef struct ServiceMenuRec {
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
} ServiceMenuRec; /* size 0x28C */

extern "C" {
/* --- callees --- */
extern void UI_PageDispatcher(void *self, int mode);
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
extern void InitGlobalTimer(void);
extern void PCBComm_Init(void);
extern void fn_801920D4(void);
extern void fn_801908F0(void);
extern void fn_8002CFB8(int, int, int, int);
extern int isJapanese(void);
extern unsigned int fn_8028B090(void);
extern void PreloadResource(int resId);
extern void Backup_PublishShadowCopy_Inline(void);
extern void *StrPcb_GetInstance(void);
extern void StrPcb_ResetCommands_NeutralDefault(void *self);
extern void fn_801A0BB4(void);

/* --- data --- */
extern char lbl_803FDE64[];          /* .data  - ServiceMenu vtable */
extern char lbl_80598A60[0x2A];      /* .bss   - config block */
extern void *lbl_806D1100;           /* .sbss  - banner sprite */
extern unsigned char lbl_806D117D;   /* .sbss */
extern float lbl_806D2E24;           /* .sdata2 */
extern float lbl_806D2E9C;           /* .sdata2 */
}

/* ------------------------------------------------------------------ */
/* C++ model used by the constructor.                                 */
/* ------------------------------------------------------------------ */

/* Base class: ctor -> GameMode_BaseInit, dtor -> dtor_8002CDF4 (both extern,
 * bridged via --redefine-sym). Polymorphic so the vptr sits at offset 0. */
struct GameModeBase {
    GameModeBase();
    virtual ~GameModeBase();
};

/* new'd payloads: only the size and the ctor signature matter. */
struct DisplayContext {
    char _opaque[0xD8];
    DisplayContext();
};

struct Sprite {
    char _opaque[0x30];
    Sprite(int id, int flag, float a, float b);
};

/* Input-state object: virtual shutdown at vtable slot 0 (= +0x8 with the
 * 2-word CW vtable header) - reproduces the lwz r12/r12 dispatch. */
struct InputState {
    virtual void vShutdown(int mode);
};

struct ServiceMenu : GameModeBase {
    int isJapaneseFlag;          /* 0x004 */
    int blinkTimer;              /* 0x008 */
    int clockTimer;              /* 0x00C */
    int pageId;                  /* 0x010 */
    int pageState;               /* 0x014 */
    int field_0x18;              /* 0x018 */
    int field_0x1C;              /* 0x01C */
    char pad_0x20[0x34 - 0x20];
    int field_0x34;              /* 0x034 */
    int field_0x38;              /* 0x038 */
    char pad_0x3C[0x50 - 0x3C];
    unsigned char openedByExtra; /* 0x050 */
    char pad_0x51[0x5C - 0x51];
    unsigned char field_0x5C;    /* 0x05C */
    char pad_0x5D[0x270 - 0x5D];
    DisplayContext *displayCtx;  /* 0x270 */
    void *cfg;                   /* 0x274 */
    char pad_0x278[0x288 - 0x278];
    int field_0x288;             /* 0x288 */

    ServiceMenu(int pageId);
    /* key function: declared, never defined -> vtable stays an external
     * reference (resolves to lbl_803FDE64 via --redefine-sym) */
    virtual void vKeyFunction();
}; /* size 0x28C */

extern "C" {
extern DisplayContext *lbl_806D1880; /* .sbss  - display context */
extern InputState *g_pInputState;    /* .sbss */
}

#pragma exceptions on

extern "C" {

/* vtable draw entry: dispatch UI page draw pass then flush the display
 * context. */
void ServiceMenu_Draw(ServiceMenuRec *self) {
    UI_PageDispatcher(self, 2);
    DisplayContext_Flush(self->displayCtx);
}

/* vtable tick entry: commit the operation clock every 600 frames, run the UI
 * page update pass, advance the 0..50 blink counter. Always returns -2 (stay
 * on page). */
int ServiceMenu_Tick(ServiceMenuRec *self) {
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
void *ServiceMenu_Dtor(ServiceMenuRec *self, short freeFlag) {
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

} /* extern "C" */

/* real constructor @ 0x80073C70 - the two new-expressions carry the
 * DELETEPOINTER guards, the ctor body the DESTROYBASE region. */
ServiceMenu::ServiceMenu(int pageId_) {
    Sprite *spr;

    lbl_806D117D = 1;
    InitGlobalTimer();
    PCBComm_Init();
    fn_801920D4();
    fn_801908F0();
    fn_8002CFB8(0, 0, 0, 0);
    this->isJapaneseFlag = isJapanese();
    if (lbl_806D1880 == 0) {
        lbl_806D1880 = new DisplayContext;
    }
    this->displayCtx = lbl_806D1880;
    this->blinkTimer = 0;
    this->clockTimer = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0;
    this->cfg = lbl_80598A60;
    this->field_0x34 = lbl_80598A60[0x20];
    this->field_0x38 = -2;
    this->field_0x5C = 0;
    this->field_0x288 = 1;
    if ((~fn_8028B090() & 1) != 0) {
        this->field_0x5C = 1;
    }
    if (pageId_ == -1) {
        this->pageState = 10;
        this->pageId = 0;
        this->openedByExtra = 0;
        PreloadResource(0x55C);
    } else {
        this->pageState = 1;
        this->pageId = pageId_;
        this->openedByExtra = 1;
        UI_PageDispatcher(this, 0);
        Backup_PublishShadowCopy_Inline();
        if (g_pInputState) {
            g_pInputState->vShutdown(1);
        }
        g_pInputState = 0;
        StrPcb_ResetCommands_NeutralDefault(StrPcb_GetInstance());
    }
    SpriteSystem_EnsureInit();
    fn_801A0BB4();
    spr = new Sprite(0x1AE, 1, lbl_806D2E24, lbl_806D2E9C);
    lbl_806D1100 = spr;
}

#pragma exceptions reset
