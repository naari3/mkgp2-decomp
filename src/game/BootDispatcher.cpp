#include "game/types/size_t.h"
#pragma inline_max_size(10000)
#pragma inline_max_total_size(100000)
#include "game/BootDispatcher_private.h"
#include "game/TestMenuPage.h"

extern "C" {
unsigned int OSGetTick();
void Profiler_RecordFrame(int, float);
void *Alloc(unsigned long);
void MemoryManager_TimedFree(void *);
void MemoryManager_Free(void *);
void *memset(void *, int, unsigned long);
void DebugPrintf(const char *, ...);
void OverlayText(int, int, int, const char *, ...);
void BootStateStruct_RefreshIfDue();
unsigned int PPCMfhid0();
void PPCMthid0(unsigned int);
void fn_80287FDC(void *);
int fn_80255640(int, int, BootError *);
unsigned int fn_8028B090();
void *fn_80287EC4(int);
void fn_80289D4C(int);
BootState *fn_80293BBC();
int fn_80293BCC();
void fn_802554DC();
void SceneFlow_InitCleanupList();
void SceneFlow_SetCleanupTag(int);
void *OSGetArenaHi();
void *OSGetArenaLo();
void *OSInitAlloc(void *, void *, int);
void OSSetArenaLo(void *);
void HSD_SetInitParameter(int, ...);
void HSD_InitComponent(void *);
void VIWaitForRetrace();
void GameBoot_Init();
void PlayStats_LoadOrInitForBoot();
void RaceContext_EnsureSingleton();
void Sci2Card_FlagReceiptTestEnable();
void InputMgr_Init();
void StrPcb_EnsureInstance();
void JvsInput_SetSteeringCalibration(int);
void JvsInput_SetAccelCalibration(int);
void JvsInput_SetBrakeCalibration(int);
void *StrPcb_GetInstance();
void StrPcb_SetPositionTarget(void *, short);
void StrPcb_SetIntensityMode(void *, int);
void ClSound_InitSoundSystem();
void fn_801934A0(unsigned char);
void fn_8019345C(unsigned char);
void fn_80193404(unsigned char);
void fn_801951E4(unsigned char);
void fn_801951CC(unsigned char);
void Sci2Card_Singleton_GetOrCreate(int);
void HSD_VISetBlack(int);
void *FUN_8003b120(unsigned int);
void fn_801F8E58();
void StrPcb_BeginEffect(void *, int);
void StrPcb_DrainInputBuffer(void *);
void fn_801213EC();
int CardTaskManager_Tick(void *);
void CardTaskManager_RenderOverlay(void *);
void CardTaskManager_Dtor(void *, int);
void HSD_StartRender(int);
void fn_802D47E8();
void SpriteHandlePool_GC();
unsigned int GXGetTexBufferSize(int,int,int,int,int);
void GXSetTexCopySrc(int,int,int,int);
void GXSetTexCopyDst(int,int,int,int);
void GXCopyTex(void *, int);
void GXDrawDone();
void fn_8018F14C();
void HSD_VICopyXFBAsync(int);
void HSD_VIDrawDoneXFBAll();
void GXInvalidateTexAll();
void *Sci2Card_Singleton_Get();
void Sci2Card_Tick(void *);
void *GetInputManager();
void InputObj_TickAndDispatch(void *);
void StrPcb_OutputTick(void *);
void fn_80193624();
void FrameUpdate();
void CreditMgr_PollInsertAndPlay(int);
unsigned char ServiceButton_Handler();
void PcbComm_Shutdown();
void FreeMediaBuffers();
void Sci2Card_Shutdown();
void fn_80193838();
void InputMgr_Shutdown();
void StrPcb_Shutdown();
void PlayStats_ShutdownStub();
void Backup_Shutdown();
void fn_80255620();
void fn_80287EE4(int,void *);
void fn_80121210();
void *DVDGetFSTLocation();
void fn_802928DC();
void fn_80290ED8();
void InitGlobalTimer();
void PCBComm_Init();
void BootPCBCheck_Init();
void BootPCBCheck_Display();
unsigned char BootPCBCheck_Poll();
void Timer_Decrement();
void PCBComm_Process(int,int);
int BootNotice_CheckEnterCondition();
void SetSyncTarget(int);
void DisplayContext_Flush(void *);
void fn_8011F994(int);
void fn_801DB68C(void *,int);
extern void (*g_dvdLoadCallback)();

extern BootState g_bootState;
extern BootConfig lbl_80598A60;
extern BootHooks lbl_806CED28;
extern unsigned char lbl_806D0FA1, g_serviceEnable, vblank_flag;
extern unsigned char g_vblankValue, g_serviceValue, lbl_806D0F96, lbl_806D0F97;
extern unsigned char Boot_bss_806D0FA0, lbl_806D0F8E, lbl_806CED30;
extern BootTimer *g_bootTimer;
extern const float lbl_806D2294, SAFE, lbl_806D22A8;
extern const char lbl_806D22AC[4];
extern char g_backupBufferTexture[];
extern BootVI HSD_VIData;
extern BootColor lbl_806CED34;
extern void *g_cardTaskManager, *lbl_806D1880, *lbl_806D12DC;
extern char *lbl_806D0FC8;
extern unsigned int BootDispatcher_bss_806D0FCC, BootDispatcher_bss_806D0FD0, BootDispatcher_bss_806D0FD4;
extern const char lbl_806D2290[4];

}

#pragma force_active on
#include "game/types/shared_data.h"
SHARED_STATIC const char lbl_802E8F48[0x14] = "             NOTICE";
static const char lbl_802E8F5C[0x22] = " THIS GAME IS FOR USE EXCLUSIVELY";
static const char lbl_802E8F80[0xA] = "IN JAPAN.";
static const char lbl_802E8F8C[0x22] = " THE SALE,EXPORT,USE OR OPERATION";
static const char lbl_802E8FB0[0x22] = "OF THIS GAME OUTSIDE OF JAPAN MAY";
static const char lbl_802E8FD4[0x21] = "BE  A VIOLATION OF INTERNATIONAL";
static const char lbl_802E8FF8[0x22] = "COPYRIGHT, TRADEMARK AND/OR OTHER";
static const char lbl_802E901C[0x22] = "RELATED LAWS SUBJECTING THE VIOL-";
static const char lbl_802E9040[0x19] = "ATOR TO LEGAL PENALTIES.";
static const float lbl_802E905C[4][3] = {{0.0f,0.0f,-300.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{1.0f,0.7f,0.9f}};
static const float lbl_802E908C[18][7][2] = {
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,66.66667f},{1000.0f,66.66667f},{2000.0f,66.66667f},{3000.0f,66.66667f},{4000.0f,66.66667f},{5000.0f,66.66667f}},
    {{0.0f,0.0f},{500.0f,83.333336f},{1000.0f,83.333336f},{2000.0f,83.333336f},{3000.0f,83.333336f},{4000.0f,83.333336f},{5000.0f,83.333336f}},
    {{0.0f,0.0f},{500.0f,83.333336f},{1000.0f,83.333336f},{2000.0f,83.333336f},{3000.0f,83.333336f},{4000.0f,83.333336f},{5000.0f,83.333336f}},
    {{0.0f,0.0f},{500.0f,83.333336f},{1000.0f,83.333336f},{2000.0f,83.333336f},{3000.0f,83.333336f},{4000.0f,83.333336f},{5000.0f,83.333336f}},
    {{0.0f,0.0f},{500.0f,83.333336f},{1000.0f,83.333336f},{2000.0f,83.333336f},{3000.0f,83.333336f},{4000.0f,83.333336f},{5000.0f,83.333336f}},
    {{0.0f,0.0f},{500.0f,83.333336f},{1000.0f,83.333336f},{2000.0f,83.333336f},{3000.0f,83.333336f},{4000.0f,83.333336f},{5000.0f,83.333336f}},
    {{0.0f,0.0f},{500.0f,83.333336f},{1000.0f,83.333336f},{2000.0f,83.333336f},{3000.0f,83.333336f},{4000.0f,83.333336f},{5000.0f,83.333336f}}
};
static const char lbl_802E947C[0x9] = "50cc URA";
static const char lbl_802E9488[0xA] = "100cc URA";
static const char lbl_802E9494[0xA] = "150cc URA";
static const char lbl_802E94A0[0xC] = "take RANDOM";
static const char lbl_802E94AC[0xA] = "take GOLD";
static const char lbl_802E94B8[0xE] = "LOCATION TEST";
static const char lbl_802E94C8[0xC] = "DONKEY KONG";
static const char lbl_802E94D4[0xB] = "Ms.PAC-MAN";
static const char lbl_802E94E0[0xE] = "Take Standard";
static const char lbl_802E94F0[0x9] = "Take All";
static const unsigned char lbl_802E94FC[0x10] = {1,42,0,10,1,1,1,1,2,1,1,1,1,1,1,1};
SHARED_STATIC const char lbl_802E950C[0x2C] = "clLibrary::backupBuffer error align no 32b\n";
SHARED_STATIC const char lbl_802E9538[0x30] = "clLibrary::backupBuffer error buffer size over\n";
SHARED_STATIC const char lbl_802E9568[0xF] = "MAIN  BD ID %s";
SHARED_STATIC const char lbl_802E9578[0xF] = "MEDIA BD ID %s";
static const char lbl_802E9588[0x10] = "wake test mode\n";
static const char lbl_802E9598[0x11] = "enter test mode\n";
static const char lbl_802E95AC[0x11] = "no device check\n";
static const char lbl_802E95C0[0x1C] = "wakeup:: jump to test mode\n";
static const char lbl_802E95DC[0x18] = "dvd location adrs %08x\n";
static const char lbl_802E95F4[0x26] = "------------------------------------\n";
static const char lbl_802E961C[0x18] = "all   %d[kb] %f[Mb] %s\n";
static const char lbl_802E9634[0xE] = "max   %d[kb]\n";
static const char lbl_802E9644[0xA] = "block %d\n";
#pragma force_active reset

static const char *BootDispatcher_data_803F5670[10] = {
    lbl_802E8F48, lbl_806D2290, lbl_802E8F5C, lbl_802E8F80,
    lbl_802E8F8C, lbl_802E8FB0, lbl_802E8FD4, lbl_802E8FF8,
    lbl_802E901C, lbl_802E9040
};

inline void *operator new(size_t n) { return Alloc(n); }
inline void operator delete(void *p) { MemoryManager_TimedFree(p); }

class ScopedTimer {
    unsigned int start;
    int slot;
public:
    ScopedTimer(int id) { slot=id; start=OSGetTick(); }
    ~ScopedTimer() {
        Profiler_RecordFrame(slot, (float)(((OSGetTick()-start)*8)/
            ((*(unsigned int *)0x800000F8/4)/125000))/lbl_806D2294);
    }
};
class BootWait {
    unsigned int start;
public:
    BootWait() { start=OSGetTick(); }
    ~BootWait() {}
    unsigned char Done() {
        return (float)(((OSGetTick()-start)*8)/
            ((*(unsigned int *)0x800000F8/4)/125000))/lbl_806D2294 >= SAFE;
    }
};
class BootCardManager {
    unsigned char data[0x14];
public:
    BootCardManager(unsigned char, int, int);
};
class BootDisplay {
    unsigned char data[0xD8];
public:
    BootDisplay();
};
class BootNotice {
public:
    int remaining;
    void *display;
    BootNotice() {
        remaining=599;
        if (!lbl_806D1880) lbl_806D1880=new BootDisplay;
        display=lbl_806D1880;
    }
    ~BootNotice() {
        if (!lbl_806D1880) {
            fn_801DB68C(lbl_806D1880,1);
            lbl_806D1880=0;
        }
    }
    unsigned char Done() {
        if (remaining<=0) return 1;
        --remaining;
        return 0;
    }
    void Draw() {
        if (display) {
            for (unsigned int i=0, y=32;i<10;++i,y+=36)
                DrawText(display,78,y,7,lbl_806D22A8,BootDispatcher_data_803F5670[i]);
            DrawText(display,588,24,7,lbl_806D22A8,lbl_806D22AC,remaining/60);
            DisplayContext_Flush(display);
        }
    }
};
struct BootTextBuffer {
    unsigned int field0, field4, field8, fieldC, width, height;
    BootTextBuffer() { field4=0; field8=0; width=11; height=14; field0=0; }
};
extern "C" BootTextBuffer *lbl_806D0FD8;
struct BootShutdownObject { virtual void Destroy(int); };

static inline void RefreshBootState() {
    fn_802554DC();
    BootState *src=fn_80293BBC();
    BootTimer *timer=g_bootTimer;
    g_bootState=*src;
    timer->lastTick=OSGetTick();
}
static inline void CopyFrame() {
    if (lbl_806CED30==1) {
        ScopedTimer timer(21);
        if ((unsigned int)g_backupBufferTexture & 31) {
            DebugPrintf(lbl_802E950C);
            return;
        }
        if (GXGetTexBufferSize(640,480,4,0,0)>0x96000) {
            DebugPrintf(lbl_802E9538);
            return;
        }
        GXSetTexCopySrc(0,0,640,480);
        GXSetTexCopyDst(640,480,4,0);
        GXCopyTex(g_backupBufferTexture,0);
    }
}
static inline void SetBootColor(BootColor color) {
    HSD_VIData.color=color;
}
static inline void FinishFrame() {
    if (lbl_806D0F8E==1) {
        OverlayText(1,12,28,lbl_802E9568,&g_bootState.f18);
        OverlayText(1,12,29,lbl_802E9578,&g_bootState.f2C);
    }
    GXDrawDone();
    fn_8018F14C();
    SetBootColor(lbl_806CED34);
    HSD_VICopyXFBAsync(0);
    HSD_VIDrawDoneXFBAll();
    VIWaitForRetrace();
    GXInvalidateTexAll();
    void *card=Sci2Card_Singleton_Get();
    if (card) {
        unsigned char active;
        if (!g_serviceEnable) active=0;
        else if (g_serviceValue==1) active=0;
        else active=1;
        if (active==1) Sci2Card_Tick(card);
    }
    RefreshBootState();
    void *input=GetInputManager();
    if (input) InputObj_TickAndDispatch(input);
    void *pcb=StrPcb_GetInstance();
    if (pcb) StrPcb_OutputTick(pcb);
    fn_80193624();
    FrameUpdate();
    CreditMgr_PollInsertAndPlay(0);
}
static inline void Shutdown() {
    GXDrawDone();
    PcbComm_Shutdown();
    FreeMediaBuffers();
    CardTaskManager_Dtor(g_cardTaskManager,1);
    g_cardTaskManager=0;
    Sci2Card_Shutdown();
    fn_80193838();
    InputMgr_Shutdown();
    StrPcb_Shutdown();
    if (lbl_806D0FD8) MemoryManager_TimedFree(lbl_806D0FD8);
    lbl_806D0FD8=0;
    MemoryManager_Free(lbl_806D0FC8);
    lbl_806D0FC8=0;
    PlayStats_ShutdownStub();
    Backup_Shutdown();
    if (lbl_806D12DC) ((BootShutdownObject *)lbl_806D12DC)->Destroy(1);
    lbl_806D12DC=0;
    fn_80255620();
    char *tail=(char *)OSGetArenaHi()-256;
    memset(tail,0,256);
    *(int *)tail=1;
    fn_80287EE4(0,tail);
}

#pragma cplusplus off
#include "game/types/c_region.h"
C_REGION_BEGIN
static inline int BootOptionDisabled(unsigned char option) {
    return option == 0;
}
C_REGION_END
#pragma cplusplus reset

static inline int IsServiceBoot(unsigned int mode) {
    return (unsigned char)(mode == 1);
}

extern "C" void BootDispatcher(unsigned char *serviceMode)
{
    g_dvdLoadCallback=BootStateStruct_RefreshIfDue;
    PPCMthid0(PPCMfhid0()|0x200);
    *serviceMode=0;
    unsigned char service=0;
    void *component=0;
    unsigned int bootInfo[64];
    fn_80287FDC(bootInfo);
    int isService=IsServiceBoot(bootInfo[0]);
    if (isService==1) { DebugPrintf(lbl_802E9588); service=1; }
    BootError error;
    memset(&error,0,24);
    error.code[0]=99;
    error.code[1]=99;
    error.code[2]=1;
    error.enabled=1;
    int mode=1;
    if (isService) mode=2;
    if (fn_80255640(isService,mode,&error)==0) {
        component=fn_80287EC4((~fn_8028B090()>>5)&1);
        BootState *state=fn_80293BBC();
        fn_80289D4C(255);
        g_bootState=*state;
    }
    SceneFlow_InitCleanupList();
    SceneFlow_SetCleanupTag(0);
    lbl_806CED28.begin=0;
    lbl_806CED28.end=0;
    void *hi=OSGetArenaHi();
    OSSetArenaLo(OSInitAlloc(OSGetArenaLo(),hi,2));
    lbl_806D0FA1=1;
    HSD_SetInitParameter(0,0x40000);
    HSD_SetInitParameter(1,2);
    g_serviceEnable=0;
    vblank_flag=0;
    g_vblankValue=1;
    g_serviceValue=1;
    lbl_806D0F96=0;
    lbl_806D0F97=0;
    HSD_InitComponent(component);
    VIWaitForRetrace(); VIWaitForRetrace();
    g_bootTimer=(BootTimer *)Alloc(4);
    while (!fn_80293BCC()) {
        BootWait wait;
        while (wait.Done()==0) {}
        RefreshBootState();
    }
    GameBoot_Init();
    PlayStats_LoadOrInitForBoot();
    RaceContext_EnsureSingleton();
    if (lbl_80598A60.receiptTest==1) Sci2Card_FlagReceiptTestEnable();
    BootConfig *config=&lbl_80598A60;
    BootConfig *calibration=&lbl_80598A60;
    unsigned char enabled=config->card;
    g_serviceEnable=enabled;
    if (!enabled) g_serviceValue=1;
    vblank_flag=1;
    int disabled=BootOptionDisabled(config->cardDisabled);
    g_serviceValue=enabled ? disabled : 1;
    g_vblankValue=BootOptionDisabled(config->otherDisabled);
    InputMgr_Init();
    StrPcb_EnsureInstance();
    JvsInput_SetSteeringCalibration(calibration->steering);
    JvsInput_SetAccelCalibration(calibration->accel);
    JvsInput_SetBrakeCalibration(calibration->brake);
    StrPcb_SetPositionTarget(StrPcb_GetInstance(),(short)calibration->position);
    StrPcb_SetIntensityMode(StrPcb_GetInstance(),config->intensity);
    ClSound_InitSoundSystem();
    fn_801934A0((unsigned char)((lbl_80598A60.volume<<7)/15));
    fn_8019345C((unsigned char)((lbl_80598A60.volume<<7)/15));
    fn_80193404((unsigned char)((lbl_80598A60.effectsVolume<<7)/15));
    fn_801951E4(lbl_80598A60.soundMode);
    fn_801951CC(lbl_80598A60.soundOption);
    Sci2Card_Singleton_GetOrCreate(0);
    HSD_VISetBlack(0);
    if (!lbl_806D0FD8) {
        lbl_806D0FD8=new BootTextBuffer;
        BootDispatcher_bss_806D0FCC=640/lbl_806D0FD8->width+1;
        BootDispatcher_bss_806D0FD0=480/lbl_806D0FD8->height;
        BootDispatcher_bss_806D0FD4=BootDispatcher_bss_806D0FCC*BootDispatcher_bss_806D0FD0;
        lbl_806D0FC8=(char *)FUN_8003b120(BootDispatcher_bss_806D0FD4);
        memset(lbl_806D0FC8,0,BootDispatcher_bss_806D0FD4);
    }
    fn_801F8E58();
    int effect=lbl_80598A60.effect-1;
    StrPcb_BeginEffect(StrPcb_GetInstance(),effect);
    StrPcb_DrainInputBuffer(StrPcb_GetInstance());
    if (service==1) {
        *serviceMode=1;
        DebugPrintf(lbl_802E9598);
        fn_801213EC();
        return;
    }
    if ((~fn_8028B090())&1) {
        g_serviceEnable=0;
        g_serviceValue=1;
        vblank_flag=0;
        g_vblankValue=1;
        Boot_bss_806D0FA0=0;
        DebugPrintf(lbl_802E95AC);
    } else Boot_bss_806D0FA0=1;
    fn_801213EC();
    if (Boot_bss_806D0FA0==1) {
        int card=1, other=1;
        if (!g_serviceEnable || g_serviceValue==1) card=0;
        if (!vblank_flag || g_vblankValue==1) other=0;
        g_cardTaskManager=new BootCardManager(lbl_80598A60.intensity!=0,card,other);
        int state=CardTaskManager_Tick(g_cardTaskManager);
        while (state==2) {
            if (lbl_806CED28.begin) lbl_806CED28.begin->Tick();
            HSD_StartRender(0);
            CardTaskManager_RenderOverlay(g_cardTaskManager);
            fn_802D47E8(); SpriteHandlePool_GC();
            if (lbl_806CED28.end) lbl_806CED28.end->Tick();
            CopyFrame();
            FinishFrame();
            state=CardTaskManager_Tick(g_cardTaskManager);
            if (ServiceButton_Handler()==1) {
                DebugPrintf(lbl_802E95C0);
                state=3;
            }
        }
        if (state==3) Shutdown();
    }
    CardTaskManager_Dtor(g_cardTaskManager,1);
    g_cardTaskManager=0;
    fn_80121210();
    DebugPrintf(lbl_802E95DC,DVDGetFSTLocation());
    for (;;) {
        BootState state=*fn_80293BBC();
        if (((unsigned char *)&state)[0x14] && ((unsigned char *)&state)[0x15]) break;
        BootWait wait;
        while (wait.Done()!=1) {}
        RefreshBootState();
    }
    fn_802928DC(); fn_80290ED8(); InitGlobalTimer(); PCBComm_Init();
    SetBootColor(lbl_806CED34);
    BootPCBCheck_Init();
    while (BootPCBCheck_Poll()) {
        if (lbl_806CED28.begin) lbl_806CED28.begin->Tick();
        HSD_StartRender(0);
        BootPCBCheck_Display();
        fn_802D47E8(); SpriteHandlePool_GC();
        if (lbl_806CED28.end) lbl_806CED28.end->Tick();
        CopyFrame();
        Timer_Decrement(); PCBComm_Process(1,1);
        FinishFrame();
        if (ServiceButton_Handler()==1) Shutdown();
    }
    BootNotice_CheckEnterCondition();
    if (!lbl_80598A60.skipNotice) {
        SetSyncTarget(55);
        BootNotice notice;
        while (!notice.Done()) {
            if (lbl_806CED28.begin) lbl_806CED28.begin->Tick();
            HSD_StartRender(0);
            notice.Draw();
            for (int i=0;i<8;++i) fn_8011F994(i);
            fn_802D47E8(); SpriteHandlePool_GC();
            if (lbl_806CED28.end) lbl_806CED28.end->Tick();
            CopyFrame();
            Timer_Decrement(); PCBComm_Process(1,1);
            FinishFrame();
        }
    }
}

