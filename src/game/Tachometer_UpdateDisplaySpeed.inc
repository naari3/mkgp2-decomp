/* === extracted from auto_Tachometer_UpdateDis_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_tachometer_coinCount;
extern unsigned int g_tachometer_displaySpeed;
extern unsigned int g_tachometer_isInitialized;
extern unsigned int g_tachometer_maxDisplaySpeed;
extern unsigned int lbl_806D4E60;
extern unsigned int lbl_806D4E64;
extern unsigned int lbl_806D4E68;
extern unsigned int lbl_806D4E70;

/* --- function index (1 fns, .text 0x800AB220..0x800AB324) ---
 * [  0] 0x800AB220 size:0x104   global Tachometer_UpdateDisplaySpeed
 */

/* --- forward decls --- */
asm void Tachometer_UpdateDisplaySpeed(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_Tachometer_UpdateDisplaySpeed[8] = {
    0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_Tachometer_UpdateDisplaySpeed = {
    (void *)&Tachometer_UpdateDisplaySpeed, 0x00000104, (void *)extab_Tachometer_UpdateDisplaySpeed
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void Tachometer_UpdateDisplaySpeed(void) { /* 0x800AB220 size:0x104 */
    nofralloc
    stwu r1, -0x10(r1)
    lbz r5, g_tachometer_isInitialized(r13)
    cmplwi r5, 0x0
    bne Tachometer_UpdateDisplaySpeed_L_800AB238
    li r3, 0x0
    b Tachometer_UpdateDisplaySpeed_L_800AB31C
    Tachometer_UpdateDisplaySpeed_L_800AB238:
    lfs f0, lbl_806D4E60(r2)
    li r0, 0xf
    lwz r4, g_tachometer_coinCount(r13)
    fmsubs f3, f0, f2, f2
    lfs f0, lbl_806D4E64(r2)
    cmpwi r4, 0xf
    fdivs f5, f3, f0
    bgt Tachometer_UpdateDisplaySpeed_L_800AB25C
    mr r0, r4
    Tachometer_UpdateDisplaySpeed_L_800AB25C:
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfs f0, lbl_806D4E68(r2)
    stw r0, 0x8(r1)
    lfd f3, lbl_806D4E70(r2)
    fcmpo cr0, f2, f0
    lfd f0, 0x8(r1)
    fsubs f0, f0, f3
    fmadds f6, f5, f0, f1
    ble Tachometer_UpdateDisplaySpeed_L_800AB2D0
    cmplwi r5, 0x0
    beq Tachometer_UpdateDisplaySpeed_L_800AB2D0
    cmpwi r4, 0xf
    li r0, 0xf
    bgt Tachometer_UpdateDisplaySpeed_L_800AB2A0
    mr r0, r4
    Tachometer_UpdateDisplaySpeed_L_800AB2A0:
    xoris r3, r0, 0x8000
    lis r0, 0x4330
    stw r3, 0xc(r1)
    lfd f4, lbl_806D4E70(r2)
    stw r0, 0x8(r1)
    lfs f0, lbl_806D4E68(r2)
    lfd f3, 0x8(r1)
    fsubs f3, f3, f4
    fmadds f2, f5, f3, f2
    fcmpo cr0, f2, f0
    ble Tachometer_UpdateDisplaySpeed_L_800AB2D0
    stfs f2, g_tachometer_maxDisplaySpeed(r13)
    Tachometer_UpdateDisplaySpeed_L_800AB2D0:
    lfs f0, lbl_806D4E68(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne Tachometer_UpdateDisplaySpeed_L_800AB2E8
    stfs f0, g_tachometer_displaySpeed(r13)
    b Tachometer_UpdateDisplaySpeed_L_800AB318
    Tachometer_UpdateDisplaySpeed_L_800AB2E8:
    fcmpo cr0, f6, f0
    cror eq, lt, eq
    bne Tachometer_UpdateDisplaySpeed_L_800AB2FC
    stfs f0, g_tachometer_displaySpeed(r13)
    b Tachometer_UpdateDisplaySpeed_L_800AB318
    Tachometer_UpdateDisplaySpeed_L_800AB2FC:
    lfs f0, g_tachometer_maxDisplaySpeed(r13)
    fcmpo cr0, f6, f0
    cror eq, gt, eq
    bne Tachometer_UpdateDisplaySpeed_L_800AB314
    stfs f0, g_tachometer_displaySpeed(r13)
    b Tachometer_UpdateDisplaySpeed_L_800AB318
    Tachometer_UpdateDisplaySpeed_L_800AB314:
    stfs f6, g_tachometer_displaySpeed(r13)
    Tachometer_UpdateDisplaySpeed_L_800AB318:
    li r3, 0x1
    Tachometer_UpdateDisplaySpeed_L_800AB31C:
    addi r1, r1, 0x10
    blr
}

