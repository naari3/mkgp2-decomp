/*
 * clFlowItem - item-award flow scene (vtable lbl_804EE52C).
 *
 *   clFlowItem_Draw   @ 0x802379F8 (size 0x1E8)
 *   clFlowItem_Update @ 0x80237BE0 (size 0x5D8)
 *   clFlowItem_Dtor   @ 0x802381B8 (size 0x1E8)
 *   clFlowItem_Init   @ 0x802383A0 (size 0x340) - real C++ ctor
 *
 * C++ class retrofit in the ServiceMenu_Page.c mold (2026-07-19 recipe,
 * docs/notes/cpp-ctor-retrofit-mangled-bridge.md). All four functions carry
 * extab entries in the target; with -Cpp_exceptions on CW auto-emits them in
 * definition order (= address order), no manual .extab_user emission.
 *
 * The EH actions come from genuine C++ constructs:
 *   - clFlowItem_Init is a real ctor: base subobject (clFlowBase, ctor =
 *     InitializeFrameSelection / dtor = dtor_801BA14C) gives the DESTROYBASE
 *     region, `new ItemSelectState` / `new ItemGridState` give the
 *     DELETEPOINTER guards, and the ResCtrl stack local (ctor = ResCtrl_Init,
 *     dtor = dtor_80082960) gives the DESTROYLOCAL 0x8(SP) region.
 *   - Every function expands the ItemMsg_Get() singleton helper whose
 *     new-expression produces the DELETEPOINTERCOND guards (the cond register
 *     is the ctor-in-progress flag CW allocates per new-site).
 *
 * The item grid teardown duplicated in Update/Dtor is `delete self->itemGrid`
 * with ~ItemGridState() defined inline in this TU: the delete null-check plus
 * the CSE'd compare produce the double-beq idiom on the same cr0.
 *
 * Mangled C++ references bridged via tools/extab_user_renames.json:
 *   __ct__10clFlowItemFv      -> clFlowItem_Init          (our ctor definition)
 *   __ct__10clFlowBaseFv      -> InitializeFrameSelection (base ctor call)
 *   __dt__10clFlowBaseFv      -> dtor_801BA14C            (DESTROYBASE dtor)
 *   __vt__10clFlowItem        -> lbl_804EE52C             (vtable store)
 *   __ct__15ItemSelectStateFv -> ItemSelectState_Init     (new ItemSelectState)
 *   __ct__13ItemGridStateFv   -> ItemGridState_Init       (new ItemGridState)
 *   __ct__10ItemMsgWndFv      -> fn_802325FC              (new ItemMsgWnd)
 *   __ct__7ResCtrlFv          -> ResCtrl_Init             (stack local ctor)
 *   __dt__7ResCtrlFv          -> dtor_80082960            (DESTROYLOCAL dtor)
 *   __nw__FUl                 -> Alloc                    (shared mapping)
 *   __dl__FPv                 -> MemoryManager_TimedFree  (shared mapping)
 * The vtable is never emitted here: clFlowItem's key function (vKeyFunction)
 * is declared but defined nowhere, so the reference stays external.
 */

typedef float f32;
typedef unsigned char u8;

/* Sprite-group handle: slot holds a pointer to the live object pointer. */
typedef struct GroupObj {
    int _pad0;   /* 0x00 */
    int mode;    /* 0x04 */
} GroupObj;

/* Anim handle target: y-threshold checked by the Draw pass. */
typedef struct AnimObj {
    char _pad0[0x20];
    f32 y;       /* 0x20 */
} AnimObj;

/* Roulette cell payload: typed so `delete` emits its own null check (the
 * second beq of the double-beq idiom). */
typedef struct GridCell {
    char _opaque[4];
} GridCell;

/* new'd payload: item selection state (0x180 bytes). */
struct ItemSelectState {
    struct IconPack *icons;   /* 0x000 */
    GroupObj **groups[9];     /* 0x004..0x024 (groups[0] = state-0 group) */
    char _pad28[0x38 - 0x28];
    void *readySprite;        /* 0x038 */
    char _pad3C[0x144 - 0x3C];
    void *aux;                /* 0x144 */
    char _pad148[0x150 - 0x148];
    int resultCode;           /* 0x150 */
    int phase;                /* 0x154 */
    u8 doneFlag;              /* 0x158 */
    u8 shownFlag;             /* 0x159 */
    char _pad15A[0x164 - 0x15A];
    int selectedItemId0;      /* 0x164 */
    char _pad168[0x170 - 0x168];
    int selectedItemId1;      /* 0x170 */
    char _pad174[0x17C - 0x174];
    int selectedItemId2;      /* 0x17C */
    ItemSelectState();
}; /* size 0x180 */

struct IconPack {
    void *handles[4];         /* 0x00..0x0C */
    void *vals[4];            /* 0x10..0x1C */
    char _pad20[0x38 - 0x20];
    int mode;                 /* 0x38 */
};

extern "C" void SpriteAnimHandle_Destroy(void *h, int flag);
extern "C" void SpriteHandle_Destroy(void *h);
extern "C" void fn_80120A08(int resId);
extern "C" void MemoryManager_TimedFree(void *p);

/* new'd payload: item roulette grid (0x78 bytes). The inline dtor is what
 * `delete self->itemGrid` expands in Update/Dtor. */
struct ItemGridState {
    void *anims[7];           /* 0x00..0x18 */
    void *sprite;             /* 0x1C */
    GridCell *cells[3][4];    /* 0x20..0x4C */
    int spinDone;             /* 0x50 */
    char _pad54[0x5C - 0x54];
    u8 readyFlag;             /* 0x5C */
    u8 forceFlag;             /* 0x5D */
    char _pad5E[0x60 - 0x5E];
    int pickedId0;            /* 0x60 */
    int pickedId1;            /* 0x64 */
    int pickedId2;            /* 0x68 */
    char _pad6C[0x78 - 0x6C];
    ItemGridState();
    ~ItemGridState() {
        int j;
        int i;
        for (j = 0; j < 3; j++) {
            for (i = 0; i < 4; i++) {
                /* doubled guard: the deleting-dtor offset-0 idiom
                 * (docs/notes/sdata-deleting-dtor-idiom.md) - both beq
                 * survive on the same cr0 */
                if (this->cells[j][i]) {
                    if (this->cells[j][i]) {
                        MemoryManager_TimedFree(this->cells[j][i]);
                    }
                    this->cells[j][i] = 0;
                }
            }
        }
        for (i = 0; i < 7; i++) {
            if (this->anims[i]) {
                SpriteAnimHandle_Destroy(this->anims[i], 1);
                this->anims[i] = 0;
            }
        }
        SpriteHandle_Destroy(this->sprite);
        fn_80120A08(0x192A);
        fn_80120A08(0x192C);
    }
}; /* size 0x78 */

/* Singleton message window (0x5C bytes, instance ptr lbl_806D1A88). */
struct ItemMsgWnd {
    int state;                /* 0x00 */
    char _pad4[0x5C - 0x4];
    ItemMsgWnd();
};

/* C view shared by the three plain (extern "C") member functions. */
typedef struct clFlowItemRec {
    void *vtbl;                      /* 0x00 - lbl_804EE52C */
    int frameCounter;                /* 0x04 */
    int subState;                    /* 0x08 */
    f32 fadeAlpha;                   /* 0x0C */
    int nextSceneId;                 /* 0x10 */
    ItemGridState *itemGrid;         /* 0x14 */
    ItemSelectState *itemSelection;  /* 0x18 */
    GroupObj **bgSpr[2];             /* 0x1C, 0x20 */
    void *hudSpr[4];                 /* 0x24, 0x28, 0x2C, 0x30 */
} clFlowItemRec; /* size 0x34 */

/* Input-state record accessed through the GetInput() inline. */
typedef struct InputRec {
    char _pad0[4];
    u8 active;                /* 0x04 */
    char _pad5[0x18 - 0x5];
    int mode;                 /* 0x18 */
    int submode;              /* 0x1C */
} InputRec;

typedef struct PlayerDataRec {
    char _pad0[0x18C];
    int unlockIdx;            /* 0x18C */
    char _pad190[0x1DC - 0x190];
} PlayerDataRec;

extern "C" {
/* --- callees --- */
extern void fn_801A0004(void *obj);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *ctx, void *item, int mode);
extern void *ItemDisplay_GetOrCreate(void);
extern void fn_8020AC34(void);
extern void ItemDisplay_Update(void *disp);
extern void ItemDisplay_Start(void *disp, int id);
extern void ItemDisplay_Destroy(void);
extern void fn_802321F8(ItemMsgWnd *wnd);
extern void fn_80232284(ItemMsgWnd *wnd, f32 alpha);
extern void fn_80232550(ItemMsgWnd *wnd, int flag);
extern void fn_802325FC(ItemMsgWnd *wnd); /* ItemMsgWnd ctor (asm Draw calls it directly) */
extern void *Alloc(unsigned long size);   /* operator new impl (asm Draw calls it directly) */
extern void SpriteGroup_CreateOrInit(void *slot, void *desc, int flag, f32 a, f32 b);
extern void SpriteHandle_SetActiveFlag(void *h, int flag);
extern void SpriteHandle_SetCornerAlpha(void *h, int alpha);
extern void SpriteHandle_RecomputeCull(void *h);
extern void *SpriteHandle_CreateDefault(void *desc, int type);
extern void Sprite_AdvanceAnim(void *obj, f32 dt);
extern void fn_80121E10(void *desc);
extern void fn_80121210(void);
extern void fn_80169C44(void);
extern void fn_801699D8(int a, int b);
extern void SetRumbleMode(int a, int b, int c);
extern void RumbleUpdate(void);
extern void InitRumbleController(int mode);
extern void SetSyncTarget(int id);
extern void InitBGM(void);
extern void SetupBgSprites(int mode);
extern int PlayerData_ResolveUnlockedIdByIndex(PlayerDataRec *pd, int idx);
extern u8 fn_801D6F30(PlayerDataRec *pd, int id, int mode);
extern void fn_80238980(ItemSelectState *sel);
extern void fn_80239D6C(ItemGridState *grid);
extern void fn_802386E0(ItemSelectState *sel);
extern void fn_80238D9C(ItemSelectState *sel);
extern void fn_8023A148(ItemGridState *grid);
extern void *ItemSelectState_Dtor(ItemSelectState *sel, short freeFlag);
extern void *dtor_801BA14C(void *self, short freeFlag);

/* --- data --- */
extern ItemMsgWnd *lbl_806D1A88;     /* .sbss  - message window singleton */
extern InputRec *g_pInputState;      /* .sbss */
extern int g_gameMode;               /* .sbss */
extern PlayerDataRec g_playerData;   /* .bss */
extern char lbl_804EE52C[];          /* .data  - clFlowItem vtable */
extern char lbl_806D0758[4];         /* .sdata - sprite group desc */
extern char lbl_806D077C[4];         /* .sdata - sprite group desc */
extern char lbl_806D0780[4];         /* .sdata - sprite group desc */
extern const f32 lbl_806DB888;       /* .sdata2 */
extern const f32 lbl_806DB88C;       /* .sdata2 */
extern const f32 lbl_806DB890;       /* .sdata2 */
extern const f32 lbl_806DB894;       /* .sdata2 */
extern const f32 lbl_806DB898;       /* .sdata2 */
extern const f32 lbl_806DB89C;       /* .sdata2 */
extern const f32 lbl_806DB8A0;       /* .sdata2 */
extern const f32 lbl_806DB8A4;       /* .sdata2 */
extern const f32 lbl_806DB8A8;       /* .sdata2 */
extern const f32 lbl_806DB8AC;       /* .sdata2 */
extern const double lbl_806DB8B0;    /* .sdata2 - int-to-float cookie */
extern const f32 lbl_806DB8B8;       /* .sdata2 */
extern const f32 lbl_806DB8BC;       /* .sdata2 */
extern const f32 lbl_806DB8C0;       /* .sdata2 */
extern const f32 lbl_806DB8C4;       /* .sdata2 */
extern const f32 lbl_806DB8C8;       /* .sdata2 */
extern const f32 lbl_806DB8CC;       /* .sdata2 */
extern const f32 lbl_806DB8D0;       /* .sdata2 */
extern const f32 lbl_806DB8D4;       /* .sdata2 */
extern const f32 lbl_806DB8D8;       /* .sdata2 */
extern const f32 lbl_806DB8DC;       /* .sdata2 */
extern const f32 lbl_806DB8E0;       /* .sdata2 */
}

/* Message-window singleton accessor: the new-expression here is the origin of
 * every DELETEPOINTERCOND action in this TU. The ternary spelling is
 * load-bearing: the new sits on a conditional expression path, which is what
 * makes CW allocate the ctor-in-progress cond flag (li rN, 0/1) and emit the
 * COND form of the delete action, plus the beq/b branch shape. */
static inline ItemMsgWnd *ItemMsg_Get(void) {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

static inline void ItemMsg_Destroy(void) {
    if (lbl_806D1A88 != 0) {
        fn_80232550(lbl_806D1A88, 1);
        lbl_806D1A88 = 0;
    }
}

static inline InputRec *GetInput(void) {
    /* inverted-cond spelling: false arm (li 0) lays out first, matching the
     * target's bne-to-value branch shape */
    return g_pInputState == 0 ? (InputRec *)0 : g_pInputState;
}

/* ------------------------------------------------------------------ */
/* C++ model used by the constructor.                                 */
/* ------------------------------------------------------------------ */

/* Base class: ctor -> InitializeFrameSelection, dtor -> dtor_801BA14C (both
 * extern, bridged via --redefine-sym). Polymorphic so the vptr sits at 0. */
struct clFlowBase {
    clFlowBase();
    virtual ~clFlowBase();
};

/* Stack-local resource descriptor used while creating the HUD sprites
 * (ctor = ResCtrl_Init, dtor = dtor_80082960 -> DESTROYLOCAL 0x8(SP)). */
struct ResCtrl {
    int resId;                /* 0x00 */
    char _pad4[0x8 - 0x4];
    int mode;                 /* 0x08 */
    char _padC[0x10 - 0xC];
    u8 flag;                  /* 0x10 */
    char _pad11[0x14 - 0x11];
    f32 fA;                   /* 0x14 */
    f32 fB;                   /* 0x18 */
    f32 fC;                   /* 0x1C */
    f32 fD;                   /* 0x20 */
    f32 fE;                   /* 0x24 */
    char _pad28[0x34 - 0x28];
    int w0;                   /* 0x34 */
    int w1;                   /* 0x38 */
    int w2;                   /* 0x3C */
    int w3;                   /* 0x40 */
    char _pad44[0x58 - 0x44];
    ResCtrl();
    /* Empty inline dtor: inlines to nothing at scope end (target has no
     * call), while the extab DESTROYLOCAL reference resolves through the
     * weak out-of-line copy, redefined to dtor_80082960 and discarded at
     * link against the strong original (MemoryManager_TimedFree.o
     * precedent). */
    ~ResCtrl() {}
}; /* size 0x58 */

struct clFlowItem : clFlowBase {
    int frameCounter;                /* 0x04 */
    int subState;                    /* 0x08 */
    f32 fadeAlpha;                   /* 0x0C */
    int nextSceneId;                 /* 0x10 */
    ItemGridState *itemGrid;         /* 0x14 */
    ItemSelectState *itemSelection;  /* 0x18 */
    GroupObj **bgSpr[2];             /* 0x1C */
    void *hudSpr[4];                 /* 0x24 */

    clFlowItem();
    /* key function: declared, never defined -> vtable stays external */
    virtual void vKeyFunction();
}; /* size 0x34 */

#pragma exceptions on

/* vtable draw entry: draw the background sprite groups, the selection HUD
 * groups, the icon pack, and the roulette grid cells, then hand the item
 * display and message window their draw passes.
 *
 * asm_fn park (2026-07-19): the C++ body below reaches 96.6% with a
 * byte-identical instruction stream; the residue is pure callee-saved
 * register coloring (walker webs refuse to coalesce with their dying base
 * pointers, decl-order/member-fn/destructive-walk probes all plateau).
 * Parked per the 6-cycle retreat rule; promote later if the coloring
 * lever is found. Manual extab emission + tools/extab_order.json keeps
 * the target extab/extabindex layout (Draw first, then the three
 * auto-emitted siblings).
 */
#if 0
void clFlowItem::Draw() {
    ItemGridState *grid;
    void *ctx;
    int j;
    int i;
    ItemSelectState *sel;
    IconPack *icons;
    f32 th;

    for (i = 0; i < 2; i++) {
        if (this->bgSpr[i]) {
            fn_801A0004(*this->bgSpr[i]);
        }
    }
    sel = this->itemSelection;
    for (i = 0; i < 9; i++) {
        if (sel->groups[i]) {
            fn_801A0004(*sel->groups[i]);
        }
    }
    fn_801F8A34(fn_801F8E58(), sel->aux, 5);
    icons = sel->icons;
    if (icons->mode < 3) {
        for (i = 0; i < 4; i++) {
            if (icons->handles[i]) {
                fn_801A0004(*(void **)icons->handles[i]);
            }
        }
        ctx = fn_801F8E58();
        for (i = 0; i < 4; i++) {
            if (icons->vals[i]) {
                fn_801F8A34(ctx, icons->vals[i], 6);
            }
        }
    }
    grid = this->itemGrid;
    if (grid) {
        th = lbl_806DB888;
        for (i = 0; i < 7; i++) {
            if (grid->anims[i]) {
                if (((AnimObj *)*(void **)grid->anims[i])->y > th) {
                    fn_801A0004(*(void **)grid->anims[i]);
                }
            }
        }
        ctx = fn_801F8E58();
        for (j = 0; j < 3; j++) {
            for (i = 0; i < 4; i++) {
                if (grid->cells[j][i]) {
                    fn_801F8A34(ctx, grid->cells[j][i], 6);
                }
            }
        }
    }
    ItemDisplay_GetOrCreate();
    fn_8020AC34();
    fn_802321F8(ItemMsg_Get());
}
#endif

extern "C" asm void clFlowItem_Draw(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; } extab_clFlowItem_Draw = { 0x304A0000, 0x000001B0, 0x00040010, 0x00000000, 0x8BC0001A, 0x001EC702, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowItem_Draw = {
    (void *)&clFlowItem_Draw, 0x000001E8, (void *)&extab_clFlowItem_Draw
};

extern "C" asm void clFlowItem_Draw(void) { /* 0x802379F8 size:0x1E8 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stmw r26, 0x8(r1)
    mr r31, r3
    li r26, 0x0
    mr r28, r31
    clFlowItem_Draw_L_80237A1C:
    lwz r3, 0x1c(r28)
    cmplwi r3, 0x0
    beq clFlowItem_Draw_L_80237A30
    lwz r3, 0x0(r3)
    bl fn_801A0004
    clFlowItem_Draw_L_80237A30:
    addi r26, r26, 0x1
    addi r28, r28, 0x4
    cmpwi r26, 0x2
    blt clFlowItem_Draw_L_80237A1C
    lwz r28, 0x18(r31)
    li r29, 0x0
    mr r27, r28
    clFlowItem_Draw_L_80237A4C:
    lwz r3, 0x4(r27)
    cmplwi r3, 0x0
    beq clFlowItem_Draw_L_80237A60
    lwz r3, 0x0(r3)
    bl fn_801A0004
    clFlowItem_Draw_L_80237A60:
    addi r29, r29, 0x1
    addi r27, r27, 0x4
    cmpwi r29, 0x9
    blt clFlowItem_Draw_L_80237A4C
    bl fn_801F8E58
    lwz r4, 0x144(r28)
    li r5, 0x5
    bl fn_801F8A34
    lwz r26, 0x0(r28)
    lwz r0, 0x38(r26)
    cmpwi r0, 0x3
    bge clFlowItem_Draw_L_80237AF0
    li r28, 0x0
    mr r27, r26
    clFlowItem_Draw_L_80237A98:
    lwz r3, 0x0(r27)
    cmplwi r3, 0x0
    beq clFlowItem_Draw_L_80237AAC
    lwz r3, 0x0(r3)
    bl fn_801A0004
    clFlowItem_Draw_L_80237AAC:
    addi r28, r28, 0x1
    addi r27, r27, 0x4
    cmpwi r28, 0x4
    blt clFlowItem_Draw_L_80237A98
    bl fn_801F8E58
    mr r29, r3
    li r28, 0x0
    clFlowItem_Draw_L_80237AC8:
    lwz r4, 0x10(r26)
    cmplwi r4, 0x0
    beq clFlowItem_Draw_L_80237AE0
    mr r3, r29
    li r5, 0x6
    bl fn_801F8A34
    clFlowItem_Draw_L_80237AE0:
    addi r28, r28, 0x1
    addi r26, r26, 0x4
    cmpwi r28, 0x4
    blt clFlowItem_Draw_L_80237AC8
    clFlowItem_Draw_L_80237AF0:
    lwz r27, 0x14(r31)
    cmplwi r27, 0x0
    beq clFlowItem_Draw_L_80237B84
    lfs f31, lbl_806DB888(r2)
    mr r26, r27
    li r28, 0x0
    clFlowItem_Draw_L_80237B08:
    lwz r3, 0x0(r26)
    cmplwi r3, 0x0
    beq clFlowItem_Draw_L_80237B28
    lwz r3, 0x0(r3)
    lfs f0, 0x20(r3)
    fcmpo cr0, f0, f31
    ble clFlowItem_Draw_L_80237B28
    bl fn_801A0004
    clFlowItem_Draw_L_80237B28:
    addi r28, r28, 0x1
    addi r26, r26, 0x4
    cmpwi r28, 0x7
    blt clFlowItem_Draw_L_80237B08
    bl fn_801F8E58
    mr r29, r3
    li r31, 0x0
    clFlowItem_Draw_L_80237B44:
    li r28, 0x0
    mr r26, r27
    clFlowItem_Draw_L_80237B4C:
    lwz r4, 0x20(r26)
    cmplwi r4, 0x0
    beq clFlowItem_Draw_L_80237B64
    mr r3, r29
    li r5, 0x6
    bl fn_801F8A34
    clFlowItem_Draw_L_80237B64:
    addi r28, r28, 0x1
    addi r26, r26, 0x4
    cmpwi r28, 0x4
    blt clFlowItem_Draw_L_80237B4C
    addi r31, r31, 0x1
    addi r27, r27, 0x10
    cmpwi r31, 0x3
    blt clFlowItem_Draw_L_80237B44
    clFlowItem_Draw_L_80237B84:
    bl ItemDisplay_GetOrCreate
    bl fn_8020AC34
    lwz r3, lbl_806D1A88(r13)
    li r26, 0x0
    cmplwi r3, 0x0
    beq clFlowItem_Draw_L_80237BA0
    b clFlowItem_Draw_L_80237BC0
    clFlowItem_Draw_L_80237BA0:
    li r3, 0x5c
    bl Alloc
    mr. r30, r3
    beq clFlowItem_Draw_L_80237BB8
    li r26, 0x1
    bl fn_802325FC
    clFlowItem_Draw_L_80237BB8:
    stw r30, lbl_806D1A88(r13)
    mr r3, r30
    clFlowItem_Draw_L_80237BC0:
    bl fn_802321F8
    psq_l f31, 0x28(r1), 0, 0
    lfd f31, 0x20(r1)
    lmw r26, 0x8(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" {

/* vtable tick entry: rumble bookkeeping, the 5-state award flow state
 * machine, sprite anim advance, and the display/message window updates.
 * Returns the next scene id (-1 = stay).
 *
 * asm_fn park (2026-07-19): the C body below is byte-identical except for
 * one callee-saved coloring residue - the selection-pointer web (case 0 /
 * case 1-else) takes r24 while the target shares r31 with the
 * &g_playerData cursor. Single-shared-variable, scoped-local and
 * decl-order (36 perm) probes all leave the live-range split colored r24
 * (register-identity park family, cf. ItemObjectManager_Init). Promote
 * later if the split-affinity lever is found.
 */
#if 0
int clFlowItem_Update(clFlowItemRec *self) {
    /* One pointer local serves both roles (player-data cursor in case 1,
     * selection pointer in cases 0/1-else): the shared web is what puts
     * both in the same callee-saved register, with &g_playerData
     * materialized once at entry. */
    ItemSelectState *sel = (ItemSelectState *)&g_playerData;
#define pd_ ((PlayerDataRec *)sel)
    int alpha;
    int flag;
    u8 ok;
    int i;
    int id;

    if (GetInput()->mode == 1) {
        SetRumbleMode(0, 1, 1);
    }
    if (GetInput()->mode == 3 && self->subState == 3) {
        SetRumbleMode(1, 1, 1);
    }
    RumbleUpdate();
    switch (self->subState) {
    case 0:
        sel = self->itemSelection;
        SpriteGroup_CreateOrInit(&sel->groups[0], lbl_806D0758, 0, lbl_806DB88C, lbl_806DB890);
        (*sel->groups[0])->mode = 5;
        sel->resultCode = 0;
        sel->phase = 1;
        self->subState = 1;
        self->frameCounter = 0;
        break;
    case 1:
        if (self->frameCounter <= 10) {
            SpriteHandle_SetActiveFlag(self->hudSpr[1], 1);
            SpriteHandle_SetActiveFlag(self->hudSpr[0], 1);
            alpha = (int)(lbl_806DB894 * ((f32)self->frameCounter / lbl_806DB898));
            SpriteHandle_SetCornerAlpha(self->hudSpr[1], alpha);
            SpriteHandle_SetCornerAlpha(self->hudSpr[0], alpha);
        }
        if (self->itemSelection->shownFlag == 1) {
            i = 0;
            do {
                id = PlayerData_ResolveUnlockedIdByIndex(pd_, pd_->unlockIdx);
                ok = fn_801D6F30(pd_, id, 0);
                if (ok == 0) {
                    break;
                }
                i++;
            } while (i < 3);
            if (ok == 0) {
                self->subState = 3;
                fn_80238980(self->itemSelection);
                self->fadeAlpha = lbl_806DB89C;
                fn_801699D8(1, 1);
            } else {
                self->subState = 2;
                fn_80239D6C(self->itemGrid);
                sel = self->itemSelection;
                SpriteHandle_SetActiveFlag(sel->readySprite, 1);
                sel->resultCode = 0;
                sel->phase = 3;
                self->fadeAlpha = lbl_806DB898;
            }
            fn_801699D8(0, 1);
        }
        break;
    case 2:
        flag = self->itemGrid->spinDone;
        if (self->fadeAlpha <= lbl_806DB888) {
            flag = 1;
            self->itemGrid->forceFlag = 1;
        }
        if (self->itemGrid->readyFlag == 1) {
            if (flag == 0) {
                self->subState = 3;
                fn_80238980(self->itemSelection);
                self->fadeAlpha = lbl_806DB89C;
                fn_801699D8(1, 1);
            } else {
                self->subState = 4;
                self->frameCounter = 0;
                SpriteHandle_SetActiveFlag(self->hudSpr[3], 1);
                self->itemSelection->selectedItemId0 = self->itemGrid->pickedId0;
                self->itemSelection->selectedItemId1 = self->itemGrid->pickedId1;
                self->itemSelection->selectedItemId2 = self->itemGrid->pickedId2;
            }
            if (self->itemGrid) {
                delete self->itemGrid;
                self->itemGrid = 0;
            }
        }
        break;
    case 3:
        if (self->fadeAlpha <= lbl_806DB888) {
            fn_802386E0(self->itemSelection);
        }
        if (self->itemSelection->doneFlag == 1) {
            self->subState = 4;
            self->frameCounter = 0;
            SpriteHandle_SetActiveFlag(self->hudSpr[3], 1);
        }
        break;
    case 4:
        fn_801699D8(0, 0);
        fn_801699D8(1, 0);
        self->fadeAlpha = lbl_806DB8A0;
        fn_80232284(ItemMsg_Get(), lbl_806DB8A0);
        SpriteHandle_SetCornerAlpha(self->hudSpr[3],
                                    (int)(lbl_806DB894 * ((f32)self->frameCounter / lbl_806DB8A4)));
        if (self->frameCounter >= 0x28) {
            if (g_gameMode == 2) {
                self->nextSceneId = 0x27;
            } else {
                self->nextSceneId = 0x25;
            }
            SpriteHandle_SetActiveFlag(self->hudSpr[1], 0);
            SpriteHandle_SetActiveFlag(self->hudSpr[0], 0);
        }
        break;
    }
    self->frameCounter = self->frameCounter + 1;
    for (i = 0; i < 2; i++) {
        if (self->bgSpr[i]) {
            Sprite_AdvanceAnim(*self->bgSpr[i], lbl_806DB8A8);
        }
    }
    for (i = 0; i < 4; i++) {
        SpriteHandle_RecomputeCull(self->hudSpr[i]);
    }
    fn_80238D9C(self->itemSelection);
    if (self->itemGrid) {
        fn_8023A148(self->itemGrid);
    }
    if (self->fadeAlpha > lbl_806DB888) {
        self->fadeAlpha = self->fadeAlpha - lbl_806DB8AC;
        if (self->fadeAlpha < lbl_806DB888) {
            self->fadeAlpha = lbl_806DB8A0;
        }
        fn_80232284(ItemMsg_Get(), self->fadeAlpha);
    }
    ItemDisplay_Update(ItemDisplay_GetOrCreate());
    return self->nextSceneId;
#undef pd_
}
#endif

extern "C" asm void clFlowItem_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; void *f8; unsigned int f9; unsigned int f10; void *f11; } extab_clFlowItem_Update = { 0x400A0000, 0x00000430, 0x00040018, 0x00000598, 0x00040024, 0x00000000, 0x8BC00019, 0x0018C702, (void *)&MemoryManager_TimedFree, 0x8BC00018, 0x001DC702, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowItem_Update = {
    (void *)&clFlowItem_Update, 0x000005D8, (void *)&extab_clFlowItem_Update
};

extern "C" asm void clFlowItem_Update(void) { /* 0x80237BE0 size:0x5D8 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    lis r4, g_playerData@ha
    stw r0, 0x44(r1)
    addi r0, r4, g_playerData@l
    stmw r24, 0x20(r1)
    mr r30, r3
    mr r31, r0
    lwz r5, g_pInputState(r13)
    cmplwi r5, 0x0
    bne clFlowItem_Update_L_80237C10
    li r5, 0x0
    clFlowItem_Update_L_80237C10:
    lwz r0, 0x18(r5)
    cmpwi r0, 0x1
    bne clFlowItem_Update_L_80237C2C
    li r3, 0x0
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    clFlowItem_Update_L_80237C2C:
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne clFlowItem_Update_L_80237C3C
    li r3, 0x0
    clFlowItem_Update_L_80237C3C:
    lwz r0, 0x18(r3)
    cmpwi r0, 0x3
    bne clFlowItem_Update_L_80237C64
    lwz r0, 0x8(r30)
    cmpwi r0, 0x3
    bne clFlowItem_Update_L_80237C64
    li r3, 0x1
    li r4, 0x1
    li r5, 0x1
    bl SetRumbleMode
    clFlowItem_Update_L_80237C64:
    bl RumbleUpdate
    lwz r0, 0x8(r30)
    cmpwi r0, 0x2
    beq clFlowItem_Update_L_80237E18
    bge clFlowItem_Update_L_80237C88
    cmpwi r0, 0x0
    beq clFlowItem_Update_L_80237C98
    bge clFlowItem_Update_L_80237CE0
    b clFlowItem_Update_L_802380B8
    clFlowItem_Update_L_80237C88:
    cmpwi r0, 0x4
    beq clFlowItem_Update_L_80237FD4
    bge clFlowItem_Update_L_802380B8
    b clFlowItem_Update_L_80237F88
    clFlowItem_Update_L_80237C98:
    lwz r31, 0x18(r30)
    subi r4, r13, 0x65C8  /* lbl_806D0758 (r13 = _SDA_BASE_ 0x806D6D20) */
    lfs f1, lbl_806DB88C(r2)
    li r5, 0x0
    lfs f2, lbl_806DB890(r2)
    addi r3, r31, 0x4
    bl SpriteGroup_CreateOrInit
    lwz r4, 0x4(r31)
    li r5, 0x5
    li r3, 0x0
    li r0, 0x1
    lwz r4, 0x0(r4)
    stw r5, 0x4(r4)
    stw r3, 0x150(r31)
    stw r0, 0x154(r31)
    stw r0, 0x8(r30)
    stw r3, 0x4(r30)
    b clFlowItem_Update_L_802380B8
    clFlowItem_Update_L_80237CE0:
    lwz r0, 0x4(r30)
    cmpwi r0, 0xa
    bgt clFlowItem_Update_L_80237D58
    lwz r3, 0x28(r30)
    li r4, 0x1
    bl SpriteHandle_SetActiveFlag
    lwz r3, 0x24(r30)
    li r4, 0x1
    bl SpriteHandle_SetActiveFlag
    lwz r3, 0x4(r30)
    lis r0, 0x4330
    stw r0, 0x8(r1)
    xoris r0, r3, 0x8000
    lfd f2, lbl_806DB8B0(r2)
    stw r0, 0xc(r1)
    lfs f0, lbl_806DB898(r2)
    lfd f1, 0x8(r1)
    lfs f3, lbl_806DB894(r2)
    fsubs f1, f1, f2
    lwz r3, 0x28(r30)
    fdivs f0, f1, f0
    fmuls f0, f3, f0
    fctiwz f0, f0
    stfd f0, 0x10(r1)
    lwz r24, 0x14(r1)
    mr r4, r24
    bl SpriteHandle_SetCornerAlpha
    lwz r3, 0x24(r30)
    mr r4, r24
    bl SpriteHandle_SetCornerAlpha
    clFlowItem_Update_L_80237D58:
    lwz r3, 0x18(r30)
    lbz r0, 0x159(r3)
    cmplwi r0, 0x1
    bne clFlowItem_Update_L_802380B8
    li r24, 0x0
    clFlowItem_Update_L_80237D6C:
    lwz r4, 0x18c(r31)
    mr r3, r31
    bl PlayerData_ResolveUnlockedIdByIndex
    mr r0, r3
    mr r3, r31
    mr r4, r0
    li r5, 0x0
    bl fn_801D6F30
    clrlwi. r0, r3, 24
    beq clFlowItem_Update_L_80237DA0
    addi r24, r24, 0x1
    cmpwi r24, 0x3
    blt clFlowItem_Update_L_80237D6C
    clFlowItem_Update_L_80237DA0:
    clrlwi. r0, r3, 24
    bne clFlowItem_Update_L_80237DD0
    li r0, 0x3
    stw r0, 0x8(r30)
    lwz r3, 0x18(r30)
    bl fn_80238980
    lfs f0, lbl_806DB89C(r2)
    li r3, 0x1
    li r4, 0x1
    stfs f0, 0xc(r30)
    bl fn_801699D8
    b clFlowItem_Update_L_80237E08
    clFlowItem_Update_L_80237DD0:
    li r0, 0x2
    stw r0, 0x8(r30)
    lwz r3, 0x14(r30)
    bl fn_80239D6C
    lwz r31, 0x18(r30)
    li r4, 0x1
    lwz r3, 0x38(r31)
    bl SpriteHandle_SetActiveFlag
    li r3, 0x0
    li r0, 0x3
    stw r3, 0x150(r31)
    lfs f0, lbl_806DB898(r2)
    stw r0, 0x154(r31)
    stfs f0, 0xc(r30)
    clFlowItem_Update_L_80237E08:
    li r3, 0x0
    li r4, 0x1
    bl fn_801699D8
    b clFlowItem_Update_L_802380B8
    clFlowItem_Update_L_80237E18:
    lfs f1, 0xc(r30)
    lfs f0, lbl_806DB888(r2)
    lwz r3, 0x14(r30)
    fcmpo cr0, f1, f0
    lwz r4, 0x50(r3)
    cror eq, lt, eq
    bne clFlowItem_Update_L_80237E40
    li r0, 0x1
    li r4, 0x1
    stb r0, 0x5d(r3)
    clFlowItem_Update_L_80237E40:
    lwz r3, 0x14(r30)
    lbz r0, 0x5c(r3)
    cmplwi r0, 0x1
    bne clFlowItem_Update_L_802380B8
    cmpwi r4, 0x0
    bne clFlowItem_Update_L_80237E80
    li r0, 0x3
    stw r0, 0x8(r30)
    lwz r3, 0x18(r30)
    bl fn_80238980
    lfs f0, lbl_806DB89C(r2)
    li r3, 0x1
    li r4, 0x1
    stfs f0, 0xc(r30)
    bl fn_801699D8
    b clFlowItem_Update_L_80237ECC
    clFlowItem_Update_L_80237E80:
    li r3, 0x4
    li r0, 0x0
    stw r3, 0x8(r30)
    li r4, 0x1
    stw r0, 0x4(r30)
    lwz r3, 0x30(r30)
    bl SpriteHandle_SetActiveFlag
    lwz r4, 0x14(r30)
    lwz r3, 0x18(r30)
    lwz r0, 0x60(r4)
    stw r0, 0x164(r3)
    lwz r4, 0x14(r30)
    lwz r3, 0x18(r30)
    lwz r0, 0x64(r4)
    stw r0, 0x170(r3)
    lwz r4, 0x14(r30)
    lwz r3, 0x18(r30)
    lwz r0, 0x68(r4)
    stw r0, 0x17c(r3)
    clFlowItem_Update_L_80237ECC:
    lwz r24, 0x14(r30)
    cmplwi r24, 0x0
    beq clFlowItem_Update_L_802380B8
    beq clFlowItem_Update_L_80237F7C
    li r27, 0x0
    mr r25, r24
    mr r31, r27
    clFlowItem_Update_L_80237EE8:
    li r28, 0x0
    mr r26, r25
    clFlowItem_Update_L_80237EF0:
    lwz r3, 0x20(r26)
    cmplwi r3, 0x0
    beq clFlowItem_Update_L_80237F08
    beq clFlowItem_Update_L_80237F04
    bl MemoryManager_TimedFree
    clFlowItem_Update_L_80237F04:
    stw r31, 0x20(r26)
    clFlowItem_Update_L_80237F08:
    addi r28, r28, 0x1
    addi r26, r26, 0x4
    cmpwi r28, 0x4
    blt clFlowItem_Update_L_80237EF0
    addi r27, r27, 0x1
    addi r25, r25, 0x10
    cmpwi r27, 0x3
    blt clFlowItem_Update_L_80237EE8
    li r26, 0x0
    mr r25, r24
    mr r31, r26
    clFlowItem_Update_L_80237F34:
    lwz r3, 0x0(r25)
    cmplwi r3, 0x0
    beq clFlowItem_Update_L_80237F4C
    li r4, 0x1
    bl SpriteAnimHandle_Destroy
    stw r31, 0x0(r25)
    clFlowItem_Update_L_80237F4C:
    addi r26, r26, 0x1
    addi r25, r25, 0x4
    cmpwi r26, 0x7
    blt clFlowItem_Update_L_80237F34
    lwz r3, 0x1c(r24)
    bl SpriteHandle_Destroy
    li r3, 0x192a
    bl fn_80120A08
    li r3, 0x192c
    bl fn_80120A08
    mr r3, r24
    bl MemoryManager_TimedFree
    clFlowItem_Update_L_80237F7C:
    li r0, 0x0
    stw r0, 0x14(r30)
    b clFlowItem_Update_L_802380B8
    clFlowItem_Update_L_80237F88:
    lfs f1, 0xc(r30)
    lfs f0, lbl_806DB888(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne clFlowItem_Update_L_80237FA4
    lwz r3, 0x18(r30)
    bl fn_802386E0
    clFlowItem_Update_L_80237FA4:
    lwz r3, 0x18(r30)
    lbz r0, 0x158(r3)
    cmplwi r0, 0x1
    bne clFlowItem_Update_L_802380B8
    li r3, 0x4
    li r0, 0x0
    stw r3, 0x8(r30)
    li r4, 0x1
    stw r0, 0x4(r30)
    lwz r3, 0x30(r30)
    bl SpriteHandle_SetActiveFlag
    b clFlowItem_Update_L_802380B8
    clFlowItem_Update_L_80237FD4:
    li r3, 0x0
    li r4, 0x0
    bl fn_801699D8
    li r3, 0x1
    li r4, 0x0
    bl fn_801699D8
    lfs f0, lbl_806DB8A0(r2)
    li r25, 0x0
    stfs f0, 0xc(r30)
    lwz r3, lbl_806D1A88(r13)
    cmplwi r3, 0x0
    beq clFlowItem_Update_L_80238008
    b clFlowItem_Update_L_80238028
    clFlowItem_Update_L_80238008:
    li r3, 0x5c
    bl Alloc
    mr. r24, r3
    beq clFlowItem_Update_L_80238020
    li r25, 0x1
    bl fn_802325FC
    clFlowItem_Update_L_80238020:
    stw r24, lbl_806D1A88(r13)
    mr r3, r24
    clFlowItem_Update_L_80238028:
    lfs f1, lbl_806DB8A0(r2)
    bl fn_80232284
    lwz r3, 0x4(r30)
    lis r0, 0x4330
    stw r0, 0x10(r1)
    xoris r0, r3, 0x8000
    lfd f2, lbl_806DB8B0(r2)
    stw r0, 0x14(r1)
    lfs f0, lbl_806DB8A4(r2)
    lfd f1, 0x10(r1)
    lfs f3, lbl_806DB894(r2)
    fsubs f1, f1, f2
    lwz r3, 0x30(r30)
    fdivs f0, f1, f0
    fmuls f0, f3, f0
    fctiwz f0, f0
    stfd f0, 0x8(r1)
    lwz r4, 0xc(r1)
    bl SpriteHandle_SetCornerAlpha
    lwz r0, 0x4(r30)
    cmpwi r0, 0x28
    blt clFlowItem_Update_L_802380B8
    lwz r0, g_gameMode(r13)
    cmpwi r0, 0x2
    bne clFlowItem_Update_L_80238098
    li r0, 0x27
    stw r0, 0x10(r30)
    b clFlowItem_Update_L_802380A0
    clFlowItem_Update_L_80238098:
    li r0, 0x25
    stw r0, 0x10(r30)
    clFlowItem_Update_L_802380A0:
    lwz r3, 0x28(r30)
    li r4, 0x0
    bl SpriteHandle_SetActiveFlag
    lwz r3, 0x24(r30)
    li r4, 0x0
    bl SpriteHandle_SetActiveFlag
    clFlowItem_Update_L_802380B8:
    lwz r3, 0x4(r30)
    mr r25, r30
    li r24, 0x0
    addi r0, r3, 0x1
    stw r0, 0x4(r30)
    clFlowItem_Update_L_802380CC:
    lwz r3, 0x1c(r25)
    cmplwi r3, 0x0
    beq clFlowItem_Update_L_802380E4
    lwz r3, 0x0(r3)
    lfs f1, lbl_806DB8A8(r2)
    bl Sprite_AdvanceAnim
    clFlowItem_Update_L_802380E4:
    addi r24, r24, 0x1
    addi r25, r25, 0x4
    cmpwi r24, 0x2
    blt clFlowItem_Update_L_802380CC
    li r24, 0x0
    mr r25, r30
    clFlowItem_Update_L_802380FC:
    lwz r3, 0x24(r25)
    bl SpriteHandle_RecomputeCull
    addi r24, r24, 0x1
    addi r25, r25, 0x4
    cmpwi r24, 0x4
    blt clFlowItem_Update_L_802380FC
    lwz r3, 0x18(r30)
    bl fn_80238D9C
    lwz r3, 0x14(r30)
    cmplwi r3, 0x0
    beq clFlowItem_Update_L_8023812C
    bl fn_8023A148
    clFlowItem_Update_L_8023812C:
    lfs f2, 0xc(r30)
    lfs f1, lbl_806DB888(r2)
    fcmpo cr0, f2, f1
    ble clFlowItem_Update_L_80238198
    lfs f0, lbl_806DB8AC(r2)
    fsubs f0, f2, f0
    stfs f0, 0xc(r30)
    lfs f0, 0xc(r30)
    fcmpo cr0, f0, f1
    bge clFlowItem_Update_L_8023815C
    lfs f0, lbl_806DB8A0(r2)
    stfs f0, 0xc(r30)
    clFlowItem_Update_L_8023815C:
    lwz r3, lbl_806D1A88(r13)
    li r24, 0x0
    cmplwi r3, 0x0
    beq clFlowItem_Update_L_80238170
    b clFlowItem_Update_L_80238190
    clFlowItem_Update_L_80238170:
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq clFlowItem_Update_L_80238188
    li r24, 0x1
    bl fn_802325FC
    clFlowItem_Update_L_80238188:
    stw r29, lbl_806D1A88(r13)
    mr r3, r29
    clFlowItem_Update_L_80238190:
    lfs f1, 0xc(r30)
    bl fn_80232284
    clFlowItem_Update_L_80238198:
    bl ItemDisplay_GetOrCreate
    bl ItemDisplay_Update
    lwz r3, 0x10(r30)
    lmw r24, 0x20(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

/* deleting destructor: shut the message window and item display down, tear
 * down every sprite resource, run the base dtor, optionally free self. */
void *clFlowItem_Dtor(clFlowItemRec *self, short freeFlag) {
    int i;

    if (self) {
        self->vtbl = lbl_804EE52C;
        fn_80169C44();
        ItemMsg_Get()->state = 4;
        ItemMsg_Destroy();
        ItemDisplay_Destroy();
        for (i = 0; i < 2; i++) {
            if (self->bgSpr[i]) {
                SpriteAnimHandle_Destroy(self->bgSpr[i], 1);
                self->bgSpr[i] = 0;
            }
        }
        if (self->itemSelection) {
            ItemSelectState_Dtor(self->itemSelection, 1);
            self->itemSelection = 0;
        }
        if (self->itemGrid) {
            delete self->itemGrid;
            self->itemGrid = 0;
        }
        for (i = 0; i < 4; i++) {
            SpriteHandle_Destroy(self->hudSpr[i]);
        }
        fn_80121210();
        dtor_801BA14C(self, 0);
        if (freeFlag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

} /* extern "C" */

/* real constructor @ 0x802383A0 - the new-expressions carry the DELETEPOINTER
 * guards, the ResCtrl local the DESTROYLOCAL region, the ctor body the
 * DESTROYBASE region. */
clFlowItem::clFlowItem() {
    this->frameCounter = 0;
    this->subState = 0;
    this->fadeAlpha = lbl_806DB8A0;
    this->nextSceneId = -1;
    this->itemGrid = 0;
    this->itemSelection = 0;
    this->bgSpr[0] = 0;
    this->bgSpr[1] = 0;
    this->itemSelection = new ItemSelectState;
    this->itemGrid = new ItemGridState;
    SetSyncTarget(0x22);
    if (GetInput() != 0) {
        InputRec *in = GetInput();
        in->active = 1;
        in->mode = 0;
        in->submode = 0;
    }
    InitBGM();
    SetupBgSprites(1);
    SpriteGroup_CreateOrInit(&this->bgSpr[1], lbl_806D077C, 1, lbl_806DB8B8, lbl_806DB8BC);
    SpriteGroup_CreateOrInit(&this->bgSpr[0], lbl_806D0780, 1, lbl_806DB8C0, lbl_806DB8C4);
    (*this->bgSpr[1])->mode = 6;
    (*this->bgSpr[0])->mode = 6;
    {
        ResCtrl desc;
        desc.resId = 0x1875;
        desc.flag = 1;
        desc.fA = lbl_806DB8C8;
        desc.fB = lbl_806DB8BC;
        desc.fC = lbl_806DB8CC;
        this->hudSpr[1] = SpriteHandle_CreateDefault(&desc, 6);
        fn_80121E10(&desc);
        desc.resId = 0x1874;
        desc.flag = 1;
        desc.fA = lbl_806DB8D0;
        desc.fB = lbl_806DB8BC;
        desc.fC = lbl_806DB8CC;
        this->hudSpr[0] = SpriteHandle_CreateDefault(&desc, 6);
        fn_80121E10(&desc);
        desc.mode = 2;
        desc.fD = lbl_806DB8D4;
        desc.fE = lbl_806DB8D8;
        desc.flag = 1;
        desc.fA = lbl_806DB8DC;
        desc.fB = lbl_806DB8E0;
        desc.fC = lbl_806DB8CC;
        desc.w0 = 0;
        desc.w1 = 0;
        desc.w2 = 0;
        desc.w3 = 0;
        this->hudSpr[2] = SpriteHandle_CreateDefault(&desc, 5);
        SpriteHandle_SetActiveFlag(this->hudSpr[2], 0);
        SpriteHandle_RecomputeCull(this->hudSpr[2]);
        fn_80121E10(&desc);
        desc.mode = 2;
        desc.fD = lbl_806DB8D4;
        desc.fE = lbl_806DB8D8;
        desc.flag = 1;
        desc.fA = lbl_806DB8DC;
        desc.fB = lbl_806DB8E0;
        desc.fC = lbl_806DB8CC;
        desc.w0 = 0;
        desc.w1 = 0;
        desc.w2 = 0;
        desc.w3 = 0;
        this->hudSpr[3] = SpriteHandle_CreateDefault(&desc, 7);
        SpriteHandle_SetActiveFlag(this->hudSpr[3], 0);
        SpriteHandle_RecomputeCull(this->hudSpr[3]);
        ItemMsg_Get();
        ItemMsg_Get()->state = 6;
        ItemDisplay_GetOrCreate();
        ItemDisplay_Start(ItemDisplay_GetOrCreate(), 0x1AE6);
        InitRumbleController(1);
    }
}

#pragma exceptions reset
