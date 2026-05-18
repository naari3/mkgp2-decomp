/*
 * ResetIOPorts @ 0x80084FF0 (size 0xC0).
 *
 * Scans the 4 PCB port descriptor structs starting at lbl_805A6154 (stride
 * 0xA3C each, total 0x28F0). For every port whose header byte (offset 0)
 * carries the local PCB role in bits [4:6] (the `(hdr >> 4) & 7` field),
 * stamps the port's status byte (offset 0xA35) with `(status & 0x80) | 0x40`
 * -- preserve bit 7, write 0x40 into bits [0:6] ("reset" state).
 *
 * Early-out: g_localPcbRole == 0 -> return 0. Otherwise refresh the cached
 * display context with `g_myPcbId - 1` and return 1.
 *
 * Cross-TU callers exist (auto_fn_801F2B70, auto_FrameSelection_Updat), so
 * symbol scope must be global.
 *
 * Held as asm_fn (Phase 1b). CW 1.3.2 codegen plateaus at 80.71% C-match:
 *   - target uses `lbzu r0, 0xa3c(r4)` (pre-update load) across all 4 ports
 *     by keeping r4 walking; CW collapses `p++` into base+cumulative-disp
 *     encoding instead, except for the very first iteration.
 *   - target hoists `li r3, 0x40` once and reuses it via 4
 *     `rlwimi r0, r3, 0, 25, 31`; CW emits `clrrwi/ori` (or `rlwinm/ori`)
 *     per-iteration even when written as `(a & ~0x7F) | (low_bits & 0x7F)`.
 * Both behaviours are CW132 scheduling/peephole choices that we could not
 * coax with statement re-ordering, struct vs raw pointer, `p++` vs
 * `(char*)p + 0xA3C`, or loop-form unroll. asm_fn preserves byte-identity
 * while leaving room to revisit (the C form above lives in this comment).
 *
 * Carries an 8-byte extab (Large Frame, no other flags) + 12-byte extabindex
 * entry. Both manually emitted via the project's .extab_user /
 * .extabindex_user pipeline (mirrors SyncSlot.c).
 */

extern int g_localPcbRole;
extern int g_myPcbId;
extern unsigned char lbl_805A6154[0x28F0];
extern void *lbl_806D11B0;
extern void GetDisplayContext(int pcbIndex);

asm void ResetIOPorts(void);

/* --- extab (manual emit, .extab_user -> extab via postprocess_extab_user) ---
 * Mirror of target @etb_80008D7C: 8 bytes, "Large Frame: Yes" flag only,
 * no Elf vector / no SR / no frame pointer / no PC ranges.
 *   0x00080000   flag word (Large Frame bit set, no ranges)
 *   0x00000000   terminator
 */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ResetIOPorts[8] = {
    0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via postprocess) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_ResetIOPorts = {
    (void *)&ResetIOPorts, 0x000000C0, (void *)extab_ResetIOPorts
};

asm void ResetIOPorts(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    lwz r0, g_localPcbRole(r13)
    cmpwi r0, 0x0
    bne ResetIOPorts_L_80085010
    li r3, 0x0
    b ResetIOPorts_L_800850A0
ResetIOPorts_L_80085010:
    lwz r3, g_myPcbId(r13)
    subi r3, r3, 0x1
    bl GetDisplayContext
    lis r4, lbl_805A6154@ha
    lbzu r0, lbl_805A6154@l(r4)
    lwz r5, g_localPcbRole(r13)
    extrwi r0, r0, 3, 25
    stw r3, lbl_806D11B0(r13)
    cmpw r0, r5
    li r3, 0x40
    bne ResetIOPorts_L_80085048
    lbz r0, 0xa35(r4)
    rlwimi r0, r3, 0, 25, 31
    stb r0, 0xa35(r4)
ResetIOPorts_L_80085048:
    lbzu r0, 0xa3c(r4)
    extrwi r0, r0, 3, 25
    cmpw r0, r5
    bne ResetIOPorts_L_80085064
    lbz r0, 0xa35(r4)
    rlwimi r0, r3, 0, 25, 31
    stb r0, 0xa35(r4)
ResetIOPorts_L_80085064:
    lbzu r0, 0xa3c(r4)
    extrwi r0, r0, 3, 25
    cmpw r0, r5
    bne ResetIOPorts_L_80085080
    lbz r0, 0xa35(r4)
    rlwimi r0, r3, 0, 25, 31
    stb r0, 0xa35(r4)
ResetIOPorts_L_80085080:
    lbzu r0, 0xa3c(r4)
    extrwi r0, r0, 3, 25
    cmpw r0, r5
    bne ResetIOPorts_L_8008509C
    lbz r0, 0xa35(r4)
    rlwimi r0, r3, 0, 25, 31
    stb r0, 0xa35(r4)
ResetIOPorts_L_8008509C:
    li r3, 0x1
ResetIOPorts_L_800850A0:
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
