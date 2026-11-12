#ifndef GAME_SCENE_801638B4_PRIVATE_H
#define GAME_SCENE_801638B4_PRIVATE_H



struct DeleteObject162 { virtual ~DeleteObject162(); };
struct DeleteCar162 {
    virtual void Key();
    virtual ~DeleteCar162();
};
struct RefObject162;
struct RefVtable162 {
    void *slots[12];
    void (*release)(RefObject162 *);
    void (*destroy)(RefObject162 *);
};
struct RefObject162 {
    RefVtable162 *vt;
    unsigned short refs;
};
struct Trace162 { float x, y, z; int n; };
struct LoaderDelete162 {
    int pad0;
    unsigned int seed;
    unsigned char randDebug;
    unsigned char trace;
    char padA[2];
    Trace162 *positions;
    int pad10;
    void *environment;
    RefObject162 *resource;
    DeleteObject162 *child;
    int pad20;
    void *paths;
    void *object;
    void *flag;
    void *reverseFlag;
    void *banner;
    void *system;
    void *ai;
    int pad40;
    float traceTime;
    float fade;
    DemoSceneBase *scene;
};

extern "C" {
extern const float lbl_806D88F0;
extern const char lbl_80369C94[], lbl_80369CCC[];
extern void *g_itemSelects[4];
extern DeleteObject162 *g_courseData[2];
void DebugPrintf(const char *, ...);
void MemoryManager_Free(void *);
void MemoryManager_TimedFree(void *);
void AI_SystemDtor(void *, int);
void fn_80208FE4(void *, int);
void ItemSelect_Dtor(void *, int);
void LakituStart_Dtor(void *, int);
void Jyugemu_Flag_Dtor(void *, int);
void Jyugemu_ReverseFlag_Dtor(void *, int);
void LapBannerScene_Dtor(void *, int);
void PathParticipantArray_Dtor(void *, int);
void SceneFlow_SetFlag1048(unsigned char);
void CourseEnvironment_Dtor(void *, int);
void *GetRaceContextPtr();
void RankingTable_Init(void *);
void fn_8013A6F8();
void CourseBgm_Free();
void HSD_FObjForceLinearInterp(int);
void fn_80121210();
}

static inline int Unref(RefObject162 *p) {
    unsigned char permanent = p->refs == (unsigned short)-1;
    if (permanent) return permanent;
    return p->refs-- == 0;
}
static inline void Release(RefObject162 *p) {
    if (p) {
        if (Unref(p)) {
            if (p) {
                p->vt->release(p);
                p->vt->destroy(p);
            }
        }
    }
}

#endif
