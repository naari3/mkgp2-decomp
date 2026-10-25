typedef struct ObjView {
    void *vt;
    void *jobj;
    float rot;
} ObjView;

extern void Object_SetJObjRotationY(void *jobj, float r);

void fn_80187784(ObjView *o) {
    if (o->jobj != 0) {
        o->rot += 0.006283186f;
        if (o->rot >= 6.2831855f) {
            o->rot -= 6.2831855f;
        }
        Object_SetJObjRotationY(o->jobj, o->rot);
    }
}
