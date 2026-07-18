/* Generated asm_fn extab bundle for the pending SceneRender methods. */
/* === extracted from auto_SceneRender_DrawObje_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void OSGetTick();
extern void Profiler_RecordFrame();
extern void fn_802C72AC();
extern void fn_802C7318();
extern void fn_802C79CC();
extern void fn_802D4748();
extern void fn_802D47E8();
extern void fn_802D6948();
extern void fn_802DB570();
extern void fn_802DB740();
extern void fn_802DB9EC();
extern void fn_802DBB84();
extern void fn_802DC0F4();
extern void fn_802DC2C0();
extern void fn_802DC4D4();
extern void fn_802DC550();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D24A8;
extern unsigned int lbl_806D24AC;
extern unsigned int lbl_806D24B0;
extern unsigned int lbl_806D24B4;
extern unsigned int lbl_806D24B8;
extern unsigned int lbl_806D24C4;
extern unsigned int lbl_806D24C8;

/* --- function index (1 fns, .text 0x8003A780..0x8003A9E8) ---
 * [  0] 0x8003A780 size:0x268   global SceneRender_DrawObjectWithLights
 */

/* --- forward decls --- */
asm void SceneRender_DrawObjectWithLights(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void __dt__11ScopedTimerFv();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_SceneRender_DrawObjectWithLights = { 0x104A0000, 0x000000B4, 0x004F0010, 0x00000000, 0x82000008, (void *)&__dt__11ScopedTimerFv };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SceneRender_DrawObjectWithLights = {
    (void *)&SceneRender_DrawObjectWithLights, 0x00000268, (void *)&extab_SceneRender_DrawObjectWithLights
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SceneRender_DrawObjectWithLights(void) { /* 0x8003A780 size:0x268 */
    nofralloc
    stwu r1, -0xa0(r1)
    mflr r0
    stw r0, 0xa4(r1)
    stfd f31, 0x90(r1)
    psq_st f31, 0x98(r1), 0, 0
    stw r31, 0x8c(r1)
    stw r30, 0x88(r1)
    li r0, 0x12
    mr r30, r3
    stw r0, 0xc(r1)
    bl OSGetTick
    lwz r4, 0x4(r30)
    stw r3, 0x8(r1)
    lwz r0, 0x0(r4)
    cmplwi r0, 0x0
    bne SceneRender_DrawObjectWithLights_L_8003A81C
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x8(r1)
    srwi r4, r5, 2
    stw r0, 0x80(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D24C8(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D24C4(r2)
    lwz r3, 0xc(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x84(r1)
    lfd f1, 0x80(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    b SceneRender_DrawObjectWithLights_L_8003A9C8
    SceneRender_DrawObjectWithLights_L_8003A81C:
    lwz r0, 0x8(r30)
    cmplwi r0, 0x0
    beq SceneRender_DrawObjectWithLights_L_8003A970
    lwz r3, 0x4(r4)
    addi r4, r30, 0x14
    bl fn_802C72AC
    lwz r3, 0x4(r30)
    lwz r4, 0x8(r30)
    lfs f1, lbl_806D24A8(r2)
    bl fn_802DBB84
    lwz r3, 0x4(r30)
    addi r4, r1, 0x10
    lwz r3, 0x4(r3)
    bl fn_802C7318
    lwz r3, 0x4(r30)
    addi r4, r1, 0x1c
    lwz r3, 0x4(r3)
    bl fn_802C79CC
    lwz r6, 0x8(r30)
    addi r3, r1, 0x28
    addi r4, r1, 0x10
    addi r5, r30, 0x14
    lhz r0, 0x8(r6)
    addi r6, r1, 0x1c
    clrlwi r8, r0, 30
    subfic r7, r8, 0x1
    subi r0, r8, 0x1
    or r0, r7, r0
    srwi r7, r0, 31
    bl fn_802DC2C0
    lwz r3, 0x4(r30)
    lfs f31, lbl_806D24AC(r2)
    lwz r31, 0x0(r3)
    b SceneRender_DrawObjectWithLights_L_8003A900
    SceneRender_DrawObjectWithLights_L_8003A8A4:
    lwz r3, 0x4(r31)
    addi r4, r1, 0x10
    addi r3, r3, 0x44
    bl fn_802D6948
    lfs f1, 0x14(r1)
    lfs f0, 0x18(r30)
    lfs f3, 0x10(r1)
    fsubs f4, f1, f0
    lfs f0, 0x14(r30)
    lfs f2, 0x18(r1)
    fsubs f3, f3, f0
    lfs f1, 0x1c(r30)
    fmuls f0, f4, f4
    fsubs f1, f2, f1
    fmadds f0, f3, f3, f0
    fmadds f0, f1, f1, f0
    fcmpo cr0, f0, f31
    bge SceneRender_DrawObjectWithLights_L_8003A8FC
    lfs f1, lbl_806D24B0(r2)
    addi r3, r1, 0x28
    addi r4, r1, 0x10
    bl fn_802DC550
    SceneRender_DrawObjectWithLights_L_8003A8FC:
    lwz r31, 0x0(r31)
    SceneRender_DrawObjectWithLights_L_8003A900:
    cmplwi r31, 0x0
    bne SceneRender_DrawObjectWithLights_L_8003A8A4
    addi r3, r1, 0x28
    bl fn_802DC4D4
    cmpwi r3, 0x0
    beq SceneRender_DrawObjectWithLights_L_8003A934
    lwz r3, 0x4(r30)
    lfs f1, 0x68(r1)
    lfs f2, 0x6c(r1)
    lfs f3, 0x70(r1)
    lfs f4, 0x74(r1)
    bl fn_802DC0F4
    b SceneRender_DrawObjectWithLights_L_8003A94C
    SceneRender_DrawObjectWithLights_L_8003A934:
    lfs f2, lbl_806D24B4(r2)
    lwz r3, 0x4(r30)
    fmr f3, f2
    lfs f1, lbl_806D24B0(r2)
    lfs f4, lbl_806D24B8(r2)
    bl fn_802DC0F4
    SceneRender_DrawObjectWithLights_L_8003A94C:
    li r3, 0x3
    bl fn_802D4748
    lwz r3, 0x4(r30)
    bl fn_802DB570
    lwz r3, 0x4(r30)
    bl fn_802DB740
    lwz r3, 0x4(r30)
    bl fn_802DB9EC
    bl fn_802D47E8
    SceneRender_DrawObjectWithLights_L_8003A970:
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x8(r1)
    srwi r4, r5, 2
    stw r0, 0x80(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D24C8(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D24C4(r2)
    lwz r3, 0xc(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x84(r1)
    lfd f1, 0x80(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    SceneRender_DrawObjectWithLights_L_8003A9C8:
    psq_l f31, 0x98(r1), 0, 0
    lwz r0, 0xa4(r1)
    lfd f31, 0x90(r1)
    lwz r31, 0x8c(r1)
    lwz r30, 0x88(r1)
    mtlr r0
    addi r1, r1, 0xa0
    blr
}


/* === extracted from auto_SceneRender_CmdA_8a9_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_802DBF20();

/* --- function index (1 fns, .text 0x8003A9E8..0x8003AA20) ---
 * [  0] 0x8003A9E8 size:0x38    global SceneRender_CmdA_8a9e8
 */

/* --- forward decls --- */
asm void SceneRender_CmdA_8a9e8(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SceneRender_CmdA_8a9e8[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SceneRender_CmdA_8a9e8 = {
    (void *)&SceneRender_CmdA_8a9e8, 0x00000038, (void *)extab_SceneRender_CmdA_8a9e8
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SceneRender_CmdA_8a9e8(void) { /* 0x8003A9E8 size:0x38 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmplwi r4, 0x0
    stw r0, 0x14(r1)
    beq SceneRender_CmdA_8a9e8_L_8003AA10
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne SceneRender_CmdA_8a9e8_L_8003AA0C
    b SceneRender_CmdA_8a9e8_L_8003AA10
    SceneRender_CmdA_8a9e8_L_8003AA0C:
    bl fn_802DBF20
    SceneRender_CmdA_8a9e8_L_8003AA10:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


/* === extracted from auto_SceneRender_CmdB_8aa_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_802DBE74();

/* --- function index (1 fns, .text 0x8003AA20..0x8003AA58) ---
 * [  0] 0x8003AA20 size:0x38    global SceneRender_CmdB_8aa20
 */

/* --- forward decls --- */
asm void SceneRender_CmdB_8aa20(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SceneRender_CmdB_8aa20[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SceneRender_CmdB_8aa20 = {
    (void *)&SceneRender_CmdB_8aa20, 0x00000038, (void *)extab_SceneRender_CmdB_8aa20
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SceneRender_CmdB_8aa20(void) { /* 0x8003AA20 size:0x38 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmplwi r4, 0x0
    stw r0, 0x14(r1)
    beq SceneRender_CmdB_8aa20_L_8003AA48
    lwz r3, 0x4(r3)
    cmplwi r3, 0x0
    bne SceneRender_CmdB_8aa20_L_8003AA44
    b SceneRender_CmdB_8aa20_L_8003AA48
    SceneRender_CmdB_8aa20_L_8003AA44:
    bl fn_802DBE74
    SceneRender_CmdB_8aa20_L_8003AA48:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


/* === extracted from auto_SceneRender_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_802DB468();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803F58FC[];

/* --- function index (1 fns, .text 0x8003AA58..0x8003AACC) ---
 * [  0] 0x8003AA58 size:0x74    global SceneRender_Dtor
 */

/* --- forward decls --- */
asm void SceneRender_Dtor(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SceneRender_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SceneRender_Dtor = {
    (void *)&SceneRender_Dtor, 0x00000074, (void *)extab_SceneRender_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SceneRender_Dtor(void) { /* 0x8003AA58 size:0x74 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr. r30, r3
    beq SceneRender_Dtor_L_8003AAB0
    lis r3, lbl_803F58FC@ha
    addi r0, r3, lbl_803F58FC@l
    stw r0, 0x0(r30)
    lwz r3, 0x4(r30)
    bl fn_802DB468
    li r0, 0x0
    mr r3, r30
    stw r0, 0x4(r30)
    li r4, 0x0
    bl dtor_8003A71C
    extsh. r0, r31
    ble SceneRender_Dtor_L_8003AAB0
    mr r3, r30
    bl MemoryManager_TimedFree
    SceneRender_Dtor_L_8003AAB0:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


