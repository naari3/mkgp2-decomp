/* Observed constructor and JObj field views; full runtime layouts unverified. */
#pragma cplusplus on
void* operator new(unsigned long);
void operator delete(void*);
struct ReverseNormal3D {
    unsigned char opaque[0x5C];
    ReverseNormal3D(void* model, int enabled);
};
/* The aggregate's word overlay preserves its copy across the root lookup. */
union ReverseVec3 {
    struct { float x, y, z; } f;
    unsigned int words[3];
};
struct ReverseJObj {
    unsigned char opaque[0x14];
    unsigned int flags;
    unsigned char opaque18[0x14];
    ReverseVec3 scale;
};
extern "C" {
extern unsigned char lbl_806CEFC0[8];
extern const float lbl_806D3078, lbl_806D307C, lbl_806D30A4;
extern const char lbl_806D308C[7], lbl_806D3094[5];
extern unsigned char lbl_80311E24[];
extern const ReverseVec3 lbl_80311DF0;
void fn_8016C510(unsigned char);
unsigned char clNormal3D_SetScale(ReverseNormal3D*, void*, float, float, float, float);
ReverseJObj* Archive_GetRootJObj(ReverseNormal3D*);
void __assert(const char*, int, const char*);
void fn_802D20AC(ReverseJObj*);
}
static inline unsigned char matrix_is_clean(ReverseJObj* jobj)
{
    unsigned int flags;
    unsigned char clean;
    if (jobj == 0) __assert(lbl_806D308C, 0x25D, lbl_806D3094);
    flags = jobj->flags;
    clean = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) clean = 1;
    return clean;
}
static inline void dirty_matrix(ReverseJObj* jobj)
{
    if (jobj != 0) {
        if (!matrix_is_clean(jobj)) fn_802D20AC(jobj);
    }
}
static inline void set_scale(ReverseJObj* jobj, ReverseVec3* scale)
{
    if (jobj == 0) __assert(lbl_806D308C, 0x316, lbl_806D3094);
    jobj->scale.f.x = scale->f.x;
    jobj->scale.f.y = scale->f.y;
    jobj->scale.f.z = scale->f.z;
    if (!(jobj->flags & 0x02000000)) dirty_matrix(jobj);
}
struct JyugemuReverseFlagCtor {
    ReverseNormal3D* normal;
    void* owner;
    unsigned char state, opaque9[3];
    int counter;
    float phase;
    JyugemuReverseFlagCtor(void* owner);
};
JyugemuReverseFlagCtor::JyugemuReverseFlagCtor(void* owner_)
{
    ReverseVec3 scale;
    lbl_806CEFC0[0] = 1;
    normal = 0;
    phase = lbl_806D3078;
    counter = 180;
    fn_8016C510(0);
    state = 0;
    normal = new ReverseNormal3D(lbl_80311E24, 0);
    if (normal == 0) return;
    clNormal3D_SetScale(normal, 0, lbl_806D307C, lbl_806D3078, lbl_806D307C, lbl_806D30A4);
    scale = lbl_80311DF0;
    set_scale(Archive_GetRootJObj(normal), &scale);
    owner = owner_;
}
#pragma cplusplus off

