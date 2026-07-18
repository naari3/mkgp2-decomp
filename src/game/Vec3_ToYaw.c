/* === extracted from auto_Vec3_ToYaw_text === */
#pragma scheduling off
extern void Atan2();
asm void Vec3_ToYaw(void);
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Vec3_ToYaw[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Vec3_ToYaw = {
    (void *)&Vec3_ToYaw, 0x0000002C, (void *)extab_Vec3_ToYaw
};
asm void Vec3_ToYaw(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lfs f1, 0x0(r3)
    stw r0, 0x14(r1)
    lfs f2, 0x8(r3)
    bl Atan2
    lwz r0, 0x14(r1)
    frsp f1, f1
    mtlr r0
    addi r1, r1, 0x10
    blr
}
