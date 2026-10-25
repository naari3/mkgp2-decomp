typedef struct ObjView {
    void *vt;
    void *jobj;
} ObjView;

extern void Object_RenderJObjTree(void *jobj, int mask);

void fn_80187754(ObjView *o) {
    if (o->jobj != 0) {
        Object_RenderJObjTree(o->jobj, 7);
    }
}
