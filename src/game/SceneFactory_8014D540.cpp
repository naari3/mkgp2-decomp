
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D7F50[8];
/*
 * 0x8014D540..0x8014DD5C: scene factory and its object.
 */
#pragma cplusplus on

struct ListNode {
    ListNode *prev;
    ListNode *next;
};
struct ListIter {
    ListNode *n;
};
struct List {
    int size;
    ListNode head;
};

/* TOP-END */

extern "C" {
void *Alloc(unsigned long size);
extern void CreditMgr_GetCreditCount();
extern void CreditMgr_SetActiveSlot();
extern void FUN_8003b120();
void Frame_PostDrawOverlay(void);
void Frame_UpdatePerFrameState(void);
extern void GetVBlankFlag();
extern void NamCam_End();
extern void NamCam_Init();
extern void SetLocalPcbRole();
extern void SetResourceLoadingFlag();
extern void SetSyncTarget();
extern void VBlankValue_Get();
extern void clRom_PurgeAll();
extern void fn_80121210();
extern void fn_8014E0C4();
extern void fn_8014FC40();
extern void fn_801500F4();
extern void fn_80151F08();
extern void fn_80163614();
extern void fn_801933D0();
extern void isJapanese();
extern unsigned int g_pInputState;
extern unsigned int lbl_806D117C;
extern unsigned int lbl_806D12B0;
extern unsigned int lbl_806D1580;
extern unsigned int lbl_806D8064;
extern unsigned int jumptable_8048FDB0[];
extern unsigned int lbl_803FE0C8[];
extern unsigned int lbl_8048FD98[];
extern unsigned int lbl_8048FF64[];
extern unsigned int lbl_8048FF80[];
void MemoryManager_TimedFree(void *p);
extern void dtor_8007D0D4();
extern void dtor_801577D4();
extern void CoinSystem_Init();
extern void CourseObjectManager_Init();
extern void DrawManager_GetOrCreate();
extern void ItemObjectManager_Init();
extern void KartDriver_InitFull();
extern void KartDriver_New_Empty();
extern void PSMTXIdentity();
extern void PreloadEffectResources();
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate();
extern void TireEffect_ResetSpin();
extern void TornadoEffect_Ctor();
extern void TornadoEffect_SetColorPairC8CC();
extern void __construct_array();
extern void clItemBoxResponder_Ctor();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();
extern void fn_8014DD5C();
extern void fn_8014E004();
extern void fn_8014E028();
extern void fn_80157B20();
extern void fn_80157C60();
extern void fn_80157D18();
extern void fn_80173DB4();
extern void fn_801F7D50();
extern unsigned int g_kartStartSlot;
extern unsigned int lbl_806D8068;
extern unsigned int fn_8014E04C[];
extern unsigned int fn_80157820[];
extern unsigned int lbl_80363D30[];
extern unsigned int lbl_8048F178[];
extern unsigned int lbl_8048FF20[];
extern unsigned int lbl_8048FF3C[];
extern void dtor_80060024();
extern void dtor_80157850();
extern void dtor_801578C8();
asm void fn_8014D540(void);
void *fn_8014D848(void);
asm void fn_8014D88C(void *p);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; void *f25; unsigned int f26; unsigned int f27; void *f28; unsigned int f29; void *f30; unsigned int f31; unsigned int f32; void *f33; unsigned int f34; void *f35; unsigned int f36; unsigned int f37; void *f38; unsigned int f39; void *f40; unsigned int f41; unsigned int f42; void *f43; unsigned int f44; void *f45; unsigned int f46; unsigned int f47; void *f48; } extab_fn_8014D540 = { 0x180A0000, 0x00000074, 0x003B0068, 0x00000174, 0x00000060, 0x00000184, 0x00000068, 0x00000198, 0x00000074, 0x000001A4, 0x00030068, 0x000001EC, 0x000E0090, 0x00000248, 0x00000088, 0x00000258, 0x00130090, 0x000002B0, 0x00030068, 0x000002C8, 0x000000B0, 0x000002D8, 0x00030068, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_8007D0D4, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_8007D0D4, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0680001F, 0x00000000, (void *)&dtor_801577D4, 0x0A80001F, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_8007D0D4, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001E, 0x00000000, (void *)&dtor_8007D0D4 };


__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; void *f41; unsigned int f42; unsigned int f43; void *f44; unsigned int f45; void *f46; unsigned int f47; unsigned int f48; void *f49; unsigned int f50; void *f51; unsigned int f52; unsigned int f53; void *f54; unsigned int f55; void *f56; unsigned int f57; unsigned int f58; void *f59; unsigned int f60; unsigned int f61; void *f62; unsigned int f63; unsigned int f64; void *f65; unsigned int f66; unsigned int f67; void *f68; unsigned int f69; void *f70; unsigned int f71; unsigned int f72; void *f73; unsigned int f74; void *f75; unsigned int f76; unsigned int f77; void *f78; unsigned int f79; void *f80; unsigned int f81; unsigned int f82; void *f83; } extab_fn_8014D88C = { 0x400A0000, 0x00000038, 0x001000A8, 0x0000008C, 0x000000A0, 0x000000A8, 0x000D00A8, 0x000000F0, 0x000000C8, 0x00000104, 0x000600BC, 0x00000128, 0x000000B4, 0x0000014C, 0x000200BC, 0x0000017C, 0x000000DC, 0x0000019C, 0x001200A8, 0x000001F8, 0x000000E8, 0x00000204, 0x000000A8, 0x00000210, 0x00000114, 0x00000218, 0x00000108, 0x00000238, 0x000000FC, 0x00000244, 0x005800A8, 0x000003C0, 0x00000128, 0x000003E0, 0x002300A8, 0x00000488, 0x0000013C, 0x000004A8, 0x000000A8, 0x00000000, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001B, 0x00000000, (void *)&dtor_801577D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x06800019, 0x00000000, (void *)&dtor_80060024, 0x0A800019, (void *)&MemoryManager_TimedFree, 0x8680001B, 0x00000000, (void *)&dtor_801577D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x010000BC, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001B, 0x00000000, (void *)&dtor_801577D4, 0x07800018, 0x0000000C, (void *)&dtor_80157850, 0x07800018, 0x00000000, (void *)&dtor_801578C8, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001B, 0x00000000, (void *)&dtor_801577D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001B, 0x00000000, (void *)&dtor_801577D4, 0x0A800018, (void *)&MemoryManager_TimedFree, 0x8680001B, 0x00000000, (void *)&dtor_801577D4 };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014D540 = {
    (void *)&fn_8014D540, 0x00000308, (void *)&extab_fn_8014D540
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014D88C = {
    (void *)&fn_8014D88C, 0x000004D0, (void *)&extab_fn_8014D88C
};

}





extern "C" asm void fn_8014D540(void) { /* 0x8014D540 size:0x308 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r6, lbl_803FE0C8@ha
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x24(r1)
    addi r0, r6, lbl_803FE0C8@l
    li r6, 0x0
    stw r31, 0x1c(r1)
    mr r31, r5
    stw r30, 0x18(r1)
    mr r30, r3
    lis r3, lbl_8048FD98@ha
    stw r29, 0x14(r1)
    addi r3, r3, lbl_8048FD98@l
    mr r29, r4
    stw r0, 0x0(r30)
    li r0, 0x1
    stb r6, 0x4(r30)
    stw r3, 0x0(r30)
    li r3, 0x0
    stw r30, lbl_806D1580(r13)
    stw r6, 0x14(r30)
    stw r6, 0x8(r30)
    stw r6, 0xc(r30)
    stw r6, 0x10(r30)
    stb r0, 0x18(r30)
    stfs f0, 0x28(r30)
    stw r6, 0x2c(r30)
    bl CreditMgr_GetCreditCount
    stw r3, 0x30(r30)
    li r0, 0x0
    stb r0, 0x34(r30)
    stw r0, 0x38(r30)
    stw r0, 0x1c(r30)
    stw r0, 0x20(r30)
    bl fn_80121210
    bl clRom_PurgeAll
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne fn_8014D540_L_8014D5E8
    li r0, 0x0
    b fn_8014D540_L_8014D5EC
    fn_8014D540_L_8014D5E8:
    mr r0, r3
    fn_8014D540_L_8014D5EC:
    cmplwi r0, 0x0
    beq fn_8014D540_L_8014D618
    cmplwi r3, 0x0
    beq fn_8014D540_L_8014D610
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    fn_8014D540_L_8014D610:
    li r0, 0x0
    stw r0, g_pInputState(r13)
    fn_8014D540_L_8014D618:
    li r3, 0x4
    bl SetSyncTarget
    li r3, 0x0
    bl SetLocalPcbRole
    li r0, 0x0
    li r3, 0x0
    stb r0, lbl_806D12B0(r13)
    bl SetResourceLoadingFlag
    li r3, 0x0
    bl CreditMgr_GetCreditCount
    cntlzw r0, r3
    li r3, 0x1
    rlwnm r0, r3, r0, 31, 31
    li r3, 0x0
    stb r0, lbl_806D117C(r13)
    bl CreditMgr_SetActiveSlot
    li r3, 0x1
    bl fn_801933D0
    cmplwi r29, 0x6
    bgt fn_8014D540_L_8014D828
    lis r3, jumptable_8048FDB0@ha
    slwi r0, r29, 2
    addi r3, r3, jumptable_8048FDB0@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    li r3, 0x1
    bl fn_8014E0C4
    stw r3, 0x8(r30)
    b fn_8014D540_L_8014D828
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x580
    bl Alloc
    mr. r29, r3
    beq fn_8014D540_L_8014D6B4
    mr r5, r31
    li r4, 0x1
    bl fn_80151F08
    fn_8014D540_L_8014D6B4:
    stw r29, 0x8(r30)
    b fn_8014D540_L_8014D828
    li r3, 0x1c
    bl Alloc
    mr. r29, r3
    beq fn_8014D540_L_8014D6D8
    mr r4, r31
    li r5, 0x2
    bl fn_801500F4
    fn_8014D540_L_8014D6D8:
    stw r29, 0x8(r30)
    b fn_8014D540_L_8014D828
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x20
    bl Alloc
    mr. r31, r3
    beq fn_8014D540_L_8014D7E4
    lis r4, lbl_8048FF80@ha
    lis r3, lbl_8048FF64@ha
    addi r0, r4, lbl_8048FF80@l
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x0(r31)
    addi r3, r3, lbl_8048FF64@l
    li r0, 0x0
    stw r3, 0x0(r31)
    stw r0, 0x4(r31)
    stfs f0, 0x8(r31)
    stfs f0, 0xc(r31)
    stfs f0, 0x14(r31)
    bl isJapanese
    stw r3, 0x18(r31)
    li r0, 0x0
    stb r0, 0x1c(r31)
    stw r0, 0x10(r31)
    bl VBlankValue_Get
    clrlwi. r0, r3, 24
    beq fn_8014D540_L_8014D750
    li r0, 0x1
    stb r0, 0x1c(r31)
    fn_8014D540_L_8014D750:
    lbz r0, 0x1c(r31)
    cmplwi r0, 0x0
    bne fn_8014D540_L_8014D7E4
    li r3, 0x8
    bl Alloc
    mr. r29, r3
    beq fn_8014D540_L_8014D78C
    li r0, 0x0
    lis r3, 0x5
    stb r0, 0x0(r29)
    subi r3, r3, 0x5000
    stb r0, 0x1(r29)
    stw r0, 0x4(r29)
    bl FUN_8003b120
    stw r3, 0x4(r29)
    fn_8014D540_L_8014D78C:
    stw r29, 0x10(r31)
    lwz r29, 0x10(r31)
    bl GetVBlankFlag
    clrlwi. r0, r3, 24
    beq fn_8014D540_L_8014D7E4
    lbz r0, 0x0(r29)
    cmplwi r0, 0x1
    bne fn_8014D540_L_8014D7D0
    bl GetVBlankFlag
    clrlwi. r0, r3, 24
    beq fn_8014D540_L_8014D7D0
    lbz r0, 0x0(r29)
    cmplwi r0, 0x0
    beq fn_8014D540_L_8014D7D0
    li r0, 0x0
    stb r0, 0x0(r29)
    bl NamCam_End
    fn_8014D540_L_8014D7D0:
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x0(r29)
    stb r0, 0x1(r29)
    bl NamCam_Init
    fn_8014D540_L_8014D7E4:
    stw r31, 0x8(r30)
    b fn_8014D540_L_8014D828
    bl Frame_PostDrawOverlay
    bl Frame_UpdatePerFrameState
    li r3, 0x2c
    bl Alloc
    mr. r29, r3
    beq fn_8014D540_L_8014D808
    bl fn_8014FC40
    fn_8014D540_L_8014D808:
    stw r29, 0x8(r30)
    b fn_8014D540_L_8014D828
    mr r3, r31
    bl fn_80163614
    stw r3, 0x8(r30)
    b fn_8014D540_L_8014D828
    bl fn_8014D848
    stw r3, 0x8(r30)
    fn_8014D540_L_8014D828:
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

struct Scene50 {
    inline Scene50() { fn_8014D88C(this); }
    char pad[0x50];
};

extern "C" void *fn_8014D848(void)
{
    Frame_PostDrawOverlay();
    Frame_UpdatePerFrameState();
    return new Scene50;
}

extern "C" asm void fn_8014D88C(void *p) { /* 0x8014D88C size:0x4D0 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    lis r5, lbl_8048FF80@ha
    lis r4, lbl_8048FF3C@ha
    stw r0, 0x54(r1)
    addi r0, r4, lbl_8048FF3C@l
    lis r6, lbl_80363D30@ha
    stmw r24, 0x30(r1)
    mr r27, r3
    addi r3, r5, lbl_8048FF80@l
    addi r31, r6, lbl_80363D30@l
    stw r3, 0x0(r27)
    stw r0, 0x0(r27)
    bl DrawManager_GetOrCreate
    li r3, 0x1
    li r0, 0x0
    stb r3, 0x24(r27)
    lfs f0, lbl_806D8064(r2)
    stw r0, 0x4(r27)
    stfs f0, 0x8(r27)
    stfs f0, 0xc(r27)
    bl isJapanese
    stw r3, 0x10(r27)
    li r0, 0x0
    lfs f0, lbl_806D8064(r2)
    li r3, 0x5c
    stw r0, 0x28(r27)
    stfs f0, 0x2c(r27)
    stfs f0, 0x30(r27)
    bl Alloc
    mr. r26, r3
    beq fn_8014D88C_L_8014D918
    addi r4, r31, 0x3810
    li r5, 0x0
    bl clNormal3D_Construct
    fn_8014D88C_L_8014D918:
    stw r26, 0x14(r27)
    li r0, 0x0
    addi r3, r31, 0x3010
    stw r0, 0x18(r27)
    stw r0, 0x1c(r27)
    stw r0, 0x20(r27)
    bl SoundDriver_GetOrCreate
    addi r3, r31, 0x3010
    li r4, 0x2
    bl CoinSystem_Init
    bl SoundChannels_ClearAll
    bl ItemObjectManager_Init
    bl CourseObjectManager_Init
    li r0, -0x1
    li r28, 0x0
    stw r0, g_kartStartSlot(r13)
    la r30, lbl_806D7F50(r2)  /* lbl_806D7F50 */
    li r29, 0x0
    fn_8014D88C_L_8014D960:
    li r3, 0x50
    bl Alloc
    mr. r25, r3
    beq fn_8014D88C_L_8014DA0C
    lwz r26, 0x0(r30)
    addi r4, r25, 0x44
    bl clItemBoxResponder_Ctor
    lis r4, lbl_8048FF20@ha
    addi r3, r25, 0x14
    addi r0, r4, lbl_8048FF20@l
    stw r0, 0x0(r25)
    bl PSMTXIdentity
    lfs f0, lbl_806D8064(r2)
    li r3, 0x384
    stfs f0, 0x44(r25)
    stfs f0, 0x48(r25)
    stfs f0, 0x4c(r25)
    bl Alloc
    mr. r24, r3
    beq fn_8014D88C_L_8014D9B4
    bl KartDriver_New_Empty
    fn_8014D88C_L_8014D9B4:
    stw r24, 0xc(r25)
    mr r5, r26
    mr r7, r28
    addi r6, r25, 0x14
    lwz r3, 0xc(r25)
    li r4, 0x0
    li r8, 0x0
    li r9, 0x0
    bl KartDriver_InitFull
    li r3, 0x154
    bl Alloc
    mr. r24, r3
    beq fn_8014D88C_L_8014DA08
    lfs f1, lbl_806D8064(r2)
    mr r6, r26
    lwz r5, 0xc(r25)
    li r4, 0x0
    fmr f2, f1
    li r7, 0x1
    fmr f3, f1
    bl TornadoEffect_Ctor
    fn_8014D88C_L_8014DA08:
    stw r24, 0x10(r25)
    fn_8014D88C_L_8014DA0C:
    addi r0, r29, 0x34
    li r4, 0x20
    stwx r25, r27, r0
    li r5, 0x20
    lwzx r3, r27, r0
    lwz r3, 0x10(r3)
    bl TornadoEffect_SetColorPairC8CC
    addi r0, r29, 0x34
    lfs f1, lbl_806D8064(r2)
    lwzx r3, r27, r0
    lfs f2, lbl_806D8068(r2)
    lwz r3, 0x10(r3)
    bl TireEffect_ResetSpin
    addi r0, r28, 0x44
    li r3, 0x0
    stbx r3, r27, r0
    addi r28, r28, 0x1
    addi r0, r29, 0x3c
    addi r29, r29, 0x4
    cmpwi r28, 0x2
    stwx r3, r27, r0
    addi r30, r30, 0x4
    blt fn_8014D88C_L_8014D960
    li r3, 0x30
    bl Alloc
    mr. r24, r3
    beq fn_8014D88C_L_8014DA84
    lwz r4, 0x34(r27)
    lwz r4, 0xc(r4)
    bl fn_80173DB4
    fn_8014D88C_L_8014DA84:
    stw r24, 0x48(r27)
    li r3, 0x30
    bl Alloc
    mr. r24, r3
    beq fn_8014D88C_L_8014DAC4
    bl fn_80157B20
    addi r3, r24, 0xc
    bl fn_80157D18
    lis r3, fn_80157820@ha
    lis r5, fn_8014E04C@ha
    addi r4, r3, fn_80157820@l
    li r6, 0xc
    addi r3, r24, 0x18
    addi r5, r5, fn_8014E04C@l
    li r7, 0x2
    bl __construct_array
    fn_8014D88C_L_8014DAC4:
    stw r24, 0x4c(r27)
    li r3, 0x1
    bl SetResourceLoadingFlag
    lwz r3, 0x4c(r27)
    li r4, 0xa
    bl fn_8014E028
    lwz r3, 0x4c(r27)
    li r4, 0xb
    bl fn_8014E028
    lwz r3, 0x4c(r27)
    li r4, 0xc
    bl fn_8014E028
    lwz r3, 0x4c(r27)
    li r4, 0xa
    bl fn_8014E004
    lwz r3, 0x4c(r27)
    li r4, 0xb
    bl fn_8014E004
    lwz r3, 0x4c(r27)
    li r4, 0xc
    bl fn_8014E004
    lwz r3, 0x4c(r27)
    li r4, 0xa
    bl fn_8014DD5C
    cmplwi r3, 0x0
    beq fn_8014D88C_L_8014DB44
    lfs f1, lbl_806D8064(r2)
    li r4, 0x0
    lfs f2, lbl_806D8068(r2)
    fmr f3, f1
    fmr f4, f1
    bl clNormal3D_SetScale
    fn_8014D88C_L_8014DB44:
    lwz r3, 0x4c(r27)
    li r4, 0xb
    bl fn_8014DD5C
    cmplwi r3, 0x0
    beq fn_8014D88C_L_8014DB70
    lfs f1, lbl_806D8064(r2)
    li r4, 0x0
    lfs f2, lbl_806D8068(r2)
    fmr f3, f1
    fmr f4, f1
    bl clNormal3D_SetScale
    fn_8014D88C_L_8014DB70:
    lwz r3, 0x4c(r27)
    li r4, 0xc
    bl fn_8014DD5C
    cmplwi r3, 0x0
    beq fn_8014D88C_L_8014DB9C
    lfs f1, lbl_806D8064(r2)
    li r4, 0x0
    lfs f2, lbl_806D8068(r2)
    fmr f3, f1
    fmr f4, f1
    bl clNormal3D_SetScale
    fn_8014D88C_L_8014DB9C:
    li r3, 0x2
    bl PreloadEffectResources
    li r3, 0x9
    bl PreloadEffectResources
    lwz r0, 0x10(r27)
    cmpwi r0, 0x1
    bne fn_8014D88C_L_8014DC80
    li r29, 0x3e
    li r28, 0x4d8
    fn_8014D88C_L_8014DBC0:
    cmplwi r29, 0x50
    lwz r26, 0x4c(r27)
    bge fn_8014D88C_L_8014DC6C
    addi r3, r31, 0x7a0
    lwzx r30, r3, r28
    cmplwi r30, 0xc
    bge fn_8014D88C_L_8014DC6C
    lwz r0, 0xc(r26)
    cmplwi r0, 0x0
    beq fn_8014D88C_L_8014DC1C
    lwz r4, 0x14(r26)
    addi r3, r26, 0x10
    b fn_8014D88C_L_8014DC14
    fn_8014D88C_L_8014DBF4:
    lwz r0, 0x8(r4)
    cmplw r0, r30
    bne fn_8014D88C_L_8014DC10
    lwz r3, 0xc(r4)
    addi r0, r3, 0x1
    stw r0, 0xc(r4)
    b fn_8014D88C_L_8014DC6C
    fn_8014D88C_L_8014DC10:
    lwz r4, 0x4(r4)
    fn_8014D88C_L_8014DC14:
    cmplw r4, r3
    bne fn_8014D88C_L_8014DBF4
    fn_8014D88C_L_8014DC1C:
    li r0, 0x1
    stw r30, 0x24(r1)
    li r3, 0x4
    stw r0, 0x28(r1)
    bl Alloc
    mr. r24, r3
    beq fn_8014D88C_L_8014DC4C
    lis r4, lbl_8048F178@ha
    slwi r0, r30, 2
    addi r4, r4, lbl_8048F178@l
    lwzx r4, r4, r0
    bl fn_801F7D50
    fn_8014D88C_L_8014DC4C:
    addi r0, r26, 0x10
    stw r24, 0x2c(r1)
    addi r3, r1, 0x10
    addi r4, r26, 0xc
    stw r0, 0x14(r1)
    addi r5, r1, 0x14
    addi r6, r1, 0x24
    bl fn_80157C60
    fn_8014D88C_L_8014DC6C:
    addi r29, r29, 0x1
    addi r28, r28, 0x14
    cmpwi r29, 0x4c
    ble fn_8014D88C_L_8014DBC0
    b fn_8014D88C_L_8014DD44
    fn_8014D88C_L_8014DC80:
    li r29, 0x14
    li r28, 0x190
    fn_8014D88C_L_8014DC88:
    cmplwi r29, 0x50
    lwz r26, 0x4c(r27)
    bge fn_8014D88C_L_8014DD34
    addi r3, r31, 0x7a0
    lwzx r30, r3, r28
    cmplwi r30, 0xc
    bge fn_8014D88C_L_8014DD34
    lwz r0, 0xc(r26)
    cmplwi r0, 0x0
    beq fn_8014D88C_L_8014DCE4
    lwz r4, 0x14(r26)
    addi r3, r26, 0x10
    b fn_8014D88C_L_8014DCDC
    fn_8014D88C_L_8014DCBC:
    lwz r0, 0x8(r4)
    cmplw r0, r30
    bne fn_8014D88C_L_8014DCD8
    lwz r3, 0xc(r4)
    addi r0, r3, 0x1
    stw r0, 0xc(r4)
    b fn_8014D88C_L_8014DD34
    fn_8014D88C_L_8014DCD8:
    lwz r4, 0x4(r4)
    fn_8014D88C_L_8014DCDC:
    cmplw r4, r3
    bne fn_8014D88C_L_8014DCBC
    fn_8014D88C_L_8014DCE4:
    li r0, 0x1
    stw r30, 0x18(r1)
    li r3, 0x4
    stw r0, 0x1c(r1)
    bl Alloc
    mr. r24, r3
    beq fn_8014D88C_L_8014DD14
    lis r4, lbl_8048F178@ha
    slwi r0, r30, 2
    addi r4, r4, lbl_8048F178@l
    lwzx r4, r4, r0
    bl fn_801F7D50
    fn_8014D88C_L_8014DD14:
    addi r0, r26, 0x10
    stw r24, 0x20(r1)
    addi r3, r1, 0x8
    addi r4, r26, 0xc
    stw r0, 0xc(r1)
    addi r5, r1, 0xc
    addi r6, r1, 0x18
    bl fn_80157C60
    fn_8014D88C_L_8014DD34:
    addi r29, r29, 0x1
    addi r28, r28, 0x14
    cmpwi r29, 0x22
    ble fn_8014D88C_L_8014DC88
    fn_8014D88C_L_8014DD44:
    mr r3, r27
    lmw r24, 0x30(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

