/*
 * InputObj deleting destructor @ 0x800395EC (size 0x60, 24 instr).
 *
 * CW C++ ABI deleting destructor for the InputObject class. Mirrors
 * ObjectBase_Dtor (0x8002CDF4) but with two extra moves:
 *   1. if (this != NULL) demote *this back to the InputObject vtable
 *      (&g_InputObjectVtable @ 0x803F5754) so any subsequent virtual
 *      dispatch sees a cleanly typed base subobject.
 *   2. invoke the InputObject member finalizer fn_80039AC4(this, 0)
 *      to release member-owned resources before the alloc is freed.
 *   3. if the second arg (delete-flag, passed as a short) is > 0, call
 *      `dtor_8003AFB8(this)` (= MemoryManager_TimedFree) to release the
 *      allocation. Otherwise leave the storage alive (subobject dtor
 *      called from a parent dtor chain).
 *   4. return this in r3 (this is what makes downstream `bl <this dtor>`
 *      chains work with the C++ ABI deleting-dtor convention).
 *
 * Frame layout differs from ObjectBase_Dtor: this dtor calls a helper
 * (fn_80039AC4) between the NULL check and the conditional free, so the
 * `this` pointer and the `flag` argument must both survive across that
 * call -> they spill to r30 and r31 respectively, producing the
 * `Saved GPR range: r30-r31` extab entry (0x10080000 / 0x00000000).
 *
 * Same shape as the other small deleting dtors in this lib: CW 1.3.2 +
 * #pragma exceptions on auto-emits the matching extab body.
 *
 * The flag argument is sign-extended (`extsh. r0, r31`) before the > 0
 * check, which matches a `short` parameter type at the source level.
 */

extern void fn_80039AC4(void *, int);
extern void dtor_8003AFB8(void *);
extern char g_InputObjectVtable[]; /* InputObject vtable @ 0x803F5754 */

#pragma exceptions on
void *InputObj_Ctor(void *this, short flag) {
    if (this != 0) {
        *(char **)this = g_InputObjectVtable;
        fn_80039AC4(this, 0);
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
#pragma exceptions reset
