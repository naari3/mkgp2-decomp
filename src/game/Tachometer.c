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
/* --- owned .data 0x80411E20..0x80412158 (tools/own_data.py) --- */
#pragma force_active on
unsigned int Tachometer_data_80411E20[206] = { 0x00000BCB, 0x00000BCB, 0x000009F0, 0x000009CA, 0x00000BBA, 0x00000B68, 0x000009F2, 0x000009CC, 0x000009F3, 0x000009CD, 0x000009F4, 0x000009CE, 0x000009F5, 0x000009CF, 0x000009F6, 0x000009D0, 0x000009F7, 0x000009D1, 0x000009F8, 0x000009D2, 0x000009F9, 0x000009D3, 0x000009FA, 0x000009D4, 0x000009FB, 0x000009D5, 0x000009FC, 0x000009D6, 0x000009FD, 0x000009D7, 0x000009FE, 0x000009D8, 0x000009FF, 0x000009D9, 0x00000A00, 0x000009DA, 0x00000A01, 0x000009DB, 0x00000A02, 0x000009DC, 0x00000A03, 0x000009DD, 0x00000A04, 0x000009DE, 0x00000A05, 0x000009DF, 0x00000A06, 0x000009E0, 0x00000A07, 0x000009E1, 0x00000A08, 0x000009E2, 0x00000A09, 0x000009E3, 0x00000A0A, 0x000009E4, 0x00000BB0, 0x00000B5E, 0x00000BB1, 0x00000B5F, 0x00000BB2, 0x00000B60, 0x00000BB3, 0x00000B61, 0x00000BB4, 0x00000B62, 0x00000BB5, 0x00000B63, 0x00000BB6, 0x00000B64, 0x00000BB7, 0x00000B65, 0x00000BB8, 0x00000B66, 0x00000BB9, 0x00000B67, 0x0000001B, 0x44048000, 0x43DD8000, 0x0000001B, 0x440A4000, 0x43DD8000, 0x0000001B, 0x44100000, 0x43DD8000, 0x00000001, 0x440F4000, 0x43BE8000, 0x00000001, 0x4410C000, 0x43BE8000, 0x00000001, 0x44124000, 0x43BE8000, 0x00000001, 0x4413C000, 0x43BE8000, 0x00000001, 0x44154000, 0x43BE8000, 0x00000001, 0x4416C000, 0x43BE8000, 0x00000001, 0x44184000, 0x43BE8000, 0x00000001, 0x4419C000, 0x43BE8000, 0x00000001, 0x441B4000, 0x43BE8000, 0x00000003, 0x43F00000, 0x43E48000, 0x00000004, 0x43F00000, 0x43E10000, 0x00000005, 0x43F10000, 0x43DD8000, 0x00000006, 0x43F18000, 0x43D98000, 0x00000007, 0x43F30000, 0x43D68000, 0x00000008, 0x43F48000, 0x43D38000, 0x00000009, 0x43F68000, 0x43D08000, 0x0000000A, 0x43F90000, 0x43CE0000, 0x0000000B, 0x43FB0000, 0x43CB8000, 0x0000000C, 0x43FE0000, 0x43C90000, 0x0000000D, 0x44004000, 0x43C70000, 0x0000000E, 0x4401C000, 0x43C58000, 0x0000000F, 0x44034000, 0x43C40000, 0x00000010, 0x44050000, 0x43C28000, 0x00000011, 0x44068000, 0x43C18000, 0x00000012, 0x44084000, 0x43C10000, 0x00000013, 0x4409C000, 0x43C08000, 0x00000014, 0x440BC000, 0x43C00000, 0x00000015, 0x440D8000, 0x43C00000, 0x00000016, 0x440F4000, 0x43BF8000, 0x00000017, 0x4410C000, 0x43BF8000, 0x00000018, 0x44124000, 0x43BF8000, 0x00000019, 0x4413C000, 0x43BF8000, 0x0000001A, 0x44154000, 0x43BF8000, 0x0000001A, 0x4416C000, 0x43BF8000, 0x0000001A, 0x44184000, 0x43BF8000, 0x0000001A, 0x4419C000, 0x43BF8000, 0x0000001A, 0x441B4000, 0x43BF8000, 0x0000001C, 0x0000001D, 0x0000001E, 0x0000001F, 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024, 0x00000025 };
#pragma force_active reset

