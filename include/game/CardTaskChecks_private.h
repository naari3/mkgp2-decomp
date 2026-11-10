#ifndef GAME_CARDTASKCHECKS_PRIVATE_H
#define GAME_CARDTASKCHECKS_PRIVATE_H
#include "game/types/pmf.h"
#include "game/TextDraw801F.h"
#include "game/ServiceButtonPrivate.h"
#include "libc/stdarg.h"

/* Views inferred from the task dispatch and initialization code. */
struct CardTaskObject {
    virtual unsigned char Ready();
    virtual ~CardTaskObject() {}
    virtual void Init();
    virtual int Tick();
    virtual void After();
    virtual void Draw();
    int state;
    CardTaskObject() : state(0) {}
};
PMF_TYPE(CardStep, CardTaskObject, int, ());
extern "C" CardStep lbl_803F1C68;
struct WelcomeObject : CardTaskObject {
    virtual unsigned char Ready();
    ~WelcomeObject();
    CardStep step;
    int result, counter;
};
struct WaitInputObject : CardTaskObject {
    virtual unsigned char Ready();
    ~WaitInputObject();
    unsigned char polling, button2000, button400, pad0B;
    int delay;
};
struct PrintState {
    char storage[0x14];
    PrintState();
    ~PrintState();
};
struct PrintObject : CardTaskObject {
    virtual unsigned char Ready();
    ~PrintObject();
    CardStep step;
    int result;
    unsigned char selected, pad19[3];
    int frames;
    float leftX, rightX, y;
    int choice;
    VHolder<PrintState> job;
    unsigned int started;
    int error;
    PrintObject() : step(lbl_803F1C68), result(0), selected(0), frames(0),
        leftX(0.0f), rightX(32.0f), y(32.0f), choice(-1), job(new PrintState) {
        leftX = 176.0f; rightX = 464.0f; y = 224.0f;
    }
};
struct CameraObject : CardTaskObject {
    virtual unsigned char Ready();
    ~CameraObject();
    int countdown;
    CardStep step;
    int result, retries, timeout;
    CameraObject() : countdown(3000), step(lbl_803F1C68), result(0) {}
};
struct CardStackText : TextDraw801F {
    CardStackText();
    ~CardStackText() {}
};
struct CardFrameTimer {
    unsigned int started;
    CardFrameTimer() {}
    ~CardFrameTimer() {}
};
struct CardTextLine {
    float x, y;
    const char *format;
    int font, r, g, b, a;
};
struct CardSettingsView {
    char pad00[0x44];
    unsigned char button2000, button400;
    char pad46[0x26C-0x46];
    int cleaningCount;
};
extern "C" {
void *Alloc(unsigned long);
extern void *CardTaskObject_vtable_803FE8B8[], *WaitInputObject_vtable_803FE86C[];
extern unsigned char CardTaskChecks_data_803FE480[];
extern CardTextLine CardTaskWaitInput_DrawByButtons_data_803FE5FC[][2];
extern CardTextLine CameraChecker_Draw_rodata_80312CC4[][2];
extern const char *CardPrinterChecker_Draw_rodata_80312BA8[];
extern CardSettingsView lbl_80598A60;
extern CardStep CardTaskWelcome_StepCommCheck_data_803FE5C0, CardTaskWelcome_StateInit_data_803FE5F0;
extern CardStep CardTaskChecks_data_803FE6BC, CardPrinterChecker_State_WaitHandle_data_803FE6C8, CardPrinterChecker_State_CleaningSelectInput_data_803FE6D4, CardPrinterChecker_State_CleaningSelectInput_data_803FE6E0;
extern CardStep CardPrinterChecker_State_WaitStatus_data_803FE71C, CardPrinterChecker_State_WaitStatus_data_803FE728, CardTaskPrintJob_StepStart_data_803FE758, CardPrinterChecker_State_InitPrinter_data_803FE764, CardPrinterChecker_State_InitPrinter_data_803FE770;
extern CardStep CameraChecker_State_ShutdownTick_data_803FE77C, CameraChecker_State_WaitButton2400_data_803FE788, CameraChecker_State_WaitButton1000_data_803FE794, CameraChecker_State_Entry_data_803FE7C4, CameraChecker_State_WaitVBlank_data_803FE7D0, CameraChecker_State_WaitVBlank_data_803FE7DC;
extern char Card_rodata_80312850[], lbl_80312DEC[], lbl_80312DFC[], lbl_80312E1C[], CardTaskPrintJob_StepNoCardPrinter_rodata_80312E40[];
extern char CardPrinterChecker_State_WaitStatus_rodata_80312E9C[], lbl_80312EF4[], lbl_80312F04[], lbl_80312F14[], lbl_80312F5C[];
extern char lbl_80312F8C[], lbl_80312FA0[];
extern const char lbl_806D3310[6], lbl_806D3328[8], lbl_806D3338[7], lbl_806D32EC[3];
void DebugPrintf(const char *, ...);
int StrPcb_TimerTick(void *);
const char *StrPcb_GetErrorCodeString(void *);
unsigned char StrPcb_HasError(void *);
unsigned char StrPcb_GetCommErrorFlag(void *);
unsigned char StrPcb_IsInErrorState(void *);
void StrPcb_BeginTimedNeutral(void *);
void StrPcb_DrainInputBuffer(void *);
unsigned char Sci2Card_IsStatusOkNonTerm(void *);
int Sci2Card_ClassifyStatusToCode();
int Sci2Card_GetPrintErrorCode();
unsigned char Sci2Card_GetByteFlag1224();
unsigned char Sci2Card_BeginSpace();
unsigned char Sci2Card_WaitPingStatus();
void Sci2Card_SendCmdRetry(void *, int);
void CardPrintJob_KickFontTransfer();
unsigned char CardPrintJob_TickFontTransfer(void *);
void ServiceLatchAux96_Set(int);
void ServiceLatchAux97_Set(int);
void ServiceValue_Set(int);
void VBlankValue_Set(int);
void VBlankEnable_Set(int);
void ServiceButtonExtra_Set(int);
unsigned char ServiceEnable_Get();
unsigned char GetVBlankFlag();
unsigned char Backup_GetMinutesSinceBoot(int);
void card_eject_init();
unsigned char card_eject_state_machine();
void card_send_cleaning_cmd_init();
void CardPrinterChecker_StartCleaningJob(PrintState *);
unsigned char CardTaskPrintJob_IsRunning_Thunk(PrintState *);
unsigned char CardTaskPrintJob_IsSuccess(PrintState *);
void CardPrinterChecker_DrawErrorOverlay(PrintState *);
void CardPrinterChecker_DrawStatusErrorLabel(int);
int NamCam_Init();
void NamCam_End();
int NamCam_GetImageHandle(void **, int);
int NamCam_LoadImage(void *, void *, void *);
int NamCam_TickShutdownCountdown();
void *FUN_8003b120(unsigned int);
void TexMgr_Init(void *);
void *fn_801F8E58();
void fn_801F8A34(void *, TextManager *, int);
int OSDisableInterrupts();
void OSRestoreInterrupts(int);
int vsprintf(char *, const char *, va_list);
void TexMgr_DrawText_Format(float, float, int, int, int, int, int, const char *, ...);
void TexMgr_DrawText_Format_Variant2(int, float, float, const char *, ...);
}
static inline CardStep &CardCallback(unsigned char *table, unsigned int offset) {
    return *(CardStep *)(table + offset);
}
static inline void CardDrawLine(CardTextLine *line) {
    TexMgr_DrawText_Format(line->x, line->y, line->font,
        line->r, line->g, line->b, line->a, line->format);
}
static inline void CardDrawWelcome(unsigned int offset) {
    CardDrawLine((CardTextLine *)(CardTaskChecks_data_803FE480 + offset) + isJapanese());
}
static inline void CardDrawFrame() {
    ResCtrl rc;
    rc.mode = 2;
    rc.width = 540.0f; rc.height = 380.0f;
    rc.Show(320.0f, 240.0f, 1.0f);
    rc.SetColor(0xFFFFFF7F);
    fn_8011FAFC(&rc, 7);
}
static inline void CardDrawLeftChoice(PrintObject *self) {
    ResCtrl rc;
    rc.resId = 0x891 + (self->frames >> 4) % 5;
    rc.Show(self->leftX, self->y, 1.0f);
    fn_8011FAFC(&rc, 0);
}
#define CardMicroseconds(ticks) (((ticks) * 8) / ((*(unsigned int *)0x800000F8 / 4) / 125000))
static inline void CardDrawWait(unsigned int offset) {
    CardDrawLine((CardTextLine *)((unsigned char *)CardTaskWaitInput_DrawByButtons_data_803FE5FC + offset) + isJapanese());
}
static inline void CardDrawCamera(unsigned int offset) {
    CardDrawLine((CardTextLine *)((unsigned char *)CameraChecker_Draw_rodata_80312CC4 + offset) + isJapanese());
}
#endif
