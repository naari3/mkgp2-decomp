/* === extracted from auto_ReverseChallenge_Dto_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ClRomTable_PurgeAll();
extern void CourseEnvironment_Dtor();
extern void *GetRaceContextPtr();
extern void ItemObjectManager_Reset();
extern void LakituStart_Dtor();
extern void MemoryManager_TimedFree();
extern void RankingTable_Init();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
extern void dtor_80122FD8();
extern void fn_80124C84();
extern void fn_8016C634();
extern void fn_80254134();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceCamera;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806D10AC;
extern unsigned int lbl_806D10D0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int ReverseChallenge_vtable_80419E70[];

/* --- function index (1 fns, .text 0x800ACD60..0x800ACFC0) ---
 * [  0] 0x800ACD60 size:0x260   global ReverseChallenge_Dtor
 */

/* --- native C++ island (deleting-destructor shape, see RivalRun.c) --- */
#pragma cplusplus on
struct RCVirtual {
    virtual ~RCVirtual();
};
struct RCCarVirtual {
    virtual void key();
    virtual ~RCCarVirtual();
};
struct RCLight;
struct RCLightInfo {
    unsigned char pad0[0x30];
    void (*release)(RCLight *);
    void (*destroy)(RCLight *);
};
struct RCLight {
    RCLightInfo *info;
    unsigned short references;
};
struct ReverseChallengeState {
    void *vtable;
    char pad4[4];
    void *environment;
    RCVirtual *camera;
    RCLight *lights;
    RCCarVirtual *car;
    void *lakitu;
    RCVirtual *scene;
    void *goalCamera;
    void *hud;
    void *buffer;
};

static inline int RCLightRefDec(RCLight *obj)
{
    unsigned char unreferenced;
    if ((unreferenced = (obj->references == (unsigned short)0xFFFF)))
        return unreferenced;
    return obj->references-- == 0;
}
static inline void RCLightDelete(RCLight *obj)
{
    if (obj) {
        obj->info->release(obj);
        obj->info->destroy(obj);
    }
}
static inline void RCLightUnref(RCLight *obj)
{
    if (obj && RCLightRefDec(obj))
        RCLightDelete(obj);
}
static inline void RCCameraRelease(RCVirtual *camera)
{
    if (camera)
        delete camera;
}

#pragma exceptions on
extern "C" void *ReverseChallenge_Dtor(ReverseChallengeState *self, short freeMemory)
{
    if (self) {
        self->vtable = ReverseChallenge_vtable_80419E70;
        if (g_weatherSystem) {
            fn_8016C634((void *)g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        delete self->scene;
        LakituStart_Dtor(self->lakitu, 1);
        fn_80124C84(self->goalCamera, 1);
        SetPlayerCarObject(0);
        delete self->car;
        g_raceCamera = 0;
        RCCameraRelease(self->camera);
        if (self->lights)
            RCLightUnref(self->lights);
        CourseEnvironment_Dtor(self->environment, 1);
        fn_80254134(self->hud, 1);
        if (self->buffer)
            MemoryManager_TimedFree(self->buffer);
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        GetRaceContextPtr();
        RankingTable_Init();
        delete (RCVirtual *)lbl_806D10D0;
        lbl_806D10D0 = 0;
        SceneDrawList_Reset();
        delete (RCVirtual *)lbl_806D109C;
        lbl_806D109C = 0;
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        delete (RCVirtual *)lbl_806D10AC;
        lbl_806D10AC = 0;
        dtor_80122FD8(self, 0);
        if (freeMemory > 0)
            MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma exceptions reset
#pragma cplusplus reset
