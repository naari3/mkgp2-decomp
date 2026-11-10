#include "game/types/size_t.h"
#include "game/mapobject/mapobject.h"
void *operator new(size_t);
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
// Each particle record starts with its active flag.
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
// Original shared resource pool: bounds, RTTI names, messages, model name.
extern "C" const Vec3f lbl_8037DA90[2][5] = {
  {
    {154.16258239746094f, 0.0f, -3856.409423828125f},
    {2851.61767578125f, 0.0f, -3856.40966796875f},
    {2851.617431640625f, 0.0f, -2856.40966796875f},
    {154.16261291503906f, 0.0f, -2856.409423828125f},
    {0.0f, 0.0f, 0.0f}
  },
  {
    {2431.533203125f, 0.0f, -3633.733642578125f},
    {3803.733154296875f, 0.0f, -4088.46630859375f},
    {4258.4658203125f, 0.0f, -2716.266357421875f},
    {2886.265869140625f, 0.0f, -2261.53369140625f},
    {0.0f, 0.0f, 0.0f}
  }
};
extern "C" const char lbl_8037DB08[9] = "clWCSnow";
extern "C" const char lbl_8037DB14[17] = "clMapEffectParts";
extern "C" const char lbl_8037DB28[29] = " DeleteMapEffect : clWCSnow\n";
extern "C" const char lbl_8037DB48[29] = " CreateMapEffect : clWCSnow\n";
extern "C" const char lbl_8037DB68[12] = "ef_snow.dat";
extern "C" {
extern const float lbl_806D95F0;
void clNormal3D_SetFlags(clNormal3D *, unsigned int, int);
void *FUN_8003b120(unsigned long);
}
P_fn_80197D20::P_fn_80197D20() {
    int i;
    DebugPrintf(lbl_8037DB48);
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
    model = new clNormal3D(lbl_8037DB68, 1);
    clNormal3D_SetFlags(model, 0x40000000, 0);
    table = new PartTable(lbl_8037DA90, 2);
    particles = (Particle *)FUN_8003b120(50 * sizeof(Particle));
    for (i = 0; i < 50; i++) {
        particles[i].active = 0;
    }
}
