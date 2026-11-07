/*
 * 0x802124FC..0x802128F4: JumpDistanceMode landing grid animation.
 */

#include "game/JumpDistanceMode.h"

extern "C" {
void *memcpy(void *dst, const void *src, unsigned long n);
unsigned char IsCardValid(void);
float Cosf_LUT_Wrap(float x);
float LUT_Sin12Bit(float x);
void fn_8016C3C8(int se, int a);
void SoundMgr_PlaySE(int se);
extern const float lbl_80495994[64];
extern const float lbl_806DAD70;
extern const float lbl_806DAD84;
extern const float lbl_806DAD8C;
extern const float lbl_806DADB4;
extern const float lbl_806DADDC;
extern const float lbl_806DADF8;
extern const float lbl_806DADFC;
extern const float lbl_806DAE00;
extern const float lbl_806DAE04;
}

static inline void TickSlot(GridSlot *s, float rise) {
    if (s->age >= 0) {
        s->y += rise;
        if (++s->age >= 10) {
            s->age = -1;
        }
    }
}

extern "C" void fn_802124FC(LandingGrid *g) {
    if (IsCardValid()) {
        float rise = lbl_806DADF8;
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 5; j++) {
                TickSlot(&g->cells[i].slots[j], rise);
            }
            if (g->cells[i].visible > 0) {
                g->cells[i].y -= lbl_806DAD8C * Cosf_LUT_Wrap(lbl_806DADFC * g->cells[i].frame);
                g->cells[i].rot += lbl_806DADDC;
                g->cells[i].alpha = lbl_806DAD70 - g->cells[i].frame / lbl_806DAE00;
                if ((g->cells[i].frame & 3) == 0) {
                    for (int j = 0; j < 5; j++) {
                        if (g->cells[i].slots[j].age < 0) {
                            g->cells[i].slots[j].age = 0;
                            g->cells[i].slots[j].x = lbl_806DADDC * LUT_Sin12Bit(lbl_806DADB4 * lbl_80495994[g->sparkle]) + g->cells[i].x;
                            g->cells[i].slots[j].y = lbl_806DAD84 * LUT_Sin12Bit(lbl_806DADB4 * lbl_80495994[g->sparkle]) + g->cells[i].y;
                            if (++g->sparkle >= 64) {
                                g->sparkle = 0;
                            }
                            break;
                        }
                    }
                }
                if (g->cells[i].frame >= 50) {
                    g->cells2[i].visible = 1;
                    g->cells[i].visible = 0;
                }
                if (g->cells[i].frame < 300) {
                    g->cells[i].frame++;
                }
            }
            if (g->cells2[i].visible > 0) {
                if (g->cells2[i].frame < 40) {
                    g->cells2[i].alpha = g->cells2[i].frame / lbl_806DAE00;
                }
                g->cells2[i].rot = g->spin;
                if (g->cells2[i].frame < 300) {
                    g->cells2[i].frame++;
                }
            }
        }
        g->spin += 1.0f;
        if (g->spin > 360.0f) {
            g->spin -= 360.0f;
        }
        if (g->pending > 0 && g->delay <= 0) {
            g->cells[g->next].visible = 1;
            g->next++;
            g->pending--;
            g->delay = 10;
            if (fn_8016C360(0xAB) == 1) {
                fn_8016C394(0xAB);
            }
            SoundMgr_PlaySE(0xAB);
        }
        if (g->delay > 0) {
            g->delay--;
        }
    }
}
