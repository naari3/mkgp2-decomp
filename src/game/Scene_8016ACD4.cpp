/*
 * 0x8016ACD4..0x8016AF3C: draw / update / deleting destructor of a course
 * object that plays SE 0x3A while the camera looks at it (vtable
 * lbl_8049107C, base vtable lbl_80490FE0).
 */

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

struct CourseObj8016ACD4 {
    void *vtable;
    void *model;
    void *anim;
    unsigned char hit;
    char pad0D[3];
    void *archive;
    float alpha;
};

extern "C" {
extern char lbl_8049107C[];
extern char lbl_80490FE0[];
extern char lbl_8036D4EC[];
extern void Object_SetColorAlphaOnly(void *, int);
extern void Object_RenderJObjTree(void *, int);
extern void fn_8018D64C(void *);
extern void *GetCourseScene3D(void);
extern void CObj_LoadProjMatrix(void *, Vec3f *);
extern float *CObj_GetViewMatrix_Cached(void *);
extern unsigned char fn_80123480(void *, Vec3f *);
extern unsigned char fn_8016C360(int);
extern unsigned char SoundMgr_PlaySE(int);
extern void fn_8016C1B0(int, int);
extern void *CObj_GetLineBufferPtr(void *);
extern void fn_8018D6F0(void *, void *, float *);
extern void *Archive_GetRootJObj(void *);
extern void fn_80182B50(void *, float, float);
extern void fn_8016C394(int);
extern void fn_8018D7CC(void *, int);
extern void fn_80123B48(void *, int);
extern void Object_DtorWithGXSync(void *, int);
extern void MemoryManager_TimedFree(void *);
extern void DebugPrintf(const char *, ...);

#pragma exceptions on

void fn_8016ACD4(CourseObj8016ACD4 *self) {
    if (self->archive && self->alpha > 0.0f) {
        Object_SetColorAlphaOnly(self->archive, 0);
        Object_RenderJObjTree(self->archive, 7);
    }
    if (!self->hit) {
        fn_8018D64C(self->model);
    }
}

void fn_8016AD40(CourseObj8016ACD4 *self) {
    void *cam;
    float *view;
    Vec3f p;

    cam = GetCourseScene3D();
    if (cam) {
        CObj_LoadProjMatrix(cam, &p);
        view = CObj_GetViewMatrix_Cached(cam);
        p.x = 30.0f * view[2] + p.x;
        p.y = 30.0f * view[6] + p.y;
        p.z = 30.0f * view[10] + p.z;
        self->hit = fn_80123480(self->anim, &p);
        if (self->hit) {
            if (!fn_8016C360(0x3A)) {
                SoundMgr_PlaySE(0x3A);
            }
            fn_8016C1B0(0x3A, 0x46);
        } else {
            if (!fn_8016C360(0x3A)) {
                SoundMgr_PlaySE(0x3A);
            }
            fn_8016C1B0(0x3A, 0x64);
            fn_8018D6F0(self->model, CObj_GetLineBufferPtr(cam), view);
        }
    }
    if (self->archive) {
        if (self->hit) {
            self->alpha = 1.0f;
        } else {
            self->alpha = 0.0f;
        }
        fn_80182B50(Archive_GetRootJObj(self->archive), 0.0f, -0.1f);
    }
}

CourseObj8016ACD4 *fn_8016AE8C(CourseObj8016ACD4 *self, short flag) {
    if (self) {
        self->vtable = lbl_8049107C;
        fn_8016C394(0x3A);
        fn_8018D7CC(self->model, 1);
        fn_80123B48(self->anim, 1);
        if (self->archive) {
            Object_DtorWithGXSync(self->archive, 1);
        }
        DebugPrintf(lbl_8036D4EC);
        if (self) {
            self->vtable = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset
}
