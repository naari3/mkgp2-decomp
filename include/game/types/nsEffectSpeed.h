#ifndef NS_EFFECT_SPEED_CLASSES_H
#define NS_EFFECT_SPEED_CLASSES_H
#include "game/types/size_t.h"
extern "C" {
void *MemoryManager_AllocTagged(unsigned long, const char *, int);
void *CarObject_GetRenderObj(void *);
void ItemEffectBus_ClearMask(void *, unsigned long long);
extern const char lbl_802EE510[];
}
inline void *operator new(size_t n, const char *file, int line) { return MemoryManager_AllocTagged(n,file,line); }
struct SpeedInitOwner;
namespace nsEffectSpeed {
struct clAction {
    clAction() {}
    virtual bool Process() = 0;
    virtual void Reset() = 0;
    virtual ~clAction();
    SpeedInitOwner *owner;
    float value;
};
struct clActionSpeedScale : clAction {
    virtual bool Process();
    virtual ~clActionSpeedScale();
    virtual void Reset();
    clActionSpeedScale(SpeedInitOwner *p) { owner=p; Reset(); }
};
struct clActionMueScale : clAction {
    virtual void Reset();
    virtual ~clActionMueScale();
    virtual bool Process();
    clActionMueScale(SpeedInitOwner *p) { owner=p; Reset(); }
};
}
typedef nsEffectSpeed::clAction SpeedInitAction;
typedef nsEffectSpeed::clActionMueScale SpeedInitMue;
typedef nsEffectSpeed::clActionSpeedScale SpeedInitScale;
struct SpeedScaleHolder {
    SpeedInitScale *p;
    SpeedScaleHolder(SpeedInitScale *v):p(v) {}
    ~SpeedScaleHolder() throw();
};
struct SpeedMueHolder {
    SpeedInitMue *p;
    SpeedMueHolder(SpeedInitMue *v):p(v) {}
    ~SpeedMueHolder() throw();
};
struct SpeedInitOwner {
    void *kart;
    int field04, field08, field0c, field10;
    unsigned char field14;
    int field18;
    SpeedInitAction *active;
    SpeedScaleHolder scale;
    SpeedMueHolder mue;
    SpeedInitOwner(void *);
};
#endif
