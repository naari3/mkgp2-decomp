#include "game/objview/path186_private.h"
extern "C" {
extern const char lbl_80377030[];
extern int g_courseVariantIdx;
void *FUN_8003b120(unsigned long);
}
struct Path186Def {
    const char *joint[4];
    Vec3f *points;
    int count;
};
struct Path186Base {
    Path186Base() {}
    virtual ~Path186Base();
};
struct Path186View : Path186Base {
    clNormal3D *object;
    Path186 *paths;
    float rotation, phase, phase2;
    Path186View();
    virtual ~Path186View();
};
static inline void CopyPoint(Vec3f *dst, const Vec3f *src) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}
Path186View::Path186View() {
    const char *pool = lbl_80377030;
    DebugPrintf(pool + 0x250);
    object = 0;
    paths = 0;
    rotation = 0.0f;
    phase = 0.0f;
    phase2 = 0.0f;
    const char *name = 0;
    switch (g_courseVariantIdx) {
    case 0: name = pool + 0x270; break;
    case 1: name = pool + 0x284; break;
    case 2: name = pool + 0x298; break;
    }
    if (!name) return;
    object = new clNormal3D(name, 0);
    paths = (Path186 *)FUN_8003b120(0xa8);
    const Path186Def *def = (const Path186Def *)(pool + 0x1ac);
    for (int i = 0; i < 2; i++, def++) {
        paths[i].joint[0] = ResolveJointByName(object, def->joint[0]);
        paths[i].joint[1] = ResolveJointByName(object, def->joint[1]);
        paths[i].joint[2] = ResolveJointByName(object, def->joint[2]);
        paths[i].joint[3] = ResolveJointByName(object, def->joint[3]);
        paths[i].points = def->points;
        paths[i].count = def->count;
        paths[i].index = 0;
        paths[i].time = 0.0f;
        Path186 *p = &paths[i];
        CopyPoint(&p->a, Path186_Point(p,p->index));
        CopyPoint(&p->b, Path186_Point(p,p->index+1));
        CopyPoint(&p->c, Path186_Point(p,p->index+2));
        p->a.x = 0.5f * (p->a.x+p->b.x);
        p->a.y = 0.5f * (p->a.y+p->b.y);
        p->a.z = 0.5f * (p->a.z+p->b.z);
        p->c.x = 0.5f * (p->b.x+p->c.x);
        p->c.y = 0.5f * (p->b.y+p->c.y);
        p->c.z = 0.5f * (p->b.z+p->c.z);
        CopyPoint(&paths[i].position, &paths[i].a);
        paths[i].yaw = 0.0f;
    }
}
