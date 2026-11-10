#include "game/CardTaskChecks_private.h"

extern "C" int CardTaskWelcome_StepStatus(WelcomeObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    switch (int status = StrPcb_TimerTick(StrPcb_GetInstance())) {
    case 0: return 1;
    case 1: self->step = CardCallback(table,0x14C); self->result = 0; return 2;
    case 2: self->step = CardCallback(table,0x158); self->result = 2; return 3;
    default:
        DebugPrintf(lbl_80312F14, status);
        self->step = CardCallback(table,0x164); self->result = 3; return 3;
    }
}
extern "C" int CardTaskWelcome_StepCommCheck(WelcomeObject *self) {
    void *pcb = StrPcb_GetInstance();
    StrPcb_GetErrorCodeString(pcb);
    if (StrPcb_HasError(pcb) == 1 || StrPcb_GetCommErrorFlag(pcb) == 1) {
        self->step = CardTaskWelcome_StepCommCheck_data_803FE5C0; self->result = 2; return 3;
    }
    return 2;
}
extern "C" int CardTaskWelcome_StepInputCheck(WelcomeObject *) {
    InputMgr_GetPlayer(GetInputManager(), 0);
    return 3;
}
extern "C" void CardTaskWelcome_DrawStatus(WelcomeObject *) {
    CardDrawWelcome(0x80);
    void *pcb = StrPcb_GetInstance();
    if (!StrPcb_GetCommErrorFlag(pcb)) {
        CardDrawWelcome(0xC0);
        const char *error = StrPcb_GetErrorCodeString(pcb);
        TexMgr_DrawText_Format_Variant2(0, 308.0f, 296.0f, lbl_806D3338,
            error[0], error[1], error[2]);
    } else CardDrawWelcome(0x100);
    CardDrawFrame();
}
WelcomeObject::~WelcomeObject() {}
extern "C" int fn_8008A6B0(WelcomeObject *self) {
    if (self->result == 2 || self->result == 3) return 1;
    return 0;
}
extern "C" void CardTaskWelcome_StateInit(WelcomeObject *self) {
    self->state = 1; self->step = CardTaskWelcome_StateInit_data_803FE5F0;
    self->result = 1; self->counter = 0;
    StrPcb_BeginTimedNeutral(StrPcb_GetInstance());
}
extern "C" int CardTaskWelcome_TickCounter(WelcomeObject *self) {
    ++self->counter;
    return (self->*self->step)();
}
extern "C" void fn_8008A760() {}
extern "C" void CardTaskWelcome_DrawByPhase(WelcomeObject *self) {
    switch (self->result) {
    case 1:
        if ((self->counter & 31) < 24) CardDrawWelcome(0x40);
        break;
    case 2:
        CardDrawWelcome(0x80);
        {
            void *pcb = StrPcb_GetInstance();
            if (!StrPcb_GetCommErrorFlag(pcb)) {
                CardDrawWelcome(0xC0);
                const char *error = StrPcb_GetErrorCodeString(pcb);
                TexMgr_DrawText_Format_Variant2(0,308.0f,296.0f,lbl_806D3338,
                    error[0],error[1],error[2]);
            } else CardDrawWelcome(0x100);
            CardDrawFrame();
        }
        break;
    case 3: CardDrawWelcome(0); break;
    }
    if (self->result != 1) {
        ResCtrl rc;
        rc.mode=2;
        rc.width=540.0f; rc.height=380.0f;
        rc.Show(320.0f,240.0f,1.0f);
        rc.SetColor(0xFFFFFF7F);
        fn_8011FAFC(&rc,7);
    }
}
extern "C" WaitInputObject *CardTaskWaitInput_New() {
    struct Storage {
        void **vtable;
        int state;
        unsigned char polling, button2000, button400, pad0B;
        int delay;
    };
    Storage *self=(Storage *)Alloc(sizeof(Storage));
    if (self) {
        self->vtable=CardTaskObject_vtable_803FE8B8;
        self->state=0;
        self->vtable=WaitInputObject_vtable_803FE86C;
    }
    return (WaitInputObject *)self;
}
WaitInputObject::~WaitInputObject() {}
extern "C" void CardTaskWaitInput_StateInit(WaitInputObject *self) {
    self->polling=1; self->button2000=0; self->button400=0; self->delay=60;
}
extern "C" int CardTaskWaitInput_StepPoll(WaitInputObject *self) {
    if (self->delay != 0) { --self->delay; return 1; }
    if (self->polling) {
        ServiceInput *input = InputMgr_GetPlayer(GetInputManager(),0);
        if (lbl_80598A60.button2000 && input->Pressed(0x2000)==1) self->button2000=1;
        if (lbl_80598A60.button400 && input->Pressed(0x400)==1) self->button400=1;
        self->polling=0;
    }
    if (self->button2000) return 3;
    return (self->button400 != 0) + 2;
}
extern "C" void fn_8008ABFC() {}
extern "C" void CardTaskWaitInput_DrawByButtons(WaitInputObject *self) {
    if (self->button2000) {
        CardDrawWait(0x0);
        CardDrawWait(0x40);
    } else if (self->button400) {
        CardDrawWait(0x0);
        CardDrawWait(0x80);
    }
}
extern "C" PrintObject *CardTaskPrintJob_New() { return new PrintObject; }
extern "C" int CardTaskPrintJob_StepStart(PrintObject *self) {
    void *card = Sci2Card_Singleton_Get();
    if (!Sci2Card_IsIdleOrExhausted(card)) return 1;
    if (Sci2Card_IsStatusOkNonTerm(card)==1) {
        DebugPrintf(lbl_80312E1C);
        self->step=CardTaskPrintJob_StepStart_data_803FE758;
        self->started=OSGetTick();
        CardPrintJob_KickFontTransfer();
        return 1;
    }
    self->error=Sci2Card_ClassifyStatusToCode();
    self->step=CardTaskChecks_data_803FE6BC; self->result=1;
    ServiceLatchAux96_Set(1); ServiceValue_Set(1); ServiceButtonExtra_Set(1);
    return 3;
}
extern "C" int CardTaskPrintJob_StepNoCardPrinter(PrintObject *) {
    DebugPrintf(CardTaskPrintJob_StepNoCardPrinter_rodata_80312E40); return 4;
}
extern "C" int CardTaskPrintJob_StepWaitFontTransfer(PrintObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    const char *messages=Card_rodata_80312850;
    if (!CardPrintJob_TickFontTransfer(Sci2Card_Singleton_Get())) return 1;
    if (Sci2Card_GetPrintErrorCode()!=1) {
        DebugPrintf(messages+0x608);
        self->error=Sci2Card_ClassifyStatusToCode();
        self->step=CardCallback(table,0x23C); self->result=1;
        ServiceLatchAux96_Set(1); ServiceValue_Set(1); ServiceButtonExtra_Set(1);
        return 3;
    }
    DebugPrintf(messages+0x620, (float)CardMicroseconds(OSGetTick()-self->started)/1000000.0f);
    self->step=CardCallback(table,0x2B4);
    DebugPrintf(messages+0x638);
    if (!Sci2Card_BeginSpace()) self->step=CardCallback(table,0x2C0);
    else self->step=CardCallback(table,0x2CC);
    return 1;
}
extern "C" int CardPrinterChecker_State_WaitStatus(PrintObject *self) {
    DebugPrintf(CardPrinterChecker_State_WaitStatus_rodata_80312E9C);
    if (!Sci2Card_BeginSpace()) self->step=CardPrinterChecker_State_WaitStatus_data_803FE71C;
    else self->step=CardPrinterChecker_State_WaitStatus_data_803FE728;
    return 1;
}
static inline int CardCleaningError(PrintObject *self,unsigned char *table) {
    self->error=Sci2Card_ClassifyStatusToCode();
    self->step=CardCallback(table,0x23C); self->result=1;
    ServiceLatchAux96_Set(1); ServiceValue_Set(1); ServiceButtonExtra_Set(1);
    return 3;
}
static inline int CardSelectCleaning(PrintObject *self,unsigned char *table,const char *messages) {
    DebugPrintf(messages+0x65C);
    unsigned char needsCleaning=0;
    if (isJapanese()==0) {
        if (lbl_80598A60.cleaningCount>=100) needsCleaning=1;
    } else if (Backup_GetMinutesSinceBoot(0xA8)==1) needsCleaning=1;
    if (!needsCleaning) { self->step=CardCallback(table,0x26C); return 2; }
    DebugPrintf(messages+0x66C);
    self->step=CardCallback(table,0x278); self->result=5;
    return 1;
}
extern "C" int CardPrinterChecker_State_SetupCleaning(PrintObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    const char *messages=Card_rodata_80312850;
    if (!Sci2Card_WaitPingStatus()) return 1;
    if (Sci2Card_GetPrintErrorCode()!=1) return CardCleaningError(self,table);
    if (!Sci2Card_GetByteFlag1224()) return CardSelectCleaning(self,table,messages);
    DebugPrintf(messages+0x680);
    self->step=CardCallback(table,0x290); self->result=4;
    card_eject_init(); return 1;
}
extern "C" int CardPrinterChecker_State_RemainCardJobEnd(PrintObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    const char *messages=Card_rodata_80312850;
    if (!card_eject_state_machine()) return 1;
    if (Sci2Card_GetPrintErrorCode()!=1) {
        if (Sci2Card_GetByteFlag1224()==1) { card_eject_init(); return 1; }
        return CardCleaningError(self,table);
    }
    DebugPrintf(messages+0x68C);
    return CardSelectCleaning(self,table,messages);
}
extern "C" int CardPrinterChecker_State_CleaningSelectInput(PrintObject *self) {
    ++self->frames;
    if (!self->selected) {
        ServiceInput *input=InputMgr_GetPlayer(GetInputManager(),0);
        if (input->Held(0x2000)==1) self->choice=0;
        else if (input->Held(0x400)==1) self->choice=1;
        if (self->choice!=-1) self->selected=1;
    }
    if (self->choice==0) {
        DebugPrintf(lbl_806D3328); self->step=CardPrinterChecker_State_CleaningSelectInput_data_803FE6D4; return 2;
    }
    if (self->choice==1) {
        DebugPrintf(lbl_80312EF4);
        self->step=CardPrinterChecker_State_CleaningSelectInput_data_803FE6E0; self->result=6;
        card_send_cleaning_cmd_init();
        CardPrinterChecker_StartCleaningJob(self->job.p);
    }
    return 1;
}
extern "C" int CardPrinterChecker_State_ExecCleaning(PrintObject *self) {
    if (!CardTaskPrintJob_IsRunning_Thunk(self->job.p)) return 1;
    if (CardTaskPrintJob_IsSuccess(self->job.p)==1) return 2;
    DebugPrintf(lbl_80312F04);
    self->error=Sci2Card_ClassifyStatusToCode();
    self->step=CardTaskChecks_data_803FE6BC; self->result=1;
    ServiceLatchAux96_Set(1); ServiceValue_Set(1); ServiceButtonExtra_Set(1);
    return 3;
}
extern "C" int fn_8008B668(CardTaskObject *self) { return self->state; }
extern "C" int CardPrinterChecker_State_WaitHandle(PrintObject *self) {
    if (!InputMgr_GetPlayer(GetInputManager(),0)->Held(0x1000)) return 3;
    self->step=CardPrinterChecker_State_WaitHandle_data_803FE6C8; self->result=2;
    return 3;
}
extern "C" int CardPrinterChecker_ReadCleaningChoice(PrintObject *) {
    return InputMgr_GetPlayer(GetInputManager(),0)->Held(0x2400) == 0 ? 3 : 4;
}
PrintObject::~PrintObject() {}
extern "C" void CardPrinterChecker_State_InitPrinter(PrintObject *self) {
    if (!ServiceEnable_Get()) { self->step=CardPrinterChecker_State_InitPrinter_data_803FE764; }
    else {
        void *card=Sci2Card_Singleton_Get();
        DebugPrintf(lbl_80312F8C); DebugPrintf(lbl_80312FA0);
        self->step=CardPrinterChecker_State_InitPrinter_data_803FE770;
        Sci2Card_SendCmdRetry(card,0);
    }
}
extern "C" int CardPrinterChecker_PostFrame(PrintObject *self) { return (self->*self->step)(); }
extern "C" void CardPrinterChecker_Draw(PrintObject *self) {
    switch (self->result) {
    case 1:
        if (isJapanese()==0) {
            const char *text=CardPrinterChecker_Draw_rodata_80312BA8[isJapanese()];
            TexMgr_DrawText_Format_Variant2(1,212.0f,256.0f,lbl_806D32EC,text);
        } else {
            const char *text=CardPrinterChecker_Draw_rodata_80312BA8[isJapanese()];
            TexMgr_DrawText_Format_Variant2(1,119.0f,240.0f,lbl_806D32EC,text);
        }
        CardPrinterChecker_DrawStatusErrorLabel(self->error);
        break;
    case 2: {
        const char *text=CardPrinterChecker_Draw_rodata_80312BA8[2+isJapanese()];
        TexMgr_DrawText_Format_Variant2(1,float(164-(isJapanese()==1 ? 40:0)),256.0f,lbl_806D32EC,text);
        TexMgr_DrawText_Format_Variant2(0,136.0f,296.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[4+isJapanese()]);
        break;
    }
    case 3: {
        const char *text=CardPrinterChecker_Draw_rodata_80312BA8[6+isJapanese()];
        TexMgr_DrawText_Format_Variant2(1,float(200-(isJapanese()==1 ? 50:0)),256.0f,lbl_806D32EC,text);
        break;
    }
    case 4: {
        TexMgr_DrawText_Format_Variant2(1,212.0f,256.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[8+isJapanese()]);
        ResCtrl rc;
        rc.resId=0x735; rc.Show(320.0f,348.0f,1.0f);
        fn_8011FAFC(&rc,0);
        break;
    }
    case 5: {
        TexMgr_DrawText_Format_Variant2(0,152.0f,184.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[12+isJapanese()]);
        if (isJapanese()==0) {
            TexMgr_DrawText_Format_Variant2(1,128.0f,142.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[10+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,104.0f,288.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[14+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,104.0f,304.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[16+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,104.0f,320.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[18+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,392.0f,288.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[20+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,392.0f,304.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[22+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,152.0f,256.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[24+isJapanese()]);
        } else {
            TexMgr_DrawText_Format_Variant2(1,110.0f,158.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[10+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,57.0f,256.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[14+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,72.0f,288.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[16+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,72.0f,304.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[18+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,350.0f,288.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[20+isJapanese()]);
            TexMgr_DrawText_Format_Variant2(0,360.0f,304.0f,lbl_806D32EC,CardPrinterChecker_Draw_rodata_80312BA8[22+isJapanese()]);
        }
        CardDrawLeftChoice(self);
        { ResCtrl right;
        right.resId=0x896+(self->frames>>4)%4;
        right.Show(self->rightX,self->y,1.0f);
        fn_8011FAFC(&right,0); }
        break;
    }
    case 6: CardPrinterChecker_DrawErrorOverlay(self->job.p); break;
    }
    if (self->Ready()==1) CardDrawFrame();
}
extern "C" int fn_8008BF1C(PrintObject *self) { return self->result!=0; }
extern "C" CameraObject *CameraChecker_Alloc() {
    return new CameraObject;
}
extern "C" int CameraChecker_State_Entry(CameraObject *self) {
    --self->countdown;
    if (StrPcb_IsInErrorState(StrPcb_GetInstance())==1 || self->countdown<0) {
        self->step=CameraChecker_State_Entry_data_803FE7C4;
        self->retries=3; self->timeout=300;
        NamCam_Init();
    }
    return 1;
}
extern "C" int fn_8008C034() { return 4; }
extern "C" int CameraChecker_State_DownloadWait(CameraObject *self) {
    unsigned char *table=CardTaskChecks_data_803FE480;
    if (self->timeout-- < 0) {
        self->step=CardCallback(table,0x320); self->result=1;
        ServiceLatchAux97_Set(1); VBlankValue_Set(1);
        DebugPrintf(lbl_80312DEC); ServiceButtonExtra_Set(1);
        return 3;
    }
    char imageInfo[0x10];
    void *handle;
    if (NamCam_GetImageHandle(&handle,0)==0) return 1;
    self->timeout=300;
    void *buffer=FUN_8003b120(0x4B000);
    unsigned int loaded=NamCam_LoadImage(handle,buffer,imageInfo)!=0;
    MemoryManager_Free(buffer);
    if (!loaded) {
        DebugPrintf(lbl_80312DFC,--self->retries);
        if (self->retries<=0) { self->step=CardCallback(table,0x32C); return 1; }
    }
    self->step=CardCallback(table,0x338); return 2;
}
extern "C" int CameraChecker_State_WaitButton1000(CameraObject *self) {
    if (InputMgr_GetPlayer(GetInputManager(),0)->Held(0x1000)==1) {
        self->result=2; self->step=CameraChecker_State_WaitButton1000_data_803FE794; VBlankEnable_Set(0);
    }
    return 3;
}
extern "C" int CameraChecker_State_WaitButton2400(CameraObject *self) {
    if (!InputMgr_GetPlayer(GetInputManager(),0)->Held(0x2400)) return 3;
    DebugPrintf(lbl_806D3310);
    self->result=0; self->step=CameraChecker_State_WaitButton2400_data_803FE788; return 3;
}
extern "C" int CameraChecker_State_ShutdownTick(CameraObject *self) {
    if (NamCam_TickShutdownCountdown()==0) return self->state;
    self->step=CameraChecker_State_ShutdownTick_data_803FE77C; return 4;
}
extern "C" int fn_8008C320(CameraObject *self) { return self->state; }
CameraObject::~CameraObject() {}
extern "C" int fn_8008C384(CameraObject *self) { return self->result!=0; }
extern "C" void CameraChecker_State_WaitVBlank(CameraObject *self) {
    if (!GetVBlankFlag()) self->step=CameraChecker_State_WaitVBlank_data_803FE7D0;
    else { DebugPrintf(lbl_80312F5C); self->step=CameraChecker_State_WaitVBlank_data_803FE7DC; }
}
extern "C" int CardTaskDispatch_WithFrameBudget(CameraObject *self) {
    CardFrameTimer timer;
    timer.started=OSGetTick();
    int result=(self->*self->step)();
    unsigned char slow=(float)CardMicroseconds(OSGetTick()-timer.started)/1000000.0f >= 1.0f ? 1 : 0;
    if (slow==1) StrPcb_DrainInputBuffer(StrPcb_GetInstance());
    return result;
}
extern "C" void CardTask_NamCamEndTrampoline() { NamCam_End(); }
extern "C" void CameraChecker_Draw(CameraObject *self) {
    switch (self->result) {
    case 1:
        CardDrawCamera(0x0);
        CardDrawCamera(0x40);
        break;
    case 2:
        CardDrawCamera(0x40);
        CardDrawCamera(0x80);
        CardDrawCamera(0xc0);
        break;
    }
    if (self->Ready()==1) CardDrawFrame();
}
#pragma use_lmw_stmw on
extern "C" void TexMgr_DrawText_Format(float x, float y, int font,
    int r, int g, int b, int a, const char *format, ...) {
    CardStackText text;
    char buffer[0x200];
    va_list args;
    text.font=font; text.color=(r<<24)|(g<<16)|(b<<8)|a;
    fn_801F93EC((TextManager *)&text,x,y);
    int enabled=OSDisableInterrupts();
    va_start(args,format); vsprintf(buffer,format,args); va_end(args);
    OSRestoreInterrupts(enabled);
    TexMgr_SetTexture((TextManager *)&text,buffer);
    fn_801F8A34(fn_801F8E58(),(TextManager *)&text,0);
}
#pragma use_lmw_stmw reset
extern "C" void TexMgr_DrawText_Format_Variant2(int font,float x,float y,const char *format,...) {
    CardStackText text;
    char buffer[0x200];
    va_list args;
    text.font=font; text.color=0xFFFFFFFF;
    fn_801F93EC((TextManager *)&text,x,y);
    int enabled=OSDisableInterrupts();
    va_start(args,format); vsprintf(buffer,format,args); va_end(args);
    OSRestoreInterrupts(enabled);
    TexMgr_SetTexture((TextManager *)&text,buffer);
    fn_801F8A34(fn_801F8E58(),(TextManager *)&text,0);
}
