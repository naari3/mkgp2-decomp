/* Observed constructor layout only; not a complete runtime class definition.
 * The 12-byte step value is a CW member-function pointer, not a word array.
 * External member destructors and array element constructors are bridged in
 * this TU's extab_user_renames entry. All EH is compiler-generated.
 */
#pragma cplusplus on
extern "C" {
extern const float lbl_806D29A8;
extern const char lbl_802EDF20[0xB8];
void DebugPrintf(const char *, ...);
}
void *operator new(unsigned long);
void operator delete(void *);

struct GroundPosition {
    float x, y, z;
    GroundPosition(float a, float b, float c) : x(a), y(b), z(c) {}
    ~GroundPosition();
};
extern "C" unsigned char Terrain_GetGroundHeight(GroundPosition *, float *, GroundPosition *, unsigned int *);
struct GroundItemBox;
typedef void (GroundItemBox::*GroundStep)();
extern "C" const GroundStep lbl_803F9C60;
struct GroundParticle {
    char opaque[0x1C];
    float lifetime;
    char tail[0xC];
    GroundParticle();
    ~GroundParticle();
};
struct GroundDebris {
    unsigned char active;
    GroundParticle particles[15];
    GroundDebris() {
        active = 0;
        for (int i = 0; i < 15; ++i) particles[i].lifetime = lbl_806D29A8;
    }
};
struct GroundMotion {
    unsigned int flag;
    float x, y, z;
    GroundMotion() : flag(0), x(lbl_806D29A8), y(lbl_806D29A8), z(lbl_806D29A8) {}
};
struct GroundItemBox {
    float height;
    GroundDebris *debris;
    GroundPosition position;
    float timer;
    GroundStep step;
    GroundMotion motion;
    GroundItemBox(float x, float z);
};
typedef char GroundParticleSize[(sizeof(GroundParticle) == 0x2C) ? 1 : -1];
typedef char GroundDebrisSize[(sizeof(GroundDebris) == 0x298) ? 1 : -1];
typedef char GroundItemBoxSize[(sizeof(GroundItemBox) == 0x34) ? 1 : -1];

GroundItemBox::GroundItemBox(float x, float z)
    : height(lbl_806D29A8), debris(0), position(x, lbl_806D29A8, z),
      timer(lbl_806D29A8), step(lbl_803F9C60)
{
    motion.flag = 0;
    if (!Terrain_GetGroundHeight(&position, &position.y, 0, 0)) DebugPrintf(lbl_802EDF20);
    height = position.y;
    if (!debris) debris = new GroundDebris;
}
#pragma cplusplus off
