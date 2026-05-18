/*
 * bitpack: schema-driven bitstream packer.
 *
 * Layout of the bitpack context (param_1 in Ghidra; 0x18 bytes wide):
 *   0x00  void *schema      schema entry table, 0x10 bytes / entry
 *                            +0x00  tag (u32, fed to FUN_80278FD8 for match)
 *                            +0x04  bit-width per slot
 *                            +0x08  slot count
 *                            +0x0C  per-entry bit offset (filled by init)
 *   0x04  int   schema_count
 *   0x08  void *dest        output byte buffer
 *   0x0C  u8    return_one_on_success / "options" byte
 *   0x10  u32   total_bits  (init result)
 *   0x14  u32   total_bytes (init result, ceil(total_bits/8) + sign-bit)
 *
 * The four routines in this TU are:
 *   bitpack_write_field   - write a value into a named field by tag/index
 *   bitpack_get_used_bytes - accessor
 *   bitpack_get_used_bits  - accessor
 *   bitpack_init          - populate per-entry offsets, derive totals,
 *                            optionally zero the destination buffer
 *
 * Ghidra has no struct type for the bitpack object yet, so we use opaque
 * pointer + raw offset.
 *
 * dtk reversed-extab group: bitpack_write_field and bitpack_init each own
 * one extab/extabindex entry (frame-bearing functions). The two leaf
 * accessors have no extab.
 *
 * Both frame-bearing fns are held as asm_fn (CW reg-allocator quirk:
 * source C produces identical instruction structure + size but with the
 * register-numbering shifted by 1, see docs/per_fn_matching_strategy.md
 * §14.3). The leaf getters remain C-matched. extab/extabindex entries are
 * manually emitted via `.extab_user`/`.extabindex_user` sections
 * (tools/postprocess_extab_user.py renames them).
 */

extern void fn_80278FD8();
extern void memset();

/* --- forward decls for asm fns (so extabindex can reference them) --- */
asm void bitpack_write_field(void);
asm void bitpack_init(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_bitpack_write_field[8] = {
    0x30, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
__declspec(section ".extab_user") static const unsigned char extab_bitpack_init[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_bitpack_write_field = {
    (void *)&bitpack_write_field, 0x0000014C, (void *)extab_bitpack_write_field
};
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_bitpack_init = {
    (void *)&bitpack_init, 0x000000C4, (void *)extab_bitpack_init
};

/* --- asm function: bitpack_write_field @ 0x80088A5C, size 0x14C --- */
asm void bitpack_write_field(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r26, 0x8(r1)
    li r29, 0x0
    mr r30, r3
    mr r31, r4
    mr r26, r5
    mr r27, r6
    mr r28, r29
    b bitpack_write_field_L_80088AB4
bitpack_write_field_L_80088A88:
    lwz r4, 0x0(r30)
    mr r3, r26
    lwzx r4, r4, r28
    bl fn_80278FD8
    cntlzw r0, r3
    extrwi r0, r0, 8, 19
    cmplwi r0, 0x1
    bne bitpack_write_field_L_80088AAC
    b bitpack_write_field_L_80088AC4
bitpack_write_field_L_80088AAC:
    addi r28, r28, 0x10
    addi r29, r29, 0x1
bitpack_write_field_L_80088AB4:
    lwz r0, 0x4(r30)
    cmpw r29, r0
    blt bitpack_write_field_L_80088A88
    li r29, -0x1
bitpack_write_field_L_80088AC4:
    cmpwi r29, 0x0
    bge bitpack_write_field_L_80088AD4
    li r3, 0x0
    b bitpack_write_field_L_80088B94
bitpack_write_field_L_80088AD4:
    lwz r3, 0x0(r30)
    slwi r0, r29, 4
    lwz r4, 0x8(r30)
    add r3, r3, r0
    lwz r0, 0x8(r3)
    cmpw r27, r0
    bge bitpack_write_field_L_80088B7C
    lwz r0, 0x4(r3)
    addi r5, r27, 0x1
    lwz r6, 0xc(r3)
    mr r11, r31
    mullw r0, r5, r0
    li r9, 0x0
    add r10, r6, r0
    b bitpack_write_field_L_80088B70
bitpack_write_field_L_80088B10:
    subi r10, r10, 0x1
    clrlwi r0, r11, 31
    slwi r5, r10, 29
    li r7, 0x1
    srwi r6, r10, 31
    srawi r8, r10, 3
    subf r5, r6, r5
    cmplwi r0, 0x1
    rotlwi r0, r5, 3
    addze r8, r8
    add r0, r0, r6
    subfic r0, r0, 0x7
    slw r0, r7, r0
    clrlwi r5, r0, 24
    bne bitpack_write_field_L_80088B5C
    lbzx r0, r4, r8
    or r0, r0, r5
    stbx r0, r4, r8
    b bitpack_write_field_L_80088B68
bitpack_write_field_L_80088B5C:
    lbzx r0, r4, r8
    andc r0, r0, r5
    stbx r0, r4, r8
bitpack_write_field_L_80088B68:
    srwi r11, r11, 1
    addi r9, r9, 0x1
bitpack_write_field_L_80088B70:
    lwz r0, 0x4(r3)
    cmpw r9, r0
    blt bitpack_write_field_L_80088B10
bitpack_write_field_L_80088B7C:
    lbz r0, 0xc(r30)
    cmplwi r0, 0x0
    bne bitpack_write_field_L_80088B90
    li r3, 0x0
    b bitpack_write_field_L_80088B94
bitpack_write_field_L_80088B90:
    li r3, 0x1
bitpack_write_field_L_80088B94:
    lmw r26, 0x8(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

/* --- C function: bitpack_get_used_bytes @ 0x80088BA8 (leaf accessor) --- */
unsigned int bitpack_get_used_bytes(int self) {
    return *(unsigned int *)(self + 0x14);
}

/* --- C function: bitpack_get_used_bits @ 0x80088BB0 (leaf accessor) --- */
unsigned int bitpack_get_used_bits(int self) {
    return *(unsigned int *)(self + 0x10);
}

/* --- asm function: bitpack_init @ 0x80088BB8, size 0xC4 --- */
asm void bitpack_init(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    li r9, 0x0
    li r10, 0x0
    stw r0, 0x14(r1)
    li r8, 0x0
    stw r31, 0xc(r1)
    mr r31, r3
    stw r4, 0x0(r3)
    stw r5, 0x4(r3)
    stw r6, 0x8(r3)
    stb r7, 0xc(r3)
    b bitpack_init_L_80088C18
bitpack_init_L_80088BEC:
    lwz r3, 0x0(r31)
    addi r0, r8, 0xc
    addi r10, r10, 0x1
    stwx r9, r3, r0
    lwz r0, 0x0(r31)
    add r4, r0, r8
    addi r8, r8, 0x10
    lwz r3, 0x4(r4)
    lwz r0, 0x8(r4)
    mullw r0, r3, r0
    add r9, r9, r0
bitpack_init_L_80088C18:
    lwz r0, 0x4(r31)
    cmpw r10, r0
    blt bitpack_init_L_80088BEC
    stw r9, 0x10(r31)
    lwz r4, 0x10(r31)
    neg r3, r4
    srawi r0, r4, 3
    or r3, r3, r4
    srwi r3, r3, 31
    addze r0, r0
    add r0, r0, r3
    stw r0, 0x14(r31)
    lbz r0, 0xc(r31)
    cmplwi r0, 0x1
    bne bitpack_init_L_80088C64
    lwz r3, 0x8(r31)
    li r4, 0x0
    lwz r5, 0x14(r31)
    bl memset
bitpack_init_L_80088C64:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
