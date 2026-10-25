/*
 * clShadow constructor (Camera_Create), 0x8003AACC..0x8003AC84. The class
 * derives from the clCallback base whose deleting dtor is dtor_8003A71C
 * (SceneRender.c); its own dtor and Exec live in SceneRender.c too. Both
 * dtors are declared-only here so neither vtable is emitted.
 *
 * NonMatching: only the string-pool base register differs (target r9, here
 * r3). The original used pooled literals from shadow.cpp's .rodata
 * (0x802E9D38..), which is not split out yet.
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
extern const char lbl_802E9D38[]; /* shadow.cpp string pool */
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

#define SHADOW_STR_SHADOW_H 0x18
#define SHADOW_STR_INFINITE 0x24
#define SHADOW_STR_POINT_SPOT 0x34
#define SHADOW_STR_SHADOW_CPP 0x48

static inline void HSD_ShadowSetLObj(const char *strings, HSD_Shadow *shadow, HSD_LObj *lobj)
{
    if (shadow == 0) {
        __assert(strings + SHADOW_STR_SHADOW_H, 0x76, lbl_806D24BC);
    }
    shadow->lobj = lobj;
}

static inline void HSD_ShadowSetFlags80(const char *strings, HSD_Shadow *shadow)
{
    if (shadow == 0) {
        __assert(strings + SHADOW_STR_SHADOW_H, 0x67, lbl_806D24BC);
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
    const char *strings = lbl_802E9D38;

    m_shadow = HSD_ShadowAlloc();
    HSD_ShadowSetLObj(strings, m_shadow, m_lobj);
    switch (m_lobj->flags & 3) {
    case 1:
        HSD_CObjSetProjectionType(m_shadow->cobj, 3);
        DebugPrintf(strings + SHADOW_STR_INFINITE);
        break;
    case 2:
    case 3:
        HSD_CObjSetProjectionType(m_shadow->cobj, 2);
        DebugPrintf(strings + SHADOW_STR_POINT_SPOT);
        break;
    default:
        __assert(strings + SHADOW_STR_SHADOW_CPP, 0x28, lbl_806D24D0);
        break;
    }
    HSD_ShadowSetSize(m_shadow, m_width, m_height);
    HSD_CObjSetNear(m_shadow->cobj, near);
    HSD_CObjSetFar(m_shadow->cobj, far);
    HSD_ShadowSetActive(m_shadow, 1);
    HSD_ShadowSetFlags80(strings, m_shadow);
    m_x = m_y = m_z = lbl_806D24D4;
}
