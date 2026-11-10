#include "game/ServiceButtonPrivate.h"
static inline unsigned char CardReady() {
    if (g_serviceEnable==0) return 0;
    if (g_serviceValue==1) return 0;
    return 1;
}
static inline void ServiceFrame() {
    Timer_Decrement();
    PCBComm_Process(1,1);
    if (lbl_806D0F8E==1) {
        OverlayText(1,12,28,lbl_802E9568,g_bootState.v18);
        OverlayText(1,12,29,lbl_802E9578,g_bootState.v2C);
    }
    GXDrawDone();
    fn_8018F14C();
    ServiceColor color=lbl_806CED34;
    HSD_VIData.r=color.r; HSD_VIData.g=color.g;
    HSD_VIData.b=color.b; HSD_VIData.a=color.a;
    HSD_VICopyXFBAsync(0); HSD_VIDrawDoneXFBAll();
    VIWaitForRetrace(); GXInvalidateTexAll();
    void *card=Sci2Card_Singleton_Get();
    if (card && CardReady()==1) Sci2Card_Tick(card);
    fn_802554DC();
    ServiceMode *mode=fn_80293BBC();
    unsigned int *tick=g_bootTimer;
    g_bootState=*mode;
    *tick=OSGetTick();
    void *input=GetInputManager();
    if (input) InputObj_TickAndDispatch(input);
    void *pcb=StrPcb_GetInstance();
    if (pcb) StrPcb_OutputTick(pcb);
    fn_80193624(); FrameUpdate(); CreditMgr_PollInsertAndPlay(0);
}
extern "C" int ServiceButton_Handler() {
    if (g_currentSceneState==0x35) return 0;
    if (ServiceButton_bss_806D0F8D==1) return 0;
    void *card=Sci2Card_Singleton_Get();
    if (card && !Sci2Card_IsIdleOrExhausted(card)) return 0;
    if (InputMgr_GetPlayer(GetInputManager(),0)->Pressed(0x800)) {
        if (InputMgr_GetPlayer(GetInputManager(),0)->Held(0x1000)) {
            fn_802557B4();
            ServiceMenu *menu=new ServiceMenu(11);
            SetSyncTarget(0x35);
            while (menu->pageId!=0x20) {
                ServiceFrame(); menu->Tick(); menu->Draw();
            }
            delete menu;
            GXDrawDone(); PcbComm_Shutdown(); FreeMediaBuffers();
            CardTaskManager_Dtor(g_cardTaskManager,1); g_cardTaskManager=0;
            Sci2Card_Shutdown(); fn_80193838(); InputMgr_Shutdown(); StrPcb_Shutdown();
            if (lbl_806D0FD8) MemoryManager_TimedFree(lbl_806D0FD8);
            lbl_806D0FD8=0;
            MemoryManager_Free(lbl_806D0FC8); lbl_806D0FC8=0;
            PlayStats_ShutdownStub(); Backup_Shutdown();
            delete lbl_806D12DC; lbl_806D12DC=0;
            fn_80255620();
            unsigned int *arena=(unsigned int *)((char *)OSGetArenaHi()-0x100);
            memset(arena,0,0x100); *arena=1; fn_80287EE4(0,arena);
            return 0;
        }
    } else if (InputMgr_GetPlayer(GetInputManager(),0)->Held(0x1000)) {
        SetSyncTarget(0x35);
        for (int i=0;i<6;i++) ServiceFrame();
        return 1;
    }
    return 0;
}
