/*
 * DMAChannelManager_Init @ 0x800662B4 size 0x9C (game lib, CW 1.3.2 +
 *   -Cpp_exceptions on).
 *
 * Init routine for the 32-entry transparent-draw slot pool at
 * lbl_805987E0 (stride 0x14 = 5 ints). For each slot:
 *   - if slot.id (offset 0) != -1, reset id=-1 and slot[3]=5
 *   - Alloc(0x84) a per-slot object, store ptr at slot[4]
 *   - if alloc succeeded, call TransparentDraw_ResetEntry (TransparentDraw_ResetEntry)
 *     to prime the freshly allocated 0x84-byte struct
 *
 * Finally sets a few globals (lbl_806CEF20=8, lbl_806D10F4=0,
 * lbl_806D10F8=0) and stamps lbl_806D10F0=1 as init-done gate (re-entry
 * via the early-out at the top of the function).
 *
 * Shape decision: asm_fn retreat.
 *
 *   The orig extab carries a DELETEPOINTER PC action at pc=0x58 (= the
 *   `bl TransparentDraw_ResetEntry` site) with ptr=r27, dtor=
 *   MemoryManager_TimedFree (= MemoryManager_TimedFree). That's a C++ unwind
 *   cleanup-on-throw artefact: if the call site throws, free the
 *   freshly Alloc'd block via the memory manager. There is no plain-C
 *   surface form for emitting this kind of PC-action extab -- `new T`
 *   semantics with a non-trivial ctor would, but Alloc / Reset are both
 *   plain C entry points (no operator new overload visible in target).
 *   So matched the InputMgr_Init / HeapStats pattern: asm void body +
 *   manual extab/extabindex emit. byte-identical SHA-1.
 *
 *   `TransparentDraw_ResetEntry` is TransparentDraw_ResetEntry (not renamed here to
 *   keep the asm body matching the symbols.txt name dtk dol split
 *   currently emits; future rename pass can flip both at once).
 *
 * The extab/extabindex are emitted into .extab_user / .extabindex_user
 * sections; tools/postprocess_extab_user.py renames the named symbols
 * (extab_xxx / extabindex_xxx) into the @etb_<addr> / @eti_<addr>
 * dtk dol split expects. configure.py wires this TU with
 *   extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]
 * to route through the mwcc_sjis_extab rule (= runs the postprocess
 * hook) and reserve the right alignment for the manual emit.
 */

extern void *Alloc(int size);
extern void TransparentDraw_ResetEntry(void *self); /* TransparentDraw_ResetEntry */
extern void MemoryManager_TimedFree(void *p);  /* MemoryManager_TimedFree */

/* sda1 globals (sdata / sbss residents). mwcc inline-asm syntax
 * `<sym>(r13)` -> auto sda21 reloc requires the symbol to be visible
 * as data; declare as `unsigned int` array so the linker keeps the
 * sda21 path. (See HeapStats.c / InputMgr.c for the same idiom.) */
extern unsigned int lbl_805987E0[];
extern unsigned int lbl_806CEF20;
extern unsigned int lbl_806D10F0;
extern unsigned int lbl_806D10F4;
extern unsigned int lbl_806D10F8;

/* forward decl for manual extab emit */
asm void DMAChannelManager_Init(void);

/* --- manual extab/extabindex emit ---
 * Mirror of:
 *   .obj @etb_800080D8 (size 0x18) Saved GPR r27-r31 + DELETEPOINTER @
 *                                   pc=0x58 ptr=r27 dtor=MemoryManager_TimedFree
 *   .obj @eti_80020FC0 (size 0xC)  -> DMAChannelManager_Init /
 *                                      extab_DMAChannelManager_Init
 *
 * Bytes verified vs build/GNLJ82/asm/auto_DMAChannelManager_In_text.s.
 */
#pragma section R ".extab_user"

__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    unsigned int f3;
    unsigned int f4;
    void *f5;
} extab_DMAChannelManager_Init = {
    0x28080000,            /* header: Saved GPR r27-r31, Large Frame */
    0x00000058,            /* PC range end (covers entire body) */
    0x00000010,            /* action @ 0x10 */
    0x00000000,            /* pad */
    0x8A80001B,            /* DELETEPOINTER + end bit, ptr=r27 */
    (void *)&MemoryManager_TimedFree
};

#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_DMAChannelManager_Init = {
    (void *)&DMAChannelManager_Init, 0x0000009C,
    (void *)&extab_DMAChannelManager_Init
};

/* --- asm function body --- */

asm void DMAChannelManager_Init(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    lbz r0, lbl_806D10F0(r13)
    cmplwi r0, 0x1
    beq DMAChannelManager_Init_L_8006633C
    lis r3, lbl_805987E0@ha
    li r28, 0x0
    addi r29, r3, lbl_805987E0@l
    li r30, -0x1
    li r31, 0x5
DMAChannelManager_Init_L_800662E4:
    lwz r0, 0x0(r29)
    cmpwi r0, -0x1
    beq DMAChannelManager_Init_L_800662F8
    stw r30, 0x0(r29)
    stw r31, 0xc(r29)
DMAChannelManager_Init_L_800662F8:
    li r3, 0x84
    bl Alloc
    mr. r27, r3
    beq DMAChannelManager_Init_L_8006630C
    bl TransparentDraw_ResetEntry
DMAChannelManager_Init_L_8006630C:
    addi r28, r28, 0x1
    stw r27, 0x10(r29)
    cmpwi r28, 0x20
    addi r29, r29, 0x14
    blt DMAChannelManager_Init_L_800662E4
    li r3, 0x0
    li r4, 0x8
    li r0, 0x1
    stw r4, lbl_806CEF20(r13)
    stw r3, lbl_806D10F4(r13)
    stw r3, lbl_806D10F8(r13)
    stb r0, lbl_806D10F0(r13)
DMAChannelManager_Init_L_8006633C:
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
