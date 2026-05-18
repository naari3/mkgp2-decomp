/*
 * TCPConn_AllocTxBuffer: scans the 6-slot g_mediaBuffers pool for a slot
 * whose busy flag is clear and pointer is non-NULL, marks it busy, zero-
 * fills the 0xA000-byte buffer, and returns the buffer pointer. Writes
 * 0xA000 to *out_size on success, 0 on exhaustion (when out_size != NULL).
 *
 * Held as asm_fn: CW132 reaches 91.1% (16/180 bytes) but cannot reproduce
 * the target's register-allocator choice in the memset preamble. Target
 * coalesces the slot base pointer directly into r31 and uses `lwzu r3,
 * 0x4(r31)` (load-with-update) so the post-memset reload becomes `lwz r3,
 * 0x0(r31)`. Every C rephrasing of the same expression
 *   ((void **)g_mediaBuffers)[i * 2 + 1]
 * keeps the base in a scratch r6, materialises r31 = slot+4 with a
 * separate `addi r31, r6, 4`, and emits a plain `lwz r3, 0x4(r6)` instead
 * of `lwzu`. Pulling the pointer into a `void **slot_addr` local would
 * trigger CSE that demotes the flag-set `stbx r0, r4, r5` to a precomputed
 * `stb r0, 0(r5)`, dropping the score further. Same scheduling family as
 * FreeMediaBuffers (also asm_fn).
 *
 * The target carries an extab record (size 0x8 at 0x80008E9C) and an
 * extabindex entry (size 0xC at 0x800219B0) even though the body itself
 * cannot throw, matching the rest of the TCPConn family compiled with
 * exceptions on.
 */

extern unsigned char g_mediaBuffers[0x30];

extern void *memset(void *dst, int c, unsigned int n);

asm void *TCPConn_AllocTxBuffer(unsigned int *out_size);

/* --- extab (manual emit, .extab_user -> extab via postprocess_extab_user) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_TCPConn_AllocTxBuffer[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via postprocess) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_TCPConn_AllocTxBuffer = {
    (void *)&TCPConn_AllocTxBuffer, 0x000000C0, (void *)extab_TCPConn_AllocTxBuffer
};

asm void *TCPConn_AllocTxBuffer(unsigned int *out_size) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, g_mediaBuffers@ha
    li r5, 0x0
    stw r0, 0x14(r1)
    li r0, 0x6
    addi r4, r4, g_mediaBuffers@l
    stw r31, 0xc(r1)
    mtctr r0
TCPConn_AllocTxBuffer_L_800879A4:
    lbz r0, 0x0(r4)
    cmplwi r0, 0x0
    bne TCPConn_AllocTxBuffer_L_80087A0C
    lwz r0, 0x4(r4)
    cmplwi r0, 0x0
    beq TCPConn_AllocTxBuffer_L_80087A0C
    lis r4, g_mediaBuffers@ha
    cmplwi r3, 0x0
    slwi r5, r5, 3
    li r0, 0x1
    addi r4, r4, g_mediaBuffers@l
    stbx r0, r4, r5
    beq TCPConn_AllocTxBuffer_L_800879E4
    lis r4, 0x1
    subi r0, r4, 0x6000
    stw r0, 0x0(r3)
TCPConn_AllocTxBuffer_L_800879E4:
    lis r4, g_mediaBuffers@ha
    lis r3, 0x1
    addi r0, r4, g_mediaBuffers@l
    add r31, r0, r5
    subi r5, r3, 0x6000
    lwzu r3, 0x4(r31)
    li r4, 0x0
    bl memset
    lwz r3, 0x0(r31)
    b TCPConn_AllocTxBuffer_L_80087A2C
TCPConn_AllocTxBuffer_L_80087A0C:
    addi r4, r4, 0x8
    addi r5, r5, 0x1
    bdnz TCPConn_AllocTxBuffer_L_800879A4
    cmplwi r3, 0x0
    beq TCPConn_AllocTxBuffer_L_80087A28
    li r0, 0x0
    stw r0, 0x0(r3)
TCPConn_AllocTxBuffer_L_80087A28:
    li r3, 0x0
TCPConn_AllocTxBuffer_L_80087A2C:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
