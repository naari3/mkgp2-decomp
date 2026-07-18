/* === extracted from auto_Jyugemu_ReverseFlag_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Archive_GetRootJObj();
extern void Atan2();
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void GetCourseScene3D();
extern void KartDriver_GetKartRootMtx();
extern void Object_DriveAnimMatrix();
extern void Vec3_Normalize();
extern void Vec3_Subtract();
extern void __assert();
extern void clNormal3D_Exec();
extern void fn_8027E9E8();
extern void fn_802D20AC();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806CEFC0;
extern unsigned int lbl_806D3078;
extern unsigned int lbl_806D307C;
extern unsigned int lbl_806D3080;
extern unsigned int lbl_806D3084;
extern unsigned int lbl_806D3088;
extern unsigned int lbl_806D309C;
extern unsigned int lbl_806D30A0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80311DFC[];

/* --- function index (1 fns, .text 0x80080C10..0x80080FAC) ---
 * [  0] 0x80080C10 size:0x39C   global Jyugemu_ReverseFlag_Tick
 */

/* --- forward decls --- */
asm void Jyugemu_ReverseFlag_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Jyugemu_ReverseFlag_Tick[8] = {
    0x18, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Jyugemu_ReverseFlag_Tick = {
    (void *)&Jyugemu_ReverseFlag_Tick, 0x0000039C, (void *)extab_Jyugemu_ReverseFlag_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Jyugemu_ReverseFlag_Tick(void) { /* 0x80080C10 size:0x39C */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    stw r0, 0x64(r1)
    stfd f31, 0x50(r1)
    psq_st f31, 0x58(r1), 0, 0
    stfd f30, 0x40(r1)
    psq_st f30, 0x48(r1), 0, 0
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    stw r29, 0x34(r1)
    mr r31, r3
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    bne Jyugemu_ReverseFlag_Tick_L_80080C50
    li r3, 0x0
    b Jyugemu_ReverseFlag_Tick_L_80080F80
    Jyugemu_ReverseFlag_Tick_L_80080C50:
    lwz r0, 0x4(r31)
    cmplwi r0, 0x0
    bne Jyugemu_ReverseFlag_Tick_L_80080C64
    li r3, 0x0
    b Jyugemu_ReverseFlag_Tick_L_80080F80
    Jyugemu_ReverseFlag_Tick_L_80080C64:
    lbz r0, lbl_806CEFC0(r13)
    cmplwi r0, 0x0
    bne Jyugemu_ReverseFlag_Tick_L_80080C78
    li r3, 0x0
    b Jyugemu_ReverseFlag_Tick_L_80080F80
    Jyugemu_ReverseFlag_Tick_L_80080C78:
    lbz r0, 0x8(r31)
    cmplwi r0, 0x1
    bne Jyugemu_ReverseFlag_Tick_L_80080CB0
    lfs f2, 0x10(r31)
    lfs f1, lbl_806D307C(r2)
    fcmpo cr0, f2, f1
    ble Jyugemu_ReverseFlag_Tick_L_80080CD8
    lfs f0, lbl_806D3080(r2)
    fsubs f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, 0x10(r31)
    bge Jyugemu_ReverseFlag_Tick_L_80080CD8
    stfs f1, 0x10(r31)
    b Jyugemu_ReverseFlag_Tick_L_80080CD8
    Jyugemu_ReverseFlag_Tick_L_80080CB0:
    lfs f2, 0x10(r31)
    lfs f1, lbl_806D3078(r2)
    fcmpo cr0, f2, f1
    bge Jyugemu_ReverseFlag_Tick_L_80080CD8
    lfs f0, lbl_806D3084(r2)
    fadds f0, f2, f0
    fcmpo cr0, f0, f1
    stfs f0, 0x10(r31)
    ble Jyugemu_ReverseFlag_Tick_L_80080CD8
    stfs f1, 0x10(r31)
    Jyugemu_ReverseFlag_Tick_L_80080CD8:
    lfs f1, 0x10(r31)
    bl fn_8027E9E8
    frsp f1, f1
    lfs f0, lbl_806D3088(r2)
    lwz r3, 0x4(r31)
    fmuls f30, f0, f1
    bl KartDriver_GetKartRootMtx
    mr r30, r3
    lwz r3, 0x0(r31)
    lfs f31, 0xc(r30)
    bl Archive_GetRootJObj
    mr. r29, r3
    bne Jyugemu_ReverseFlag_Tick_L_80080D1C
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x3b8
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Tick_L_80080D1C:
    stfs f31, 0x38(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne Jyugemu_ReverseFlag_Tick_L_80080D74
    cmplwi r29, 0x0
    beq Jyugemu_ReverseFlag_Tick_L_80080D74
    bne Jyugemu_ReverseFlag_Tick_L_80080D48
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x25d
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Tick_L_80080D48:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Jyugemu_ReverseFlag_Tick_L_80080D64
    rlwinm. r0, r4, 0, 25, 25
    beq Jyugemu_ReverseFlag_Tick_L_80080D64
    li r3, 0x1
    Jyugemu_ReverseFlag_Tick_L_80080D64:
    clrlwi. r0, r3, 24
    bne Jyugemu_ReverseFlag_Tick_L_80080D74
    mr r3, r29
    bl fn_802D20AC
    Jyugemu_ReverseFlag_Tick_L_80080D74:
    lfs f1, lbl_806D309C(r2)
    lfs f0, 0x1c(r30)
    lwz r3, 0x0(r31)
    fadds f0, f1, f0
    fadds f31, f0, f30
    bl Archive_GetRootJObj
    mr. r29, r3
    bne Jyugemu_ReverseFlag_Tick_L_80080DA4
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x3c6
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Tick_L_80080DA4:
    stfs f31, 0x3c(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne Jyugemu_ReverseFlag_Tick_L_80080DFC
    cmplwi r29, 0x0
    beq Jyugemu_ReverseFlag_Tick_L_80080DFC
    bne Jyugemu_ReverseFlag_Tick_L_80080DD0
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x25d
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Tick_L_80080DD0:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Jyugemu_ReverseFlag_Tick_L_80080DEC
    rlwinm. r0, r4, 0, 25, 25
    beq Jyugemu_ReverseFlag_Tick_L_80080DEC
    li r3, 0x1
    Jyugemu_ReverseFlag_Tick_L_80080DEC:
    clrlwi. r0, r3, 24
    bne Jyugemu_ReverseFlag_Tick_L_80080DFC
    mr r3, r29
    bl fn_802D20AC
    Jyugemu_ReverseFlag_Tick_L_80080DFC:
    lfs f31, 0x2c(r30)
    lwz r3, 0x0(r31)
    bl Archive_GetRootJObj
    mr. r29, r3
    bne Jyugemu_ReverseFlag_Tick_L_80080E20
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x3d4
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Tick_L_80080E20:
    stfs f31, 0x40(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne Jyugemu_ReverseFlag_Tick_L_80080E78
    cmplwi r29, 0x0
    beq Jyugemu_ReverseFlag_Tick_L_80080E78
    bne Jyugemu_ReverseFlag_Tick_L_80080E4C
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x25d
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Tick_L_80080E4C:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Jyugemu_ReverseFlag_Tick_L_80080E68
    rlwinm. r0, r4, 0, 25, 25
    beq Jyugemu_ReverseFlag_Tick_L_80080E68
    li r3, 0x1
    Jyugemu_ReverseFlag_Tick_L_80080E68:
    clrlwi. r0, r3, 24
    bne Jyugemu_ReverseFlag_Tick_L_80080E78
    mr r3, r29
    bl fn_802D20AC
    Jyugemu_ReverseFlag_Tick_L_80080E78:
    bl GetCourseScene3D
    mr. r29, r3
    beq Jyugemu_ReverseFlag_Tick_L_80080F6C
    addi r4, r1, 0x14
    bl CObj_LoadProjMatrix
    mr r3, r29
    addi r4, r1, 0x20
    bl CObj_ApplyScissor
    addi r3, r1, 0x20
    addi r4, r1, 0x14
    addi r5, r1, 0x8
    bl Vec3_Subtract
    lfs f0, lbl_806D307C(r2)
    addi r3, r1, 0x8
    mr r4, r3
    stfs f0, 0xc(r1)
    bl Vec3_Normalize
    lfs f1, 0x8(r1)
    lfs f2, 0x10(r1)
    bl Atan2
    frsp f1, f1
    lfs f0, lbl_806D30A0(r2)
    lwz r3, 0x0(r31)
    fadds f31, f0, f1
    bl Archive_GetRootJObj
    mr. r29, r3
    bne Jyugemu_ReverseFlag_Tick_L_80080EF4
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x2b8
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Tick_L_80080EF4:
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 14, 14
    beq Jyugemu_ReverseFlag_Tick_L_80080F14
    lis r4, lbl_80311DFC@ha
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    addi r5, r4, lbl_80311DFC@l
    li r4, 0x2b9
    bl __assert
    Jyugemu_ReverseFlag_Tick_L_80080F14:
    stfs f31, 0x20(r29)
    lwz r0, 0x14(r29)
    rlwinm. r0, r0, 0, 6, 6
    bne Jyugemu_ReverseFlag_Tick_L_80080F6C
    cmplwi r29, 0x0
    beq Jyugemu_ReverseFlag_Tick_L_80080F6C
    bne Jyugemu_ReverseFlag_Tick_L_80080F40
    addi r3, r2, -0x71D4  /* lbl_806D308C */
    li r4, 0x25d
    addi r5, r2, -0x71CC  /* lbl_806D3094 */
    bl __assert
    Jyugemu_ReverseFlag_Tick_L_80080F40:
    lwz r4, 0x14(r29)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne Jyugemu_ReverseFlag_Tick_L_80080F5C
    rlwinm. r0, r4, 0, 25, 25
    beq Jyugemu_ReverseFlag_Tick_L_80080F5C
    li r3, 0x1
    Jyugemu_ReverseFlag_Tick_L_80080F5C:
    clrlwi. r0, r3, 24
    bne Jyugemu_ReverseFlag_Tick_L_80080F6C
    mr r3, r29
    bl fn_802D20AC
    Jyugemu_ReverseFlag_Tick_L_80080F6C:
    lwz r3, 0x0(r31)
    bl clNormal3D_Exec
    lwz r3, 0x0(r31)
    bl Object_DriveAnimMatrix
    li r3, 0x1
    Jyugemu_ReverseFlag_Tick_L_80080F80:
    psq_l f31, 0x58(r1), 0, 0
    lfd f31, 0x50(r1)
    psq_l f30, 0x48(r1), 0, 0
    lfd f30, 0x40(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    lwz r0, 0x64(r1)
    lwz r29, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

