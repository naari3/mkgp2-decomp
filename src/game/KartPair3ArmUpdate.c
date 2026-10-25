/* KartPair3ArmUpdate (0x800B2AF8): carrot item effect (sprite 0x8D). Three
 * carrots wander around the screen, bouncing off its edges, while the
 * horn SE loops; once the timer runs out they leave the screen and the
 * effect frees itself. Picks the character voice lines on its first frame.
 * NonMatching (98.8%): stack slot order of the line table / yaw copies and
 * the character / loop-pointer callee-saved registers differ. */

typedef struct Vec { float x, y, z; } Vec;
typedef struct Vec2 { float x, y; } Vec2;
typedef struct Int4 { int v[4]; } Int4;

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
extern Int4 lbl_803292E0;
extern Vec lbl_803293D0;
extern Camera lbl_805DF3D0;
extern const float lbl_806D5020;
extern const float lbl_806D5024;
extern const float lbl_806D5034;
extern const float lbl_806D5054;
extern const float lbl_806D5070;
extern const float lbl_806D5080;
extern const float lbl_806D50C4;
extern const float lbl_806D50D0;
extern const float lbl_806D50E4;
extern const float lbl_806D50E8;
extern const float lbl_806D50EC;
extern const float lbl_806D50F0;
extern const float lbl_806D50F4;
extern const float lbl_806D50F8;
extern const float lbl_806D50FC;
extern const float lbl_806D5100;
extern const float lbl_806D5104;
extern const float lbl_806D5108;
extern const float lbl_806D510C;
extern const float lbl_806D5110;
extern const float lbl_806D5114;

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
extern void SoundMgr_PlaySE_WithChannel(int se, Vec pos, int ch);
extern void SoundMgr_StopSE_OrSpecial(int se);
extern float BuildOrientationFromYaw(float yaw);
extern float Rand_RangeFloatMax(float max);
extern double sin(double);
extern double cos(double);

static inline void Carrot_Init(Carrots *c, int i)
{
    Vec yaw = lbl_803293D0;
    c->pos[i].x = lbl_806D5020;
    c->pos[i].y = lbl_806D5024;
    c->yaw[i] = (&yaw.x)[i];
    c->gone[i] = 0;
}

void KartPair3ArmUpdate(unsigned char *self)
{
    CarrotKart *kart;
    Carrots *c = (Carrots *)(self + 0xEC);
    int i;
    int character;

    switch ((signed char)self[0xC8]) {
    case 0: {
        Int4 lines;

        SpriteSlot_InitNonLoop(self + 0x14, 0x8D);
        self[0x14] = 1;
        *(void **)(self + 0x78) = CarrotItemEffect_AddDraw;
        *(void **)(self + 0x7C) = self;
        kart = c->kart;
        c->voice = -1;
        c->line = -1;
        lines = lbl_803292E0;
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
        c->timer = 600;
        c->skipDelay = 3;
        c->holdDelay = 3;
        for (i = 0; i < 3; i++) {
            Carrot_Init(c, i);
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
        c->pos[i].x += lbl_806D5054 * (float)sin(c->yaw[i]);
        c->pos[i].y += lbl_806D5054 * (float)cos(c->yaw[i]);
        if (c->timer != 0) {
            int hit = 0;
            if (c->pos[i].x < lbl_806D50E4 || lbl_806D50E8 < c->pos[i].x) {
                if (c->pos[i].x < lbl_806D50E4) {
                    c->pos[i].x = lbl_806D50E4;
                } else {
                    c->pos[i].x = lbl_806D50E8;
                }
                c->yaw[i] = BuildOrientationFromYaw(c->yaw[i]);
                c->yaw[i] = c->yaw[i] * lbl_806D5070;
                c->yaw[i] = BuildOrientationFromYaw(c->yaw[i]);
                hit = 1;
            }
            if (c->pos[i].y < lbl_806D50EC || lbl_806D50F0 < c->pos[i].y) {
                if (c->pos[i].y < lbl_806D50EC) {
                    c->pos[i].y = lbl_806D50EC;
                } else {
                    c->pos[i].y = lbl_806D50F0;
                }
                c->yaw[i] = BuildOrientationFromYaw(lbl_806D50F4 + c->yaw[i]);
                c->yaw[i] = c->yaw[i] * lbl_806D5070;
                c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - lbl_806D50F4);
                hit = 1;
            }
            if (hit) {
                float a = c->yaw[i];
                if (a < lbl_806D50D0) {
                    if (a < lbl_806D50F8) {
                        c->yaw[i] = BuildOrientationFromYaw(lbl_806D5080 * Rand_RangeFloatMax(lbl_806D50FC) + c->yaw[i]);
                    } else {
                        c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - lbl_806D5080 * Rand_RangeFloatMax(lbl_806D50FC));
                    }
                } else if (a < lbl_806D5034) {
                    if (a < lbl_806D5100) {
                        c->yaw[i] = BuildOrientationFromYaw(lbl_806D5080 * Rand_RangeFloatMax(lbl_806D50FC) + c->yaw[i]);
                    } else {
                        c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - lbl_806D5080 * Rand_RangeFloatMax(lbl_806D50FC));
                    }
                } else if (a < lbl_806D50F4) {
                    if (a < lbl_806D50C4) {
                        c->yaw[i] = BuildOrientationFromYaw(lbl_806D5080 * Rand_RangeFloatMax(lbl_806D50FC) + c->yaw[i]);
                    } else {
                        c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - lbl_806D5080 * Rand_RangeFloatMax(lbl_806D50FC));
                    }
                } else if (a < lbl_806D5104) {
                    c->yaw[i] = BuildOrientationFromYaw(lbl_806D5080 * Rand_RangeFloatMax(lbl_806D50FC) + c->yaw[i]);
                } else {
                    c->yaw[i] = BuildOrientationFromYaw(c->yaw[i] - lbl_806D5080 * Rand_RangeFloatMax(lbl_806D50FC));
                }
            }
        } else {
            if (c->pos[i].x < lbl_806D5108) {
                c->gone[i] = 1;
            }
            if (c->pos[i].y < lbl_806D510C) {
                c->gone[i] = 1;
            }
            if (lbl_806D5110 < c->pos[i].x) {
                c->gone[i] = 1;
            }
            if (lbl_806D5114 < c->pos[i].y) {
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
            SoundMgr_StopSE_OrSpecial(0xCD);
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
