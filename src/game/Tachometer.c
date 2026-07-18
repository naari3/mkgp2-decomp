/* === extracted from auto_03_800AB17C_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_806cf25c;
extern unsigned int FLOAT_806d1474;
extern unsigned int g_tachometer_coinCount;
extern unsigned int g_tachometer_coinTier;
extern unsigned int g_tachometer_isInitialized;

/* --- function index (3 fns, .text 0x800AB17C..0x800AB220) ---
 * [  0] 0x800AB17C size:0x20    global Tachometer_SetMaxSpeedRef
 * [  1] 0x800AB19C size:0x20    global Tachometer_SetDisplaySpeedRef
 * [  2] 0x800AB1BC size:0x64    global Tachometer_SetCoinCount
 */

/* --- forward decls --- */
asm void Tachometer_SetMaxSpeedRef(void);
asm void Tachometer_SetDisplaySpeedRef(void);
asm void Tachometer_SetCoinCount(void);

/* --- asm function bodies (.text order = fn address order) --- */
asm void Tachometer_SetMaxSpeedRef(void) { /* 0x800AB17C size:0x20 */
    nofralloc
    lbz r0, g_tachometer_isInitialized(r13)
    cmplwi r0, 0x0
    bne Tachometer_SetMaxSpeedRef_L_800AB190
    li r3, 0x0
    blr
    Tachometer_SetMaxSpeedRef_L_800AB190:
    stfs f1, FLOAT_806cf25c(r13)
    li r3, 0x1
    blr
}

asm void Tachometer_SetDisplaySpeedRef(void) { /* 0x800AB19C size:0x20 */
    nofralloc
    lbz r0, g_tachometer_isInitialized(r13)
    cmplwi r0, 0x0
    bne Tachometer_SetDisplaySpeedRef_L_800AB1B0
    li r3, 0x0
    blr
    Tachometer_SetDisplaySpeedRef_L_800AB1B0:
    stfs f1, FLOAT_806d1474(r13)
    li r3, 0x1
    blr
}

asm void Tachometer_SetCoinCount(void) { /* 0x800AB1BC size:0x64 */
    nofralloc
    lbz r0, g_tachometer_isInitialized(r13)
    cmplwi r0, 0x0
    bne Tachometer_SetCoinCount_L_800AB1D0
    li r3, 0x0
    blr
    Tachometer_SetCoinCount_L_800AB1D0:
    cmpwi r3, 0x0
    stw r3, g_tachometer_coinCount(r13)
    bgt Tachometer_SetCoinCount_L_800AB1E8
    li r0, 0x0
    stw r0, g_tachometer_coinTier(r13)
    b Tachometer_SetCoinCount_L_800AB218
    Tachometer_SetCoinCount_L_800AB1E8:
    cmpwi r3, 0x5
    bge Tachometer_SetCoinCount_L_800AB1FC
    li r0, 0x1
    stw r0, g_tachometer_coinTier(r13)
    b Tachometer_SetCoinCount_L_800AB218
    Tachometer_SetCoinCount_L_800AB1FC:
    cmpwi r3, 0xa
    bge Tachometer_SetCoinCount_L_800AB210
    li r0, 0x2
    stw r0, g_tachometer_coinTier(r13)
    b Tachometer_SetCoinCount_L_800AB218
    Tachometer_SetCoinCount_L_800AB210:
    li r0, 0x3
    stw r0, g_tachometer_coinTier(r13)
    Tachometer_SetCoinCount_L_800AB218:
    li r3, 0x1
    blr
}

/* The remaining address-ordered members of the Tachometer unit. */
#include "Tachometer_UpdateDisplaySpeed.inc"
#include "Tachometer_RenderDigits.inc"
#include "Tachometer_Destroy.inc"
#include "Tachometer_Init.inc"

