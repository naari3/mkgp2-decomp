/* clCamera: 0x80030A48..0x80030D24.
 * Keep the SDK reference-counting helpers in C mode: their comparison result
 * type affects the inlined IR and the deleting destructor register allocation. */
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


static const float cameraOrigin[3] = { 0.0f, 0.0f, 0.0f };

#pragma cplusplus on
#include "game/types/clCamera.h"

void operator delete(void *p);

extern "C" {
void HSD_CObjEndCurrent(void *);
void HSD_LObjSetupInit(HSDObj *);
float *HSD_CObjGetViewingMtxPtr(HSDObj *);
void fn_80137C8C(const float *, const void *);
int HSD_CObjSetCurrent(HSDObj *);
}
void clCamera::Render() { HSD_CObjEndCurrent(this); }
void clCamera::DebugFlush() {
    HSD_LObjSetupInit(cobj);
    fn_80137C8C(HSD_CObjGetViewingMtxPtr(cobj), projection);
}
int clCamera::Ready() {
    if (archive == 0) return 0;
    return HSD_CObjSetCurrent(cobj) != 0;
}
extern "C" void Stub_NoOp_80030aec(void) {}

clCamera::~clCamera() {
    if (archive) {
        HSD_CObjUnref(cobj);
        clRom_Release(archive);
    }
}
// Fakematch: an uncalled diagnostic preserves the RTTI name's place in the pool.
void clCamera::PrintTypeName() { DebugPrintf("clCamera"); }
extern "C" const char lbl_802E96D0[] = "************************************** \n";
extern "C" const char lbl_802E96FC[] = "CObj ProjectionType is not PERSPECTIVE \n";
extern "C" const char lbl_802E9728[] = "stLine2 line_no1[] = {\n";
extern "C" const char lbl_802E9740[] = "\tLINE1(% 14ff, % 14ff, % 14ff),\n";
extern "C" const char lbl_802E9764[] = "\tLINE_END(%d),\n";
extern "C" const char lbl_802E9774[] = "scene_data";

clCamera::clCamera(const char *name) {

    archive = 0;
    ready = 0;
    flag8 = 0;
    flag9 = 0;
    flagA = 0;
    c = lbl_806D22F4;
    d = lbl_806D22F4;
    nearClip = lbl_806D22F4;
    farClip = lbl_806D22F4;
    archive = FileLoader_Open(name);
    if (archive) {
        desc = (Scene3DDesc *)HSD_ArchiveGetPublicAddress(Archive_GetCurrent(archive), lbl_802E9774);
        if (desc->cobjDesc) {
            cobj = HSD_CObjLoadDesc(*desc->cobjDesc);
            nearClip = HSD_CObjGetNear(cobj);
            farClip = HSD_CObjGetFar(cobj);
            if (HSD_CObjGetProjectionType(cobj) == 1) {
                float aspect = HSD_CObjGetAspect(cobj);
                fn_8013879C(projection, lbl_806D22E0 * HSD_CObjGetFov(cobj), aspect, nearClip,
                            farClip);
            } else {
                DebugPrintf(lbl_802E96D0);
                DebugPrintf(lbl_802E96FC);
                DebugPrintf(lbl_802E96D0);
            }
        }
    }
}


#pragma cplusplus reset
