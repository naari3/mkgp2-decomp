/* === extracted from auto_Tachometer_UpdateDis_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_tachometer_coinCount;
extern unsigned int g_tachometer_displaySpeed;
extern unsigned char g_tachometer_isInitialized;
extern unsigned int g_tachometer_maxDisplaySpeed;
extern unsigned int lbl_806D4E60;
extern unsigned int lbl_806D4E64;
extern unsigned int lbl_806D4E68;
extern unsigned int lbl_806D4E70;

/* --- function index (1 fns, .text 0x800AB220..0x800AB324) ---
 * [  0] 0x800AB220 size:0x104   global Tachometer_UpdateDisplaySpeed
 */

/* --- forward decls --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x800AB220 size:0x104 */
#define TACH_F(x) (*(float *)&(x))
static inline int Tachometer_CoinSteps(void) {
    return (int)g_tachometer_coinCount > 15 ? 15 : (int)g_tachometer_coinCount;
}
#pragma exceptions on
int Tachometer_UpdateDisplaySpeed(float speed, float maxSpeed) {
    float step;
    float display;
    if (!g_tachometer_isInitialized) {
        return 0;
    }
    step = (1.08f * maxSpeed - maxSpeed) / 15.0f;
    display = step * (float)Tachometer_CoinSteps() + speed;
    if (maxSpeed > 0.0f && g_tachometer_isInitialized) {
        maxSpeed = step * (float)Tachometer_CoinSteps() + maxSpeed;
        if (maxSpeed > 0.0f) {
            TACH_F(g_tachometer_maxDisplaySpeed) = maxSpeed;
        }
    }
    if (speed <= 0.0f) {
        TACH_F(g_tachometer_displaySpeed) = 0.0f;
    } else if (display <= 0.0f) {
        TACH_F(g_tachometer_displaySpeed) = 0.0f;
    } else if (display >= TACH_F(g_tachometer_maxDisplaySpeed)) {
        TACH_F(g_tachometer_displaySpeed) = TACH_F(g_tachometer_maxDisplaySpeed);
    } else {
        TACH_F(g_tachometer_displaySpeed) = display;
    }
    return 1;
}
#pragma exceptions reset

