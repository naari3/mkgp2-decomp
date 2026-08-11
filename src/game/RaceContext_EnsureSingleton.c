/* === extracted from auto_RaceContext_EnsureSi_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree();

/* --- extern decls: sda21-referenced data --- */
#pragma cplusplus on
struct RaceContext {
    unsigned int vtable;
    RaceContext();
};

extern RaceContext *lbl_806D12DC;
#pragma cplusplus off

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8040E4DC[];

/* --- function index (2 fns, .text 0x8009DC80..0x8009DD28) ---
 * [  0] 0x8009DC80 size:0x60    global RaceContext_EnsureSingleton
 * [  1] 0x8009DCE0 size:0x48    global dtor_8009DCE0
 */

/* --- forward decls --- */
#pragma cplusplus on
extern "C" RaceContext *RaceContext_EnsureSingleton(void);
#pragma cplusplus off
asm void dtor_8009DCE0(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_dtor_8009DCE0[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_dtor_8009DCE0 = {
    (void *)&dtor_8009DCE0, 0x00000048, (void *)extab_dtor_8009DCE0
};

/* --- asm function bodies (.text order = fn address order) --- */
#pragma cplusplus on
#pragma exceptions on
extern "C" RaceContext *RaceContext_EnsureSingleton(void) { /* 0x8009DC80 size:0x60 */
    RaceContext *instance = lbl_806D12DC == 0 ? (RaceContext *)0 : lbl_806D12DC;
    if (instance == 0) {
        new RaceContext;
    }
    return lbl_806D12DC == 0 ? (RaceContext *)0 : lbl_806D12DC;
}
#pragma exceptions reset
#pragma cplusplus off

asm void dtor_8009DCE0(void) { /* 0x8009DCE0 size:0x48 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr. r31, r3
    beq dtor_8009DCE0_L_8009DD10
    lis r5, lbl_8040E4DC@ha
    extsh. r0, r4
    addi r0, r5, lbl_8040E4DC@l
    stw r0, 0x0(r31)
    ble dtor_8009DCE0_L_8009DD10
    bl MemoryManager_TimedFree
    dtor_8009DCE0_L_8009DD10:
    lwz r0, 0x14(r1)
    mr r3, r31
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

