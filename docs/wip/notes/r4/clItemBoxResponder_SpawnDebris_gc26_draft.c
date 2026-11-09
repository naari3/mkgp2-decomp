/* === extracted from auto_clItemBoxResponder_S_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */



/* --- function index (1 fns, .text 0x8005E46C..0x8005E788) ---
 * [  0] 0x8005E46C size:0x31C   global clItemBoxResponder_SpawnDebris
 */

/* --- function bodies --- */
/* Observed debris ownership and particle layout; TU-local views only. */
#pragma exceptions on
#pragma cplusplus on
void *operator new(unsigned long);
void operator delete(void *);
extern "C" {
extern const float lbl_806D29A8, lbl_806D29C4, lbl_806D29C8, lbl_806D29CC;
extern const float lbl_806D29D0, lbl_806D29D4, lbl_806D29D8, lbl_806D29DC;
extern const float lbl_806D29E0, lbl_806D29E4;
float HSD_Randf(void);
float Saturate_Double(float, float, float);
}
struct DebrisVec { float x, y, z; };
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
struct DebrisResponder { BoxDebris *debris; DebrisResponder(DebrisVec, DebrisVec); };
#pragma opt_common_subs off
DebrisResponder::DebrisResponder(DebrisVec position, DebrisVec direction)
{
    DebrisResponder *self = this;
    self->debris = new BoxDebris;
    SpawnVec pos(position.x, position.y, position.z);
    float dz = direction.z, dy = direction.y, dx = direction.x;
    float bz = lbl_806D29C4 * dz;
    float by = lbl_806D29C4 * dy;
    float bx = lbl_806D29C4 * dx;
    BoxDebris *debris = self->debris;
    debris->active = 1;
    for (unsigned int i = 0; i < 15; ++i) {
        BoxParticle &p = debris->particles[i];
        p.x = pos.x; p.y = pos.y; p.z = pos.z;
        float x = lbl_806D29C8 * (lbl_806D29CC * (HSD_Randf() - lbl_806D29D0));
        float y = lbl_806D29C8 * (lbl_806D29CC * (HSD_Randf() - lbl_806D29D0));
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
    }
}
#pragma cplusplus reset
#pragma exceptions reset
