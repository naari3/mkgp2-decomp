/* Generated asm_fn extab bundle for the pending SceneRender methods. */
/* === extracted from auto_SceneRender_DrawObje_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
typedef struct SRVec3 { float x, y, z; } SRVec3;
typedef struct SRViewingRect {
    SRVec3 origin, up_v, right_v, eye_v, eye_vn;
    float distance;
    float top, bottom, left, right;
    int bits;
} SRViewingRect;
typedef struct SRSList { struct SRSList *next; void *data; } SRSList;
typedef struct SRShadow { SRSList *objects; void *camera; } SRShadow;
typedef struct SRLObj { char pad[8]; unsigned short flags; } SRLObj;
typedef struct SRScene {
    void *vtbl;
    SRShadow *shadow;   /* 0x04 */
    SRLObj *light;      /* 0x08 */
    char pad0C[8];
    SRVec3 interest;    /* 0x14 */
} SRScene;
void HSD_CObjSetInterest(void *cobj, SRVec3 *interest);
void HSD_CObjGetEyePosition(void *cobj, SRVec3 *out);
void HSD_CObjGetUpVector(void *cobj, SRVec3 *out);
void HSD_StartRender(int pass);
void fn_802D47E8(void);
void HSD_MtxGetTranslate(void *mtx, SRVec3 *out);
void HSD_ShadowInit(SRShadow *shadow);
void HSD_ShadowStartRender(SRShadow *shadow);
void HSD_ShadowEndRender(SRShadow *shadow);
void fn_802DBB84(SRShadow *shadow, SRLObj *lobj, float f);
void HSD_ShadowSetViewingRect(SRShadow *shadow, float top, float bottom, float left, float right);
void HSD_ViewingRectInit(SRViewingRect *rect, SRVec3 *position, SRVec3 *interest, SRVec3 *up, int perspective);
int HSD_ViewingRectCheck(SRViewingRect *rect);
void HSD_ViewingRectAddSphere(SRViewingRect *rect, SRVec3 *position, float radius);
extern const float lbl_806D24A8;
extern const float lbl_806D24AC;
extern const float lbl_806D24B0;
extern const float lbl_806D24B4;
extern const float lbl_806D24B8;
extern const float lbl_806D24C4;
}

class ScopedTimer {
public:
    inline ScopedTimer(int slot)
    {
        m_slot = slot;
        m_startTick = OSGetTick();
    }

    inline ~ScopedTimer()
    {
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D24C4);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};

#pragma exceptions on
extern "C" void SceneRender_DrawObjectWithLights(SRScene *self)
{
    ScopedTimer timer(0x12);
    SRViewingRect rect;
    SRVec3 up;
    SRVec3 pos;
    SRSList *node;

    if (self->shadow->objects == 0) {
        return;
    }
    if (self->light != 0) {
        HSD_CObjSetInterest(self->shadow->camera, &self->interest);
        fn_802DBB84(self->shadow, self->light, lbl_806D24A8);
        HSD_CObjGetEyePosition(self->shadow->camera, &pos);
        HSD_CObjGetUpVector(self->shadow->camera, &up);
        HSD_ViewingRectInit(&rect, &pos, &self->interest, &up, (self->light->flags & 3) != 1);
        for (node = self->shadow->objects; node != 0; node = node->next) {
            float dx, dy, dz;
            HSD_MtxGetTranslate((char *)node->data + 0x44, &pos);
            dx = pos.x - self->interest.x;
            dy = pos.y - self->interest.y;
            dz = pos.z - self->interest.z;
            if (dx * dx + dy * dy + dz * dz < lbl_806D24AC) {
                HSD_ViewingRectAddSphere(&rect, &pos, lbl_806D24B0);
            }
        }
        if (HSD_ViewingRectCheck(&rect)) {
            HSD_ShadowSetViewingRect(self->shadow, rect.top, rect.bottom, rect.left, rect.right);
        } else {
            HSD_ShadowSetViewingRect(self->shadow, lbl_806D24B0, lbl_806D24B4, lbl_806D24B4, lbl_806D24B8);
        }
        HSD_StartRender(3);
        HSD_ShadowInit(self->shadow);
        HSD_ShadowStartRender(self->shadow);
        HSD_ShadowEndRender(self->shadow);
        fn_802D47E8();
    }
}
#pragma exceptions reset
#pragma cplusplus reset



/* === extracted from auto_SceneRender_CmdA_8a9_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
typedef struct SRShadowOwner { void *x0; void *shadow; } SRShadowOwner;
extern void HSD_ShadowDeleteObject(void *shadow, void *jobj);

/* --- function index (1 fns, .text 0x8003A9E8..0x8003AA20) ---
 * [  0] 0x8003A9E8 size:0x38    global SceneRender_CmdA_8a9e8
 */

#pragma exceptions on
void SceneRender_CmdA_8a9e8(SRShadowOwner *scene, void *jobj) {
    if (jobj == 0 || scene->shadow == 0) {
        return;
    }
    HSD_ShadowDeleteObject(scene->shadow, jobj);
}
#pragma exceptions reset


/* === extracted from auto_SceneRender_CmdB_8aa_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void HSD_ShadowAddObject(void *shadow, void *jobj);

/* --- function index (1 fns, .text 0x8003AA20..0x8003AA58) ---
 * [  0] 0x8003AA20 size:0x38    global SceneRender_CmdB_8aa20
 */

#pragma exceptions on
void SceneRender_CmdB_8aa20(SRShadowOwner *scene, void *jobj) {
    if (jobj == 0 || scene->shadow == 0) {
        return;
    }
    HSD_ShadowAddObject(scene->shadow, jobj);
}
#pragma exceptions reset


/* === extracted from auto_SceneRender_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void HSD_ShadowRemove(void *);

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern char clShadow_vtable_803F58FC[];

/* --- function index (1 fns, .text 0x8003AA58..0x8003AACC) ---
 * [  0] 0x8003AA58 size:0x74    global SceneRender_Dtor
 */

/* --- forward decls --- */

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */

/* --- asm function bodies (.text order = fn address order) --- */
/* 0x8003AA58 size:0x74 */
#pragma exceptions on
#pragma dont_inline on
void *SceneRender_Dtor(void *this, short flag) {
    if (this != 0) {
        *(void **)this = clShadow_vtable_803F58FC;
        HSD_ShadowRemove(*(void **)((char *)this + 4));
        *(void **)((char *)this + 4) = 0;
        dtor_8003A71C(this, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(this);
        }
    }
    return this;
}
#pragma dont_inline reset
#pragma exceptions reset


