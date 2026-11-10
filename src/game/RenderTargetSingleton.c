#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * Ref-counted render-target singleton used by the kart preview
 * (0x8013C334..0x8013C4A4), same shape as OrthoCam.
 */

#include "game/types/size_t.h"
#include "game/types/HSD_JObj.h"

#include "game/types/RenderTargetHolder.h"

#include "game/types/CharacterData.h"

#include "game/types/KartPreview.h"

extern unsigned int RenderTargetSingleton_bss_806D1558;
extern RenderTargetHolder *RenderTargetSingleton_bss_806D155C;
extern char RenderTargetSingleton_data_8048EA78[];
extern char lbl_806D76D0[];
extern char lbl_806D76D8[];
extern float lbl_806D76E0;
extern float lbl_806D76E4;
extern char KartPreview_data_8048EAD8[];
extern char clCSModelInterface_vtable_8048EAE8[];

extern void HSD_LObjDeleteCurrentAll(int);
extern void HSD_LObjAddCurrent(void *rt);
extern void HSD_LObjRemoveAll(void *rt);
extern void *HSD_LObjLoadDesc(void *desc);
extern void *Alloc(unsigned int size);
extern void MemoryManager_TimedFree(void *p);
extern void Object_SetColorAlphaOnly(void *obj, int, float a);
extern void Object_SetColorRGBA(void *obj, int, float r, float g, float b, float a);
extern void Object_SetJObjRotationY(void *obj, float r);
extern void Object_SetJObjRotationX(void *obj, float r);
extern void Object_SetJObjScaleXYZ(void *obj, float x, float y, float z);
extern void *fn_8013BC98(void);
extern void fn_8013BB1C(void *cam, float x, float y);
extern unsigned char fn_8013BC38(void *cam);
extern void fn_8013BBFC(void *cam);
extern void fn_8013BB9C(void *cam);
extern void fn_8013BCA0(void);
extern void Object_RenderJObjTree(void *obj, int flags);
extern void __assert(char *file, int line, char *expr);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
extern void Object_SetAnimBinding(void *obj, void *anim, int);
extern void Object_DriveAnimMatrix(void *obj);
extern void clNormal3D_SetScale(void *obj, void *anim, float frame, float a, float b, float c);
extern void *Archive_GetRootJObj(void *obj);
extern void ObjectTree_BlendOrCopy_Timed(void *obj, void *a, void *b, int, float t);
extern void clNormal3D_Exec(void *obj);
extern CharacterData *GetCharacterDataEntry(int chara);
extern void HSD_JObjClearFlags(HSD_JObj *jobj, int flags);
extern void HSD_JObjSetFlags(HSD_JObj *jobj, int flags);
extern void Object_DtorWithGXSync(void *obj, int flag);

void fn_8013C334(RenderTargetHolder *h) {
    if (h->active) {
        h->active = 0;
    }
}

int fn_8013C34C(RenderTargetHolder *h) {
    if (!h->rt) {
        return 0;
    }
    if (h->active) {
        return 1;
    }
    HSD_LObjDeleteCurrentAll(0);
    HSD_LObjAddCurrent(h->rt);
    h->active = 1;
    return 1;
}

RenderTargetHolder *fn_8013C3B8(void) {
    return RenderTargetSingleton_bss_806D155C;
}

static inline void RenderTargetHolder_Free(RenderTargetHolder *h) {
    if (h) {
        if (h->rt) {
            HSD_LObjRemoveAll(h->rt);
        }
        MemoryManager_TimedFree(h);
    }
}

void fn_8013C3C0(void) {
    if (RenderTargetSingleton_bss_806D1558 != 0) {
        if (--RenderTargetSingleton_bss_806D1558 == 0) {
            RenderTargetHolder_Free(RenderTargetSingleton_bss_806D155C);
            RenderTargetSingleton_bss_806D155C = 0;
        }
    }
}

C_REGION_END
#pragma cplusplus on
void *operator new(size_t size);
void operator delete(void *p);
struct RenderTargetObj {
    unsigned char active;
    void *rt;
    RenderTargetObj() {
        active = 0;
        rt = HSD_LObjLoadDesc(RenderTargetSingleton_data_8048EA78);
    }
};

extern "C" int fn_8013C428(void) {
    if (RenderTargetSingleton_bss_806D1558 == 0) {
        RenderTargetObj *h = new RenderTargetObj;
        RenderTargetSingleton_bss_806D155C = (RenderTargetHolder *)h;
        if (h == 0) {
            return 0;
        }
    }
    RenderTargetSingleton_bss_806D1558++;
    return 1;
}
#pragma cplusplus reset

