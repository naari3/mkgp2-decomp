#include "game/types/clEnemyItemAIKartPrivate.h"
#include "game/types/clEnemyItemInterface.h"

extern "C" {
extern char lbl_804E4A34[];
extern char lbl_803BD7C8[];
extern void *g_pathSystem;
extern int g_roundIndex, g_cupId;
void MemoryManager_TimedFree(void *);
void GetStartPosition(int, float *, float *, float *);
void Mtx4x4_TransposeTo4x3(float *, float *);
int PathManager_RegisterCarObject(void *, float *, float *, float *, int, AIDriver *, int);
void DebugPrintf(const char *, ...);
void KartItem_SetField2ac(AIDriver *, int);
void *GetEnemyParam();
struct AITuning { char opaque[0x2c]; int runType; };
AITuning *GetKartTuningEntry(void *, int, int, int);
int IsTimerModeEnabled();
}

EnemyItemAIKart::EnemyItemAIKart(void *owner, int id, int character, int arg)
    : AIResponder(&position), AIWarpResponder() {
    AIResponder::vptr = lbl_804E4A34;
    AIWarpResponder::vptr = lbl_804E4A34 + 0x10;
    driver.p = 0; tornado.p = 0; audio.p = 0; extra.p = 0;
    run.p = 0; item.p = 0; steering.p = 0; aux.p = 0;
    driver.reset(new AIDriver(6, owner, matrix, id, 0, 0));
    tornado.reset(new AITornado(0, driver.p, owner, 0, 0.0f, 0.0f, 0.0f));
    audio.reset(new AIAudio(owner, 0, 1, id, matrix));
    extra.reset(new AIExtra(1, id));
    run.reset(0);
    item.reset(0);
    steering.reset(new AISteering(driver.p, tornado.p));
    aux.reset(new AIAux(driver.p, tornado.p));
    path = g_pathSystem;
    pathId = -1;
    kartId = id;
    characterId = character % 10;
    arg7 = arg;
    f8c = 0.0f;
    f90 = 0.0f;
    flag94 = 0;
    f98 = 0; f9c = 0; fa0 = 0; fc4 = 0; fac = 0; fd0 = 0;
    fa4 = 1.0f;
    fb0 = 0; fb8 = 0; fc0 = 0; fbc = 0;
    fd4 = 0; fd8 = 0; fdc = 0; fe0 = 0; fe4 = 0; fe8 = 0;
    fa8 = -1; fec = 0; ff0 = 0;
    GetStartPosition(kartId, &position.x, &position.y, &position.z);
    float m[16];
    int i;
    float *cursor = m;
    for (i = 0; i < 16; ++i) *cursor++ = 0.0f;
    m[0] = m[5] = m[10] = m[15] = 1.0f;
    float y, z, x;
    z = position.z;
    y = position.y;
    x = position.x;
    m[12] = x; m[13] = y; m[14] = z;
    Mtx4x4_TransposeTo4x3(m, matrix);
    driver.p->warp = this;
    if (path) {
        pathId = PathManager_RegisterCarObject(path, &position.x, &position.y, &position.z, 0, driver.p, -1);
        if (pathId == -1) DebugPrintf(lbl_803BD7C8);
    }
    KartItem_SetField2ac(driver.p, pathId);
    int round = g_roundIndex;
    int cup = g_cupId;
    AITuning *tuning = GetKartTuningEntry(GetEnemyParam(), cup, round, id);
    if (tuning->runType % 2 == 1)
        run.reset(new AIRun2(driver.p, tornado.p, kartId, pathId, characterId));
    else
        run.reset(new AIRun1(driver.p, tornado.p, kartId, pathId, characterId));
    if (IsTimerModeEnabled() == 1)
        item.reset(new clEnemyItemDegu(driver.p, tornado.p, kartId, characterId));
}
