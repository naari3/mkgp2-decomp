#include "game/FlowScene.h"
class EntryPad {
public:
    virtual ~EntryPad();
    virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void *IsPressed(int);
};
struct EntryCard {
    char pad0[0x10]; int stage; char pad14[0x25]; unsigned char flag39; char pad3A[0x52];
    EntryCard(int, int, int);
    bool Done() { return stage == 6; }
};
struct EntryUpdate {
    void *vt; unsigned char done, cardMode, cardDone, clean;
    int peers; float brightness; int next;
    void *sprite, *fade;
    EntryCard *card;
};
extern "C" {
extern int lbl_8049A858[];
extern const float lbl_806D9968, lbl_806D996C, lbl_806D9978, lbl_806D997C;
extern int g_gameMode, g_localPcbRole;
void RumbleUpdate(); void card_cleaning_state_machine(); int CountPeersWithRole(int);
void Sprite_SetAnimParam(void *, short, short);
float PcbSyncTable_GetMyValue(); void SetScreenBrightness(float);
void Sprite_SetAnimTime(void *, float); void Sprite_AdvanceAnim(void *, float);
void *GetInputManager(); EntryPad *InputMgr_GetPlayer(void *, int);
void fn_80161F28(EntryCard *, int); void fn_801618CC(EntryCard *, int, int);
void fn_80161888(EntryCard *); void SetRumbleMode(int, int, int);
void fn_80160588(EntryCard *, int, int); int fn_801BA1A4(EntryUpdate *);
void SetSyncTarget(int); unsigned char PCBComm_ConfirmHostLobby(); void SetTimerModeEnabled(int);
int clFlowEntry_Update(EntryUpdate *self) {
    RumbleUpdate();
    if (self->clean) card_cleaning_state_machine();
    int peers = CountPeersWithRole(1);
    if (self->peers != peers) {
        if (self->sprite) Sprite_SetAnimParam(self->sprite, lbl_8049A858[self->peers], lbl_8049A858[peers]);
        self->peers = peers;
    }
    self->brightness = PcbSyncTable_GetMyValue();
    SetScreenBrightness(self->brightness);
    float brightness = self->brightness;
    if (brightness < lbl_806D996C && self->fade) Sprite_SetAnimTime(self->fade, lbl_806D996C - brightness);
    if (self->sprite) Sprite_AdvanceAnim(self->sprite, lbl_806D9968);
    if (self->next == -1) {
        EntryPad *pad = InputMgr_GetPlayer(GetInputManager(), 0);
        if (self->cardMode) {
            int dir = 0;
            int held = 0;
            if (self->cardDone) {
                int finished = (unsigned char)self->card->Done();
                if (finished) {
                    fn_80161F28(self->card, 1);
                    self->card = 0;
                    self->cardMode = 0;
                }
            } else if (self->brightness < lbl_806D9978) {
                fn_801618CC(self->card, 1, 0);
                fn_80161888(self->card);
                self->cardDone = 1;
            } else {
                InputState *input = GetInput();
                if (input) {
                    dir = input->dir;
                    held = (unsigned char)(input->held == 1);
                    if (held) SetRumbleMode(0, 1, 1);
                }
            }
            if (self->card) fn_80160588(self->card, dir, held);
        } else if (!self->done && self->brightness > lbl_806D997C) {
            if (pad->IsPressed(0x400)) {
                SetRumbleMode(1, 1, 1);
                self->cardMode = 1;
                self->card = new EntryCard(1, 0, 9);
                self->card->flag39 = 1;
                self->cardDone = 0;
            }
        }
        if (!self->done && self->next == -1) fn_801BA1A4(self);
    } else {
        if (self->card) {
            if (self->card->stage == 6) return self->next;
            else fn_80160588(self->card, 0, 0);
        } else return self->next;
    }
    if (self->done) {
        SetSyncTarget(8);
        if (PCBComm_ConfirmHostLobby() == 1) {
            if (g_localPcbRole) { g_gameMode = 2; SetTimerModeEnabled(1); }
            else { g_gameMode = 0; SetTimerModeEnabled(0); }
            self->next = 9;
        }
        return self->next;
    }
    return -1;
}
}

