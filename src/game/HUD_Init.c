/* === extracted from auto_HUD_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void DoublyLinkedList_Init();
extern void fn_801477BC();
extern void fn_80149CD8();
extern void fn_8020E3AC();
extern void fn_80215708();
extern void fn_80215DB0();
extern void fn_80217E9C();
extern void fn_8021819C();
extern void fn_8022B9B0();
extern void fn_80243958();
extern void fn_802512AC();
extern void fn_802518C8();
extern void fn_80252D6C();
extern void memset();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_cupId;
extern unsigned int g_gameMode;
extern unsigned int lbl_806DC1DC;
extern unsigned int lbl_806DC1E0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_804ECAC0[];
extern unsigned int lbl_804ECB44[];

/* --- function index (1 fns, .text 0x8025421C..0x80254330) ---
 * [  0] 0x8025421C size:0x114   global HUD_Init
 */

/* --- forward decls --- */
asm void HUD_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_8020EB04();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; unsigned int f9; void *f10; } extab_HUD_Init = { 0x180A0000, 0x00000044, 0x00000018, 0x0000009C, 0x00160020, 0x00000000, 0x8A80001E, (void *)&MemoryManager_TimedFree, 0x8780001D, 0x00000000, (void *)&dtor_8020EB04 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_HUD_Init = {
    (void *)&HUD_Init, 0x00000114, (void *)&extab_HUD_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void HUD_Init(void) { /* 0x8025421C size:0x114 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r4
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r3
    li r3, 0x10
    bl Alloc
    mr. r30, r3
    beq HUD_Init_L_8025426C
    lis r4, lbl_804ECAC0@ha
    addi r3, r30, 0x4
    addi r0, r4, lbl_804ECAC0@l
    stw r0, 0x0(r30)
    bl DoublyLinkedList_Init
    lis r3, lbl_804ECB44@ha
    addi r0, r3, lbl_804ECB44@l
    stw r0, 0x0(r30)
    HUD_Init_L_8025426C:
    stw r30, 0x0(r29)
    li r0, 0x3
    li r4, 0x5
    li r6, 0x0
    stw r0, 0x4(r29)
    li r0, -0x1
    lfs f1, lbl_806DC1DC(r2)
    addi r3, r29, 0x10
    stw r4, 0x8(r29)
    li r4, 0x0
    lfs f0, lbl_806DC1E0(r2)
    li r5, 0x5c
    stw r31, 0xc(r29)
    stw r6, 0x6c(r29)
    stfs f1, 0x70(r29)
    stfs f0, 0x78(r29)
    stfs f0, 0x74(r29)
    stw r0, 0x7c(r29)
    bl memset
    lwz r0, g_cupId(r13)
    cmpwi r0, 0x9
    blt HUD_Init_L_802542E0
    cmpwi r0, 0x10
    bgt HUD_Init_L_802542E0
    bl fn_802518C8
    bl fn_80217E9C
    bl fn_8021819C
    bl fn_801477BC
    b HUD_Init_L_80254300
    HUD_Init_L_802542E0:
    bl fn_802512AC
    bl fn_802518C8
    bl fn_80215708
    bl fn_8020E3AC
    bl fn_8022B9B0
    bl fn_80252D6C
    bl fn_80243958
    bl fn_80215DB0
    HUD_Init_L_80254300:
    lwz r0, g_gameMode(r13)
    cmpwi r0, 0x2
    bne HUD_Init_L_80254310
    bl fn_80149CD8
    HUD_Init_L_80254310:
    lwz r0, 0x24(r1)
    mr r3, r29
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

