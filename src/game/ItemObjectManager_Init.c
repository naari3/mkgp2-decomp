/*
 * ItemObjectManager_Init @ 0x800D81E0 size 0xA8 (game lib, CW 1.3.2 +
 *   -Cpp_exceptions on).
 *
 * Init routine for the 256-entry item-object slot pool at lbl_80638300
 * (stride 0x1EC bytes/slot, total 0x1EC00 = 126KB). For each slot:
 *   memset(slot, 0, 0x1EC);
 *
 * After zeroing the pool:
 *   - Alloc(0x5C) a clNormal3D instance, init via clNormal3D_Construct
 *     against the resource pointer at lbl_8041BC00 + 0xab4 (= 0x8041C6B4),
 *     useSkinModel = 1.
 *   - Store the constructed instance at lbl_80656F00 (= lbl_80638300 +
 *     0x1EC00, just past the slot array; CW emits @ha + @l + addis +0x2
 *     + stw -0x1400 because 0x1EC00 doesn't fit in 16-bit @l).
 *   - Call fn_800AF46C (AnimStatePool_ZeroInit per Ghidra plate).
 *   - Stamp lbl_80656F04 = 0.
 *   - Call fn_800D8D8C (ItemHitRegistry_Reset per Ghidra plate).
 *
 * Shape decision: asm_fn retreat.
 *
 *   The orig extab carries a DELETEPOINTER PC action at pc=0x64 (= the
 *   `bl clNormal3D_Construct` site) with ptr=r30, dtor=dtor_8003AFB8
 *   (= MemoryManager_TimedFree). That's a C++ unwind cleanup-on-throw
 *   artefact: if the call site throws, free the freshly Alloc'd block.
 *   There is no plain-C surface form for emitting this kind of PC-action
 *   extab -- `new T` semantics with a non-trivial ctor would, but Alloc /
 *   Construct are both plain C entry points (no operator new overload
 *   visible in target). So matched the DMAChannelManager_Init pattern:
 *   asm void body + manual extab/extabindex emit. byte-identical SHA-1.
 *
 *   `fn_800AF46C` and `fn_800D8D8C` are left unrenamed (Ghidra plate
 *   calls them AnimStatePool_ZeroInit / ItemHitRegistry_Reset but the
 *   semantics are not yet verified in this repo; future rename pass).
 *
 * The extab/extabindex are emitted into .extab_user / .extabindex_user
 * sections; tools/postprocess_extab_user.py renames the named symbols
 * (extab_xxx / extabindex_xxx) into the @etb_<addr> / @eti_<addr>
 * dtk dol split expects. configure.py wires this TU with
 *   extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]
 * to route through the mwcc_sjis_extab rule (= runs the postprocess
 * hook) and reserve the right alignment for the manual emit.
 *
 * Generated baseline via `python tools/extract_fn_asm.py
 * auto_ItemObjectManager_In_text`.
 */

/* --- extern decls: branch callees (bl/b targets) --- */
extern void Alloc();
extern void clNormal3D_Construct();
extern void fn_800AF46C();
extern void fn_800D8D8C();
extern void memset();

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
extern unsigned int lbl_8041BC00[];
extern unsigned int lbl_80638300[];

/* --- forward decls --- */
asm void ItemObjectManager_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void dtor_8003AFB8();

/* --- extab (manual emit, .extab_user -> extab via objcopy) ---
 * Mirror of:
 *   .obj @etb_8000B334 (size 0x18) Saved GPR r30-r31 + DELETEPOINTER @
 *                                   pc=0x64 ptr=r30 dtor=dtor_8003AFB8
 *   .obj @eti_800239FC (size 0xC)  -> ItemObjectManager_Init /
 *                                      extab_ItemObjectManager_Init
 *
 * Bytes verified vs build/GNLJ82/asm/auto_ItemObjectManager_In_text.s.
 */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    unsigned int f3;
    unsigned int f4;
    void *f5;
} extab_ItemObjectManager_Init = {
    0x10080000,            /* header: Saved GPR r30-r31, Large Frame */
    0x00000064,            /* PC range end (covers Alloc + Construct site) */
    0x00000010,            /* action @ 0x10 */
    0x00000000,            /* pad */
    0x8A80001E,            /* DELETEPOINTER + end bit, ptr=r30 */
    (void *)&dtor_8003AFB8
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_ItemObjectManager_Init = {
    (void *)&ItemObjectManager_Init, 0x000000A8,
    (void *)&extab_ItemObjectManager_Init
};

/* --- asm function body --- */
asm void ItemObjectManager_Init(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r3, lbl_80638300@ha
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    li r31, 0x0
    stw r30, 0x8(r1)
    addi r30, r3, lbl_80638300@l
ItemObjectManager_Init_L_800D8200:
    mr r3, r30
    li r4, 0x0
    li r5, 0x1ec
    bl memset
    addi r31, r31, 0x1
    addi r30, r30, 0x1ec
    cmpwi r31, 0x100
    blt ItemObjectManager_Init_L_800D8200
    li r3, 0x5c
    bl Alloc
    mr. r30, r3
    beq ItemObjectManager_Init_L_800D8244
    lis r4, lbl_8041BC00@ha
    li r5, 0x1
    addi r4, r4, lbl_8041BC00@l
    lwz r4, 0xab4(r4)
    bl clNormal3D_Construct
ItemObjectManager_Init_L_800D8244:
    lis r3, lbl_80638300@ha
    addi r3, r3, lbl_80638300@l
    addis r3, r3, 0x2
    stw r30, -0x1400(r3)
    bl fn_800AF46C
    lis r3, lbl_80638300@ha
    li r0, 0x0
    addi r3, r3, lbl_80638300@l
    addis r3, r3, 0x2
    stw r0, -0x13fc(r3)
    bl fn_800D8D8C
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
