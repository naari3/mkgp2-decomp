#include "game/clFlowCourse.h"
#include "game/singleton.h"

/* clFlowCourse_Update, 801CF360..801D0C30 (6352 bytes).
 * Complete state-machine draft, retained as Object(NonMatching).
 * The four allocation guards use real C++ new expressions. */

struct CourseLayout {
    short id, field02;
    int field04;
    float x, y, field10;
};
struct ArrowLayout { float x, y, angle, x2, y2, angle2; };
struct CourseParams { int cup, round, field08; };
struct CoursePlayerInput {
    virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24();
    virtual void slot28(); virtual unsigned int Test(int);
};
/* Shared constant pool, 8039B990..8039BF3C. The leading three scales and
 * eighteen seven-key XY curves are also read by the course slot helpers.
 * Keeping each table distinct lets MWCC address it from one pooled base. */
static const float motionCurves[255] = {
        1.0f, 0.699999988f, 0.899999976f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
        1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
        66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
        1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
        83.3333359f, 5000.0f, 83.3333359f,
    };
static const float iconOffsets[4][2] = { { -28.0f, -28.0f }, { 28.0f, -28.0f }, { -28.0f, 28.0f }, { 28.0f, 28.0f } };
static const short animIds[8] = { 6511, 6512, 6513, 6514, 6515, 6516, 6517, 6518 };
static const ArrowLayout courseArrows[16] = {
        { 0.0f, 0.0f, 0.0f, 145.0f, 185.0f, -50.0f },
        { 115.0f, 225.0f, 130.0f, 205.0f, 225.0f, 50.0f },
        { 170.0f, 185.0f, -130.0f, 260.0f, 185.0f, -50.0f },
        { 240.0f, 225.0f, 130.0f, 330.0f, 225.0f, 50.0f },
        { 295.0f, 185.0f, -130.0f, 385.0f, 185.0f, -50.0f },
        { 365.0f, 225.0f, 130.0f, 455.0f, 225.0f, 50.0f },
        { 420.0f, 185.0f, -130.0f, 510.0f, 185.0f, -50.0f },
        { 490.0f, 225.0f, 130.0f, 580.0f, 225.0f, 50.0f },
        { 60.0f, 225.0f, 130.0f, 150.0f, 225.0f, 50.0f },
        { 134.0f, 185.0f, -130.0f, 224.0f, 185.0f, -50.0f },
        { 192.0f, 225.0f, 130.0f, 282.0f, 225.0f, 50.0f },
        { 248.0f, 185.0f, -130.0f, 338.0f, 185.0f, -50.0f },
        { 284.0f, 225.0f, 130.0f, 394.0f, 225.0f, 50.0f },
        { 372.0f, 185.0f, -130.0f, 460.0f, 185.0f, -50.0f },
        { 426.0f, 225.0f, 130.0f, 516.0f, 225.0f, 50.0f },
        { 492.0f, 185.0f, -130.0f, 0.0f, 0.0f, 0.0f },
    };

extern "C" {
extern CourseLayout clFlowCourse_data_8049B1E0[];
extern short clFlowCourse_data_8049B388[][2];
extern int g_gameMode, g_roundIndex, g_localPcbRole, lbl_806CF12C;
extern signed char lbl_806D184C, lbl_806D184D;
extern unsigned char g_playerData[];
extern const float lbl_806D9ED8, lbl_806D9EDC, lbl_806D9EE0, lbl_806D9EE4;
extern const float lbl_806D9EE8, lbl_806D9EEC, lbl_806D9EF0, lbl_806D9EF4;
extern const float lbl_806D9EF8, lbl_806D9EFC, lbl_806D9F00, lbl_806D9F04;
extern const float lbl_806D9F08, lbl_806D9F0C, lbl_806D9F10, lbl_806D9F14;
extern const float lbl_806D9F18, lbl_806D9F1C, lbl_806D9F20, lbl_806D9F24;
extern const float lbl_806D9F28, lbl_806D9F2C, lbl_806D9F30;
void RumbleUpdate();
void fn_801CEB78(CourseFlow *, int, int);
void fn_801CE918(CourseFlow *, int);
void Sprite_SetAnimParam(CourseSprite *, int, short);
void Sprite_SetupAnim(CourseSprite *, int, int, int);
unsigned char Sprite_AdvanceAnim(CourseSprite *, float);
void fn_801A0550(CourseSprite *);
void fn_8019FF6C(CourseSprite *, int);
void fn_80121E10(ResCtrl *);
short GetCourseShortIdByCupAndMirror(int, int);
void fn_801699D8(int, int);
void fn_801B7CAC();
void fn_801B7C64();
void *GetInputManager();
CoursePlayerInput *InputMgr_GetPlayer(void *, int);
void SetScreenBrightness(float);
void SetRumbleMode(int, int, int);
CourseParams *GetCourseSelectEntry(int);
void SetCourseParams(int, int, int, int);
void SetSyncTarget(int);
unsigned char IsSyncReached();
unsigned char *SyncSlot_GetRecv();
int GetDisplayBufferIndex();
unsigned char *PcbSlot_GetByIndex(int);
}

static inline InputState *CourseInput() {
    return SINGLETON_INSTANCE(g_pInputState);
}

static inline void SetSpritePosition(CourseSprite *sprite, float x, float y) {
    sprite->x = x;
    sprite->y = y;
}

static inline void SetAlpha(ResCtrl *ctrl, unsigned int color, float a) {
    color = ((color) & 0xFFFFFF00 | (unsigned char)((int)(lbl_806D9EE4 * a)));
    ctrl->SetColor(color);
}

static inline int CourseCup(int i) {
    switch (i) {
    case 0: return 7; case 1: return 1; case 2: return 8; case 3: return 2;
    case 4: return 3; case 5: return 4; case 6: return 5; case 7: return 6;
    default: return 1;
    }
}
static inline void UpdatePreview(CourseFlow *self, int selection) {
    int cup = selection / 2;
    *self->mapIdA = clFlowCourse_data_8049B388[cup][0];
    *self->mapIdB = clFlowCourse_data_8049B388[cup][1];
    fn_80121E10(&self->preview);
    self->preview.resId = GetCourseShortIdByCupAndMirror(CourseCup(cup), selection % 2);
    self->preview.Show(lbl_806D9EE8, lbl_806D9EEC, lbl_806D9EDC);
}
static inline void UpdateArrows(CourseFlow *self, const ArrowLayout *arrows) {
    self->field140 = 0;
    if (self->field138) {
        float y;
        float x = arrows[self->selection].x;
        y = arrows[self->selection].y;
        SetSpritePosition(self->field138, x, y);
        self->field138->rotation = arrows[self->selection].angle;
        if (self->selection != 0) self->field140 = 1;
    }
    self->field141 = 0;
    if (self->field13C) {
        float y;
        float x = arrows[self->selection].x2;
        y = arrows[self->selection].y2;
        SetSpritePosition(self->field13C, x, y);
        self->field13C->rotation = arrows[self->selection].angle2;
        if (self->selection != 15) self->field141 = 1;
        if (self->field15D == 1 && self->selection == 7) self->field141 = 0;
    }
}
static inline void ActivatePulse(CoursePulse *p) {
    if ( (p->active != 1 || p->flag != 0)) {
        p->active = 1; p->flag = 0; p->timer = 0;
    }
}
static inline void DeactivatePulse(CoursePulse *p) {
    if (p->active != 0 && p->flag != 1) {
        p->flag = 1; p->timer = 0;
    }
}
static inline void ShowPulse(CoursePulse *p) { if (p) ActivatePulse(p); }
static inline void HidePulse(CoursePulse *p) { if (p) DeactivatePulse(p); }
static inline float PulseAlpha(CoursePulse *p) {
    if (p->flag == 0) return (float)p->timer * lbl_806D9F30;
    return lbl_806D9EDC - (float)p->timer * lbl_806D9F30;
}
static inline void SetupExitSprites(CourseFlow *self) {
    if (self->left) Sprite_SetupAnim(self->left, 0x23, 1, 0);
    if (self->right) Sprite_SetupAnim(self->right, 0x26, 1, 0);
    if (self->fieldC4) {
        Sprite_SetupAnim(self->fieldC4, 0x83, 1, 0);
        Sprite_SetAnimParam(self->fieldC4, 0x1970, animIds[self->selection / 2]);
    }
}

static inline void UpdateRemoteIcons(CourseFlow *self) {
    for (int i = 0; i < 4; i++) {
        if (i != GetDisplayBufferIndex()) {
            int role = g_localPcbRole;
            if (((PcbSlot_GetByIndex(i)[0] >> 4) & 7) == role) {
                CourseLayout *layout;
                int selected = (PcbSlot_GetByIndex(i)[5] >> 1) & 0x7F;
                layout = &clFlowCourse_data_8049B1E0[selected];
                float x = layout->x;
                float a;
                if (self->selection >= 8) x -= lbl_806D9ED8;
                CourseIcon *icon = self->icons[i];
                a = lbl_806D9EDC;
                icon->ctrl.Show(x + iconOffsets[icon->index][0],
                    layout->y + iconOffsets[icon->index][1], a);
                if (self->state >= 3) a = lbl_806D9EE0;
                if (self->selection / 8 != selected / 8) a = lbl_806D9EE0;
                SetAlpha(&self->icons[i]->ctrl, 0xFFFFFF00, a);
            }
        }
    }
}

#pragma push
#pragma opt_dead_assignments off
extern "C" int clFlowCourse_Update(CourseFlow *self) {
    RumbleUpdate();
    if (self->advance) { self->state++; self->advance = 0; }
    self->timer++;
    switch (self->state) {
    case 0:
        if (self->timer == 1) fn_801CEB78(self, 0, 1);
        if (self->timer == 6) fn_801CEB78(self, 1, 1);
        if (self->timer == 10) fn_801CEB78(self, 2, 1);
        if (self->timer == 14) fn_801CEB78(self, 3, 1);
        if (self->timer == 18) fn_801CEB78(self, 4, 1);
        if (self->timer == 22) fn_801CEB78(self, 5, 1);
        if (self->timer == 26) fn_801CEB78(self, 6, 1);
        if (self->timer == 30) fn_801CEB78(self, 7, 1);
        if (self->timer == 25) {
            self->fieldC4 = new CourseSprite(0x84, 0, lbl_806D9EFC, lbl_806D9F00,
                lbl_806D9EDC, lbl_806D9EDC, lbl_806D9EE0, lbl_806D9EDC);
            Sprite_SetAnimParam(self->fieldC4, 0x1970, 0x196F);
        }
        if (self->timer >= 54) {
            float a = (float)(self->timer - 50) / lbl_806D9F04;
            self->map->alpha = a; self->field12C->alpha = a; self->field130->alpha = a;
            SetAlpha(&self->preview, 0xFFFFFF00, a);
        }
        if (self->timer == 60) {
            SetScreenBrightness(self->field18);
            lbl_806D184C = 1; lbl_806D184D = 0;
            UpdateArrows(self, courseArrows);
            fn_801CEB78(self, 0, 2);
            for (int i = 1; i < 8; i++) fn_801CEB78(self, i, 6);
            for (int i = 8; i < 16; i++) fn_801CEB78(self, i, 5);
            self->fieldBC = new CourseSprite(0x25, 1, lbl_806D9F08, lbl_806D9F0C,
                lbl_806D9EDC, lbl_806D9EDC, lbl_806D9EE0, lbl_806D9EDC);
            self->fieldC0 = new CourseSprite(0x28, 1, lbl_806D9F10, lbl_806D9F0C,
                lbl_806D9EDC, lbl_806D9EDC, lbl_806D9EE0, lbl_806D9EDC);
            self->advance = 1;
            fn_801699D8(0, 1); fn_801699D8(1, 1);
            if (self->field15D) {
                self->fieldBC->alpha = lbl_806D9EE0;
                self->fieldC0->alpha = lbl_806D9EE0;
            }
        }
        break;
    case 1: {
        int previous = self->selection;
        if (CourseInput()) {
            self->selection += CourseInput()->dir;
            if (self->selection > 15) self->selection = 15;
            if (self->selection < 0) self->selection = 0;
            if (self->field15D && self->selection > 7) self->selection = 7;
        }
        if (previous != self->selection) {
            fn_801CEB78(self, previous, 6);
            fn_801CEB78(self, self->selection, 2);
            UpdatePreview(self, self->selection);
            UpdateArrows(self, courseArrows);
            if (previous == 7 && self->selection == 8) {
                self->state = 98; self->timer = 0;
                self->field140 = 0; self->field141 = 0;
            }
            if (previous == 8 && self->selection == 7) {
                self->state = 99; self->timer = 0;
                self->field140 = 0; self->field141 = 0;
            }
            if (self->fieldC4) {
                delete self->fieldC4;
                self->fieldC4 = new CourseSprite(0x1BF, 0, 0);
                Sprite_SetAnimParam(self->fieldC4, 0x1970, animIds[self->selection / 2]);
                fn_801A0550(self->fieldC4);
                SetSpritePosition(self->fieldC4, lbl_806D9EFC, lbl_806D9F00);
                fn_8019FF6C(self->fieldC4, 1);
            }
            fn_801B7CAC(); lbl_806CF12C = self->selection;
        }
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Test(0x400)) {
            self->reverse = 1; ShowPulse(self->pulse);
        } else { self->reverse = 0; HidePulse(self->pulse); }
        int next = self->field20;
        switch (next) {
        case -1: {
            self->field18 -= lbl_806D9EF4;
            InputMgr_GetPlayer(GetInputManager(), 0);
            if (CourseInput()->held == 1 || self->field18 < lbl_806D9EE0) {
                SetRumbleMode(0, 1, 1);
                if (CourseInput()) {
                    InputState *input = CourseInput();
                    input->enabled = 0; input->held = 0; input->edge = 0;
                }
                CourseParams *params = GetCourseSelectEntry(self->selection);
                lbl_806CF12C = self->selection;
                SetCourseParams(params->cup, params->round, params->field08, self->reverse);
                int extra;
                int round = self->selection % 2;
                extra = 4;
                if (self->reverse == 0) extra = 0;
                g_roundIndex = round + extra;
                if (g_gameMode == 1) self->field20 = 0x26; else self->field04 = 1;
                self->field18 = lbl_806D9EF8;
                fn_801B7C64(); lbl_806D184C = -1;
                self->field140 = 0; self->field141 = 0;
            }
            SetScreenBrightness(self->field18);
            next = self->field20;
            break;
        }
        default: break;
        }
        if (next != -1 || self->field04) {
            fn_801CEB78(self, self->selection, 3);
            delete self->fieldBC; delete self->fieldC0;
            self->fieldBC = 0; self->fieldC0 = 0; self->timer = 0;
            if (g_gameMode == 2) {
                CourseBanner *banner = self->banner;
                if (banner->state == 3) { banner->state = 0; banner->timer = 0; }
                self->advance = 1;
            } else {
                self->state = 4;
                for (int i = 0; i < 18; i++)
                    if (i != self->selection) fn_801CEB78(self, i, 7);
            }
        }
        break;
    }
    case 2:
        SetSyncTarget(0x1A);
        if (IsSyncReached()) {
            if (g_playerData[0x19F]) self->field20 = 0x21;
            else self->field20 = 0x22;
            CourseBanner *banner = self->banner;
            if (banner->state == 0 || banner->state == 1) {
                banner->state = 2; banner->timer = 0;
            }
        }
        if (self->field20 != -1) {
            self->selected = (*(unsigned short *)SyncSlot_GetRecv() >> 4) & 0x7F;
            self->reverse = (SyncSlot_GetRecv()[1] >> 3) & 1;
            CoursePulse *pulse = self->pulse;
            if (pulse) {
                if (self->reverse == 0) DeactivatePulse(pulse); else ActivatePulse(pulse);
            }
            UpdatePreview(self, self->selected);
            self->timer = 0; self->advance = 1;
        }
        break;
    case 3:
        if (self->timer < 5) break;
        if (self->timer == 5) {
            for (int i = 0; i < 18; i++) if (i != self->selected) fn_801CEB78(self, i, 7);
            fn_801CEB78(self, self->selected, 3);
        }
        if (self->timer <= 10) {
            float a = lbl_806D9EDC - (float)(self->timer - 5) / lbl_806D9F14;
            self->field12C->alpha = a; self->field130->alpha = a;
        }
        if (self->timer < 20) break;
        if (self->timer <= 30) {
            CourseLayout *p;
            float t = (float)(self->timer - 20) / lbl_806D9F04;
            p = &clFlowCourse_data_8049B1E0[self->selected];
            float y = p->y + t * (lbl_806D9F18 - p->y);
            float x;
            if (self->selection > 8) {
                float from = p->x - lbl_806D9ED8;
                x = from + t * (lbl_806D9EFC - from);
            } else x = p->x + t * (lbl_806D9EFC - p->x);
            SetSpritePosition(self->slots[self->selected].sprite, x, y);
        }
        if (self->timer == 30) self->field15C = 1;
        if (self->timer == 120) {
            fn_801CEB78(self, self->selected, 4);
            SetupExitSprites(self);
            self->field06 = 1; self->timer = 0; self->state = 5;
        }
        break;
    case 4:
        if (self->timer <= 5 && self->field12C->alpha > lbl_806D9EE0) {
            float a = lbl_806D9EDC - (float)self->timer / lbl_806D9F14;
            self->field12C->alpha = a; self->field130->alpha = a;
        }
        if (self->timer > 42) {
            fn_801CEB78(self, self->selection, 4); SetupExitSprites(self);
            self->field06 = 1; self->advance = 1; self->timer = 0;
        }
        break;
    case 5:
        if (self->timer <= 5) {
            float a = lbl_806D9EDC - (float)self->timer / lbl_806D9F14;
            self->map->alpha = a;
            SetAlpha(&self->preview, 0xFFFFFF00, a);
            HidePulse(self->pulse);
        }
        if (self->timer >= 30) {
            fn_801699D8(0, 0); fn_801699D8(1, 0);
            return self->field20;
        }
        break;
    case 98:
        self->field14 = -(lbl_806D9F1C * (float)self->timer);
        for (int i = 0; i < 18; i++)
            if (self->slots[i].sprite) self->slots[i].sprite->x = self->field14 + clFlowCourse_data_8049B1E0[i].x;
        if (self->field12C) self->field12C->x = lbl_806D9F20 + self->field14;
        if (self->field130) self->field130->x = lbl_806D9F24 + self->field14;
        if (self->timer >= 20) { self->state = 1; UpdateArrows(self, courseArrows); }
        break;
    case 99:
        self->field14 = lbl_806D9F1C * (float)self->timer + lbl_806D9F28;
        for (int i = 0; i < 18; i++)
            if (self->slots[i].sprite) self->slots[i].sprite->x = self->field14 + clFlowCourse_data_8049B1E0[i].x;
        if (self->field12C) self->field12C->x = lbl_806D9F20 + self->field14;
        if (self->field130) self->field130->x = lbl_806D9F24 + self->field14;
        if (self->timer >= 20) { self->state = 1; UpdateArrows(self, courseArrows); }
        break;
    }
    if (self->left) {
        if (!Sprite_AdvanceAnim(self->left, lbl_806D9EF0) && !self->field06) {
            Sprite_SetupAnim(self->left, 0x16D, 1, 0); fn_8019FF6C(self->left, 1);
        }
        SetSpritePosition(self->left, lbl_806D9EFC + self->field14, lbl_806D9F2C);
    }
    if (self->right) {
        if (!Sprite_AdvanceAnim(self->right, lbl_806D9EF0) && !self->field06) {
            Sprite_SetupAnim(self->right, 0x16F, 1, 0); fn_8019FF6C(self->right, 1);
        }
        SetSpritePosition(self->right, lbl_806D9F24 + self->field14, lbl_806D9F2C);
    }
    if (self->fieldC4 && !Sprite_AdvanceAnim(self->fieldC4, lbl_806D9EF0) && !self->field06) {
        Sprite_SetupAnim(self->fieldC4, 0x1BF, 0, 0);
        Sprite_SetAnimParam(self->fieldC4, 0x1970, 0x196F);
        fn_801A0550(self->fieldC4); fn_8019FF6C(self->fieldC4, 1);
    }
    if (self->fieldBC) {
        Sprite_AdvanceAnim(self->fieldBC, lbl_806D9EF0);
        self->fieldBC->x = lbl_806D9F08 + self->field14;
    }
    if (self->fieldC0) {
        Sprite_AdvanceAnim(self->fieldC0, lbl_806D9EF0);
        self->fieldC0->x = lbl_806D9F10 + self->field14;
    }
    if (self->field12C) Sprite_AdvanceAnim(self->field12C, lbl_806D9EF0);
    if (self->field130) Sprite_AdvanceAnim(self->field130, lbl_806D9EF0);
    if (self->map) Sprite_AdvanceAnim(self->map, lbl_806D9EF0);
    CoursePulse *p = self->pulse;
    if (p && p->active) {
        if (p->timer <= 8) {
            p->sprite->alpha = PulseAlpha(p);
            if (p->timer++ == 8 && p->flag) { p->active = 0; p->flag = 0; }
        }
        Sprite_AdvanceAnim(p->sprite, lbl_806D9EF0);
    }
    if (self->field138) Sprite_AdvanceAnim(self->field138, lbl_806D9EF0);
    if (self->field13C) Sprite_AdvanceAnim(self->field13C, lbl_806D9EF0);
    for (int i = 0; i < 18; i++) fn_801CE918(self, i);
    if (self->field15C == 1 && self->slots[self->selected].sprite) {
        SetSpritePosition(self->slots[self->selected].sprite, lbl_806D9EFC, lbl_806D9F18);
    }
    if (g_gameMode == 2) {
        UpdateRemoteIcons(self);
        if (self->banner) fn_801D1684(self->banner);
    }
    return -1;
}
#pragma pop

