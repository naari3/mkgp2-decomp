struct Vec3f {
    float x, y, z;
};

struct HSD_CObj;

class Scene3D {
public:
    virtual ~Scene3D();
    HSD_CObj *cobj;
    char pad08[0x307C];
    Scene3D(const char *name);
};

class clNormal3D {
public:
    char pad00[0x24];
    void *archive;
    char pad28[0x34];
    clNormal3D(const char *desc, int flags);
    ~clNormal3D();
};

struct clPathNode {
    char pad[0x34];
    clPathNode *next;
    ~clPathNode() {}
};

extern "C" {
extern clPathNode *lbl_806D163C;
extern clPathNode *lbl_806D1640;
extern unsigned int lbl_806D1614;
extern Scene3D *lbl_806D1618;
extern float lbl_806D161C;
extern clNormal3D *lbl_806D1620;
extern float lbl_806D1624;
extern int lbl_806CFB7C;
extern float lbl_806CFB80;
extern unsigned char lbl_806CFB84;
extern Vec3f lbl_80677D00;
extern Vec3f lbl_80677D0C;
extern const char lbl_80376B78[];
extern char lbl_806D91C0[5];
extern char lbl_806D91C8[2];
void GXDrawDone(void);
void SetCourseScene3D(Scene3D *scene);
void TransparentDraw_RemoveByOwner(int owner);
void clNormal3D_SetFlags(clNormal3D *obj, unsigned int flags, int arg);
void clNormal3D_SetScale(clNormal3D *, int, float, float, float, float);
int SceneDrawList_RegisterArchive(void *archive, int layer);
void HSD_CObjSetEyePosition(HSD_CObj *cobj, Vec3f *pos);
void HSD_CObjSetInterest(HSD_CObj *cobj, Vec3f *pos);
void HSD_CObjSetRoll(HSD_CObj *cobj, float roll);
void *Archive_GetCurrent(void *archive);
const char *HSD_ArchiveGetPublicName(void *archive, int index);
void DebugPrintf(const char *fmt, ...);
}

static inline void RemoveNode(clPathNode *n) {
    clPathNode *p;
    clPathNode *q;
    if (n == 0) {
        return;
    }
    p = lbl_806D163C;
    if (n == p) {
        lbl_806D163C = n->next;
        delete n;
        lbl_806D1640 = lbl_806D163C;
        return;
    }
    for (; (q = p->next) != 0; p = q) {
        if (q == n) {
            clPathNode *next = q->next;
            delete q;
            p->next = next;
            lbl_806D1640 = p;
            return;
        }
    }
}

extern "C" void fn_8017E824(const char *name) {
    GXDrawDone();
    while (lbl_806D1640 != 0) {
        RemoveNode(lbl_806D1640);
    }
    if (lbl_806D1618 != 0) {
        delete lbl_806D1618;
        lbl_806D1618 = 0;
    }
    SetCourseScene3D(0);
    if (lbl_806D1620 != 0) {
        delete lbl_806D1620;
        lbl_806D1620 = 0;
    }
    if (lbl_806CFB7C >= 0) {
        TransparentDraw_RemoveByOwner(lbl_806CFB7C);
        lbl_806CFB7C = -1;
    }
    if (name == 0) {
        return;
    }
    lbl_806D1618 = new Scene3D(name);
    lbl_806D1620 = new clNormal3D(name, 0);
    clNormal3D_SetFlags(lbl_806D1620, 0x40000000, 0);
    if (lbl_806D1618 == 0 || lbl_806D1620 == 0) {
        return;
    }
    clNormal3D_SetScale(lbl_806D1620, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    SetCourseScene3D(lbl_806D1618);
    lbl_806CFB7C = SceneDrawList_RegisterArchive(lbl_806D1620->archive, 4);
    if (lbl_806D1614 == 1) {
        lbl_80677D00.x = 0.0f;
        lbl_80677D0C.x = 0.0f;
        lbl_80677D00.y = 500.0f;
        lbl_80677D00.z = 0.0f;
        lbl_80677D0C.y = -1.0f;
        lbl_80677D0C.z = 0.0f;
        lbl_806D161C = 1.570796f;
    } else {
        lbl_80677D00.x = 0.0f;
        lbl_80677D00.y = 0.0f;
        lbl_80677D00.z = 200.0f;
        lbl_80677D0C.x = 0.0f;
        lbl_80677D0C.y = 0.0f;
        lbl_80677D0C.z = -1.0f;
        lbl_806D161C = 0.0f;
    }
    HSD_CObj *cobj = lbl_806D1618->cobj;
    if (cobj != 0) {
        Vec3f at;
        at.x = 200.0f * lbl_80677D0C.x + lbl_80677D00.x;
        at.y = 200.0f * lbl_80677D0C.y + lbl_80677D00.y;
        at.z = 200.0f * lbl_80677D0C.z + lbl_80677D00.z;
        HSD_CObjSetEyePosition(cobj, &lbl_80677D00);
        HSD_CObjSetInterest(cobj, &at);
        HSD_CObjSetRoll(cobj, lbl_806D161C);
    }
    lbl_806D1624 = 0.0f;
    lbl_806CFB80 = 1.0f;
    lbl_806CFB84 = 1;
    if (lbl_806D1620->archive != 0) {
        void *arc = Archive_GetCurrent(lbl_806D1620->archive);
        DebugPrintf(lbl_80376B78, name);
        for (int i = 0;; i++) {
            const char *s = HSD_ArchiveGetPublicName(arc, i);
            if (s == 0) {
                break;
            }
            DebugPrintf(lbl_806D91C0, s);
        }
        DebugPrintf(lbl_806D91C8);
    }
}
