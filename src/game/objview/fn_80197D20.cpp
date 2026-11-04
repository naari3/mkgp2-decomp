#include "game/mapobject/mapobject.h"
void *operator new(unsigned long);
void operator delete(void *) throw();
struct clMapEffectParts {
    virtual ~clMapEffectParts();
    virtual void Update();
    virtual void Draw();
    virtual void Enable(int);
    clMapEffectParts() {}
};
struct PartTable {
    void *data;
    PartTable(const void *, int);
};
struct Particle {
    unsigned char active;
    unsigned char rest[0x23];
};
struct P_fn_80197D20 : clMapEffectParts {
    clNormal3D *model;
    PartTable *table;
    Particle *particles;
    void *x10;
    unsigned char enabled;
    unsigned char state;
    unsigned char pad16[2];
    float x18, x1c, x20;
    int x24, x28, x2c, x30;
    P_fn_80197D20();
    virtual ~P_fn_80197D20();
};
extern "C" {
extern const char lbl_8037DA90[];
extern const float lbl_806D95F0;
void clNormal3D_SetFlags(clNormal3D *, unsigned int, int);
void *FUN_8003b120(unsigned long);
}
P_fn_80197D20::P_fn_80197D20() {
    const char *data = lbl_8037DA90;
    int i;
    DebugPrintf(data + 0xB8);
    model = 0;
    table = 0;
    particles = 0;
    x10 = 0;
    enabled = 1;
    state = 0;
    x18 = lbl_806D95F0;
    x1c = lbl_806D95F0;
    x20 = lbl_806D95F0;
    x24 = 0;
    x28 = 0;
    x2c = 0;
    x30 = 0;
    model = new clNormal3D(data + 0xD8, 1);
    clNormal3D_SetFlags(model, 0x40000000, 0);
    table = new PartTable(data, 2);
    particles = (Particle *)FUN_8003b120(50 * sizeof(Particle));
    for (i = 0; i < 50; i++) {
        particles[i].active = 0;
    }
}
