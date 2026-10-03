/* Bounded genuine C++ retrofit draft: 80.677246%, 756 bytes.
 * Three material approaches retained the same output. Owned automatic EH
 * was exact; scale FP homes and tens-digit/reset scheduling remain.
 * Original assembly below remains the accepted source-linked fallback. */
#if 0
/* Observed timer display constructor and local ResCtrl lifetime.
 * The empty inline destructor has no normal-path work; its weak EH copy
 * resolves to the existing strong dtor_80082960 at final link. */
#pragma cplusplus on
#pragma exceptions on
typedef unsigned char u8;
struct ResCtrl {
    int resourceId;
    char pad04[0x10-4];
    u8 visible;
    char pad11[3];
    float x, y, z;
    char pad20[0x2c-0x20];
    float scaleX, scaleY;
    char pad34[0x58-0x34];
    ResCtrl();
    ~ResCtrl() {}
};
extern "C" void *SpriteHandle_CreateDefault(ResCtrl *, int);
extern "C" void fn_80121E10(ResCtrl *);
extern const float lbl_806DAD70;
extern const float lbl_806DAD7C;
extern const float lbl_806DAE10;
extern const float lbl_803C3CF0[];
struct JumpTimer {
    int state;
    int value;
    u8 active;
    char pad09[3];
    float elapsed;
    void *sprites[7];
    JumpTimer(int);
};
JumpTimer::JumpTimer(int input) {
    state = 0;
    value = input;
    active = 0;
    elapsed = lbl_806DAD7C;
    ResCtrl desc;
    desc.resourceId = 0x1b72;
    desc.visible = 1;
    desc.x = lbl_803C3CF0[0];
    desc.y = lbl_803C3CF0[1];
    desc.z = lbl_806DAD70;
    sprites[0] = SpriteHandle_CreateDefault(&desc, 4);
    fn_80121E10(&desc);
    desc.resourceId = 0x1ecd;
    desc.visible = 1;
    desc.x = lbl_803C3CF0[2];
    desc.y = lbl_803C3CF0[3];
    desc.z = lbl_806DAD70;
    sprites[1] = SpriteHandle_CreateDefault(&desc, 4);
    desc.visible = 1;
    desc.x = lbl_803C3CF0[4];
    desc.y = lbl_803C3CF0[5];
    desc.z = lbl_806DAD70;
    sprites[2] = SpriteHandle_CreateDefault(&desc, 4);
    fn_80121E10(&desc);
    desc.resourceId = 0x1b73;
    desc.visible = 1;
    desc.x = lbl_803C3CF0[6];
    desc.y = lbl_803C3CF0[7];
    desc.z = lbl_806DAD70;
    sprites[3] = SpriteHandle_CreateDefault(&desc, 4);
    int digit = (input / 100) % 10;
    fn_80121E10(&desc);
    int id = 0x1ecd;
    if (digit != 0) id = digit + 0x1b73;
    desc.resourceId = id;
    desc.visible = 1;
    desc.x = lbl_803C3CF0[8];
    desc.y = lbl_803C3CF0[9];
    desc.z = lbl_806DAD70;
    desc.scaleX = lbl_806DAE10;
    desc.scaleY = lbl_806DAE10;
    sprites[4] = SpriteHandle_CreateDefault(&desc, 4);
    digit = (input / 10) % 10;
    fn_80121E10(&desc);
    desc.resourceId = digit + 0x1b73;
    desc.visible = 1;
    desc.x = lbl_803C3CF0[10];
    desc.y = lbl_803C3CF0[11];
    desc.z = lbl_806DAD70;
    desc.scaleX = lbl_806DAE10;
    desc.scaleY = lbl_806DAE10;
    sprites[5] = SpriteHandle_CreateDefault(&desc, 4);
    fn_80121E10(&desc);
    desc.resourceId = input % 10 + 0x1b73;
    desc.visible = 1;
    desc.x = lbl_803C3CF0[12];
    desc.y = lbl_803C3CF0[13];
    desc.z = lbl_806DAD70;
    desc.scaleX = lbl_806DAE10;
    desc.scaleY = lbl_806DAE10;
    sprites[6] = SpriteHandle_CreateDefault(&desc, 4);
}
#pragma exceptions reset
#pragma cplusplus reset
#endif

/* === extracted from auto_JumpDistanceMode_Ini_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ResCtrl_Init();
extern void SpriteHandle_CreateDefault();
extern void fn_80121E10();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806DAD70;
extern unsigned int lbl_806DAD7C;
extern unsigned int lbl_806DAE10;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803C3CF0[];

/* --- function index (1 fns, .text 0x80213A64..0x80213D58) ---
 * [  0] 0x80213A64 size:0x2F4   global JumpDistanceMode_InitTimerDisplay
 */

/* --- forward decls --- */
asm void JumpDistanceMode_InitTimerDisplay(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void dtor_80082960();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_JumpDistanceMode_InitTimerDisplay = { 0x180A0000, 0x00000078, 0x00960010, 0x00000000, 0x82000008, (void *)&dtor_80082960 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_JumpDistanceMode_InitTimerDisplay = {
    (void *)&JumpDistanceMode_InitTimerDisplay, 0x000002F4, (void *)&extab_JumpDistanceMode_InitTimerDisplay
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void JumpDistanceMode_InitTimerDisplay(void) { /* 0x80213A64 size:0x2F4 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    lfs f0, lbl_806DAD7C(r2)
    stw r0, 0x74(r1)
    li r0, 0x0
    stw r31, 0x6c(r1)
    mr r31, r4
    stw r30, 0x68(r1)
    mr r30, r3
    stw r29, 0x64(r1)
    stw r0, 0x0(r3)
    addi r3, r1, 0x8
    stw r31, 0x4(r30)
    stb r0, 0x8(r30)
    stfs f0, 0xc(r30)
    bl ResCtrl_Init
    lis r3, lbl_803C3CF0@ha
    lfsu f2, lbl_803C3CF0@l(r3)
    lfs f0, lbl_806DAD70(r2)
    li r4, 0x1b72
    lfs f1, 0x4(r3)
    li r0, 0x1
    stw r4, 0x8(r1)
    addi r3, r1, 0x8
    li r4, 0x4
    stb r0, 0x18(r1)
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    bl SpriteHandle_CreateDefault
    stw r3, 0x10(r30)
    addi r3, r1, 0x8
    bl fn_80121E10
    lis r3, lbl_803C3CF0@ha
    lfs f0, lbl_806DAD70(r2)
    addi r3, r3, lbl_803C3CF0@l
    li r4, 0x1ecd
    lfs f2, 0x8(r3)
    li r0, 0x1
    lfs f1, 0xc(r3)
    addi r3, r1, 0x8
    stw r4, 0x8(r1)
    li r4, 0x4
    stb r0, 0x18(r1)
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    bl SpriteHandle_CreateDefault
    lis r4, lbl_803C3CF0@ha
    stw r3, 0x14(r30)
    addi r3, r4, lbl_803C3CF0@l
    lfs f0, lbl_806DAD70(r2)
    lfs f2, 0x10(r3)
    li r0, 0x1
    lfs f1, 0x14(r3)
    addi r3, r1, 0x8
    stb r0, 0x18(r1)
    li r4, 0x4
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    bl SpriteHandle_CreateDefault
    stw r3, 0x18(r30)
    addi r3, r1, 0x8
    bl fn_80121E10
    lis r3, lbl_803C3CF0@ha
    lfs f0, lbl_806DAD70(r2)
    addi r3, r3, lbl_803C3CF0@l
    li r4, 0x1b73
    lfs f2, 0x18(r3)
    li r0, 0x1
    lfs f1, 0x1c(r3)
    addi r3, r1, 0x8
    stw r4, 0x8(r1)
    li r4, 0x4
    stb r0, 0x18(r1)
    stfs f2, 0x1c(r1)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    bl SpriteHandle_CreateDefault
    lis r5, 0x51ec
    lis r4, 0x6666
    subi r0, r5, 0x7ae1
    stw r3, 0x1c(r30)
    mulhw r5, r0, r31
    addi r0, r4, 0x6667
    addi r3, r1, 0x8
    srawi r4, r5, 5
    srwi r5, r4, 31
    add r5, r4, r5
    mulhw r0, r0, r5
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    subf r29, r0, r5
    bl fn_80121E10
    cmpwi r29, 0x0
    li r4, 0x1ecd
    beq JumpDistanceMode_InitTimerDisplay_L_80213BF8
    addi r4, r29, 0x1b73
    JumpDistanceMode_InitTimerDisplay_L_80213BF8:
    lis r3, lbl_803C3CF0@ha
    lfs f0, lbl_806DAE10(r2)
    addi r3, r3, lbl_803C3CF0@l
    lfs f1, lbl_806DAD70(r2)
    lfs f3, 0x20(r3)
    li r0, 0x1
    lfs f2, 0x24(r3)
    addi r3, r1, 0x8
    stw r4, 0x8(r1)
    li r4, 0x4
    stb r0, 0x18(r1)
    stfs f3, 0x1c(r1)
    stfs f2, 0x20(r1)
    stfs f1, 0x24(r1)
    stfs f0, 0x34(r1)
    stfs f0, 0x38(r1)
    bl SpriteHandle_CreateDefault
    lis r4, 0x6666
    stw r3, 0x20(r30)
    addi r6, r4, 0x6667
    addi r3, r1, 0x8
    mulhw r0, r6, r31
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r5, r0, r4
    mulhw r0, r6, r5
    srawi r0, r0, 2
    srwi r4, r0, 31
    add r0, r0, r4
    mulli r0, r0, 0xa
    subf r29, r0, r5
    bl fn_80121E10
    lis r3, lbl_803C3CF0@ha
    lfs f0, lbl_806DAE10(r2)
    addi r3, r3, lbl_803C3CF0@l
    lfs f1, lbl_806DAD70(r2)
    lfs f3, 0x28(r3)
    addi r4, r29, 0x1b73
    lfs f2, 0x2c(r3)
    li r0, 0x1
    stw r4, 0x8(r1)
    addi r3, r1, 0x8
    li r4, 0x4
    stb r0, 0x18(r1)
    stfs f3, 0x1c(r1)
    stfs f2, 0x20(r1)
    stfs f1, 0x24(r1)
    stfs f0, 0x34(r1)
    stfs f0, 0x38(r1)
    bl SpriteHandle_CreateDefault
    stw r3, 0x24(r30)
    addi r3, r1, 0x8
    bl fn_80121E10
    lis r3, 0x6666
    lfs f0, lbl_806DAE10(r2)
    addi r0, r3, 0x6667
    lis r3, lbl_803C3CF0@ha
    mulhw r4, r0, r31
    lfs f1, lbl_806DAD70(r2)
    addi r3, r3, lbl_803C3CF0@l
    stfs f0, 0x34(r1)
    lfs f3, 0x30(r3)
    li r0, 0x1
    srawi r4, r4, 2
    lfs f2, 0x34(r3)
    srwi r3, r4, 31
    stb r0, 0x18(r1)
    add r0, r4, r3
    addi r3, r1, 0x8
    mulli r0, r0, 0xa
    stfs f3, 0x1c(r1)
    li r4, 0x4
    stfs f2, 0x20(r1)
    subf r5, r0, r31
    addi r0, r5, 0x1b73
    stfs f1, 0x24(r1)
    stw r0, 0x8(r1)
    stfs f0, 0x38(r1)
    bl SpriteHandle_CreateDefault
    stw r3, 0x28(r30)
    mr r3, r30
    lwz r0, 0x74(r1)
    lwz r31, 0x6c(r1)
    lwz r30, 0x68(r1)
    lwz r29, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

