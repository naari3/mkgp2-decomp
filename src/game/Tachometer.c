/* === extracted from auto_03_800AB17C_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int FLOAT_806cf25c;
extern unsigned int FLOAT_806d1474;
extern unsigned int g_tachometer_coinCount;
extern unsigned int g_tachometer_coinTier;
extern unsigned char g_tachometer_isInitialized;

/* --- function index (3 fns, .text 0x800AB17C..0x800AB220) ---
 * [  0] 0x800AB17C size:0x20    global Tachometer_SetMaxSpeedRef
 * [  1] 0x800AB19C size:0x20    global Tachometer_SetDisplaySpeedRef
 * [  2] 0x800AB1BC size:0x64    global Tachometer_SetCoinCount
 */

/* --- forward decls --- */
int Tachometer_SetMaxSpeedRef(float value);
int Tachometer_SetDisplaySpeedRef(float value);
int Tachometer_SetCoinCount(int count);

/* --- asm function bodies (.text order = fn address order) --- */
int Tachometer_SetMaxSpeedRef(float value) { /* 0x800AB17C size:0x20 */
    if (!g_tachometer_isInitialized) return 0;
    *(float *)&FLOAT_806cf25c = value;
    return 1;
}

int Tachometer_SetDisplaySpeedRef(float value) { /* 0x800AB19C size:0x20 */
    if (!g_tachometer_isInitialized) return 0;
    *(float *)&FLOAT_806d1474 = value;
    return 1;
}

int Tachometer_SetCoinCount(int count) { /* 0x800AB1BC size:0x64 */
    if (!g_tachometer_isInitialized) return 0;
    g_tachometer_coinCount = count;
    if (count <= 0) g_tachometer_coinTier = 0;
    else if (count < 5) g_tachometer_coinTier = 1;
    else if (count < 10) g_tachometer_coinTier = 2;
    else g_tachometer_coinTier = 3;
    return 1;
}

/* The remaining address-ordered members of the Tachometer unit. */
#include "Tachometer_UpdateDisplaySpeed.inc"
#include "Tachometer_RenderDigits.inc"
#include "Tachometer_Destroy.inc"
#include "Tachometer_Init.inc"

