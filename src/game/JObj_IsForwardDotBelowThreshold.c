#include "game/PathCursor.h"

extern float *Object_GetJObjLocalMatrix(void *obj);
extern const float lbl_806D2544;

typedef struct ForwardDotObj {
    void *obj;
    unsigned char pad_4[8];
    void *jobj;
} ForwardDotObj;

/* 0x8003DCD4: true if the XZ angle between the object's forward axis and
 * from->to is wider than the lbl_806D2544 cosine threshold. */
int JObj_IsForwardDotBelowThreshold(ForwardDotObj *o, Vec3 *from, Vec3 *to)
{
    float *m;
    Vec3 fwd;
    Vec3 dir;

    if (o->obj == 0 || o->jobj == 0) {
        m = 0;
    } else {
        m = Object_GetJObjLocalMatrix(o->obj);
    }
    fwd.x = m[2];
    fwd.y = 0.0f;
    fwd.z = m[10];
    dir.x = to->x - from->x;
    dir.y = 0.0f;
    dir.z = to->z - from->z;
    Vec3_Normalize(&fwd, &fwd);
    Vec3_Normalize(&dir, &dir);
    if (Vec3_Dot(&fwd, &dir) < lbl_806D2544) {
        return 1;
    }
    return 0;
}
