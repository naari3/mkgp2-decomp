#include "game/ItemEffectBusPrivate.h"
#pragma auto_inline off
#pragma section R ".extab_user"
#pragma section R ".extabindex_user"

/* Item-effect state and driver action dispatch. Unconverted bodies retain the original assembly. */

/* === extracted from auto_ItemEffectBus_Commit_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartDriver_TickAction_78778();
extern void KartDriver_TickAction_78a3c();
extern void KartDriver_TickAction_78d00();

/* --- function index (1 fns, .text 0x8009107C..0x80091284) ---
 * [  0] 0x8009107C size:0x208   global ItemEffectBus_Commit
 */

/* --- forward decls --- */
void ItemEffectBus_Commit(ItemEffectBus *bus, ItemEffectMask mask);

/* Native body; exception tables are compiler emitted. */
#pragma exceptions on
void ItemEffectBus_Commit(ItemEffectBus *bus, ItemEffectMask mask)
{
    if (mask & 0x40000ULL) {
        if (!(bus->mask & 0x40000ULL))
            KartDriver_TickAction_78d00(bus->driver, 2);
    } else if (mask & 0x20ULL) {
        if (!(bus->mask & 0x20ULL)) {
            if (bus->actionMode == 1)
                KartDriver_TickAction_78a3c(bus->driver, 3);
            else
                KartDriver_TickAction_78778(bus->driver, 3);
        }
    } else if (mask & 0x8ULL) {
        if (!(bus->mask & 0x8ULL))
            KartDriver_TickAction_78d00(bus->driver, 0);
    } else if (mask & 0x10ULL) {
        if (!(bus->mask & 0x10ULL))
            KartDriver_TickAction_78d00(bus->driver, 1);
    } else if (mask & 0x400000ULL) {
        if (!(bus->mask & 0x400000ULL))
            KartDriver_TickAction_78d00(bus->driver, 4);
    } else if (bus->mask & 0x440038ULL) {
        KartDriver_TickAction_78d00(bus->driver, 0);
    }
    bus->mask = mask;
}
#pragma exceptions reset

/* Contiguous incumbent dtor at 0x80091284; folded into this TU so the
 * promoted split remains a single uninterrupted .text range. */
extern void MemoryManager_TimedFree(void *this);
void *dtor_80091284(void *bus, short deleting);

#pragma section R ".extab_user"


#pragma section R ".extabindex_user"


#pragma exceptions on
void *dtor_80091284(void *bus, short deleting)
{
    if (bus != 0 && deleting > 0)
        MemoryManager_TimedFree(bus);
    return bus;
}
#pragma exceptions reset

/* === extracted from auto_03_800912C0_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D34B0;

/* --- function index (1 fns, .text 0x800912C0..0x80091300) ---
 * [  0] 0x800912C0 size:0x40    global ItemEffectBus_Init
 */

/* --- forward decls --- */
void ItemEffectBus_Init(ItemEffectBus *bus, void *driver);

/* Native body; exception tables are compiler emitted. */
#pragma exceptions on
void ItemEffectBus_Init(ItemEffectBus *bus, void *driver)
{
    bus->driver = driver;
    bus->bonkPending = 0;
    bus->eventFlags = 0;
    bus->mask = 0;
    bus->snapshot = 0;
    bus->positionPending = 0;
    bus->timer24 = 0.0f;
    bus->timer28 = 0.0f;
    bus->timer48 = 0.0f;
    bus->field4C = 0;
    bus->tornadoCooldown = 0;
}
#pragma exceptions reset

/* === extracted from auto_ItemEffectBus_ClearB_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D34B8;
extern unsigned int lbl_806D34BC;
extern unsigned int lbl_806D34C0;
extern unsigned int lbl_806D34C4;
extern unsigned int lbl_806D34C8;
extern unsigned int lbl_806D34CC;
extern unsigned int lbl_806D34D0;
extern unsigned int lbl_806D34D4;
extern unsigned int lbl_806D34D8;
extern unsigned int lbl_806D34DC;
extern unsigned int lbl_806D34E0;
extern unsigned int lbl_806D34E4;
extern unsigned int lbl_806D34E8;
extern unsigned int lbl_806D34EC;
extern unsigned int lbl_806D34F0;
extern unsigned int lbl_806D34F4;

/* --- function index (1 fns, .text 0x80091300..0x800913F8) ---
 * [  0] 0x80091300 size:0xF8    global ItemEffectBus_ClearByTable8
 */

/* --- forward decls --- */
asm void ItemEffectBus_ClearByTable8(void);

/* --- asm function bodies (.text order = fn address order) --- */
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_ClearByTable8[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_ClearByTable8 = {
    (void *)&ItemEffectBus_ClearByTable8, 0x000000F8, (void *)extab_ItemEffectBus_ClearByTable8
};

asm void ItemEffectBus_ClearByTable8(void) { /* 0x80091300 size:0xF8 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r7, 0x0
    li r6, 0x0
    stw r0, 0x14(r1)
    clrlwi. r0, r4, 31
    beq ItemEffectBus_ClearByTable8_L_80091324
    lwz r6, lbl_806D34B8(r2)
    lwz r7, lbl_806D34BC(r2)
    ItemEffectBus_ClearByTable8_L_80091324:
    rlwinm. r0, r4, 0, 30, 30
    beq ItemEffectBus_ClearByTable8_L_8009133C
    lwz r0, lbl_806D34C0(r2)
    lwz r5, lbl_806D34C4(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_8009133C:
    rlwinm. r0, r4, 0, 29, 29
    beq ItemEffectBus_ClearByTable8_L_80091354
    lwz r0, lbl_806D34C8(r2)
    lwz r5, lbl_806D34CC(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_80091354:
    rlwinm. r0, r4, 0, 28, 28
    beq ItemEffectBus_ClearByTable8_L_8009136C
    lwz r0, lbl_806D34D0(r2)
    lwz r5, lbl_806D34D4(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_8009136C:
    rlwinm. r0, r4, 0, 27, 27
    beq ItemEffectBus_ClearByTable8_L_80091384
    lwz r0, lbl_806D34D8(r2)
    lwz r5, lbl_806D34DC(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_80091384:
    rlwinm. r0, r4, 0, 26, 26
    beq ItemEffectBus_ClearByTable8_L_8009139C
    lwz r0, lbl_806D34E0(r2)
    lwz r5, lbl_806D34E4(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_8009139C:
    rlwinm. r0, r4, 0, 25, 25
    beq ItemEffectBus_ClearByTable8_L_800913B4
    lwz r0, lbl_806D34E8(r2)
    lwz r5, lbl_806D34EC(r2)
    or r6, r6, r0
    or r7, r7, r5
    ItemEffectBus_ClearByTable8_L_800913B4:
    rlwinm. r0, r4, 0, 24, 24
    beq ItemEffectBus_ClearByTable8_L_800913CC
    lwz r0, lbl_806D34F0(r2)
    lwz r4, lbl_806D34F4(r2)
    or r6, r6, r0
    or r7, r7, r4
    ItemEffectBus_ClearByTable8_L_800913CC:
    nor r0, r6, r6
    lwz r5, 0x10(r3)
    lwz r6, 0x14(r3)
    nor r4, r7, r7
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_Regist_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- function index (1 fns, .text 0x800913F8..0x80091438) ---
 * [  0] 0x800913F8 size:0x40    global ItemEffectBus_RegisterBonkPosition
 */

/* --- forward decls --- */
void ItemEffectBus_RegisterBonkPosition(ItemEffectBus *bus, float x, float y, float z);

/* Native body; exception tables are compiler emitted. */
#pragma exceptions on
void ItemEffectBus_RegisterBonkPosition(ItemEffectBus *bus, float x, float y, float z)
{
    bus->bonkPosition[0] = x;
    bus->bonkPosition[1] = y;
    bus->bonkPosition[2] = z;
    bus->bonkPending = 1;
    ItemEffectBus_Commit(bus, bus->mask | 0x100000000ULL);
}
#pragma exceptions reset

/* === extracted from auto_ItemEffectBus_ApplyI_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D34B0;
extern unsigned int lbl_806D34B8;
extern unsigned int lbl_806D34BC;
extern unsigned int lbl_806D34C0;
extern unsigned int lbl_806D34C4;
extern unsigned int lbl_806D34C8;
extern unsigned int lbl_806D34CC;
extern unsigned int lbl_806D34D0;
extern unsigned int lbl_806D34D4;
extern unsigned int lbl_806D34D8;
extern unsigned int lbl_806D34DC;
extern unsigned int lbl_806D34E0;
extern unsigned int lbl_806D34E4;
extern unsigned int lbl_806D34E8;
extern unsigned int lbl_806D34EC;
extern unsigned int lbl_806D34F0;
extern unsigned int lbl_806D34F4;
extern unsigned int lbl_806D34F8;
extern unsigned int lbl_806D34FC;
extern unsigned int lbl_806D3500;
extern unsigned int lbl_806D3504;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803FF4E0[];

/* --- function index (1 fns, .text 0x80091438..0x8009185C) ---
 * [  0] 0x80091438 size:0x424   global ItemEffectBus_ApplyItemEventClear
 */

/* --- forward decls --- */
asm void ItemEffectBus_ApplyItemEventClear(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_ApplyItemEventClear[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_ApplyItemEventClear = {
    (void *)&ItemEffectBus_ApplyItemEventClear, 0x00000424, (void *)extab_ItemEffectBus_ApplyItemEventClear
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void ItemEffectBus_ApplyItemEventClear(void) { /* 0x80091438 size:0x424 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f0, lbl_806D34B0(r2)
    cmplwi r4, 0x121
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    li r31, 0x0
    stw r30, 0x8(r1)
    mr r30, r3
    stfs f0, 0x28(r3)
    bgt ItemEffectBus_ApplyItemEventClear_L_80091844
    lis r5, jumptable_803FF4E0@ha
    slwi r0, r4, 2
    addi r4, r5, jumptable_803FF4E0@l
    lwzx r0, r4, r0
    mtctr r0
    bctr
    lwz r31, lbl_806D34F8(r2)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r31, lbl_806D34FC(r2)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r31, lbl_806D3500(r2)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r3, 0x0(r30)
    li r4, 0x0
    lwz r31, lbl_806D3500(r2)
    stb r4, 0x2b1(r3)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lfs f0, lbl_806D34B0(r2)
    lwz r31, lbl_806D3504(r2)
    stfs f0, 0x28(r30)
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xff80
    lwz r5, 0x10(r30)
    li r0, -0x1
    lwz r6, 0x14(r30)
    subi r4, r4, 0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r4, 0x10(r30)
    li r0, -0x1
    lwz r6, 0x14(r30)
    and r5, r4, r0
    and r6, r6, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xc000
    lwz r5, 0x10(r30)
    li r0, -0x1
    lwz r6, 0x14(r30)
    subi r4, r4, 0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x11
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x9
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x9
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x21
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x1001
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfffe
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfffc
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfff8
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfff0
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xffe0
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x41
    lwz r6, 0x14(r30)
    li r4, -0x1
    mr r3, r30
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xffff
    lwz r5, 0x10(r30)
    addi r0, r4, 0x7fff
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x4001
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xffff
    lwz r5, 0x10(r30)
    subi r0, r4, 0x1
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lis r4, 0xfc00
    lwz r5, 0x10(r30)
    subi r0, r4, 0x2001
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r6, r6, r4
    and r5, r5, r0
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x401
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    lwz r5, 0x10(r30)
    li r0, -0x801
    lwz r6, 0x14(r30)
    li r4, -0x1
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    b ItemEffectBus_ApplyItemEventClear_L_80091764
    b ItemEffectBus_ApplyItemEventClear_L_80091844
    ItemEffectBus_ApplyItemEventClear_L_80091764:
    clrlwi. r3, r31, 31
    li r0, 0x0
    mr r6, r0
    beq ItemEffectBus_ApplyItemEventClear_L_8009177C
    lwz r6, lbl_806D34B8(r2)
    lwz r0, lbl_806D34BC(r2)
    ItemEffectBus_ApplyItemEventClear_L_8009177C:
    rlwinm. r3, r31, 0, 30, 30
    beq ItemEffectBus_ApplyItemEventClear_L_80091794
    lwz r3, lbl_806D34C0(r2)
    lwz r4, lbl_806D34C4(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_80091794:
    rlwinm. r3, r31, 0, 29, 29
    beq ItemEffectBus_ApplyItemEventClear_L_800917AC
    lwz r3, lbl_806D34C8(r2)
    lwz r4, lbl_806D34CC(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_800917AC:
    rlwinm. r3, r31, 0, 28, 28
    beq ItemEffectBus_ApplyItemEventClear_L_800917C4
    lwz r3, lbl_806D34D0(r2)
    lwz r4, lbl_806D34D4(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_800917C4:
    rlwinm. r3, r31, 0, 27, 27
    beq ItemEffectBus_ApplyItemEventClear_L_800917DC
    lwz r3, lbl_806D34D8(r2)
    lwz r4, lbl_806D34DC(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_800917DC:
    rlwinm. r3, r31, 0, 26, 26
    beq ItemEffectBus_ApplyItemEventClear_L_800917F4
    lwz r3, lbl_806D34E0(r2)
    lwz r4, lbl_806D34E4(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_800917F4:
    rlwinm. r3, r31, 0, 25, 25
    beq ItemEffectBus_ApplyItemEventClear_L_8009180C
    lwz r3, lbl_806D34E8(r2)
    lwz r4, lbl_806D34EC(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_8009180C:
    rlwinm. r3, r31, 0, 24, 24
    beq ItemEffectBus_ApplyItemEventClear_L_80091824
    lwz r3, lbl_806D34F0(r2)
    lwz r4, lbl_806D34F4(r2)
    or r6, r6, r3
    or r0, r0, r4
    ItemEffectBus_ApplyItemEventClear_L_80091824:
    lwz r5, 0x10(r30)
    nor r4, r6, r6
    lwz r6, 0x14(r30)
    nor r0, r0, r0
    mr r3, r30
    and r5, r5, r4
    and r6, r6, r0
    bl ItemEffectBus_Commit
    ItemEffectBus_ApplyItemEventClear_L_80091844:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_ApplyI_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803FF968[];

/* --- function index (1 fns, .text 0x8009185C..0x80091AC4) ---
 * [  0] 0x8009185C size:0x268   global ItemEffectBus_ApplyItemEventSet
 */

/* --- forward decls --- */
void ItemEffectBus_ApplyItemEventSet(ItemEffectBus *bus, unsigned int event, int mode);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"


/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"


/* --- asm function bodies (.text order = fn address order) --- */
#pragma exceptions on
void ItemEffectBus_ApplyItemEventSet(ItemEffectBus *bus, unsigned int event, int mode)
{
    ItemEffectMask add = 0;
    bus->actionMode = mode;
    ItemEffectBus_Commit(bus, bus->mask & 0x8FFFFFFFFFFFFFFFULL);
    switch (event) {
    case 0x58:
        add = 0x0000002000000000ULL; break;
    case 0x88:
        add = 0x0004000000000000ULL; break;
    case 0x8F:
        add = 0x0008000000000000ULL; break;
    case 0x93:
        add = 0x0010000000000000ULL; break;
    case 0x94:
        add = 0x0020000000000000ULL; break;
    case 0x12:
    case 0x45:
    case 0x5F:
    case 0x60:
    case 0x70:
        add = 0x0000000000080000ULL; break;
    case 0x39:
    case 0x3A:
    case 0x8E:
        add = 0x0200000000000000ULL; break;
    case 0x75:
        add = 0x0000001000000000ULL; break;
    case 0x55:
        add = 0x0000000800000000ULL; break;
    case 0x85:
        add = 0x0000000800000000ULL; break;
    case 0x2B:
        add = 0x0000000000000002ULL; break;
    case 0x2D:
        add = 0x0000000000000020ULL; break;
    case 0x46:
        add = 0x0000000000000020ULL; break;
    case 0x8D:
        add = 0x0000000000000020ULL; break;
    case 0x5C:
        add = 0x0000000000000008ULL; break;
    case 0x5D:
        add = 0x0000000000000010ULL; break;
    case 0x50:
        add = 0x0000000000000200ULL; break;
    case 0x65:
        add = 0x0000000000000800ULL; break;
    case 0x40:
        add = 0x0000000000000800ULL; break;
    case 0x4A:
    case 0x4B:
        add = 0x0000000000040000ULL; break;
    case 0x71:
        add = 0x0000000000200000ULL; break;
    case 0x72:
        add = 0x0000000000400000ULL; break;
    case 0x73:
        add = 0x0000000000100000ULL; break;
    case 0x53:
        add = 0x0000000008000000ULL; break;
    case 0x68:
    case 0x79:
        add = 0x0000004000000000ULL; break;
    case 0x5A:
        add = 0x0000000000000000ULL; break;
    case 0x67:
        add = 0x0000000200000000ULL; break;
    case 0x6B:
        add = 0x0000000400000000ULL; break;
    case 0x59:
        add = 0x0000000000800000ULL; break;
    case 0x98:
        add = 0x0000100000000000ULL; break;
    case 0x8:
    case 0x11C:
        add = 0x0100000000020000ULL; break;
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0x9:
    case 0xB:
    case 0x2E:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x37:
    case 0x38:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    case 0x4D:
    case 0x4F:
    case 0x61:
    case 0x63:
    case 0x6A:
    case 0x76:
    case 0x89:
    case 0x8A:
    case 0x96:
    case 0x121:
        add = 0x0100000000000000ULL; break;
    case 0x9E:
        add = 0x0000080000000000ULL; break;
    case 0x74:
        add = 0x0000000040000000ULL; break;
    case 0x95:
        add = 0x0002000000000000ULL; break;
    case 0x2C:
        add = 0x0000000000002000ULL; break;
    case 0x3C:
        add = 0x0000000002000000ULL; break;
    }
    add |= bus->mask;
    ItemEffectBus_Commit(bus, add);
}
#pragma exceptions reset

/* === extracted from auto_ItemEffectBus_ArmTor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- function index (1 fns, .text 0x80091AC4..0x80091B9C) ---
 * [  0] 0x80091AC4 size:0xD8    global ItemEffectBus_ArmTornadoAndQuery
 */

/* --- forward decls --- */
int ItemEffectBus_ArmTornadoAndQuery(ItemEffectBus *bus);

/* Native body; exception tables are compiler emitted. */
#pragma exceptions on
int ItemEffectBus_ArmTornadoAndQuery(ItemEffectBus *bus)
{
    bus->tornadoCooldown = 1;
    ItemEffectBus_Commit(bus, bus->mask | 0x10001ULL);
    if (bus->mask & 0x40ULL) return 0;
    if (bus->mask & 0x400ULL) return 0;
    if (bus->mask & 0x80ULL) return 0;
    return (bus->mask & 0x100000000000000ULL) == 0;
}
#pragma exceptions reset

/* === extracted from auto_ItemEffectBus_ApplyI_text_2 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D3508;
extern unsigned int lbl_806D350C;
extern unsigned int lbl_806D3510;
extern unsigned int lbl_806D3514;
extern unsigned int lbl_806D3518;
extern unsigned int lbl_806D351C;
extern unsigned int lbl_806D3520;
extern unsigned int lbl_806D3524;
extern unsigned int lbl_806D3528;
extern unsigned int lbl_806D352C;
extern unsigned int lbl_806D3530;
extern unsigned int lbl_806D3534;
extern unsigned int lbl_806D3538;
extern unsigned int lbl_806D353C;
extern unsigned int lbl_806D3540;
extern unsigned int lbl_806D3544;
extern unsigned int lbl_806D3548;
extern unsigned int lbl_806D354C;
extern unsigned int lbl_806D3550;
extern unsigned int lbl_806D3554;
extern unsigned int lbl_806D3558;
extern unsigned int lbl_806D355C;
extern unsigned int lbl_806D3560;
extern unsigned int lbl_806D3564;
extern unsigned int lbl_806D3568;
extern unsigned int lbl_806D356C;

/* --- function index (1 fns, .text 0x80091B9C..0x80091E40) ---
 * [  0] 0x80091B9C size:0x2A4   global ItemEffectBus_ApplyItemConfirm
 */

/* --- forward decls --- */
asm void ItemEffectBus_ApplyItemConfirm(void);

/* --- asm function bodies (.text order = fn address order) --- */
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_ApplyItemConfirm[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_ApplyItemConfirm = {
    (void *)&ItemEffectBus_ApplyItemConfirm, 0x000002A4, (void *)extab_ItemEffectBus_ApplyItemConfirm
};

asm void ItemEffectBus_ApplyItemConfirm(void) { /* 0x80091B9C size:0x2A4 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmpwi r4, 0x28
    stw r0, 0x14(r1)
    lwz r5, 0x10(r3)
    lwz r6, 0x14(r3)
    beq ItemEffectBus_ApplyItemConfirm_L_80091DAC
    bge ItemEffectBus_ApplyItemConfirm_L_80091C60
    cmpwi r4, 0x19
    beq ItemEffectBus_ApplyItemConfirm_L_80091E2C
    bge ItemEffectBus_ApplyItemConfirm_L_80091C18
    cmpwi r4, 0x11
    beq ItemEffectBus_ApplyItemConfirm_L_80091DD8
    bge ItemEffectBus_ApplyItemConfirm_L_80091BF8
    cmpwi r4, 0xe
    beq ItemEffectBus_ApplyItemConfirm_L_80091DAC
    bge ItemEffectBus_ApplyItemConfirm_L_80091BEC
    cmpwi r4, 0xc
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091BEC:
    cmpwi r4, 0x10
    bge ItemEffectBus_ApplyItemConfirm_L_80091DAC
    b ItemEffectBus_ApplyItemConfirm_L_80091DD8
    ItemEffectBus_ApplyItemConfirm_L_80091BF8:
    cmpwi r4, 0x17
    beq ItemEffectBus_ApplyItemConfirm_L_80091E2C
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    cmpwi r4, 0x15
    bge ItemEffectBus_ApplyItemConfirm_L_80091DAC
    cmpwi r4, 0x13
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091C18:
    cmpwi r4, 0x21
    beq ItemEffectBus_ApplyItemConfirm_L_80091DC0
    bge ItemEffectBus_ApplyItemConfirm_L_80091C48
    cmpwi r4, 0x1c
    beq ItemEffectBus_ApplyItemConfirm_L_80091DCC
    bge ItemEffectBus_ApplyItemConfirm_L_80091C3C
    cmpwi r4, 0x1b
    bge ItemEffectBus_ApplyItemConfirm_L_80091D0C
    b ItemEffectBus_ApplyItemConfirm_L_80091D84
    ItemEffectBus_ApplyItemConfirm_L_80091C3C:
    cmpwi r4, 0x1e
    bge ItemEffectBus_ApplyItemConfirm_L_80091DAC
    b ItemEffectBus_ApplyItemConfirm_L_80091D70
    ItemEffectBus_ApplyItemConfirm_L_80091C48:
    cmpwi r4, 0x24
    beq ItemEffectBus_ApplyItemConfirm_L_80091DAC
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    cmpwi r4, 0x23
    bge ItemEffectBus_ApplyItemConfirm_L_80091D48
    b ItemEffectBus_ApplyItemConfirm_L_80091CF8
    ItemEffectBus_ApplyItemConfirm_L_80091C60:
    cmpwi r4, 0x91
    beq ItemEffectBus_ApplyItemConfirm_L_80091DD8
    bge ItemEffectBus_ApplyItemConfirm_L_80091CA8
    cmpwi r4, 0x52
    beq ItemEffectBus_ApplyItemConfirm_L_80091D5C
    bge ItemEffectBus_ApplyItemConfirm_L_80091C90
    cmpwi r4, 0x3c
    beq ItemEffectBus_ApplyItemConfirm_L_80091D34
    bge ItemEffectBus_ApplyItemConfirm_L_80091E2C
    cmpwi r4, 0x2c
    beq ItemEffectBus_ApplyItemConfirm_L_80091D20
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091C90:
    cmpwi r4, 0x8c
    beq ItemEffectBus_ApplyItemConfirm_L_80091E08
    bge ItemEffectBus_ApplyItemConfirm_L_80091E2C
    cmpwi r4, 0x8b
    bge ItemEffectBus_ApplyItemConfirm_L_80091DD8
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091CA8:
    cmpwi r4, 0x9c
    beq ItemEffectBus_ApplyItemConfirm_L_80091E2C
    bge ItemEffectBus_ApplyItemConfirm_L_80091CCC
    cmpwi r4, 0x9a
    beq ItemEffectBus_ApplyItemConfirm_L_80091DF4
    bge ItemEffectBus_ApplyItemConfirm_L_80091D98
    cmpwi r4, 0x99
    bge ItemEffectBus_ApplyItemConfirm_L_80091DE0
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091CCC:
    cmpwi r4, 0x142
    beq ItemEffectBus_ApplyItemConfirm_L_80091CE4
    bge ItemEffectBus_ApplyItemConfirm_L_80091E2C
    cmpwi r4, 0x9e
    bge ItemEffectBus_ApplyItemConfirm_L_80091E2C
    b ItemEffectBus_ApplyItemConfirm_L_80091E1C
    ItemEffectBus_ApplyItemConfirm_L_80091CE4:
    lwz r0, lbl_806D3508(r2)
    lwz r4, lbl_806D350C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091CF8:
    lwz r0, lbl_806D3510(r2)
    lwz r4, lbl_806D3514(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D0C:
    lwz r0, lbl_806D3518(r2)
    lwz r4, lbl_806D351C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D20:
    lwz r0, lbl_806D3520(r2)
    lwz r4, lbl_806D3524(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D34:
    lwz r0, lbl_806D3528(r2)
    lwz r4, lbl_806D352C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D48:
    lwz r0, lbl_806D3530(r2)
    lwz r4, lbl_806D3534(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D5C:
    lwz r0, lbl_806D3538(r2)
    lwz r4, lbl_806D353C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D70:
    lwz r0, lbl_806D3540(r2)
    lwz r4, lbl_806D3544(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D84:
    lwz r0, lbl_806D3508(r2)
    lwz r4, lbl_806D350C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091D98:
    lwz r0, lbl_806D3548(r2)
    lwz r4, lbl_806D354C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DAC:
    lis r4, 0x2000
    ori r5, r5, 0x100
    addi r0, r4, 0x40
    or r6, r6, r0
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DC0:
    li r6, 0x80
    li r5, 0x80
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DCC:
    li r6, 0x0
    li r5, 0x80
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DD8:
    ori r6, r6, 0x140
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DE0:
    lwz r0, lbl_806D3550(r2)
    lwz r4, lbl_806D3554(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091DF4:
    lwz r0, lbl_806D3558(r2)
    lwz r4, lbl_806D355C(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091E08:
    lwz r0, lbl_806D3560(r2)
    lwz r4, lbl_806D3564(r2)
    or r5, r5, r0
    or r6, r6, r4
    b ItemEffectBus_ApplyItemConfirm_L_80091E2C
    ItemEffectBus_ApplyItemConfirm_L_80091E1C:
    lwz r0, lbl_806D3568(r2)
    lwz r4, lbl_806D356C(r2)
    or r5, r5, r0
    or r6, r6, r4
    ItemEffectBus_ApplyItemConfirm_L_80091E2C:
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_ClearM_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- function index (1 fns, .text 0x80091E40..0x80091E78) ---
 * [  0] 0x80091E40 size:0x38    global ItemEffectBus_ClearMask
 */

/* --- forward decls --- */
void ItemEffectBus_ClearMask(ItemEffectBus *bus, ItemEffectMask mask);

/* Native body; exception tables are compiler emitted. */
#pragma exceptions on
void ItemEffectBus_ClearMask(ItemEffectBus *bus, ItemEffectMask mask)
{
    ItemEffectBus_Commit(bus, bus->mask & ~mask);
}
#pragma exceptions reset

/* === extracted from auto_ItemEffectBus_OrMask_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- function index (1 fns, .text 0x80091E78..0x80091EA8) ---
 * [  0] 0x80091E78 size:0x30    global ItemEffectBus_OrMask
 */

/* --- forward decls --- */
void ItemEffectBus_OrMask(ItemEffectBus *bus, ItemEffectMask mask);

/* Native body; exception tables are compiler emitted. */
#pragma exceptions on
void ItemEffectBus_OrMask(ItemEffectBus *bus, ItemEffectMask mask)
{
    ItemEffectBus_Commit(bus, mask | bus->mask);
}
#pragma exceptions reset

/* === extracted from auto_ItemEffectBus_TickTo_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D3570;
extern unsigned int lbl_806D3574;

/* --- function index (1 fns, .text 0x80091EA8..0x80091F0C) ---
 * [  0] 0x80091EA8 size:0x64    global ItemEffectBus_TickTornadoCooldown
 */

/* --- forward decls --- */
asm void ItemEffectBus_TickTornadoCooldown(void);

/* --- asm function bodies (.text order = fn address order) --- */
__declspec(section ".extab_user") static const unsigned char extab_ItemEffectBus_TickTornadoCooldown[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ItemEffectBus_TickTornadoCooldown = {
    (void *)&ItemEffectBus_TickTornadoCooldown, 0x00000064, (void *)extab_ItemEffectBus_TickTornadoCooldown
};

asm void ItemEffectBus_TickTornadoCooldown(void) { /* 0x80091EA8 size:0x64 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r7, 0x0
    lis r6, 0xc000
    stw r0, 0x14(r1)
    lwz r4, 0x50(r3)
    cmpwi r4, 0x0
    ble ItemEffectBus_TickTornadoCooldown_L_80091ED4
    subi r0, r4, 0x1
    stw r0, 0x50(r3)
    b ItemEffectBus_TickTornadoCooldown_L_80091EE0
    ItemEffectBus_TickTornadoCooldown_L_80091ED4:
    lwz r0, lbl_806D3570(r2)
    lwz r7, lbl_806D3574(r2)
    or r6, r6, r0
    ItemEffectBus_TickTornadoCooldown_L_80091EE0:
    nor r0, r6, r6
    lwz r5, 0x10(r3)
    lwz r6, 0x14(r3)
    nor r4, r7, r7
    and r5, r5, r0
    and r6, r6, r4
    bl ItemEffectBus_Commit
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

/* === extracted from auto_ItemEffectBus_Snapsh_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- function index (1 fns, .text 0x80091F0C..0x80091F58) ---
 * [  0] 0x80091F0C size:0x4C    global ItemEffectBus_SnapshotAndClearSpawnFlags
 */

/* --- forward decls --- */
void ItemEffectBus_SnapshotAndClearSpawnFlags(ItemEffectBus *bus);

/* Native body; exception tables are compiler emitted. */
#pragma exceptions on
void ItemEffectBus_SnapshotAndClearSpawnFlags(ItemEffectBus *bus)
{
    bus->snapshot = bus->mask;
    ItemEffectBus_Commit(bus, bus->mask & 0xFFFFFFFFFFFF3EFFULL);
}
#pragma exceptions reset

/* === extracted from auto_ItemEffectBus_Snapsh_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */


/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D34B0;

/* --- function index (1 fns, .text 0x80091F58..0x80091FD4) ---
 * [  0] 0x80091F58 size:0x7C    global ItemEffectBus_SnapshotAndFullReset
 */

/* --- forward decls --- */
void ItemEffectBus_SnapshotAndFullReset(ItemEffectBus *bus);

/* Native body; exception tables are compiler emitted. */
#pragma exceptions on
void ItemEffectBus_SnapshotAndFullReset(ItemEffectBus *bus)
{
    bus->snapshot = bus->mask;
    ItemEffectBus_Commit(bus, bus->mask & 0xFD7FFFDC77FF14FEULL);
    bus->eventFlags = 0;
    bus->bonkPending = 0;
    bus->positionPending = 0;
    bus->position[0] = 0.0f;
    bus->position[1] = 0.0f;
    bus->position[2] = 0.0f;
}
#pragma exceptions reset

