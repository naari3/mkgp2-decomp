/* GP please panel: update anchor positions, animate badge, and enter race. */
#include "game/FlowScene.h"
#include "game/singleton.h"
#include "game/GpPleaseUpdate_private.h"
struct SpriteUpdateView { char pad[0x20]; float scale; };
struct BadgeUpdateView { SpriteUpdateView *sprite; unsigned char active, reverse; int frame; };
struct GpPleaseUpdate {
    void *vt; int timer, next;
    void *bg; TextManager *title; TextManager *texts[3];
    short *anchors[4]; unsigned char fading;
    void *anim; BadgeUpdateView *badge;
};
extern "C" {
void RumbleUpdate();
void fn_8019FF8C(void *, int, float *);
void Sprite_AdvanceAnim(void *, float);
void fn_8023CDA8(void *);
void fn_801699D8(int, int);
int VSMode_SeedRandomItemSequence(int, int, int);
void SetTimerModeEnabled(int);
int GetDisplayBufferIndex();
void RaceSlot_InitSlot(int, int, int, int, int);
void fn_801B7CD0(int);
extern int g_characterId;
extern unsigned char g_lakituStartAnimDone, lbl_806D1290, g_rendererGateFlag;
extern unsigned char g_playerData[0x2000];
extern const float lbl_806D9E88, lbl_806D9EA8, lbl_806D9EB0, lbl_806D9EB4;
static inline PlayerCharacterView *GetPlayerCharacter() { return (PlayerCharacterView *)g_playerData; }
static inline void InitPlayerSlot(int seed, int character) {
    RaceSlot_InitSlot(seed, GetDisplayBufferIndex(), character, 1, 0);
}
static inline void EnterRace(int seed) {
    SetTimerModeEnabled(1);
    g_lakituStartAnimDone = 0;
    lbl_806D1290 = 0;
    InitPlayerSlot(seed, g_characterId);
    GetPlayerCharacter()->SetCharacter(g_characterId);
    g_rendererGateFlag = 1;
    fn_801B7CD0(-1);
}
static inline void UpdateFade(GpPleaseUpdate *self) {
    bool pressed = SINGLETON_INSTANCE(g_pInputState)->held == 1;
    self->timer++;
    if (self->timer == 100) fn_801699D8(0, 1);
    if ((self->timer >= 240 || (pressed && self->timer >= 120)) && !self->fading) {
        self->fading = 1;
        self->timer = 0;
        fn_801699D8(0, 0);
    }
}
int fn_801CDF10(GpPleaseUpdate *self) {
    float pos[12]; // Complete 0x30-byte sprite node record.
    RumbleUpdate();
    fn_8019FF8C(self->bg, *self->anchors[0], pos);
    fn_801F93EC(self->title, pos[0], pos[1]);
    fn_8019FF8C(self->bg, *self->anchors[1], pos);
    fn_801F93EC(self->texts[0], pos[0], pos[1]);
    fn_8019FF8C(self->bg, *self->anchors[2], pos);
    fn_801F93EC(self->texts[1], pos[0], pos[1]);
    fn_8019FF8C(self->bg, *self->anchors[3], pos);
    fn_801F93EC(self->texts[2], pos[0], pos[1]);
    Sprite_AdvanceAnim(self->bg, lbl_806D9EB0);
    fn_8023CDA8(self->anim);
    BadgeUpdateView *badge = self->badge;
    if (badge->active) {
        if (badge->frame <= 8) {
            float scale;
            if (badge->reverse == 0) scale = badge->frame * lbl_806D9EB4;
            else scale = lbl_806D9EA8 - badge->frame * lbl_806D9EB4;
            badge->sprite->scale = scale;
            if (badge->frame++ == 8 && badge->reverse) {
                badge->active = 0;
                badge->reverse = 0;
            }
        }
        Sprite_AdvanceAnim(badge->sprite, lbl_806D9EB0);
    }
    if (self->next != -1) return self->next;
    UpdateFade(self);
    if (self->fading == 1 && self->timer > lbl_806D9E88) {
        EnterRace(VSMode_SeedRandomItemSequence(0, g_characterId, 0));
        self->next = 42;
    }
    return self->next;
}
}
