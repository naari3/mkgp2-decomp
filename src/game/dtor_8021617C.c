/*
 * Trivial deleting destructor @ 0x8021617C (size 0x48, 18 instr).
 *
 * Same generic CW C++ ABI deleting-dtor shape as ObjectBase_Dtor
 * (src/game/ObjectBase.c, dtor_8002CDF4) and the other sibling dtors
 * (SceneRender / CourseAuxClass / CardTaskWelcome / BtMode):
 *   1. if (this != NULL) demote *this to the parent vtable
 *      (&lbl_804EDB28). Parent class owner not yet identified, so the
 *      function name is kept as placeholder dtor_8021617C.
 *   2. if the short flag arg is > 0, call dtor_8003AFB8(this)
 *      (= MemoryManager_TimedFree placeholder) to free the storage.
 *   3. return this in r3 for downstream `bl <this dtor>` chains.
 *
 * Built with CW 1.3.2 + #pragma exceptions on so the matching extab
 * body (Large Frame: Yes / Saved GPR: r31, 0x08080000 / 0x00000000)
 * and extabindex entry auto-emit alongside the .text body.
 *
 * The flag arg is sign-extended (`extsh. r0, r4`) before the > 0
 * compare, which matches a `short` source-level parameter.
 *
 * extab @ 0x8001A50C-0x8001A514, extabindex @ 0x8002A068-0x8002A074.
 */

extern void dtor_8003AFB8(void *);
extern char lbl_804EDB28[];  /* parent-class vtable @ 0x804EDB28 */

#pragma exceptions on
void *dtor_8021617C(void *this, short flag) {
    if (this != 0) {
        *(char **)this = lbl_804EDB28;
        if (flag > 0) {
            dtor_8003AFB8(this);
        }
    }
    return this;
}
#pragma exceptions reset
