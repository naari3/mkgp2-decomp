/* === extracted from auto_clFlowItemSelect_Dto_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ItemDisplay_Destroy();
extern void ItemDisplay_GetOrCreate();
extern void ItemDisplay_Stop();
extern void MemoryManager_TimedFree();
extern void SetScreenBrightness();
extern void SpriteAnimHandle_Destroy();
extern void SpriteHandle_Destroy();
extern void __unexpected();
extern void dtor_801BA14C();
extern void fn_80121210();
extern void fn_80169C44();
extern void fn_8023CFE0();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_pInputState;
extern unsigned int lbl_806D1264;
extern unsigned int lbl_806D9DF8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8049B148[];

/* --- function index (1 fns, .text 0x801CC104..0x801CC2EC) ---
 * [  0] 0x801CC104 size:0x1E8   global clFlowItemSelect_Dtor
 */

/* --- forward decls --- */
asm void clFlowItemSelect_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clFlowItemSelect_Dtor[40] = {
    0x38, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x01, 0x9C,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x01, 0xA8,
    0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
    0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xA0,
    0x00, 0x00, 0x00, 0x08, 0x8D, 0x00, 0x00, 0x08
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowItemSelect_Dtor = {
    (void *)&clFlowItemSelect_Dtor, 0x000001E8, (void *)extab_clFlowItemSelect_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowItemSelect_Dtor(void) { /* 0x801CC104 size:0x1E8 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stmw r25, 0x24(r1)
    mr. r29, r3
    mr r31, r1
    mr r30, r4
    beq clFlowItemSelect_Dtor_L_801CC2CC
    lis r3, lbl_8049B148@ha
    addi r0, r3, lbl_8049B148@l
    stw r0, 0x0(r29)
    bl fn_80169C44
    lfs f1, lbl_806D9DF8(r2)
    bl SetScreenBrightness
    bl ItemDisplay_GetOrCreate
    bl ItemDisplay_Stop
    bl ItemDisplay_Destroy
    mr r27, r29
    li r26, 0x0
    b clFlowItemSelect_Dtor_L_801CC194
    clFlowItemSelect_Dtor_L_801CC154:
    mr r28, r27
    li r25, 0x0
    b clFlowItemSelect_Dtor_L_801CC184
    clFlowItemSelect_Dtor_L_801CC160:
    lwz r3, 0x98(r28)
    cmplwi r3, 0x0
    beq clFlowItemSelect_Dtor_L_801CC17C
    beq clFlowItemSelect_Dtor_L_801CC174
    bl MemoryManager_TimedFree
    clFlowItemSelect_Dtor_L_801CC174:
    li r0, 0x0
    stw r0, 0x98(r28)
    clFlowItemSelect_Dtor_L_801CC17C:
    addi r28, r28, 0x4
    addi r25, r25, 0x1
    clFlowItemSelect_Dtor_L_801CC184:
    cmpwi r25, 0x4
    blt clFlowItemSelect_Dtor_L_801CC160
    addi r27, r27, 0x10
    addi r26, r26, 0x1
    clFlowItemSelect_Dtor_L_801CC194:
    cmpwi r26, 0x3
    blt clFlowItemSelect_Dtor_L_801CC154
    lwz r3, g_pInputState(r13)
    cmplwi r3, 0x0
    bne clFlowItemSelect_Dtor_L_801CC1B0
    li r0, 0x0
    b clFlowItemSelect_Dtor_L_801CC1B4
    clFlowItemSelect_Dtor_L_801CC1B0:
    mr r0, r3
    clFlowItemSelect_Dtor_L_801CC1B4:
    cmplwi r0, 0x0
    beq clFlowItemSelect_Dtor_L_801CC1D8
    cmplwi r3, 0x0
    bne clFlowItemSelect_Dtor_L_801CC1C8
    li r3, 0x0
    clFlowItemSelect_Dtor_L_801CC1C8:
    li r0, 0x0
    stb r0, 0x4(r3)
    stw r0, 0x18(r3)
    stw r0, 0x1c(r3)
    clFlowItemSelect_Dtor_L_801CC1D8:
    lwz r0, 0x4(r29)
    addi r3, r13, -0x5ABC  /* lbl_806D1264 */
    mr r27, r29
    li r25, 0x0
    stb r0, lbl_806D1264(r13)
    lwz r0, 0x8(r29)
    stb r0, 0x1(r3)
    lwz r0, 0xc(r29)
    stb r0, 0x2(r3)
    b clFlowItemSelect_Dtor_L_801CC224
    clFlowItemSelect_Dtor_L_801CC200:
    lwz r3, 0x80(r27)
    cmplwi r3, 0x0
    beq clFlowItemSelect_Dtor_L_801CC21C
    li r4, 0x1
    bl SpriteAnimHandle_Destroy
    li r0, 0x0
    stw r0, 0x80(r27)
    clFlowItemSelect_Dtor_L_801CC21C:
    addi r27, r27, 0x4
    addi r25, r25, 0x1
    clFlowItemSelect_Dtor_L_801CC224:
    cmpwi r25, 0x5
    blt clFlowItemSelect_Dtor_L_801CC200
    mr r27, r29
    li r25, 0x0
    b clFlowItemSelect_Dtor_L_801CC248
    clFlowItemSelect_Dtor_L_801CC238:
    lwz r3, 0x94(r27)
    bl SpriteHandle_Destroy
    addi r27, r27, 0x4
    addi r25, r25, 0x1
    clFlowItemSelect_Dtor_L_801CC248:
    cmpwi r25, 0x1
    blt clFlowItemSelect_Dtor_L_801CC238
    mr r27, r29
    li r25, 0x0
    b clFlowItemSelect_Dtor_L_801CC280
    clFlowItemSelect_Dtor_L_801CC25C:
    lwz r3, 0xdc(r27)
    cmplwi r3, 0x0
    beq clFlowItemSelect_Dtor_L_801CC278
    beq clFlowItemSelect_Dtor_L_801CC270
    bl MemoryManager_TimedFree
    clFlowItemSelect_Dtor_L_801CC270:
    li r0, 0x0
    stw r0, 0xdc(r27)
    clFlowItemSelect_Dtor_L_801CC278:
    addi r27, r27, 0x4
    addi r25, r25, 0x1
    clFlowItemSelect_Dtor_L_801CC280:
    cmpwi r25, 0x3
    blt clFlowItemSelect_Dtor_L_801CC25C
    bl fn_80121210
    addic. r0, r29, 0xe8
    beq clFlowItemSelect_Dtor_L_801CC2B0
    lwz r3, 0xe8(r29)
    li r4, 0x1
    bl fn_8023CFE0
    b clFlowItemSelect_Dtor_L_801CC2B0
    addi r3, r31, 0x8
    bl __unexpected
    clFlowItemSelect_Dtor_L_801CC2AC:
    b clFlowItemSelect_Dtor_L_801CC2AC
    clFlowItemSelect_Dtor_L_801CC2B0:
    mr r3, r29
    li r4, 0x0
    bl dtor_801BA14C
    extsh. r0, r30
    ble clFlowItemSelect_Dtor_L_801CC2CC
    mr r3, r29
    bl MemoryManager_TimedFree
    clFlowItemSelect_Dtor_L_801CC2CC:
    mr r10, r31
    mr r3, r29
    lmw r25, 0x24(r10)
    lwz r10, 0x0(r1)
    lwz r0, 0x4(r10)
    mr r1, r10
    mtlr r0
    blr
}

