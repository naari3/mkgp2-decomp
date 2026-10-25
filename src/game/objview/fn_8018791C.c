typedef struct Placement {
    float pos[3];
    float rx;
    float ry;
    float rz;
    unsigned char pad[4];
    int hidden;
} Placement;

typedef struct ObjView {
    void *vt;
    void *jobj;
    Placement *places;
} ObjView;

extern unsigned char fn_801379F0(Placement *p, float radius);
extern void Object_SetJObjPositionVec(void *jobj, Placement *p);
extern void Object_SetJObjRotationX(void *jobj, float r);
extern void Object_SetJObjRotationY(void *jobj, float r);
extern void Object_SetJObjRotationZ(void *jobj, float r);
extern void Object_RenderJObjTree(void *jobj, int mask);

void fn_8018791C(ObjView *o) {
    int i;
    Placement *p;
    if (o->places == 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        p = &o->places[i];
        if (p->hidden == 0 && fn_801379F0(p, 20.0f)) {
            Object_SetJObjPositionVec(o->jobj, p);
            Object_SetJObjRotationX(o->jobj, p->rx);
            Object_SetJObjRotationY(o->jobj, p->ry);
            Object_SetJObjRotationZ(o->jobj, p->rz);
            Object_RenderJObjTree(o->jobj, 7);
        }
    }
}
