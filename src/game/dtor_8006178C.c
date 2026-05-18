/*
 * Trivial deleting destructors @ 0x8006178C / 0x800617C8 (each size 0x3C, 15 instr).
 *
 * Two byte-identical CW C++ ABI trivial deleting dtors generated per
 * vtable instance. Each dispatches to `MemoryManager_TimedFree` when the second
 * argument (the delete-flag) is positive, otherwise it just returns
 * `this`. Same pattern as dtor_80036988 / dtor_80036E40 (commit fb9a2cf)
 * and dtor_8024F40C (commit dd3a581).
 *
 * The two functions are immediately adjacent (0x8006178C + 0x3C =
 * 0x800617C8) with no wedge in between, so a single TU with one
 * contiguous .text / extab / extabindex range works.
 *
 * Approach B inverse (`#pragma exceptions on` / `reset`): CW 1.3.2 auto-
 * emits the matching extab body (Large Frame: Yes / Saved GPR: r31) when
 * exceptions are enabled, so no manual extab/extabindex emission needed.
 */

extern void MemoryManager_TimedFree(void *);

#pragma exceptions on
void *dtor_8006178C(void *this, short flag) {
    if (this != 0) {
        if (flag > 0) {
            MemoryManager_TimedFree(this);
        }
    }
    return this;
}

void *dtor_800617C8(void *this, short flag) {
    if (this != 0) {
        if (flag > 0) {
            MemoryManager_TimedFree(this);
        }
    }
    return this;
}
#pragma exceptions reset
