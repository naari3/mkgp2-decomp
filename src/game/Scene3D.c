/* Scene3D: camera scene loaded from an archive, 0x80030AF0..0x80030D24.
 * The view layout matches CObjDebugRender.c. */
typedef struct HSDClassInfo {
    unsigned char pad[0x30];
    void (*release)(void *obj);
    void (*destroy)(void *obj);
} HSDClassInfo;

typedef struct HSDObj {
    HSDClassInfo *info;
    unsigned short ref_count;
} HSDObj;

typedef struct Scene3DDesc {
    unsigned char pad0[4];
    void **cobjDesc;
} Scene3DDesc;

typedef struct Scene3D {
    void *vtable; /* 0x00 */
    HSDObj *cobj; /* 0x04 */
    unsigned char flag8; /* 0x08 */
    unsigned char flag9; /* 0x09 */
    unsigned char flagA; /* 0x0A */
    float c; /* 0x0C */
    float d; /* 0x10 */
    unsigned char pad14[0x10];
    unsigned int ready; /* 0x24 */
    void *archive; /* 0x28 */
    Scene3DDesc *desc; /* 0x2C */
    unsigned char pad30[0x3004];
    unsigned char projection[0x48]; /* 0x3034 */
    float near; /* 0x307C */
    float far; /* 0x3080 */
} Scene3D;

extern char lbl_803F56B8[];
extern char lbl_802E96B8[];
extern const float lbl_806D22E0;
extern const float lbl_806D22F4;

void clRom_Release(void *archive);
void *FileLoader_Open(const char *name);
void *Archive_GetCurrent(void *archive);
void *HSD_ArchiveGetPublicAddress(void *archive, const char *name);
HSDObj *HSD_CObjLoadDesc(void *desc);
float HSD_CObjGetNear(HSDObj *cobj);
float HSD_CObjGetFar(HSDObj *cobj);
int HSD_CObjGetProjectionType(HSDObj *cobj);
float HSD_CObjGetAspect(HSDObj *cobj);
float HSD_CObjGetFov(HSDObj *cobj);
void fn_8013879C(void *proj, float fov, float aspect, float near, float far);
void DebugPrintf(const char *fmt, ...);
void MemoryManager_TimedFree(void *p);

static inline int ref_DEC(void *o)
{
    int ret;
    if ((ret = (unsigned char)(((HSDObj *)o)->ref_count == (unsigned short)-1))) {
        return ret;
    }
    return (((HSDObj *)o)->ref_count-- == 0) & 0xFF;
}

static inline void hsdDelete(void *object)
{
    if (object == 0) {
        return;
    }
    ((HSDObj *)object)->info->release(object);
    ((HSDObj *)object)->info->destroy(object);
}

static inline void HSD_CObjUnref(HSDObj *cobj)
{
    if (cobj == 0) {
        return;
    }
    if (ref_DEC(cobj) != 0) {
        hsdDelete(cobj);
    }
}

#pragma exceptions on

Scene3D *Object_DtorTree_56b8(Scene3D *self, short flag) {
    if (self) {
        self->vtable = lbl_803F56B8;
        if (self->archive) {
            HSD_CObjUnref(self->cobj);
            clRom_Release(self->archive);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

Scene3D *Scene3D_Init(Scene3D *self, const char *name) {
    char *str = lbl_802E96B8;

    self->vtable = lbl_803F56B8;
    self->archive = 0;
    self->ready = 0;
    self->flag8 = 0;
    self->flag9 = 0;
    self->flagA = 0;
    self->c = lbl_806D22F4;
    self->d = lbl_806D22F4;
    self->near = lbl_806D22F4;
    self->far = lbl_806D22F4;
    self->archive = FileLoader_Open(name);
    if (self->archive) {
        self->desc = HSD_ArchiveGetPublicAddress(Archive_GetCurrent(self->archive), str + 0xBC);
        if (self->desc->cobjDesc) {
            self->cobj = HSD_CObjLoadDesc(*self->desc->cobjDesc);
            self->near = HSD_CObjGetNear(self->cobj);
            self->far = HSD_CObjGetFar(self->cobj);
            if (HSD_CObjGetProjectionType(self->cobj) == 1) {
                float aspect = HSD_CObjGetAspect(self->cobj);
                fn_8013879C(self->projection, lbl_806D22E0 * HSD_CObjGetFov(self->cobj), aspect, self->near,
                            self->far);
            } else {
                DebugPrintf(str + 0x18);
                DebugPrintf(str + 0x44);
                DebugPrintf(str + 0x18);
            }
        }
    }
    return self;
}

#pragma exceptions reset
