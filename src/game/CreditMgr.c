/*
 * Credit manager: coin/credit banner, queries and acceptor polling,
 * 0x80081184..0x8008299C.
 */

typedef struct CoinCounters {
    unsigned char pad00[0x10];
    unsigned int coins; /* 0x10 */
    unsigned char pad14[0x04];
    unsigned int credits; /* 0x18 */
    unsigned char pad1C[0x24];
} CoinCounters;

typedef struct CreditCfg {
    unsigned char pad00[0x0C];
    unsigned int coinsSeen; /* 0x0C */
    unsigned int creditsSeen; /* 0x10 */
    unsigned char pad14[0x3C];
    unsigned char freeVs2P; /* 0x50 */
    unsigned char freeVs3P; /* 0x51 */
    unsigned char freeVs4P; /* 0x52 */
} CreditCfg;

typedef struct CoinStatus {
    int credits; /* 0x00 */
    int coins; /* 0x04 */
    unsigned int coinsPerCredit; /* 0x08 */
    unsigned char pad0C[0x34];
} CoinStatus;

typedef struct CoinConfig {
    unsigned char pad00[0x08];
    unsigned char mode; /* 0x08 */
    unsigned char pad09[0x02];
    unsigned char divisor; /* 0x0B */
    unsigned char perSlot[0x14]; /* 0x0C */
} CoinConfig;

extern CreditCfg lbl_80598A60;
extern int lbl_806D1180; /* active slot */
extern int lbl_806D1184; /* last queried slot */
extern unsigned char lbl_806D117C;
extern unsigned char lbl_806D117D; /* polling disabled */

unsigned int fn_80288CC8(int ch);
int fn_80288F6C(int ch, int kind);
unsigned int fn_80289040(int ch, int alt);
void fn_80289A90(CoinCounters *out);
void fn_80289B04(CoinStatus *out);
void fn_80289B7C(CoinConfig *out);
void MemoryManager_TimedFree(void *p);
void *dtor_80082960(void *p, short flags);
void PlayStats_IncCoinInserted(void);
void PlayStats_IncCreditAdded(void);
void PlayStats_PublishCoinCreditShadow(void);
void PlayStats_IncSinglePlayJoin(void);
void PlayStats_IncVs2PJoin(void);
void PlayStats_IncVs2PlusJoin(void);
void PlayStats_IncVs3PlusJoin(void);
void PlayStats_IncVs4PJoin(void);
void PlayStats_BeginPlaySession(void);
void SoundMgr_Play(int id);
int CreditMgr_GetCreditCount(int slot);

extern void ResCtrl_Init();
double fmod(double x, double y);
extern void isJapanese();
extern void fn_8011FAFC();
extern void fn_80121E10();
extern unsigned int lbl_806D1178;
extern unsigned int lbl_806D1179;
extern unsigned int lbl_806D117A;
extern unsigned int lbl_806D117B;
extern unsigned int lbl_806D30A8;
extern unsigned int lbl_806D30AC;
extern unsigned int lbl_806D30B0;
extern unsigned int lbl_806D30B4;
extern unsigned int lbl_806D30B8;
extern unsigned int lbl_806D30BC;
extern unsigned int lbl_806D30C0;
extern unsigned int lbl_806D30C4;
extern unsigned int lbl_806D30C8;
extern unsigned int lbl_806D30CC;
extern unsigned int lbl_806D30D0;
extern unsigned int lbl_806D30D4;
extern unsigned int lbl_806D30D8;
extern unsigned int lbl_806D30DC;
extern unsigned int lbl_806D30E0;
extern unsigned int lbl_806D30E4;
extern unsigned int lbl_806D30E8;
extern unsigned int lbl_806D30EC;
extern unsigned int lbl_806D30F0;
extern unsigned int lbl_806D30F4;
extern unsigned int lbl_806D30F8;
extern unsigned int lbl_806D30FC;
extern unsigned int lbl_806D3100;
extern unsigned int lbl_806D3104;
extern unsigned int lbl_806D3108;
extern unsigned int lbl_806D310C;
extern unsigned int lbl_806D3110;
extern unsigned int lbl_806D3114;
extern unsigned int lbl_806D3118;
extern unsigned int lbl_806D311C;
extern unsigned int lbl_806D3120;
extern unsigned int lbl_806D3124;
extern unsigned int lbl_806D3128;
extern unsigned int lbl_806D3130;
extern unsigned int lbl_806D3138;
extern unsigned int lbl_806D3140;

asm void CreditMgr_DrawCoinCreditBanner(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; unsigned int f51; unsigned int f52; unsigned int f53; unsigned int f54; unsigned int f55; unsigned int f56; unsigned int f57; unsigned int f58; unsigned int f59; unsigned int f60; unsigned int f61; unsigned int f62; unsigned int f63; unsigned int f64; unsigned int f65; unsigned int f66; unsigned int f67; unsigned int f68; unsigned int f69; unsigned int f70; unsigned int f71; unsigned int f72; unsigned int f73; unsigned int f74; unsigned int f75; unsigned int f76; void *f77; unsigned int f78; void *f79; unsigned int f80; void *f81; unsigned int f82; void *f83; unsigned int f84; void *f85; unsigned int f86; void *f87; unsigned int f88; void *f89; unsigned int f90; void *f91; unsigned int f92; void *f93; unsigned int f94; void *f95; unsigned int f96; void *f97; unsigned int f98; void *f99; unsigned int f100; void *f101; unsigned int f102; void *f103; unsigned int f104; void *f105; unsigned int f106; void *f107; unsigned int f108; void *f109; unsigned int f110; void *f111; unsigned int f112; void *f113; unsigned int f114; void *f115; unsigned int f116; void *f117; unsigned int f118; void *f119; unsigned int f120; void *f121; unsigned int f122; void *f123; unsigned int f124; void *f125; unsigned int f126; void *f127; unsigned int f128; void *f129; unsigned int f130; void *f131; unsigned int f132; void *f133; unsigned int f134; void *f135; unsigned int f136; void *f137; unsigned int f138; void *f139; unsigned int f140; void *f141; unsigned int f142; void *f143; unsigned int f144; void *f145; unsigned int f146; void *f147; unsigned int f148; void *f149; } extab_CreditMgr_DrawCoinCreditBanner = { 0x280A0000, 0x0000015C, 0x00110130, 0x000001B0, 0x00110138, 0x00000208, 0x00110140, 0x00000324, 0x00110148, 0x00000378, 0x00110150, 0x000003D0, 0x00110158, 0x0000042C, 0x00100160, 0x0000047C, 0x00100168, 0x000004CC, 0x00110170, 0x00000524, 0x00110178, 0x00000578, 0x00110180, 0x000005D4, 0x00100188, 0x00000624, 0x00100190, 0x00000674, 0x00110198, 0x00000740, 0x001101A0, 0x00000794, 0x001101A8, 0x000007F4, 0x001001B0, 0x00000844, 0x001001B8, 0x00000894, 0x001101C0, 0x000008EC, 0x001101C8, 0x00000948, 0x001001D0, 0x00000998, 0x001001D8, 0x000009E8, 0x001101E0, 0x00000A54, 0x001101E8, 0x00000AA8, 0x001101F0, 0x00000B00, 0x001101F8, 0x00000C08, 0x00110200, 0x00000C5C, 0x00110208, 0x00000CB4, 0x00110210, 0x00000D10, 0x00100218, 0x00000D60, 0x00100220, 0x00000DB0, 0x00110228, 0x00000E08, 0x00110230, 0x00000E5C, 0x00110238, 0x00000EB8, 0x00100240, 0x00000F08, 0x00100248, 0x00000F58, 0x00110250, 0x00000000, 0x82000D88, (void *)&dtor_80082960, 0x82000D30, (void *)&dtor_80082960, 0x82000CD8, (void *)&dtor_80082960, 0x82000C80, (void *)&dtor_80082960, 0x82000C28, (void *)&dtor_80082960, 0x82000BD0, (void *)&dtor_80082960, 0x82000B78, (void *)&dtor_80082960, 0x82000B20, (void *)&dtor_80082960, 0x82000AC8, (void *)&dtor_80082960, 0x82000A70, (void *)&dtor_80082960, 0x82000A18, (void *)&dtor_80082960, 0x820009C0, (void *)&dtor_80082960, 0x82000968, (void *)&dtor_80082960, 0x82000910, (void *)&dtor_80082960, 0x820008B8, (void *)&dtor_80082960, 0x82000860, (void *)&dtor_80082960, 0x82000808, (void *)&dtor_80082960, 0x820007B0, (void *)&dtor_80082960, 0x82000758, (void *)&dtor_80082960, 0x82000700, (void *)&dtor_80082960, 0x820006A8, (void *)&dtor_80082960, 0x82000650, (void *)&dtor_80082960, 0x820005F8, (void *)&dtor_80082960, 0x820005A0, (void *)&dtor_80082960, 0x82000548, (void *)&dtor_80082960, 0x820004F0, (void *)&dtor_80082960, 0x82000498, (void *)&dtor_80082960, 0x82000440, (void *)&dtor_80082960, 0x820003E8, (void *)&dtor_80082960, 0x82000390, (void *)&dtor_80082960, 0x82000338, (void *)&dtor_80082960, 0x820002E0, (void *)&dtor_80082960, 0x82000288, (void *)&dtor_80082960, 0x82000230, (void *)&dtor_80082960, 0x820001D8, (void *)&dtor_80082960, 0x82000180, (void *)&dtor_80082960, 0x82000128, (void *)&dtor_80082960 };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CreditMgr_DrawCoinCreditBanner = {
    (void *)&CreditMgr_DrawCoinCreditBanner, 0x00000FB0, (void *)&extab_CreditMgr_DrawCoinCreditBanner
};

asm void CreditMgr_DrawCoinCreditBanner(void) { /* 0x80081184 size:0xFB0 */
    nofralloc
    stwu r1, -0xe00(r1)
    mflr r0
    stw r0, 0xe04(r1)
    stmw r27, 0xdec(r1)
    mr r30, r3
    mr r28, r4
    mr r29, r5
    lbz r0, lbl_806D1179(r13)
    extsb. r0, r0
    bne CreditMgr_DrawCoinCreditBanner_L_800811BC
    li r3, 0x0
    li r0, 0x1
    stb r3, lbl_806D1178(r13)
    stb r0, lbl_806D1179(r13)
    CreditMgr_DrawCoinCreditBanner_L_800811BC:
    lbz r0, lbl_806D117B(r13)
    extsb. r0, r0
    bne CreditMgr_DrawCoinCreditBanner_L_800811D4
    li r0, 0x1
    stb r0, lbl_806D117A(r13)
    stb r0, lbl_806D117B(r13)
    CreditMgr_DrawCoinCreditBanner_L_800811D4:
    li r31, 0x0
    li r27, 0x2
    li r3, 0x0
    bl fn_80288CC8
    cmplwi r3, 0x0
    beq CreditMgr_DrawCoinCreditBanner_L_8008122C
    cmpwi r30, 0x1
    li r4, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_800811FC
    li r4, 0x1
    CreditMgr_DrawCoinCreditBanner_L_800811FC:
    li r3, 0x0
    bl fn_80289040
    cmplwi r3, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_80081210
    li r27, 0x0
    CreditMgr_DrawCoinCreditBanner_L_80081210:
    cmplwi r3, 0x1
    bne CreditMgr_DrawCoinCreditBanner_L_8008121C
    li r27, 0x1
    CreditMgr_DrawCoinCreditBanner_L_8008121C:
    cmplwi r3, 0x2
    bne CreditMgr_DrawCoinCreditBanner_L_80081230
    li r27, 0x2
    b CreditMgr_DrawCoinCreditBanner_L_80081230
    CreditMgr_DrawCoinCreditBanner_L_8008122C:
    li r27, 0x3
    CreditMgr_DrawCoinCreditBanner_L_80081230:
    cmpwi r27, 0x2
    bge CreditMgr_DrawCoinCreditBanner_L_80081250
    mr r3, r30
    bl CreditMgr_GetCreditCount
    cmpwi r3, 0x0
    bgt CreditMgr_DrawCoinCreditBanner_L_80081254
    li r31, 0x1
    b CreditMgr_DrawCoinCreditBanner_L_80081254
    CreditMgr_DrawCoinCreditBanner_L_80081250:
    li r31, 0x1
    CreditMgr_DrawCoinCreditBanner_L_80081254:
    cmpwi r29, 0x1
    ble CreditMgr_DrawCoinCreditBanner_L_800812A4
    clrlwi r0, r28, 24
    cmplwi r0, 0x4
    bge CreditMgr_DrawCoinCreditBanner_L_80081298
    lbz r0, lbl_806D1178(r13)
    cmplwi r0, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_800812B0
    lbz r4, lbl_806D117A(r13)
    li r0, 0x1
    stb r0, lbl_806D1178(r13)
    subfic r3, r4, 0x1
    subi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    stb r0, lbl_806D117A(r13)
    b CreditMgr_DrawCoinCreditBanner_L_800812B0
    CreditMgr_DrawCoinCreditBanner_L_80081298:
    li r0, 0x0
    stb r0, lbl_806D1178(r13)
    b CreditMgr_DrawCoinCreditBanner_L_800812B0
    CreditMgr_DrawCoinCreditBanner_L_800812A4:
    li r0, 0x0
    stb r0, lbl_806D117A(r13)
    stb r0, lbl_806D1178(r13)
    CreditMgr_DrawCoinCreditBanner_L_800812B0:
    bl isJapanese
    cmpwi r3, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_80081BB4
    clrlwi. r0, r31, 24
    beq CreditMgr_DrawCoinCreditBanner_L_800813D4
    lbz r0, lbl_806D117A(r13)
    cmplwi r0, 0x0
    beq CreditMgr_DrawCoinCreditBanner_L_8008137C
    addi r3, r1, 0xd88
    bl ResCtrl_Init
    addi r3, r1, 0xd88
    bl fn_80121E10
    lfs f2, lbl_806D30AC(r2)
    addi r4, r29, 0x1b54
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0xd88
    stw r4, 0xd88(r1)
    li r4, 0x6
    stb r0, 0xd98(r1)
    stfs f2, 0xd9c(r1)
    stfs f1, 0xda0(r1)
    stfs f0, 0xda4(r1)
    stw r28, 0xdbc(r1)
    stw r28, 0xdc0(r1)
    stw r28, 0xdc4(r1)
    stw r28, 0xdc8(r1)
    bl fn_8011FAFC
    addi r3, r1, 0xd30
    bl ResCtrl_Init
    addi r3, r1, 0xd30
    bl fn_80121E10
    lfs f2, lbl_806D30B4(r2)
    li r4, 0x1b53
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0xd30
    stw r4, 0xd30(r1)
    li r4, 0x6
    stb r0, 0xd40(r1)
    stfs f2, 0xd44(r1)
    stfs f1, 0xd48(r1)
    stfs f0, 0xd4c(r1)
    stw r28, 0xd64(r1)
    stw r28, 0xd68(r1)
    stw r28, 0xd6c(r1)
    stw r28, 0xd70(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_8008137C:
    addi r3, r1, 0xcd8
    bl ResCtrl_Init
    addi r3, r1, 0xcd8
    bl fn_80121E10
    lfs f2, lbl_806D30B8(r2)
    li r4, 0x1b4e
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0xcd8
    stw r4, 0xcd8(r1)
    li r4, 0x6
    stb r0, 0xce8(r1)
    stfs f2, 0xcec(r1)
    stfs f1, 0xcf0(r1)
    stfs f0, 0xcf4(r1)
    stw r28, 0xd0c(r1)
    stw r28, 0xd10(r1)
    stw r28, 0xd14(r1)
    stw r28, 0xd18(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_800813D4:
    mr r3, r30
    bl CreditMgr_GetCreditCount
    lis r5, 0x6666
    lis r4, lbl_80598A60@ha
    addi r0, r5, 0x6667
    mulhw r6, r0, r3
    addi r4, r4, lbl_80598A60@l
    lbz r0, 0x27(r4)
    cmplwi r0, 0x0
    srawi r5, r6, 2
    srawi r0, r6, 2
    srwi r4, r0, 31
    srwi r6, r5, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    add r4, r5, r6
    addi r31, r4, 0x1b54
    subf r3, r0, r3
    addi r30, r3, 0x1b54
    bne CreditMgr_DrawCoinCreditBanner_L_80081840
    li r3, 0x0
    bl fn_80288CC8
    mr r27, r3
    addi r3, r1, 0xe8
    bl fn_80289B04
    cmplwi r27, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_80081448
    li r0, 0x63
    b CreditMgr_DrawCoinCreditBanner_L_80081484
    CreditMgr_DrawCoinCreditBanner_L_80081448:
    addi r3, r1, 0x48
    bl fn_80289B7C
    lbz r0, 0x50(r1)
    cmplwi r0, 0x1
    ble CreditMgr_DrawCoinCreditBanner_L_80081464
    lwz r0, 0xe8(r1)
    b CreditMgr_DrawCoinCreditBanner_L_80081478
    CreditMgr_DrawCoinCreditBanner_L_80081464:
    lwz r3, 0xe8(r1)
    lwz r0, 0xf0(r1)
    lwz r4, 0xec(r1)
    mullw r0, r3, r0
    add r0, r4, r0
    CreditMgr_DrawCoinCreditBanner_L_80081478:
    cmpwi r0, 0x63
    ble CreditMgr_DrawCoinCreditBanner_L_80081484
    li r0, 0x63
    CreditMgr_DrawCoinCreditBanner_L_80081484:
    cmpwi r0, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_80081698
    lbz r0, lbl_806D117A(r13)
    cmplwi r0, 0x0
    beq CreditMgr_DrawCoinCreditBanner_L_80081544
    addi r3, r1, 0xc80
    bl ResCtrl_Init
    addi r3, r1, 0xc80
    bl fn_80121E10
    lfs f2, lbl_806D30AC(r2)
    addi r4, r29, 0x1b54
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0xc80
    stw r4, 0xc80(r1)
    li r4, 0x6
    stb r0, 0xc90(r1)
    stfs f2, 0xc94(r1)
    stfs f1, 0xc98(r1)
    stfs f0, 0xc9c(r1)
    stw r28, 0xcb4(r1)
    stw r28, 0xcb8(r1)
    stw r28, 0xcbc(r1)
    stw r28, 0xcc0(r1)
    bl fn_8011FAFC
    addi r3, r1, 0xc28
    bl ResCtrl_Init
    addi r3, r1, 0xc28
    bl fn_80121E10
    lfs f2, lbl_806D30B4(r2)
    li r4, 0x1b53
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0xc28
    stw r4, 0xc28(r1)
    li r4, 0x6
    stb r0, 0xc38(r1)
    stfs f2, 0xc3c(r1)
    stfs f1, 0xc40(r1)
    stfs f0, 0xc44(r1)
    stw r28, 0xc5c(r1)
    stw r28, 0xc60(r1)
    stw r28, 0xc64(r1)
    stw r28, 0xc68(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081544:
    addi r3, r1, 0xbd0
    bl ResCtrl_Init
    addi r3, r1, 0xbd0
    bl fn_80121E10
    lfs f2, lbl_806D30BC(r2)
    li r4, 0x1b4f
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0xbd0
    stw r4, 0xbd0(r1)
    li r4, 0x6
    stb r0, 0xbe0(r1)
    stfs f2, 0xbe4(r1)
    stfs f1, 0xbe8(r1)
    stfs f0, 0xbec(r1)
    stw r28, 0xc04(r1)
    stw r28, 0xc08(r1)
    stw r28, 0xc0c(r1)
    stw r28, 0xc10(r1)
    bl fn_8011FAFC
    cmpwi r31, 0x1b54
    beq CreditMgr_DrawCoinCreditBanner_L_800815F0
    addi r3, r1, 0xb78
    bl ResCtrl_Init
    addi r3, r1, 0xb78
    bl fn_80121E10
    lfs f2, lbl_806D30C0(r2)
    li r0, 0x1
    lfs f1, lbl_806D30B0(r2)
    addi r3, r1, 0xb78
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r31, 0xb78(r1)
    stb r0, 0xb88(r1)
    stfs f2, 0xb8c(r1)
    stfs f1, 0xb90(r1)
    stfs f0, 0xb94(r1)
    stw r28, 0xbac(r1)
    stw r28, 0xbb0(r1)
    stw r28, 0xbb4(r1)
    stw r28, 0xbb8(r1)
    bl fn_8011FAFC
    CreditMgr_DrawCoinCreditBanner_L_800815F0:
    addi r3, r1, 0xb20
    bl ResCtrl_Init
    addi r3, r1, 0xb20
    bl fn_80121E10
    lfs f2, lbl_806D30C4(r2)
    li r0, 0x1
    lfs f1, lbl_806D30B0(r2)
    addi r3, r1, 0xb20
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r30, 0xb20(r1)
    stb r0, 0xb30(r1)
    stfs f2, 0xb34(r1)
    stfs f1, 0xb38(r1)
    stfs f0, 0xb3c(r1)
    stw r28, 0xb54(r1)
    stw r28, 0xb58(r1)
    stw r28, 0xb5c(r1)
    stw r28, 0xb60(r1)
    bl fn_8011FAFC
    addi r3, r1, 0xac8
    bl ResCtrl_Init
    addi r3, r1, 0xac8
    bl fn_80121E10
    lfs f2, lbl_806D30C8(r2)
    li r4, 0x1b51
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0xac8
    stw r4, 0xac8(r1)
    li r4, 0x6
    stb r0, 0xad8(r1)
    stfs f2, 0xadc(r1)
    stfs f1, 0xae0(r1)
    stfs f0, 0xae4(r1)
    stw r28, 0xafc(r1)
    stw r28, 0xb00(r1)
    stw r28, 0xb04(r1)
    stw r28, 0xb08(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081698:
    addi r3, r1, 0xa70
    bl ResCtrl_Init
    addi r3, r1, 0xa70
    bl fn_80121E10
    lfs f2, lbl_806D30CC(r2)
    li r4, 0x1b4f
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0xa70
    stw r4, 0xa70(r1)
    li r4, 0x6
    stb r0, 0xa80(r1)
    stfs f2, 0xa84(r1)
    stfs f1, 0xa88(r1)
    stfs f0, 0xa8c(r1)
    stw r28, 0xaa4(r1)
    stw r28, 0xaa8(r1)
    stw r28, 0xaac(r1)
    stw r28, 0xab0(r1)
    bl fn_8011FAFC
    addi r3, r1, 0xa18
    bl ResCtrl_Init
    addi r3, r1, 0xa18
    bl fn_80121E10
    lfs f2, lbl_806D30D0(r2)
    li r4, 0x1b50
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0xa18
    stw r4, 0xa18(r1)
    li r4, 0x6
    stb r0, 0xa28(r1)
    stfs f2, 0xa2c(r1)
    stfs f1, 0xa30(r1)
    stfs f0, 0xa34(r1)
    stw r28, 0xa4c(r1)
    stw r28, 0xa50(r1)
    stw r28, 0xa54(r1)
    stw r28, 0xa58(r1)
    bl fn_8011FAFC
    cmpwi r31, 0x1b54
    beq CreditMgr_DrawCoinCreditBanner_L_80081798
    addi r3, r1, 0x9c0
    bl ResCtrl_Init
    addi r3, r1, 0x9c0
    bl fn_80121E10
    lfs f2, lbl_806D30D4(r2)
    li r0, 0x1
    lfs f1, lbl_806D30B0(r2)
    addi r3, r1, 0x9c0
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r31, 0x9c0(r1)
    stb r0, 0x9d0(r1)
    stfs f2, 0x9d4(r1)
    stfs f1, 0x9d8(r1)
    stfs f0, 0x9dc(r1)
    stw r28, 0x9f4(r1)
    stw r28, 0x9f8(r1)
    stw r28, 0x9fc(r1)
    stw r28, 0xa00(r1)
    bl fn_8011FAFC
    CreditMgr_DrawCoinCreditBanner_L_80081798:
    addi r3, r1, 0x968
    bl ResCtrl_Init
    addi r3, r1, 0x968
    bl fn_80121E10
    lfs f2, lbl_806D30D8(r2)
    li r0, 0x1
    lfs f1, lbl_806D30B0(r2)
    addi r3, r1, 0x968
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r30, 0x968(r1)
    stb r0, 0x978(r1)
    stfs f2, 0x97c(r1)
    stfs f1, 0x980(r1)
    stfs f0, 0x984(r1)
    stw r28, 0x99c(r1)
    stw r28, 0x9a0(r1)
    stw r28, 0x9a4(r1)
    stw r28, 0x9a8(r1)
    bl fn_8011FAFC
    addi r3, r1, 0x910
    bl ResCtrl_Init
    addi r3, r1, 0x910
    bl fn_80121E10
    lfs f2, lbl_806D30DC(r2)
    li r4, 0x1b51
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x910
    stw r4, 0x910(r1)
    li r4, 0x6
    stb r0, 0x920(r1)
    stfs f2, 0x924(r1)
    stfs f1, 0x928(r1)
    stfs f0, 0x92c(r1)
    stw r28, 0x944(r1)
    stw r28, 0x948(r1)
    stw r28, 0x94c(r1)
    stw r28, 0x950(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081840:
    li r3, 0x0
    bl fn_80288CC8
    mr r27, r3
    addi r3, r1, 0xa8
    bl fn_80289B04
    cmplwi r27, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_80081864
    li r0, 0x63
    b CreditMgr_DrawCoinCreditBanner_L_800818A0
    CreditMgr_DrawCoinCreditBanner_L_80081864:
    addi r3, r1, 0x28
    bl fn_80289B7C
    lbz r0, 0x30(r1)
    cmplwi r0, 0x1
    ble CreditMgr_DrawCoinCreditBanner_L_80081880
    lwz r0, 0xa8(r1)
    b CreditMgr_DrawCoinCreditBanner_L_80081894
    CreditMgr_DrawCoinCreditBanner_L_80081880:
    lwz r3, 0xa8(r1)
    lwz r0, 0xb0(r1)
    lwz r4, 0xac(r1)
    mullw r0, r3, r0
    add r0, r4, r0
    CreditMgr_DrawCoinCreditBanner_L_80081894:
    cmpwi r0, 0x63
    ble CreditMgr_DrawCoinCreditBanner_L_800818A0
    li r0, 0x63
    CreditMgr_DrawCoinCreditBanner_L_800818A0:
    cmpwi r0, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_80081A60
    lbz r0, lbl_806D117A(r13)
    cmplwi r0, 0x0
    beq CreditMgr_DrawCoinCreditBanner_L_80081960
    addi r3, r1, 0x8b8
    bl ResCtrl_Init
    addi r3, r1, 0x8b8
    bl fn_80121E10
    lfs f2, lbl_806D30AC(r2)
    addi r4, r29, 0x1b54
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x8b8
    stw r4, 0x8b8(r1)
    li r4, 0x6
    stb r0, 0x8c8(r1)
    stfs f2, 0x8cc(r1)
    stfs f1, 0x8d0(r1)
    stfs f0, 0x8d4(r1)
    stw r28, 0x8ec(r1)
    stw r28, 0x8f0(r1)
    stw r28, 0x8f4(r1)
    stw r28, 0x8f8(r1)
    bl fn_8011FAFC
    addi r3, r1, 0x860
    bl ResCtrl_Init
    addi r3, r1, 0x860
    bl fn_80121E10
    lfs f2, lbl_806D30B4(r2)
    li r4, 0x1b53
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x860
    stw r4, 0x860(r1)
    li r4, 0x6
    stb r0, 0x870(r1)
    stfs f2, 0x874(r1)
    stfs f1, 0x878(r1)
    stfs f0, 0x87c(r1)
    stw r28, 0x894(r1)
    stw r28, 0x898(r1)
    stw r28, 0x89c(r1)
    stw r28, 0x8a0(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081960:
    cmpwi r31, 0x1b54
    beq CreditMgr_DrawCoinCreditBanner_L_800819B8
    addi r3, r1, 0x808
    bl ResCtrl_Init
    addi r3, r1, 0x808
    bl fn_80121E10
    lfs f2, lbl_806D30E0(r2)
    li r0, 0x1
    lfs f1, lbl_806D30B0(r2)
    addi r3, r1, 0x808
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r31, 0x808(r1)
    stb r0, 0x818(r1)
    stfs f2, 0x81c(r1)
    stfs f1, 0x820(r1)
    stfs f0, 0x824(r1)
    stw r28, 0x83c(r1)
    stw r28, 0x840(r1)
    stw r28, 0x844(r1)
    stw r28, 0x848(r1)
    bl fn_8011FAFC
    CreditMgr_DrawCoinCreditBanner_L_800819B8:
    addi r3, r1, 0x7b0
    bl ResCtrl_Init
    addi r3, r1, 0x7b0
    bl fn_80121E10
    lfs f2, lbl_806D30E4(r2)
    li r0, 0x1
    lfs f1, lbl_806D30B0(r2)
    addi r3, r1, 0x7b0
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r30, 0x7b0(r1)
    stb r0, 0x7c0(r1)
    stfs f2, 0x7c4(r1)
    stfs f1, 0x7c8(r1)
    stfs f0, 0x7cc(r1)
    stw r28, 0x7e4(r1)
    stw r28, 0x7e8(r1)
    stw r28, 0x7ec(r1)
    stw r28, 0x7f0(r1)
    bl fn_8011FAFC
    addi r3, r1, 0x758
    bl ResCtrl_Init
    addi r3, r1, 0x758
    bl fn_80121E10
    lfs f2, lbl_806D30E8(r2)
    li r4, 0x1b52
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x758
    stw r4, 0x758(r1)
    li r4, 0x6
    stb r0, 0x768(r1)
    stfs f2, 0x76c(r1)
    stfs f1, 0x770(r1)
    stfs f0, 0x774(r1)
    stw r28, 0x78c(r1)
    stw r28, 0x790(r1)
    stw r28, 0x794(r1)
    stw r28, 0x798(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081A60:
    addi r3, r1, 0x700
    bl ResCtrl_Init
    addi r3, r1, 0x700
    bl fn_80121E10
    lfs f2, lbl_806D30EC(r2)
    li r4, 0x1b50
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x700
    stw r4, 0x700(r1)
    li r4, 0x6
    stb r0, 0x710(r1)
    stfs f2, 0x714(r1)
    stfs f1, 0x718(r1)
    stfs f0, 0x71c(r1)
    stw r28, 0x734(r1)
    stw r28, 0x738(r1)
    stw r28, 0x73c(r1)
    stw r28, 0x740(r1)
    bl fn_8011FAFC
    cmpwi r31, 0x1b54
    beq CreditMgr_DrawCoinCreditBanner_L_80081B0C
    addi r3, r1, 0x6a8
    bl ResCtrl_Init
    addi r3, r1, 0x6a8
    bl fn_80121E10
    lfs f2, lbl_806D30F0(r2)
    li r0, 0x1
    lfs f1, lbl_806D30B0(r2)
    addi r3, r1, 0x6a8
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r31, 0x6a8(r1)
    stb r0, 0x6b8(r1)
    stfs f2, 0x6bc(r1)
    stfs f1, 0x6c0(r1)
    stfs f0, 0x6c4(r1)
    stw r28, 0x6dc(r1)
    stw r28, 0x6e0(r1)
    stw r28, 0x6e4(r1)
    stw r28, 0x6e8(r1)
    bl fn_8011FAFC
    CreditMgr_DrawCoinCreditBanner_L_80081B0C:
    addi r3, r1, 0x650
    bl ResCtrl_Init
    addi r3, r1, 0x650
    bl fn_80121E10
    lfs f2, lbl_806D30F4(r2)
    li r0, 0x1
    lfs f1, lbl_806D30B0(r2)
    addi r3, r1, 0x650
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r30, 0x650(r1)
    stb r0, 0x660(r1)
    stfs f2, 0x664(r1)
    stfs f1, 0x668(r1)
    stfs f0, 0x66c(r1)
    stw r28, 0x684(r1)
    stw r28, 0x688(r1)
    stw r28, 0x68c(r1)
    stw r28, 0x690(r1)
    bl fn_8011FAFC
    addi r3, r1, 0x5f8
    bl ResCtrl_Init
    addi r3, r1, 0x5f8
    bl fn_80121E10
    lfs f2, lbl_806D30F8(r2)
    li r4, 0x1b52
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x5f8
    stw r4, 0x5f8(r1)
    li r4, 0x6
    stb r0, 0x608(r1)
    stfs f2, 0x60c(r1)
    stfs f1, 0x610(r1)
    stfs f0, 0x614(r1)
    stw r28, 0x62c(r1)
    stw r28, 0x630(r1)
    stw r28, 0x634(r1)
    stw r28, 0x638(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081BB4:
    clrlwi. r0, r31, 24
    beq CreditMgr_DrawCoinCreditBanner_L_80081CCC
    lbz r0, lbl_806D117A(r13)
    cmplwi r0, 0x0
    beq CreditMgr_DrawCoinCreditBanner_L_80081C74
    addi r3, r1, 0x5a0
    bl ResCtrl_Init
    addi r3, r1, 0x5a0
    bl fn_80121E10
    lfs f2, lbl_806D30FC(r2)
    addi r4, r29, 0x3ba
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x5a0
    stw r4, 0x5a0(r1)
    li r4, 0x6
    stb r0, 0x5b0(r1)
    stfs f2, 0x5b4(r1)
    stfs f1, 0x5b8(r1)
    stfs f0, 0x5bc(r1)
    stw r28, 0x5d4(r1)
    stw r28, 0x5d8(r1)
    stw r28, 0x5dc(r1)
    stw r28, 0x5e0(r1)
    bl fn_8011FAFC
    addi r3, r1, 0x548
    bl ResCtrl_Init
    addi r3, r1, 0x548
    bl fn_80121E10
    lfs f2, lbl_806D3100(r2)
    li r4, 0x3b9
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x548
    stw r4, 0x548(r1)
    li r4, 0x6
    stb r0, 0x558(r1)
    stfs f2, 0x55c(r1)
    stfs f1, 0x560(r1)
    stfs f0, 0x564(r1)
    stw r28, 0x57c(r1)
    stw r28, 0x580(r1)
    stw r28, 0x584(r1)
    stw r28, 0x588(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081C74:
    addi r3, r1, 0x4f0
    bl ResCtrl_Init
    addi r3, r1, 0x4f0
    bl fn_80121E10
    lfs f2, lbl_806D3104(r2)
    li r4, 0x3b5
    lfs f1, lbl_806D3108(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x4f0
    stw r4, 0x4f0(r1)
    li r4, 0x6
    stb r0, 0x500(r1)
    stfs f2, 0x504(r1)
    stfs f1, 0x508(r1)
    stfs f0, 0x50c(r1)
    stw r28, 0x524(r1)
    stw r28, 0x528(r1)
    stw r28, 0x52c(r1)
    stw r28, 0x530(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081CCC:
    mr r3, r30
    bl CreditMgr_GetCreditCount
    lis r4, 0x6666
    addi r0, r4, 0x6667
    mulhw r0, r0, r3
    srawi r5, r0, 2
    srawi r0, r0, 2
    srwi r4, r0, 31
    srwi r6, r5, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    add r4, r5, r6
    addi r30, r4, 0x3ba
    subf r4, r0, r3
    li r3, 0x0
    addi r31, r4, 0x3ba
    bl fn_80288CC8
    mr r27, r3
    addi r3, r1, 0x68
    bl fn_80289B04
    cmplwi r27, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_80081D2C
    li r0, 0x63
    b CreditMgr_DrawCoinCreditBanner_L_80081D68
    CreditMgr_DrawCoinCreditBanner_L_80081D2C:
    addi r3, r1, 0x8
    bl fn_80289B7C
    lbz r0, 0x10(r1)
    cmplwi r0, 0x1
    ble CreditMgr_DrawCoinCreditBanner_L_80081D48
    lwz r0, 0x68(r1)
    b CreditMgr_DrawCoinCreditBanner_L_80081D5C
    CreditMgr_DrawCoinCreditBanner_L_80081D48:
    lwz r3, 0x68(r1)
    lwz r0, 0x70(r1)
    lwz r4, 0x6c(r1)
    mullw r0, r3, r0
    add r0, r4, r0
    CreditMgr_DrawCoinCreditBanner_L_80081D5C:
    cmpwi r0, 0x63
    ble CreditMgr_DrawCoinCreditBanner_L_80081D68
    li r0, 0x63
    CreditMgr_DrawCoinCreditBanner_L_80081D68:
    cmpwi r0, 0x0
    bne CreditMgr_DrawCoinCreditBanner_L_80081F7C
    lbz r0, lbl_806D117A(r13)
    cmplwi r0, 0x0
    beq CreditMgr_DrawCoinCreditBanner_L_80081E28
    addi r3, r1, 0x498
    bl ResCtrl_Init
    addi r3, r1, 0x498
    bl fn_80121E10
    lfs f2, lbl_806D30FC(r2)
    addi r4, r29, 0x3ba
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x498
    stw r4, 0x498(r1)
    li r4, 0x6
    stb r0, 0x4a8(r1)
    stfs f2, 0x4ac(r1)
    stfs f1, 0x4b0(r1)
    stfs f0, 0x4b4(r1)
    stw r28, 0x4cc(r1)
    stw r28, 0x4d0(r1)
    stw r28, 0x4d4(r1)
    stw r28, 0x4d8(r1)
    bl fn_8011FAFC
    addi r3, r1, 0x440
    bl ResCtrl_Init
    addi r3, r1, 0x440
    bl fn_80121E10
    lfs f2, lbl_806D3100(r2)
    li r4, 0x3b9
    lfs f1, lbl_806D30B0(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x440
    stw r4, 0x440(r1)
    li r4, 0x6
    stb r0, 0x450(r1)
    stfs f2, 0x454(r1)
    stfs f1, 0x458(r1)
    stfs f0, 0x45c(r1)
    stw r28, 0x474(r1)
    stw r28, 0x478(r1)
    stw r28, 0x47c(r1)
    stw r28, 0x480(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081E28:
    addi r3, r1, 0x3e8
    bl ResCtrl_Init
    addi r3, r1, 0x3e8
    bl fn_80121E10
    lfs f2, lbl_806D310C(r2)
    li r4, 0x3b8
    lfs f1, lbl_806D3108(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x3e8
    stw r4, 0x3e8(r1)
    li r4, 0x6
    stb r0, 0x3f8(r1)
    stfs f2, 0x3fc(r1)
    stfs f1, 0x400(r1)
    stfs f0, 0x404(r1)
    stw r28, 0x41c(r1)
    stw r28, 0x420(r1)
    stw r28, 0x424(r1)
    stw r28, 0x428(r1)
    bl fn_8011FAFC
    cmpwi r30, 0x3ba
    beq CreditMgr_DrawCoinCreditBanner_L_80081ED4
    addi r3, r1, 0x390
    bl ResCtrl_Init
    addi r3, r1, 0x390
    bl fn_80121E10
    lfs f2, lbl_806D3110(r2)
    li r0, 0x1
    lfs f1, lbl_806D3108(r2)
    addi r3, r1, 0x390
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r30, 0x390(r1)
    stb r0, 0x3a0(r1)
    stfs f2, 0x3a4(r1)
    stfs f1, 0x3a8(r1)
    stfs f0, 0x3ac(r1)
    stw r28, 0x3c4(r1)
    stw r28, 0x3c8(r1)
    stw r28, 0x3cc(r1)
    stw r28, 0x3d0(r1)
    bl fn_8011FAFC
    CreditMgr_DrawCoinCreditBanner_L_80081ED4:
    addi r3, r1, 0x338
    bl ResCtrl_Init
    addi r3, r1, 0x338
    bl fn_80121E10
    lfs f2, lbl_806D3114(r2)
    li r0, 0x1
    lfs f1, lbl_806D3108(r2)
    addi r3, r1, 0x338
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r31, 0x338(r1)
    stb r0, 0x348(r1)
    stfs f2, 0x34c(r1)
    stfs f1, 0x350(r1)
    stfs f0, 0x354(r1)
    stw r28, 0x36c(r1)
    stw r28, 0x370(r1)
    stw r28, 0x374(r1)
    stw r28, 0x378(r1)
    bl fn_8011FAFC
    addi r3, r1, 0x2e0
    bl ResCtrl_Init
    addi r3, r1, 0x2e0
    bl fn_80121E10
    lfs f2, lbl_806D30DC(r2)
    li r4, 0x3b6
    lfs f1, lbl_806D3108(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x2e0
    stw r4, 0x2e0(r1)
    li r4, 0x6
    stb r0, 0x2f0(r1)
    stfs f2, 0x2f4(r1)
    stfs f1, 0x2f8(r1)
    stfs f0, 0x2fc(r1)
    stw r28, 0x314(r1)
    stw r28, 0x318(r1)
    stw r28, 0x31c(r1)
    stw r28, 0x320(r1)
    bl fn_8011FAFC
    b CreditMgr_DrawCoinCreditBanner_L_80082120
    CreditMgr_DrawCoinCreditBanner_L_80081F7C:
    addi r3, r1, 0x288
    bl ResCtrl_Init
    addi r3, r1, 0x288
    bl fn_80121E10
    lfs f2, lbl_806D3118(r2)
    li r4, 0x3b8
    lfs f1, lbl_806D3108(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x288
    stw r4, 0x288(r1)
    li r4, 0x6
    stb r0, 0x298(r1)
    stfs f2, 0x29c(r1)
    stfs f1, 0x2a0(r1)
    stfs f0, 0x2a4(r1)
    stw r28, 0x2bc(r1)
    stw r28, 0x2c0(r1)
    stw r28, 0x2c4(r1)
    stw r28, 0x2c8(r1)
    bl fn_8011FAFC
    addi r3, r1, 0x230
    bl ResCtrl_Init
    addi r3, r1, 0x230
    bl fn_80121E10
    lfs f2, lbl_806D311C(r2)
    li r4, 0x3b7
    lfs f1, lbl_806D3108(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x230
    stw r4, 0x230(r1)
    li r4, 0x6
    stb r0, 0x240(r1)
    stfs f2, 0x244(r1)
    stfs f1, 0x248(r1)
    stfs f0, 0x24c(r1)
    stw r28, 0x264(r1)
    stw r28, 0x268(r1)
    stw r28, 0x26c(r1)
    stw r28, 0x270(r1)
    bl fn_8011FAFC
    cmpwi r30, 0x3ba
    beq CreditMgr_DrawCoinCreditBanner_L_8008207C
    addi r3, r1, 0x1d8
    bl ResCtrl_Init
    addi r3, r1, 0x1d8
    bl fn_80121E10
    lfs f2, lbl_806D3120(r2)
    li r0, 0x1
    lfs f1, lbl_806D3108(r2)
    addi r3, r1, 0x1d8
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r30, 0x1d8(r1)
    stb r0, 0x1e8(r1)
    stfs f2, 0x1ec(r1)
    stfs f1, 0x1f0(r1)
    stfs f0, 0x1f4(r1)
    stw r28, 0x20c(r1)
    stw r28, 0x210(r1)
    stw r28, 0x214(r1)
    stw r28, 0x218(r1)
    bl fn_8011FAFC
    CreditMgr_DrawCoinCreditBanner_L_8008207C:
    addi r3, r1, 0x180
    bl ResCtrl_Init
    addi r3, r1, 0x180
    bl fn_80121E10
    lfs f2, lbl_806D3124(r2)
    li r0, 0x1
    lfs f1, lbl_806D3108(r2)
    addi r3, r1, 0x180
    lfs f0, lbl_806D30A8(r2)
    li r4, 0x6
    stw r31, 0x180(r1)
    stb r0, 0x190(r1)
    stfs f2, 0x194(r1)
    stfs f1, 0x198(r1)
    stfs f0, 0x19c(r1)
    stw r28, 0x1b4(r1)
    stw r28, 0x1b8(r1)
    stw r28, 0x1bc(r1)
    stw r28, 0x1c0(r1)
    bl fn_8011FAFC
    addi r3, r1, 0x128
    bl ResCtrl_Init
    addi r3, r1, 0x128
    bl fn_80121E10
    lfs f2, lbl_806D3128(r2)
    li r4, 0x3b6
    lfs f1, lbl_806D3108(r2)
    li r0, 0x1
    lfs f0, lbl_806D30A8(r2)
    addi r3, r1, 0x128
    stw r4, 0x128(r1)
    li r4, 0x6
    stb r0, 0x138(r1)
    stfs f2, 0x13c(r1)
    stfs f1, 0x140(r1)
    stfs f0, 0x144(r1)
    stw r28, 0x15c(r1)
    stw r28, 0x160(r1)
    stw r28, 0x164(r1)
    stw r28, 0x168(r1)
    bl fn_8011FAFC
    CreditMgr_DrawCoinCreditBanner_L_80082120:
    lmw r27, 0xdec(r1)
    lwz r0, 0xe04(r1)
    mtlr r0
    addi r1, r1, 0xe00
    blr
}

#pragma exceptions on

int CreditMgr_TryConfirmPlay(int mode) {
    int kind;

    if (mode == 0) {
        kind = 0;
    } else if (mode == 1) {
        kind = 1;
    } else if (mode == 2) {
        kind = 2;
    } else if (mode == 3) {
        kind = 3;
    } else {
        kind = 4;
    }

    if (mode == 2 && lbl_80598A60.freeVs2P == 1) {
        PlayStats_IncVs2PJoin();
        PlayStats_IncVs2PlusJoin();
        return 1;
    }
    if (mode == 3 && lbl_80598A60.freeVs3P == 1) {
        PlayStats_IncVs2PlusJoin();
        PlayStats_IncVs3PlusJoin();
        return 1;
    }
    if (mode == 4 && lbl_80598A60.freeVs4P == 1) {
        PlayStats_IncVs4PJoin();
        PlayStats_IncVs3PlusJoin();
        return 1;
    }

    if (fn_80288F6C(0, kind) == 0) {
        return 0;
    }
    if (mode == 0) {
        PlayStats_IncSinglePlayJoin();
        PlayStats_BeginPlaySession();
    }
    if (mode == 1) {
        PlayStats_IncSinglePlayJoin();
    }
    if (mode == 2) {
        PlayStats_IncVs2PJoin();
        PlayStats_IncVs2PlusJoin();
    }
    if (mode == 3) {
        PlayStats_IncVs2PlusJoin();
        PlayStats_IncVs3PlusJoin();
    }
    if (mode == 4) {
        PlayStats_IncVs4PJoin();
        PlayStats_IncVs3PlusJoin();
    }
    return 1;
}

int CreditMgr_GetCoinCount(unsigned char noClamp) {
    CoinConfig cfg;
    CoinStatus st;
    unsigned int ok;
    int n;

    ok = fn_80288CC8(0);
    fn_80289B04(&st);
    if (ok == 0) {
        return 99;
    }
    fn_80289B7C(&cfg);
    if (cfg.mode > 1) {
        n = st.credits;
    } else {
        n = st.coins + st.credits * st.coinsPerCredit;
    }
    if (!noClamp && n > 99) {
        n = 99;
    }
    return n;
}

int CreditMgr_GetCoinsPerCredit(int slot) {
    CoinConfig cfg;
    CoinStatus st;
    unsigned int ok;
    int n;

    ok = fn_80288CC8(0);
    fn_80289B04(&st);
    if (ok == 0) {
        return -1;
    }
    if (slot == 2 && lbl_80598A60.freeVs2P == 1) {
        return 0;
    }
    if (slot == 3 && lbl_80598A60.freeVs3P == 1) {
        return 0;
    }
    if (slot == 4 && lbl_80598A60.freeVs4P == 1) {
        return 0;
    }
    fn_80289B7C(&cfg);
    if (slot == -1) {
        slot = lbl_806D1180;
    }
    lbl_806D1184 = slot;
    if (cfg.mode > 1) {
        n = cfg.perSlot[slot];
    } else {
        n = st.coinsPerCredit * cfg.perSlot[slot];
    }
    if (n > 99) {
        n = 99;
    }
    return n;
}

#pragma exceptions reset

#pragma exceptions on

int CreditMgr_GetCreditCount(int slot) {
    CoinConfig cfg;
    CoinStatus st;
    unsigned int ok;
    int n;
    int count;
    int r;

    ok = fn_80288CC8(0);
    fn_80289B04(&st);
    if (ok == 0) {
        return -1;
    }
    if (slot == 2 && lbl_80598A60.freeVs2P == 1) {
        return 0;
    }
    if (slot == 3 && lbl_80598A60.freeVs3P == 1) {
        return 0;
    }
    if (slot == 4 && lbl_80598A60.freeVs4P == 1) {
        return 0;
    }
    fn_80289B7C(&cfg);
    if (slot == -1) {
        slot = lbl_806D1180;
    }
    lbl_806D1184 = slot;
    if ((unsigned int)st.credits >= cfg.perSlot[slot]) {
        return 0;
    }
    n = st.credits;
    count = 0;
    while (n < cfg.perSlot[slot]) {
        n += cfg.mode;
        count++;
    }
    if (st.coinsPerCredit == 1) {
        if (fmod(count, cfg.divisor) == 0.0) {
            r = count / cfg.divisor;
        } else {
            r = count / cfg.divisor + 1;
        }
    } else {
        r = st.coinsPerCredit * count - st.coins;
    }
    if (r > 99) {
        r = 99;
    }
    return r;
}

#pragma exceptions reset

int CreditMgr_SetActiveSlot(int slot) {
    if (slot == lbl_806D1180) {
        return 0;
    }
    lbl_806D1180 = slot;
    lbl_806D1184 = slot;
    return 1;
}

#pragma exceptions on

int CreditMgr_PollAcceptor(void) {
    return fn_80288CC8(0);
}

int CreditMgr_AcceptorIsAbsent(void) {
    return fn_80288CC8(0) == 0;
}

int CreditMgr_GetPlayState(int alt) {
    int state = 2;
    unsigned int s;

    if (fn_80288CC8(0) != 0) {
        int k = 0;
        if (alt == 1) {
            k = 1;
        }
        s = fn_80289040(0, k);
        if (s == 0) {
            state = 0;
        }
        if (s == 1) {
            state = 1;
        }
        if (s == 2) {
            state = 2;
        }
    } else {
        state = 3;
    }
    return state;
}

void CreditMgr_PollInsertAndPlay(unsigned char silent) {
    CoinCounters cnt;
    CreditCfg *cfg;
    int event = 0;
    unsigned char sound = 1;
    int coins;
    int per;

    if (lbl_806D117D == 1) {
        return;
    }
    if (fn_80288CC8(0) == 0) {
        sound = 0;
    }
    cfg = &lbl_80598A60;
    fn_80289A90(&cnt);
    while (cfg->coinsSeen != cnt.coins) {
        PlayStats_IncCoinInserted();
        event = 1;
        cfg->coinsSeen++;
    }
    while (cfg->creditsSeen != cnt.credits) {
        PlayStats_IncCreditAdded();
        event = 2;
        cfg->creditsSeen++;
    }
    if (silent) {
        return;
    }
    if (event == 1) {
        coins = CreditMgr_GetCoinCount(1);
        per = CreditMgr_GetCoinsPerCredit(lbl_806D1184);
        if (per == -1) {
            event = 2;
        } else if (coins % per == 0) {
            event = 2;
        }
    }
    if (sound && event > 0) {
        if (event == 1) {
            SoundMgr_Play(1);
        } else if (event == 2) {
            SoundMgr_Play(2);
        }
    }
    if (event != 0) {
        PlayStats_PublishCoinCreditShadow();
    }
}

int CreditMgr_ResetState(void) {
    lbl_806D117C = 0;
    lbl_806D117D = 0;
    lbl_806D1180 = 0;
    lbl_806D1184 = 0;
    CreditMgr_PollInsertAndPlay(1);
    return 1;
}

void *dtor_80082960(void *p, short flags) {
    if (p != 0 && flags > 0) {
        MemoryManager_TimedFree(p);
    }
    return p;
}

#pragma exceptions reset
