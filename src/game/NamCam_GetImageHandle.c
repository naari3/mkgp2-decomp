/* === extracted from auto_NamCam_GetImageHandl_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void AcError_LogIfError();
extern void DebugPrintf();
extern void acClosesocket();
extern void acConnect();
extern void acPollResponse();
extern void acReadResponse();
extern void acRecv();
extern void acSelect();
extern void acSend();
extern void acSetTimeOuts();
extern void acSocket();
extern void fn_802929BC();
extern void fn_80292BFC();
extern void memset();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D1070;
extern unsigned int lbl_806D1074;
extern unsigned int lbl_806D1078;
extern unsigned int lbl_806DCF00;
extern unsigned int lbl_806DCF04;
extern unsigned int lbl_806DCF08;
extern unsigned int lbl_806DCF0C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EB4E0[];

/* --- function index (1 fns, .text 0x80048E0C..0x80049628) ---
 * [  0] 0x80048E0C size:0x81C   global NamCam_GetImageHandle
 */

/* --- forward decls --- */
asm void NamCam_GetImageHandle(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_NamCam_GetImageHandle[8] = {
    0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_NamCam_GetImageHandle = {
    (void *)&NamCam_GetImageHandle, 0x0000081C, (void *)extab_NamCam_GetImageHandle
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void NamCam_GetImageHandle(void) { /* 0x80048E0C size:0x81C */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    lis r5, lbl_802EB4E0@ha
    stw r0, 0x94(r1)
    stw r31, 0x8c(r1)
    addi r31, r5, lbl_802EB4E0@l
    stw r30, 0x88(r1)
    mr r30, r4
    stw r29, 0x84(r1)
    mr r29, r3
    stw r28, 0x80(r1)
    lbz r0, lbl_806D1078(r13)
    lwz r8, 0x0(r31)
    extsb. r0, r0
    lwz r7, 0x4(r31)
    lwz r6, 0x8(r31)
    lwz r5, 0xc(r31)
    lwz r4, 0x10(r31)
    lwz r3, 0x14(r31)
    lhz r0, 0x18(r31)
    stw r8, 0x58(r1)
    stw r7, 0x5c(r1)
    stw r6, 0x60(r1)
    stw r5, 0x64(r1)
    stw r4, 0x68(r1)
    stw r3, 0x6c(r1)
    sth r0, 0x70(r1)
    bne NamCam_GetImageHandle_L_80048E8C
    li r3, 0x0
    li r0, 0x1
    stw r3, lbl_806D1074(r13)
    stb r0, lbl_806D1078(r13)
    NamCam_GetImageHandle_L_80048E8C:
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lbz r0, 0x10(r4)
    extsb r0, r0
    cmpwi r0, 0x2
    beq NamCam_GetImageHandle_L_80049014
    bge NamCam_GetImageHandle_L_80048EB8
    cmpwi r0, 0x0
    beq NamCam_GetImageHandle_L_80048EC8
    bge NamCam_GetImageHandle_L_80048F4C
    b NamCam_GetImageHandle_L_80049604
    NamCam_GetImageHandle_L_80048EB8:
    cmpwi r0, 0x4
    beq NamCam_GetImageHandle_L_800492F4
    bge NamCam_GetImageHandle_L_80049604
    b NamCam_GetImageHandle_L_8004909C
    NamCam_GetImageHandle_L_80048EC8:
    li r3, 0x3c
    li r0, 0x0
    stw r3, 0x28(r4)
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    stb r0, 0x18(r3)
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    cmpwi r3, 0x0
    blt NamCam_GetImageHandle_L_80048EF8
    bl acClosesocket
    NamCam_GetImageHandle_L_80048EF8:
    lwz r3, lbl_806D1070(r13)
    li r0, -0x1
    addis r3, r3, 0x8
    stw r0, 0x14(r3)
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r3, 0x24(r4)
    subic. r0, r3, 0x1
    stw r0, 0x24(r4)
    ble NamCam_GetImageHandle_L_80048F28
    li r3, 0x0
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_80048F28:
    lwz r3, lbl_806D1070(r13)
    li r4, 0x0
    lis r5, 0x8
    bl memset
    lwz r3, lbl_806D1070(r13)
    li r0, 0x1
    addis r3, r3, 0x8
    stb r0, 0x10(r3)
    b NamCam_GetImageHandle_L_80049604
    NamCam_GetImageHandle_L_80048F4C:
    li r3, 0x2
    li r4, 0x1
    li r5, 0x0
    bl acSocket
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    stw r3, 0x14(r4)
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r3, 0x14(r4)
    cmpwi r3, 0x0
    bge NamCam_GetImageHandle_L_80048FC8
    li r0, 0x3c
    addi r3, r31, 0x440
    stw r0, 0x24(r4)
    lwz r4, lbl_806D1070(r13)
    addis r4, r4, 0x8
    lwz r4, 0x14(r4)
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r4, lbl_806D1070(r13)
    li r3, 0x0
    addis r4, r4, 0x8
    lwz r4, 0x14(r4)
    bl AcError_LogIfError
    lwz r4, lbl_806D1070(r13)
    li r0, 0x0
    li r3, 0x0
    addis r4, r4, 0x8
    stb r0, 0x10(r4)
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_80048FC8:
    li r4, 0x7d0
    li r5, 0x7d0
    li r6, 0x7d0
    bl acSetTimeOuts
    lwz r3, lbl_806D1070(r13)
    li r0, 0x2
    li r5, 0x10
    addis r3, r3, 0x8
    stb r0, 0x10(r3)
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r3, 0x14(r4)
    bl acConnect
    cmpwi r3, 0x0
    bge NamCam_GetImageHandle_L_80049604
    addi r3, r31, 0x494
    crxor 6, 6, 6
    bl DebugPrintf
    NamCam_GetImageHandle_L_80049010:
    b NamCam_GetImageHandle_L_80049010
    NamCam_GetImageHandle_L_80049014:
    lwz r3, 0x14(r4)
    bl acPollResponse
    cmpwi r3, 0x1
    bne NamCam_GetImageHandle_L_80049604
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    bl acReadResponse
    mr. r28, r3
    bge NamCam_GetImageHandle_L_80049078
    mr r4, r28
    addi r3, r31, 0x454
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r3, lbl_806D1070(r13)
    mr r4, r28
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    bl AcError_LogIfError
    lwz r4, lbl_806D1070(r13)
    li r0, 0x0
    li r3, 0x0
    addis r4, r4, 0x8
    stb r0, 0x10(r4)
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_80049078:
    lwz r3, lbl_806D1070(r13)
    li r4, 0x3
    li r0, 0x0
    addis r3, r3, 0x8
    stb r4, 0x10(r3)
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    stb r0, 0x11(r3)
    b NamCam_GetImageHandle_L_80049604
    NamCam_GetImageHandle_L_8004909C:
    lbz r0, 0x11(r4)
    extsb r0, r0
    cmpwi r0, 0x1
    beq NamCam_GetImageHandle_L_800490E4
    bge NamCam_GetImageHandle_L_800490BC
    cmpwi r0, 0x0
    bge NamCam_GetImageHandle_L_800490C8
    b NamCam_GetImageHandle_L_80049604
    NamCam_GetImageHandle_L_800490BC:
    cmpwi r0, 0x3
    bge NamCam_GetImageHandle_L_80049604
    b NamCam_GetImageHandle_L_8004922C
    NamCam_GetImageHandle_L_800490C8:
    li r0, 0x0
    stw r0, 0x1c(r4)
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lbz r3, 0x11(r4)
    addi r0, r3, 0x1
    stb r0, 0x11(r4)
    NamCam_GetImageHandle_L_800490E4:
    lwz r5, lbl_806DCF00(r2)
    addi r3, r1, 0x38
    lwz r0, lbl_806DCF04(r2)
    li r4, 0x0
    stw r5, 0x10(r1)
    li r5, 0x20
    stw r0, 0x14(r1)
    bl memset
    lwz r3, lbl_806D1070(r13)
    addi r5, r1, 0x38
    li r8, 0x1
    addi r7, r1, 0x10
    addis r3, r3, 0x8
    li r4, 0x0
    lwz r9, 0x14(r3)
    li r3, 0x100
    li r6, 0x0
    clrlwi r0, r9, 27
    rlwinm r9, r9, 29, 3, 29
    slw r10, r8, r0
    lwzx r8, r5, r9
    rlwinm r0, r10, 8, 8, 15
    rlwimi r0, r10, 24, 0, 7
    rlwimi r0, r10, 24, 16, 23
    rlwimi r0, r10, 8, 24, 31
    or r0, r8, r0
    stwx r0, r5, r9
    bl acSelect
    cmpwi r3, 0x0
    bgt NamCam_GetImageHandle_L_80049174
    mr r4, r3
    addi r3, r31, 0x4a4
    crxor 6, 6, 6
    bl DebugPrintf
    li r3, 0x0
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_80049174:
    lwz r5, lbl_806D1070(r13)
    li r3, 0x1
    addi r4, r1, 0x38
    addis r6, r5, 0x8
    lwz r5, 0x14(r6)
    clrlwi r0, r5, 27
    rlwinm r5, r5, 29, 3, 29
    slw r7, r3, r0
    lwzx r3, r4, r5
    rlwinm r0, r7, 8, 8, 15
    rlwimi r0, r7, 24, 0, 7
    rlwimi r0, r7, 24, 16, 23
    rlwimi r0, r7, 8, 24, 31
    and. r0, r3, r0
    bne NamCam_GetImageHandle_L_800491B8
    li r3, 0x0
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_800491B8:
    lwz r4, 0x1c(r6)
    addi r3, r1, 0x58
    subfic r5, r4, 0x1a
    bl fn_802929BC
    lwz r4, lbl_806D1070(r13)
    addis r6, r4, 0x8
    lwz r4, 0x1c(r6)
    subfic r5, r4, 0x1a
    cmplw r3, r5
    beq NamCam_GetImageHandle_L_800491F4
    mr r5, r3
    addi r3, r2, -0x7BA0  /* lbl_806D26C0@sda21 */
    crxor 6, 6, 6
    bl DebugPrintf
    NamCam_GetImageHandle_L_800491F0:
    b NamCam_GetImageHandle_L_800491F0
    NamCam_GetImageHandle_L_800491F4:
    lwz r3, 0x14(r6)
    li r6, 0x0
    bl acSend
    cmpwi r3, 0x0
    bge NamCam_GetImageHandle_L_80049218
    addi r3, r31, 0x4c0
    crxor 6, 6, 6
    bl DebugPrintf
    NamCam_GetImageHandle_L_80049214:
    b NamCam_GetImageHandle_L_80049214
    NamCam_GetImageHandle_L_80049218:
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lbz r3, 0x11(r4)
    addi r0, r3, 0x1
    stb r0, 0x11(r4)
    NamCam_GetImageHandle_L_8004922C:
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    bl acPollResponse
    cmpwi r3, 0x1
    beq NamCam_GetImageHandle_L_8004924C
    li r3, 0x0
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_8004924C:
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    bl acReadResponse
    mr. r28, r3
    bge NamCam_GetImageHandle_L_800492A0
    mr r4, r28
    addi r3, r31, 0x468
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r3, lbl_806D1070(r13)
    mr r4, r28
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    bl AcError_LogIfError
    lwz r4, lbl_806D1070(r13)
    li r0, 0x0
    li r3, 0x0
    addis r4, r4, 0x8
    stb r0, 0x10(r4)
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_800492A0:
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r0, 0x1c(r3)
    add r0, r0, r28
    stw r0, 0x1c(r3)
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r0, 0x1c(r4)
    cmplwi r0, 0x1a
    bge NamCam_GetImageHandle_L_800492D8
    li r0, 0x1
    li r3, 0x0
    stb r0, 0x11(r4)
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_800492D8:
    li r3, 0x4
    li r0, 0x0
    stb r3, 0x10(r4)
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    stb r0, 0x11(r3)
    b NamCam_GetImageHandle_L_80049604
    NamCam_GetImageHandle_L_800492F4:
    lbz r0, 0x11(r4)
    extsb r0, r0
    cmpwi r0, 0x1
    beq NamCam_GetImageHandle_L_80049330
    bge NamCam_GetImageHandle_L_80049604
    cmpwi r0, 0x0
    bge NamCam_GetImageHandle_L_80049314
    b NamCam_GetImageHandle_L_80049604
    NamCam_GetImageHandle_L_80049314:
    li r0, 0x0
    stw r0, 0x20(r4)
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lbz r3, 0x11(r4)
    addi r0, r3, 0x1
    stb r0, 0x11(r4)
    NamCam_GetImageHandle_L_80049330:
    lwz r5, lbl_806DCF08(r2)
    addi r3, r1, 0x18
    lwz r0, lbl_806DCF0C(r2)
    li r4, 0x0
    stw r5, 0x8(r1)
    li r5, 0x20
    stw r0, 0xc(r1)
    bl memset
    lwz r3, lbl_806D1070(r13)
    addi r4, r1, 0x18
    li r8, 0x1
    addi r7, r1, 0x8
    addis r3, r3, 0x8
    li r5, 0x0
    lwz r9, 0x14(r3)
    li r3, 0x100
    li r6, 0x0
    clrlwi r0, r9, 27
    rlwinm r9, r9, 29, 3, 29
    slw r10, r8, r0
    lwzx r8, r4, r9
    rlwinm r0, r10, 8, 8, 15
    rlwimi r0, r10, 24, 0, 7
    rlwimi r0, r10, 24, 16, 23
    rlwimi r0, r10, 8, 24, 31
    or r0, r8, r0
    stwx r0, r4, r9
    bl acSelect
    cmpwi r3, 0x0
    bgt NamCam_GetImageHandle_L_80049400
    mr r4, r3
    addi r3, r31, 0x4d8
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r3, 0x28(r4)
    subi r0, r3, 0x1
    stw r0, 0x28(r4)
    lwz r3, lbl_806D1070(r13)
    addis r4, r3, 0x8
    lwz r0, 0x28(r4)
    cmpwi r0, 0x0
    bge NamCam_GetImageHandle_L_800493F8
    li r3, -0x1
    li r0, 0x0
    stw r3, 0x14(r4)
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    stb r0, 0x10(r3)
    NamCam_GetImageHandle_L_800493F8:
    li r3, 0x0
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_80049400:
    lwz r3, lbl_806D1070(r13)
    li r4, 0x1
    addi r5, r1, 0x18
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    clrlwi r0, r3, 27
    rlwinm r6, r3, 29, 3, 29
    slw r7, r4, r0
    lwzx r4, r5, r6
    rlwinm r0, r7, 8, 8, 15
    rlwimi r0, r7, 24, 0, 7
    rlwimi r0, r7, 24, 16, 23
    rlwimi r0, r7, 8, 24, 31
    and. r0, r4, r0
    bne NamCam_GetImageHandle_L_80049444
    li r3, 0x0
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_80049444:
    li r4, 0x0
    lis r5, 0x1
    li r6, 0x0
    bl acRecv
    NamCam_GetImageHandle_L_80049454:
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    bl acPollResponse
    cmpwi r3, 0x1
    bne NamCam_GetImageHandle_L_80049454
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    bl acReadResponse
    mr. r28, r3
    ble NamCam_GetImageHandle_L_800494A0
    lwz r6, lbl_806D1070(r13)
    mr r5, r28
    li r3, 0x0
    addis r4, r6, 0x8
    lwz r0, 0x20(r4)
    add r4, r6, r0
    bl fn_80292BFC
    NamCam_GetImageHandle_L_800494A0:
    cmpwi r28, 0x0
    bge NamCam_GetImageHandle_L_800494E4
    mr r4, r28
    addi r3, r31, 0x47c
    crxor 6, 6, 6
    bl DebugPrintf
    lwz r3, lbl_806D1070(r13)
    mr r4, r28
    addis r3, r3, 0x8
    lwz r3, 0x14(r3)
    bl AcError_LogIfError
    lwz r4, lbl_806D1070(r13)
    li r0, 0x0
    li r3, 0x0
    addis r4, r4, 0x8
    stb r0, 0x10(r4)
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_800494E4:
    ble NamCam_GetImageHandle_L_800494FC
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    lwz r0, 0x20(r3)
    add r0, r0, r28
    stw r0, 0x20(r3)
    NamCam_GetImageHandle_L_800494FC:
    cmpwi r28, 0x0
    beq NamCam_GetImageHandle_L_8004950C
    li r3, 0x0
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_8004950C:
    lwz r4, lbl_806D1070(r13)
    addis r3, r4, 0x8
    lwz r0, 0x20(r3)
    add r3, r4, r0
    lbz r0, -0x2(r3)
    extsb r0, r0
    cmpwi r0, -0x1
    bne NamCam_GetImageHandle_L_800495F0
    lbz r0, -0x1(r3)
    extsb r0, r0
    cmpwi r0, -0x27
    bne NamCam_GetImageHandle_L_800495F0
    addi r0, r4, 0x3
    stw r0, 0x0(r29)
    b NamCam_GetImageHandle_L_80049554
    NamCam_GetImageHandle_L_80049548:
    lwz r3, 0x0(r29)
    addi r0, r3, 0x1
    stw r0, 0x0(r29)
    NamCam_GetImageHandle_L_80049554:
    lwz r3, 0x0(r29)
    lbz r0, 0x0(r3)
    cmpwi r0, 0xa
    bne NamCam_GetImageHandle_L_80049548
    lbz r0, -0x1(r3)
    cmpwi r0, 0xd
    bne NamCam_GetImageHandle_L_80049548
    lbz r0, -0x2(r3)
    cmpwi r0, 0xa
    bne NamCam_GetImageHandle_L_80049548
    lbz r0, -0x3(r3)
    cmpwi r0, 0xd
    bne NamCam_GetImageHandle_L_80049548
    addi r0, r3, 0x1
    li r4, 0x1
    stw r0, 0x0(r29)
    cmplwi r30, 0x0
    li r0, 0x0
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    stb r4, 0x18(r3)
    lwz r3, lbl_806D1070(r13)
    addis r3, r3, 0x8
    stb r0, 0x10(r3)
    beq NamCam_GetImageHandle_L_800495E8
    lwz r3, lbl_806D1070(r13)
    lis r0, 0x8
    addis r3, r3, 0x8
    lwz r3, 0x20(r3)
    stw r3, 0x0(r30)
    lwz r3, 0x0(r30)
    cmplw r3, r0
    ble NamCam_GetImageHandle_L_800495E8
    addi r3, r31, 0x4f4
    crxor 6, 6, 6
    bl DebugPrintf
    NamCam_GetImageHandle_L_800495E4:
    b NamCam_GetImageHandle_L_800495E4
    NamCam_GetImageHandle_L_800495E8:
    li r3, 0x1
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_800495F0:
    addis r3, r4, 0x8
    li r0, 0x0
    stb r0, 0x10(r3)
    li r3, 0x0
    b NamCam_GetImageHandle_L_80049608
    NamCam_GetImageHandle_L_80049604:
    li r3, 0x0
    NamCam_GetImageHandle_L_80049608:
    lwz r0, 0x94(r1)
    lwz r31, 0x8c(r1)
    lwz r30, 0x88(r1)
    lwz r29, 0x84(r1)
    lwz r28, 0x80(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}
