/* === extracted from auto_BtMode_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf();
extern void ItemUse_ResetAllKartUseSlots();
extern void ProcessSystemTick();
extern void RaceScene_ClearPlayerSlotPointers();
extern void RaceSlot_ResetAll();
extern void SetSyncTarget();
extern void VoiceSystem_Init();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_finalLapCoinJumpEnabled;
extern unsigned int g_gameMode;
extern unsigned int g_spawnedKartCount;
extern unsigned int lbl_806CF14C;
extern unsigned int lbl_806D1050;
extern unsigned int lbl_806D130C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80320960[];
extern unsigned int lbl_8040E734[];
extern unsigned int lbl_8040E76C[];

/* --- function index (1 fns, .text 0x800A05D0..0x800A0688) ---
 * [  0] 0x800A05D0 size:0xB8    global BtMode_Init
 */

/* --- forward decls --- */
asm void BtMode_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void dtor_800A0688();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; } extab_BtMode_Init = { 0x10080000, 0x00000048, 0x00110010, 0x00000000, 0x8680001E, 0x00000000, (void *)&dtor_800A0688 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_BtMode_Init = {
    (void *)&BtMode_Init, 0x000000B8, (void *)&extab_BtMode_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void BtMode_Init(void) { /* 0x800A05D0 size:0xB8 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, lbl_8040E76C@ha
    stw r0, 0x14(r1)
    addi r0, r4, lbl_8040E76C@l
    lis r4, lbl_80320960@ha
    stw r31, 0xc(r1)
    addi r31, r4, lbl_80320960@l
    stw r30, 0x8(r1)
    mr r30, r3
    lis r3, lbl_8040E734@ha
    stw r0, 0x0(r30)
    addi r3, r3, lbl_8040E734@l
    li r0, 0x2
    stw r3, 0x0(r30)
    li r3, 0x2a
    stw r0, g_gameMode(r13)
    bl SetSyncTarget
    bl RaceSlot_ResetAll
    li r0, 0x4
    stw r0, g_spawnedKartCount(r13)
    bl ItemUse_ResetAllKartUseSlots
    li r0, 0x0
    stb r0, g_finalLapCoinJumpEnabled(r13)
    bl RaceScene_ClearPlayerSlotPointers
    li r0, 0x0
    addi r3, r31, 0x7b4
    stw r0, lbl_806D1050(r13)
    bl ProcessSystemTick
    bl VoiceSystem_Init
    addi r3, r31, 0x7cc
    bl ProcessSystemTick
    addi r3, r31, 0x7e0
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, -0x1
    li r0, 0x0
    stw r3, lbl_806CF14C(r13)
    mr r3, r30
    stb r0, lbl_806D130C(r13)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


