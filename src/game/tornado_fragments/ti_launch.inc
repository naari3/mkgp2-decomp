/* === extracted from auto_TornadoLaunch_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AngleStepTowards_Shortest();
extern void BuildOrientationFromYaw();
extern void GetSpawnPosition();
extern void ItemObject_DecrementCategoryBudget();
extern void ItemObject_GetGroundTypeAt();
extern void Item_AdvanceTetherToJoint13();
extern void Item_DecayVelocityScalar();
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetTransform();
extern void TornadoItem_TickActive();
extern void Vec3_Add_DestFirst();
extern void Vec3_ToPitch();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D61F0;
extern unsigned int lbl_806D61F4;
extern unsigned int lbl_806D61F8;
extern unsigned int lbl_806D61FC;
extern unsigned int lbl_806D6200;
extern unsigned int lbl_806D6204;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_804217D8[];

/* --- function index (1 fns, .text 0x800F869C..0x800F8FD8) ---
 * [  0] 0x800F869C size:0x93C   global TornadoLaunch_Tick
 */

/* --- forward decls --- */
asm void TornadoLaunch_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoLaunch_Tick[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoLaunch_Tick = {
    (void *)&TornadoLaunch_Tick, 0x0000093C, (void *)extab_TornadoLaunch_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoLaunch_Tick(void) { /* 0x800F869C size:0x93C */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stw r31, 0x9c(r1)
    stw r30, 0x98(r1)
    mr r30, r3
    addi r31, r30, 0xec
    lbz r0, 0xc8(r3)
    extsb r0, r0
    cmpwi r0, 0x2
    beq TornadoLaunch_Tick_L_800F8720
    bge TornadoLaunch_Tick_L_800F86DC
    cmpwi r0, 0x0
    beq TornadoLaunch_Tick_L_800F86E8
    bge TornadoLaunch_Tick_L_800F8710
    b TornadoLaunch_Tick_L_800F8F1C
    TornadoLaunch_Tick_L_800F86DC:
    cmpwi r0, 0x4
    bge TornadoLaunch_Tick_L_800F8F1C
    b TornadoLaunch_Tick_L_800F8F0C
    TornadoLaunch_Tick_L_800F86E8:
    addi r3, r30, 0x14
    li r4, 0x4e
    bl SpriteSlot_InitNonLoop
    li r0, 0x4
    li r3, 0x0
    stb r0, 0x8c(r30)
    li r0, 0x1
    stb r3, 0x8d(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    TornadoLaunch_Tick_L_800F8710:
    mr r3, r30
    mr r4, r31
    bl TornadoItem_TickActive
    b TornadoLaunch_Tick_L_800F8F1C
    TornadoLaunch_Tick_L_800F8720:
    lbz r0, 0xcb(r30)
    extsb r3, r0
    subi r0, r3, 0x3
    cmplwi r0, 0x6
    bgt TornadoLaunch_Tick_L_800F8F1C
    lis r3, jumptable_804217D8@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_804217D8@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TornadoLaunch_Tick_L_800F87A4
    bge TornadoLaunch_Tick_L_800F87A4
    cmpwi r0, 0x0
    bge TornadoLaunch_Tick_L_800F876C
    b TornadoLaunch_Tick_L_800F87A4
    TornadoLaunch_Tick_L_800F876C:
    lfs f1, lbl_806D61F0(r2)
    addi r3, r30, 0xb8
    fmr f2, f1
    fmr f3, f1
    bl GetSpawnPosition
    li r0, 0x0
    lfs f0, lbl_806D61F0(r2)
    stb r0, 0x3c(r30)
    stfs f0, 0x14(r31)
    lfs f0, 0xc4(r30)
    stfs f0, 0x18(r31)
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    TornadoLaunch_Tick_L_800F87A4:
    lfs f2, lbl_806D61F4(r2)
    mr r3, r30
    lfs f1, 0x18(r31)
    addi r4, r31, 0x14
    fmr f3, f2
    bl Item_AdvanceTetherToJoint13
    cmpwi r3, 0x0
    beq TornadoLaunch_Tick_L_800F8F1C
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TornadoLaunch_Tick_L_800F8F1C
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TornadoLaunch_Tick_L_800F8850
    bge TornadoLaunch_Tick_L_800F8850
    cmpwi r0, 0x0
    bge TornadoLaunch_Tick_L_800F87FC
    b TornadoLaunch_Tick_L_800F8850
    TornadoLaunch_Tick_L_800F87FC:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x60
    lwz r0, 0xa4(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stw r6, 0x60(r1)
    stw r0, 0x64(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x68(r1)
    bl ItemObject_GetGroundTypeAt
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq TornadoLaunch_Tick_L_800F883C
    li r0, 0xa
    stw r0, 0x4(r31)
    b TornadoLaunch_Tick_L_800F8844
    TornadoLaunch_Tick_L_800F883C:
    li r0, 0x0
    stw r0, 0x4(r31)
    TornadoLaunch_Tick_L_800F8844:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    TornadoLaunch_Tick_L_800F8850:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne TornadoLaunch_Tick_L_800F8894
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D61F8(r2)
    lfs f0, lbl_806D61F0(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge TornadoLaunch_Tick_L_800F8894
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TornadoLaunch_Tick_L_800F8F1C
    TornadoLaunch_Tick_L_800F8894:
    lfs f1, 0xbc(r30)
    addi r3, r1, 0x6c
    lfs f0, lbl_806D61FC(r2)
    addi r4, r1, 0x14
    li r5, 0x0
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x6c(r1)
    stw r0, 0x70(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x74(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq TornadoLaunch_Tick_L_800F88F4
    lfs f1, 0x14(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x14(r1)
    stfs f0, 0x14(r31)
    TornadoLaunch_Tick_L_800F88F4:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmpwi r0, 0x7
    beq TornadoLaunch_Tick_L_800F8944
    bge TornadoLaunch_Tick_L_800F8920
    cmpwi r0, 0x5
    beq TornadoLaunch_Tick_L_800F897C
    bge TornadoLaunch_Tick_L_800F8998
    cmpwi r0, 0x4
    bge TornadoLaunch_Tick_L_800F892C
    b TornadoLaunch_Tick_L_800F8998
    TornadoLaunch_Tick_L_800F8920:
    cmpwi r0, 0x9
    beq TornadoLaunch_Tick_L_800F895C
    b TornadoLaunch_Tick_L_800F8998
    TornadoLaunch_Tick_L_800F892C:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6200(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8998
    TornadoLaunch_Tick_L_800F8944:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6200(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8998
    TornadoLaunch_Tick_L_800F895C:
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    fmr f2, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8998
    TornadoLaunch_Tick_L_800F897C:
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    fmr f2, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    TornadoLaunch_Tick_L_800F8998:
    lfs f1, lbl_806D6204(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b TornadoLaunch_Tick_L_800F8F1C
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TornadoLaunch_Tick_L_800F8A1C
    bge TornadoLaunch_Tick_L_800F8A1C
    cmpwi r0, 0x0
    bge TornadoLaunch_Tick_L_800F89C8
    b TornadoLaunch_Tick_L_800F8A1C
    TornadoLaunch_Tick_L_800F89C8:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x48
    lwz r0, 0xa4(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stw r6, 0x48(r1)
    stw r0, 0x4c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x50(r1)
    bl ItemObject_GetGroundTypeAt
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq TornadoLaunch_Tick_L_800F8A08
    li r0, 0xa
    stw r0, 0x4(r31)
    b TornadoLaunch_Tick_L_800F8A10
    TornadoLaunch_Tick_L_800F8A08:
    li r0, 0x0
    stw r0, 0x4(r31)
    TornadoLaunch_Tick_L_800F8A10:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    TornadoLaunch_Tick_L_800F8A1C:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne TornadoLaunch_Tick_L_800F8A60
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D61F8(r2)
    lfs f0, lbl_806D61F0(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge TornadoLaunch_Tick_L_800F8A60
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TornadoLaunch_Tick_L_800F8F1C
    TornadoLaunch_Tick_L_800F8A60:
    lfs f1, 0xbc(r30)
    addi r3, r1, 0x54
    lfs f0, lbl_806D61FC(r2)
    addi r4, r1, 0x10
    li r5, 0x0
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x54(r1)
    stw r0, 0x58(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x5c(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq TornadoLaunch_Tick_L_800F8AC0
    lfs f1, 0x10(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x10(r1)
    stfs f0, 0x14(r31)
    TornadoLaunch_Tick_L_800F8AC0:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmpwi r0, 0x7
    beq TornadoLaunch_Tick_L_800F8B10
    bge TornadoLaunch_Tick_L_800F8AEC
    cmpwi r0, 0x5
    beq TornadoLaunch_Tick_L_800F8B48
    bge TornadoLaunch_Tick_L_800F8B64
    cmpwi r0, 0x4
    bge TornadoLaunch_Tick_L_800F8AF8
    b TornadoLaunch_Tick_L_800F8B64
    TornadoLaunch_Tick_L_800F8AEC:
    cmpwi r0, 0x9
    beq TornadoLaunch_Tick_L_800F8B28
    b TornadoLaunch_Tick_L_800F8B64
    TornadoLaunch_Tick_L_800F8AF8:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6200(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8B64
    TornadoLaunch_Tick_L_800F8B10:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6200(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8B64
    TornadoLaunch_Tick_L_800F8B28:
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    fmr f2, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8B64
    TornadoLaunch_Tick_L_800F8B48:
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    fmr f2, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    TornadoLaunch_Tick_L_800F8B64:
    lfs f1, lbl_806D6204(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b TornadoLaunch_Tick_L_800F8F1C
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TornadoLaunch_Tick_L_800F8BE8
    bge TornadoLaunch_Tick_L_800F8BE8
    cmpwi r0, 0x0
    bge TornadoLaunch_Tick_L_800F8B94
    b TornadoLaunch_Tick_L_800F8BE8
    TornadoLaunch_Tick_L_800F8B94:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x30
    lwz r0, 0xa4(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stw r6, 0x30(r1)
    stw r0, 0x34(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x38(r1)
    bl ItemObject_GetGroundTypeAt
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq TornadoLaunch_Tick_L_800F8BD4
    li r0, 0xa
    stw r0, 0x4(r31)
    b TornadoLaunch_Tick_L_800F8BDC
    TornadoLaunch_Tick_L_800F8BD4:
    li r0, 0x0
    stw r0, 0x4(r31)
    TornadoLaunch_Tick_L_800F8BDC:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    TornadoLaunch_Tick_L_800F8BE8:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne TornadoLaunch_Tick_L_800F8C2C
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D61F8(r2)
    lfs f0, lbl_806D61F0(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge TornadoLaunch_Tick_L_800F8C2C
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TornadoLaunch_Tick_L_800F8F1C
    TornadoLaunch_Tick_L_800F8C2C:
    lfs f1, 0xbc(r30)
    addi r3, r1, 0x3c
    lfs f0, lbl_806D61FC(r2)
    addi r4, r1, 0xc
    li r5, 0x0
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x3c(r1)
    stw r0, 0x40(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x44(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq TornadoLaunch_Tick_L_800F8C8C
    lfs f1, 0xc(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0xc(r1)
    stfs f0, 0x14(r31)
    TornadoLaunch_Tick_L_800F8C8C:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmpwi r0, 0x7
    beq TornadoLaunch_Tick_L_800F8CDC
    bge TornadoLaunch_Tick_L_800F8CB8
    cmpwi r0, 0x5
    beq TornadoLaunch_Tick_L_800F8D14
    bge TornadoLaunch_Tick_L_800F8D30
    cmpwi r0, 0x4
    bge TornadoLaunch_Tick_L_800F8CC4
    b TornadoLaunch_Tick_L_800F8D30
    TornadoLaunch_Tick_L_800F8CB8:
    cmpwi r0, 0x9
    beq TornadoLaunch_Tick_L_800F8CF4
    b TornadoLaunch_Tick_L_800F8D30
    TornadoLaunch_Tick_L_800F8CC4:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6200(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8D30
    TornadoLaunch_Tick_L_800F8CDC:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6200(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8D30
    TornadoLaunch_Tick_L_800F8CF4:
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    fmr f2, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8D30
    TornadoLaunch_Tick_L_800F8D14:
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    fmr f2, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    TornadoLaunch_Tick_L_800F8D30:
    lfs f1, lbl_806D6204(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b TornadoLaunch_Tick_L_800F8F1C
    lbz r0, 0xc9(r30)
    extsb r0, r0
    cmpwi r0, 0x1
    beq TornadoLaunch_Tick_L_800F8DB4
    bge TornadoLaunch_Tick_L_800F8DB4
    cmpwi r0, 0x0
    bge TornadoLaunch_Tick_L_800F8D60
    b TornadoLaunch_Tick_L_800F8DB4
    TornadoLaunch_Tick_L_800F8D60:
    lwz r6, 0xa0(r30)
    addi r3, r1, 0x18
    lwz r0, 0xa4(r30)
    addi r4, r31, 0x14
    li r5, 0x0
    stw r6, 0x18(r1)
    stw r0, 0x1c(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x20(r1)
    bl ItemObject_GetGroundTypeAt
    lbz r0, 0xcb(r30)
    cmpwi r0, 0x5
    beq TornadoLaunch_Tick_L_800F8DA0
    li r0, 0xa
    stw r0, 0x4(r31)
    b TornadoLaunch_Tick_L_800F8DA8
    TornadoLaunch_Tick_L_800F8DA0:
    li r0, 0x0
    stw r0, 0x4(r31)
    TornadoLaunch_Tick_L_800F8DA8:
    lbz r3, 0xc9(r30)
    addi r0, r3, 0x1
    stb r0, 0xc9(r30)
    TornadoLaunch_Tick_L_800F8DB4:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne TornadoLaunch_Tick_L_800F8DF8
    lfs f2, 0x2c(r30)
    lfs f1, lbl_806D61F8(r2)
    lfs f0, lbl_806D61F0(r2)
    fsubs f1, f2, f1
    stfs f1, 0x2c(r30)
    lfs f1, 0x2c(r30)
    fcmpo cr0, f1, f0
    bge TornadoLaunch_Tick_L_800F8DF8
    li r3, 0x0
    li r0, 0x3
    stb r3, 0x28(r30)
    stb r0, 0xc8(r30)
    stb r3, 0xc9(r30)
    b TornadoLaunch_Tick_L_800F8F1C
    TornadoLaunch_Tick_L_800F8DF8:
    lfs f1, 0xbc(r30)
    addi r3, r1, 0x24
    lfs f0, lbl_806D61FC(r2)
    addi r4, r1, 0x8
    li r5, 0x0
    fadds f0, f1, f0
    stfs f0, 0xbc(r30)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x24(r1)
    stw r0, 0x28(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x2c(r1)
    bl ItemObject_GetGroundTypeAt
    extsb. r0, r3
    beq TornadoLaunch_Tick_L_800F8E58
    lfs f1, 0x8(r1)
    lfs f0, 0x14(r31)
    lfs f2, 0xa4(r30)
    fsubs f0, f1, f0
    fadds f0, f2, f0
    stfs f0, 0xa4(r30)
    lfs f0, 0x8(r1)
    stfs f0, 0x14(r31)
    TornadoLaunch_Tick_L_800F8E58:
    lbz r0, 0xcb(r30)
    extsb r0, r0
    cmpwi r0, 0x7
    beq TornadoLaunch_Tick_L_800F8EA8
    bge TornadoLaunch_Tick_L_800F8E84
    cmpwi r0, 0x5
    beq TornadoLaunch_Tick_L_800F8EE0
    bge TornadoLaunch_Tick_L_800F8EFC
    cmpwi r0, 0x4
    bge TornadoLaunch_Tick_L_800F8E90
    b TornadoLaunch_Tick_L_800F8EFC
    TornadoLaunch_Tick_L_800F8E84:
    cmpwi r0, 0x9
    beq TornadoLaunch_Tick_L_800F8EC0
    b TornadoLaunch_Tick_L_800F8EFC
    TornadoLaunch_Tick_L_800F8E90:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6200(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8EFC
    TornadoLaunch_Tick_L_800F8EA8:
    lfs f1, 0xac(r30)
    lfs f0, lbl_806D6200(r2)
    fsubs f1, f1, f0
    bl BuildOrientationFromYaw
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8EFC
    TornadoLaunch_Tick_L_800F8EC0:
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    fmr f2, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    b TornadoLaunch_Tick_L_800F8EFC
    TornadoLaunch_Tick_L_800F8EE0:
    addi r3, r30, 0xb8
    bl Vec3_ToPitch
    fmr f2, f1
    lfs f1, 0xac(r30)
    lfs f3, lbl_806D61F4(r2)
    bl AngleStepTowards_Shortest
    stfs f1, 0xac(r30)
    TornadoLaunch_Tick_L_800F8EFC:
    lfs f1, lbl_806D6204(r2)
    mr r3, r30
    bl Item_DecayVelocityScalar
    b TornadoLaunch_Tick_L_800F8F1C
    TornadoLaunch_Tick_L_800F8F0C:
    bl ItemObject_DecrementCategoryBudget
    mr r3, r30
    bl SpriteSlot_Container_Free
    b TornadoLaunch_Tick_L_800F8FC0
    TornadoLaunch_Tick_L_800F8F1C:
    addi r3, r30, 0xa0
    addi r5, r30, 0xb8
    mr r4, r3
    bl Vec3_Add_DestFirst
    lwz r6, 0xac(r30)
    addi r3, r30, 0x14
    lwz r0, 0xb0(r30)
    addi r4, r1, 0x84
    addi r5, r1, 0x78
    stw r6, 0x78(r1)
    stw r0, 0x7c(r1)
    lwz r0, 0xb4(r30)
    stw r0, 0x80(r1)
    lwz r6, 0xa0(r30)
    lwz r0, 0xa4(r30)
    stw r6, 0x84(r1)
    stw r0, 0x88(r1)
    lwz r0, 0xa8(r30)
    stw r0, 0x8c(r1)
    lfs f1, 0xc4(r30)
    bl SpriteSlot_SetTransform
    lwz r3, 0x4(r31)
    cmplwi r3, 0x0
    beq TornadoLaunch_Tick_L_800F8F84
    subi r0, r3, 0x1
    stw r0, 0x4(r31)
    TornadoLaunch_Tick_L_800F8F84:
    lwz r3, 0x8(r31)
    cmplwi r3, 0x0
    beq TornadoLaunch_Tick_L_800F8F98
    subi r0, r3, 0x1
    stw r0, 0x8(r31)
    TornadoLaunch_Tick_L_800F8F98:
    lwz r3, 0xc(r31)
    cmplwi r3, 0x0
    beq TornadoLaunch_Tick_L_800F8FAC
    subi r0, r3, 0x1
    stw r0, 0xc(r31)
    TornadoLaunch_Tick_L_800F8FAC:
    lwz r3, 0x10(r31)
    cmplwi r3, 0x0
    beq TornadoLaunch_Tick_L_800F8FC0
    subi r0, r3, 0x1
    stw r0, 0x10(r31)
    TornadoLaunch_Tick_L_800F8FC0:
    lwz r0, 0xa4(r1)
    lwz r31, 0x9c(r1)
    lwz r30, 0x98(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}

