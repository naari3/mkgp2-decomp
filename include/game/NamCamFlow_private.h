#ifndef GAME_NAMCAMFLOW_PRIVATE_H
#define GAME_NAMCAMFLOW_PRIVATE_H
#include "game/FlowScene.h"
extern "C" const float lbl_806DA59C, lbl_806DA5C4, lbl_806DA5C8;
extern "C" void PreloadResource(int);

/* Private views of the camera capture flow, inferred from target accesses. */
extern "C" void MemoryManager_Free(void *);
extern "C" void NamCam_End();

struct NamCamByteHolder {
    unsigned char *p;
    NamCamByteHolder(unsigned char *q) : p(q) {}
    ~NamCamByteHolder();
};
struct NamCamImage {
    unsigned char ready;
    char pad01[3];
    NamCamByteHolder display;
    NamCamByteHolder scratch;
    char texture[0x20];
    NamCamImage();
    ~NamCamImage() {}
};
struct NamCamBuffers {
    int size;
    void *pixels;
    char descriptor[0xC];
    NamCamBuffers();
    ~NamCamBuffers() {
        if (pixels) { MemoryManager_Free(pixels); pixels = 0; }
    }
};
struct NamCamCapture {
    /* These two ordinary owning wrappers intentionally have no throw spec. */
    struct ImageOwner {
        NamCamImage *p;
        ImageOwner(NamCamImage *q) : p(q) {}
        ~ImageOwner();
    } image;
    struct BufferOwner {
        NamCamBuffers *p;
        BufferOwner(NamCamBuffers *q) : p(q) {}
        ~BufferOwner();
    } buffers;
    unsigned char ready;
    char pad09[3];
    void *pixels;
    NamCamCapture();
    ~NamCamCapture() { NamCam_End(); MemoryManager_Free(pixels); }
};
struct NamCamCaptureHolder {
    NamCamCapture *p;
    NamCamCaptureHolder(NamCamCapture *q) : p(q) {}
    ~NamCamCaptureHolder() throw();
};

struct NamCamFlow {
    void *vptr;
    unsigned char finished;
    char pad05[3];
    NamCamCapture *capture;
    int player;
    FlowFaderI *fade;
    int color;
    int timer;
    unsigned char camera;
    char pad1D[3];
    int state;
    FlowSceneList *list;
    TextManager *text;
};

struct NamCamCountdown : FlowTask {
    virtual void _keyCountdown();
    VHolder<FlowFaderI> fade;
    VHolder<FlowFaderF> scale;
    int timer;
    float x, y;
    int resource;
    int layer;
    NamCamCountdown(int id, int res) : FlowTask(id), fade(new FlowFaderI),
        scale(new FlowFaderF(lbl_806DA59C)), timer(0),
        x(lbl_806DA59C), y(lbl_806DA59C), resource(res), layer(7) {
        if (res < 0 || res > 5) resource = 0;
        PreloadResource(resource + 0x68C);
        fade.p->Set(0, 255, 15);
        scale.p->Set(lbl_806DA5C4, lbl_806DA5C8, 15);
    }
    ~NamCamCountdown();
};

struct NamCamScaleHolder {
    FlowFaderF *p;
    ~NamCamScaleHolder() throw();
};
struct NamCamListHolder {
    FlowSceneList *p;
    NamCamListHolder(FlowSceneList *q) : p(q) {}
    ~NamCamListHolder() throw();
};

/* Destructor hierarchy; NamCamFlow above remains the plain access view. */
struct NamCamRoot {
    virtual void _keyRoot();
    unsigned char finished;
    char pad05[3];
    NamCamRoot() : finished(0) {}
    ~NamCamRoot() {}
};
struct NamCamBase : NamCamRoot {
    virtual void _keyBase();
    NamCamCaptureHolder capture;
    int player;
    VHolder<FlowFaderI> fade;
    int color;
    int timer;
    unsigned char camera;
    char pad1D[3];
    NamCamBase(int player);
    ~NamCamBase();
};
/* Text arrays use the UI allocator's untimed array cleanup. */
struct NamCamText : TextManager {
    static void *operator new[](unsigned long);
    static void operator delete[](void *) throw();
    NamCamText();
    ~NamCamText();
};
struct NamCamScene : NamCamBase {
    virtual void _keyScene();
    int state;
    NamCamListHolder list;
    NamCamText *text;
    NamCamScene(int player, int mode);
    ~NamCamScene();
};

extern "C" {
void fn_8011F994(int);
void fn_8011FAB8();
void fn_801F43F8(NamCamImage *);
void fn_80121E10(ResCtrl *);
void fn_8011FAFC(ResCtrl *, int);
void *fn_801F8E58();
void fn_801F8A34(void *, TextManager *, int);
extern const float NamCamFlow_rodata_803BE434[];
extern const float lbl_806DA588, lbl_806DA590, lbl_806DA594;
extern const float lbl_806DA5C8, lbl_806DA5D8, lbl_806DA5DC;
extern const int lbl_806DA854;
int GetDisplayBufferIndex();
void *SyncSlot_GetRecv();
extern int g_localPcbRole;
extern const float lbl_806DA598, lbl_806DA5A8;
extern const float lbl_806DA578[2];
struct NamCamLayout {
    char pad000[0x4E4];
    float labels[4];
    int playerLabels[6][2];
    int icons[11][4];
    int modeLabels[11][2];
};
extern const NamCamLayout NamCamFlow_rodata_803BDF20;
struct NamCamPlayerInput {
    virtual void key0();
    virtual void key1();
    virtual void key2();
    virtual void key3();
    virtual void key4();
    virtual void key5();
    virtual unsigned char Pressed(int mask);
};
void *GetInputManager();
NamCamPlayerInput *InputMgr_GetPlayer(void *, int);
void fn_801FE1FC(int);
void fn_801FE1D8();
void *fn_80271340(void *, int, const void *, const void *, int);
extern const unsigned int lbl_806D0028[2], lbl_806D0020[2];
extern const float lbl_806DA5CC, lbl_806DA5D0, lbl_806DA5D4;
extern const int lbl_806DA858;
void fn_80120A08(int);
void fn_801F8E54();
extern const int NamCamFlow_rodata_803BE4F4[][2], NamCamFlow_rodata_803BE444[][4];
void *FUN_8003b120(unsigned long);
void NamCam_Init();
unsigned char GetVBlankFlag();
unsigned char VBlankValue_Get();
void SetSyncTarget(int);
unsigned char Sci2Card_GetByteFlag1224();
void fn_801F9014(TextManager *, const void *, ...);
void fn_801F93D0(TextManager *, float, float);
extern const char g_playerData[];
extern const char lbl_806DA5AC[1];
extern const float lbl_806DA570[2], lbl_806DA5B0;
extern const int lbl_806DA850, lbl_806DA84C;
extern const char *lbl_806DA94C[], *lbl_806DA9EC[];
extern const float lbl_803BE54C[4], lbl_803BE55C[4];
}
#endif
