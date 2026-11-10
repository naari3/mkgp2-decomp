#ifndef SERVICE_BUTTON_PRIVATE_H
#define SERVICE_BUTTON_PRIVATE_H
struct ServiceInput {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual unsigned char Held(unsigned int);
    virtual unsigned char Pressed(unsigned int);
};
class ServiceMenu {
public:
    ServiceMenu(int);
    virtual void Tick(); virtual void Draw(); virtual ~ServiceMenu();
    unsigned char pad04[12];
    int pageId;
    unsigned char pad14[0x278];
};
class ServiceOwned { public: virtual ~ServiceOwned(); };
struct ServiceMode {
    unsigned short v0,v2,v4,v6;
    struct Pair { unsigned int a,b; } v8;
    unsigned char v10,v11;
    unsigned short v12,v14,v16;
    unsigned int v18[5],v2C[5],v40[7],v5C;
};
struct ServiceVI { unsigned char pad[0x48]; unsigned char r,g,b,a; };
struct ServiceColor { unsigned char r,g,b,a; };
extern "C" {
extern int g_currentSceneState;
extern unsigned char ServiceButton_bss_806D0F8D,lbl_806D0F8E,g_serviceEnable,g_serviceValue;
extern void *g_cardTaskManager,*lbl_806D0FD8,*lbl_806D0FC8;
extern ServiceOwned *lbl_806D12DC;
extern unsigned int *g_bootTimer;
extern ServiceMode g_bootState;
extern ServiceVI HSD_VIData;
extern ServiceColor lbl_806CED34;
extern char lbl_802E9568[],lbl_802E9578[];
void *Sci2Card_Singleton_Get();
unsigned char Sci2Card_IsIdleOrExhausted(void *);
void *GetInputManager();
ServiceInput *InputMgr_GetPlayer(void *,int);
void fn_802557B4();
void SetSyncTarget(int);
void Timer_Decrement();
void PCBComm_Process(int,int);
void OverlayText(int,int,int,char *,...);
void GXDrawDone(); void fn_8018F14C();
void HSD_VICopyXFBAsync(int); void HSD_VIDrawDoneXFBAll();
void VIWaitForRetrace(); void GXInvalidateTexAll();
void Sci2Card_Tick(void *); void fn_802554DC();
ServiceMode *fn_80293BBC(); unsigned int OSGetTick();
void InputObj_TickAndDispatch(void *); void *StrPcb_GetInstance();
void StrPcb_OutputTick(void *); void fn_80193624(); void FrameUpdate();
void CreditMgr_PollInsertAndPlay(int);
void PcbComm_Shutdown(); void FreeMediaBuffers();
void CardTaskManager_Dtor(void *,int); void Sci2Card_Shutdown();
void fn_80193838(); void InputMgr_Shutdown(); void StrPcb_Shutdown();
void MemoryManager_TimedFree(void *); void MemoryManager_Free(void *);
void PlayStats_ShutdownStub(); void Backup_Shutdown(); void fn_80255620();
void *OSGetArenaHi(); void *memset(void *,int,unsigned long);
void fn_80287EE4(int,void *);
}
void *operator new(unsigned long);
void operator delete(void *);
#endif
