/* clEnemyRunType2: RTTI, base list and virtual table are emitted by MWCC.
 * Deferred code generation puts the definitions in reverse address order.
 * RTTI names share the original enemy-run string pool in fn_801ECA14.c.
 */
#include "game/types/clEnemyRunInterface.h"

extern "C" {
extern void *GetEnemyParam(void);
extern char *GetKartTuningEntry(void *param, int cup, int round, int kart);
extern int g_cupId;
extern int g_roundIndex;
extern float lbl_806D1948;
extern const float lbl_806DA428;
extern const float lbl_806DA42C;
extern const float lbl_806DA430;
extern const float lbl_806DA434;
extern const float lbl_806DA438;

}

class clEnemyRunType2 : public clEnemyRunInterface {
public:
    clEnemyRunType2(int owner, int driver, int kart, int pathIndex, int character);
    virtual ~clEnemyRunType2();
    virtual float CalcSteering(float input);
};

clEnemyRunType2::clEnemyRunType2(int owner, int driver, int kart, int pathIndex, int character)
    : clEnemyRunInterface(owner, driver, kart, pathIndex, character) {}

float clEnemyRunType2::CalcSteering(float input) {
    int round = g_roundIndex;
    int cup = g_cupId;
    float gain;
    float result;

    gain = *(float *)(GetKartTuningEntry(GetEnemyParam(), cup, round, kartId) + 0x30);
    if (lbl_806DA428 < gain) {
        gain = lbl_806DA428;
    }
    if (gain < lbl_806DA42C) {
        gain = lbl_806DA42C;
    }
    gain *= lbl_806DA430;
    result = lbl_806D1948 * gain;
    result -= lbl_806DA434 * input;
    if (reverse) {
        result *= lbl_806DA438;
    }
    return result;
}

clEnemyRunType2::~clEnemyRunType2() {}
