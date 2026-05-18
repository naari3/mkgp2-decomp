/*
 * Trivial deleting destructor @ 0x80036988 (size 0x3C, 15 instr).
 *
 * Body is byte-identical to dtor_80036E40 but the binary contains two
 * separate instances (referenced from distinct vtables), so each lives in
 * its own TU. The pair sits across a wedge (QuadFrame_FromPackedCorners/QuadFrame_FromCornerPtrs carry
 * extabindex entries between them) so a single TU with two disjoint .text
 * ranges would trigger a dtk cyclic-dependency error.
 *
 * CW 1.3.2 + `#pragma exceptions on` auto-emits the matching extab body
 * (Large Frame: Yes / Saved GPR: r31), so no manual extab/extabindex emit
 * is required for this singleton dtk extab group.
 */

extern void dtor_8003AFB8(void *);

#pragma exceptions on
void *dtor_80036988(void *this, short flag) {
    if (this != 0) {
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
#pragma exceptions reset
