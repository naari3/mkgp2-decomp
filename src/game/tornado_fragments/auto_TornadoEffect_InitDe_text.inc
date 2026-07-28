/* === extracted from auto_TornadoEffect_InitDe_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void DrawEffect_SetU32CC();
extern void DrawEffect_SpawnWithDescriptor();
extern void Object_SetColorAlphaOnly();
extern void Object_SetJObjScaleXYZ();
extern void clNormal3D_Construct();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D28C8;
extern unsigned int lbl_806D28CC;
extern unsigned int lbl_806D28D0;
extern unsigned int lbl_806D28D4;
extern unsigned int lbl_806D28D8;
extern unsigned int lbl_806D28DC;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_802EDC54[];
extern unsigned int lbl_802EDC60[];

/* --- function index (1 fns, .text 0x80056CB0..0x80056EC0) ---
 * [  0] 0x80056CB0 size:0x210   global TornadoEffect_InitDetails
 */

/* --- forward decls --- */
asm void TornadoEffect_InitDetails(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_TornadoEffect_InitDetails = { 0x100A0000, 0x000001B0, 0x00000010, 0x00000000, 0x8A80001F, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_TornadoEffect_InitDetails = {
    (void *)&TornadoEffect_InitDetails, 0x00000210, (void *)&extab_TornadoEffect_InitDetails
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void TornadoEffect_InitDetails(void) { /* 0x80056CB0 size:0x210 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r5, lbl_802EDC54@ha
    stw r0, 0x34(r1)
    addi r7, r5, lbl_802EDC54@l
    stw r31, 0x2c(r1)
    mr r31, r4
    addi r4, r1, 0x8
    stw r30, 0x28(r1)
    mr r30, r3
    li r3, 0x1
    lwz r6, 0x0(r7)
    lwz r5, 0x4(r7)
    lwz r0, 0x8(r7)
    stw r6, 0x14(r1)
    stw r5, 0x18(r1)
    stw r0, 0x1c(r1)
    stfs f1, 0x14(r1)
    stfs f2, 0x18(r1)
    lwz r6, 0x14(r1)
    stfs f3, 0x1c(r1)
    lwz r5, 0x18(r1)
    lwz r0, 0x1c(r1)
    stw r6, 0x8(r1)
    stw r5, 0xc(r1)
    stw r0, 0x10(r1)
    bl DrawEffect_SpawnWithDescriptor
    stw r3, 0x10(r30)
    mr r4, r31
    lwz r3, 0x10(r30)
    bl DrawEffect_SetU32CC
    lfs f2, lbl_806D28C8(r2)
    li r4, 0x0
    lfs f1, lbl_806D28CC(r2)
    li r0, -0x1
    stfs f2, 0x5c(r30)
    li r3, 0x5c
    lfs f0, lbl_806D28D0(r2)
    stfs f2, 0x60(r30)
    stfs f2, 0x64(r30)
    stfs f2, 0x68(r30)
    stfs f2, 0x6c(r30)
    stfs f2, 0x70(r30)
    stfs f2, 0x74(r30)
    stfs f2, 0x78(r30)
    stfs f2, 0x7c(r30)
    stfs f2, 0x80(r30)
    stfs f2, 0x84(r30)
    stfs f2, 0x88(r30)
    stfs f2, 0x8c(r30)
    stfs f2, 0x90(r30)
    stfs f2, 0x94(r30)
    stfs f2, 0x98(r30)
    stfs f2, 0x9c(r30)
    stfs f2, 0xa0(r30)
    stfs f2, 0xa4(r30)
    stfs f1, 0xa4(r30)
    stfs f1, 0x90(r30)
    stfs f1, 0x7c(r30)
    stfs f1, 0x68(r30)
    stfs f2, 0xac(r30)
    stfs f2, 0xb0(r30)
    stb r4, 0xb4(r30)
    stfs f2, 0xb8(r30)
    stfs f2, 0xbc(r30)
    stb r4, 0xc0(r30)
    stfs f2, 0xc4(r30)
    stw r4, 0xc8(r30)
    stw r4, 0xcc(r30)
    stb r4, 0xd0(r30)
    stb r4, 0xd1(r30)
    stb r4, 0xd2(r30)
    stw r4, 0x13c(r30)
    stw r4, 0xd4(r30)
    stfs f1, 0xec(r30)
    stfs f1, 0xf0(r30)
    stfs f1, 0xf4(r30)
    stfs f1, 0xe0(r30)
    stfs f1, 0xe4(r30)
    stfs f1, 0xe8(r30)
    stb r4, 0xf8(r30)
    stfs f2, 0xfc(r30)
    stw r4, 0x104(r30)
    stfs f1, 0x10c(r30)
    stfs f0, 0x110(r30)
    stfs f2, 0x118(r30)
    stfs f2, 0x114(r30)
    stw r0, 0x100(r30)
    stfs f2, 0x11c(r30)
    stfs f2, 0x120(r30)
    stw r4, 0x124(r30)
    stw r4, 0x128(r30)
    stb r4, 0x12c(r30)
    stw r4, 0x130(r30)
    stw r4, 0x134(r30)
    stw r4, 0x138(r30)
    stw r4, 0x140(r30)
    stw r4, 0x144(r30)
    stw r4, 0x148(r30)
    stw r0, 0x14c(r30)
    stw r0, 0x150(r30)
    bl Alloc
    mr. r31, r3
    beq TornadoEffect_InitDetails_L_80056E60
    lis r4, lbl_802EDC60@ha
    li r5, 0x1
    addi r4, r4, lbl_802EDC60@l
    bl clNormal3D_Construct
    TornadoEffect_InitDetails_L_80056E60:
    stw r31, 0xa8(r30)
    lbz r0, 0x8(r30)
    cmplwi r0, 0x1
    bne TornadoEffect_InitDetails_L_80056E84
    lwz r3, 0xa8(r30)
    li r4, 0x0
    lfs f1, lbl_806D28D4(r2)
    bl Object_SetColorAlphaOnly
    b TornadoEffect_InitDetails_L_80056E94
    TornadoEffect_InitDetails_L_80056E84:
    lwz r3, 0xa8(r30)
    li r4, 0x0
    lfs f1, lbl_806D28D8(r2)
    bl Object_SetColorAlphaOnly
    TornadoEffect_InitDetails_L_80056E94:
    lfs f1, lbl_806D28CC(r2)
    lwz r3, 0xa8(r30)
    fmr f3, f1
    lfs f2, lbl_806D28DC(r2)
    bl Object_SetJObjScaleXYZ
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

