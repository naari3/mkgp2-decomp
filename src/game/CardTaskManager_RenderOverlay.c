/* === extracted from auto_CardTaskManager_Rend_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void TexMgr_DrawText_Format_Variant2();
extern void fn_8011F994();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D32D4;
extern unsigned int lbl_806D32D8;
extern unsigned int lbl_806D32E8;
extern unsigned int lbl_806D32F0;
extern unsigned int lbl_806D32F4;
extern unsigned int lbl_806D32F8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80312850[];
extern unsigned int lbl_803FE7E8[];

/* --- function index (1 fns, .text 0x80089C58..0x80089E6C) ---
 * [  0] 0x80089C58 size:0x214   global CardTaskManager_RenderOverlay
 */

/* --- forward decls --- */
asm void CardTaskManager_RenderOverlay(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_CardTaskManager_RenderOverlay[8] = {
    0x50, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_CardTaskManager_RenderOverlay = {
    (void *)&CardTaskManager_RenderOverlay, 0x00000214, (void *)extab_CardTaskManager_RenderOverlay
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void CardTaskManager_RenderOverlay(void) { /* 0x80089C58 size:0x214 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stmw r22, 0x18(r1)
    mr r25, r3
    lis r3, lbl_80312850@ha
    lwz r4, 0x8(r25)
    addi r30, r3, lbl_80312850@l
    lwz r0, 0x4(r25)
    cmpw r4, r0
    bge CardTaskManager_RenderOverlay_L_80089D20
    lwz r3, 0x0(r25)
    slwi r0, r4, 3
    lwzx r23, r3, r0
    cmplwi r23, 0x0
    beq CardTaskManager_RenderOverlay_L_80089D20
    lwz r0, 0xc(r25)
    addi r5, r2, -0x6F94  /* lbl_806D32CC */
    lfs f1, lbl_806D32D4(r2)
    li r3, 0x1
    srawi r0, r0, 4
    lfs f2, lbl_806D32D8(r2)
    clrlwi r0, r0, 30
    addi r4, r2, -0x6F84  /* lbl_806D32DC */
    lbzx r5, r5, r0
    extsb r5, r5
    creqv 6, 6, 6
    bl TexMgr_DrawText_Format_Variant2
    mr r3, r23
    lwz r12, 0x0(r23)
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne CardTaskManager_RenderOverlay_L_80089D20
    mr r3, r23
    lwz r12, 0x0(r23)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    li r23, 0x0
    CardTaskManager_RenderOverlay_L_80089D08:
    subfic r3, r23, 0x7
    bl fn_8011F994
    addi r23, r23, 0x1
    cmpwi r23, 0x8
    blt CardTaskManager_RenderOverlay_L_80089D08
    b CardTaskManager_RenderOverlay_L_80089E50
    CardTaskManager_RenderOverlay_L_80089D20:
    lis r3, lbl_803FE7E8@ha
    lfd f31, lbl_806D32F8(r2)
    addi r31, r3, lbl_803FE7E8@l
    addi r23, r30, 0xc
    li r27, 0x0
    li r29, 0x0
    li r28, 0x3c
    lis r24, 0x4330
    b CardTaskManager_RenderOverlay_L_80089E44
    CardTaskManager_RenderOverlay_L_80089D44:
    lwz r3, 0x0(r25)
    lwz r0, 0x8(r25)
    add r3, r3, r29
    lwz r26, 0x0(r3)
    cmpw r27, r0
    lwz r3, 0x4(r3)
    lwz r0, 0x4(r26)
    slwi r3, r3, 3
    add r3, r31, r3
    slwi r0, r0, 2
    lwz r5, 0x4(r3)
    lwzx r22, r23, r0
    ble CardTaskManager_RenderOverlay_L_80089D7C
    addi r22, r2, -0x6F80  /* lbl_806D32E0 */
    CardTaskManager_RenderOverlay_L_80089D7C:
    xoris r0, r28, 0x8000
    stw r24, 0x8(r1)
    lfs f1, lbl_806D32E8(r2)
    li r3, 0x1
    stw r0, 0xc(r1)
    addi r4, r2, -0x6F74  /* lbl_806D32EC */
    lfd f0, 0x8(r1)
    fsubs f2, f0, f31
    creqv 6, 6, 6
    bl TexMgr_DrawText_Format_Variant2
    xoris r0, r28, 0x8000
    stw r24, 0x10(r1)
    lfs f1, lbl_806D32F0(r2)
    mr r5, r22
    stw r0, 0x14(r1)
    li r3, 0x1
    addi r4, r2, -0x6F74  /* lbl_806D32EC */
    lfd f0, 0x10(r1)
    fsubs f2, f0, f31
    creqv 6, 6, 6
    bl TexMgr_DrawText_Format_Variant2
    lfs f1, lbl_806D32F4(r2)
    addi r4, r30, 0x574
    li r3, 0x1
    fmr f2, f1
    creqv 6, 6, 6
    bl TexMgr_DrawText_Format_Variant2
    lfs f1, lbl_806D32F4(r2)
    addi r4, r30, 0x584
    lfs f2, lbl_806D32D8(r2)
    li r3, 0x1
    creqv 6, 6, 6
    bl TexMgr_DrawText_Format_Variant2
    lwz r0, 0x8(r25)
    cmpw r27, r0
    bne CardTaskManager_RenderOverlay_L_80089E20
    mr r3, r26
    lwz r12, 0x0(r26)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    CardTaskManager_RenderOverlay_L_80089E20:
    li r22, 0x0
    CardTaskManager_RenderOverlay_L_80089E24:
    mr r3, r22
    bl fn_8011F994
    addi r22, r22, 0x1
    cmpwi r22, 0x8
    blt CardTaskManager_RenderOverlay_L_80089E24
    addi r29, r29, 0x8
    addi r28, r28, 0x26
    addi r27, r27, 0x1
    CardTaskManager_RenderOverlay_L_80089E44:
    lwz r0, 0x4(r25)
    cmpw r27, r0
    blt CardTaskManager_RenderOverlay_L_80089D44
    CardTaskManager_RenderOverlay_L_80089E50:
    psq_l f31, 0x48(r1), 0, 0
    lfd f31, 0x40(r1)
    lmw r22, 0x18(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

