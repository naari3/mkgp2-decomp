#include "game/os_time.h"

typedef struct AttractScene {
    char pad00[5];
    signed char peers;
    char pad06[2];
    float brightness;
    char pad0C[0xC];
    OSTime lastBeep;
    void *spr20;
    void *spr24;
    void *spr28;
    void *spr2C;
    void *spr30;
} AttractScene;

extern void RumbleUpdate(void);
extern void PlaySoundDSP(int id);
extern unsigned char Sprite_AdvanceAnim(void *spr, float dt);
extern void Sprite_Destroy(void *spr, int flag);
extern void Sprite_SetAnimParam(void *spr, short from, short to);
extern void Sprite_SetAnimTime(void *spr, float time);
extern int CountPeersWithRole(int role);
extern float PcbSyncTable_GetMyValue(void);
extern void SetScreenBrightness(float brightness);
extern void fn_801DA1C4(AttractScene *self);
extern int lbl_8049BBE8[];

void fn_801DA574(AttractScene *self) {
    OSTime now;
    int peers;

    RumbleUpdate();
    now = OSGetTime();
    if ((float)OSTicksToMilliseconds(now - self->lastBeep) / 1000.0f >= 4.0f) {
        self->lastBeep = now;
        PlaySoundDSP(0x271);
    }
    if (self->spr20 != 0) {
        Sprite_AdvanceAnim(self->spr20, 0.0165f);
    }
    if (self->spr2C != 0 && Sprite_AdvanceAnim(self->spr2C, 0.0165f) == 0) {
        Sprite_Destroy(self->spr2C, 1);
        self->spr2C = 0;
    }
    if (self->spr30 != 0) {
        Sprite_AdvanceAnim(self->spr30, 0.0165f);
    }
    peers = CountPeersWithRole(1);
    if (self->peers != peers) {
        if (self->spr24 != 0) {
            Sprite_SetAnimParam(self->spr24, lbl_8049BBE8[self->peers], lbl_8049BBE8[peers]);
        }
        self->peers = peers;
    }
    self->brightness = PcbSyncTable_GetMyValue();
    SetScreenBrightness(self->brightness);
    if (self->brightness < 6.0f && self->spr28 != 0) {
        Sprite_SetAnimTime(self->spr28, 6.0f - self->brightness);
    }
    fn_801DA1C4(self);
}
