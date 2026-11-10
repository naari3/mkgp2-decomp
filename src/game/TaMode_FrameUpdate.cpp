#include "game/types/arg_order.h"
#include "game/types/port_hooks.h"
/* clGameTimeAttack (time-attack mode scene): one TU, 0x800A2B90..0x800A4578.
 * Built with -inline deferred, so functions are written in reverse address
 * order (ctor, dtor, FrameUpdate). Deferred codegen runs the class action
 * (vtable + RTTI base list) before the ctor is generated, so the ctor reaches
 * the vtable through the .data section anchor (target: anchor+0x658).
 * Render is BtMode_RenderFrame (own TU). */
/* Time-attack scene constructor; native C++ draft, retained NonMatching. */
#include "game/TaModeInitPrivate.h"
struct TaModeRaceTables { RaceParams cups[8][3][2]; };

static inline int CcClass_Get() { return g_ccClass; }
static inline int KartVariant_Get() { return g_kartVariant; }
static inline void Render_SetReady(void *p) { *(int *)((char *)p + 0x238) = 1; }

static inline int RegisterGhost(float *matrix, void *render) {
    return PathManager_RegisterCarObject(TaMode_FrameUpdate_bss_806D13A4, matrix + 12, matrix + 13, matrix + 14, g_taGhostCar, render, 1);
}

/* Shared time-attack curve constants, ghost filenames and loading messages. */
struct TaModeCurvePool { float scale[3]; float curves[18][7][2]; };
extern "C" {
extern const TaModeCurvePool taModeCurves = {
    { 1.0f, 0.699999988079071f, 0.8999999761581421f },
    {
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 66.66667175292969f }, { 1000.0f, 66.66667175292969f }, { 2000.0f, 66.66667175292969f }, { 3000.0f, 66.66667175292969f }, { 4000.0f, 66.66667175292969f }, { 5000.0f, 66.66667175292969f } },
        { { 0.0f, 0.0f }, { 500.0f, 83.33333587646484f }, { 1000.0f, 83.33333587646484f }, { 2000.0f, 83.33333587646484f }, { 3000.0f, 83.33333587646484f }, { 4000.0f, 83.33333587646484f }, { 5000.0f, 83.33333587646484f } },
        { { 0.0f, 0.0f }, { 500.0f, 83.33333587646484f }, { 1000.0f, 83.33333587646484f }, { 2000.0f, 83.33333587646484f }, { 3000.0f, 83.33333587646484f }, { 4000.0f, 83.33333587646484f }, { 5000.0f, 83.33333587646484f } },
        { { 0.0f, 0.0f }, { 500.0f, 83.33333587646484f }, { 1000.0f, 83.33333587646484f }, { 2000.0f, 83.33333587646484f }, { 3000.0f, 83.33333587646484f }, { 4000.0f, 83.33333587646484f }, { 5000.0f, 83.33333587646484f } },
        { { 0.0f, 0.0f }, { 500.0f, 83.33333587646484f }, { 1000.0f, 83.33333587646484f }, { 2000.0f, 83.33333587646484f }, { 3000.0f, 83.33333587646484f }, { 4000.0f, 83.33333587646484f }, { 5000.0f, 83.33333587646484f } },
        { { 0.0f, 0.0f }, { 500.0f, 83.33333587646484f }, { 1000.0f, 83.33333587646484f }, { 2000.0f, 83.33333587646484f }, { 3000.0f, 83.33333587646484f }, { 4000.0f, 83.33333587646484f }, { 5000.0f, 83.33333587646484f } },
        { { 0.0f, 0.0f }, { 500.0f, 83.33333587646484f }, { 1000.0f, 83.33333587646484f }, { 2000.0f, 83.33333587646484f }, { 3000.0f, 83.33333587646484f }, { 4000.0f, 83.33333587646484f }, { 5000.0f, 83.33333587646484f } },
    }
};
extern const char lbl_80321D7C[0x10] = "ta_mr_short.bin";
extern const char lbl_80321D8C[0xF] = "ta_mr_long.bin";
extern const char lbl_80321D9C[0x10] = "ta_dk_short.bin";
extern const char lbl_80321DAC[0xF] = "ta_dk_long.bin";
extern const char lbl_80321DBC[0x10] = "ta_wc_short.bin";
extern const char lbl_80321DCC[0xF] = "ta_wc_long.bin";
extern const char lbl_80321DDC[0x10] = "ta_pc_short.bin";
extern const char lbl_80321DEC[0xF] = "ta_pc_long.bin";
extern const char lbl_80321DFC[0x10] = "ta_kp_short.bin";
extern const char lbl_80321E0C[0xF] = "ta_kp_long.bin";
extern const char lbl_80321E1C[0x10] = "ta_rb_short.bin";
extern const char lbl_80321E2C[0xF] = "ta_rb_long.bin";
extern const char lbl_80321E3C[0x10] = "ta_yi_short.bin";
extern const char lbl_80321E4C[0xF] = "ta_yi_long.bin";
extern const char lbl_80321E5C[0x10] = "ta_dn_short.bin";
extern const char lbl_80321E6C[0xF] = "ta_dn_long.bin";
extern const char lbl_80321E7C[0x11] = "ta_mr_shortR.bin";
extern const char lbl_80321E90[0x10] = "ta_mr_longR.bin";
extern const char lbl_80321EA0[0x11] = "ta_dk_shortR.bin";
extern const char lbl_80321EB4[0x10] = "ta_dk_longR.bin";
extern const char lbl_80321EC4[0x11] = "ta_wc_shortR.bin";
extern const char lbl_80321ED8[0x10] = "ta_wc_longR.bin";
extern const char lbl_80321EE8[0x11] = "ta_pc_shortR.bin";
extern const char lbl_80321EFC[0x10] = "ta_pc_longR.bin";
extern const char lbl_80321F0C[0x11] = "ta_kp_shortR.bin";
extern const char lbl_80321F20[0x10] = "ta_kp_longR.bin";
extern const char lbl_80321F30[0x11] = "ta_rb_shortR.bin";
extern const char lbl_80321F44[0x10] = "ta_rb_longR.bin";
extern const char lbl_80321F54[0x11] = "ta_yi_shortR.bin";
extern const char lbl_80321F68[0x10] = "ta_yi_longR.bin";
extern const char lbl_80321F78[0x11] = "ta_dn_shortR.bin";
extern const char lbl_80321F8C[0x10] = "ta_dn_longR.bin";
extern const char lbl_80321F9C[0x11] = "clGameTimeAttack";
extern const char lbl_80321FB0[0xC] = "clGameWorld";
extern const char lbl_80321FBC[0xA] = "OK ghost!";
extern const char lbl_80321FC8[0x1B] = "camera jugemu shadow free!";
extern const char lbl_80321FE4[0xA] = "map free!";
extern const char lbl_80321FF0[0x1B] = "effect autorun light free!";
extern const char lbl_8032200C[0x15] = "OK clGame::setting()";
extern const char lbl_80322024[0x23] = "OK ObjectWorkInit & EffectWorkInit";
extern const char lbl_80322048[0xB] = "OK shadow!";
extern const char lbl_80322054[0xE] = "OK Player car";
extern const char lbl_80322064[0xB] = "OK ghost!!";
extern const char lbl_80322070[0x12] = "jyugemu_start.dat";
extern const char lbl_80322084[0x12] = "OK jugemu & etc!!";
extern const char lbl_80322098[0x12] = "OK sprite cdisp()";
extern const char lbl_803220AC[0x11] = "OK TIME setting!";
extern const char lbl_803220C0[0x1A] = "OK ENEMY Item Model load!";
extern const char lbl_803220DC[0xF] = "OK effect load";
extern const char lbl_803220EC[0x32] = "---RACE ----------------------------------------\n";
}
namespace tafu {
/* Time-attack update, 0x800A2B90..0x800A38F8; retained NonMatching. */
#include "game/TaMode_FrameUpdate_private.h"



/* Shared BATTLE prefix, followed by the time-attack record tables. */
struct TaRaceParams { unsigned char laps; float timeLimit, lapBonus; };
struct TaBattlePrefix { TaRaceParams params[48]; TaRecord records[16]; };
extern "C" TaBattlePrefix BATTLE = {
    {
        { 6, 120.0f, 15.0f },
        { 4, 120.0f, 20.0f },
        { 6, 120.0f, 15.0f },
        { 4, 120.0f, 20.0f },
        { 9, 90.0f, 15.0f },
        { 6, 90.0f, 20.0f },
        { 8, 120.0f, 10.0f },
        { 4, 120.0f, 20.0f },
        { 8, 120.0f, 10.0f },
        { 4, 120.0f, 20.0f },
        { 9, 90.0f, 10.0f },
        { 6, 90.0f, 20.0f },
        { 4, 120.0f, 20.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 20.0f },
        { 4, 120.0f, 30.0f },
        { 6, 90.0f, 20.0f },
        { 5, 90.0f, 30.0f },
        { 3, 120.0f, 40.0f },
        { 3, 120.0f, 50.0f },
        { 3, 120.0f, 40.0f },
        { 3, 120.0f, 50.0f },
        { 4, 100.0f, 40.0f },
        { 4, 100.0f, 50.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 35.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 35.0f },
        { 5, 100.0f, 30.0f },
        { 5, 100.0f, 35.0f },
        { 2, 120.0f, 90.0f },
        { 2, 120.0f, 100.0f },
        { 2, 120.0f, 90.0f },
        { 2, 120.0f, 100.0f },
        { 3, 100.0f, 90.0f },
        { 3, 100.0f, 100.0f },
        { 3, 120.0f, 90.0f },
        { 2, 150.0f, 100.0f },
        { 3, 120.0f, 90.0f },
        { 2, 150.0f, 100.0f },
        { 4, 100.0f, 90.0f },
        { 3, 150.0f, 100.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 30.0f },
        { 5, 100.0f, 30.0f },
        { 5, 100.0f, 30.0f },
    },
    {
        { 0, lbl_80321D7C, 7128, 117.0f },
        { 1, lbl_80321D8C, 7192, 118.0f },
        { 6, lbl_80321D9C, 6653, 111.0f },
        { 6, lbl_80321DAC, 6976, 120.0f },
        { 2, lbl_80321DBC, 7052, 119.0f },
        { 2, lbl_80321DCC, 8605, 144.0f },
        { 8, lbl_80321DDC, 7793, 127.0f },
        { 8, lbl_80321DEC, 8983, 150.0f },
        { 4, lbl_80321DFC, 7730, 130.0f },
        { 4, lbl_80321E0C, 7086, 119.0f },
        { 3, lbl_80321E1C, 8575, 140.0f },
        { 10, lbl_80321E2C, 8784, 147.0f },
        { 3, lbl_80321E3C, 8575, 140.0f },
        { 10, lbl_80321E2C, 8784, 147.0f },
        { 3, lbl_80321E1C, 8575, 140.0f },
        { 10, lbl_80321E2C, 8784, 147.0f },
    }
};

static TaRecord taNormalRecords[16][2] = {
    { { 0, lbl_80321D7C, 7443, 122.0999984741211f }, { 1, lbl_80321D8C, 7714, 126.5f } },
    { { 10, lbl_80321D9C, 6472, 105.9000015258789f }, { 8, lbl_80321DAC, 7686, 126.0999984741211f } },
    { { 2, lbl_80321DBC, 7847, 128.6999969482422f }, { 12, lbl_80321DCC, 7876, 129.1999969482422f } },
    { { 8, lbl_80321DDC, 7373, 120.80000305175781f }, { 9, lbl_80321DEC, 8542, 140.3000030517578f } },
    { { 7, lbl_80321DFC, 7400, 121.30000305175781f }, { 3, lbl_80321E0C, 8932, 146.8000030517578f } },
    { { 11, lbl_80321E1C, 9052, 148.8000030517578f }, { 5, lbl_80321E2C, 9548, 154.10000610351562f } },
    { { 4, lbl_80321E3C, 7528, 123.4000015258789f }, { 2, lbl_80321E4C, 8170, 132.0f } },
    { { 0, lbl_80321E5C, 7746, 127.0999984741211f }, { 4, lbl_80321E6C, 7580, 125.30000305175781f } },
    { { 0, lbl_80321E7C, 7146, 117.5f }, { 1, lbl_80321E90, 7316, 118.5f } },
    { { 6, lbl_80321EA0, 6748, 112.0f }, { 6, lbl_80321EB4, 7067, 119.5f } },
    { { 2, lbl_80321EC4, 7143, 118.5f }, { 2, lbl_80321ED8, 8652, 142.0f } },
    { { 8, lbl_80321EE8, 7727, 127.0f }, { 8, lbl_80321EFC, 9021, 152.0f } },
    { { 4, lbl_80321F0C, 7880, 130.5f }, { 4, lbl_80321F20, 7216, 118.5f } },
    { { 7, lbl_80321F30, 8577, 138.5f }, { 5, lbl_80321F44, 8829, 146.5f } },
    { { 7, lbl_80321F30, 8577, 138.5f }, { 5, lbl_80321F44, 8829, 146.5f } },
    { { 7, lbl_80321F30, 8577, 138.5f }, { 5, lbl_80321F44, 8829, 146.5f } },
};

static TaRecord taReverseRecords[8][2] = {
    { { 6, lbl_80321E7C, 7503, 123.0999984741211f }, { 1, lbl_80321E90, 7627, 125.0999984741211f } },
    { { 7, lbl_80321EA0, 6487, 106.0999984741211f }, { 12, lbl_80321EB4, 7626, 125.0999984741211f } },
    { { 6, lbl_80321EC4, 7929, 130.10000610351562f }, { 5, lbl_80321ED8, 7818, 131.3000030517578f } },
    { { 3, lbl_80321EE8, 7526, 123.4000015258789f }, { 10, lbl_80321EFC, 8630, 141.8000030517578f } },
    { { 10, lbl_80321F0C, 7372, 120.80000305175781f }, { 12, lbl_80321F20, 8836, 145.1999969482422f } },
    { { 9, lbl_80321F30, 9018, 148.1999969482422f }, { 7, lbl_80321F44, 9888, 162.6999969482422f } },
    { { 2, lbl_80321F54, 7558, 123.9000015258789f }, { 4, lbl_80321F68, 8199, 134.60000610351562f } },
    { { 11, lbl_80321F78, 7708, 126.4000015258789f }, { 0, lbl_80321F8C, 7687, 126.0999984741211f } },
};

static unsigned int taMemberFunction[3] = { 0, 16, 0 };

static inline void SelectTaRecord(TaRecord *&record, int reversed, int cup)
{
    record = !reversed ? &taNormalRecords[cup - 1][g_longRoundFlag] : &taReverseRecords[cup - 1][g_longRoundFlag];
}


}
namespace tadtor {
/* TaMode_Dtor (0x800A38F8): deleting destructor of the time-attack mode
 * scene; the time-attack counterpart of RaceScene_Dtor (ghost kart, ghost
 * buffer and TA HUD instead of the AI and item HUD). */

struct Deletable {
    virtual ~Deletable();
};

struct CarObject {
    virtual void v0();
    virtual void Destroy(int flag);
};

struct HsdClass {
    unsigned char pad0[0x30];
    void (*release)(void *obj);
    void (*destroy)(void *obj);
};

struct HsdObj {
    HsdClass *klass;
    unsigned short pad4;
};

struct HsdRefObj {
    HsdClass *klass;
    unsigned short ref;
};

struct RaceScene {
    void *vtable;
    void *lakitu;          /* 0x04 */
    void *jyugemuFlag;     /* 0x08 */
    void *jyugemuReverse;  /* 0x0C */
    void *lapBanner;       /* 0x10 */
    void *environment;     /* 0x14 */
    void *pad18;
    Deletable *camera;     /* 0x1C */
    void *pad20[2];
    Deletable *shadow;     /* 0x28 */
    void *hud;             /* 0x2C */
    void *pad30;
    void *ai;              /* 0x34 */
    void *hud38;           /* 0x38 */
    void *overlay;         /* 0x3C */
};

extern "C" {
#ifdef __MWERKS__
extern char TaMode_FrameUpdate_rodata_80321980[];
#else /* this namespace sees TaMode_FrameUpdate_rodata_80321980 with another type: a view of the same object */
static char *const TaMode_FrameUpdate_rodata_80321980 = (char *)::TaMode_FrameUpdate_rodata_80321980;
#endif
extern char GameModeBase_vtable_8040E76C[];
#ifdef __MWERKS__
extern void *g_weatherSystem;
#else /* this namespace sees g_weatherSystem with another type: a view of the same object */
static void * &g_weatherSystem = *(void * *)&::g_weatherSystem;
#endif
#ifdef __MWERKS__
extern CarObject *g_carObjects[];
#else /* this namespace sees g_carObjects with another type: a view of the same object */
static CarObject * *const g_carObjects = (CarObject * *)::g_carObjects;
#endif
#ifdef __MWERKS__
extern void *g_itemSelects[];
#else /* this namespace sees g_itemSelects with another type: a view of the same object */
static void * *const g_itemSelects = (void * *)::g_itemSelects;
#endif
#ifdef __MWERKS__
extern void *TaMode_FrameUpdate_bss_806D13A4;
#else /* this namespace sees TaMode_FrameUpdate_bss_806D13A4 with another type: a view of the same object */
static void * &TaMode_FrameUpdate_bss_806D13A4 = *(void * *)&::TaMode_FrameUpdate_bss_806D13A4;
#endif
#ifdef __MWERKS__
extern CarObject *g_taGhostCar;
#else /* this namespace sees g_taGhostCar with another type: a view of the same object */
static CarObject * &g_taGhostCar = *(CarObject * *)&::g_taGhostCar;
#endif
extern void *TaMode_FrameUpdate_bss_806D1390;
#ifdef __MWERKS__
extern void *g_taSound;
#else /* this namespace sees g_taSound with another type: a view of the same object */
static void * &g_taSound = *(void * *)&::g_taSound;
#endif
#ifdef __MWERKS__
extern HsdRefObj *TaMode_FrameUpdate_bss_806D13C8;
#else /* this namespace sees TaMode_FrameUpdate_bss_806D13C8 with another type: a view of the same object */
static HsdRefObj * &TaMode_FrameUpdate_bss_806D13C8 = *(HsdRefObj * *)&::TaMode_FrameUpdate_bss_806D13C8;
#endif
#ifdef __MWERKS__
extern Deletable *lbl_806D10D0;
#else /* this namespace sees lbl_806D10D0 with another type: a view of the same object */
static Deletable * &lbl_806D10D0 = *(Deletable * *)&tafu::lbl_806D10D0;
#endif
#ifdef __MWERKS__
extern Deletable *lbl_806D109C;
#else /* this namespace sees lbl_806D109C with another type: a view of the same object */
static Deletable * &lbl_806D109C = *(Deletable * *)&tafu::lbl_806D109C;
#endif
extern Deletable *g_courseData;
#ifdef __MWERKS__
extern void *g_raceCamera;
#else /* this namespace sees g_raceCamera with another type: a view of the same object */
static void * &g_raceCamera = *(void * *)&::g_raceCamera;
#endif

void fn_801B6B94(void);
void fn_8016C634(void *p, int flag);
#ifdef __MWERKS__
void SetActiveCamera(void *cam, int flag);
#else /* this namespace declares SetActiveCamera with other types: a view of the same object */
static inline void SetActiveCamera(void * a0, int a1) { ((void (*)(void *, int))&::SetActiveCamera)(a0, a1); }
#endif
void fn_8020AF08(void *p, int flag);
void ProcessSystemTick(const char *msg);
void AI_SystemDtor(void *p, int flag);
void fn_80208FE4(void *p, int flag);
void ItemSelect_Dtor(void *p, int flag);
void Tachometer_Destroy(void);
void HitMessageOverlay_Destroy(void);
void fn_80254134(void *p, int flag);
void LakituStart_Dtor(void *p, int flag);
void Jyugemu_Flag_Dtor(void *p, int flag);
void Jyugemu_ReverseFlag_Dtor(void *p, int flag);
void LapBannerScene_Dtor(void *p, int flag);
void PathParticipantArray_Dtor(void *p, int flag);
void CourseEnvironment_Dtor(void *p, int flag);
void ItemObjectManager_Reset(void);
void VfxSlotMgr_Shutdown(void);
void *GetRaceContextPtr(void);
void RankingTable_Init(void *ctx);
void ClRomTable_PurgeAll(void);
#ifdef __MWERKS__
void SetPlayerCarObject(void *car);
#else /* this namespace declares SetPlayerCarObject with other types: a view of the same object */
static inline void SetPlayerCarObject(void * a0) { ((void (*)(void *))&::SetPlayerCarObject)(a0); }
#endif
void fn_8013A6F8(void);
void CourseBgm_Free(void);
void SceneDrawList_Reset(void);
void SetResourceLoadingFlag(int flag);
void clRom_PurgeAll(void);
#ifdef __MWERKS__
void SetCourseScene3D(void *scene);
#else /* this namespace declares SetCourseScene3D with other types: a view of the same object */
static inline void SetCourseScene3D(void * a0) { ((void (*)(void *))&::SetCourseScene3D)(a0); }
#endif
void MemoryManager_TimedFree(void *p);
void MemoryManager_Free(void *p);
void fn_8023E808(void *p, int flag);
}

static inline int HsdRef_Dec(HsdRefObj *o)
{
    int done = o->ref == (unsigned short)-1;
    if (done) {
        return done;
    }
    return o->ref-- == 0;
}

static inline void HsdRef_Unref(HsdRefObj *o)
{
    if (o == 0) {
        return;
    }
    if (HsdRef_Dec(o)) {
        if (o != 0) {
            o->klass->release(o);
            o->klass->destroy(o);
        }
    }
}


}
TaMode::TaMode() {
    float startX, startY;
    HSD_RandSeedPtr = &TaMode_Init_bss_806D13CC;
    *HSD_RandSeedPtr = lbl_806D1110;
    g_gameMode = 1;
    SetSyncTarget(0x2a);
    g_isCommHost = 0;
    ItemUse_ResetAllKartUseSlots();
    RaceScene_ClearPlayerSlotPointers();
    RaceSlot_ResetAll();
    g_spawnedKartCount = 1;
    int character = g_characterId;
    lbl_806D1050 = 0;
    RaceSlot_InitSlot(0, GetDisplayBufferIndex(), character, 1, 0);
    g_finalLapCoinJumpEnabled = 0;
    ProcessSystemTick(lbl_8032200C);
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    ProcessSystemTick(lbl_80322024);
    environment = new EnvironmentMgr;
    CourseData_GetOrCreate(g_cupId, g_longRoundFlag, g_reverseRoundFlag);
    TaMode_FrameUpdate_bss_806D13C8 = HSD_LObjLoadDesc(GetCourseDataPtr());
    camera = new RaceCamera ARGS_ORDER((lbl_806D483C, 0x200, lbl_806D4838, 0x200, TaMode_FrameUpdate_bss_806D13C8), (0x200, 0x200, TaMode_FrameUpdate_bss_806D13C8, lbl_806D483C, lbl_806D4838));
    SetActiveCamera(0, camera);
    g_raceCamera = camera;
    ProcessSystemTick(lbl_80322048);
    RankingTable_Init(GetRaceContextPtr());
    SoundDriver_GetOrCreate(0);
    CoinSystem_Init(0, 2);
    TaMode_FrameUpdate_bss_806D13A8 = GetKartStartSlot(GetDisplayBufferIndex());
    g_kartStartSlot = TaMode_FrameUpdate_bss_806D13A8;
    GetStartPosition(TaMode_FrameUpdate_bss_806D13A8, &startX, 0, &startY);
    g_carObjects[0] = new CarObject ARGS_ORDER((GetDisplayBufferIndex(), GetKartSlotCharId(TaMode_FrameUpdate_bss_806D13A8), startX, startY, GetCourseStartYaw(), CcClass_Get(), KartVariant_Get(), 1, -1, 0, 0), (GetDisplayBufferIndex(), GetKartSlotCharId(TaMode_FrameUpdate_bss_806D13A8), CcClass_Get(), KartVariant_Get(), 1, -1, 0, 0, startX, startY, GetCourseStartYaw()));
    Render_SetReady(CarObject_GetRenderObj(g_carObjects[0]));
    KartItem_SetShortArray34a(CarObject_GetRenderObj(g_carObjects[0]), g_playerData);
    if (GetVBlankFlag() && !g_playerData[0x19d]) KartItem_SetField358(CarObject_GetRenderObj(g_carObjects[0]), 0);
    g_playerRenderObj = CarObject_GetRenderObj(g_carObjects[0]);
    ProcessSystemTick(lbl_80322054);
    SetPlayerCarObject(g_carObjects[0]);
    {
    float *matrix = CarObject_GetTransformMatrix(g_carObjects[0]);
    TaMode_FrameUpdate_bss_806D13A4 = new PathManager(CourseData_GetDefaultPathKey_Safe(), g_carObjects[0], CarObject_GetRenderObj(g_carObjects[0]), matrix + 12, matrix + 13, matrix + 14);
    }
    int cup = g_cupId - 1;
    int reverse = g_reverseRoundFlag;
    int cc = g_ccClass;
    int round = g_longRoundFlag;
    int index = round + cup * 4 + reverse * 2;
    if (cc == 2) {
        if (g_playerData[0x48 + index] == 1) TaMode_FrameUpdate_bss_806D13A0 = 1;
        else TaMode_FrameUpdate_bss_806D13A0 = 0;
    }
    TaMode_FrameUpdate_bss_806D1394 = 0;
    if (cc == 2 && TaMode_FrameUpdate_bss_806D13A0) {
        const TaGhostSource &ghost = !reverse
            ? *(const TaGhostSource *)&tafu::taNormalRecords[cup][g_longRoundFlag]
            : *(const TaGhostSource *)&tafu::taReverseRecords[cup][g_longRoundFlag];
        g_taGhostCar = new CarObject ARGS_ORDER((4, ghost.character, startX, startY, GetCourseStartYaw(), 2, 3, 0, -1, 0, 0), (4, ghost.character, 2, 3, 0, -1, 0, 0, startX, startY, GetCourseStartYaw()));
        float *matrix = CarObject_GetTransformMatrix(g_taGhostCar);
        TaMode_FrameUpdate_bss_806D139C = RegisterGhost(matrix, CarObject_GetRenderObj(g_taGhostCar));
        TaMode_FrameUpdate_data_806CF198 = 3;
        TaMode_FrameUpdate_bss_806D1390 = DVDFile_LoadSync(ghost.file);
        PORT_DATA_LOADED(PORT_DATA_GHOST, TaMode_FrameUpdate_bss_806D1390, ghost.size);
        TaMode_FrameUpdate_bss_806D1388 = TaMode_FrameUpdate_bss_806D1390;
        TaMode_FrameUpdate_bss_806D138C = ghost.size;
        if (g_taGhostCar) {
            KartMovement_EquipItem(CarObject_GetRenderObj(g_taGhostCar), 0x17);
            ItemEffectBus_OrMask(*(void **)((char *)CarObject_GetRenderObj(g_taGhostCar) + 0x304), 0x8000000000ULL);
        }
    } else { g_taGhostCar = 0; TaMode_FrameUpdate_bss_806D1390 = 0; }
    ProcessSystemTick(lbl_80322064);
    lakitu = new LakituStart(lbl_80322070, TaMode_FrameUpdate_bss_806D13A8, lbl_806D4830, lbl_806D4830, lbl_806D4830);
    scene = new Scene3D(*GetKartModelNameEntry(GetKartSlotCharId(TaMode_FrameUpdate_bss_806D13A8), -1));
    jyugemuFlag = new JyugemuFlag(scene);
    jyugemuReverse = new JyugemuReverseFlag(CarObject_GetRenderObj(g_carObjects[0]));
    lapBanner = new FinalLapBanner(CarObject_GetRenderObj(g_carObjects[0]));
    ProcessSystemTick(lbl_80322084);
    float cameraX, cameraY;
    Scene3D_GetCameraPos(scene, &cameraX, &cameraY);
    cameraX += lbl_806D4860;
    Scene3D_SetupProjection(scene, cameraX, cameraY);
    Tachometer_Init();
    hud = new RaceHud(TaMode_FrameUpdate_bss_806D13A4);
    g_raceHud = hud;
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 3, 0);
    HUD_RegisterOverlay(hud, 5, 0);
    HUD_RegisterOverlay(hud, 1, 0);
    HUD_RegisterOverlay(hud, 2, 0);
    HUD_RegisterOverlay(hud, 10, 0);
    HUD_RegisterOverlay(hud, 11, 0);
    HUD_RegisterOverlay(hud, 7, 0);
    HUD_RegisterOverlay(hud, 15, 0);
    HUD_RegisterOverlay(hud, 16, 0);
    HUD_RegisterOverlay(hud, 14, 0);
    if (IsTimerModeEnabled() == 1) HUD_RegisterOverlay(hud, 4, 0);
    HUD_RegisterOverlay(hud, 13, 0);
    fn_80253EB8(hud, lbl_806D484C);
    HUD_RegisterOverlay(hud, 8, 0);
    HUD_RegisterOverlay(hud, 9, 0);
    HUD_RegisterOverlay(hud, 21, 0);
    ProcessSystemTick(lbl_80322098);
    g_sceneTransitionTimer = -1;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    g_raceEnded = 0;
    ai = 0;
    flag38 = 0;
    /* Cups are one-based; one cup contains six (class, round) records. */
    const RaceParams (*row)[3][2] = (const RaceParams (*)[3][2])&tafu::BATTLE + g_cupId;
    g_bestLapTime = lbl_806D4830;
    g_currentLapTime = lbl_806D4830;
    g_totalRaceTime = lbl_806D4830;
    lbl_806D13A1 = 0;
    g_finalRacePosition = 0;
    g_currentLap = 1;
    g_raceResultCode = -2;
    g_finalLapBannerShown = 0;
    g_lapChangePending = 0;
    g_totalLaps = row[-1][g_ccClass][g_longRoundFlag].laps;
    g_raceTimeRemaining = row[-1][g_ccClass][g_longRoundFlag].timeLimit;
    g_lapBonusTimeDelta = row[-1][g_ccClass][g_longRoundFlag].lapBonus;
    TaMode_FrameUpdate_data_806CF19C = lbl_806D4834;
    HUD_SetTotalLaps(hud, g_totalLaps);
    ProcessSystemTick(lbl_803220AC);
    CourseBgm_Load();
    if (!g_weatherSystem) g_weatherSystem = new WeatherSystem(1);
    TaMode_FrameUpdate_bss_806D13B0 = 0;
    TaMode_FrameUpdate_bss_806D13AC = 3;
    PreloadItemResources(0x17);
    KartMovement_EquipItem(CarObject_GetRenderObj(g_carObjects[0]), 0x17);
    g_taSound = new TaSound(0);
    if (g_taSound) fn_8023E1E4(g_taSound, 0x117, 0);
    StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 0);
    StrPcb_SetStatusBits(StrPcb_GetInstance(), 8, 0);
    ProcessSystemTick(lbl_803220C0);
    SetResourceLoadingFlag(1);
    g_raceFrameCounterLo2digits = 0;
    switch (g_cupId) {
    case 1: PreloadEffectResources(1); break;
    case 2: PreloadEffectResources(2); break;
    case 3: PreloadEffectResources(3); break;
    case 4: PreloadEffectResources(4); break;
    case 5: PreloadEffectResources(5); break;
    case 6: PreloadEffectResources(6); break;
    case 7: PreloadEffectResources(7); break;
    case 8: PreloadEffectResources(8); break;
    }
    PreloadEffectResources(9);
    PreloadEffectResources(10);
    ProcessSystemTick(lbl_803220DC);
    TaMode_FrameUpdate_bss_806D13B8 = 0;
    long long timestamp = OSGetTime();
    TaMode_FrameUpdate_bss_806D13C0 = (unsigned long)(timestamp >> 32);
    TaMode_FrameUpdate_bss_806D13C4 = (unsigned long)timestamp;
    SetSyncTarget(0x2c);
    PlayStats_IncTaPlay();
    DebugPrintf(lbl_803220EC);
}

TaMode::~TaMode()
{
    using namespace tadtor;
    tadtor::RaceScene *self = (tadtor::RaceScene *)this;

    if (tadtor::g_weatherSystem != 0) {
        fn_8016C634(tadtor::g_weatherSystem, 1);
        tadtor::g_weatherSystem = 0;
    }
    tadtor::SetActiveCamera(0, 0);
    if (tadtor::g_taGhostCar != 0) {
        tadtor::g_taGhostCar->Destroy(1);
    }
    MemoryManager_Free(tadtor::TaMode_FrameUpdate_bss_806D1390);
    tadtor::g_taGhostCar = 0;
    tadtor::TaMode_FrameUpdate_bss_806D1390 = 0;
    tadtor::ProcessSystemTick(::lbl_80321FBC);
    Tachometer_Destroy();
    fn_80254134(self->hud, 1);
    delete self->camera;
    LakituStart_Dtor(self->lakitu, 1);
    Jyugemu_Flag_Dtor(self->jyugemuFlag, 1);
    Jyugemu_ReverseFlag_Dtor(self->jyugemuReverse, 1);
    LapBannerScene_Dtor(self->lapBanner, 1);
    PathParticipantArray_Dtor(tadtor::TaMode_FrameUpdate_bss_806D13A4, 1);
    if (tadtor::g_carObjects[0] != 0) {
        tadtor::g_carObjects[0]->Destroy(1);
    }
    if (self->shadow != 0) {
        delete self->shadow;
    }
    tadtor::ProcessSystemTick(::lbl_80321FC8);
    CourseEnvironment_Dtor(self->environment, 1);
    fn_8023E808(tadtor::g_taSound, 1);
    tadtor::ProcessSystemTick(::lbl_80321FE4);
    if (tadtor::TaMode_FrameUpdate_bss_806D13C8 != 0) {
        HsdRef_Unref(tadtor::TaMode_FrameUpdate_bss_806D13C8);
        tadtor::TaMode_FrameUpdate_bss_806D13C8 = 0;
    }
    ItemObjectManager_Reset();
    VfxSlotMgr_Shutdown();
    tadtor::RankingTable_Init(tadtor::GetRaceContextPtr());
    ClRomTable_PurgeAll();
    self->lakitu = 0;
    self->jyugemuFlag = 0;
    self->jyugemuReverse = 0;
    self->lapBanner = 0;
    tadtor::g_carObjects[0] = 0;
    tadtor::TaMode_FrameUpdate_bss_806D13A4 = 0;
    self->camera = 0;
    self->environment = 0;
    tadtor::g_taSound = 0;
    tadtor::SetPlayerCarObject(0);
    delete lbl_806D10D0;
    lbl_806D10D0 = 0;
    fn_8013A6F8();
    tadtor::g_raceCamera = 0;
    CourseBgm_Free();
    SceneDrawList_Reset();
    delete lbl_806D109C;
    lbl_806D109C = 0;
    delete g_courseData;
    g_courseData = 0;
    tadtor::ProcessSystemTick(::lbl_80321FF0);
    tadtor::SetResourceLoadingFlag(0);
    clRom_PurgeAll();
    tadtor::SetCourseScene3D(0);
}

int TaMode::FrameUpdate()
{
    using namespace tafu;
    RaceScene *self = (RaceScene *)this;
    InputPlayer *pad = InputMgr_GetPlayer(GetInputManager(), 0);
    if (tafu::g_sceneTransitionTimer > 0 && --tafu::g_sceneTransitionTimer == 0) {
        tafu::SetSyncTarget(0x2d);
        void *stats = TitleStats();
        if (stats) TitleStats_FinalizeRace_PlayCountThenTitle(stats);
        return 13;
    }
    float steer = 0.0f;
    float accel, brake;
    signed char coins;
    void *camera;
    signed char started;
    ItemObjectManager_PerFrameUpdate(tafu::GetRaceContextPtr());
    if (tafu::g_taSound) fn_8023E324(tafu::g_taSound, __ptmf_test(taMemberFunction) != 0);
    if (tafu::g_raceEnded != 1) {
        unsigned long long now = tafu::OSGetTime();
        steer = QuantizeInput(pad->Steer());
        accel = QuantizeInput(pad->Brake());
        brake = accel;
        if (tafu::g_ccClass != 2) {
            if (!IsRaceStarted()) {
                tafu::TaMode_FrameUpdate_bss_806D13C4 = (unsigned int)now;
                tafu::TaMode_FrameUpdate_bss_806D13C0 = (unsigned int)(now >> 32);
            } else if (steer < 0.1f && accel < 0.1f) {
                if (!tafu::TaMode_FrameUpdate_bss_806D13B8) {
                    long long prev = ((long long)tafu::TaMode_FrameUpdate_bss_806D13C0 << 32) | tafu::TaMode_FrameUpdate_bss_806D13C4;
                    long long ms = (long long)(now - prev) / ((*(unsigned int *)0x800000f8 / 4) / 1000);
                    if ((float)ms / 1000.0f >= 4.0f) tafu::TaMode_FrameUpdate_bss_806D13B8 = 1;
                }
                if (tafu::TaMode_FrameUpdate_bss_806D13B8) steer = 1.0f;
            } else {
                tafu::TaMode_FrameUpdate_bss_806D13C4 = (unsigned int)now;
                tafu::TaMode_FrameUpdate_bss_806D13B8 = 0;
                tafu::TaMode_FrameUpdate_bss_806D13C0 = (unsigned int)(now >> 32);
            }
        }
        accel = QuantizeInput(pad->Accel());
        started = IsRaceStarted();
        if (IsRaceStarted() == 1 && tafu::TaMode_FrameUpdate_bss_806D13AC > 0) {
            TaRender *render = CarObject_GetRenderObj(tafu::g_carObjects[0]);
            if (KartMovement_GetCurrentItemId(render) != -1) {
                if (!KartItem_GetByte_f4(tafu::g_carObjects[0])) {
                    if (Input_IsItemButtonPressed(pad->Held(0xe3ff)) && RenderObj_UseItem(render, 0, 0)) {
                        void *stats = TitleStats();
                        if (stats) RankLog_OnPlayerVictory(stats, tafu::GetDisplayBufferIndex(), 0);
                        CarObject_ApplyDriftBoost(tafu::g_carObjects[0], 5, 3.0f);
                        --tafu::TaMode_FrameUpdate_bss_806D13AC;
                        if (tafu::g_taSound) {
                            if (tafu::TaMode_FrameUpdate_bss_806D13AC == 2) fn_8023E1E4(tafu::g_taSound, 0x116, 0);
                            if (tafu::TaMode_FrameUpdate_bss_806D13AC == 1) fn_8023E1E4(tafu::g_taSound, 0x17, 0);
                            if (tafu::TaMode_FrameUpdate_bss_806D13AC == 0) fn_8023E1E4(tafu::g_taSound, -1, 0);
                        }
                        tafu::TaMode_FrameUpdate_bss_806D13B0 = 30;
                    }
                }
            } else KartMovement_EquipItem(render, 0x17);
        }
    } else {
        accel = CalcSoundDirection(CarObject_GetRenderObj(tafu::g_carObjects[0]), tafu::TaMode_FrameUpdate_bss_806D13A4, &steer, 0);
        brake = 0.0f;
        started = 1;
    }
    CarObject_ApplyInput(tafu::g_carObjects[0], accel, steer, brake, started != 0);
    CarObject_FrameUpdate(tafu::g_carObjects[0], 0);
    if (!tafu::g_raceEnded && pad->Held(0x400) && GetCoinMilage(tafu::g_playerData) >= 4000)
        CoinJumpFlasher_Toggle(tafu::g_carObjects[0]);
    fn_8013A534();
    if (tafu::TaMode_FrameUpdate_bss_806D13A0) {
        coins = 0;
        if (tafu::TaMode_FrameUpdate_bss_806D1394 < tafu::TaMode_FrameUpdate_bss_806D138C) {
            accel = ((float *)tafu::TaMode_FrameUpdate_bss_806D1388)[tafu::TaMode_FrameUpdate_bss_806D1394 * 4];
            TaGhostFrame *frame = &tafu::TaMode_FrameUpdate_bss_806D1388[tafu::TaMode_FrameUpdate_bss_806D1394];
            steer = frame->steer;
            brake = frame->brake;
            started = frame->started;
            signed char item = frame->item;
            coins = frame->coins;
            ++tafu::TaMode_FrameUpdate_bss_806D1394;
            if (tafu::g_taGhostCar && tafu::TaMode_FrameUpdate_data_806CF198 > 0) {
                TaRender *render = CarObject_GetRenderObj(tafu::g_taGhostCar);
                if (KartMovement_GetCurrentItemId(render) != -1) {
                    if (item == 1) {
                        RenderObj_UseItem(render, 0, 0);
                        CarObject_ApplyDriftBoost(tafu::g_taGhostCar, 5, 3.0f);
                        --tafu::TaMode_FrameUpdate_data_806CF198;
                    }
                } else KartMovement_EquipItem(render, 0x17);
            }
        } else if (tafu::g_taGhostCar) {
            accel = CalcSoundDirection(CarObject_GetRenderObj(tafu::g_taGhostCar), tafu::TaMode_FrameUpdate_bss_806D13A4, &steer, tafu::TaMode_FrameUpdate_bss_806D139C);
            brake = 0.0f;
            started = IsRaceStarted();
        }
        if (tafu::g_taGhostCar) {
            if (IsRaceStarted() == 1) {
                void *bus = CarObject_GetRenderObj(tafu::g_taGhostCar)->itemBus;
                if (!CarObject_GetRenderObj(tafu::g_taGhostCar)->effectActive)
                    ItemEffectBus_ClearMask(bus, 0x8000000000ULL);
                else tafu::ItemEffectBus_OrMask(bus, 0x8000000000ULL);
            }
            CarObject_ApplyInput(tafu::g_taGhostCar, accel, steer, brake, started != 0);
            CarObject_FrameUpdate(tafu::g_taGhostCar, 0);
            TaRender *render = CarObject_GetRenderObj(tafu::g_taGhostCar);
            render->coins += coins;
        }
    }
    if (tafu::TaMode_FrameUpdate_bss_806D13B0 != 0) {
        if (--tafu::TaMode_FrameUpdate_bss_806D13B0 == 0) {
            if (tafu::TaMode_FrameUpdate_bss_806D13AC != 0) {
                tafu::StrPcb_SetStatusBits(tafu::StrPcb_GetInstance(), 4, 0);
                tafu::StrPcb_SetStatusBits(tafu::StrPcb_GetInstance(), 8, 0);
            } else {
                StrPcb_ClearStatusBits(tafu::StrPcb_GetInstance(), 4);
                StrPcb_ClearStatusBits(tafu::StrPcb_GetInstance(), 8);
            }
        } else if (!(tafu::TaMode_FrameUpdate_bss_806D13B0 & 1)) {
            tafu::StrPcb_SetStatusBits(tafu::StrPcb_GetInstance(), 4, 0);
            tafu::StrPcb_SetStatusBits(tafu::StrPcb_GetInstance(), 8, 0);
        } else {
            StrPcb_ClearStatusBits(tafu::StrPcb_GetInstance(), 4);
            StrPcb_ClearStatusBits(tafu::StrPcb_GetInstance(), 8);
        }
    }
    if (!tafu::lbl_806D13A1) tafu::lbl_806D13A1 = 1;
    if (self->demoCamera) {
        Object_SetByte10_Return1(self->scene, 0);
        TaBookend *book = TaMode_GetDemoCameraBookend();
        if (book) {
            Vec direction;
            Vec3_Subtract(&book->eye, &book->target, &direction);
            Vec3_Normalize(&direction, &direction);
            direction.x = 1000.0f * direction.x + book->target.x;
            direction.y = 100.0f + (1000.0f * direction.y + book->target.y);
            direction.z = 1000.0f * direction.z + book->target.z;
            CObj_LoadIntoGX(self->scene, &direction);
            CObj_ApplyViewport(self->scene, &book->target);
        }
        camera = tafu::g_raceCamera;
        SceneRender_SetViewportRect(camera,
            CarObject_GetTransformMatrix(tafu::g_carObjects[0])[12],
            CarObject_GetTransformMatrix(tafu::g_carObjects[0])[13],
            CarObject_GetTransformMatrix(tafu::g_carObjects[0])[14],
            CarObject_GetTransformMatrix(tafu::g_carObjects[0])[8],
            CarObject_GetTransformMatrix(tafu::g_carObjects[0])[9],
            CarObject_GetTransformMatrix(tafu::g_carObjects[0])[10]);
    } else KartItem_UpdateShadowBillboardAndViewport(tafu::g_carObjects[0], self->scene, 0);
    Fog_UpdateFromCourseScene3D();
    PathManager_UpdateAll(tafu::TaMode_FrameUpdate_bss_806D13A4);
    LakituStart_UpdateCountdown(self->lakitu);
    Jyugemu_Flag_Tick(self->jyugemuFlag);
    Jyugemu_ReverseFlag_Tick(self->jyugemuReverse);
    LapBannerScene_UpdateAndDriveAnim(self->lapBanner);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);
    CObj_LoadProjMatrix(self->scene, &TaMode_FrameUpdate_bss_805D2B28);
    CObj_ApplyScissor(self->scene, &TaMode_FrameUpdate_bss_805D2B34);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(TaMode_FrameUpdate_bss_805D2B28, TaMode_FrameUpdate_bss_805D2B34);
    if (g_rendererGateFlag == 1 && IsRaceStarted() == 1 && !tafu::g_raceEnded && tafu::g_raceTimeRemaining > 0.0f) {
        tafu::g_raceTimeRemaining -= 0.016666668f;
        if (tafu::g_raceTimeRemaining <= 0.0f) {
            tafu::g_raceTimeRemaining = 0.0f;
            fn_80253BE4(self->hud);
            tafu::g_sceneTransitionTimer = 180;
            fn_8016C554(0);
        }
    }
    Tachometer_RenderDigits();
    HUD_SetCurrentLap(self->hud, tafu::g_currentLap);
    fn_80253FD8(self->hud, tafu::g_raceTimeRemaining);
    fn_80253EBC(self->hud, 100.0f * CarObject_CalcSpeedRatio(tafu::g_carObjects[0]));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(tafu::g_carObjects[0]));
    fn_80253EC4(self->hud, tafu::g_currentLapTime);
    fn_80253F2C(self->hud, tafu::g_bestLapTime);
    HUD_SetRacePosition(self->hud, tafu::g_finalRacePosition);
    fn_80253E18(self->hud, CarObject_GetRenderObj(tafu::g_carObjects[0])->coins);
    TransitionEffect_Tick(Transition());
    if (!tafu::g_finalLapBannerShown && tafu::g_currentLap >= tafu::g_totalLaps) {
        tafu::g_finalLapBannerShown = 1;
        fn_80253DF0(self->hud);
    }
    if (0.0f != tafu::g_raceTimeRemaining && tafu::g_raceResultCode == -2) {
        if (tafu::g_currentLap >= tafu::g_totalLaps + 1) {
            if (tafu::g_finalLapCoinJumpEnabled == 1) CoinJumpFlasher_Toggle(tafu::g_carObjects[0]);
            KartItem_OnFallOffOrDeath(tafu::g_carObjects[0]);
            CoinJumpFlasher_SetArmed(tafu::g_carObjects[0], 0);
            tafu::g_finalRacePosition = ((TaRender *)tafu::g_playerRenderObj)->position;
            tafu::g_raceResultCode = -1;
            int rank = TaRecord_InsertResult(tafu::g_playerData, tafu::g_playerData[0x19b], tafu::g_playerData[0x19c], tafu::g_playerData[0x1b1], tafu::GetKartSlotCharId(tafu::TaMode_FrameUpdate_bss_806D13A8), tafu::g_totalRaceTime);
            Jyugemu_Flag_SetKartDriver(self->jyugemuFlag, CarObject_GetRenderObj(tafu::g_carObjects[0]));
            if (tafu::g_ccClass == 2) {
                if (tafu::TaMode_FrameUpdate_bss_806D13A0) {
                    if (tafu::g_finalRacePosition == 0) fn_801D670C(tafu::g_playerData);
                } else {
                    float time = tafu::g_totalRaceTime;
                    TaRecord *record;
                    SelectTaRecord(record, tafu::g_reverseRoundFlag, tafu::g_cupId);
                    if (time < record->time) {
                        fn_801D676C(tafu::g_playerData);
                        PlayStats_IncTaBestRecord();
                    }
                }
            } else if (tafu::g_ccClass == 1 && rank < 3) fn_801D597C(tafu::g_playerData);
            void *stats = TitleStats();
            if (stats) {
                RankLog_SetRaceResult(stats, tafu::GetDisplayBufferIndex(), tafu::g_finalRacePosition, (int)tafu::g_raceTimeRemaining);
                TitleStats_CaptureRoundContext(stats, rank, tafu::g_totalRaceTime);
                TitleStats_FinalizeRace_PlayCountThenTitle(stats);
            }
            fn_80253D00(self->hud);
            Object_SetByte10_Return1(self->scene, 1);
            fn_8016C554(1);
            tafu::g_raceEnded = 1;
            tafu::g_lakituStartAnimDone = 0;
            ++self->finishFrames;
            tafu::TaMode_FrameUpdate_data_806CF19C = tafu::g_totalRaceTime;
        } else if (tafu::g_lapChangePending) {
            if (tafu::g_finalLapBannerShown) {
                fn_8016C598();
                LapBannerScene_TriggerBannerAnim(self->lapBanner);
            } else fn_8016C5CC();
            void *stats = TitleStats();
            if (stats) TitleTracker_ResetPerRound(stats, tafu::GetDisplayBufferIndex(), tafu::g_currentLap - 1);
            tafu::g_lapChangePending = 0;
        }
    } else if (self->finishFrames != 0) {
        if (++self->finishFrames > 300) self->demoCamera = 1;
        if (fn_80253C40(self->hud)) {
            tafu::SetSyncTarget(0x2d);
            return 13;
        }
    }
    HUD_FrameUpdate(self->hud);
    clItemBoxManager_Update(ItemBoxMgr());
    if (tafu::g_weatherSystem) fn_8016B32C(tafu::g_weatherSystem);
    if (!lbl_806D0051 && pad->Pressed(0x400) == 1) return 2;
    return -2;
}


#pragma readonly_strings on
