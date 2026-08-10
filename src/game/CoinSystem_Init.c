/* === extracted from auto_CoinSystem_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void Archive_GetRootJObj();
extern void FUN_8003b120();
extern void GetCoinSpawnTable();
extern void IsCardValid();
extern void IsSpawnTableTerminator();
extern void MemoryManager_Free();
extern void Object_DtorWithGXSync();
extern void RankLog_UpdateTechnicalFlag();
extern void Terrain_GetGroundHeight();
extern void clNormal3D_Construct();
extern void clNormal3D_SetFlags();
extern void fn_8024F588();
extern void fn_802D07D4();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10A0;
extern unsigned int lbl_806D1528;
extern unsigned int lbl_806D152C;
extern unsigned int lbl_806D1530;
extern unsigned int lbl_806D1534;
extern unsigned int lbl_806D1538;
extern unsigned int lbl_806D153C;
extern unsigned int lbl_806D1540;
extern unsigned int lbl_806D1544;
extern unsigned int lbl_806D1548;
extern unsigned int lbl_806D73E8;
extern unsigned int lbl_806D7440;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8035C240[];
extern unsigned int lbl_80677CC8[];

/* --- function index (1 fns, .text 0x8013A778..0x8013AB74) ---
 * [  0] 0x8013A778 size:0x3FC   global CoinSystem_Init
 */

/* --- forward decls --- */
asm void CoinSystem_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; unsigned int f12; void *f13; } extab_CoinSystem_Init = { 0x288A0000, 0x000000F4, 0x00000020, 0x00000114, 0x00000028, 0x00000134, 0x00000030, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CoinSystem_Init = {
    (void *)&CoinSystem_Init, 0x000003FC, (void *)&extab_CoinSystem_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CoinSystem_Init(void) { /* 0x8013A778 size:0x3FC */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stfd f30, 0x30(r1)
    psq_st f30, 0x38(r1), 0, 0
    stmw r27, 0x1c(r1)
    lwz r0, lbl_806D1538(r13)
    lis r5, lbl_8035C240@ha
    mr r30, r3
    mr r28, r4
    cmpwi r0, 0x0
    addi r27, r5, lbl_8035C240@l
    beq CoinSystem_Init_L_8013A818
    lwz r3, lbl_806D1528(r13)
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013A7C8
    li r4, 0x1
    bl Object_DtorWithGXSync
    CoinSystem_Init_L_8013A7C8:
    lwz r3, lbl_806D152C(r13)
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013A7DC
    li r4, 0x1
    bl Object_DtorWithGXSync
    CoinSystem_Init_L_8013A7DC:
    lwz r3, lbl_806D1530(r13)
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013A7F0
    li r4, 0x1
    bl Object_DtorWithGXSync
    CoinSystem_Init_L_8013A7F0:
    lwz r3, lbl_806D1534(r13)
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013A800
    bl MemoryManager_Free
    CoinSystem_Init_L_8013A800:
    li r0, 0x0
    stw r0, lbl_806D1528(r13)
    stw r0, lbl_806D152C(r13)
    stw r0, lbl_806D1530(r13)
    stw r0, lbl_806D1534(r13)
    stw r0, lbl_806D1538(r13)
    CoinSystem_Init_L_8013A818:
    cmpwi r28, 0x0
    beq CoinSystem_Init_L_8013AAE8
    bl IsCardValid
    clrlwi. r0, r3, 24
    bne CoinSystem_Init_L_8013A830
    li r28, 0x1
    CoinSystem_Init_L_8013A830:
    lis r3, lbl_80677CC8@ha
    li r0, 0x0
    addi r4, r3, lbl_80677CC8@l
    stb r0, lbl_806D1548(r13)
    li r3, 0x5c
    stw r0, 0x0(r4)
    stw r0, 0x4(r4)
    stw r0, 0x8(r4)
    stw r0, 0xc(r4)
    bl Alloc
    mr. r29, r3
    beq CoinSystem_Init_L_8013A86C
    addi r4, r27, 0x408
    li r5, 0x1
    bl clNormal3D_Construct
    CoinSystem_Init_L_8013A86C:
    stw r29, lbl_806D1528(r13)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq CoinSystem_Init_L_8013A88C
    addi r4, r27, 0x418
    li r5, 0x1
    bl clNormal3D_Construct
    CoinSystem_Init_L_8013A88C:
    stw r29, lbl_806D152C(r13)
    li r3, 0x5c
    bl Alloc
    mr. r29, r3
    beq CoinSystem_Init_L_8013A8AC
    addi r4, r27, 0x428
    li r5, 0x1
    bl clNormal3D_Construct
    CoinSystem_Init_L_8013A8AC:
    lwz r3, lbl_806D1528(r13)
    stw r29, lbl_806D1530(r13)
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013AAE8
    lwz r0, lbl_806D152C(r13)
    cmplwi r0, 0x0
    beq CoinSystem_Init_L_8013AAE8
    cmplwi r29, 0x0
    beq CoinSystem_Init_L_8013AAE8
    lis r4, 0x4000
    li r5, 0x0
    bl clNormal3D_SetFlags
    lwz r3, lbl_806D152C(r13)
    lis r4, 0x4000
    li r5, 0x0
    bl clNormal3D_SetFlags
    lwz r3, lbl_806D1530(r13)
    bl Archive_GetRootJObj
    li r4, 0x200
    bl fn_802D07D4
    cmplwi r30, 0x0
    bne CoinSystem_Init_L_8013A90C
    bl GetCoinSpawnTable
    mr r30, r3
    CoinSystem_Init_L_8013A90C:
    cmplwi r30, 0x0
    beq CoinSystem_Init_L_8013AAE8
    li r0, 0x0
    mr r27, r30
    stw r0, lbl_806D1538(r13)
    b CoinSystem_Init_L_8013A934
    CoinSystem_Init_L_8013A924:
    lwz r3, lbl_806D1538(r13)
    addi r27, r27, 0x10
    addi r0, r3, 0x1
    stw r0, lbl_806D1538(r13)
    CoinSystem_Init_L_8013A934:
    mr r3, r27
    bl IsSpawnTableTerminator
    clrlwi. r0, r3, 24
    beq CoinSystem_Init_L_8013A924
    lwz r4, lbl_806D1538(r13)
    cmpwi r4, 0x0
    beq CoinSystem_Init_L_8013AAE8
    lwz r3, lbl_806D10A0(r13)
    cmplwi r3, 0x0
    bne CoinSystem_Init_L_8013A960
    li r3, 0x0
    CoinSystem_Init_L_8013A960:
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013A96C
    bl RankLog_UpdateTechnicalFlag
    CoinSystem_Init_L_8013A96C:
    lwz r0, lbl_806D1538(r13)
    mulli r3, r0, 0xc0
    bl FUN_8003b120
    cmplwi r3, 0x0
    stw r3, lbl_806D1534(r13)
    beq CoinSystem_Init_L_8013AAE8
    li r29, 0x0
    lfs f30, lbl_806D73E8(r2)
    lfs f31, lbl_806D7440(r2)
    mr r31, r30
    mr r30, r29
    b CoinSystem_Init_L_8013AAA8
    CoinSystem_Init_L_8013A99C:
    lfs f0, 0x0(r31)
    addi r3, r30, 0x4
    lwz r4, lbl_806D1534(r13)
    addi r12, r30, 0x8
    addi r10, r30, 0xc
    addi r9, r30, 0x18
    stfsx f0, r4, r3
    li r11, 0x0
    addi r8, r30, 0x10
    addi r6, r30, 0x6c
    lfs f0, 0x4(r31)
    addi r5, r30, 0x14
    lwz r27, lbl_806D1534(r13)
    li r7, -0x1
    addi r4, r30, 0x1c
    addi r0, r30, 0x34
    stfsx f0, r27, r12
    lfs f0, 0x8(r31)
    lwz r12, lbl_806D1534(r13)
    stfsx f0, r12, r10
    lwz r10, lbl_806D1534(r13)
    stwx r28, r10, r30
    lwz r10, lbl_806D1534(r13)
    stwx r11, r10, r9
    lwz r9, lbl_806D1534(r13)
    stwx r11, r9, r8
    lwz r8, lbl_806D1534(r13)
    stwx r11, r8, r6
    lwz r6, lbl_806D1534(r13)
    stwx r7, r6, r5
    lwz r5, lbl_806D1534(r13)
    stfsx f30, r5, r4
    lwz r4, lbl_806D1534(r13)
    stfsx f30, r4, r0
    lwz r0, 0xc(r31)
    clrlwi. r0, r0, 31
    beq CoinSystem_Init_L_8013AA60
    lwz r0, lbl_806D1534(r13)
    addi r4, r1, 0x8
    li r5, 0x0
    li r6, 0x0
    add r3, r0, r3
    bl Terrain_GetGroundHeight
    clrlwi. r0, r3, 24
    beq CoinSystem_Init_L_8013AA60
    lfs f0, 0x8(r1)
    addi r0, r30, 0x8
    lwz r3, lbl_806D1534(r13)
    stfsx f0, r3, r0
    CoinSystem_Init_L_8013AA60:
    lwz r3, lbl_806D1534(r13)
    addi r0, r30, 0x70
    addi r5, r30, 0x80
    addi r4, r30, 0x90
    stfsx f31, r3, r0
    addi r3, r30, 0xa0
    addi r0, r30, 0xb0
    addi r31, r31, 0x10
    lwz r6, lbl_806D1534(r13)
    addi r30, r30, 0xc0
    addi r29, r29, 0x1
    stfsx f31, r6, r5
    lwz r5, lbl_806D1534(r13)
    stfsx f31, r5, r4
    lwz r4, lbl_806D1534(r13)
    stfsx f31, r4, r3
    lwz r3, lbl_806D1534(r13)
    stfsx f31, r3, r0
    CoinSystem_Init_L_8013AAA8:
    lwz r0, lbl_806D1538(r13)
    cmpw r29, r0
    blt CoinSystem_Init_L_8013A99C
    li r0, 0x0
    stw r0, lbl_806D153C(r13)
    stw r0, lbl_806D1540(r13)
    stw r0, lbl_806D1544(r13)
    bl fn_8024F588
    li r0, 0x0
    stw r0, 0x1c(r3)
    stw r0, 0x18(r3)
    lwz r27, lbl_806D1538(r13)
    bl fn_8024F588
    stw r27, 0x1c(r3)
    li r3, 0x1
    b CoinSystem_Init_L_8013AB50
    CoinSystem_Init_L_8013AAE8:
    lwz r3, lbl_806D1528(r13)
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013AAFC
    li r4, 0x1
    bl Object_DtorWithGXSync
    CoinSystem_Init_L_8013AAFC:
    lwz r3, lbl_806D152C(r13)
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013AB10
    li r4, 0x1
    bl Object_DtorWithGXSync
    CoinSystem_Init_L_8013AB10:
    lwz r3, lbl_806D1530(r13)
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013AB24
    li r4, 0x1
    bl Object_DtorWithGXSync
    CoinSystem_Init_L_8013AB24:
    lwz r3, lbl_806D1534(r13)
    cmplwi r3, 0x0
    beq CoinSystem_Init_L_8013AB34
    bl MemoryManager_Free
    CoinSystem_Init_L_8013AB34:
    li r0, 0x0
    li r3, 0x0
    stw r0, lbl_806D1528(r13)
    stw r0, lbl_806D152C(r13)
    stw r0, lbl_806D1530(r13)
    stw r0, lbl_806D1534(r13)
    stw r0, lbl_806D1538(r13)
    CoinSystem_Init_L_8013AB50:
    psq_l f31, 0x48(r1), 0, 0
    lfd f31, 0x40(r1)
    psq_l f30, 0x38(r1), 0, 0
    lfd f30, 0x30(r1)
    lmw r27, 0x1c(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}
