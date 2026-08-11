/* === extracted from auto_KartDriver_InitFull_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void Archive_GetRootJObj();
extern void GetCharacterDataEntry();
extern void GetKartModelNameEntry();
extern void GetRaceContextPtr();
extern void HeapStats_DumpForTag();
extern void ItemEffectBus_Init();
extern void ItemEffectState_DefaultInit();
extern void JObj_Hide();
extern void JObj_Show();
extern void KartDriver_GetJointByIdx();
extern void KartTireFX_Ctor();
extern void KartTireFX_SetVisibleAll4Wheels();
extern void ObjectTree_BlendOrCopy_Timed();
extern void Object_BindMatrixSource();
extern void Object_DriveAnimAndSkin();
extern void RaceContextSlot_AllocDriver();
extern void RaceSlot_SetDriverPtr();
extern void ResolveJointByName();
extern void SceneRender_CmdB_8aa20();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();
extern void fn_80173DB4();
extern void fn_801B5BF4();
extern void fn_80232070();
extern void fn_802457E0();
extern void fn_8024F81C();
extern void fn_80250D1C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_cupId;
extern unsigned int g_kartStartSlot;
extern unsigned int g_raceCamera;
extern unsigned int g_roundIndex;
extern unsigned int lbl_806CEDD8;
extern unsigned int lbl_806CEDDC;
extern unsigned int lbl_806CEDE0;
extern unsigned int lbl_806CEDE4;
extern unsigned int lbl_806CEDE8;
extern unsigned int lbl_806D2540;
extern unsigned int lbl_806D2570;
extern unsigned int lbl_806D2574;
extern unsigned int lbl_806D264C;
extern unsigned int lbl_806D2650;
extern unsigned int lbl_806D2654;
extern unsigned int lbl_806D2658;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int chara_mario_hand_fin_joint[];
extern unsigned int chara_mario_hand_goo_joint[];
extern unsigned int chara_mario_hand_pa_joint[];
extern unsigned int chara_mario_head_null_joint[];
extern unsigned int chara_mario_r_hand_null_joint[];
extern unsigned int lbl_802E9F80[];
extern unsigned int lbl_803F5928[];
extern unsigned int mario_cart_body_joint[];
extern unsigned int mario_cart_engine_joint[];
extern unsigned int mario_cart_ground_fl_joint[];
extern unsigned int mario_cart_ground_fr_joint[];
extern unsigned int mario_cart_ground_rl_joint[];
extern unsigned int mario_cart_ground_rr_joint[];
extern unsigned int mario_cart_info_null_joint[];
extern unsigned int mario_cart_muffler_l_joint[];
extern unsigned int mario_cart_muffler_r_joint[];
extern unsigned int mario_cart_position_joint[];
extern unsigned int mario_cart_teresa_null_joint[];
extern unsigned int mario_cart_tire_fl_joint[];
extern unsigned int mario_cart_tire_fr_joint[];
extern unsigned int mario_cart_tire_rl_joint[];
extern unsigned int mario_cart_tire_rr_joint[];

/* --- function index (1 fns, .text 0x80044D50..0x80045950) ---
 * [  0] 0x80044D50 size:0xC00   global KartDriver_InitFull
 */

/* --- forward decls --- */
asm void KartDriver_InitFull(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
#define static
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; unsigned int f23; unsigned int f24; unsigned int f25; unsigned int f26; unsigned int f27; unsigned int f28; unsigned int f29; unsigned int f30; unsigned int f31; unsigned int f32; unsigned int f33; unsigned int f34; unsigned int f35; unsigned int f36; unsigned int f37; unsigned int f38; unsigned int f39; unsigned int f40; unsigned int f41; unsigned int f42; unsigned int f43; unsigned int f44; unsigned int f45; unsigned int f46; unsigned int f47; unsigned int f48; unsigned int f49; unsigned int f50; void *f51; unsigned int f52; void *f53; unsigned int f54; void *f55; unsigned int f56; void *f57; unsigned int f58; void *f59; unsigned int f60; void *f61; unsigned int f62; void *f63; unsigned int f64; void *f65; unsigned int f66; void *f67; unsigned int f68; void *f69; unsigned int f70; void *f71; unsigned int f72; void *f73; unsigned int f74; void *f75; unsigned int f76; void *f77; unsigned int f78; void *f79; unsigned int f80; void *f81; unsigned int f82; void *f83; unsigned int f84; void *f85; unsigned int f86; void *f87; unsigned int f88; void *f89; unsigned int f90; void *f91; unsigned int f92; void *f93; unsigned int f94; void *f95; unsigned int f96; void *f97; } extab_KartDriver_InitFull = { 0x800A0000, 0x000000F8, 0x000000C8, 0x00000118, 0x000000D0, 0x00000138, 0x000000D8, 0x00000158, 0x000000E0, 0x00000174, 0x000000E8, 0x00000200, 0x000000F0, 0x00000220, 0x000000F8, 0x0000030C, 0x00000100, 0x00000344, 0x00000108, 0x00000370, 0x00000110, 0x0000039C, 0x00000118, 0x000003C8, 0x00000120, 0x00000400, 0x00000128, 0x00000750, 0x00000130, 0x000008B4, 0x00000138, 0x000009A0, 0x00000140, 0x000009C8, 0x00000148, 0x00000A0C, 0x00000150, 0x00000A98, 0x00000158, 0x00000AB0, 0x00000160, 0x00000B28, 0x00000168, 0x00000B58, 0x00000170, 0x00000BB4, 0x00000178, 0x00000BCC, 0x00000180, 0x00000000, 0x8A800019, (void *)&MemoryManager_TimedFree, 0x8A800019, (void *)&MemoryManager_TimedFree, 0x8A800019, (void *)&MemoryManager_TimedFree, 0x8A800019, (void *)&MemoryManager_TimedFree, 0x8A800019, (void *)&MemoryManager_TimedFree, 0x8A800018, (void *)&MemoryManager_TimedFree, 0x8A800018, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree, 0x8A800010, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#undef static
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_InitFull = {
    (void *)&KartDriver_InitFull, 0x00000C00, (void *)&extab_KartDriver_InitFull
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_InitFull(void) { /* 0x80044D50 size:0xC00 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    lis r11, lbl_803F5928@ha
    lis r10, lbl_802E9F80@ha
    stw r0, 0x54(r1)
    stmw r16, 0x10(r1)
    mr r31, r3
    mr r20, r7
    mr r21, r6
    mr r22, r4
    mr r27, r5
    mr r24, r8
    mr r29, r9
    mr r3, r20
    mr r6, r31
    addi r18, r11, lbl_803F5928@l
    addi r30, r10, lbl_802E9F80@l
    bl fn_801B5BF4
    lwz r0, g_cupId(r13)
    li r19, -0x1
    cmpwi r0, 0xe
    bne KartDriver_InitFull_L_80044DCC
    cmpwi r22, 0x6
    bne KartDriver_InitFull_L_80044DCC
    lwz r5, g_roundIndex(r13)
    li r0, 0x4
    srwi r3, r0, 31
    li r27, 0x0
    srawi r4, r5, 31
    subfc r0, r0, r5
    adde r19, r4, r3
    KartDriver_InitFull_L_80044DCC:
    addi r3, r2, -0x7C24  /* lbl_806D263C */
    li r4, 0x0
    bl HeapStats_DumpForTag
    cmpwi r19, 0x0
    mr r17, r3
    blt KartDriver_InitFull_L_80044E04
    mr r3, r27
    li r4, 0x1
    bl GetKartModelNameEntry
    mulli r0, r19, 0x2c
    addi r28, r18, 0x274
    mr r23, r3
    add r28, r28, r0
    b KartDriver_InitFull_L_80044E24
    KartDriver_InitFull_L_80044E04:
    mr r3, r27
    mr r4, r29
    bl GetKartModelNameEntry
    mr r0, r3
    mr r3, r27
    mr r23, r0
    bl GetCharacterDataEntry
    mr r28, r3
    KartDriver_InitFull_L_80044E24:
    stw r22, 0x1f4(r31)
    li r3, 0x5c
    stw r27, 0x1f8(r31)
    bl Alloc
    mr. r25, r3
    beq KartDriver_InitFull_L_80044E48
    lwz r4, 0x0(r23)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80044E48:
    stw r25, 0x0(r31)
    li r3, 0x5c
    bl Alloc
    mr. r25, r3
    beq KartDriver_InitFull_L_80044E68
    lwz r4, 0x4(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80044E68:
    stw r25, 0xc(r31)
    li r3, 0x5c
    bl Alloc
    mr. r25, r3
    beq KartDriver_InitFull_L_80044E88
    lwz r4, 0x8(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80044E88:
    stw r25, 0x10(r31)
    li r3, 0x5c
    bl Alloc
    mr. r25, r3
    beq KartDriver_InitFull_L_80044EA8
    lwz r4, 0xc(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80044EA8:
    stw r25, 0x14(r31)
    li r3, 0x30
    bl Alloc
    mr. r25, r3
    beq KartDriver_InitFull_L_80044EC4
    mr r4, r31
    bl fn_80173DB4
    KartDriver_InitFull_L_80044EC4:
    stw r25, 0x29c(r31)
    li r0, 0x0
    stw r24, 0x22c(r31)
    stw r20, 0x23c(r31)
    stw r20, 0x248(r31)
    stw r0, 0x24c(r31)
    lwz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq KartDriver_InitFull_L_80044F0C
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    beq KartDriver_InitFull_L_80044F0C
    lwz r0, 0x10(r31)
    cmplwi r0, 0x0
    beq KartDriver_InitFull_L_80044F0C
    lwz r0, 0x14(r31)
    cmplwi r0, 0x0
    bne KartDriver_InitFull_L_80044F14
    KartDriver_InitFull_L_80044F0C:
    li r3, 0x0
    b KartDriver_InitFull_L_8004593C
    KartDriver_InitFull_L_80044F14:
    cmpwi r29, 0x2
    beq KartDriver_InitFull_L_80044F24
    cmpwi r29, 0x3
    bne KartDriver_InitFull_L_80044F34
    KartDriver_InitFull_L_80044F24:
    li r0, 0x0
    stw r0, 0x4(r31)
    stw r0, 0x8(r31)
    b KartDriver_InitFull_L_80044F74
    KartDriver_InitFull_L_80044F34:
    li r3, 0x5c
    bl Alloc
    mr. r24, r3
    beq KartDriver_InitFull_L_80044F50
    lwz r4, 0x4(r23)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80044F50:
    stw r24, 0x4(r31)
    li r3, 0x5c
    bl Alloc
    mr. r24, r3
    beq KartDriver_InitFull_L_80044F70
    lwz r4, 0x8(r23)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80044F70:
    stw r24, 0x8(r31)
    KartDriver_InitFull_L_80044F74:
    lwz r3, 0x248(r31)
    mr r4, r31
    bl RaceSlot_SetDriverPtr
    lwz r3, 0x248(r31)
    lwz r0, g_kartStartSlot(r13)
    cmpw r3, r0
    bne KartDriver_InitFull_L_80044F9C
    li r0, 0x1
    stb r0, 0x2d0(r31)
    b KartDriver_InitFull_L_80044FA4
    KartDriver_InitFull_L_80044F9C:
    li r0, 0x0
    stb r0, 0x2d0(r31)
    KartDriver_InitFull_L_80044FA4:
    stw r21, 0x17c(r31)
    bl GetRaceContextPtr
    mr r4, r22
    mr r5, r27
    mr r6, r21
    mr r7, r31
    mr r8, r20
    bl RaceContextSlot_AllocDriver
    stw r3, 0x218(r31)
    mr r4, r21
    li r5, 0x0
    lwz r3, 0x0(r31)
    bl Object_BindMatrixSource
    lwz r3, 0xc(r31)
    mr r4, r21
    li r5, 0x0
    bl Object_BindMatrixSource
    lwz r3, 0xc(r31)
    li r4, 0x0
    lfs f1, lbl_806D2540(r2)
    lfs f2, lbl_806D2570(r2)
    bl Object_DriveAnimAndSkin
    slwi r0, r27, 4
    addi r21, r18, 0xe0
    add r21, r21, r0
    mr r25, r31
    addi r24, r21, 0x4
    li r20, 0x0
    addi r23, r21, 0x8
    addi r22, r21, 0xc
    li r26, 0x0
    KartDriver_InitFull_L_80045020:
    lwz r0, g_cupId(r13)
    cmpwi r0, 0xb
    beq KartDriver_InitFull_L_80045070
    lwz r3, 0x18(r28)
    lwzx r0, r3, r26
    cmplwi r0, 0x0
    beq KartDriver_InitFull_L_80045064
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_8004505C
    lwz r4, 0x18(r28)
    li r5, 0x0
    lwzx r4, r4, r26
    bl clNormal3D_Construct
    KartDriver_InitFull_L_8004505C:
    stw r16, 0x24(r25)
    b KartDriver_InitFull_L_80045160
    KartDriver_InitFull_L_80045064:
    li r0, 0x0
    stw r0, 0x24(r25)
    b KartDriver_InitFull_L_80045160
    KartDriver_InitFull_L_80045070:
    cmpwi r20, 0x0
    bne KartDriver_InitFull_L_8004509C
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_80045094
    lwz r4, 0x0(r21)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80045094:
    stw r16, 0x24(r25)
    b KartDriver_InitFull_L_80045160
    KartDriver_InitFull_L_8004509C:
    cmpwi r20, 0x5
    bne KartDriver_InitFull_L_800450C8
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_800450C0
    lwz r4, 0x0(r24)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_800450C0:
    stw r16, 0x24(r25)
    b KartDriver_InitFull_L_80045160
    KartDriver_InitFull_L_800450C8:
    cmpwi r20, 0xa
    bne KartDriver_InitFull_L_800450F4
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_800450EC
    lwz r4, 0x0(r23)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_800450EC:
    stw r16, 0x24(r25)
    b KartDriver_InitFull_L_80045160
    KartDriver_InitFull_L_800450F4:
    cmpwi r20, 0xf
    bne KartDriver_InitFull_L_80045120
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_80045118
    lwz r4, 0x0(r22)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80045118:
    stw r16, 0x24(r25)
    b KartDriver_InitFull_L_80045160
    KartDriver_InitFull_L_80045120:
    lwz r3, 0x18(r28)
    lwzx r0, r3, r26
    cmplwi r0, 0x0
    beq KartDriver_InitFull_L_80045158
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_80045150
    lwz r4, 0x18(r28)
    li r5, 0x0
    lwzx r4, r4, r26
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80045150:
    stw r16, 0x24(r25)
    b KartDriver_InitFull_L_80045160
    KartDriver_InitFull_L_80045158:
    li r0, 0x0
    stw r0, 0x24(r25)
    KartDriver_InitFull_L_80045160:
    addi r20, r20, 0x1
    addi r25, r25, 0x4
    cmpwi r20, 0x31
    addi r26, r26, 0x4
    blt KartDriver_InitFull_L_80045020
    lwz r3, 0x10(r31)
    lfs f1, lbl_806D2574(r2)
    lfs f2, lbl_806D2540(r2)
    lwz r4, 0x24(r31)
    bl Object_DriveAnimAndSkin
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r20, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0xc(r31)
    lfs f1, lbl_806D2540(r2)
    mr r5, r20
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    mr r4, r17
    addi r3, r2, -0x7C1C  /* lbl_806D2644 */
    bl HeapStats_DumpForTag
    lis r3, mario_cart_tire_fl_joint@ha
    slwi r17, r27, 2
    addi r4, r3, mario_cart_tire_fl_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0xe8(r31)
    lis r3, mario_cart_tire_fr_joint@ha
    addi r4, r3, mario_cart_tire_fr_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0xec(r31)
    lis r3, mario_cart_tire_rl_joint@ha
    addi r4, r3, mario_cart_tire_rl_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0xf0(r31)
    lis r3, mario_cart_tire_rr_joint@ha
    addi r4, r3, mario_cart_tire_rr_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0xf4(r31)
    lis r3, mario_cart_ground_fl_joint@ha
    addi r4, r3, mario_cart_ground_fl_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0xf8(r31)
    lis r3, mario_cart_ground_fr_joint@ha
    addi r4, r3, mario_cart_ground_fr_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0xfc(r31)
    lis r3, mario_cart_ground_rl_joint@ha
    addi r4, r3, mario_cart_ground_rl_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x100(r31)
    lis r3, mario_cart_ground_rr_joint@ha
    addi r4, r3, mario_cart_ground_rr_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x104(r31)
    lis r3, mario_cart_engine_joint@ha
    addi r4, r3, mario_cart_engine_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x10c(r31)
    lis r3, mario_cart_body_joint@ha
    addi r4, r3, mario_cart_body_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x110(r31)
    lis r3, mario_cart_muffler_l_joint@ha
    addi r4, r3, mario_cart_muffler_l_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x114(r31)
    lis r3, mario_cart_muffler_r_joint@ha
    addi r4, r3, mario_cart_muffler_r_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x118(r31)
    lis r3, mario_cart_teresa_null_joint@ha
    addi r4, r3, mario_cart_teresa_null_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    cmpwi r19, 0x0
    stw r3, 0x120(r31)
    blt KartDriver_InitFull_L_80045374
    lwz r3, 0xc(r31)
    lwz r4, lbl_806CEDD8(r13)
    bl ResolveJointByName
    stw r3, 0x124(r31)
    lwz r3, 0xc(r31)
    lwz r4, lbl_806CEDE8(r13)
    bl ResolveJointByName
    stw r3, 0x128(r31)
    lwz r3, 0xc(r31)
    lwz r4, lbl_806CEDDC(r13)
    bl ResolveJointByName
    stw r3, 0x11c(r31)
    li r0, 0x0
    stw r0, 0x138(r31)
    lwz r3, 0xc(r31)
    lwz r4, lbl_806CEDE0(r13)
    bl ResolveJointByName
    stw r3, 0x130(r31)
    lwz r3, 0xc(r31)
    lwz r4, lbl_806CEDE4(r13)
    bl ResolveJointByName
    stw r3, 0x134(r31)
    li r0, 0x0
    stw r0, 0x12c(r31)
    stw r0, 0x158(r31)
    stw r0, 0x15c(r31)
    stw r0, 0x160(r31)
    b KartDriver_InitFull_L_80045488
    KartDriver_InitFull_L_80045374:
    lis r4, mario_cart_info_null_joint@ha
    lwz r3, 0xc(r31)
    addi r4, r4, mario_cart_info_null_joint@l
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x124(r31)
    lis r3, chara_mario_head_null_joint@ha
    addi r4, r3, chara_mario_head_null_joint@l
    lwz r3, 0xc(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x128(r31)
    lis r3, chara_mario_r_hand_null_joint@ha
    addi r4, r3, chara_mario_r_hand_null_joint@l
    lwz r3, 0xc(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x11c(r31)
    lis r3, chara_mario_hand_fin_joint@ha
    addi r4, r3, chara_mario_hand_fin_joint@l
    lwz r3, 0xc(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x138(r31)
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0x4
    bne KartDriver_InitFull_L_800453F4
    lwz r3, 0xc(r31)
    addi r4, r30, 0xf60
    bl ResolveJointByName
    stw r3, 0x12c(r31)
    b KartDriver_InitFull_L_800453FC
    KartDriver_InitFull_L_800453F4:
    li r0, 0x0
    stw r0, 0x12c(r31)
    KartDriver_InitFull_L_800453FC:
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0xc
    bne KartDriver_InitFull_L_80045448
    li r0, 0x0
    addi r4, r30, 0xe64
    stw r0, 0x130(r31)
    stw r0, 0x134(r31)
    lwz r3, 0xc(r31)
    bl ResolveJointByName
    stw r3, 0x158(r31)
    addi r4, r30, 0xe84
    lwz r3, 0xc(r31)
    bl ResolveJointByName
    stw r3, 0x15c(r31)
    addi r4, r30, 0xea4
    lwz r3, 0xc(r31)
    bl ResolveJointByName
    stw r3, 0x160(r31)
    b KartDriver_InitFull_L_80045488
    KartDriver_InitFull_L_80045448:
    lis r4, chara_mario_hand_goo_joint@ha
    lwz r3, 0xc(r31)
    addi r4, r4, chara_mario_hand_goo_joint@l
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x130(r31)
    lis r3, chara_mario_hand_pa_joint@ha
    addi r4, r3, chara_mario_hand_pa_joint@l
    lwz r3, 0xc(r31)
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x134(r31)
    li r0, 0x0
    stw r0, 0x158(r31)
    stw r0, 0x15c(r31)
    stw r0, 0x160(r31)
    KartDriver_InitFull_L_80045488:
    li r3, 0x58
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_800454A0
    mr r4, r31
    bl ItemEffectBus_Init
    KartDriver_InitFull_L_800454A0:
    cmpwi r29, 0x2
    stw r16, 0x304(r31)
    beq KartDriver_InitFull_L_800454B4
    cmpwi r29, 0x3
    bne KartDriver_InitFull_L_800454D0
    KartDriver_InitFull_L_800454B4:
    lis r4, mario_cart_position_joint@ha
    lwz r3, 0x0(r31)
    addi r4, r4, mario_cart_position_joint@l
    lwzx r4, r4, r17
    bl ResolveJointByName
    stw r3, 0x154(r31)
    b KartDriver_InitFull_L_800454D8
    KartDriver_InitFull_L_800454D0:
    li r0, 0x0
    stw r0, 0x154(r31)
    KartDriver_InitFull_L_800454D8:
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0xb
    bne KartDriver_InitFull_L_80045514
    cmpwi r29, 0x2
    beq KartDriver_InitFull_L_800454F4
    cmpwi r29, 0x3
    bne KartDriver_InitFull_L_80045508
    KartDriver_InitFull_L_800454F4:
    lwz r3, 0x0(r31)
    addi r4, r30, 0xec4
    bl ResolveJointByName
    stw r3, 0x164(r31)
    b KartDriver_InitFull_L_8004551C
    KartDriver_InitFull_L_80045508:
    li r0, 0x0
    stw r0, 0x164(r31)
    b KartDriver_InitFull_L_8004551C
    KartDriver_InitFull_L_80045514:
    li r0, 0x0
    stw r0, 0x164(r31)
    KartDriver_InitFull_L_8004551C:
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0xa
    bne KartDriver_InitFull_L_8004556C
    cmpwi r29, 0x2
    beq KartDriver_InitFull_L_80045538
    cmpwi r29, 0x3
    bne KartDriver_InitFull_L_8004555C
    KartDriver_InitFull_L_80045538:
    lwz r3, 0x0(r31)
    addi r4, r30, 0xee4
    bl ResolveJointByName
    stw r3, 0x168(r31)
    addi r4, r30, 0xf04
    lwz r3, 0x0(r31)
    bl ResolveJointByName
    stw r3, 0x16c(r31)
    b KartDriver_InitFull_L_80045578
    KartDriver_InitFull_L_8004555C:
    li r0, 0x0
    stw r0, 0x16c(r31)
    stw r0, 0x168(r31)
    b KartDriver_InitFull_L_80045578
    KartDriver_InitFull_L_8004556C:
    li r0, 0x0
    stw r0, 0x16c(r31)
    stw r0, 0x168(r31)
    KartDriver_InitFull_L_80045578:
    lfs f0, lbl_806D2540(r2)
    stfs f0, 0x170(r31)
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0xc
    bne KartDriver_InitFull_L_800455BC
    cmpwi r29, 0x2
    beq KartDriver_InitFull_L_8004559C
    cmpwi r29, 0x3
    bne KartDriver_InitFull_L_800455B0
    KartDriver_InitFull_L_8004559C:
    lwz r3, 0x0(r31)
    addi r4, r30, 0xf1c
    bl ResolveJointByName
    stw r3, 0x108(r31)
    b KartDriver_InitFull_L_800455C4
    KartDriver_InitFull_L_800455B0:
    li r0, 0x0
    stw r0, 0x108(r31)
    b KartDriver_InitFull_L_800455C4
    KartDriver_InitFull_L_800455BC:
    li r0, 0x0
    stw r0, 0x108(r31)
    KartDriver_InitFull_L_800455C4:
    lfs f0, lbl_806D2540(r2)
    stfs f0, 0x318(r31)
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0x3
    bne KartDriver_InitFull_L_80045628
    lwz r3, 0xc(r31)
    addi r4, r30, 0xf34
    bl ResolveJointByName
    stw r3, 0x150(r31)
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_80045604
    addi r4, r30, 0xf50
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80045604:
    lfs f1, lbl_806D2540(r2)
    li r4, 0x0
    stw r16, 0x20(r31)
    fmr f3, f1
    lfs f2, lbl_806D2570(r2)
    lwz r3, 0x20(r31)
    lfs f4, lbl_806D2574(r2)
    bl clNormal3D_SetScale
    b KartDriver_InitFull_L_80045634
    KartDriver_InitFull_L_80045628:
    li r0, 0x0
    stw r0, 0x150(r31)
    stw r0, 0x20(r31)
    KartDriver_InitFull_L_80045634:
    lwz r4, 0x158(r31)
    cmplwi r4, 0x0
    beq KartDriver_InitFull_L_8004564C
    lwz r3, 0xc(r31)
    li r5, 0x10
    bl JObj_Hide
    KartDriver_InitFull_L_8004564C:
    lwz r4, 0x15c(r31)
    cmplwi r4, 0x0
    beq KartDriver_InitFull_L_80045664
    lwz r3, 0xc(r31)
    li r5, 0x10
    bl JObj_Show
    KartDriver_InitFull_L_80045664:
    lwz r4, 0x160(r31)
    cmplwi r4, 0x0
    beq KartDriver_InitFull_L_8004567C
    lwz r3, 0xc(r31)
    li r5, 0x10
    bl JObj_Hide
    KartDriver_InitFull_L_8004567C:
    mr r3, r31
    li r4, 0x8
    bl KartDriver_GetJointByIdx
    lfs f0, 0x1c(r3)
    mr r3, r31
    li r4, 0x9
    stfs f0, 0x324(r31)
    bl KartDriver_GetJointByIdx
    lfs f0, 0x1c(r3)
    lfs f1, lbl_806D2570(r2)
    stfs f0, 0x328(r31)
    lfs f0, lbl_806D2540(r2)
    stfs f1, 0x31c(r31)
    stfs f0, 0x320(r31)
    lwz r0, g_raceCamera(r13)
    cmplwi r0, 0x0
    beq KartDriver_InitFull_L_80045738
    cmpwi r29, 0x2
    beq KartDriver_InitFull_L_800456D0
    cmpwi r29, 0x3
    bne KartDriver_InitFull_L_800456F8
    KartDriver_InitFull_L_800456D0:
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_800456F0
    addi r4, r18, 0xac
    li r5, 0x0
    lwzx r4, r4, r17
    bl clNormal3D_Construct
    KartDriver_InitFull_L_800456F0:
    stw r16, 0x18(r31)
    b KartDriver_InitFull_L_8004571C
    KartDriver_InitFull_L_800456F8:
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_80045718
    addi r4, r18, 0x78
    li r5, 0x0
    lwzx r4, r4, r17
    bl clNormal3D_Construct
    KartDriver_InitFull_L_80045718:
    stw r16, 0x18(r31)
    KartDriver_InitFull_L_8004571C:
    lwz r17, g_raceCamera(r13)
    lwz r3, 0x18(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    mr r3, r17
    bl SceneRender_CmdB_8aa20
    b KartDriver_InitFull_L_80045740
    KartDriver_InitFull_L_80045738:
    li r0, 0x0
    stw r0, 0x18(r31)
    KartDriver_InitFull_L_80045740:
    li r3, 0x5c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_8004575C
    addi r4, r30, 0xd8c
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_InitFull_L_8004575C:
    stw r16, 0x1c(r31)
    lwz r0, 0x1c(r31)
    cmplwi r0, 0x0
    beq KartDriver_InitFull_L_800457C8
    li r0, 0x0
    addi r4, r30, 0xda0
    stb r0, 0x174(r31)
    stw r0, 0x178(r31)
    lwz r3, 0x1c(r31)
    bl ResolveJointByName
    stw r3, 0x13c(r31)
    addi r4, r30, 0xdc4
    lwz r3, 0x1c(r31)
    bl ResolveJointByName
    stw r3, 0x140(r31)
    addi r4, r30, 0xde0
    lwz r3, 0x1c(r31)
    bl ResolveJointByName
    stw r3, 0x144(r31)
    addi r4, r30, 0xe00
    lwz r3, 0x1c(r31)
    bl ResolveJointByName
    stw r3, 0x148(r31)
    addi r4, r30, 0xe20
    lwz r3, 0x1c(r31)
    bl ResolveJointByName
    stw r3, 0x14c(r31)
    KartDriver_InitFull_L_800457C8:
    lbz r0, 0x2d0(r31)
    cmplwi r0, 0x1
    bne KartDriver_InitFull_L_80045840
    li r3, 0x1c
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_800457E8
    bl fn_80232070
    KartDriver_InitFull_L_800457E8:
    stw r16, 0x35c(r31)
    li r3, 0x10
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_80045800
    bl fn_802457E0
    KartDriver_InitFull_L_80045800:
    stw r16, 0x360(r31)
    lwz r3, 0x35c(r31)
    cmplwi r3, 0x0
    beq KartDriver_InitFull_L_80045820
    lfs f1, lbl_806D264C(r2)
    lfs f0, lbl_806D2650(r2)
    stfs f1, 0x8(r3)
    stfs f0, 0xc(r3)
    KartDriver_InitFull_L_80045820:
    lwz r3, 0x360(r31)
    cmplwi r3, 0x0
    beq KartDriver_InitFull_L_8004584C
    lfs f1, lbl_806D2654(r2)
    lfs f0, lbl_806D2658(r2)
    stfs f1, 0x8(r3)
    stfs f0, 0xc(r3)
    b KartDriver_InitFull_L_8004584C
    KartDriver_InitFull_L_80045840:
    li r0, 0x0
    stw r0, 0x35c(r31)
    stw r0, 0x360(r31)
    KartDriver_InitFull_L_8004584C:
    li r3, 0xc4
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_80045878
    lwz r6, 0xe8(r31)
    mr r4, r27
    lwz r7, 0xec(r31)
    mr r5, r29
    lwz r8, 0xf0(r31)
    lwz r9, 0xf4(r31)
    bl KartTireFX_Ctor
    KartDriver_InitFull_L_80045878:
    stw r16, 0x30c(r31)
    lwz r3, 0x30c(r31)
    cmplwi r3, 0x0
    beq KartDriver_InitFull_L_80045890
    li r4, 0x0
    bl KartTireFX_SetVisibleAll4Wheels
    KartDriver_InitFull_L_80045890:
    li r3, 0x28
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_800458A8
    mr r4, r31
    bl ItemEffectState_DefaultInit
    KartDriver_InitFull_L_800458A8:
    stw r16, 0x32c(r31)
    li r3, 0x1c
    bl Alloc
    cmplwi r3, 0x0
    beq KartDriver_InitFull_L_800458E0
    stw r31, 0x0(r3)
    li r4, 0x0
    li r0, -0x1
    stw r4, 0x4(r3)
    stw r4, 0xc(r3)
    stw r4, 0x10(r3)
    stb r4, 0x14(r3)
    stb r4, 0x15(r3)
    stw r0, 0x18(r3)
    KartDriver_InitFull_L_800458E0:
    stw r3, 0x344(r31)
    lbz r0, 0x2d0(r31)
    cmplwi r0, 0x0
    beq KartDriver_InitFull_L_80045924
    li r3, 0xc
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_80045904
    bl fn_8024F81C
    KartDriver_InitFull_L_80045904:
    stw r16, 0x378(r31)
    li r3, 0x24
    bl Alloc
    mr. r16, r3
    beq KartDriver_InitFull_L_8004591C
    bl fn_80250D1C
    KartDriver_InitFull_L_8004591C:
    stw r16, 0x380(r31)
    b KartDriver_InitFull_L_80045930
    KartDriver_InitFull_L_80045924:
    li r0, 0x0
    stw r0, 0x378(r31)
    stw r0, 0x380(r31)
    KartDriver_InitFull_L_80045930:
    li r0, -0x1
    li r3, 0x1
    stw r0, 0x374(r31)
    KartDriver_InitFull_L_8004593C:
    lmw r16, 0x10(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

