#include "game/types/reg_args.h"
#include "game/FlowDispatcher_private.h"
#include "game/CreditHud.h"
extern "C" {
unsigned int OSGetTick();
void Profiler_RecordFrame(int, float);
extern const float lbl_806D2280;
extern unsigned char lbl_806D1191;
extern unsigned char lbl_80598A60[];
void MetricsTable_ResetAll();
void Sci2Card_PollAndAdvanceState();
void Frame_Begin();
void Scene_Draw(FlowObject *);
void Frame_PostDraw_BackupBuffer();
int Vtable_CallSlot2(FlowObject *);
void GXDrawDone();
void Flow_TransitionTo(FlowDispatcher *, int);
void DebugOverlay_Dispatch(FlowDispatcher *);
void Timer_Decrement();
void PCBComm_Process(int, int);
void Frame_PostDrawOverlay();
void Frame_UpdatePerFrameState();
unsigned char ServiceButton_Handler();
void Profiler_ResetWriteIndex();
void *GetInputManager();
int WrapInRange(int, int, int);
void *StrPcb_GetInstance();
unsigned char BootConfigFlag_Get();
const char *StrPcb_GetErrorCodeString(void *);
unsigned char StrPcb_HasError(void *);
unsigned char StrPcb_GetCommErrorFlag(void *);
void DrawLinkErrorOverlay();
void CardTaskWelcome_DrawStatus(REG_ARGS1(void *unused));
void fn_80218B5C(CreditHud *);
void fn_8011F994(int);
void fn_801A1280();
void Game_Shutdown();
}
class FrameInput {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual unsigned char Pressed(int);
};
extern "C" FrameInput *InputMgr_GetPlayer(void *, unsigned int);
class ScopedTimer {
    unsigned int start;
    int slot;
public:
    ScopedTimer(int id) { slot = id; start = OSGetTick(); }
    ~ScopedTimer() {
        Profiler_RecordFrame(slot, (float)(((OSGetTick() - start) << 3) /
            ((*(volatile unsigned int *)0x800000F8 >> 2) / 125000)) / lbl_806D2280);
    }
};
extern "C" void MainGameLoop(FlowDispatcher *self)
{
    const char *text = lbl_802E89A0;
    unsigned char error = 0;
    while (!error) {
        DebugOverlay_Dispatch(self);
        MetricsTable_ResetAll();
        Sci2Card_PollAndAdvanceState();
        {
            ScopedTimer frame(0);
            Frame_Begin();
            {
                ScopedTimer draw(2);
                Scene_Draw(self->current);
                SpriteHandlePool_GC();
                if (!self) DebugPrintf(text + 0x550);
            }
            Frame_PostDraw_BackupBuffer();
            {
                ScopedTimer update(6);
                int next = Vtable_CallSlot2(self->current);
                if (!self) DebugPrintf(text + 0x560);
                if (next != -2) {
                    if (next == -3) {
                        DebugPrintf(text + 0x570);
                        break;
                    }
                    GXDrawDone();
                    Flow_TransitionTo(self, next);
                }
            }
            Timer_Decrement();
            PCBComm_Process(1, 1);
            error = lbl_806D1191;
        }
        Frame_PostDrawOverlay();
        {
            ScopedTimer update(6);
            Frame_UpdatePerFrameState();
            if (ServiceButton_Handler() == 1) {
                DebugPrintf(text + 0x584);
                break;
            }
            {
                ScopedTimer draw(2);
                Profiler_ResetWriteIndex();
            }
            if (lbl_80598A60[0x2a]) {
                FrameInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
                int change = 0;
                if (input->Pressed(0x40) == 1) change = -1;
                else if (input->Pressed(0x80) == 1) change = 1;
                self->overlay = WrapInRange(self->overlay + change, 0, 13);
            }
        }
        void *pcb = StrPcb_GetInstance();
        if (pcb && BootConfigFlag_Get() == 1) {
            StrPcb_GetErrorCodeString(pcb);
            if (StrPcb_HasError(pcb) == 1) error = 1;
            if (StrPcb_GetCommErrorFlag(pcb) == 1) error = 1;
        }
    }
    if (error == 1) {
        fn_80121210();
        CreditHud *hud = new CreditHud(0);
        do {
            Frame_Begin();
            if (lbl_806D1191) DrawLinkErrorOverlay();
            else CardTaskWelcome_DrawStatus(REG_ARGS1(0)); /* the callee ignores its parameter */
            hud->Update();
            fn_80218B5C(hud);
            for (int i = 0; i < 8; ++i) fn_8011F994(i);
            fn_801A1280();
            SpriteHandlePool_GC();
            Frame_PostDraw_BackupBuffer();
            if (lbl_806D1191) {
                Timer_Decrement();
                PCBComm_Process(1, 1);
            }
            Frame_PostDrawOverlay();
            Frame_UpdatePerFrameState();
        } while (!InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x1000));
        delete hud;
        Frame_PostDrawOverlay();
        Frame_UpdatePerFrameState();
    }
    Game_Shutdown();
}
