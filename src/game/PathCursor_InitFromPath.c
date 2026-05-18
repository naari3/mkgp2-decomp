/* asm_fn retreat: PathCursor_InitFromPath (sibling of PathCursor_ResetToPath).
 *
 * Reason: target prologue uses the same CW 1.3.2 r3/r31 base-register swap
 * idiom as PathCursor_ResetToPath. Reset retreated to asm_fn after 10+
 * source attempts; Init shares the identical prologue (li r0,-1 then
 * li r3,0 reuse, then stw r3,0(r31)/stw r0,4(r31)/stw r4,0xc(r31) with
 * r31 base post `mr r31,r3`). 3 source attempts here (ternary,
 * if-cd==0, store-order swap) all produced r3-base stores instead of
 * r31-base, never reaching 100%. Retreating to asm_fn keeps the bundle
 * SHA-1 OK and follows the established sibling pattern.
 *
 * extab layout (manual emit, .extab_user/.extabindex_user via objcopy):
 *   extab      @ 0x800066D8  size 0x08  (same 0x0808 prefix as ResetToPath)
 *   extabindex @ 0x80020018  size 0x0C  -> fn=0x800468F4, fn_size=0x6C
 */

/* --- extern decls: branch callees --- */
extern void CourseData_ResolveByKey();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_courseData;

/* --- forward decls --- */
asm void PathCursor_InitFromPath(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_PathCursor_InitFromPath[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_PathCursor_InitFromPath = {
    (void *)&PathCursor_InitFromPath, 0x0000006C, (void *)extab_PathCursor_InitFromPath
};

/* --- asm function body (.text order = fn address order) --- */
asm void PathCursor_InitFromPath(void) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    cmplwi r4, 0x0
    stw r0, 0x14(r1)
    li r0, -0x1
    stw r31, 0xc(r1)
    mr r31, r3
    li r3, 0x0
    stw r3, 0x0(r31)
    stw r0, 0x4(r31)
    stw r4, 0xc(r31)
    beq PathCursor_InitFromPath_L_80046940
    lwz r0, g_courseData(r13)
    cmplwi r0, 0x0
    bne PathCursor_InitFromPath_L_80046934
    b PathCursor_InitFromPath_L_80046938
    PathCursor_InitFromPath_L_80046934:
    mr r3, r0
    PathCursor_InitFromPath_L_80046938:
    bl CourseData_ResolveByKey
    stw r3, 0x0(r31)
    PathCursor_InitFromPath_L_80046940:
    li r0, 0x0
    mr r3, r31
    stw r0, 0x8(r31)
    lwz r31, 0xc(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}
