extern void MJObj_SetColorRGBA_Float();
extern unsigned int lbl_806D2344;

asm void Object_SetColorRGBA(void);
asm void Object_SetColorAlphaOnly(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Object_SetColorRGBA[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_Object_SetColorAlphaOnly[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Object_SetColorRGBA = {
    (void *)&Object_SetColorRGBA, 0x80, (void *)extab_Object_SetColorRGBA
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Object_SetColorAlphaOnly = {
    (void *)&Object_SetColorAlphaOnly, 0x94, (void *)extab_Object_SetColorAlphaOnly
};

asm void Object_SetColorRGBA(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lfs f0, 0x4c(r3)
    fcmpu cr0, f0, f1
    bne Object_SetColorRGBA_L_80031444
    lfs f0, 0x50(r3)
    fcmpu cr0, f0, f2
    bne Object_SetColorRGBA_L_80031444
    lfs f0, 0x54(r3)
    fcmpu cr0, f0, f3
    bne Object_SetColorRGBA_L_80031444
    lfs f0, 0x58(r3)
    fcmpu cr0, f0, f4
    beq Object_SetColorRGBA_L_80031478
Object_SetColorRGBA_L_80031444:
    stfs f1, 0x4c(r3)
    cmplwi r4, 0
    stfs f2, 0x50(r3)
    stfs f3, 0x54(r3)
    stfs f4, 0x58(r3)
    bne Object_SetColorRGBA_L_80031470
    lwz r4, 0x30(r3)
    cmplwi r4, 0
    beq Object_SetColorRGBA_L_8003146C
    b Object_SetColorRGBA_L_80031470
Object_SetColorRGBA_L_8003146C:
    lwz r4, 0x2c(r3)
Object_SetColorRGBA_L_80031470:
    mr r3, r4
    bl MJObj_SetColorRGBA_Float
Object_SetColorRGBA_L_80031478:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void Object_SetColorAlphaOnly(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    fmr f4, f1
    cmplwi r4, 0
    stw r0, 0x14(r1)
    bne Object_SetColorAlphaOnly_L_800314B4
    lwz r4, 0x30(r3)
    cmplwi r4, 0
    beq Object_SetColorAlphaOnly_L_800314B0
    b Object_SetColorAlphaOnly_L_800314B4
Object_SetColorAlphaOnly_L_800314B0:
    lwz r4, 0x2c(r3)
Object_SetColorAlphaOnly_L_800314B4:
    lfs f1, lbl_806D2344(r2)
    lfs f0, 0x4c(r3)
    fcmpu cr0, f1, f0
    bne Object_SetColorAlphaOnly_L_800314E8
    lfs f0, 0x50(r3)
    fcmpu cr0, f1, f0
    bne Object_SetColorAlphaOnly_L_800314E8
    lfs f0, 0x54(r3)
    fcmpu cr0, f1, f0
    bne Object_SetColorAlphaOnly_L_800314E8
    lfs f0, 0x58(r3)
    fcmpu cr0, f0, f4
    beq Object_SetColorAlphaOnly_L_8003150C
Object_SetColorAlphaOnly_L_800314E8:
    lfs f1, lbl_806D2344(r2)
    stfs f1, 0x4c(r3)
    fmr f2, f1
    fmr f3, f1
    stfs f1, 0x50(r3)
    stfs f1, 0x54(r3)
    stfs f4, 0x58(r3)
    mr r3, r4
    bl MJObj_SetColorRGBA_Float
Object_SetColorAlphaOnly_L_8003150C:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
