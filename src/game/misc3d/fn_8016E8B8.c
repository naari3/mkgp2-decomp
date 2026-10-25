typedef struct Obj { unsigned char pad[0xc]; float t; } Obj;
extern const float lbl_806D8BAC;
extern const float lbl_806D8BB0;
extern const float lbl_806D8BA8;

void fn_8016E8B8(Obj *o) {
    float t = o->t + lbl_806D8BAC;
    o->t = t;
    if (t > lbl_806D8BB0) {
        o->t = lbl_806D8BA8;
    }
}
