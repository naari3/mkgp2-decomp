/* === extracted from auto_PathCursor_ResetToPa_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CourseData_ResolveByKey();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_courseData;

/* --- forward decls --- */
asm void PathCursor_ResetToPath(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_PathCursor_ResetToPath[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_PathCursor_ResetToPath = {
    (void *)&PathCursor_ResetToPath, 0x00000060, (void *)extab_PathCursor_ResetToPath
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void PathCursor_ResetToPath(void) {
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
    beq PathCursor_ResetToPath_L_800468A4
    lwz r0, g_courseData(r13)
    cmplwi r0, 0x0
    bne PathCursor_ResetToPath_L_80046898
    b PathCursor_ResetToPath_L_8004689C
    PathCursor_ResetToPath_L_80046898:
    mr r3, r0
    PathCursor_ResetToPath_L_8004689C:
    bl CourseData_ResolveByKey
    stw r3, 0x0(r31)
    PathCursor_ResetToPath_L_800468A4:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

