/* === extracted from auto_BtMode_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf(const char *fmt, ...);
extern void ItemUse_ResetAllKartUseSlots();
extern void ProcessSystemTick(const char *name);
extern void RaceScene_ClearPlayerSlotPointers();
extern void RaceSlot_ResetAll();
extern void SetSyncTarget();
extern void VoiceSystem_Init();

/* --- extern decls: sda21-referenced data --- */
extern unsigned char g_finalLapCoinJumpEnabled;
extern unsigned int g_gameMode;
extern unsigned int g_spawnedKartCount;
extern int lbl_806CF14C;
extern unsigned int lbl_806D1050;
extern unsigned char lbl_806D130C;

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
void *BtMode_Init(void **self);

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

/* BtMode_Init @ 0x800A05D0: battle-mode scene constructor. Sets game mode 2
 * (battle), resets the race slots for four karts and starts the voice
 * system, logging each step. Written in C with explicit vtable stores
 * (base lbl_8040E76C, then derived lbl_8040E734): the C++ ctor form loads
 * the string-pool base after the derived vtable store instead of between
 * the two. The extab (base dtor cleanup) stays a manual emit above. */
void *BtMode_Init(void **self)
{
    const char *log;

    *self = lbl_8040E76C;
    log = (const char *)lbl_80320960;
    *self = lbl_8040E734;
    g_gameMode = 2;
    SetSyncTarget(0x2a);
    RaceSlot_ResetAll();
    g_spawnedKartCount = 4;
    ItemUse_ResetAllKartUseSlots();
    g_finalLapCoinJumpEnabled = 0;
    RaceScene_ClearPlayerSlotPointers();
    lbl_806D1050 = 0;
    ProcessSystemTick(log + 0x7b4);
    VoiceSystem_Init();
    ProcessSystemTick(log + 0x7cc);
    DebugPrintf(log + 0x7e0);
    lbl_806CF14C = -1;
    lbl_806D130C = 0;
    return self;
}
