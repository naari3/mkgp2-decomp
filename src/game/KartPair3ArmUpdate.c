/* KartPair3ArmUpdate (0x800B2AF8): carrot item effect (sprite 0x8D). Three
 * carrots wander around the screen, bouncing off its edges, while the
 * horn SE loops; once the timer runs out they leave the screen and the
 * effect frees itself. Picks the character voice lines on its first frame. */

#include "game/types/Vec.h"
#include "game/types/Vec2.h"
#include "game/types/Int4.h"

typedef struct CarrotPad {
    unsigned char pad0[0x10];
    unsigned long long buttons;
} CarrotPad;

typedef struct CarrotOwner {
    unsigned char pad0[0x304];
    CarrotPad *pad;
} CarrotOwner;

typedef struct CarrotKart {
    unsigned char pad0[0x1F4];
    int character;
    int lineSet;
} CarrotKart;

typedef struct Carrots {
    CarrotKart *kart;      /* 0x00 */
    CarrotOwner *owner;    /* 0x04 */
    int voice;             /* 0x08 */
    int line;              /* 0x0C */
    int timer;             /* 0x10 */
    int skipDelay;         /* 0x14 */
    int holdDelay;         /* 0x18 */
    int counter;           /* 0x1C */
    Vec2 pos[3];           /* 0x20 */
    float yaw[3];          /* 0x38 */
    signed char gone[3];   /* 0x44 */
    int se;                /* 0x48 */
} Carrots;

typedef struct Camera {
    unsigned char pad0[0x80];
    Vec pos;
} Camera;

extern int g_gameMode;
extern unsigned char g_namCamFlag;
extern unsigned char g_playerData[];
extern Int4 Kart_rodata_803292E0;
extern Vec KartPair3ArmUpdate_rodata_803293D0;
extern Camera lbl_805DF3D0;

extern void CarrotItemEffect_AddDraw(void *self);
extern void SpriteSlot_InitNonLoop(void *slot, int res);
extern void SpriteSlot_Container_Free(void *self);
extern unsigned char GetVBlankFlag(void);
extern unsigned char VBlankValue_Get(void);
extern unsigned char *PcbSlot_GetByIndex(int idx);
extern int fn_80231BD4(int character, int set, int alt);
extern void PreloadResource(int id);
extern void fn_80120A08(int id);
extern int SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
#ifdef __MWERKS__
extern void SoundMgr_PlaySE_WithChannel(int se, Vec pos, int ch);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void SoundMgr_PlaySE_WithChannel(int, Vec *, int);
static inline void SoundMgr_PlaySE_WithChannel_ByValue(int se, Vec pos, int ch) { SoundMgr_PlaySE_WithChannel(se, &pos, ch); }
#define SoundMgr_PlaySE_WithChannel SoundMgr_PlaySE_WithChannel_ByValue
#endif
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern float BuildOrientationFromYaw(float yaw);
extern float Rand_RangeFloatMax(float max);
extern double sin(double);
extern double cos(double);

static inline void Carrot_InitVoice(Carrots *c)
{
    CarrotKart *kart;
    Int4 lines;
    int character;
    kart = c->kart;
    c->voice = -1;
    c->line = -1;
    lines = Kart_rodata_803292E0;
    character = kart->character;
    if (g_gameMode == 0) {
        if (GetVBlankFlag() && VBlankValue_Get() != 1 && g_playerData[0x19D] && g_namCamFlag &&
            character != 6) {
            c->voice = fn_80231BD4(character, kart->lineSet, 0);
            c->line = lines.v[character];
        }
    } else if (g_gameMode == 2 && character != 6 && ((PcbSlot_GetByIndex(character)[3] >> 5) & 1)) {
        c->voice = fn_80231BD4(character, kart->lineSet, 1);
        c->line = lines.v[character];
    }
    if (c->voice == -1 && c->line == -1) {
        c->voice = fn_80231BD4(6, kart->lineSet, 0);
        c->line = -1;
    }
    if (c->voice != -1) {
        PreloadResource(c->voice);
    }
    if (c->line != -1) {
        PreloadResource(c->line);
    }
}

void KartPair3ArmUpdate(unsigned char *self)
{
    Carrots *c = (Carrots *)(self + 0xEC);
    int i;

    switch ((signed char)self[0xC8]) {
    case 0: {
        SpriteSlot_InitNonLoop(self + 0x14, 0x8D);
        self[0x14] = 1;
        *(void **)(self + 0x78) = CarrotItemEffect_AddDraw;
        *(void **)(self + 0x7C) = self;
        Carrot_InitVoice(c);
        c->timer = 600;
        c->skipDelay = 3;
        c->holdDelay = 3;
        for (i = 0; i < 3; i++) {
            Vec yaw = KartPair3ArmUpdate_rodata_803293D0;
            c->pos[i].x = 320.0f;
            c->pos[i].y = 240.0f;
            c->yaw[i] = (&yaw.x)[i];
            c->gone[i] = 0;
        }
        c->se = -1;
        self[0xC8]++;
    }
    case 1:
        break;
    }

    if (c->se < 0) {
        c->se = SoundMgr_CountActiveSEInstances(0xCD);
        if (c->se >= 0) {
            SoundMgr_PlaySE_Positional(0xCD, lbl_805DF3D0.pos, c->se);
        }
    } else {
        SoundMgr_PlaySE_WithChannel(0xCD, lbl_805DF3D0.pos, c->se);
    }

    for (i = 0; i < 3; i++) {
        if (c->gone[i]) {
            continue;
        }
        c->pos[i].x += 10.0f * (float)sin(c->yaw[i]);
        c->pos[i].y += 10.0f * (float)cos(c->yaw[i]);
        if (c->timer != 0) {
            int hit = 0;
            if (c->pos[i].x < 50.0f || 590.0f < c->pos[i].x) {
                if (c->pos[i].x < 50.0f) {
                    c->pos[i].x = 50.0f;
                } else {
                    c->pos[i].x = 590.0f;
                }
                c->yaw[i] = BuildOrientationFromYaw(c->yaw[i]);
                c->yaw[i] *= -1.0f;
                c->yaw[i] = BuildOrientationFromYaw(c->yaw[i]);
                hit = 1;
            }
            if (c->pos[i].y < 140.0f || 520.0f < c->pos[i].y) {
                if (c->pos[i].y < 140.0f) {
                    c->pos[i].y = 140.0f;
                } else {
                    c->pos[i].y = 520.0f;
                }
                c->yaw[i] = BuildOrientationFromYaw(1.570796f + c->yaw[i]);
                c->yaw[i] *= -1.0f;
                c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - 1.570796f);
                hit = 1;
            }
            if (hit) {
                float a = c->yaw[i];
                if (a < -1.570796f) {
                    if (a < -2.356194f) {
                        c->yaw[i] = BuildOrientationFromYaw(0.017453289f * Rand_RangeFloatMax(30.0f) + c->yaw[i]);
                    } else {
                        c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - 0.017453289f * Rand_RangeFloatMax(30.0f));
                    }
                } else if (a < 0.0f) {
                    if (a < -0.785398f) {
                        c->yaw[i] = BuildOrientationFromYaw(0.017453289f * Rand_RangeFloatMax(30.0f) + c->yaw[i]);
                    } else {
                        c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - 0.017453289f * Rand_RangeFloatMax(30.0f));
                    }
                } else if (a < 1.570796f) {
                    if (a < 0.785398f) {
                        c->yaw[i] = BuildOrientationFromYaw(0.017453289f * Rand_RangeFloatMax(30.0f) + c->yaw[i]);
                    } else {
                        c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - 0.017453289f * Rand_RangeFloatMax(30.0f));
                    }
                } else if (a < 2.356194f) {
                    c->yaw[i] = BuildOrientationFromYaw(0.017453289f * Rand_RangeFloatMax(30.0f) + c->yaw[i]);
                } else {
                    c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - 0.017453289f * Rand_RangeFloatMax(30.0f));
                }
            }
        } else {
            if (c->pos[i].x < -640.0f) {
                c->gone[i] = 1;
            }
            if (c->pos[i].y < -480.0f) {
                c->gone[i] = 1;
            }
            if (1280.0f < c->pos[i].x) {
                c->gone[i] = 1;
            }
            if (960.0f < c->pos[i].y) {
                c->gone[i] = 1;
            }
        }
    }

    if (c->skipDelay == 0 && (c->owner->pad->buttons & 0x10000ULL)) {
        c->timer = 0;
    }
    if (c->holdDelay == 0 && !(c->owner->pad->buttons & 0x0020000000000000ULL)) {
        c->timer = 0;
    }

    if (c->gone[0] && c->gone[1] && c->gone[2]) {
        if (c->se >= 0) {
            SoundMgr_StopSE_OrSpecial(0xCD, c->se);
            c->se = -1;
        }
        if (c->voice != -1) {
            fn_80120A08(c->voice);
        }
        if (c->line != -1) {
            fn_80120A08(c->line);
        }
        SpriteSlot_Container_Free(self);
        return;
    }

    if (c->timer != 0) {
        c->timer--;
    }
    if (c->skipDelay != 0) {
        c->skipDelay--;
    }
    if (c->holdDelay != 0) {
        c->holdDelay--;
    }
    if (c->counter != 0) {
        c->counter--;
    }
}
