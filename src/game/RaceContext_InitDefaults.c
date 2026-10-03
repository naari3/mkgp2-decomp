/* Bounded genuine C++ retrofit draft: approach 2, 88.20822% text,
 * 1428B versus 1460B target. Natural DESTROYBASE r29 begins PC40;
 * saved range r24..31 and end PC554 differ from target r22..31/PC570.
 * Original exact ASM follows unchanged. This draft is NOT a promotion. */
#if 0
/* Genuine C++ reconstruction of the observed RaceContext constructor.
 * Only the vptr/base lifetime and global storage accesses are established.
 * Authoritative target/callee assembly was used (Ghidra unavailable). */
#pragma cplusplus on
#pragma exceptions on

extern "C" {
void ItemTable_PopulateAliasedSlots(void);
int CreditMgr_GetCreditCount(int);
void *TitleTracker_GetOrCreateSingleton(void);
void fn_8018CC64(void);
void fn_801D7610(void *, unsigned char);
void *memset(void *, int, unsigned long);
extern int g_ccClass, g_consecutiveWinsTier, g_courseVariantIdx, g_cupId;
extern int g_currentSceneState, g_gameMode, g_humanPlayerCount, g_kartVariant;
extern int g_localPcbRole, g_longRoundFlag, g_reverseRoundFlag, g_timerModeEnabled;
extern int lbl_806CF10C, lbl_806CF110, lbl_806CF12C, lbl_806D1280, lbl_806D12D8;
extern unsigned char g_isCommHost, g_isPcbHost, g_lakituStartAnimDone, g_raceStarted;
extern unsigned char lbl_806D117C, lbl_806D1258, lbl_806D1259, lbl_806D1290;
extern unsigned char lbl_806D12B0, lbl_806D12E1, lbl_806D12E2;
extern unsigned char lbl_806D1264[3], lbl_806D12E4[3];
extern unsigned char lbl_805AC600[], lbl_80598A60[], lbl_805B2580[];
extern const float lbl_806D4790, lbl_806D4798;
}

struct RaceContextBase;
extern "C" RaceContextBase *lbl_806D12DC;
struct RaceContextBase {
    RaceContextBase() { lbl_806D12DC = this; }
    virtual ~RaceContextBase();
};
struct RaceContext : RaceContextBase {
    RaceContext();
    virtual ~RaceContext();
};
struct RaceSlot {
    int type, selection, enabled, pending, count;
    unsigned char item[3], unused;
};
struct RaceAux {
    int value, enabled;
    float current, limit;
};
struct RaceWideRow {
    unsigned char active, pad1;
    unsigned short count;
    unsigned char pad4[12];
    int selection, state;
    unsigned char flag18, flag19, pad1A[2];
    int value;
    float x, y;
    unsigned char enabled, pad29[3];
};

static inline void InitializeWideRow(RaceWideRow *row) {
    row->active = 0;
    row->count = 0;
    row->selection = -1;
    row->state = -1;
    row->flag18 = 0;
    row->flag19 = 0;
    row->value = 0;
    row->x = lbl_806D4790;
    row->y = lbl_806D4790;
    row->enabled = 1;
}

RaceContext::RaceContext() {
    unsigned char *farBank = lbl_805AC600 + 0x20000;
    unsigned char *storage = lbl_805AC600;
    RaceSlot *slots = (RaceSlot *)storage;

    ItemTable_PopulateAliasedSlots();
    if (lbl_806D1259 != 1) {
        unsigned char *destination = lbl_805B2580;
        int bank = 0;
        unsigned char *settings = lbl_80598A60;
        do {
            memset(destination, (signed char)((signed char)settings[0x21] - 1), 0x8000);
            ++bank;
            destination += 0x8000;
        } while (bank <= 3);
        lbl_806D1259 = 1;
    }

    g_timerModeEnabled = 1;
    g_cupId = 1;
    g_longRoundFlag = 0;
    g_courseVariantIdx = 0;
    g_reverseRoundFlag = 0;
    {
        int *counts = (int *)(farBank + 0x6338);
        for (int i = 0; i < 8; ++i) {
            slots[i].type = -1;
            slots[i].selection = -1;
            slots[i].enabled = 1;
            slots[i].item[0] = 0x24;
            slots[i].item[1] = 0x25;
            slots[i].item[2] = 0x26;
            slots[i].count = 0;
            counts[i] = 0;
        }
    }
    if (g_cupId >= 0 && g_longRoundFlag >= 0) {
        g_raceStarted = 0;
    }

    unsigned char initialized = lbl_806D1258;
    lbl_806CF10C = 0;
    if (initialized == 0) {
        RaceAux *aux = (RaceAux *)(storage + 0x5ECC);
        RaceWideRow *rows = (RaceWideRow *)(farBank + 0x6348);
        for (int i = 0; i < 5; ++i) {
            aux[i].value = 0;
            aux[i].enabled = 0;
            aux[i].current = lbl_806D4790;
            aux[i].limit = lbl_806D4798;
        }
        for (int i = 5; i < 10; ++i) {
            aux[i].value = 0;
            aux[i].enabled = 1;
            aux[i].current = lbl_806D4790;
            aux[i].limit = lbl_806D4798;
        }
        RaceAux *last = (RaceAux *)(storage + 0x5F6C);
        last->value = 0;
        last->enabled = 0;
        last->current = lbl_806D4790;
        last->limit = lbl_806D4798;
        lbl_806D1280 = 4;
        lbl_806D1258 = 1;
        InitializeWideRow(&rows[0]);
        InitializeWideRow(&rows[1]);
        InitializeWideRow(&rows[2]);
        InitializeWideRow(&rows[3]);
        InitializeWideRow(&rows[4]);
        InitializeWideRow(&rows[5]);
        InitializeWideRow(&rows[6]);
        InitializeWideRow(&rows[7]);
        lbl_806D12D8 = 0;
    }

    g_ccClass = 0;
    for (int i = 0; i < 7; ++i) {
        slots[i].type = 6;
        slots[i].selection = i + 1;
        slots[i].enabled = 1;
        slots[i].pending = 0;
        slots[i].count = 0;
    }
    slots[7].type = 0;
    slots[7].selection = 0;
    slots[7].enabled = 1;
    slots[7].pending = 0;
    slots[7].count = 0;
    slots[7].item[0] = 0x2B;
    slots[7].item[1] = 0x2D;
    slots[7].item[2] = 0x32;
    lbl_806D1264[0] = 0x2B;
    lbl_806D1264[1] = 0x2D;
    lbl_806D1264[2] = 0x32;
    g_lakituStartAnimDone = 0;
    lbl_806D1290 = 0;
    lbl_806CF110 = 1;
    g_gameMode = 0;
    g_isCommHost = 0;
    g_currentSceneState = 2;
    g_isPcbHost = 0;
    g_localPcbRole = 0;
    lbl_806D12B0 = 0;
    g_kartVariant = -1;
    g_humanPlayerCount = -1;
    g_consecutiveWinsTier = 0;
    lbl_806CF12C = -1;
    memset(farBank + 0x5F80, 0, 0x1DC);
    fn_801D7610(farBank + 0x5F80, 1);
    fn_8018CC64();
    TitleTracker_GetOrCreateSingleton();
    bool noCredit = CreditMgr_GetCreditCount(0) == 0;
    lbl_806D12E1 = 0;
    lbl_806D117C = noCredit;
    lbl_806D12E2 = 0;
    lbl_806D12E4[0] = 0;
    lbl_806D12E4[1] = 0;
    lbl_806D12E4[2] = 0;
}
#pragma exceptions reset
#pragma cplusplus off
#endif

/* === extracted from auto_RaceContext_InitDefa_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CreditMgr_GetCreditCount();
extern void ItemTable_PopulateAliasedSlots();
extern void TitleTracker_GetOrCreateSingleton();
extern void fn_8018CC64();
extern void fn_801D7610();
extern void memset();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_consecutiveWinsTier;
extern unsigned int g_courseVariantIdx;
extern unsigned int g_cupId;
extern unsigned int g_currentSceneState;
extern unsigned int g_gameMode;
extern unsigned int g_humanPlayerCount;
extern unsigned int g_isCommHost;
extern unsigned int g_isPcbHost;
extern unsigned int g_kartVariant;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_localPcbRole;
extern unsigned int g_longRoundFlag;
extern unsigned int g_raceStarted;
extern unsigned int g_reverseRoundFlag;
extern unsigned int g_timerModeEnabled;
extern unsigned int lbl_806CF10C;
extern unsigned int lbl_806CF110;
extern unsigned int lbl_806CF12C;
extern unsigned int lbl_806D117C;
extern unsigned int lbl_806D1258;
extern unsigned int lbl_806D1259;
extern unsigned int lbl_806D1264;
extern unsigned int lbl_806D1280;
extern unsigned int lbl_806D1290;
extern unsigned int lbl_806D12B0;
extern unsigned int lbl_806D12D8;
extern unsigned int lbl_806D12DC;
extern unsigned int lbl_806D12E1;
extern unsigned int lbl_806D12E2;
extern unsigned int lbl_806D12E4;
extern unsigned int lbl_806D4790;
extern unsigned int lbl_806D4798;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8040E4D0[];
extern unsigned int lbl_8040E4DC[];
extern unsigned int lbl_80598A60[];
extern unsigned int lbl_805AC600[];
extern unsigned int lbl_805B2580[];

/* --- function index (1 fns, .text 0x8009D6CC..0x8009DC80) ---
 * [  0] 0x8009D6CC size:0x5B4   global RaceContext_InitDefaults
 */

/* --- forward decls --- */
asm void RaceContext_InitDefaults(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void dtor_8009DCE0();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; } extab_RaceContext_InitDefaults = { 0x500A0000, 0x00000040, 0x014C0010, 0x00000000, 0x8680001D, 0x00000000, (void *)&dtor_8009DCE0 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RaceContext_InitDefaults = {
    (void *)&RaceContext_InitDefaults, 0x000005B4, (void *)&extab_RaceContext_InitDefaults
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RaceContext_InitDefaults(void) { /* 0x8009D6CC size:0x5B4 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r5, lbl_8040E4DC@ha
    lis r4, lbl_8040E4D0@ha
    stw r0, 0x34(r1)
    lis r6, lbl_805AC600@ha
    addi r0, r4, lbl_8040E4D0@l
    stmw r22, 0x8(r1)
    mr r29, r3
    addi r3, r5, lbl_8040E4DC@l
    addi r30, r6, lbl_805AC600@l
    addis r31, r30, 0x2
    stw r3, 0x0(r29)
    stw r29, lbl_806D12DC(r13)
    stw r0, 0x0(r29)
    bl ItemTable_PopulateAliasedSlots
    lbz r0, lbl_806D1259(r13)
    cmplwi r0, 0x1
    beq RaceContext_InitDefaults_L_8009D768
    lis r4, lbl_805B2580@ha
    lis r3, lbl_80598A60@ha
    addi r24, r4, lbl_805B2580@l
    li r25, 0x0
    addi r23, r3, lbl_80598A60@l
    lis r22, 0x1
    RaceContext_InitDefaults_L_8009D730:
    lbz r0, 0x21(r23)
    mr r3, r24
    addi r5, r22, -0x8000
    extsb r4, r0
    subi r0, r4, 0x1
    extsb r4, r0
    bl memset
    addi r25, r25, 0x1
    addis r24, r24, 0x1
    cmpwi r25, 0x3
    addi r24, r24, -0x8000
    ble RaceContext_InitDefaults_L_8009D730
    li r0, 0x1
    stb r0, lbl_806D1259(r13)
    RaceContext_InitDefaults_L_8009D768:
    li r8, 0x0
    addi r6, r30, 0x0
    li r7, -0x1
    li r9, 0x1
    li r5, 0x24
    li r4, 0x25
    li r0, 0x26
    addi r3, r31, 0x6338
    stw r9, g_timerModeEnabled(r13)
    stw r9, g_cupId(r13)
    stw r8, g_longRoundFlag(r13)
    stw r8, g_courseVariantIdx(r13)
    stw r8, g_reverseRoundFlag(r13)
    stw r7, 0x0(r30)
    stw r7, 0x4(r6)
    stw r9, 0x8(r6)
    stb r5, 0x14(r6)
    stb r4, 0x15(r6)
    stb r0, 0x16(r6)
    stw r8, 0x10(r6)
    stw r8, 0x6338(r31)
    stw r7, 0x18(r6)
    stw r7, 0x1c(r6)
    stw r9, 0x20(r6)
    stb r5, 0x2c(r6)
    stb r4, 0x2d(r6)
    stb r0, 0x2e(r6)
    stw r8, 0x28(r6)
    stw r8, 0x4(r3)
    stw r7, 0x30(r6)
    stw r7, 0x34(r6)
    stw r9, 0x38(r6)
    stb r5, 0x44(r6)
    stb r4, 0x45(r6)
    stb r0, 0x46(r6)
    stw r8, 0x40(r6)
    stw r8, 0x8(r3)
    stw r7, 0x48(r6)
    stw r7, 0x4c(r6)
    stw r9, 0x50(r6)
    stb r5, 0x5c(r6)
    stb r4, 0x5d(r6)
    stb r0, 0x5e(r6)
    stw r8, 0x58(r6)
    stw r8, 0xc(r3)
    stw r7, 0x60(r6)
    stw r7, 0x64(r6)
    stw r9, 0x68(r6)
    stb r5, 0x74(r6)
    stb r4, 0x75(r6)
    stb r0, 0x76(r6)
    stw r8, 0x70(r6)
    stw r8, 0x10(r3)
    stw r7, 0x78(r6)
    stw r7, 0x7c(r6)
    stw r9, 0x80(r6)
    stb r5, 0x8c(r6)
    stb r4, 0x8d(r6)
    stb r0, 0x8e(r6)
    stw r8, 0x88(r6)
    stw r8, 0x14(r3)
    stw r7, 0x90(r6)
    stw r7, 0x94(r6)
    stw r9, 0x98(r6)
    stb r5, 0xa4(r6)
    stb r4, 0xa5(r6)
    stb r0, 0xa6(r6)
    stw r8, 0xa0(r6)
    stw r8, 0x18(r3)
    stw r7, 0xa8(r6)
    stw r7, 0xac(r6)
    stw r9, 0xb0(r6)
    stb r5, 0xbc(r6)
    stb r4, 0xbd(r6)
    stb r0, 0xbe(r6)
    stw r8, 0xb8(r6)
    stw r8, 0x1c(r3)
    lwz r0, g_cupId(r13)
    cmpwi r0, 0x0
    blt RaceContext_InitDefaults_L_8009D8B8
    lwz r0, g_longRoundFlag(r13)
    cmpwi r0, 0x0
    blt RaceContext_InitDefaults_L_8009D8B8
    stb r8, g_raceStarted(r13)
    RaceContext_InitDefaults_L_8009D8B8:
    lbz r0, lbl_806D1258(r13)
    li r5, 0x0
    stw r5, lbl_806CF10C(r13)
    cmplwi r0, 0x0
    bne RaceContext_InitDefaults_L_8009DAE8
    addi r9, r30, 0x5ecc
    addi r8, r31, 0x6348
    stw r5, 0x0(r9)
    li r0, -0x1
    lfs f1, lbl_806D4790(r2)
    li r7, 0x1
    stw r5, 0x4(r9)
    addi r4, r30, 0x5f6c
    lfs f0, lbl_806D4798(r2)
    li r3, 0x4
    stfs f1, 0x8(r9)
    stfs f0, 0xc(r9)
    stw r5, 0x10(r9)
    stw r5, 0x14(r9)
    stfs f1, 0x18(r9)
    stfs f0, 0x1c(r9)
    stw r5, 0x20(r9)
    stw r5, 0x24(r9)
    stfs f1, 0x28(r9)
    stfs f0, 0x2c(r9)
    stw r5, 0x30(r9)
    stw r5, 0x34(r9)
    stfs f1, 0x38(r9)
    stfs f0, 0x3c(r9)
    stw r5, 0x40(r9)
    stw r5, 0x44(r9)
    stfs f1, 0x48(r9)
    stfs f0, 0x4c(r9)
    stw r5, 0x50(r9)
    stw r7, 0x54(r9)
    stfs f1, 0x58(r9)
    stfs f0, 0x5c(r9)
    stw r5, 0x60(r9)
    stw r7, 0x64(r9)
    stfs f1, 0x68(r9)
    stfs f0, 0x6c(r9)
    stw r5, 0x70(r9)
    stw r7, 0x74(r9)
    stfs f1, 0x78(r9)
    stfs f0, 0x7c(r9)
    stw r5, 0x80(r9)
    stw r7, 0x84(r9)
    stfs f1, 0x88(r9)
    stfs f0, 0x8c(r9)
    stw r5, 0x90(r9)
    stw r7, 0x94(r9)
    stfs f1, 0x98(r9)
    stfs f0, 0x9c(r9)
    stw r5, 0x5f6c(r30)
    stw r5, 0x4(r4)
    stfs f1, 0x8(r4)
    stfs f0, 0xc(r4)
    stw r3, lbl_806D1280(r13)
    stb r7, lbl_806D1258(r13)
    stb r5, 0x0(r8)
    sth r5, 0x2(r8)
    stw r0, 0x10(r8)
    stw r0, 0x14(r8)
    stb r5, 0x18(r8)
    stb r5, 0x19(r8)
    stw r5, 0x1c(r8)
    stfs f1, 0x20(r8)
    stfs f1, 0x24(r8)
    stb r7, 0x28(r8)
    stb r5, 0x2c(r8)
    sth r5, 0x2e(r8)
    stw r0, 0x3c(r8)
    stw r0, 0x40(r8)
    stb r5, 0x44(r8)
    stb r5, 0x45(r8)
    stw r5, 0x48(r8)
    stfs f1, 0x4c(r8)
    stfs f1, 0x50(r8)
    stb r7, 0x54(r8)
    stb r5, 0x58(r8)
    sth r5, 0x5a(r8)
    stw r0, 0x68(r8)
    stw r0, 0x6c(r8)
    stb r5, 0x70(r8)
    stb r5, 0x71(r8)
    stw r5, 0x74(r8)
    stfs f1, 0x78(r8)
    stfs f1, 0x7c(r8)
    stb r7, 0x80(r8)
    stb r5, 0x84(r8)
    sth r5, 0x86(r8)
    stw r0, 0x94(r8)
    stw r0, 0x98(r8)
    stb r5, 0x9c(r8)
    stb r5, 0x9d(r8)
    stw r5, 0xa0(r8)
    stfs f1, 0xa4(r8)
    stfs f1, 0xa8(r8)
    stb r7, 0xac(r8)
    stb r5, 0xb0(r8)
    sth r5, 0xb2(r8)
    stw r0, 0xc0(r8)
    stw r0, 0xc4(r8)
    stb r5, 0xc8(r8)
    stb r5, 0xc9(r8)
    stw r5, 0xcc(r8)
    stfs f1, 0xd0(r8)
    stfs f1, 0xd4(r8)
    stb r7, 0xd8(r8)
    stb r5, 0xdc(r8)
    sth r5, 0xde(r8)
    stw r0, 0xec(r8)
    stw r0, 0xf0(r8)
    stb r5, 0xf4(r8)
    stb r5, 0xf5(r8)
    stw r5, 0xf8(r8)
    stfs f1, 0xfc(r8)
    stfs f1, 0x100(r8)
    stb r7, 0x104(r8)
    stb r5, 0x108(r8)
    sth r5, 0x10a(r8)
    stw r0, 0x118(r8)
    stw r0, 0x11c(r8)
    stb r5, 0x120(r8)
    stb r5, 0x121(r8)
    stw r5, 0x124(r8)
    stfs f1, 0x128(r8)
    stfs f1, 0x12c(r8)
    stb r7, 0x130(r8)
    stb r5, 0x134(r8)
    sth r5, 0x136(r8)
    stw r0, 0x144(r8)
    stw r0, 0x148(r8)
    stb r5, 0x14c(r8)
    stb r5, 0x14d(r8)
    stw r5, 0x150(r8)
    stfs f1, 0x154(r8)
    stfs f1, 0x158(r8)
    stb r7, 0x15c(r8)
    stw r5, lbl_806D12D8(r13)
    RaceContext_InitDefaults_L_8009DAE8:
    li r22, 0x0
    li r24, 0x1
    addi r25, r30, 0x0
    li r23, 0x6
    li r0, -0x1
    li r26, 0x2
    li r10, 0x2b
    li r27, 0x3
    li r28, 0x4
    li r12, 0x5
    li r11, 0x7
    li r9, 0x2d
    li r8, 0x32
    addi r7, r13, -0x5ABC  /* lbl_806D1264 */
    stw r22, g_ccClass(r13)
    addi r3, r31, 0x5f80
    li r4, 0x0
    li r5, 0x1dc
    stw r23, 0x0(r30)
    stw r24, 0x4(r6)
    stw r24, 0x8(r6)
    stw r22, 0xc(r25)
    stw r22, 0x10(r6)
    stw r23, 0x18(r6)
    stw r26, 0x1c(r6)
    stw r24, 0x20(r6)
    stw r22, 0x24(r25)
    stw r22, 0x28(r6)
    stw r23, 0x30(r6)
    stw r27, 0x34(r6)
    stw r24, 0x38(r6)
    stw r22, 0x3c(r25)
    stw r22, 0x40(r6)
    stw r23, 0x48(r6)
    stw r28, 0x4c(r6)
    stw r24, 0x50(r6)
    stw r22, 0x54(r25)
    stw r22, 0x58(r6)
    stw r23, 0x60(r6)
    stw r12, 0x64(r6)
    stw r24, 0x68(r6)
    stw r22, 0x6c(r25)
    stw r22, 0x70(r6)
    stw r23, 0x78(r6)
    stw r23, 0x7c(r6)
    stw r24, 0x80(r6)
    stw r22, 0x84(r25)
    stw r22, 0x88(r6)
    stw r23, 0x90(r6)
    stw r11, 0x94(r6)
    stw r24, 0x98(r6)
    stw r22, 0x9c(r25)
    stw r22, 0xa0(r6)
    stw r22, 0xa8(r6)
    stw r22, 0xac(r6)
    stw r24, 0xb0(r6)
    stw r22, 0xb4(r25)
    stw r22, 0xb8(r6)
    stb r10, 0xbc(r6)
    stb r9, 0xbd(r6)
    stb r8, 0xbe(r6)
    stb r10, lbl_806D1264(r13)
    stb r9, 0x1(r7)
    stb r8, 0x2(r7)
    stb r22, g_lakituStartAnimDone(r13)
    stb r22, lbl_806D1290(r13)
    stw r24, lbl_806CF110(r13)
    stw r22, g_gameMode(r13)
    stb r22, g_isCommHost(r13)
    stw r26, g_currentSceneState(r13)
    stb r22, g_isPcbHost(r13)
    stw r22, g_localPcbRole(r13)
    stb r22, lbl_806D12B0(r13)
    stw r0, g_kartVariant(r13)
    stw r0, g_humanPlayerCount(r13)
    stw r22, g_consecutiveWinsTier(r13)
    stw r0, lbl_806CF12C(r13)
    bl memset
    addi r3, r31, 0x5f80
    li r4, 0x1
    bl fn_801D7610
    bl fn_8018CC64
    bl TitleTracker_GetOrCreateSingleton
    li r3, 0x0
    bl CreditMgr_GetCreditCount
    cntlzw r3, r3
    li r5, 0x1
    li r0, 0x0
    addi r4, r13, -0x5A3C  /* lbl_806D12E4 */
    rlwnm r5, r5, r3, 31, 31
    stb r0, lbl_806D12E1(r13)
    mr r3, r29
    stb r5, lbl_806D117C(r13)
    stb r0, lbl_806D12E2(r13)
    stb r0, lbl_806D12E4(r13)
    stb r0, 0x1(r4)
    stb r0, 0x2(r4)
    lmw r22, 0x8(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

