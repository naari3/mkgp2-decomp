/* KartTireFX unit: target asm extracted from dtk auto-split groups. */
/* Keep body order and extab metadata synchronized with 0x80077E24..0x80079B24. */

/* === extracted from auto_KartTireFX_ShowGearS_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void JObj_Hide();
extern void JObj_Show();

/* --- function index (1 fns, .text 0x80077E24..0x8007842C) ---
 * [  0] 0x80077E24 size:0x608   global KartTireFX_ShowGearStageJObjs
 */

/* --- forward decls --- */
asm void KartTireFX_ShowGearStageJObjs(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartTireFX_ShowGearStageJObjs[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartTireFX_ShowGearStageJObjs = {
    (void *)&KartTireFX_ShowGearStageJObjs, 0x00000608, (void *)extab_KartTireFX_ShowGearStageJObjs
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartTireFX_ShowGearStageJObjs(void) { /* 0x80077E24 size:0x608 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r3
    lwz r0, 0x18(r3)
    cmpwi r0, 0x0
    bne KartTireFX_ShowGearStageJObjs_L_80077E78
    lwz r4, 0x64(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077E5C
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_80077E5C:
    lwz r4, 0x6c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077EA8
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_80077EA8
    KartTireFX_ShowGearStageJObjs_L_80077E78:
    lwz r4, 0x64(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077E90
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80077E90:
    lwz r4, 0x6c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077EA8
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80077EA8:
    lwz r0, 0x1c(r31)
    cmpwi r0, 0x0
    bne KartTireFX_ShowGearStageJObjs_L_80077EE8
    lwz r4, 0x68(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077ECC
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_80077ECC:
    lwz r4, 0x70(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077F18
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_80077F18
    KartTireFX_ShowGearStageJObjs_L_80077EE8:
    lwz r4, 0x70(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077F00
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80077F00:
    lwz r4, 0x68(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077F18
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80077F18:
    lwz r0, 0x18(r31)
    cmpwi r0, 0x1
    bne KartTireFX_ShowGearStageJObjs_L_80077F58
    lwz r4, 0x34(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077F3C
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_80077F3C:
    lwz r4, 0x3c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077F88
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_80077F88
    KartTireFX_ShowGearStageJObjs_L_80077F58:
    lwz r4, 0x34(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077F70
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80077F70:
    lwz r4, 0x3c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077F88
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80077F88:
    lwz r0, 0x1c(r31)
    cmpwi r0, 0x1
    bne KartTireFX_ShowGearStageJObjs_L_80077FC8
    lwz r4, 0x38(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077FAC
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_80077FAC:
    lwz r4, 0x40(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077FF8
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_80077FF8
    KartTireFX_ShowGearStageJObjs_L_80077FC8:
    lwz r4, 0x38(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077FE0
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80077FE0:
    lwz r4, 0x40(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80077FF8
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80077FF8:
    lwz r0, 0x18(r31)
    cmpwi r0, 0x4
    bne KartTireFX_ShowGearStageJObjs_L_80078038
    lwz r4, 0xb4(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_8007801C
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_8007801C:
    lwz r4, 0xbc(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078068
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_80078068
    KartTireFX_ShowGearStageJObjs_L_80078038:
    lwz r4, 0xb4(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078050
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078050:
    lwz r4, 0xbc(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078068
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078068:
    lwz r0, 0x1c(r31)
    cmpwi r0, 0x4
    bne KartTireFX_ShowGearStageJObjs_L_800780A8
    lwz r4, 0xb8(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_8007808C
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_8007808C:
    lwz r4, 0xc0(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800780D8
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_800780D8
    KartTireFX_ShowGearStageJObjs_L_800780A8:
    lwz r4, 0xb8(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800780C0
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_800780C0:
    lwz r4, 0xc0(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800780D8
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_800780D8:
    lwz r0, 0x18(r31)
    cmpwi r0, 0x2
    bne KartTireFX_ShowGearStageJObjs_L_80078148
    lwz r4, 0x44(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800780FC
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_800780FC:
    lwz r4, 0x4c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078114
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_80078114:
    lwz r4, 0x54(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_8007812C
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_8007812C:
    lwz r4, 0x5c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800781A8
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_800781A8
    KartTireFX_ShowGearStageJObjs_L_80078148:
    lwz r4, 0x44(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078160
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078160:
    lwz r4, 0x4c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078178
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078178:
    lwz r4, 0x54(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078190
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078190:
    lwz r4, 0x5c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800781A8
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_800781A8:
    lwz r0, 0x1c(r31)
    cmpwi r0, 0x2
    bne KartTireFX_ShowGearStageJObjs_L_80078218
    lwz r4, 0x48(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800781CC
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_800781CC:
    lwz r4, 0x50(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800781E4
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_800781E4:
    lwz r4, 0x58(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800781FC
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_800781FC:
    lwz r4, 0x60(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078278
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_80078278
    KartTireFX_ShowGearStageJObjs_L_80078218:
    lwz r4, 0x48(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078230
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078230:
    lwz r4, 0x50(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078248
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078248:
    lwz r4, 0x58(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078260
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078260:
    lwz r4, 0x60(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078278
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078278:
    lwz r0, 0x18(r31)
    cmpwi r0, 0x3
    bne KartTireFX_ShowGearStageJObjs_L_800782E8
    lwz r4, 0x94(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_8007829C
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_8007829C:
    lwz r4, 0x9c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800782B4
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_800782B4:
    lwz r4, 0xa4(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800782CC
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_800782CC:
    lwz r4, 0xac(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078348
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_80078348
    KartTireFX_ShowGearStageJObjs_L_800782E8:
    lwz r4, 0x94(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078300
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078300:
    lwz r4, 0x9c(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078318
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078318:
    lwz r4, 0xa4(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078330
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078330:
    lwz r4, 0xac(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078348
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078348:
    lwz r0, 0x1c(r31)
    cmpwi r0, 0x3
    bne KartTireFX_ShowGearStageJObjs_L_800783B8
    lwz r4, 0xa8(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_8007836C
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_8007836C:
    lwz r4, 0xb0(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078384
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_80078384:
    lwz r4, 0x98(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_8007839C
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    KartTireFX_ShowGearStageJObjs_L_8007839C:
    lwz r4, 0xa0(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078418
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Show
    b KartTireFX_ShowGearStageJObjs_L_80078418
    KartTireFX_ShowGearStageJObjs_L_800783B8:
    lwz r4, 0xa8(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800783D0
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_800783D0:
    lwz r4, 0xb0(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_800783E8
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_800783E8:
    lwz r4, 0x98(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078400
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078400:
    lwz r4, 0xa0(r31)
    cmplwi r4, 0x0
    beq KartTireFX_ShowGearStageJObjs_L_80078418
    lwz r3, 0x20(r31)
    li r5, 0x10
    bl JObj_Hide
    KartTireFX_ShowGearStageJObjs_L_80078418:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


/* === extracted from auto_KartTireFX_ResolveJo_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void ResolveJointByName();
extern void clNormal3D_Construct();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803115F0[];

/* --- function index (1 fns, .text 0x8007842C..0x80078778) ---
 * [  0] 0x8007842C size:0x34C   global KartTireFX_ResolveJoints
 */

/* --- forward decls --- */
asm void KartTireFX_ResolveJoints(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; void *f9; } extab_KartTireFX_ResolveJoints = { 0x30080000, 0x000000BC, 0x00000018, 0x000000E0, 0x00000020, 0x00000000, 0x8A80001B, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartTireFX_ResolveJoints = {
    (void *)&KartTireFX_ResolveJoints, 0x0000034C, (void *)&extab_KartTireFX_ResolveJoints
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartTireFX_ResolveJoints(void) { /* 0x8007842C size:0x34C */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    lis r6, lbl_803115F0@ha
    cmpwi r5, 0x2
    stw r0, 0x64(r1)
    stmw r26, 0x48(r1)
    addi r31, r6, lbl_803115F0@l
    mr r30, r3
    mr r26, r4
    lwz r27, 0x160(r31)
    lwz r28, 0x164(r31)
    lwz r29, 0x168(r31)
    lwz r12, 0x16c(r31)
    lwz r11, 0x170(r31)
    lwz r10, 0x174(r31)
    lwz r9, 0x178(r31)
    lwz r8, 0x17c(r31)
    lwz r7, 0x180(r31)
    lwz r6, 0x184(r31)
    lwz r4, 0x188(r31)
    lwz r3, 0x18c(r31)
    lwz r0, 0x190(r31)
    stw r27, 0x8(r1)
    stw r28, 0xc(r1)
    stw r29, 0x10(r1)
    stw r12, 0x14(r1)
    stw r11, 0x18(r1)
    stw r10, 0x1c(r1)
    stw r9, 0x20(r1)
    stw r8, 0x24(r1)
    stw r7, 0x28(r1)
    stw r6, 0x2c(r1)
    stw r4, 0x30(r1)
    stw r3, 0x34(r1)
    stw r0, 0x38(r1)
    beq KartTireFX_ResolveJoints_L_800784C4
    cmpwi r5, 0x3
    bne KartTireFX_ResolveJoints_L_800784F0
    KartTireFX_ResolveJoints_L_800784C4:
    li r3, 0x5c
    bl Alloc
    mr. r27, r3
    beq KartTireFX_ResolveJoints_L_800784E8
    slwi r0, r26, 2
    addi r4, r1, 0x8
    lwzx r4, r4, r0
    li r5, 0x0
    bl clNormal3D_Construct
    KartTireFX_ResolveJoints_L_800784E8:
    stw r27, 0x20(r30)
    b KartTireFX_ResolveJoints_L_80078510
    KartTireFX_ResolveJoints_L_800784F0:
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq KartTireFX_ResolveJoints_L_8007850C
    addi r4, r31, 0x194
    li r5, 0x0
    bl clNormal3D_Construct
    KartTireFX_ResolveJoints_L_8007850C:
    stw r26, 0x20(r30)
    KartTireFX_ResolveJoints_L_80078510:
    lwz r3, 0x20(r30)
    cmplwi r3, 0x0
    bne KartTireFX_ResolveJoints_L_80078524
    li r3, 0x0
    b KartTireFX_ResolveJoints_L_80078764
    KartTireFX_ResolveJoints_L_80078524:
    addi r4, r31, 0x1a4
    bl ResolveJointByName
    stw r3, 0x34(r30)
    addi r4, r31, 0x1bc
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x38(r30)
    addi r4, r31, 0x1d4
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x3c(r30)
    addi r4, r31, 0x1ec
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x40(r30)
    addi r4, r31, 0x204
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x44(r30)
    addi r4, r31, 0x21c
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x48(r30)
    addi r4, r31, 0x234
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x4c(r30)
    addi r4, r31, 0x24c
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x50(r30)
    addi r4, r31, 0x264
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x54(r30)
    addi r4, r31, 0x27c
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x58(r30)
    addi r4, r31, 0x294
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x5c(r30)
    addi r4, r31, 0x2ac
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x60(r30)
    addi r4, r31, 0x2c4
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x64(r30)
    addi r4, r31, 0x2e0
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x68(r30)
    addi r4, r31, 0x2fc
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x6c(r30)
    addi r4, r31, 0x318
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x70(r30)
    addi r4, r31, 0x334
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x74(r30)
    addi r4, r31, 0x34c
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x78(r30)
    addi r4, r31, 0x364
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x7c(r30)
    addi r4, r31, 0x37c
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x80(r30)
    addi r4, r31, 0x394
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x84(r30)
    addi r4, r31, 0x3ac
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x88(r30)
    addi r4, r31, 0x3c4
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x8c(r30)
    addi r4, r31, 0x3dc
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x90(r30)
    addi r4, r31, 0x3f4
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x94(r30)
    addi r4, r31, 0x40c
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x98(r30)
    addi r4, r31, 0x424
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0x9c(r30)
    addi r4, r31, 0x43c
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0xa0(r30)
    addi r4, r31, 0x454
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0xa4(r30)
    addi r4, r31, 0x46c
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0xa8(r30)
    addi r4, r31, 0x484
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0xac(r30)
    addi r4, r31, 0x49c
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0xb0(r30)
    addi r4, r31, 0x4b4
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0xb4(r30)
    addi r4, r31, 0x4cc
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0xb8(r30)
    addi r4, r31, 0x4e4
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0xbc(r30)
    addi r4, r31, 0x4fc
    lwz r3, 0x20(r30)
    bl ResolveJointByName
    stw r3, 0xc0(r30)
    li r3, 0x1
    KartTireFX_ResolveJoints_L_80078764:
    lmw r26, 0x48(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}


/* === extracted from auto_KartTireFX_SetRollPa_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_802D20AC();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80311608[];

/* --- function index (1 fns, .text 0x80078778..0x80078A3C) ---
 * [  0] 0x80078778 size:0x2C4   global KartTireFX_SetRollPair_Joints88_90
 */

/* --- forward decls --- */
asm void KartTireFX_SetRollPair_Joints88_90(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartTireFX_SetRollPair_Joints88_90[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartTireFX_SetRollPair_Joints88_90 = {
    (void *)&KartTireFX_SetRollPair_Joints88_90, 0x000002C4, (void *)extab_KartTireFX_SetRollPair_Joints88_90
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartTireFX_SetRollPair_Joints88_90(void) { /* 0x80078778 size:0x2C4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    stw r4, 0x1c(r3)
    lwz r0, 0x1c(r3)
    cmpwi r0, 0x0
    bne KartTireFX_SetRollPair_Joints88_90_L_800788EC
    lwz r30, 0x88(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints88_90_L_80078844
    bne KartTireFX_SetRollPair_Joints88_90_L_800787C0
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_800787C0:
    addic. r0, r31, 0xc
    bne KartTireFX_SetRollPair_Joints88_90_L_800787D8
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x317
    addi r5, r2, -0x7358  /* lbl_806D2F08 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_800787D8:
    lfs f0, 0xc(r31)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r31)
    stfs f0, 0x30(r30)
    lfs f0, 0x14(r31)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetRollPair_Joints88_90_L_80078844
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints88_90_L_80078844
    bne KartTireFX_SetRollPair_Joints88_90_L_80078818
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_80078818:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetRollPair_Joints88_90_L_80078834
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetRollPair_Joints88_90_L_80078834
    li r3, 0x1
    KartTireFX_SetRollPair_Joints88_90_L_80078834:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetRollPair_Joints88_90_L_80078844
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetRollPair_Joints88_90_L_80078844:
    lwz r30, 0x90(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints88_90_L_80078A24
    bne KartTireFX_SetRollPair_Joints88_90_L_80078864
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_80078864:
    addic. r0, r31, 0xc
    bne KartTireFX_SetRollPair_Joints88_90_L_8007887C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x317
    addi r5, r2, -0x7358  /* lbl_806D2F08 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_8007887C:
    lfs f0, 0xc(r31)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r31)
    stfs f0, 0x30(r30)
    lfs f0, 0x14(r31)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetRollPair_Joints88_90_L_80078A24
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints88_90_L_80078A24
    bne KartTireFX_SetRollPair_Joints88_90_L_800788BC
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_800788BC:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetRollPair_Joints88_90_L_800788D8
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetRollPair_Joints88_90_L_800788D8
    li r3, 0x1
    KartTireFX_SetRollPair_Joints88_90_L_800788D8:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetRollPair_Joints88_90_L_80078A24
    mr r3, r30
    bl fn_802D20AC
    b KartTireFX_SetRollPair_Joints88_90_L_80078A24
    KartTireFX_SetRollPair_Joints88_90_L_800788EC:
    lis r3, lbl_80311608@ha
    lwz r30, 0x88(r31)
    addi r5, r3, lbl_80311608@l
    lwz r4, 0x0(r5)
    cmplwi r30, 0x0
    lwz r3, 0x4(r5)
    lwz r0, 0x8(r5)
    stw r4, 0x8(r1)
    stw r3, 0xc(r1)
    stw r0, 0x10(r1)
    beq KartTireFX_SetRollPair_Joints88_90_L_80078998
    bne KartTireFX_SetRollPair_Joints88_90_L_8007892C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_8007892C:
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r1)
    stfs f1, 0x30(r30)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetRollPair_Joints88_90_L_80078998
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints88_90_L_80078998
    bne KartTireFX_SetRollPair_Joints88_90_L_8007896C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_8007896C:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetRollPair_Joints88_90_L_80078988
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetRollPair_Joints88_90_L_80078988
    li r3, 0x1
    KartTireFX_SetRollPair_Joints88_90_L_80078988:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetRollPair_Joints88_90_L_80078998
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetRollPair_Joints88_90_L_80078998:
    lwz r30, 0x90(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints88_90_L_80078A24
    bne KartTireFX_SetRollPair_Joints88_90_L_800789B8
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_800789B8:
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r1)
    stfs f1, 0x30(r30)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetRollPair_Joints88_90_L_80078A24
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints88_90_L_80078A24
    bne KartTireFX_SetRollPair_Joints88_90_L_800789F8
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints88_90_L_800789F8:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetRollPair_Joints88_90_L_80078A14
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetRollPair_Joints88_90_L_80078A14
    li r3, 0x1
    KartTireFX_SetRollPair_Joints88_90_L_80078A14:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetRollPair_Joints88_90_L_80078A24
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetRollPair_Joints88_90_L_80078A24:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


/* === extracted from auto_KartTireFX_SetRollPa_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_802D20AC();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803115FC[];

/* --- function index (1 fns, .text 0x80078A3C..0x80078D00) ---
 * [  0] 0x80078A3C size:0x2C4   global KartTireFX_SetRollPair_Joints84_8c
 */

/* --- forward decls --- */
asm void KartTireFX_SetRollPair_Joints84_8c(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartTireFX_SetRollPair_Joints84_8c[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartTireFX_SetRollPair_Joints84_8c = {
    (void *)&KartTireFX_SetRollPair_Joints84_8c, 0x000002C4, (void *)extab_KartTireFX_SetRollPair_Joints84_8c
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartTireFX_SetRollPair_Joints84_8c(void) { /* 0x80078A3C size:0x2C4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    stw r4, 0x18(r3)
    lwz r0, 0x18(r3)
    cmpwi r0, 0x0
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078BB0
    lwz r30, 0x84(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078B08
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078A84
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078A84:
    addic. r0, r31, 0xc
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078A9C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x317
    addi r5, r2, -0x7358  /* lbl_806D2F08 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078A9C:
    lfs f0, 0xc(r31)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r31)
    stfs f0, 0x30(r30)
    lfs f0, 0x14(r31)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078B08
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078B08
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078ADC
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078ADC:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078AF8
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078AF8
    li r3, 0x1
    KartTireFX_SetRollPair_Joints84_8c_L_80078AF8:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078B08
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetRollPair_Joints84_8c_L_80078B08:
    lwz r30, 0x8c(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078CE8
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078B28
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078B28:
    addic. r0, r31, 0xc
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078B40
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x317
    addi r5, r2, -0x7358  /* lbl_806D2F08 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078B40:
    lfs f0, 0xc(r31)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r31)
    stfs f0, 0x30(r30)
    lfs f0, 0x14(r31)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078CE8
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078CE8
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078B80
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078B80:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078B9C
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078B9C
    li r3, 0x1
    KartTireFX_SetRollPair_Joints84_8c_L_80078B9C:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078CE8
    mr r3, r30
    bl fn_802D20AC
    b KartTireFX_SetRollPair_Joints84_8c_L_80078CE8
    KartTireFX_SetRollPair_Joints84_8c_L_80078BB0:
    lis r3, lbl_803115FC@ha
    lwz r30, 0x84(r31)
    addi r5, r3, lbl_803115FC@l
    lwz r4, 0x0(r5)
    cmplwi r30, 0x0
    lwz r3, 0x4(r5)
    lwz r0, 0x8(r5)
    stw r4, 0x8(r1)
    stw r3, 0xc(r1)
    stw r0, 0x10(r1)
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078C5C
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078BF0
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078BF0:
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r1)
    stfs f1, 0x30(r30)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078C5C
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078C5C
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078C30
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078C30:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078C4C
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078C4C
    li r3, 0x1
    KartTireFX_SetRollPair_Joints84_8c_L_80078C4C:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078C5C
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetRollPair_Joints84_8c_L_80078C5C:
    lwz r30, 0x8c(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078CE8
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078C7C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078C7C:
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r1)
    stfs f1, 0x30(r30)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078CE8
    cmplwi r30, 0x0
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078CE8
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078CBC
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetRollPair_Joints84_8c_L_80078CBC:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078CD8
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetRollPair_Joints84_8c_L_80078CD8
    li r3, 0x1
    KartTireFX_SetRollPair_Joints84_8c_L_80078CD8:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetRollPair_Joints84_8c_L_80078CE8
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetRollPair_Joints84_8c_L_80078CE8:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


/* === extracted from auto_KartTireFX_SetVisibl_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void __assert();
extern void fn_802D20AC();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803115F0[];

/* --- function index (1 fns, .text 0x80078D00..0x80079224) ---
 * [  0] 0x80078D00 size:0x524   global KartTireFX_SetVisibleAll4Wheels
 */

/* --- forward decls --- */
asm void KartTireFX_SetVisibleAll4Wheels(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartTireFX_SetVisibleAll4Wheels[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartTireFX_SetVisibleAll4Wheels = {
    (void *)&KartTireFX_SetVisibleAll4Wheels, 0x00000524, (void *)extab_KartTireFX_SetVisibleAll4Wheels
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartTireFX_SetVisibleAll4Wheels(void) { /* 0x80078D00 size:0x524 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    cmpwi r4, 0x0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r3
    stw r30, 0x18(r1)
    stw r4, 0x18(r3)
    stw r4, 0x1c(r3)
    bne KartTireFX_SetVisibleAll4Wheels_L_80078FBC
    lwz r30, 0x84(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_80078DCC
    bne KartTireFX_SetVisibleAll4Wheels_L_80078D48
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078D48:
    addic. r0, r31, 0xc
    bne KartTireFX_SetVisibleAll4Wheels_L_80078D60
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x317
    addi r5, r2, -0x7358  /* lbl_806D2F08 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078D60:
    lfs f0, 0xc(r31)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r31)
    stfs f0, 0x30(r30)
    lfs f0, 0x14(r31)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetVisibleAll4Wheels_L_80078DCC
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_80078DCC
    bne KartTireFX_SetVisibleAll4Wheels_L_80078DA0
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078DA0:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetVisibleAll4Wheels_L_80078DBC
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetVisibleAll4Wheels_L_80078DBC
    li r3, 0x1
    KartTireFX_SetVisibleAll4Wheels_L_80078DBC:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetVisibleAll4Wheels_L_80078DCC
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetVisibleAll4Wheels_L_80078DCC:
    lwz r30, 0x8c(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_80078E70
    bne KartTireFX_SetVisibleAll4Wheels_L_80078DEC
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078DEC:
    addic. r0, r31, 0xc
    bne KartTireFX_SetVisibleAll4Wheels_L_80078E04
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x317
    addi r5, r2, -0x7358  /* lbl_806D2F08 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078E04:
    lfs f0, 0xc(r31)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r31)
    stfs f0, 0x30(r30)
    lfs f0, 0x14(r31)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetVisibleAll4Wheels_L_80078E70
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_80078E70
    bne KartTireFX_SetVisibleAll4Wheels_L_80078E44
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078E44:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetVisibleAll4Wheels_L_80078E60
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetVisibleAll4Wheels_L_80078E60
    li r3, 0x1
    KartTireFX_SetVisibleAll4Wheels_L_80078E60:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetVisibleAll4Wheels_L_80078E70
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetVisibleAll4Wheels_L_80078E70:
    lwz r30, 0x88(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_80078F14
    bne KartTireFX_SetVisibleAll4Wheels_L_80078E90
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078E90:
    addic. r0, r31, 0xc
    bne KartTireFX_SetVisibleAll4Wheels_L_80078EA8
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x317
    addi r5, r2, -0x7358  /* lbl_806D2F08 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078EA8:
    lfs f0, 0xc(r31)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r31)
    stfs f0, 0x30(r30)
    lfs f0, 0x14(r31)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetVisibleAll4Wheels_L_80078F14
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_80078F14
    bne KartTireFX_SetVisibleAll4Wheels_L_80078EE8
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078EE8:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetVisibleAll4Wheels_L_80078F04
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetVisibleAll4Wheels_L_80078F04
    li r3, 0x1
    KartTireFX_SetVisibleAll4Wheels_L_80078F04:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetVisibleAll4Wheels_L_80078F14
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetVisibleAll4Wheels_L_80078F14:
    lwz r30, 0x90(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_8007920C
    bne KartTireFX_SetVisibleAll4Wheels_L_80078F34
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078F34:
    addic. r0, r31, 0xc
    bne KartTireFX_SetVisibleAll4Wheels_L_80078F4C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x317
    addi r5, r2, -0x7358  /* lbl_806D2F08 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078F4C:
    lfs f0, 0xc(r31)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r31)
    stfs f0, 0x30(r30)
    lfs f0, 0x14(r31)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetVisibleAll4Wheels_L_8007920C
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_8007920C
    bne KartTireFX_SetVisibleAll4Wheels_L_80078F8C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078F8C:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetVisibleAll4Wheels_L_80078FA8
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetVisibleAll4Wheels_L_80078FA8
    li r3, 0x1
    KartTireFX_SetVisibleAll4Wheels_L_80078FA8:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetVisibleAll4Wheels_L_8007920C
    mr r3, r30
    bl fn_802D20AC
    b KartTireFX_SetVisibleAll4Wheels_L_8007920C
    KartTireFX_SetVisibleAll4Wheels_L_80078FBC:
    lis r3, lbl_803115F0@ha
    lwz r30, 0x84(r31)
    addi r5, r3, lbl_803115F0@l
    lwz r4, 0x0(r5)
    cmplwi r30, 0x0
    lwz r3, 0x4(r5)
    lwz r0, 0x8(r5)
    stw r4, 0x8(r1)
    stw r3, 0xc(r1)
    stw r0, 0x10(r1)
    beq KartTireFX_SetVisibleAll4Wheels_L_80079068
    bne KartTireFX_SetVisibleAll4Wheels_L_80078FFC
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80078FFC:
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r1)
    stfs f1, 0x30(r30)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetVisibleAll4Wheels_L_80079068
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_80079068
    bne KartTireFX_SetVisibleAll4Wheels_L_8007903C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_8007903C:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetVisibleAll4Wheels_L_80079058
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetVisibleAll4Wheels_L_80079058
    li r3, 0x1
    KartTireFX_SetVisibleAll4Wheels_L_80079058:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetVisibleAll4Wheels_L_80079068
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetVisibleAll4Wheels_L_80079068:
    lwz r30, 0x8c(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_800790F4
    bne KartTireFX_SetVisibleAll4Wheels_L_80079088
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80079088:
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r1)
    stfs f1, 0x30(r30)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetVisibleAll4Wheels_L_800790F4
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_800790F4
    bne KartTireFX_SetVisibleAll4Wheels_L_800790C8
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_800790C8:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetVisibleAll4Wheels_L_800790E4
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetVisibleAll4Wheels_L_800790E4
    li r3, 0x1
    KartTireFX_SetVisibleAll4Wheels_L_800790E4:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetVisibleAll4Wheels_L_800790F4
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetVisibleAll4Wheels_L_800790F4:
    lwz r30, 0x88(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_80079180
    bne KartTireFX_SetVisibleAll4Wheels_L_80079114
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80079114:
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r1)
    stfs f1, 0x30(r30)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetVisibleAll4Wheels_L_80079180
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_80079180
    bne KartTireFX_SetVisibleAll4Wheels_L_80079154
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_80079154:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetVisibleAll4Wheels_L_80079170
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetVisibleAll4Wheels_L_80079170
    li r3, 0x1
    KartTireFX_SetVisibleAll4Wheels_L_80079170:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetVisibleAll4Wheels_L_80079180
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetVisibleAll4Wheels_L_80079180:
    lwz r30, 0x90(r31)
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_8007920C
    bne KartTireFX_SetVisibleAll4Wheels_L_800791A0
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x316
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_800791A0:
    lfs f0, 0x8(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x10(r1)
    stfs f1, 0x30(r30)
    stfs f0, 0x34(r30)
    lwz r0, 0x14(r30)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_SetVisibleAll4Wheels_L_8007920C
    cmplwi r30, 0x0
    beq KartTireFX_SetVisibleAll4Wheels_L_8007920C
    bne KartTireFX_SetVisibleAll4Wheels_L_800791E0
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_SetVisibleAll4Wheels_L_800791E0:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_SetVisibleAll4Wheels_L_800791FC
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_SetVisibleAll4Wheels_L_800791FC
    li r3, 0x1
    KartTireFX_SetVisibleAll4Wheels_L_800791FC:
    clrlwi. r0, r3, 24
    bne KartTireFX_SetVisibleAll4Wheels_L_8007920C
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_SetVisibleAll4Wheels_L_8007920C:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}


/* === extracted from auto_03_80079224_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- function index (5 fns, .text 0x80079224..0x80079270) ---
 * [  0] 0x80079224 size:0x10    global KartTireFX_AddYaw
 * [  1] 0x80079234 size:0x10    global KartTireFX_AddPitch
 * [  2] 0x80079244 size:0x1C    global KartTireFX_AddSpinBoth
 * [  3] 0x80079260 size:0x8     global KartTireFX_SetYaw
 * [  4] 0x80079268 size:0x8     global KartTireFX_SetPitch
 */

/* --- forward decls --- */
asm void KartTireFX_AddYaw(void);
asm void KartTireFX_AddPitch(void);
asm void KartTireFX_AddSpinBoth(void);
asm void KartTireFX_SetYaw(void);
asm void KartTireFX_SetPitch(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartTireFX_AddYaw(void) { /* 0x80079224 size:0x10 */
    nofralloc
    lfs f0, 0x8(r3)
    fadds f0, f0, f1
    stfs f0, 0x8(r3)
    blr
}

asm void KartTireFX_AddPitch(void) { /* 0x80079234 size:0x10 */
    nofralloc
    lfs f0, 0x4(r3)
    fadds f0, f0, f1
    stfs f0, 0x4(r3)
    blr
}

asm void KartTireFX_AddSpinBoth(void) { /* 0x80079244 size:0x1C */
    nofralloc
    lfs f0, 0x4(r3)
    fadds f0, f0, f1
    stfs f0, 0x4(r3)
    lfs f0, 0x8(r3)
    fadds f0, f0, f1
    stfs f0, 0x8(r3)
    blr
}

asm void KartTireFX_SetYaw(void) { /* 0x80079260 size:0x8 */
    nofralloc
    stfs f1, 0x8(r3)
    blr
}

asm void KartTireFX_SetPitch(void) { /* 0x80079268 size:0x8 */
    nofralloc
    stfs f1, 0x4(r3)
    blr
}


/* === extracted from auto_KartTireFX_ApplyAndR_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Archive_GetRootJObj();
extern void KartTireFX_ShowGearStageJObjs();
extern void Object_RenderJObjTree();
extern void __assert();
extern void fn_8025D1B8();
extern void fn_802CD3DC();
extern void fn_802D1E34();
extern void fn_802D20AC();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80311B04[];

/* --- function index (1 fns, .text 0x80079270..0x800799D0) ---
 * [  0] 0x80079270 size:0x760   global KartTireFX_ApplyAndRender
 */

/* --- forward decls --- */
asm void KartTireFX_ApplyAndRender(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartTireFX_ApplyAndRender[8] = {
    0x18, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartTireFX_ApplyAndRender = {
    (void *)&KartTireFX_ApplyAndRender, 0x00000760, (void *)extab_KartTireFX_ApplyAndRender
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartTireFX_ApplyAndRender(void) { /* 0x80079270 size:0x760 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r31, r3
    lbz r0, 0x0(r3)
    cmplwi r0, 0x0
    bne KartTireFX_ApplyAndRender_L_800792A8
    li r3, 0x0
    b KartTireFX_ApplyAndRender_L_800799AC
    KartTireFX_ApplyAndRender_L_800792A8:
    lwz r0, 0x74(r31)
    cmplwi r0, 0x0
    beq KartTireFX_ApplyAndRender_L_800793B0
    lwz r29, 0x24(r31)
    cmplwi r29, 0x0
    bne KartTireFX_ApplyAndRender_L_800792D0
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x47c
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800792D0:
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079318
    bne KartTireFX_ApplyAndRender_L_800792EC
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800792EC:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_80079308
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_80079308
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_80079308:
    clrlwi. r0, r3, 24
    beq KartTireFX_ApplyAndRender_L_80079318
    mr r3, r29
    bl fn_802D1E34
    KartTireFX_ApplyAndRender_L_80079318:
    lwz r30, 0x74(r31)
    addi r29, r29, 0x44
    cmplwi r30, 0x0
    bne KartTireFX_ApplyAndRender_L_80079338
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x495
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079338:
    cmplwi r29, 0x0
    bne KartTireFX_ApplyAndRender_L_80079350
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x496
    addi r5, r2, -0x7350  /* lbl_806D2F10 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079350:
    mr r3, r29
    addi r4, r30, 0x44
    bl fn_8025D1B8
    lwz r0, 0x14(r30)
    cmplwi r30, 0x0
    oris r0, r0, 0x380
    stw r0, 0x14(r30)
    beq KartTireFX_ApplyAndRender_L_800793B0
    bne KartTireFX_ApplyAndRender_L_80079384
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079384:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_800793A0
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_800793A0
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_800793A0:
    clrlwi. r0, r3, 24
    bne KartTireFX_ApplyAndRender_L_800793B0
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_ApplyAndRender_L_800793B0:
    lwz r0, 0x78(r31)
    cmplwi r0, 0x0
    beq KartTireFX_ApplyAndRender_L_800794B8
    lwz r29, 0x28(r31)
    cmplwi r29, 0x0
    bne KartTireFX_ApplyAndRender_L_800793D8
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x47c
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800793D8:
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079420
    bne KartTireFX_ApplyAndRender_L_800793F4
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800793F4:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_80079410
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_80079410
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_80079410:
    clrlwi. r0, r3, 24
    beq KartTireFX_ApplyAndRender_L_80079420
    mr r3, r29
    bl fn_802D1E34
    KartTireFX_ApplyAndRender_L_80079420:
    lwz r30, 0x78(r31)
    addi r29, r29, 0x44
    cmplwi r30, 0x0
    bne KartTireFX_ApplyAndRender_L_80079440
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x495
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079440:
    cmplwi r29, 0x0
    bne KartTireFX_ApplyAndRender_L_80079458
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x496
    addi r5, r2, -0x7350  /* lbl_806D2F10 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079458:
    mr r3, r29
    addi r4, r30, 0x44
    bl fn_8025D1B8
    lwz r0, 0x14(r30)
    cmplwi r30, 0x0
    oris r0, r0, 0x380
    stw r0, 0x14(r30)
    beq KartTireFX_ApplyAndRender_L_800794B8
    bne KartTireFX_ApplyAndRender_L_8007948C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_8007948C:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_800794A8
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_800794A8
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_800794A8:
    clrlwi. r0, r3, 24
    bne KartTireFX_ApplyAndRender_L_800794B8
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_ApplyAndRender_L_800794B8:
    lwz r0, 0x7c(r31)
    cmplwi r0, 0x0
    beq KartTireFX_ApplyAndRender_L_800795C0
    lwz r29, 0x2c(r31)
    cmplwi r29, 0x0
    bne KartTireFX_ApplyAndRender_L_800794E0
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x47c
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800794E0:
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079528
    bne KartTireFX_ApplyAndRender_L_800794FC
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800794FC:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_80079518
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_80079518
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_80079518:
    clrlwi. r0, r3, 24
    beq KartTireFX_ApplyAndRender_L_80079528
    mr r3, r29
    bl fn_802D1E34
    KartTireFX_ApplyAndRender_L_80079528:
    lwz r30, 0x7c(r31)
    addi r29, r29, 0x44
    cmplwi r30, 0x0
    bne KartTireFX_ApplyAndRender_L_80079548
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x495
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079548:
    cmplwi r29, 0x0
    bne KartTireFX_ApplyAndRender_L_80079560
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x496
    addi r5, r2, -0x7350  /* lbl_806D2F10 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079560:
    mr r3, r29
    addi r4, r30, 0x44
    bl fn_8025D1B8
    lwz r0, 0x14(r30)
    cmplwi r30, 0x0
    oris r0, r0, 0x380
    stw r0, 0x14(r30)
    beq KartTireFX_ApplyAndRender_L_800795C0
    bne KartTireFX_ApplyAndRender_L_80079594
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079594:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_800795B0
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_800795B0
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_800795B0:
    clrlwi. r0, r3, 24
    bne KartTireFX_ApplyAndRender_L_800795C0
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_ApplyAndRender_L_800795C0:
    lwz r0, 0x80(r31)
    cmplwi r0, 0x0
    beq KartTireFX_ApplyAndRender_L_800796C8
    lwz r29, 0x30(r31)
    cmplwi r29, 0x0
    bne KartTireFX_ApplyAndRender_L_800795E8
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x47c
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800795E8:
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079630
    bne KartTireFX_ApplyAndRender_L_80079604
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079604:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_80079620
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_80079620
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_80079620:
    clrlwi. r0, r3, 24
    beq KartTireFX_ApplyAndRender_L_80079630
    mr r3, r29
    bl fn_802D1E34
    KartTireFX_ApplyAndRender_L_80079630:
    lwz r30, 0x80(r31)
    addi r29, r29, 0x44
    cmplwi r30, 0x0
    bne KartTireFX_ApplyAndRender_L_80079650
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x495
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079650:
    cmplwi r29, 0x0
    bne KartTireFX_ApplyAndRender_L_80079668
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x496
    addi r5, r2, -0x7350  /* lbl_806D2F10 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079668:
    mr r3, r29
    addi r4, r30, 0x44
    bl fn_8025D1B8
    lwz r0, 0x14(r30)
    cmplwi r30, 0x0
    oris r0, r0, 0x380
    stw r0, 0x14(r30)
    beq KartTireFX_ApplyAndRender_L_800796C8
    bne KartTireFX_ApplyAndRender_L_8007969C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_8007969C:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_800796B8
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_800796B8
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_800796B8:
    clrlwi. r0, r3, 24
    bne KartTireFX_ApplyAndRender_L_800796C8
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_ApplyAndRender_L_800796C8:
    lwz r29, 0x84(r31)
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079764
    lfs f31, 0x4(r31)
    bne KartTireFX_ApplyAndRender_L_800796EC
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x2a4
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800796EC:
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 14, 14
    beq KartTireFX_ApplyAndRender_L_8007970C
    lis r4, lbl_80311B04@ha
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    addi r5, r4, lbl_80311B04@l
    li r4, 0x2a5
    bl __assert
    KartTireFX_ApplyAndRender_L_8007970C:
    stfs f31, 0x1c(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_ApplyAndRender_L_80079764
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079764
    bne KartTireFX_ApplyAndRender_L_80079738
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079738:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_80079754
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_80079754
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_80079754:
    clrlwi. r0, r3, 24
    bne KartTireFX_ApplyAndRender_L_80079764
    mr r3, r29
    bl fn_802D20AC
    KartTireFX_ApplyAndRender_L_80079764:
    lwz r29, 0x88(r31)
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079800
    lfs f31, 0x4(r31)
    bne KartTireFX_ApplyAndRender_L_80079788
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x2a4
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079788:
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 14, 14
    beq KartTireFX_ApplyAndRender_L_800797A8
    lis r4, lbl_80311B04@ha
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    addi r5, r4, lbl_80311B04@l
    li r4, 0x2a5
    bl __assert
    KartTireFX_ApplyAndRender_L_800797A8:
    stfs f31, 0x1c(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_ApplyAndRender_L_80079800
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079800
    bne KartTireFX_ApplyAndRender_L_800797D4
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800797D4:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_800797F0
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_800797F0
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_800797F0:
    clrlwi. r0, r3, 24
    bne KartTireFX_ApplyAndRender_L_80079800
    mr r3, r29
    bl fn_802D20AC
    KartTireFX_ApplyAndRender_L_80079800:
    lwz r29, 0x8c(r31)
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_8007989C
    lfs f31, 0x8(r31)
    bne KartTireFX_ApplyAndRender_L_80079824
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x2a4
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079824:
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 14, 14
    beq KartTireFX_ApplyAndRender_L_80079844
    lis r4, lbl_80311B04@ha
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    addi r5, r4, lbl_80311B04@l
    li r4, 0x2a5
    bl __assert
    KartTireFX_ApplyAndRender_L_80079844:
    stfs f31, 0x1c(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_ApplyAndRender_L_8007989C
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_8007989C
    bne KartTireFX_ApplyAndRender_L_80079870
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079870:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_8007988C
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_8007988C
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_8007988C:
    clrlwi. r0, r3, 24
    bne KartTireFX_ApplyAndRender_L_8007989C
    mr r3, r29
    bl fn_802D20AC
    KartTireFX_ApplyAndRender_L_8007989C:
    lwz r29, 0x90(r31)
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079938
    lfs f31, 0x8(r31)
    bne KartTireFX_ApplyAndRender_L_800798C0
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x2a4
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_800798C0:
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 14, 14
    beq KartTireFX_ApplyAndRender_L_800798E0
    lis r4, lbl_80311B04@ha
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    addi r5, r4, lbl_80311B04@l
    li r4, 0x2a5
    bl __assert
    KartTireFX_ApplyAndRender_L_800798E0:
    stfs f31, 0x1c(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne KartTireFX_ApplyAndRender_L_80079938
    cmplwi r29, 0x0
    beq KartTireFX_ApplyAndRender_L_80079938
    bne KartTireFX_ApplyAndRender_L_8007990C
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_8007990C:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_80079928
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_80079928
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_80079928:
    clrlwi. r0, r3, 24
    bne KartTireFX_ApplyAndRender_L_80079938
    mr r3, r29
    bl fn_802D20AC
    KartTireFX_ApplyAndRender_L_80079938:
    mr r3, r31
    bl KartTireFX_ShowGearStageJObjs
    lwz r3, 0x20(r31)
    bl Archive_GetRootJObj
    mr. r30, r3
    beq KartTireFX_ApplyAndRender_L_80079990
    bne KartTireFX_ApplyAndRender_L_80079964
    addi r3, r2, -0x7368  /* lbl_806D2EF8 */
    li r4, 0x25d
    addi r5, r2, -0x7360  /* lbl_806D2F00 */
    bl __assert
    KartTireFX_ApplyAndRender_L_80079964:
    lwz r4, 0x14(r30)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne KartTireFX_ApplyAndRender_L_80079980
    rlwinm. r0, r4, 0, 25, 25
    beq KartTireFX_ApplyAndRender_L_80079980
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_80079980:
    clrlwi. r0, r3, 24
    bne KartTireFX_ApplyAndRender_L_80079990
    mr r3, r30
    bl fn_802D20AC
    KartTireFX_ApplyAndRender_L_80079990:
    lwz r3, 0x20(r31)
    bl Archive_GetRootJObj
    bl fn_802CD3DC
    lwz r3, 0x20(r31)
    li r4, 0x7
    bl Object_RenderJObjTree
    li r3, 0x1
    KartTireFX_ApplyAndRender_L_800799AC:
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


/* === extracted from auto_KartTireFX_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree();
extern void Object_DtorWithGXSync();

/* --- function index (1 fns, .text 0x800799D0..0x80079A44) ---
 * [  0] 0x800799D0 size:0x74    global KartTireFX_Dtor
 */

/* --- forward decls --- */
asm void KartTireFX_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartTireFX_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartTireFX_Dtor = {
    (void *)&KartTireFX_Dtor, 0x00000074, (void *)extab_KartTireFX_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartTireFX_Dtor(void) { /* 0x800799D0 size:0x74 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq KartTireFX_Dtor_L_80079A28
    lbz r0, 0x0(r30)
    cmplwi r0, 0x1
    bne KartTireFX_Dtor_L_80079A18
    lwz r3, 0x20(r30)
    cmplwi r3, 0x0
    beq KartTireFX_Dtor_L_80079A10
    li r4, 0x1
    bl Object_DtorWithGXSync
    KartTireFX_Dtor_L_80079A10:
    li r0, 0x0
    stw r0, 0x20(r30)
    KartTireFX_Dtor_L_80079A18:
    extsh. r0, r31
    ble KartTireFX_Dtor_L_80079A28
    mr r3, r30
    bl MemoryManager_TimedFree
    KartTireFX_Dtor_L_80079A28:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


/* === extracted from auto_KartTireFX_Ctor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void KartTireFX_ResolveJoints();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D2F14;
extern unsigned int lbl_806D2F18;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803FE018[];

/* --- function index (1 fns, .text 0x80079A44..0x80079B24) ---
 * [  0] 0x80079A44 size:0xE0    global KartTireFX_Ctor
 */

/* --- forward decls --- */
asm void KartTireFX_Ctor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartTireFX_Ctor[8] = {
    0x38, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartTireFX_Ctor = {
    (void *)&KartTireFX_Ctor, 0x000000E0, (void *)extab_KartTireFX_Ctor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartTireFX_Ctor(void) { /* 0x80079A44 size:0xE0 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stmw r25, 0x14(r1)
    mr r25, r3
    mr r26, r4
    mr r27, r5
    mr r28, r6
    mr r29, r7
    mr r30, r8
    mr r31, r9
    bl KartTireFX_ResolveJoints
    stb r3, 0x0(r25)
    li r0, 0x0
    lfs f0, lbl_806D2F14(r2)
    cmpwi r26, 0x0
    stw r0, 0x18(r25)
    stw r0, 0x1c(r25)
    stfs f0, 0x4(r25)
    stfs f0, 0x8(r25)
    stw r28, 0x24(r25)
    stw r29, 0x28(r25)
    stw r30, 0x2c(r25)
    stw r31, 0x30(r25)
    bge KartTireFX_Ctor_L_80079AC4
    cmpwi r26, 0xd
    blt KartTireFX_Ctor_L_80079AC4
    lfs f0, lbl_806D2F18(r2)
    stfs f0, 0xc(r25)
    stfs f0, 0x10(r25)
    stfs f0, 0x14(r25)
    b KartTireFX_Ctor_L_80079B0C
    KartTireFX_Ctor_L_80079AC4:
    cmpwi r27, 0x2
    beq KartTireFX_Ctor_L_80079AD4
    cmpwi r27, 0x3
    bne KartTireFX_Ctor_L_80079AE8
    KartTireFX_Ctor_L_80079AD4:
    lfs f0, lbl_806D2F18(r2)
    stfs f0, 0xc(r25)
    stfs f0, 0x10(r25)
    stfs f0, 0x14(r25)
    b KartTireFX_Ctor_L_80079B0C
    KartTireFX_Ctor_L_80079AE8:
    lis r3, lbl_803FE018@ha
    slwi r0, r26, 2
    addi r3, r3, lbl_803FE018@l
    lfsx f0, r3, r0
    stfs f0, 0xc(r25)
    lfsx f0, r3, r0
    stfs f0, 0x10(r25)
    lfsx f0, r3, r0
    stfs f0, 0x14(r25)
    KartTireFX_Ctor_L_80079B0C:
    mr r3, r25
    lmw r25, 0x14(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}


