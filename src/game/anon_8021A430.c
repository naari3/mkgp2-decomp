/*
 * 0x8021A430..0x8021A7BC: apply colour / transform to every model of an
 * object group (main + shadow, optional extra pair and an optional effect).
 */

typedef struct ObjGroup {
    int x0;
    void *main;
    void *shadow;
    void *extra;
    void *extraShadow;
    char pad14[0x24 - 0x14];
    void *effect;
} ObjGroup;

void Object_SetColorAlphaOnly(void *obj, int mode, float a);
void Object_SetColorRGBA(void *obj, int mode, float r, float g, float b, float a);
void Object_SetJObjRotationX(void *obj, float v);
void Object_SetJObjRotationY(void *obj, float v);
void Object_SetJObjRotationZ(void *obj, float v);
void Object_SetJObjScaleXYZ(void *obj, float x, float y, float z);
void Object_SetJObjPositionXYZ(void *obj, float x, float y, float z);

void fn_8021A430(ObjGroup *g, float a) {
    if (g->main != 0) {
        Object_SetColorAlphaOnly(g->main, 0, a);
        Object_SetColorAlphaOnly(g->shadow, 0, a);
        if (g->extra != 0) {
            Object_SetColorAlphaOnly(g->extra, 0, a);
            if (g->effect != 0) {
                Object_SetColorAlphaOnly(g->effect, 0, a);
            }
        }
    }
}

void fn_8021A4B8(ObjGroup *g, float r, float gr, float b, float a) {
    if (g->main != 0) {
        Object_SetColorRGBA(g->main, 0, r, gr, b, a);
        Object_SetColorRGBA(g->shadow, 0, r, gr, b, a);
        if (g->extra != 0) {
            Object_SetColorRGBA(g->extra, 0, r, gr, b, a);
            if (g->effect != 0) {
                Object_SetColorRGBA(g->effect, 0, r, gr, b, a);
            }
        }
    }
}

void fn_8021A578(ObjGroup *g, float x, float y, float z) {
    if (g->main != 0) {
        Object_SetJObjRotationX(g->main, x);
        Object_SetJObjRotationY(g->main, y);
        Object_SetJObjRotationZ(g->main, z);
        Object_SetJObjRotationX(g->shadow, x);
        Object_SetJObjRotationY(g->shadow, y);
        Object_SetJObjRotationZ(g->shadow, z);
        if (g->extra != 0) {
            Object_SetJObjRotationX(g->extra, x);
            Object_SetJObjRotationY(g->extra, y);
            Object_SetJObjRotationZ(g->extra, z);
            Object_SetJObjRotationX(g->extraShadow, x);
            Object_SetJObjRotationY(g->extraShadow, y);
            Object_SetJObjRotationZ(g->extraShadow, z);
        }
    }
}

void fn_8021A660(ObjGroup *g, float x, float y, float z) {
    if (g->main != 0) {
        Object_SetJObjScaleXYZ(g->main, x, y, z);
        Object_SetJObjScaleXYZ(g->shadow, x, y, z);
        if (g->extra != 0) {
            Object_SetJObjScaleXYZ(g->extra, x, y, z);
            Object_SetJObjScaleXYZ(g->extraShadow, x, y, z);
            if (g->effect != 0) {
                Object_SetJObjScaleXYZ(g->effect, x, y, z);
            }
        }
    }
}

void fn_8021A71C(ObjGroup *g, float x, float y, float z) {
    if (g->main != 0) {
        Object_SetJObjPositionXYZ(g->main, x, y, z);
        Object_SetJObjPositionXYZ(g->shadow, x, y, z);
        if (g->extra != 0) {
            Object_SetJObjPositionXYZ(g->extra, x, y, z);
            Object_SetJObjPositionXYZ(g->extraShadow, x, y, z);
        }
    }
}
