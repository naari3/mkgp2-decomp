/* === extracted from auto_card_send_track_data_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void FUN_8003b120();
extern void MemoryManager_Free();
extern void Sci2Card_BuildPacket();
extern void memcpy();
extern void memset();

/* --- function index (1 fns, .text 0x800776CC..0x80077810) ---
 * [  0] 0x800776CC size:0x144   global card_send_track_data
 */

/* --- forward decls --- */
asm void card_send_track_data(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_card_send_track_data[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_card_send_track_data = {
    (void *)&card_send_track_data, 0x00000144, (void *)extab_card_send_track_data
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void card_send_track_data(void) { /* 0x800776CC size:0x144 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr r27, r3
    mr r28, r4
    mr r29, r5
    mr r30, r6
    lwz r0, 0x0(r3)
    cmpwi r0, 0x0
    beq card_send_track_data_L_80077700
    li r3, 0x0
    b card_send_track_data_L_800777FC
    card_send_track_data_L_80077700:
    cmpwi r29, 0x0
    ble card_send_track_data_L_80077710
    cmpwi r29, 0x45
    ble card_send_track_data_L_80077718
    card_send_track_data_L_80077710:
    li r3, 0x0
    b card_send_track_data_L_800777FC
    card_send_track_data_L_80077718:
    cmplwi r28, 0x0
    bne card_send_track_data_L_80077728
    li r3, 0x0
    b card_send_track_data_L_800777FC
    card_send_track_data_L_80077728:
    li r3, 0x48
    bl FUN_8003b120
    li r4, 0x0
    mr r31, r3
    li r5, 0x48
    bl memset
    clrlwi r0, r30, 24
    li r3, 0x30
    cmplwi r0, 0x1
    stb r3, 0x0(r31)
    bne card_send_track_data_L_8007775C
    stb r3, 0x1(r31)
    b card_send_track_data_L_80077764
    card_send_track_data_L_8007775C:
    li r0, 0x31
    stb r0, 0x1(r31)
    card_send_track_data_L_80077764:
    li r0, 0x30
    mr r4, r28
    stb r0, 0x2(r31)
    mr r5, r29
    addi r3, r31, 0x3
    bl memcpy
    lwz r4, 0x8(r27)
    mr r3, r27
    mr r8, r31
    addi r5, r27, 0xc
    li r6, 0x2
    li r7, 0x53
    li r9, 0x48
    bl Sci2Card_BuildPacket
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne card_send_track_data_L_800777F0
    li r3, 0x1
    li r0, 0x0
    stw r3, 0x0(r27)
    li r4, 0x0
    li r5, 0x102
    stb r0, 0x4(r27)
    stb r0, 0x5(r27)
    stb r0, 0x6(r27)
    lwz r3, 0x10(r27)
    bl memset
    li r3, 0x0
    li r0, 0x8
    stw r3, 0x14(r27)
    mr r3, r31
    stw r0, 0x1c(r27)
    bl MemoryManager_Free
    li r3, 0x1
    b card_send_track_data_L_800777FC
    card_send_track_data_L_800777F0:
    mr r3, r31
    bl MemoryManager_Free
    li r3, 0x0
    card_send_track_data_L_800777FC:
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
