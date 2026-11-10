/* C++ with exceptions on, GC/2.6 (GC/1.3.2 schedules the float loads
 * differently and allocates position/direction the other way round).
 * Locals are declared in descending target register order (regalloc_patterns 89).
 */
/* Observed debris ownership and particle layout; TU-local views only. */
#include "game/types/size_t.h"
#pragma cplusplus on
#pragma exceptions on
void *operator new(size_t);
void operator delete(void *);
extern "C" {
extern const float lbl_806D29A8, lbl_806D29C4, lbl_806D29C8, lbl_806D29CC;
extern const float lbl_806D29D0, lbl_806D29D4, lbl_806D29D8, lbl_806D29DC;
extern const float lbl_806D29E0, lbl_806D29E4;
float HSD_Randf(void);
float Saturate_Double(float, float, float);
}
struct InputVec { float x, y, z; };
struct SpawnVec {
    float x, y, z;
    SpawnVec(float a, float b, float c) : x(a), y(b), z(c) {}
    ~SpawnVec() {}
};
struct BoxParticle {
    float x, y, z, vx, vy, vz, acceleration, age, scale, rotation, spin;
    BoxParticle();
    ~BoxParticle();
};
struct BoxDebris {
    unsigned char active, pad[3];
    BoxParticle particles[15];
    BoxDebris() {
        active = 0;
        for (int i = 0; i < 15; ++i) particles[i].age = lbl_806D29A8;
    }
};
struct SpawnResponder { BoxDebris *debris; };
extern "C" SpawnResponder *clItemBoxResponder_SpawnDebris(
    SpawnResponder *self, const InputVec *position, const InputVec *direction)
{
    unsigned int i;
    self->debris = new BoxDebris;
    SpawnVec pos(position->x, position->y, position->z);
    BoxDebris *debris = self->debris;
    float dx, dy, dz, y, x, bx, by, bz;
    dz = direction->z;
    dy = direction->y;
    dx = direction->x;
    debris->active = 1;
    bz = 1.5f * dz;
    by = 1.5f * dy;
    bx = 1.5f * dx;
    for (i = 0; i < 15; ++i) {
        BoxParticle &p = debris->particles[0];
        p.x = pos.x; p.y = pos.y; p.z = pos.z;
        x = lbl_806D29C8 * (lbl_806D29CC * (HSD_Randf() - lbl_806D29D0));
        y = lbl_806D29C8 * (lbl_806D29CC * (HSD_Randf() - lbl_806D29D0));
        float z = lbl_806D29C8 * (lbl_806D29CC * (HSD_Randf() - lbl_806D29D0));
        if (dx * x + dy * y + dz * z < lbl_806D29A8) {
            x = -x; y = -y; z = -z;
        }
        p.vx = x + bx; p.vy = y + by; p.vz = z + bz;
        p.acceleration = lbl_806D29D4;
        p.scale = Saturate_Double(lbl_806D29D8 * HSD_Randf(), lbl_806D29DC, lbl_806D29D8);
        p.rotation = lbl_806D29E0 * HSD_Randf();
        p.spin = lbl_806D29E0 * HSD_Randf();
        p.age = lbl_806D29E4;
        /* fakematch (hand): the target walks the debris pointer itself
         * (stores at 4(r30), no separate induction temp); natural code is
         * `BoxParticle &p = debris->particles[i];` with no manual step. */
        debris = (BoxDebris *)((char *)debris + 0x2c);
    }
    return self;
}
#pragma cplusplus off
#pragma exceptions reset
