/*
 * clShadow constructor (Camera_Create), 0x8003AACC..0x8003AC84. The class
 * derives from the clCallback base whose deleting dtor is dtor_8003A71C
 * (SceneRender.c); its own dtor and Exec live in SceneRender.c too. Both
 * dtors are declared-only here so neither vtable is emitted.
 *
 * File-static strings share shadow.cpp's original constant pool. Direct
 * references let MWCC form one pool base and retain the original schedule.
 */
struct HSD_CObj;

struct HSD_LObj {
    unsigned char pad00[8];
    unsigned short flags; /* 0x08 */
};

struct HSD_Shadow {
    unsigned char pad00[4];
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

#include "game/types/shared_data.h"
#ifndef __MWERKS__ /* the names other units use (tools/alias_census.py) */
#define callback_name lbl_802E9D44
#endif
SHARED_STATIC const char lbl_802E9D38[] = "clShadow";
SHARED_STATIC const char callback_name[] = "clCallback";
static const char shadow_header[] = "shadow.h";
static const char infinite_message[] = "LOBJ_INFINITE\n";
static const char point_spot_message[] = "LOBJ_POINT or SPOT\n";
static const char shadow_source[] = "shadow.cpp";

static inline void HSD_ShadowSetLObj(HSD_Shadow *shadow, HSD_LObj *lobj)
{
    if (shadow == 0) {
        __assert(shadow_header, 0x76, lbl_806D24BC);
    }
    shadow->lobj = lobj;
}

static inline void HSD_ShadowSetFlags80(HSD_Shadow *shadow)
{
    if (shadow == 0) {
        __assert(shadow_header, 0x67, lbl_806D24BC);
    }
    shadow->flags = 0x80;
}

class clCallback {
public:
    clCallback() {}
    virtual ~clCallback();
    virtual void Exec() = 0;
};

class clShadow : public clCallback {
public:
    clShadow(int width, int height, HSD_LObj *lobj, float far, float near);
    virtual ~clShadow();
    virtual void Exec();

private:
    HSD_Shadow *m_shadow; /* 0x04 */
    HSD_LObj *m_lobj; /* 0x08 */
    int m_width; /* 0x0C */
    int m_height; /* 0x10 */
    float m_x; /* 0x14 */
    float m_y; /* 0x18 */
    float m_z; /* 0x1C */
};

clShadow::clShadow(int width, int height, HSD_LObj *lobj, float far, float near)
    : m_shadow(0), m_lobj(lobj), m_width(width), m_height(height)
{
    m_shadow = HSD_ShadowAlloc();
    HSD_ShadowSetLObj(m_shadow, m_lobj);
    switch (m_lobj->flags & 3) {
    case 1:
        HSD_CObjSetProjectionType(m_shadow->cobj, 3);
        DebugPrintf(infinite_message);
        break;
    case 2:
    case 3:
        HSD_CObjSetProjectionType(m_shadow->cobj, 2);
        DebugPrintf(point_spot_message);
        break;
    default:
        __assert(shadow_source, 0x28, lbl_806D24D0);
        break;
    }
    HSD_ShadowSetSize(m_shadow, m_width, m_height);
    HSD_CObjSetNear(m_shadow->cobj, near);
    HSD_CObjSetFar(m_shadow->cobj, far);
    HSD_ShadowSetActive(m_shadow, 1);
    HSD_ShadowSetFlags80(m_shadow);
    m_x = m_y = m_z = lbl_806D24D4;
}
