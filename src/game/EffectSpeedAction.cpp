#include "game/EffectSpeedInitPrivate.h"

extern "C" {
void KartMovement_SetMueScale(void *kart, float scale);
void KartMovement_SetSpeedScale(void *kart, float scale);
void MemoryManager_TimedFree(void *p);
}

void operator delete(void *p);

/* 0x8006520C */
void SpeedInitMue::Reset() {
    KartMovement_SetMueScale(owner->kart, 1.0f);
    value = 0.0f;
}

/* 0x8006524C */
void SpeedInitScale::Reset() {
    KartMovement_SetSpeedScale(owner->kart, 1.0f);
    value = 0.0f;
}

/* 0x8006528C */
SpeedInitAction::~SpeedInitAction() {}

static inline unsigned char Ramp(SpeedInitOwner *o) {
    if (o->field14 == 0) {
        return 0;
    }
    o->field0c += o->field10;
    if (o->field10 > 0) {
        if (o->field08 < o->field0c) {
            o->field14 = 0;
            o->field0c = o->field08;
        }
    } else {
        if (o->field08 > o->field0c) {
            o->field14 = 0;
            o->field0c = o->field08;
        }
    }
    return o->field14;
}

/* 0x800652D4 */
extern "C" void MediaBoard_SendAndCheck(SpeedInitOwner *o) {
    if (o->active) o->active->Reset();
    o->active = 0;
    o->field18 = 0;
    void *render = CarObject_GetRenderObj(o->kart);
    ItemEffectBus_ClearMask(*(void **)((char *)render + 0x304), 0ULL);
}

/* 0x8006533C */
extern "C" bool EffectSpeed_TickTimer(SpeedInitOwner *o) {
    if (o->field18 == 0) {
        return false;
    }
    if (!Ramp(o) || !o->active->Process()) {
        MediaBoard_SendAndCheck(o);
    }
    return true;
}

static inline bool Start(SpeedInitOwner *o, int mode, SpeedInitAction *const *holder, float sec) {
    if (o->field18 != 0) {
        return false;
    }
    o->field18 = mode;
    if (o->field10 > 0) {
        if (o->field08 >= o->field04) goto init;
        goto skip;
    } else {
        if (o->field08 > o->field04) goto skip;
    }
init:
    {
        o->field04 = 0;
        o->field0c = o->field04;
        o->field08 = (int)(60.0f * (60.0f * sec));
        o->field10 = 1;
        o->field14 = 1;
    }
skip:
    o->active = 0;
    o->active = *holder;
    return true;
}

/* 0x80065458 */
extern "C" bool InterpolationStep(SpeedInitOwner *o, float sec, float value) {
    if (!Start(o, 2, (SpeedInitAction *const *)&o->mue.p, sec)) {
        return false;
    }
    SpeedInitMue *a = o->mue.p;
    a->Reset();
    a->value = value;
    return true;
}

/* 0x80065558 */
extern "C" bool EffectSpeed_ApplySpeedScale(SpeedInitOwner *o, float sec, float value) {
    if (!Start(o, 1, (SpeedInitAction *const *)&o->scale.p, sec)) {
        return false;
    }
    SpeedInitScale *a = o->scale.p;
    a->Reset();
    a->value = value;
    return true;
}

/* 0x80065658 */
bool SpeedInitMue::Process() {
    KartMovement_SetMueScale(owner->kart, value);
    return true;
}

/* 0x80065688 */
bool SpeedInitScale::Process() {
    KartMovement_SetSpeedScale(owner->kart, value);
    return true;
}

/* 0x800656B8 */
SpeedMueHolder::~SpeedMueHolder() throw() { delete p; }

/* 0x80065748 */
SpeedScaleHolder::~SpeedScaleHolder() throw() { delete p; }
