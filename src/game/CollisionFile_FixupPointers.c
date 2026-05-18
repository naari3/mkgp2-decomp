/* CollisionFile_FixupPointers (0x80035220, size 0x48)
 *
 * asm_fn fallback: 6 C-source iterations converged on size 0x48 with
 * the exact instruction structure of the target, but every variant
 * landed with the r5 <-> r6 loop-var / tmp-offset pair swapped vs
 * target. The CW 1.3.2 register allocator picks r6 for the loop var
 * and r5 for the (i + 8) tmp regardless of (in)voluntary declare
 * order, parenthesisation around (i + 8), signed vs unsigned arg, or
 * adding a `v = test_load()` assign-in-condition. With (i + 8)
 * parenthesised the CW switches to a `add r4, r5, r0` /
 * `lwz/stw 0x8(r4)` codegen for the second pointer fix, which
 * diverges from target's `addi r6, r5, 0x8; lwzx ...; stwx ...`
 * indexed-access pattern. Sibling functions in this region
 * (CollisionFile_Load at 0x801F9954) can revisit the C version
 * later by promoting this asm_fn body to plain C if a way to flip
 * the r5/r6 allocation is discovered.
 *
 * Behaviour (C reference for future promotion):
 *   void CollisionFile_FixupPointers(int file_base) {
 *       int *table;
 *       int i;
 *       *(int *)(file_base + 0x28) += file_base;
 *       i = 0;
 *       while (table = *(int **)(file_base + 0x28),
 *              *(unsigned int *)((char *)table + i) != 0) {
 *           *(int *)((char *)table + i) += file_base;
 *           table = *(int **)(file_base + 0x28);
 *           *(int *)((char *)table + i + 8) += file_base;
 *           i += 0x10;
 *       }
 *   }
 */

asm void CollisionFile_FixupPointers(int file_base) {
    nofralloc
    lwz r0, 0x28(r3)
    li r5, 0x0
    add r0, r0, r3
    stw r0, 0x28(r3)
    b _test
_body:
    add r0, r0, r3
    addi r6, r5, 0x8
    stwx r0, r4, r5
    addi r5, r5, 0x10
    lwz r4, 0x28(r3)
    lwzx r0, r4, r6
    add r0, r0, r3
    stwx r0, r4, r6
_test:
    lwz r4, 0x28(r3)
    lwzx r0, r4, r5
    cmplwi r0, 0x0
    bne _body
    blr
}
