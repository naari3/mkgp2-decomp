typedef struct Ref {
    unsigned char pad[0x88];
    float a;
    float b;
} Ref;

typedef struct Obj {
    void *vt;
    Ref *ref;
    unsigned char pad[0x288 - 8];
    float vals[4];
} Obj;

float fn_8019A850(Obj *o, int i) {
    Ref *r = o->ref;
    float v = o->vals[i];
    float d = v - r->b;
    if (i < 2) {
        d = v - r->a;
    }
    return d;
}
