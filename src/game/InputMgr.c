/*
 * InputMgr TU expansion (game lib, CW 1.3.2 + -Cpp_exceptions on).
 *
 * Covers the contiguous range 0x8003907C..0x80039154 (3 fns) and the
 * matching extab @ 0x80005DF8..0x80005E28 / extabindex @ 0x8001FA60..
 * 0x8001FA78 ranges that dtk dol split detected as orphaned when only
 * the .text slice was claimed.
 *
 * Function map:
 *   GetInputManager      @ 0x8003907C size 0x08 (no extab)
 *   InputMgr_Shutdown    @ 0x80039084 size 0x64 (extab 0x8, Saved-GPR r31)
 *   InputMgr_Init        @ 0x800390E8 size 0x6C (extab 0x28, Saved-GPR
 *                                                r30-r31 + DELETEPOINTER
 *                                                cleanup of mgr + obj
 *                                                via MemoryManager_TimedFree)
 *
 * Shape decisions:
 *
 *   GetInputManager is the pre-existing matched trivial getter; kept as C.
 *
 *   InputMgr_Shutdown: target prologue loads g_inputManager *directly*
 *     into r31 (the eventual home for the saved-mgr value), and the
 *     vtable[+0x8] dispatch loads via `lwz r12, 0x0(r3); lwz r12, 0x8(r12)`
 *     (i.e. reuses r12 for both indirections). The CW 1.3.2 register
 *     allocator under any plain-C formulation we tried picks r3 as the
 *     load destination, then mr's into r31 (extra `mr r31, r3` insn) and
 *     dispatches via `lwz r5, 0x0(r3); lwz r12, 0x8(r5)`. The shape diff
 *     is the same family as docs/notes/cw132-fp-decl-order-regalloc.md.
 *     Retreat to `asm void` keeps the bundle progress and the auto-emit
 *     of the matching 8-byte extab is unnecessary -- the manual emit
 *     below covers it.
 *
 *   InputMgr_Init: the orig extab carries a DELETEPOINTER cleanup chain
 *     (`mgr` then `obj`, both dtor=MemoryManager_TimedFree). That's an artifact of
 *     C++ `new T()` semantics with cleanup-on-throw, which has no plain-C
 *     surface form -- a try/catch is also not expressible since the asm
 *     contains no exception-region branches (the extab is descriptive-
 *     only for unwinder). Retreat to `asm void` + manual extab emit is
 *     the right shape (mirror of game/ItemSelect.c::ItemSelect_Init).
 *
 * The extab/extabindex are emitted into .extab_user / .extabindex_user
 * sections; tools/postprocess_extab_user.py renames the named symbols
 * (extab_xxx / extabindex_xxx) into the @etb_<addr> / @eti_<addr>
 * dtk dol split expects. configure.py wires this TU with
 *   extab_padding=b"\x00\x00", extra_cflags=["-Cpp_exceptions on"]
 * to route through the mwcc_sjis_extab rule (= runs the postprocess
 * hook) and reserve the right alignment for the manual emit.
 */

struct InputObject;

extern struct InputObject **g_inputManager;
extern void *Alloc(int size);
extern void MemoryManager_TimedFree(void *p);
extern void InputMgr_TeardownStub(void);
extern void JvsInput_ResetCalibration(void);
extern void *InputObj_Ctor_Internal(void *self, int arg);

/* forward decls for manual extab emit */
asm void InputMgr_Shutdown(void);
asm void InputMgr_Init(void);

#pragma exceptions off

struct InputObject **GetInputManager(void) {
    return g_inputManager;
}

/* --- manual extab/extabindex emit ---
 * Mirror of:
 *   .obj @etb_80005DF8 (size 0x8)  Saved GPR r31
 *   .obj @etb_80005E00 (size 0x28) Saved GPR r30-r31, DELETEPOINTER chain
 *   .obj @eti_8001FA60 (size 0xC)  -> InputMgr_Shutdown / extab_InputMgr_Shutdown
 *   .obj @eti_8001FA6C (size 0xC)  -> InputMgr_Init     / extab_InputMgr_Init
 *
 * Source byte order = target section layout (Shutdown first, then Init).
 * Bytes verified vs build/GNLJ82/asm/game/InputMgr.s extab section.
 */
#pragma section R ".extab_user"

__declspec(section ".extab_user") static const unsigned int extab_InputMgr_Shutdown[2] = {
    0x08080000, 0x00000000
};

/* Init extab carries a 5-field action descriptor + 2 DELETEPOINTER
 * actions (the last one carries the end bit). Layout from
 * build/GNLJ82/asm/game/InputMgr.s @etb_80005E00:
 *   0x10080000  -- header: Saved GPR r30-r31, Large Frame, 0 elf vec
 *   0x00000034  -- PC range end 0x34 (alloc(mgr) call site)
 *   0x00020020  -- next PC end implicit, action @ 0x20
 *   0x0000004C  -- PC range end 0x4C
 *   0x00000018  -- action @ 0x18
 *   0x00000000  -- pad
 *   0x0A80001E  -- DELETEPOINTER action, ptr=r30
 *   MemoryManager_TimedFree
 *   0x8A80001F  -- DELETEPOINTER + end, ptr=r31
 *   MemoryManager_TimedFree
 */
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    unsigned int f3;
    unsigned int f4;
    unsigned int f5;
    unsigned int f6;
    void *f7;
    unsigned int f8;
    void *f9;
} extab_InputMgr_Init = {
    0x10080000, 0x00000034, 0x00020020, 0x0000004C, 0x00000018, 0x00000000,
    0x0A80001E, (void *)&MemoryManager_TimedFree,
    0x8A80001F, (void *)&MemoryManager_TimedFree
};

#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_InputMgr_Shutdown = {
    (void *)&InputMgr_Shutdown, 0x00000064, (void *)&extab_InputMgr_Shutdown
};

__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_InputMgr_Init = {
    (void *)&InputMgr_Init, 0x0000006C, (void *)&extab_InputMgr_Init
};

/* --- asm function bodies (.text order = fn address order) --- */

asm void InputMgr_Shutdown(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    lwz r31, g_inputManager(r13)
    cmplwi r31, 0x0
    beq InputMgr_Shutdown_L_800390CC
    lwz r3, 0x0(r31)
    cmplwi r3, 0x0
    beq InputMgr_Shutdown_L_800390C0
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
InputMgr_Shutdown_L_800390C0:
    bl InputMgr_TeardownStub
    mr r3, r31
    bl MemoryManager_TimedFree
InputMgr_Shutdown_L_800390CC:
    li r0, 0x0
    stw r0, g_inputManager(r13)
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

asm void InputMgr_Init(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    lwz r0, g_inputManager(r13)
    cmplwi r0, 0x0
    bne InputMgr_Init_L_8003913C
    li r3, 0x4
    bl Alloc
    mr. r31, r3
    beq InputMgr_Init_L_80039138
    bl JvsInput_ResetCalibration
    li r3, 0x28
    bl Alloc
    mr. r30, r3
    beq InputMgr_Init_L_80039134
    li r4, 0x0
    bl InputObj_Ctor_Internal
InputMgr_Init_L_80039134:
    stw r30, 0x0(r31)
InputMgr_Init_L_80039138:
    stw r31, g_inputManager(r13)
InputMgr_Init_L_8003913C:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

#pragma exceptions reset
