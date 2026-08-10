/* === extracted from auto_KartAudioChannel_Set_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void fn_8016C394();

/* --- function index (1 fns, .text 0x800595B4..0x80059644) ---
 * [  0] 0x800595B4 size:0x90    global KartAudioChannel_Set24WithSeStop
 */

/* --- forward decls --- */
asm void KartAudioChannel_Set24WithSeStop(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_KartAudioChannel_Set24WithSeStop[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartAudioChannel_Set24WithSeStop = {
    (void *)&KartAudioChannel_Set24WithSeStop, 0x00000090, (void *)extab_KartAudioChannel_Set24WithSeStop
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartAudioChannel_Set24WithSeStop(void) { /* 0x800595B4 size:0x90 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    mr r31, r4
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r0, 0x24(r3)
    cmpw r0, r31
    beq KartAudioChannel_Set24WithSeStop_L_80059628
    cmpwi r0, 0x1
    beq KartAudioChannel_Set24WithSeStop_L_80059608
    bge KartAudioChannel_Set24WithSeStop_L_8005962C
    cmpwi r0, 0x0
    bge KartAudioChannel_Set24WithSeStop_L_800595F4
    b KartAudioChannel_Set24WithSeStop_L_8005962C
    KartAudioChannel_Set24WithSeStop_L_800595F4:
    lwz r0, 0x8(r30)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x51
    bl fn_8016C394
    b KartAudioChannel_Set24WithSeStop_L_80059620
    KartAudioChannel_Set24WithSeStop_L_80059608:
    lwz r0, 0x8(r30)
    clrlslwi r0, r0, 28, 27
    ori r3, r0, 0x52
    bl fn_8016C394
    b KartAudioChannel_Set24WithSeStop_L_80059620
    b KartAudioChannel_Set24WithSeStop_L_8005962C
    KartAudioChannel_Set24WithSeStop_L_80059620:
    li r0, 0x0
    stb r0, 0x18(r30)
    KartAudioChannel_Set24WithSeStop_L_80059628:
    stw r31, 0x24(r30)
    KartAudioChannel_Set24WithSeStop_L_8005962C:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

