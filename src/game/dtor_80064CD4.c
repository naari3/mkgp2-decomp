/*
 * Owner-of-pointer dtor @ 0x80064CD4 (size 0x54).
 *
 * Frees a single heap-allocated member pointer stored at offset 0
 * of `this`, then optionally frees `this` itself when the C++ ABI
 * delete-flag (`flag > 0`) is set. NOT the trivial vtable-demote
 * pattern (which only forwards `this`); this dtor performs two
 * sequential `MemoryManager_TimedFree` (= MemoryManager_TimedFree) calls and
 * therefore saves r30-r31 (Saved GPR range r30-r31, Large Frame:
 * Yes; see auto_dtor_80064CD4_text.s extab body).
 *
 * Approach: `#pragma exceptions on` lets CW 1.3.2 auto-emit the
 * matching extab (0x80007F1C, size 0x8) and extabindex (0x80020E70,
 * size 0xC) entries. Orphan stub: no xrefs surfaced in callers,
 * placeholder name (`dtor_80064CD4`) is kept until caller-side
 * context appears.
 */

extern void MemoryManager_TimedFree(void *p);

#pragma exceptions on
void *dtor_80064CD4(void *this, short flag) {
    if (this != 0) {
        MemoryManager_TimedFree(*(void **)this);
        if (flag > 0) {
            MemoryManager_TimedFree(this);
        }
    }
    return this;
}
#pragma exceptions reset
