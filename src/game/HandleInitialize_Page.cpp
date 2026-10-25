/*
 * HandleInitialize_Page @ 0x80071AE0..0x80071E1C: the handle (steering
 * wheel / pedal) initialize test page. Waits for the force-feedback board
 * to settle, then stores the current analog values as the new neutral
 * calibration when the select button is pressed.
 */
#include "game/TestMenuPage.h"

struct HandleCalib {
    unsigned char pad_0[0x34];
    int steer; /* 0x34 */
    int pos;   /* 0x38 */
    int brake; /* 0x3C */
    int accel; /* 0x40 */
};

struct HandleInitPage {
    unsigned char pad_0[8];
    int blink;            /* 0x08 */
    unsigned char pad_C[4];
    int next;             /* 0x10 */
    unsigned char pad_14[0x30];
    int steer;            /* 0x44 */
    int brake;            /* 0x48 */
    int accel;            /* 0x4C */
    unsigned char pad_50[0xC];
    unsigned char ready;  /* 0x5C */
    unsigned char pad_5D[0x213];
    void *text;           /* 0x270 */
    HandleCalib *calib;   /* 0x274 */
    unsigned char pad_278[0x10];
    int status;           /* 0x288 */
};

extern "C" {
extern unsigned short g_jvsOperatorBits[16];
extern MenuItem lbl_803FC5F4[];
extern const char lbl_806D2E60[6];
extern const char lbl_806D2E68[5];
void *StrPcb_GetInstance(void);
void StrPcb_BeginTimedNeutral(void *pcb);
int StrPcb_TimerTick(void *pcb);
int StrPcb_GetReceivedPosData(void *pcb);
void StrPcb_SetPositionTarget(void *pcb, short pos);
void JvsInput_SetSteeringCalibration(int raw);
void JvsInput_SetAccelCalibration(int raw);
void JvsInput_SetBrakeCalibration(int raw);
void Backup_PublishShadowCopy_Inline(void);
void SwitchTest_Page(HandleInitPage *self, int phase, int arg);
}

#pragma exceptions on

extern "C" int HandleInitialize_Page(HandleInitPage *self, int phase)
{
    char *pool = lbl_8030E598;
    int steer;
    int accel;
    int brake;

    if (phase == 0) {
        if (self->ready == 0) {
            StrPcb_BeginTimedNeutral(StrPcb_GetInstance());
        }
        self->steer = g_jvsOperatorBits[4];
        self->accel = g_jvsOperatorBits[5];
        self->brake = g_jvsOperatorBits[6];
    }
    if (phase == 1) {
        if (self->ready == 0) {
            self->status = StrPcb_TimerTick(StrPcb_GetInstance());
            if (self->status != 0) {
                self->ready = 1;
            }
            return 1;
        }
        steer = g_jvsOperatorBits[4];
        accel = g_jvsOperatorBits[5];
        brake = g_jvsOperatorBits[6];
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x800)) {
            self->calib->steer = steer;
            self->steer = steer;
            self->calib->accel = accel;
            self->accel = accel;
            self->calib->brake = brake;
            self->brake = brake;
            JvsInput_SetSteeringCalibration(self->steer);
            JvsInput_SetAccelCalibration(self->accel);
            JvsInput_SetBrakeCalibration(self->brake);
            self->calib->pos = StrPcb_GetReceivedPosData(StrPcb_GetInstance());
            StrPcb_SetPositionTarget(StrPcb_GetInstance(), self->calib->pos);
            Backup_PublishShadowCopy_Inline();
            self->next = 0xC;
            SwitchTest_Page(self, 0, -1);
        }
    }
    if (phase == 2) {
        if (self->ready == 0) {
            if (self->blink <= 0x1E) {
                DrawText(self->text, 0x7E, 0xD8, 7, 1.0f, pool + 0x2668);
            }
            return 1;
        }
        TestPage_DrawItems((TestPage *)self, lbl_803FC5F4, -1);
        if (self->text != 0) {
            int ds = g_jvsOperatorBits[4] - self->steer;
            int da = g_jvsOperatorBits[5] - self->accel;
            int db = g_jvsOperatorBits[6] - self->brake;
            if (da < 0) {
                da = 0;
            }
            if (db < 0) {
                db = 0;
            }
            DrawText(self->text, 0x177, 0x60, 7, 1.0f, lbl_806D2E60, ds / 64);
            DrawText(self->text, 0x177, 0x78, 7, 1.0f, lbl_806D2E68, da / 64);
            DrawText(self->text, 0x177, 0x90, 7, 1.0f, lbl_806D2E68, db / 64);
            DrawText(self->text, 0x2A, 0x198, 4, 1.0f, pool + 0x2680);
            if (self->status == 2) {
                DrawText(self->text, 0x2A, 0x138, 4, 1.0f, pool + 0x26A0);
                DrawText(self->text, 0x2A, 0x150, 4, 1.0f, pool + 0x26BC);
            }
        }
    }
    return 1;
}

#pragma exceptions reset
