/* === extracted from auto_TornadoEffect_Tick_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DrawEffect_SetByte104();
extern void DrawEffect_SetByte10C();
extern void DrawEffect_SetBytePairD4D5();
extern void DrawEffect_SetFloat108Avg();
extern void DrawEffect_SetFloat110();
extern void KartDriver_SetUniformScale_4Wheels();
extern void KartItem_BroadcastParamToCarAndISE();
extern void Object_GetJObjRotationY();
extern void Object_SetColorAlphaOnly();
extern void Object_SetJObjRotationY();
extern void Saturate_Double();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D28C8;
extern unsigned int lbl_806D28CC;
extern unsigned int lbl_806D28D0;
extern unsigned int lbl_806D28D4;
extern unsigned int lbl_806D28D8;
extern unsigned int lbl_806D28DC;
extern unsigned int lbl_806D28E8;
extern unsigned int lbl_806D28EC;
extern unsigned int lbl_806D28F0;
extern unsigned int lbl_806D28F4;
extern unsigned int lbl_806D28F8;
extern unsigned int lbl_806D28FC;
extern unsigned int lbl_806D2900;
extern unsigned int lbl_806D2904;
extern unsigned int lbl_806D2908;
extern unsigned int lbl_806D290C;
extern unsigned int lbl_806D2910;
extern unsigned int lbl_806D2914;
extern unsigned int lbl_806D2918;
extern unsigned int lbl_806D2920;
extern unsigned int lbl_806D2924;
extern unsigned int lbl_806D2928;
extern unsigned int lbl_806D2930;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EDC3C[];
extern unsigned int lbl_802EDC48[];

/* --- function index (1 fns, .text 0x80056FC0..0x800576D8) ---
 * [  0] 0x80056FC0 size:0x718   global TornadoEffect_Tick
 */

/* --- forward decls --- */
asm void TornadoEffect_Tick(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TornadoEffect_Tick[8] = {
    0x20, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_Tick = {
    (void *)&TornadoEffect_Tick, 0x00000718, (void *)extab_TornadoEffect_Tick
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_Tick(void) { /* 0x80056FC0 size:0x718 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    stw r0, 0x54(r1)
    stfd f31, 0x40(r1)
    psq_st f31, 0x48(r1), 0, 0
    stw r31, 0x3c(r1)
    stw r30, 0x38(r1)
    stw r29, 0x34(r1)
    stw r28, 0x30(r1)
    mr r31, r3
    lwz r3, 0x140(r3)
    lwz r4, 0xc(r31)
    cmpwi r3, 0x0
    lwz r8, 0x304(r4)
    ble TornadoEffect_Tick_L_80057004
    subi r0, r3, 0x1
    stw r0, 0x140(r31)
    TornadoEffect_Tick_L_80057004:
    lwz r6, 0x10(r8)
    li r4, 0x0
    lwz r3, 0x18(r8)
    lis r0, 0x800
    lwz r7, 0x14(r8)
    lwz r5, 0x1c(r8)
    or r6, r6, r3
    and r0, r6, r0
    or r7, r7, r5
    and r3, r7, r4
    xor r0, r0, r4
    xor r3, r3, r4
    or. r0, r3, r0
    bne TornadoEffect_Tick_L_80057040
    b TornadoEffect_Tick_L_80057044
    TornadoEffect_Tick_L_80057040:
    li r4, 0x1
    TornadoEffect_Tick_L_80057044:
    clrlwi r0, r4, 24
    cmplwi r0, 0x1
    bne TornadoEffect_Tick_L_80057060
    lwz r3, 0xc(r31)
    lwz r4, 0x4c(r8)
    bl KartItem_BroadcastParamToCarAndISE
    b TornadoEffect_Tick_L_8005706C
    TornadoEffect_Tick_L_80057060:
    lwz r3, 0xc(r31)
    li r4, -0x1
    bl KartItem_BroadcastParamToCarAndISE
    TornadoEffect_Tick_L_8005706C:
    lwz r3, 0x138(r31)
    cmpwi r3, 0x0
    ble TornadoEffect_Tick_L_80057080
    subi r0, r3, 0x1
    stw r0, 0x138(r31)
    TornadoEffect_Tick_L_80057080:
    lwz r0, 0x124(r31)
    cmpwi r0, 0x0
    beq TornadoEffect_Tick_L_80057098
    lwz r3, 0x130(r31)
    addi r0, r3, 0x1
    stw r0, 0x130(r31)
    TornadoEffect_Tick_L_80057098:
    lwz r0, 0x128(r31)
    cmpwi r0, 0x0
    beq TornadoEffect_Tick_L_800570B0
    lwz r3, 0x134(r31)
    addi r0, r3, 0x1
    stw r0, 0x134(r31)
    TornadoEffect_Tick_L_800570B0:
    lwz r3, 0x100(r31)
    cmpwi r3, 0x0
    ble TornadoEffect_Tick_L_80057138
    subi r0, r3, 0x1
    stw r0, 0x100(r31)
    lwz r3, 0xa8(r31)
    bl Object_GetJObjRotationY
    lfs f0, lbl_806D28DC(r2)
    lwz r3, 0xa8(r31)
    fsubs f1, f1, f0
    bl Object_SetJObjRotationY
    lwz r4, 0x100(r31)
    lis r3, 0x4330
    lbz r0, 0x8(r31)
    xoris r4, r4, 0x8000
    stw r3, 0x20(r1)
    lfd f2, lbl_806D2930(r2)
    cmplwi r0, 0x1
    stw r4, 0x24(r1)
    lfs f0, lbl_806D28EC(r2)
    lfd f1, 0x20(r1)
    lfs f3, lbl_806D28E8(r2)
    fsubs f1, f1, f2
    lfs f2, lbl_806D28C8(r2)
    fdivs f0, f1, f0
    fmuls f1, f3, f0
    bne TornadoEffect_Tick_L_80057124
    lfs f3, lbl_806D28D4(r2)
    b TornadoEffect_Tick_L_80057128
    TornadoEffect_Tick_L_80057124:
    lfs f3, lbl_806D28D8(r2)
    TornadoEffect_Tick_L_80057128:
    bl Saturate_Double
    lwz r3, 0xa8(r31)
    li r4, 0x0
    bl Object_SetColorAlphaOnly
    TornadoEffect_Tick_L_80057138:
    lwz r0, 0x104(r31)
    lfs f31, 0x10c(r31)
    cmpwi r0, 0x1
    beq TornadoEffect_Tick_L_800571B0
    bge TornadoEffect_Tick_L_80057158
    cmpwi r0, 0x0
    bge TornadoEffect_Tick_L_80057164
    b TornadoEffect_Tick_L_8005723C
    TornadoEffect_Tick_L_80057158:
    cmpwi r0, 0x3
    bge TornadoEffect_Tick_L_8005723C
    b TornadoEffect_Tick_L_80057204
    TornadoEffect_Tick_L_80057164:
    lfs f1, lbl_806D28CC(r2)
    fcmpo cr0, f31, f1
    ble TornadoEffect_Tick_L_80057190
    lfs f0, lbl_806D28D0(r2)
    fsubs f0, f31, f0
    stfs f0, 0x10c(r31)
    lfs f0, 0x10c(r31)
    fcmpo cr0, f0, f1
    bge TornadoEffect_Tick_L_8005723C
    stfs f1, 0x10c(r31)
    b TornadoEffect_Tick_L_8005723C
    TornadoEffect_Tick_L_80057190:
    lfs f0, lbl_806D28D0(r2)
    fadds f0, f31, f0
    stfs f0, 0x10c(r31)
    lfs f0, 0x10c(r31)
    fcmpo cr0, f0, f1
    ble TornadoEffect_Tick_L_8005723C
    stfs f1, 0x10c(r31)
    b TornadoEffect_Tick_L_8005723C
    TornadoEffect_Tick_L_800571B0:
    lfs f0, 0x108(r31)
    fcmpo cr0, f31, f0
    ble TornadoEffect_Tick_L_800571E0
    lfs f0, lbl_806D28D0(r2)
    fsubs f0, f31, f0
    stfs f0, 0x10c(r31)
    lfs f0, 0x10c(r31)
    lfs f1, 0x108(r31)
    fcmpo cr0, f0, f1
    bge TornadoEffect_Tick_L_8005723C
    stfs f1, 0x10c(r31)
    b TornadoEffect_Tick_L_8005723C
    TornadoEffect_Tick_L_800571E0:
    lfs f0, lbl_806D28D0(r2)
    fadds f0, f31, f0
    stfs f0, 0x10c(r31)
    lfs f0, 0x10c(r31)
    lfs f1, 0x108(r31)
    fcmpo cr0, f0, f1
    ble TornadoEffect_Tick_L_8005723C
    stfs f1, 0x10c(r31)
    b TornadoEffect_Tick_L_8005723C
    TornadoEffect_Tick_L_80057204:
    lfs f2, 0x110(r31)
    lfs f0, lbl_806D28F0(r2)
    fadds f1, f31, f2
    fcmpo cr0, f1, f0
    bgt TornadoEffect_Tick_L_80057224
    lfs f0, lbl_806D28F4(r2)
    fcmpo cr0, f1, f0
    bge TornadoEffect_Tick_L_8005722C
    TornadoEffect_Tick_L_80057224:
    fneg f0, f2
    stfs f0, 0x110(r31)
    TornadoEffect_Tick_L_8005722C:
    lfs f2, lbl_806D28F4(r2)
    lfs f3, lbl_806D28F0(r2)
    bl Saturate_Double
    stfs f1, 0x10c(r31)
    TornadoEffect_Tick_L_8005723C:
    lfs f0, 0x10c(r31)
    fcmpo cr0, f0, f31
    ble TornadoEffect_Tick_L_80057264
    lwz r0, 0x144(r31)
    cmpwi r0, 0x0
    bgt TornadoEffect_Tick_L_80057290
    li r0, 0x1
    stw r0, 0x144(r31)
    stw r0, 0x148(r31)
    b TornadoEffect_Tick_L_80057290
    TornadoEffect_Tick_L_80057264:
    bge TornadoEffect_Tick_L_80057284
    lwz r0, 0x144(r31)
    cmpwi r0, 0x0
    blt TornadoEffect_Tick_L_80057290
    li r0, -0x1
    stw r0, 0x144(r31)
    stw r0, 0x148(r31)
    b TornadoEffect_Tick_L_80057290
    TornadoEffect_Tick_L_80057284:
    li r0, 0x0
    stw r0, 0x144(r31)
    stw r0, 0x148(r31)
    TornadoEffect_Tick_L_80057290:
    lwz r3, 0xc(r31)
    lfs f1, 0x10c(r31)
    bl KartDriver_SetUniformScale_4Wheels
    lfs f1, 0xbc(r31)
    lfs f0, lbl_806D28D8(r2)
    fcmpo cr0, f1, f0
    bge TornadoEffect_Tick_L_800572B4
    lfs f1, lbl_806D28D0(r2)
    b TornadoEffect_Tick_L_800572B8
    TornadoEffect_Tick_L_800572B4:
    lfs f1, lbl_806D28F8(r2)
    TornadoEffect_Tick_L_800572B8:
    lbz r0, 0xb4(r31)
    lfs f3, lbl_806D28FC(r2)
    cmplwi r0, 0x1
    bne TornadoEffect_Tick_L_800572CC
    lfs f3, lbl_806D28CC(r2)
    TornadoEffect_Tick_L_800572CC:
    lfs f0, 0xb8(r31)
    lfs f2, lbl_806D28C8(r2)
    fadds f1, f0, f1
    bl Saturate_Double
    stfs f1, 0xb8(r31)
    lfs f0, lbl_806D2900(r2)
    lfs f5, 0xac(r31)
    lfs f1, 0xb8(r31)
    fabs f3, f5
    fmr f2, f1
    frsp f4, f3
    fcmpo cr0, f4, f0
    ble TornadoEffect_Tick_L_80057328
    lfs f3, lbl_806D28CC(r2)
    lfs f0, lbl_806D28C8(r2)
    fsubs f3, f3, f4
    lfs f4, lbl_806D2904(r2)
    fcmpo cr0, f5, f0
    fmadds f0, f4, f3, f4
    bge TornadoEffect_Tick_L_80057324
    fmuls f1, f1, f0
    b TornadoEffect_Tick_L_80057328
    TornadoEffect_Tick_L_80057324:
    fmuls f2, f1, f0
    TornadoEffect_Tick_L_80057328:
    lbz r0, 0x8(r31)
    cmplwi r0, 0x0
    beq TornadoEffect_Tick_L_8005734C
    lbz r0, 0xc0(r31)
    cmplwi r0, 0x1
    beq TornadoEffect_Tick_L_8005734C
    lbz r0, 0xd2(r31)
    cmplwi r0, 0x1
    bne TornadoEffect_Tick_L_80057354
    TornadoEffect_Tick_L_8005734C:
    lfs f1, lbl_806D28C8(r2)
    fmr f2, f1
    TornadoEffect_Tick_L_80057354:
    lwz r3, 0x10(r31)
    bl DrawEffect_SetFloat108Avg
    lbz r0, 0xd2(r31)
    cmplwi r0, 0x1
    bne TornadoEffect_Tick_L_800573AC
    lwz r3, 0x10(r31)
    li r4, 0x1
    bl DrawEffect_SetByte10C
    lwz r3, 0x13c(r31)
    cmpwi r3, 0x0
    ble TornadoEffect_Tick_L_800573C0
    subi r0, r3, 0x1
    stw r0, 0x13c(r31)
    lwz r0, 0x13c(r31)
    cmpwi r0, 0x0
    bne TornadoEffect_Tick_L_800573C0
    lwz r3, 0x10(r31)
    li r4, 0x0
    bl DrawEffect_SetByte10C
    li r0, 0x0
    stb r0, 0xd2(r31)
    b TornadoEffect_Tick_L_800573C0
    TornadoEffect_Tick_L_800573AC:
    lwz r3, 0x10(r31)
    li r4, 0x0
    bl DrawEffect_SetByte10C
    li r0, 0x0
    stw r0, 0x13c(r31)
    TornadoEffect_Tick_L_800573C0:
    lbz r0, 0xc0(r31)
    cmplwi r0, 0x1
    bne TornadoEffect_Tick_L_800573E0
    lwz r3, 0x10(r31)
    li r4, 0x0
    li r5, 0x0
    bl DrawEffect_SetBytePairD4D5
    b TornadoEffect_Tick_L_80057444
    TornadoEffect_Tick_L_800573E0:
    lbz r0, 0x8(r31)
    cmplwi r0, 0x1
    bne TornadoEffect_Tick_L_80057408
    lwz r4, 0xc8(r31)
    lwz r0, 0xcc(r31)
    lwz r3, 0x10(r31)
    extsb r4, r4
    extsb r5, r0
    bl DrawEffect_SetBytePairD4D5
    b TornadoEffect_Tick_L_80057418
    TornadoEffect_Tick_L_80057408:
    lwz r3, 0x10(r31)
    li r4, 0x0
    li r5, 0x0
    bl DrawEffect_SetBytePairD4D5
    TornadoEffect_Tick_L_80057418:
    lfs f1, 0xc4(r31)
    lfs f0, lbl_806D28C8(r2)
    fcmpo cr0, f1, f0
    ble TornadoEffect_Tick_L_8005743C
    lbz r0, 0x8(r31)
    cmplwi r0, 0x1
    bne TornadoEffect_Tick_L_8005743C
    lwz r3, 0x10(r31)
    bl DrawEffect_SetFloat110
    TornadoEffect_Tick_L_8005743C:
    lfs f0, lbl_806D28C8(r2)
    stfs f0, 0xc4(r31)
    TornadoEffect_Tick_L_80057444:
    lwz r5, 0xc(r31)
    li r3, 0x20
    li r4, 0x0
    lfs f2, lbl_806D28C8(r2)
    lwz r30, 0x304(r5)
    lwz r0, 0x10(r30)
    lwz r5, 0x14(r30)
    and r0, r0, r4
    and r3, r5, r3
    xor r3, r3, r4
    xor r0, r0, r4
    or. r0, r3, r0
    bne TornadoEffect_Tick_L_8005747C
    b TornadoEffect_Tick_L_80057480
    TornadoEffect_Tick_L_8005747C:
    li r4, 0x1
    TornadoEffect_Tick_L_80057480:
    clrlwi r0, r4, 24
    cmplwi r0, 0x1
    bne TornadoEffect_Tick_L_800574A4
    lwz r0, 0x2c(r30)
    cmpwi r0, 0x1
    bne TornadoEffect_Tick_L_800574A0
    lfs f2, lbl_806D2908(r2)
    b TornadoEffect_Tick_L_800574A4
    TornadoEffect_Tick_L_800574A0:
    lfs f2, lbl_806D290C(r2)
    TornadoEffect_Tick_L_800574A4:
    lfs f1, 0x11c(r31)
    lfs f0, 0x120(r31)
    fadds f1, f1, f2
    lfs f2, lbl_806D2910(r2)
    lfs f3, lbl_806D2914(r2)
    fsubs f1, f1, f0
    bl Saturate_Double
    lfs f0, 0x120(r31)
    lfd f2, lbl_806D2918(r2)
    fadds f0, f0, f1
    stfs f0, 0x120(r31)
    lfs f0, 0x120(r31)
    fmul f0, f2, f0
    frsp f0, f0
    stfs f0, 0x48(r30)
    lbz r0, 0x12c(r31)
    cmplwi r0, 0x1
    bne TornadoEffect_Tick_L_800574FC
    lwz r3, 0x10(r31)
    li r4, 0x1
    bl DrawEffect_SetByte104
    b TornadoEffect_Tick_L_80057508
    TornadoEffect_Tick_L_800574FC:
    lwz r3, 0x10(r31)
    li r4, 0x0
    bl DrawEffect_SetByte104
    TornadoEffect_Tick_L_80057508:
    lwz r0, 0xd4(r31)
    cmpwi r0, 0x0
    beq TornadoEffect_Tick_L_800576B0
    cmpwi r0, 0x2
    beq TornadoEffect_Tick_L_80057568
    bge TornadoEffect_Tick_L_8005752C
    cmpwi r0, 0x1
    bge TornadoEffect_Tick_L_80057538
    b TornadoEffect_Tick_L_800576B0
    TornadoEffect_Tick_L_8005752C:
    cmpwi r0, 0x4
    bge TornadoEffect_Tick_L_800576B0
    b TornadoEffect_Tick_L_800575C8
    TornadoEffect_Tick_L_80057538:
    lfs f2, 0xf0(r31)
    lfs f1, lbl_806D2920(r2)
    lfs f0, lbl_806D28CC(r2)
    fadds f1, f2, f1
    stfs f1, 0xf0(r31)
    lfs f1, 0xf0(r31)
    fcmpo cr0, f1, f0
    ble TornadoEffect_Tick_L_800576B0
    stfs f0, 0xf0(r31)
    li r0, 0x0
    stw r0, 0xd4(r31)
    b TornadoEffect_Tick_L_800576B0
    TornadoEffect_Tick_L_80057568:
    lfs f1, 0xe4(r31)
    lfs f2, 0xf0(r31)
    fcmpo cr0, f2, f1
    bge TornadoEffect_Tick_L_80057598
    lfs f0, lbl_806D2924(r2)
    fadds f2, f2, f0
    fcmpo cr0, f2, f1
    ble TornadoEffect_Tick_L_800575B8
    li r0, 0x0
    fmr f2, f1
    stw r0, 0xd4(r31)
    b TornadoEffect_Tick_L_800575B8
    TornadoEffect_Tick_L_80057598:
    ble TornadoEffect_Tick_L_800575B8
    lfs f0, lbl_806D2928(r2)
    fsubs f2, f2, f0
    fcmpo cr0, f2, f1
    bge TornadoEffect_Tick_L_800575B8
    li r0, 0x0
    fmr f2, f1
    stw r0, 0xd4(r31)
    TornadoEffect_Tick_L_800575B8:
    stfs f2, 0xec(r31)
    stfs f2, 0xf0(r31)
    stfs f2, 0xf4(r31)
    b TornadoEffect_Tick_L_800576B0
    TornadoEffect_Tick_L_800575C8:
    lis r4, lbl_802EDC3C@ha
    lwzu r0, lbl_802EDC3C@l(r4)
    lis r3, lbl_802EDC48@ha
    lwzu r8, lbl_802EDC48@l(r3)
    lwz r30, 0x4(r4)
    addi r11, r31, 0xe0
    lwz r12, 0x8(r4)
    addi r10, r31, 0xe4
    stw r0, 0x14(r1)
    addi r9, r31, 0xe8
    lwz r7, 0x4(r3)
    addi r5, r31, 0xec
    lwz r6, 0x8(r3)
    addi r4, r31, 0xf0
    stw r30, 0x18(r1)
    addi r3, r31, 0xf4
    li r0, 0x3
    addi r29, r1, 0x14
    stw r12, 0x1c(r1)
    addi r28, r1, 0x8
    li r30, 0x0
    stw r8, 0x8(r1)
    stw r7, 0xc(r1)
    stw r6, 0x10(r1)
    stw r11, 0x14(r1)
    stw r10, 0x18(r1)
    stw r9, 0x1c(r1)
    stw r5, 0x8(r1)
    stw r4, 0xc(r1)
    stw r3, 0x10(r1)
    mtctr r0
    lfs f0, lbl_806D28D0(r2)
    TornadoEffect_Tick_L_80057648:
    lwz r3, 0x0(r29)
    lwz r4, 0x0(r28)
    lfs f1, 0x0(r3)
    lfs f2, 0x0(r4)
    fcmpo cr0, f2, f1
    bge TornadoEffect_Tick_L_80057678
    fadds f2, f2, f0
    fcmpo cr0, f2, f1
    ble TornadoEffect_Tick_L_80057690
    fmr f2, f1
    addi r30, r30, 0x1
    b TornadoEffect_Tick_L_80057690
    TornadoEffect_Tick_L_80057678:
    ble TornadoEffect_Tick_L_80057690
    fsubs f2, f2, f0
    fcmpo cr0, f2, f1
    bge TornadoEffect_Tick_L_80057690
    fmr f2, f1
    addi r30, r30, 0x1
    TornadoEffect_Tick_L_80057690:
    stfs f2, 0x0(r4)
    addi r29, r29, 0x4
    addi r28, r28, 0x4
    bdnz TornadoEffect_Tick_L_80057648
    cmpwi r30, 0x3
    blt TornadoEffect_Tick_L_800576B0
    li r0, 0x0
    stw r0, 0xd4(r31)
    TornadoEffect_Tick_L_800576B0:
    psq_l f31, 0x48(r1), 0, 0
    lwz r0, 0x54(r1)
    lfd f31, 0x40(r1)
    lwz r31, 0x3c(r1)
    lwz r30, 0x38(r1)
    lwz r29, 0x34(r1)
    lwz r28, 0x30(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

