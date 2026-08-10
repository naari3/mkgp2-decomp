/* === extracted from auto_SoundMgr_Play_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int ClSound_Initialized;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80379554[];
extern unsigned int lbl_80677F40[];
extern unsigned int lbl_80678378[];

/* --- function index (1 fns, .text 0x80192884..0x80192F04) ---
 * [  0] 0x80192884 size:0x680   global SoundMgr_Play
 */

/* --- forward decls --- */
asm void SoundMgr_Play(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_SoundMgr_Play[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SoundMgr_Play = {
    (void *)&SoundMgr_Play, 0x00000680, (void *)extab_SoundMgr_Play
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void SoundMgr_Play(void) { /* 0x80192884 size:0x680 */
    nofralloc
    stwu r1, -0x30(r1)
    stw r31, 0x2c(r1)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    stw r28, 0x20(r1)
    lbz r0, ClSound_Initialized(r13)
    cmplwi r0, 0x0
    bne SoundMgr_Play_L_801928AC
    li r3, 0x0
    b SoundMgr_Play_L_80192EEC
    SoundMgr_Play_L_801928AC:
    rlwinm r4, r3, 0, 5, 0
    rlwinm r8, r3, 0, 1, 4
    cmplwi r4, 0x1ea
    blt SoundMgr_Play_L_801928C4
    li r3, 0x0
    b SoundMgr_Play_L_80192EEC
    SoundMgr_Play_L_801928C4:
    lis r5, lbl_80678378@ha
    li r0, 0x8
    addi r6, r5, lbl_80678378@l
    li r5, 0x0
    mr r7, r6
    mtctr r0
    SoundMgr_Play_L_801928DC:
    lwz r0, 0x4(r7)
    cmplw r3, r0
    bne SoundMgr_Play_L_801928F8
    lwz r0, 0x0(r7)
    rlwinm. r0, r0, 0, 29, 30
    bne SoundMgr_Play_L_801928F8
    b SoundMgr_Play_L_80192974
    SoundMgr_Play_L_801928F8:
    lwz r0, 0x20(r7)
    addi r5, r5, 0x1
    addi r7, r7, 0x1c
    cmplw r3, r0
    bne SoundMgr_Play_L_8019291C
    lwz r0, 0x0(r7)
    rlwinm. r0, r0, 0, 29, 30
    bne SoundMgr_Play_L_8019291C
    b SoundMgr_Play_L_80192974
    SoundMgr_Play_L_8019291C:
    lwz r0, 0x20(r7)
    addi r5, r5, 0x1
    addi r7, r7, 0x1c
    cmplw r3, r0
    bne SoundMgr_Play_L_80192940
    lwz r0, 0x0(r7)
    rlwinm. r0, r0, 0, 29, 30
    bne SoundMgr_Play_L_80192940
    b SoundMgr_Play_L_80192974
    SoundMgr_Play_L_80192940:
    lwz r0, 0x20(r7)
    addi r5, r5, 0x1
    addi r7, r7, 0x1c
    cmplw r3, r0
    bne SoundMgr_Play_L_80192964
    lwz r0, 0x0(r7)
    rlwinm. r0, r0, 0, 29, 30
    bne SoundMgr_Play_L_80192964
    b SoundMgr_Play_L_80192974
    SoundMgr_Play_L_80192964:
    addi r7, r7, 0x1c
    addi r5, r5, 0x1
    bdnz SoundMgr_Play_L_801928DC
    li r5, -0x1
    SoundMgr_Play_L_80192974:
    cmpwi r5, 0x0
    blt SoundMgr_Play_L_80192A84
    mulli r0, r5, 0x1c
    lis r5, lbl_80678378@ha
    addi r5, r5, lbl_80678378@l
    add r9, r5, r0
    lbz r5, 0x19(r9)
    cmplwi r5, 0x0
    beq SoundMgr_Play_L_801929A0
    li r3, 0x1
    b SoundMgr_Play_L_80192EEC
    SoundMgr_Play_L_801929A0:
    lis r7, lbl_80677F40@ha
    li r5, 0x25
    addi r10, r7, lbl_80677F40@l
    lwz r7, 0x4(r9)
    li r12, 0x0
    mtctr r5
    SoundMgr_Play_L_801929B8:
    lwz r9, 0x0(r10)
    addis r5, r9, 0x1
    cmplwi r5, 0xffff
    beq SoundMgr_Play_L_80192A6C
    cmplw r7, r9
    bne SoundMgr_Play_L_80192A60
    mulli r9, r12, 0xc
    lis r5, lbl_80677F40@ha
    li r7, 0x3
    addi r11, r5, lbl_80677F40@l
    add r30, r11, r9
    li r5, 0x0
    stw r7, 0x4(r30)
    stw r5, 0x8(r30)
    mtctr r12
    cmpwi r12, 0x0
    ble SoundMgr_Play_L_80192A6C
    SoundMgr_Play_L_801929FC:
    lwz r5, -0x8(r30)
    cmpwi r5, 0x3
    beq SoundMgr_Play_L_80192A6C
    subi r5, r12, 0x1
    lwz r10, 0x0(r30)
    mulli r5, r5, 0xc
    lwz r9, 0x4(r30)
    lwz r7, 0x8(r30)
    subi r12, r12, 0x1
    stw r10, 0x14(r1)
    add r31, r11, r5
    lwz r5, 0x0(r31)
    stw r9, 0x18(r1)
    stw r5, 0x0(r30)
    lwz r5, 0x4(r31)
    stw r7, 0x1c(r1)
    stw r5, 0x4(r30)
    lwz r5, 0x8(r31)
    stw r5, 0x8(r30)
    subi r30, r30, 0xc
    stw r10, 0x0(r31)
    stw r9, 0x4(r31)
    stw r7, 0x8(r31)
    bdnz SoundMgr_Play_L_801929FC
    b SoundMgr_Play_L_80192A6C
    SoundMgr_Play_L_80192A60:
    addi r10, r10, 0xc
    addi r12, r12, 0x1
    bdnz SoundMgr_Play_L_801929B8
    SoundMgr_Play_L_80192A6C:
    lis r5, lbl_80678378@ha
    addi r7, r5, lbl_80678378@l
    lwzx r5, r7, r0
    rlwinm r5, r5, 0, 31, 28
    ori r5, r5, 0x4
    stwx r5, r7, r0
    SoundMgr_Play_L_80192A84:
    mulli r0, r4, 0x1c
    lis r4, lbl_80379554@ha
    addi r4, r4, lbl_80379554@l
    add r5, r4, r0
    lbz r4, 0x5(r5)
    cmplwi r4, 0x2
    bne SoundMgr_Play_L_80192BCC
    mr r4, r6
    addi r5, r5, 0x4
    li r7, 0x0
    SoundMgr_Play_L_80192AAC:
    lwz r11, 0x4(r4)
    addis r9, r11, 0x1
    cmplwi r9, 0xffff
    beq SoundMgr_Play_L_80192BBC
    lbz r10, 0x8(r4)
    lbz r9, 0x0(r5)
    cmplw r10, r9
    bne SoundMgr_Play_L_80192BBC
    rlwinm r9, r11, 0, 1, 4
    cmplw r8, r9
    bne SoundMgr_Play_L_80192BBC
    lwz r9, 0x0(r4)
    rlwinm. r9, r9, 0, 29, 30
    bne SoundMgr_Play_L_80192BBC
    lis r10, lbl_80677F40@ha
    li r9, 0x25
    addi r10, r10, lbl_80677F40@l
    li r30, 0x0
    mtctr r9
    SoundMgr_Play_L_80192AF8:
    lwz r12, 0x0(r10)
    addis r9, r12, 0x1
    cmplwi r9, 0xffff
    beq SoundMgr_Play_L_80192BAC
    cmplw r11, r12
    bne SoundMgr_Play_L_80192BA0
    mulli r10, r30, 0xc
    lis r9, lbl_80677F40@ha
    li r11, 0x3
    addi r31, r9, lbl_80677F40@l
    add r29, r31, r10
    li r9, 0x0
    stw r11, 0x4(r29)
    stw r9, 0x8(r29)
    mtctr r30
    cmpwi r30, 0x0
    ble SoundMgr_Play_L_80192BAC
    SoundMgr_Play_L_80192B3C:
    lwz r9, -0x8(r29)
    cmpwi r9, 0x3
    beq SoundMgr_Play_L_80192BAC
    subi r9, r30, 0x1
    lwz r12, 0x0(r29)
    mulli r9, r9, 0xc
    lwz r11, 0x4(r29)
    lwz r10, 0x8(r29)
    subi r30, r30, 0x1
    stw r12, 0x8(r1)
    add r28, r31, r9
    lwz r9, 0x0(r28)
    stw r11, 0xc(r1)
    stw r9, 0x0(r29)
    lwz r9, 0x4(r28)
    stw r10, 0x10(r1)
    stw r9, 0x4(r29)
    lwz r9, 0x8(r28)
    stw r9, 0x8(r29)
    subi r29, r29, 0xc
    stw r12, 0x0(r28)
    stw r11, 0x4(r28)
    stw r10, 0x8(r28)
    bdnz SoundMgr_Play_L_80192B3C
    b SoundMgr_Play_L_80192BAC
    SoundMgr_Play_L_80192BA0:
    addi r10, r10, 0xc
    addi r30, r30, 0x1
    bdnz SoundMgr_Play_L_80192AF8
    SoundMgr_Play_L_80192BAC:
    lwz r9, 0x0(r4)
    rlwinm r9, r9, 0, 31, 28
    ori r9, r9, 0x4
    stw r9, 0x0(r4)
    SoundMgr_Play_L_80192BBC:
    addi r7, r7, 0x1
    addi r4, r4, 0x1c
    cmpwi r7, 0x20
    blt SoundMgr_Play_L_80192AAC
    SoundMgr_Play_L_80192BCC:
    li r4, 0x4
    li r7, 0x0
    mtctr r4
    SoundMgr_Play_L_80192BD8:
    lwz r4, 0x0(r6)
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    lwz r4, 0x1c(r6)
    addi r7, r7, 0x1
    addi r6, r6, 0x1c
    cmplwi r4, 0x0
    beq SoundMgr_Play_L_80192C7C
    addi r6, r6, 0x1c
    addi r7, r7, 0x1
    bdnz SoundMgr_Play_L_80192BD8
    SoundMgr_Play_L_80192C7C:
    cmpwi r7, 0x20
    blt SoundMgr_Play_L_80192C8C
    li r3, 0x0
    b SoundMgr_Play_L_80192EEC
    SoundMgr_Play_L_80192C8C:
    lis r5, lbl_80379554@ha
    lis r4, lbl_80678378@ha
    addi r6, r5, lbl_80379554@l
    li r8, -0x1
    add r12, r6, r0
    addi r11, r4, lbl_80678378@l
    lwz r0, 0x18(r12)
    mulli r28, r7, 0x1c
    li r5, 0x200
    lbz r10, 0x4(r12)
    extrwi r0, r0, 1, 30
    lbz r9, 0x15(r12)
    neg r0, r0
    andc r0, r5, r0
    add r29, r11, r28
    ori r0, r0, 0x11
    li r7, 0x80
    stwx r0, r11, r28
    li r6, 0x7f
    li r5, 0x40
    lhz r4, 0x12(r12)
    stw r3, 0x4(r29)
    li r3, 0x2000
    lbz r0, 0x14(r12)
    stb r10, 0x8(r29)
    stb r9, 0x18(r29)
    stw r8, 0xc(r29)
    stb r7, 0x10(r29)
    stb r6, 0x11(r29)
    stb r5, 0x12(r29)
    stb r5, 0x13(r29)
    sth r4, 0x14(r29)
    sth r3, 0x16(r29)
    stb r0, 0x19(r29)
    lhz r0, 0x14(r29)
    addi r29, r29, 0x4
    cmplwi r0, 0x2000
    beq SoundMgr_Play_L_80192D30
    lwzx r0, r11, r28
    ori r0, r0, 0x80
    stwx r0, r11, r28
    SoundMgr_Play_L_80192D30:
    lis r3, lbl_80677F40@ha
    li r0, 0x25
    addi r3, r3, lbl_80677F40@l
    lwz r8, 0x0(r29)
    li r9, 0x0
    mr r4, r3
    mtctr r0
    SoundMgr_Play_L_80192D4C:
    lwz r5, 0x0(r4)
    addis r0, r5, 0x1
    cmplwi r0, 0xffff
    bne SoundMgr_Play_L_80192D64
    li r9, -0x1
    b SoundMgr_Play_L_80192D80
    SoundMgr_Play_L_80192D64:
    cmplw r8, r5
    bne SoundMgr_Play_L_80192D70
    b SoundMgr_Play_L_80192D80
    SoundMgr_Play_L_80192D70:
    addi r4, r4, 0xc
    addi r9, r9, 0x1
    bdnz SoundMgr_Play_L_80192D4C
    li r9, -0x1
    SoundMgr_Play_L_80192D80:
    cmpwi r9, 0x0
    blt SoundMgr_Play_L_80192E98
    mulli r0, r9, 0xc
    lis r4, lbl_80677F40@ha
    cmpwi r9, 0x24
    addi r7, r4, lbl_80677F40@l
    subfic r4, r9, 0x24
    add r11, r7, r0
    bge SoundMgr_Play_L_80192E88
    srwi. r0, r4, 2
    mtctr r0
    beq SoundMgr_Play_L_80192E54
    SoundMgr_Play_L_80192DB0:
    addi r6, r9, 0x1
    mulli r5, r6, 0xc
    addi r6, r9, 0x2
    add r10, r7, r5
    lwz r0, 0x0(r10)
    mulli r5, r6, 0xc
    addi r6, r9, 0x3
    stw r0, 0x0(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x4(r11)
    lwz r0, 0x8(r10)
    add r10, r7, r5
    mulli r5, r6, 0xc
    addi r6, r9, 0x4
    stw r0, 0x8(r11)
    addi r9, r9, 0x4
    lwz r0, 0x0(r10)
    stw r0, 0xc(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x10(r11)
    lwz r0, 0x8(r10)
    add r10, r7, r5
    mulli r5, r6, 0xc
    stw r0, 0x14(r11)
    lwz r0, 0x0(r10)
    stw r0, 0x18(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x1c(r11)
    lwz r0, 0x8(r10)
    add r10, r7, r5
    stw r0, 0x20(r11)
    lwz r0, 0x0(r10)
    stw r0, 0x24(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x28(r11)
    lwz r0, 0x8(r10)
    stw r0, 0x2c(r11)
    addi r11, r11, 0x30
    bdnz SoundMgr_Play_L_80192DB0
    andi. r4, r4, 0x3
    beq SoundMgr_Play_L_80192E88
    SoundMgr_Play_L_80192E54:
    mtctr r4
    SoundMgr_Play_L_80192E58:
    addi r6, r9, 0x1
    addi r9, r9, 0x1
    mulli r5, r6, 0xc
    add r10, r7, r5
    lwz r0, 0x0(r10)
    stw r0, 0x0(r11)
    lwz r0, 0x4(r10)
    stw r0, 0x4(r11)
    lwz r0, 0x8(r10)
    stw r0, 0x8(r11)
    addi r11, r11, 0xc
    bdnz SoundMgr_Play_L_80192E58
    SoundMgr_Play_L_80192E88:
    lis r4, lbl_80677F40@ha
    li r0, -0x1
    addi r4, r4, lbl_80677F40@l
    stw r0, 0x1b0(r4)
    SoundMgr_Play_L_80192E98:
    li r0, 0x25
    li r5, 0x0
    mtctr r0
    SoundMgr_Play_L_80192EA4:
    lwz r4, 0x0(r3)
    addis r0, r4, 0x1
    cmplwi r0, 0xffff
    bne SoundMgr_Play_L_80192EDC
    mulli r0, r5, 0xc
    lis r3, lbl_80677F40@ha
    li r4, 0x1
    addi r3, r3, lbl_80677F40@l
    stwx r8, r3, r0
    add r3, r3, r0
    li r0, 0xa
    stw r4, 0x4(r3)
    stw r0, 0x8(r3)
    b SoundMgr_Play_L_80192EE8
    SoundMgr_Play_L_80192EDC:
    addi r3, r3, 0xc
    addi r5, r5, 0x1
    bdnz SoundMgr_Play_L_80192EA4
    SoundMgr_Play_L_80192EE8:
    li r3, 0x1
    SoundMgr_Play_L_80192EEC:
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    lwz r28, 0x20(r1)
    addi r1, r1, 0x30
    blr
}

