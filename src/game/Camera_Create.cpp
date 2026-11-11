/* clShadow methods and constructor, 0x8003A764..0x8003AC84.
 * Deferred generation emits the definitions below in reverse source order.
 * clCallback keeps its out-of-line destructor in SceneRender.cpp; each TU
 * emits its own RTTI record, as in the original shadow.cpp/callback.cpp.
 */

struct SRVec3 { float x, y, z; };
struct SRSList { SRSList *next; void *data; };
struct HSD_CObj;

struct HSD_LObj {
    unsigned char pad00[8];
    unsigned short flags; /* 0x08 */
};

struct HSD_Shadow {
    SRSList *objects;
    HSD_CObj *cobj; /* 0x04 */
    unsigned char pad08[0x18];
    unsigned char flags; /* 0x20 */
    unsigned char pad21[3];
    HSD_LObj *lobj; /* 0x24 */
};

extern "C" {
extern char lbl_806D24BC[7]; /* "shadow" */
extern char lbl_806D24D0[2]; /* "0" */
extern const float lbl_806D24D4;
void __assert(const char *file, int line, const char *cond);
void DebugPrintf(const char *fmt, ...);
HSD_Shadow *HSD_ShadowAlloc(void);
void HSD_ShadowSetSize(HSD_Shadow *shadow, unsigned short w, unsigned short h);
void HSD_ShadowSetActive(HSD_Shadow *shadow, int active);
void HSD_CObjSetProjectionType(HSD_CObj *cobj, int type);
void HSD_CObjSetNear(HSD_CObj *cobj, float near);
void HSD_CObjSetFar(HSD_CObj *cobj, float far);
}


static inline void HSD_ShadowSetLObj(HSD_Shadow *shadow, HSD_LObj *lobj)
{
    if (shadow == 0) {
        __assert("shadow.h", 0x76, lbl_806D24BC);
    }
    shadow->lobj = lobj;
}

static inline void HSD_ShadowSetFlags80(HSD_Shadow *shadow)
{
    if (shadow == 0) {
        __assert("shadow.h", 0x67, lbl_806D24BC);
    }
    shadow->flags = 0x80;
}

#include "game/types/clCallback.h"

class clShadow : public clCallback {
public:
    clShadow(int width, int height, HSD_LObj *lobj, float far, float near);
    virtual ~clShadow();
    virtual void Exec();
    void SetViewport(float, float, float, float, float, float);
    void DeleteObject(void *);
    void AddObject(void *);

private:
    HSD_Shadow *m_shadow; /* 0x04 */
    HSD_LObj *m_lobj; /* 0x08 */
    int m_width; /* 0x0C */
    int m_height; /* 0x10 */
    SRVec3 interest; /* 0x14 */
    SRVec3 direction; /* 0x20 */
};

extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
typedef struct SRViewingRect {
    SRVec3 origin, up_v, right_v, eye_v, eye_vn;
    float distance;
    float top, bottom, left, right;
    int bits;
} SRViewingRect;
void HSD_CObjSetInterest(void *cobj, SRVec3 *interest);
void HSD_CObjGetEyePosition(void *cobj, SRVec3 *out);
void HSD_CObjGetUpVector(void *cobj, SRVec3 *out);
void HSD_StartRender(int pass);
void fn_802D47E8(void);
void HSD_MtxGetTranslate(void *mtx, SRVec3 *out);
void HSD_ShadowInit(HSD_Shadow *shadow);
void HSD_ShadowStartRender(HSD_Shadow *shadow);
void HSD_ShadowEndRender(HSD_Shadow *shadow);
void fn_802DBB84(HSD_Shadow *shadow, HSD_LObj *lobj, float f);
void HSD_ShadowSetViewingRect(HSD_Shadow *shadow, float top, float bottom, float left, float right);
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


extern "C" {
void HSD_ShadowRemove(void *);
void HSD_ShadowDeleteObject(void *, void *);
void HSD_ShadowAddObject(void *, void *);
}

clShadow::clShadow(int width, int height, HSD_LObj *lobj, float far, float near)
    : m_shadow(0), m_lobj(lobj), m_width(width), m_height(height)
{
    m_shadow = HSD_ShadowAlloc();
    HSD_ShadowSetLObj(m_shadow, m_lobj);
    switch (m_lobj->flags & 3) {
    case 1:
        HSD_CObjSetProjectionType(m_shadow->cobj, 3);
        DebugPrintf("LOBJ_INFINITE\n");
        break;
    case 2:
    case 3:
        HSD_CObjSetProjectionType(m_shadow->cobj, 2);
        DebugPrintf("LOBJ_POINT or SPOT\n");
        break;
    default:
        __assert("shadow.cpp", 0x28, lbl_806D24D0);
        break;
    }
    HSD_ShadowSetSize(m_shadow, m_width, m_height);
    HSD_CObjSetNear(m_shadow->cobj, near);
    HSD_CObjSetFar(m_shadow->cobj, far);
    HSD_ShadowSetActive(m_shadow, 1);
    HSD_ShadowSetFlags80(m_shadow);
    interest.x = interest.y = interest.z = lbl_806D24D4;
}

clShadow::~clShadow() {
    HSD_ShadowRemove(m_shadow);
    m_shadow = 0;
}


void clShadow::AddObject(void *jobj) {
    if (jobj == 0 || m_shadow == 0) return;
    HSD_ShadowAddObject(m_shadow, jobj);
}


void clShadow::DeleteObject(void *jobj) {
    if (jobj == 0 || m_shadow == 0) return;
    HSD_ShadowDeleteObject(m_shadow, jobj);
}


void clShadow::Exec() {
    ScopedTimer timer(0x12);
    SRViewingRect rect;
    SRVec3 up;
    SRVec3 pos;
    SRSList *node;

    if (m_shadow->objects == 0) {
        return;
    }
    if (m_lobj != 0) {
        HSD_CObjSetInterest(m_shadow->cobj, &interest);
        fn_802DBB84(m_shadow, m_lobj, lbl_806D24A8);
        HSD_CObjGetEyePosition(m_shadow->cobj, &pos);
        HSD_CObjGetUpVector(m_shadow->cobj, &up);
        HSD_ViewingRectInit(&rect, &pos, &interest, &up, (m_lobj->flags & 3) != 1);
        for (node = m_shadow->objects; node != 0; node = node->next) {
            float dx, dy, dz;
            HSD_MtxGetTranslate((char *)node->data + 0x44, &pos);
            dx = pos.x - interest.x;
            dy = pos.y - interest.y;
            dz = pos.z - interest.z;
            if (dx * dx + dy * dy + dz * dz < lbl_806D24AC) {
                HSD_ViewingRectAddSphere(&rect, &pos, lbl_806D24B0);
            }
        }
        if (HSD_ViewingRectCheck(&rect)) {
            HSD_ShadowSetViewingRect(m_shadow, rect.top, rect.bottom, rect.left, rect.right);
        } else {
            HSD_ShadowSetViewingRect(m_shadow, lbl_806D24B0, lbl_806D24B4, lbl_806D24B4, lbl_806D24B8);
        }
        HSD_StartRender(3);
        HSD_ShadowInit(m_shadow);
        HSD_ShadowStartRender(m_shadow);
        HSD_ShadowEndRender(m_shadow);
        fn_802D47E8();
    }
}


void clShadow::SetViewport(float x, float y, float z, float dx, float dy, float dz) {
    interest.x = x; interest.y = y; interest.z = z;
    direction.x = dx; direction.y = dy; direction.z = dz;
}
