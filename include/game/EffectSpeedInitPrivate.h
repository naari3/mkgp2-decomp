#ifndef EFFECT_SPEED_INIT_PRIVATE_H
#define EFFECT_SPEED_INIT_PRIVATE_H
extern "C" {
void *MemoryManager_AllocTagged(unsigned long, const char *, int);
void *CarObject_GetRenderObj(void *);
void ItemEffectBus_ClearMask(void *, unsigned long long);
extern const char lbl_802EE510[];
}
inline void *operator new(unsigned long n, const char *file, int line) { return MemoryManager_AllocTagged(n,file,line); }
struct SpeedInitOwner;
struct SpeedInitAction {
    SpeedInitAction() {}
    virtual ~SpeedInitAction();
    virtual void Reset();
    virtual void Tick();
    SpeedInitOwner *owner;
    float value;
};
struct SpeedInitScale : SpeedInitAction {
    virtual ~SpeedInitScale();
    virtual void Reset();
    SpeedInitScale(SpeedInitOwner *p) { owner=p; Reset(); }
};
struct SpeedInitMue : SpeedInitAction {
    virtual ~SpeedInitMue();
    virtual void Reset();
    SpeedInitMue(SpeedInitOwner *p) { owner=p; Reset(); }
};
struct SpeedScaleHolder {
    SpeedInitScale *p;
    SpeedScaleHolder(SpeedInitScale *v):p(v) {}
    ~SpeedScaleHolder();
};
struct SpeedMueHolder {
    SpeedInitMue *p;
    SpeedMueHolder(SpeedInitMue *v):p(v) {}
    ~SpeedMueHolder();
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
