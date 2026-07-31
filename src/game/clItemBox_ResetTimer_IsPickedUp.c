/* === extracted from auto_03_8005EA74_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int lbl_806D29A8;

/* --- function index (2 fns, .text 0x8005EA74..0x8005EA94) ---
 * [  0] 0x8005EA74 size:0xC     global clItemBox_ResetTimer
 * [  1] 0x8005EA80 size:0x14    global clItemBox_IsPickedUp
 */

/* --- forward decls --- */
asm void clItemBox_ResetTimer(void);
asm void clItemBox_IsPickedUp(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void clItemBox_ResetTimer(void) { /* 0x8005EA74 size:0xC */
    nofralloc
    lfs f0, lbl_806D29A8(r2)
    stfs f0, 0x2c(r3)
    blr
}

asm void clItemBox_IsPickedUp(void) { /* 0x8005EA80 size:0x14 */
    nofralloc
    lwz r0, 0x24(r3)
    subfic r0, r0, 0x3
    cntlzw r0, r0
    srwi r3, r0, 5
    blr
}

