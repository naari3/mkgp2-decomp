#include "game/singleton.h"
/*
 * clFlowItem - item-award flow scene (vtable clFlowItem_vtable_804EE52C).
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
 *   __vt__10clFlowItem        -> clFlowItem_vtable_804EE52C             (vtable store)
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
#include "game/types/AnimObj.h"

/* Roulette cell payload: typed so `delete` emits its own null check (the
 * second beq of the double-beq idiom). */
#include "game/types/GridCell.h"

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

#include "game/types/IconPack.h"

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
    void *vtbl;                      /* 0x00 - clFlowItem_vtable_804EE52C */
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
extern void fn_8020AC34(void *);
extern void ItemDisplay_Update(void *disp);
extern void ItemDisplay_Start(void *disp, int id);
extern void ItemDisplay_Destroy(void);
extern void fn_802321F8(ItemMsgWnd *wnd);
extern void fn_80232284(ItemMsgWnd *wnd, f32 alpha);
extern void fn_80232550(ItemMsgWnd *wnd, int flag);
extern void fn_802325FC(ItemMsgWnd *wnd); /* ItemMsgWnd ctor */
extern void *Alloc(unsigned long size);   /* operator new impl */
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
extern char clFlowItem_vtable_804EE52C[];          /* .data  - clFlowItem vtable */
extern char clFlowItem_Update_data_806D0758[4];         /* .sdata - sprite group desc */
extern char clFlowItem_Init_data_806D077C[4];         /* .sdata - sprite group desc */
extern char clFlowItem_Init_data_806D0780[4];         /* .sdata - sprite group desc */
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
    return SINGLETON_INSTANCE(g_pInputState);
}

/* ------------------------------------------------------------------ */
/* C++ model used by the constructor.                                 */
/* ------------------------------------------------------------------ */

/* Base class: ctor -> InitializeFrameSelection, dtor -> dtor_801BA14C (both
 * extern, bridged via --redefine-sym). Polymorphic so the vptr sits at 0. */
#include "game/types/clFlowBase.h"

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
 * Each sub-object draw is its own inline (IconPack / ItemGrid / ItemSelect):
 * the strength-reduced walker of a loop that is the last use of the inline's
 * parameter then reuses the parameter's register (no `mr` copy), as in the
 * target. Loop counters of later loops are separately scoped (`int k`): one
 * shared `i` merges their webs and shifts the callee-saved coloring.
 * tools/extab_order.json keeps the target extab/extabindex layout.
 */
static inline void IconPack_Draw(IconPack *icons) {
    if (icons->mode < 3) {
        int i;
        for (i = 0; i < 4; i++) {
            if (icons->handles[i]) {
                fn_801A0004(*(void **)icons->handles[i]);
            }
        }
        void *ctx = fn_801F8E58();
        for (int k = 0; k < 4; k++) {
            if (icons->vals[k]) {
                fn_801F8A34(ctx, icons->vals[k], 6);
            }
        }
    }
}

static inline void ItemGrid_Draw(ItemGridState *grid) {
    int i;
    int j;
    void *ctx;

    for (i = 0; i < 7; i++) {
        if (grid->anims[i]) {
            if (((AnimObj *)*(void **)grid->anims[i])->y > lbl_806DB888) {
                fn_801A0004(*(void **)grid->anims[i]);
            }
        }
    }
    ctx = fn_801F8E58();
    for (j = 0; j < 3; j++) {
        for (int k = 0; k < 4; k++) {
            if (grid->cells[j][k]) {
                fn_801F8A34(ctx, grid->cells[j][k], 6);
            }
        }
    }
}

static inline void ItemSelect_Draw(ItemSelectState *sel) {
    int i;

    for (i = 0; i < 9; i++) {
        if (sel->groups[i]) {
            fn_801A0004(*sel->groups[i]);
        }
    }
    fn_801F8A34(fn_801F8E58(), sel->aux, 5);
    IconPack_Draw(sel->icons);
}

extern "C" void clFlowItem_Draw(clFlowItem *self) {
    int i;

    for (i = 0; i < 2; i++) {
        if (self->bgSpr[i]) {
            fn_801A0004(*self->bgSpr[i]);
        }
    }
    ItemSelect_Draw(self->itemSelection);
    if (self->itemGrid) {
        ItemGrid_Draw(self->itemGrid);
    }
    fn_8020AC34(ItemDisplay_GetOrCreate());
    fn_802321F8(ItemMsg_Get());
}

extern "C" {

/* vtable tick entry: rumble bookkeeping, the 5-state award flow state
 * machine, sprite anim advance, and the display/message window updates.
 * Returns the next scene id (-1 = stay).
 *
 * The two selection-state updates are inline helpers taking the selection
 * pointer: a plain local `sel` gets its own web colored r24, while the
 * inlined parameter shares r31 with the &g_playerData cursor as in the
 * target.
 */
static inline void ItemSel_Begin(ItemSelectState *sel) {
    SpriteGroup_CreateOrInit(&sel->groups[0], clFlowItem_Update_data_806D0758, 0, lbl_806DB88C, lbl_806DB890);
    (*sel->groups[0])->mode = 5;
    sel->resultCode = 0;
    sel->phase = 1;
}
static inline void ItemSel_Ready(ItemSelectState *sel) {
    SpriteHandle_SetActiveFlag(sel->readySprite, 1);
    sel->resultCode = 0;
    sel->phase = 3;
}
int clFlowItem_Update(clFlowItemRec *self) {
    PlayerDataRec *pd = &g_playerData;
#define pd_ pd
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
        ItemSel_Begin(self->itemSelection);
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
                ItemSel_Ready(self->itemSelection);
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


/* deleting destructor: shut the message window and item display down, tear
 * down every sprite resource, run the base dtor, optionally free self. */
void *clFlowItem_Dtor(clFlowItemRec *self, short freeFlag) {
    int i;

    if (self) {
        self->vtbl = clFlowItem_vtable_804EE52C;
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
    SpriteGroup_CreateOrInit(&this->bgSpr[1], clFlowItem_Init_data_806D077C, 1, lbl_806DB8B8, lbl_806DB8BC);
    SpriteGroup_CreateOrInit(&this->bgSpr[0], clFlowItem_Init_data_806D0780, 1, lbl_806DB8C0, lbl_806DB8C4);
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
