/* === extracted from auto_clMiyoshiCardCreate_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void DisplayContext_Flush();
extern void DisplayContext_Init();
extern void DrawText();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10D8;
extern unsigned int lbl_806D1880;
extern unsigned int lbl_806D2B58;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EE028[];
extern unsigned int lbl_803F9E18[];

/* --- function index (1 fns, .text 0x80061054..0x80061394) ---
 * [  0] 0x80061054 size:0x340   global clMiyoshiCardCreate_Draw
 */

/* --- forward decls --- */
asm void clMiyoshiCardCreate_Draw(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; void *f9; } extab_clMiyoshiCardCreate_Draw = { 0x200A0000, 0x0000004C, 0x00000018, 0x00000314, 0x00000020, 0x00000000, 0x8A80001C, (void *)&MemoryManager_TimedFree, 0x8A80001C, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clMiyoshiCardCreate_Draw = {
    (void *)&clMiyoshiCardCreate_Draw, 0x00000340, (void *)&extab_clMiyoshiCardCreate_Draw
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clMiyoshiCardCreate_Draw(void) { /* 0x80061054 size:0x340 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r4, lbl_803F9E18@ha
    lis r3, lbl_802EE028@ha
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    addi r31, r3, lbl_802EE028@l
    stw r30, 0x18(r1)
    addi r30, r4, lbl_803F9E18@l
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    lwz r0, lbl_806D1880(r13)
    cmplwi r0, 0x0
    bne clMiyoshiCardCreate_Draw_L_800610A4
    li r3, 0xd8
    bl Alloc
    mr. r28, r3
    beq clMiyoshiCardCreate_Draw_L_800610A0
    bl DisplayContext_Init
    clMiyoshiCardCreate_Draw_L_800610A0:
    stw r28, lbl_806D1880(r13)
    clMiyoshiCardCreate_Draw_L_800610A4:
    lwz r28, lbl_806D1880(r13)
    addi r7, r31, 0x220
    lwz r29, lbl_806D10D8(r13)
    li r4, 0xe
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    li r5, 0x18
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0xc(r29)
    addi r4, r30, 0x24
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    slwi r0, r0, 2
    addi r7, r31, 0x22c
    lwzx r8, r4, r0
    li r4, 0x1c
    li r5, 0x48
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x10(r29)
    addi r4, r30, 0x0
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    slwi r0, r0, 2
    addi r7, r31, 0x240
    lwzx r8, r4, r0
    li r4, 0x1c
    li r5, 0x60
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x14(r29)
    addi r4, r30, 0xc
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    slwi r0, r0, 2
    addi r7, r31, 0x254
    lwzx r8, r4, r0
    li r4, 0x1c
    li r5, 0x78
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x18(r29)
    addi r4, r30, 0x18
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    slwi r0, r0, 2
    addi r7, r31, 0x268
    lwzx r8, r4, r0
    li r4, 0x1c
    li r5, 0x90
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lbz r4, 0x1c(r29)
    addi r6, r13, -0x7E60  /* lbl_806CEEC0 */
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    neg r0, r4
    addi r7, r31, 0x27c
    or r0, r0, r4
    li r4, 0x1c
    rlwinm r0, r0, 3, 29, 29
    li r5, 0xa8
    lwzx r8, r6, r0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lbz r4, 0x1d(r29)
    addi r6, r13, -0x7E58  /* lbl_806CEEC8 */
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    neg r0, r4
    addi r7, r31, 0x290
    or r0, r0, r4
    li r4, 0x1c
    rlwinm r0, r0, 3, 29, 29
    li r5, 0xc0
    lwzx r8, r6, r0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lbz r4, 0x1e(r29)
    addi r6, r13, -0x7E50  /* lbl_806CEED0 */
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    neg r0, r4
    addi r7, r31, 0x2a4
    or r0, r0, r4
    li r4, 0x1c
    rlwinm r0, r0, 3, 29, 29
    li r5, 0xd8
    lwzx r8, r6, r0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x20(r29)
    addi r4, r30, 0x58
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    slwi r0, r0, 2
    addi r7, r31, 0x2b8
    lwzx r8, r4, r0
    li r4, 0x1c
    li r5, 0xf0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lwz r0, 0x24(r29)
    cmpwi r0, 0x0
    bgt clMiyoshiCardCreate_Draw_L_80061278
    li r8, 0x0
    b clMiyoshiCardCreate_Draw_L_80061280
    clMiyoshiCardCreate_Draw_L_80061278:
    mulli r3, r0, 0x64
    subi r8, r3, 0x1
    clMiyoshiCardCreate_Draw_L_80061280:
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    addi r7, r31, 0x2cc
    li r4, 0x1c
    li r5, 0x108
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lbz r4, 0x28(r29)
    addi r6, r13, -0x7E48  /* lbl_806CEED8 */
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    neg r0, r4
    addi r7, r31, 0x2e0
    or r0, r0, r4
    li r4, 0x1c
    rlwinm r0, r0, 3, 29, 29
    li r5, 0x120
    lwzx r8, r6, r0
    li r6, 0x7
    creqv 6, 6, 6
    bl DrawText
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    li r4, 0x1c
    li r5, 0x138
    li r6, 0x7
    addi r7, r2, -0x7704  /* lbl_806D2B5C */
    creqv 6, 6, 6
    bl DrawText
    lwz r3, 0x4(r29)
    cmpwi r3, 0xa
    bne clMiyoshiCardCreate_Draw_L_8006130C
    li r5, 0x138
    b clMiyoshiCardCreate_Draw_L_80061314
    clMiyoshiCardCreate_Draw_L_8006130C:
    addi r0, r3, 0x3
    mulli r5, r0, 0x18
    clMiyoshiCardCreate_Draw_L_80061314:
    lwz r0, 0x8(r29)
    clrlwi r0, r0, 27
    stw r0, 0x8(r29)
    lwz r0, 0x8(r29)
    cmpwi r0, 0x18
    bge clMiyoshiCardCreate_Draw_L_80061348
    lfs f1, lbl_806D2B58(r2)
    mr r3, r28
    li r4, 0xe
    li r6, 0x7
    addi r7, r2, -0x76FC  /* lbl_806D2B64 */
    creqv 6, 6, 6
    bl DrawText
    clMiyoshiCardCreate_Draw_L_80061348:
    lwz r0, lbl_806D1880(r13)
    cmplwi r0, 0x0
    bne clMiyoshiCardCreate_Draw_L_8006136C
    li r3, 0xd8
    bl Alloc
    mr. r28, r3
    beq clMiyoshiCardCreate_Draw_L_80061368
    bl DisplayContext_Init
    clMiyoshiCardCreate_Draw_L_80061368:
    stw r28, lbl_806D1880(r13)
    clMiyoshiCardCreate_Draw_L_8006136C:
    lwz r3, lbl_806D1880(r13)
    bl DisplayContext_Flush
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}



/* === extracted from auto_clMiyoshiCardCreate_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CardSave_Tick();
extern void GetInputManager();
extern void InputMgr_GetPlayer();
extern void PlayerData_Construct();
extern void WrapInRange();
extern void card_rw_kick_state_machine();
extern void card_rw_state_machine();
extern void card_save_trigger();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10D8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int g_playerData[];
extern unsigned int jumptable_803F9F00[];
extern unsigned int lbl_803F9E70[];

/* --- function index (1 fns, .text 0x80061394..0x80061668) ---
 * [  0] 0x80061394 size:0x2D4   global clMiyoshiCardCreate_Tick
 */

/* --- forward decls --- */
asm void clMiyoshiCardCreate_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clMiyoshiCardCreate_Tick[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clMiyoshiCardCreate_Tick = {
    (void *)&clMiyoshiCardCreate_Tick, 0x000002D4, (void *)extab_clMiyoshiCardCreate_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clMiyoshiCardCreate_Tick(void) { /* 0x80061394 size:0x2D4 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r31, r3
    li r4, 0x1
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    mr r30, r3
    mr r3, r31
    lwz r12, 0x0(r31)
    li r4, 0x80
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    lwz r31, lbl_806D10D8(r13)
    lwz r0, 0x0(r31)
    cmpwi r0, 0x0
    bne clMiyoshiCardCreate_Tick_L_800615E4
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_80061420
    lwz r3, 0x4(r31)
    li r4, 0x0
    li r5, 0xa
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x4(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    clMiyoshiCardCreate_Tick_L_80061420:
    clrlwi r0, r30, 24
    cmplwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_8006162C
    lwz r0, 0x4(r31)
    cmplwi r0, 0xa
    bgt clMiyoshiCardCreate_Tick_L_8006162C
    lis r3, jumptable_803F9F00@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_803F9F00@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lwz r3, 0xc(r31)
    li r4, 0x0
    li r5, 0xc
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0xc(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x10(r31)
    li r4, 0x0
    li r5, 0x2
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x10(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x14(r31)
    li r4, 0x0
    li r5, 0x2
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x14(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x18(r31)
    li r4, 0x0
    li r5, 0x2
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x18(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lbz r4, 0x1c(r31)
    subfic r3, r4, 0x1
    subi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    stb r0, 0x1c(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lbz r4, 0x1d(r31)
    subfic r3, r4, 0x1
    subi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    stb r0, 0x1d(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lbz r4, 0x1e(r31)
    subfic r3, r4, 0x1
    subi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    stb r0, 0x1e(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x20(r31)
    li r4, 0x0
    li r5, 0x10
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x20(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r3, 0x24(r31)
    li r4, 0x0
    li r5, 0x28
    addi r3, r3, 0x1
    bl WrapInRange
    stw r3, 0x24(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lbz r4, 0x28(r31)
    subfic r3, r4, 0x1
    subi r0, r4, 0x1
    or r0, r3, r0
    srwi r0, r0, 31
    stb r0, 0x28(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    lwz r0, 0x24(r31)
    cmpwi r0, 0x0
    bgt clMiyoshiCardCreate_Tick_L_8006157C
    li r5, 0x0
    b clMiyoshiCardCreate_Tick_L_80061584
    clMiyoshiCardCreate_Tick_L_8006157C:
    mulli r3, r0, 0x64
    subi r5, r3, 0x1
    clMiyoshiCardCreate_Tick_L_80061584:
    lwz r0, 0x20(r31)
    lis r4, lbl_803F9E70@ha
    lis r3, g_playerData@ha
    slwi r0, r0, 2
    addi r4, r4, lbl_803F9E70@l
    lwzx r0, r4, r0
    addi r3, r3, g_playerData@l
    stw r0, 0x8(r1)
    stw r5, 0xc(r1)
    lbz r0, 0x28(r31)
    stw r0, 0x10(r1)
    lwz r4, 0xc(r31)
    lwz r5, 0x10(r31)
    lwz r6, 0x14(r31)
    lwz r7, 0x18(r31)
    lbz r8, 0x1c(r31)
    lbz r9, 0x1d(r31)
    lbz r10, 0x1e(r31)
    bl PlayerData_Construct
    li r3, 0x0
    bl card_save_trigger
    li r0, 0x1
    stw r0, 0x0(r31)
    b clMiyoshiCardCreate_Tick_L_8006162C
    clMiyoshiCardCreate_Tick_L_800615E4:
    cmpwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_8006160C
    bl CardSave_Tick
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_8006162C
    li r0, 0x2
    stw r0, 0x0(r31)
    bl card_rw_kick_state_machine
    b clMiyoshiCardCreate_Tick_L_8006162C
    clMiyoshiCardCreate_Tick_L_8006160C:
    cmpwi r0, 0x2
    bne clMiyoshiCardCreate_Tick_L_8006162C
    bl card_rw_state_machine
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne clMiyoshiCardCreate_Tick_L_8006162C
    li r0, 0x3
    stw r0, 0x0(r31)
    clMiyoshiCardCreate_Tick_L_8006162C:
    lwz r3, 0x8(r31)
    addi r0, r3, 0x1
    stw r0, 0x8(r31)
    lwz r0, 0x0(r31)
    cmpwi r0, 0x3
    bne clMiyoshiCardCreate_Tick_L_8006164C
    li r3, -0x4
    b clMiyoshiCardCreate_Tick_L_80061650
    clMiyoshiCardCreate_Tick_L_8006164C:
    li r3, -0x2
    clMiyoshiCardCreate_Tick_L_80061650:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}



/* === extracted from auto_clMiyoshiCardCreate_text_2 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree();
extern void dtor_8002CDF4();
extern void fn_801DB68C();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10D8;
extern unsigned int lbl_806D1880;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803F9EEC[];

/* --- function index (1 fns, .text 0x80061668..0x800616F8) ---
 * [  0] 0x80061668 size:0x90    global clMiyoshiCardCreate_Dtor
 */

/* --- forward decls --- */
asm void clMiyoshiCardCreate_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_clMiyoshiCardCreate_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clMiyoshiCardCreate_Dtor = {
    (void *)&clMiyoshiCardCreate_Dtor, 0x00000090, (void *)extab_clMiyoshiCardCreate_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clMiyoshiCardCreate_Dtor(void) { /* 0x80061668 size:0x90 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq clMiyoshiCardCreate_Dtor_L_800616DC
    lis r3, lbl_803F9EEC@ha
    addi r0, r3, lbl_803F9EEC@l
    stw r0, 0x0(r30)
    lwz r3, lbl_806D10D8(r13)
    bl MemoryManager_TimedFree
    lwz r3, lbl_806D1880(r13)
    li r0, 0x0
    stw r0, lbl_806D10D8(r13)
    cmplwi r3, 0x0
    bne clMiyoshiCardCreate_Dtor_L_800616C0
    li r4, 0x1
    bl fn_801DB68C
    li r0, 0x0
    stw r0, lbl_806D1880(r13)
    clMiyoshiCardCreate_Dtor_L_800616C0:
    mr r3, r30
    li r4, 0x0
    bl dtor_8002CDF4
    extsh. r0, r31
    ble clMiyoshiCardCreate_Dtor_L_800616DC
    mr r3, r30
    bl MemoryManager_TimedFree
    clMiyoshiCardCreate_Dtor_L_800616DC:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}



/* === extracted from auto_clMiyoshiCardCreate_text_3 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void GameMode_BaseInit();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D10D8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803F9EEC[];

/* --- function index (1 fns, .text 0x800616F8..0x8006178C) ---
 * [  0] 0x800616F8 size:0x94    global clMiyoshiCardCreate_Ctor
 */

/* --- forward decls --- */
asm void clMiyoshiCardCreate_Ctor(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();
extern void dtor_8002CDF4();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; void *f8; unsigned int f9; void *f10; } extab_clMiyoshiCardCreate_Ctor = { 0x08080000, 0x00000024, 0x00000024, 0x00000038, 0x00000018, 0x00000000, 0x0680001F, 0x00000000, (void *)&dtor_8002CDF4, 0x8A80001F, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clMiyoshiCardCreate_Ctor = {
    (void *)&clMiyoshiCardCreate_Ctor, 0x00000094, (void *)&extab_clMiyoshiCardCreate_Ctor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clMiyoshiCardCreate_Ctor(void) { /* 0x800616F8 size:0x94 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r3, 0x4
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    bl Alloc
    mr. r31, r3
    beq clMiyoshiCardCreate_Ctor_L_80061774
    bl GameMode_BaseInit
    lis r4, lbl_803F9EEC@ha
    li r3, 0x2c
    addi r0, r4, lbl_803F9EEC@l
    stw r0, 0x0(r31)
    bl Alloc
    cmplwi r3, 0x0
    beq clMiyoshiCardCreate_Ctor_L_80061770
    li r0, 0x0
    stw r0, 0xc(r3)
    stw r0, 0x10(r3)
    stw r0, 0x14(r3)
    stw r0, 0x18(r3)
    stb r0, 0x1c(r3)
    stb r0, 0x1d(r3)
    stb r0, 0x1e(r3)
    stw r0, 0x20(r3)
    stw r0, 0x24(r3)
    stw r0, 0x4(r3)
    stb r0, 0x28(r3)
    stw r0, 0x0(r3)
    stw r0, 0x8(r3)
    clMiyoshiCardCreate_Ctor_L_80061770:
    stw r3, lbl_806D10D8(r13)
    clMiyoshiCardCreate_Ctor_L_80061774:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


