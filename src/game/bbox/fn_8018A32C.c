typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Pair {
    float a;
    float b;
} Pair;

typedef struct ObjView {
    void *vt;
    void *jobj;
    float radius;
    float yoff;
    Vec3 *pos;
    float *rot;
    Pair *frames;
    int count;
} ObjView;

extern unsigned char fn_801379F0(Vec3 *p, float radius);
extern void Object_SetField8_AndDirty(void *jobj, float v);
extern void clNormal3D_Exec(void *jobj);
extern void Object_SetJObjPositionVec(void *jobj, Vec3 *p);
extern void Object_SetJObjRotationY(void *jobj, float r);
extern void Object_RenderJObjTree(void *jobj, int mask);

void fn_8018A32C(ObjView *o) {
    int i;
    Vec3 p;
    if (o->count == 0) {
        return;
    }
    for (i = 0; i < o->count; i++) {
        Vec3 *src = &o->pos[i];
        p.x = src->x;
        p.y = src->y;
        p.z = src->z;
        p.y = p.y + o->yoff;
        if (fn_801379F0(&p, o->radius)) {
            Object_SetField8_AndDirty(o->jobj, o->frames[i].b);
            clNormal3D_Exec(o->jobj);
            Object_SetJObjPositionVec(o->jobj, &o->pos[i]);
            Object_SetJObjRotationY(o->jobj, o->rot[i]);
            Object_RenderJObjTree(o->jobj, 7);
        }
    }
}
