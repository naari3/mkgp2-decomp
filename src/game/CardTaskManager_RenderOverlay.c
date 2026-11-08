
/* sdata symbols referenced from asm */
extern unsigned char lbl_806D32CC[5];
extern unsigned char lbl_806D32DC[3];
extern unsigned char lbl_806D32E0[6];
extern unsigned char lbl_806D32EC[3];
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
extern unsigned char lbl_806D3290[], lbl_806D3294[], lbl_806D3298[], lbl_806D32A0[], lbl_806D32A4[];
/* owned pool .rodata 0x80312850..0x80312DEC (tools/data2c.py) */
#pragma force_active on
const void *const lbl_80312850[9] = {
    (void *)0x43484543,
    (void *)0x4B494E47,
    (void *)0x2E2E2E00,
    (void *)&lbl_806D3290,
    (void *)&lbl_80312850,
    (void *)&lbl_806D3294,
    (void *)&lbl_806D3298,
    (void *)&lbl_806D3290,
    (void *)&lbl_806D3290
};
const unsigned int lbl_80312874[4] = { 0x975C917A, 0x82B582C8, 0x82A297E1, 0x8A4F0000 };
const char lbl_80312884[] = "Program error";
const unsigned int lbl_80312894[9] = { 0x836E8393, 0x8368838B, 0x82C98EE8, 0x82F09047, 0x82EA82C8, 0x82A282C5, 0x82AD82BE, 0x82B382A2, 0x00000000 };
const char lbl_803128B8[] = "Do not touch wheel";
const unsigned int lbl_803128CC[6] = { 0x8C5788F5, 0x82F08CC4, 0x82F182C5, 0x82AD82BE, 0x82B382A2, 0x00000000 };
const char lbl_803128E4[] = "Please call an attendant";
const unsigned int lbl_80312900[7] = { 0x836E8393, 0x8368838B, 0x82C988D9, 0x8FED82AA, 0x82A082E8, 0x82DC82B7, 0x00000000 };
const char lbl_8031291C[] = "Wheel error";
const char lbl_80312928[] = "JVS I/O ERROR";
const unsigned int lbl_80312938[8] = { 0x83418343, 0x83658380, 0x837B835E, 0x839382C9, 0x88D98FED, 0x82AA82A0, 0x82E882DC, 0x82B70000 };
const char lbl_80312958[] = "Item button Error";
const unsigned int lbl_8031296C[10] = { 0x91CE90ED, 0x834C8383, 0x8393835A, 0x838B837B, 0x835E8393, 0x82C988D9, 0x8FED82AA, 0x82A082E8, 0x82DC82B7, 0x00000000 };
const char lbl_80312994[] = "Versus Cancel button Error";
const unsigned int lbl_803129B0[7] = { 0x834A815B, 0x83685281, 0x5E5782CD, 0x8E679770, 0x82C582AB, 0x82DC82B9, 0x82F10000 };
const char lbl_803129CC[] = "Card R/W is out of order";
const unsigned int lbl_803129E8[15] = { 0x83418343, 0x83658380, 0x837B835E, 0x839382DC, 0x82BD82CD, 0x91CE90ED, 0x834C8383, 0x8393835A, 0x838B837B, 0x835E8393, 0x82F0899F, 0x82B582C4, 0x82AD82BE, 0x82B382A2, 0x00000000 };
const char lbl_80312A24[] = "Press Item button or Versus Cancel button";
const unsigned int lbl_80312A50[6] = { 0x834A815B, 0x836882AA, 0x95A582A2, 0x8F6F82B3, 0x82EA82DC, 0x82B70000 };
const char lbl_80312A68[] = "Card will be ejected";
const unsigned int lbl_80312A80[6] = { 0x834A815B, 0x836882F0, 0x82A88EE6, 0x82E882AD, 0x82BE82B3, 0x82A20000 };
const char lbl_80312A98[] = "Take card";
const unsigned int lbl_80312AA4[9] = { 0x834A815B, 0x83685281, 0x5E5782CC, 0x834E838A, 0x815B836A, 0x8393834F, 0x8E9E8AFA, 0x82C582B7, 0x00000000 };
const char lbl_80312AC8[] = "Please clean the card R/W";
const unsigned int lbl_80312AE4[11] = { 0x834A815B, 0x83685281, 0x5E5782CC, 0x834E838A, 0x815B836A, 0x8393834F, 0x82F08EC0, 0x8D7382B5, 0x82C482AD, 0x82BE82B3, 0x82A20000 };
const unsigned int lbl_80312B10[8] = { 0x8B4E93AE, 0x8CE382C9, 0x834A815B, 0x8368834E, 0x838A815B, 0x836A8393, 0x834F82F0, 0x00000000 };
const char lbl_80312B30[] = "          Skip";
const unsigned int lbl_80312B40[3] = { 0x82B582C4, 0x89BA82B3, 0x82A20000 };
const char lbl_80312B4C[] = "when activating";
const unsigned int lbl_80312B5C[6] = { 0x834A815B, 0x8368834E, 0x838A815B, 0x836A8393, 0x834F82F0, 0x00000000 };
const char lbl_80312B74[] = "Card R/W will be cleaned";
const unsigned int lbl_80312B90[3] = { 0x8EC08D73, 0x82B582DC, 0x82B70000 };
const unsigned int lbl_80312B9C[3] = { 0x8358834C, 0x83628376, 0x00000000 };
const void *const lbl_80312BA8[26] = {
    (void *)&lbl_803128CC,
    (void *)&lbl_803128E4,
    (void *)&lbl_803129B0,
    (void *)&lbl_803129CC,
    (void *)&lbl_803129E8,
    (void *)&lbl_80312A24,
    (void *)&lbl_80312A50,
    (void *)&lbl_80312A68,
    (void *)&lbl_80312A80,
    (void *)&lbl_80312A98,
    (void *)&lbl_80312AA4,
    (void *)&lbl_80312AC8,
    (void *)&lbl_80312AE4,
    (void *)&lbl_806D32A0,
    (void *)&lbl_80312B10,
    (void *)&lbl_80312B30,
    (void *)&lbl_80312B40,
    (void *)&lbl_80312AC8,
    (void *)&lbl_806D32A0,
    (void *)&lbl_80312B4C,
    (void *)&lbl_80312B5C,
    (void *)&lbl_80312B74,
    (void *)&lbl_80312B90,
    (void *)&lbl_806D32A0,
    (void *)&lbl_80312B9C,
    (void *)&lbl_806D32A4
};
const unsigned int lbl_80312C10[6] = { 0x834A8381, 0x838982C9, 0x88D98FED, 0x82AA82A0, 0x82E882DC, 0x82B70000 };
const char lbl_80312C28[] = "CAMERA ERROR";
const unsigned int lbl_80312C38[6] = { 0x834A8381, 0x838982CD, 0x8E679770, 0x82C582AB, 0x82DC82B9, 0x82F10000 };
const char lbl_80312C50[] = "CAMERA DISABLED";
const unsigned int lbl_80312C60[14] = { 0x83418343, 0x83658380, 0x837B835E, 0x839382DC, 0x82BD82CD, 0x91CE90ED, 0x834C8383, 0x8393835A, 0x838B837B, 0x835E8393, 0x82F0899F, 0x82B582C4, 0x89BA82B3, 0x82A20000 };
const char lbl_80312C98[] = "Press Item button or Versus Cancel Button";
const void *const lbl_80312CC4[74] = {
    (void *)0x43540000,
    (void *)0x43800000,
    (void *)&lbl_803128CC,
    (void *)0x1,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x42EE0000,
    (void *)0x43700000,
    (void *)&lbl_803128E4,
    (void *)0x1,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43700000,
    (void *)0x43960000,
    (void *)&lbl_80312C10,
    (void *)0x0,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43820000,
    (void *)0x43960000,
    (void *)&lbl_80312C28,
    (void *)0x0,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43480000,
    (void *)0x43800000,
    (void *)&lbl_80312C38,
    (void *)0x1,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43480000,
    (void *)0x43800000,
    (void *)&lbl_80312C50,
    (void *)0x1,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x42C80000,
    (void *)0x43B40000,
    (void *)&lbl_80312C60,
    (void *)0x0,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x43040000,
    (void *)0x43B40000,
    (void *)&lbl_80312C98,
    (void *)0x0,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0xFF,
    (void *)0x44657669,
    (void *)0x63652043,
    (void *)0x6865636B,
    (void *)0x0,
    (void *)0x4D4B3231,
    (void *)0x30302D31,
    (void *)0x2D4E412D,
    (void *)0x4D505230,
    (void *)0x2D413336,
    (void *)0x0
};
#pragma force_active reset
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
    la r5, lbl_806D32CC(r2)  /* lbl_806D32CC */
    lfs f1, lbl_806D32D4(r2)
    li r3, 0x1
    srawi r0, r0, 4
    lfs f2, lbl_806D32D8(r2)
    clrlwi r0, r0, 30
    la r4, lbl_806D32DC(r2)  /* lbl_806D32DC */
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
    la r22, lbl_806D32E0(r2)  /* lbl_806D32E0 */
    CardTaskManager_RenderOverlay_L_80089D7C:
    xoris r0, r28, 0x8000
    stw r24, 0x8(r1)
    lfs f1, lbl_806D32E8(r2)
    li r3, 0x1
    stw r0, 0xc(r1)
    la r4, lbl_806D32EC(r2)  /* lbl_806D32EC */
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
    la r4, lbl_806D32EC(r2)  /* lbl_806D32EC */
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

