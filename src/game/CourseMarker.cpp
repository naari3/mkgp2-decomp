/*
 * 0x80169E34..0x8016A2B8: course marker effect (three animated markers that
 * fly along a curve when a kart comes close). Vtable lbl_80491004, base
 * vtable lbl_80490FE0 (deleting dtor dtor_8016A270). The constructor is real
 * C++ for its EH actions; mangled names are bridged in
 * tools/extab_user_renames.json.
 */

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

typedef struct MarkerPath {
    Vec3f start;
    Vec3f trigger;
    Vec3f end;
} MarkerPath;

typedef struct Marker {
    int state;
    float t;
    float frame;
    Vec3f pos;
    float rotY;
} Marker;

typedef struct KartDriver {
    char pad[0x2D0];
    unsigned char active;
} KartDriver;

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(void *res, int flags);
};

extern "C" {
extern const MarkerPath lbl_8036C8C0[3];
extern char lbl_8036C940[];
extern char lbl_8036C960[];
extern char lbl_80491004[];
extern char lbl_80490FE0[];
extern void *lbl_806CF9D8;
extern unsigned char fn_801379F0(Vec3f *, float);
extern void Object_SetField8_AndDirty(clNormal3D *, float);
extern void clNormal3D_Exec(clNormal3D *);
extern void Object_SetJObjPositionVec(clNormal3D *, Vec3f *);
extern void Object_SetJObjRotationY(clNormal3D *, float);
extern void Object_RenderJObjTree(clNormal3D *, int);
extern KartDriver *GetKartSlotKartVariant(int);
extern float *KartDriver_GetKartRootMtx(KartDriver *);
extern void Vec3_Subtract(const Vec3f *, Vec3f *, Vec3f *);
extern float fn_8025E30C(Vec3f *);
extern void fn_80181F18(const Vec3f *, const Vec3f *, const Vec3f *, Vec3f *, float);
extern double atan2(float, float);
extern void Object_DtorWithGXSync(clNormal3D *, int);
extern void MemoryManager_Free(void *);
extern void MemoryManager_TimedFree(void *);
extern void DebugPrintf(const char *, ...);
extern void clNormal3D_SetScale(clNormal3D *, int, float, float, float, float);
extern void *FUN_8003b120(int);
}

struct CourseMarkerBase {
    virtual void vKeyFunction();
    virtual ~CourseMarkerBase();
    CourseMarkerBase() {}
};

struct CourseMarker : CourseMarkerBase {
    clNormal3D *model;
    Marker *markers;

    CourseMarker();
    virtual void vKeyFunction2();
};

#pragma exceptions on

extern "C" {

void fn_80169E34(CourseMarker *self) {
    int i;

    for (i = 0; i < 3; i++) {
        if (self->markers[i].state == 1 && fn_801379F0(&self->markers[i].pos, 30.0f)) {
            Object_SetField8_AndDirty(self->model, self->markers[i].frame);
            clNormal3D_Exec(self->model);
            Object_SetJObjPositionVec(self->model, &self->markers[i].pos);
            Object_SetJObjRotationY(self->model, self->markers[i].rotY);
            Object_RenderJObjTree(self->model, 7);
        }
    }
}

void fn_80169EFC(CourseMarker *self) {
    int i;
    KartDriver *kart;
    Vec3f kp;
    Vec3f d;

    for (i = 0; i < 8; i++) {
        kart = GetKartSlotKartVariant(i);
        if (kart && kart->active) {
            kp.x = KartDriver_GetKartRootMtx(kart)[3];
            kp.y = KartDriver_GetKartRootMtx(kart)[7];
            kp.z = KartDriver_GetKartRootMtx(kart)[11];
            for (i = 0; i < 3; i++) {
                Vec3_Subtract(&lbl_8036C8C0[i].trigger, &kp, &d);
                if (fn_8025E30C(&d) < 1000000.0f) {
                    if (self->markers[i].state == 0) {
                        self->markers[i].state = 1;
                        self->markers[i].t = 0.0f;
                        self->markers[i].frame = 0.0f;
                        kp = lbl_8036C8C0[i].start;
                    }
                } else if (self->markers[i].state == 2) {
                    self->markers[i].state = 0;
                }
                if (self->markers[i].state == 1) {
                    self->markers[i].frame += 1.0f;
                    self->markers[i].t += 0.0055555557f;
                    if (self->markers[i].t < 1.0f) {
                        d.x = self->markers[i].pos.x;
                        d.y = self->markers[i].pos.y;
                        d.z = self->markers[i].pos.z;
                        fn_80181F18(&lbl_8036C8C0[i].start, &lbl_8036C8C0[i].trigger, &lbl_8036C8C0[i].end, &self->markers[i].pos,
                                    self->markers[i].t);
                        self->markers[i].rotY = atan2(self->markers[i].pos.x - d.x,
                                                      self->markers[i].pos.z - d.z);
                    } else {
                        self->markers[i].state = 2;
                    }
                }
            }
            return;
        }
    }
}

CourseMarker *fn_8016A11C(CourseMarker *self, short flag) {
    if (self) {
        *(char **)self = lbl_80491004;
        Object_DtorWithGXSync(self->model, 1);
        MemoryManager_Free(self->markers);
        DebugPrintf(lbl_8036C940);
        if (self) {
            *(char **)self = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

}

/* real constructor @ 0x8016A1AC: the new-expression carries the
 * DELETEPOINTER guard, the ctor body the DESTROYBASE region. */
CourseMarker::CourseMarker() {
    DebugPrintf(lbl_8036C960);
    model = new clNormal3D(lbl_806CF9D8, 0);
    clNormal3D_SetScale(model, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    markers = (Marker *)FUN_8003b120(sizeof(Marker) * 3);
    markers[0].state = 0;
    markers[1].state = 0;
    markers[2].state = 0;
}

extern "C" {

void fn_8016A26C(void) {
}

CourseMarkerBase *dtor_8016A270(CourseMarkerBase *self, short flag) {
    if (self) {
        *(char **)self = lbl_80490FE0;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_8016A2B8(void) {
}

void fn_8016A2BC(void) {
}

}

#pragma exceptions reset
