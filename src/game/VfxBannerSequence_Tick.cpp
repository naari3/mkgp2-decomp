/* VfxBannerSequence_Tick (0x800B08FC): plays the 68-frame banner flipbook
 * (lbl_803297E0) from frame 82 on, preloading two frames ahead and
 * releasing the previous one, then fades in a full-screen overlay after
 * frame 110 and tears both sprites down after frame 190. */
extern "C" {
#include "game/DrawEffectAccess.h"
}

struct ResCtrl {
    void *resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    int tail[5];
    ResCtrl();
    ~ResCtrl() {}
};

extern "C" {
extern const float lbl_806D5020; /* 320.0 */
extern const float lbl_806D5024; /* 240.0 */
extern const float lbl_806D5028; /* 1.0 */
extern const float lbl_806D502C; /* 640.0 */
extern const float lbl_806D5030; /* 480.0 */
extern const float lbl_806D5034; /* 0.0 */
extern const float lbl_806D503C; /* 255.0 */
extern const float lbl_806D5040; /* 2.0 */
extern const float lbl_806D5044; /* 0.1 */
extern void *lbl_803297E0[68];
void fn_80121E10(ResCtrl *rc);
void *SpriteHandle_CreateDefault(ResCtrl *rc, int layer);
void SpriteHandle_SetActiveFlag(void *h, int on);
void SpriteLayer_SetResource(void *h, void *res);
void SpriteHandle_RecomputeCull(void *h);
void SpriteHandle_SetCornerAlpha(void *h, unsigned char alpha);
void SpriteHandle_Destroy(void *h);
void PreloadResource(void *res);
void fn_80120A08(void *res);
}

extern "C" void VfxBannerSequence_Tick(unsigned char *self)
{
    switch (STATE) {
    case 0: {
        {
        ResCtrl banner;

        fn_80121E10(&banner);
        banner.resId = lbl_803297E0[0];
        banner.flag = 1;
        banner.x = lbl_806D5020;
        banner.y = lbl_806D5024;
        banner.z = lbl_806D5028;
        banner.scaleX = 2.0f;
        banner.scaleY = 2.0f;
        banner.tail[1] = 1;
        banner.tail[2] = 4;
        banner.tail[3] = 1;
        P(0x170) = (unsigned char *)SpriteHandle_CreateDefault(&banner, 6);
        SpriteHandle_SetActiveFlag(P(0x170), 0);
        }
        {
        ResCtrl overlay;
        fn_80121E10(&overlay);
        overlay.mode = 2;
        overlay.flag = 1;
        overlay.x = lbl_806D5020;
        overlay.y = lbl_806D5024;
        overlay.z = lbl_806D5028;
        overlay.width = lbl_806D502C;
        overlay.height = lbl_806D5030;
        overlay.colors[0] = 0;
        overlay.colors[1] = 0;
        overlay.colors[2] = 0;
        overlay.colors[3] = 0;
        P(0x174) = (unsigned char *)SpriteHandle_CreateDefault(&overlay, 0);
        SpriteHandle_SetActiveFlag(P(0x174), 0);
        }

        F(0x150) = lbl_806D5034;
        U32(0x180) = 0;
        STATE++;
    }
    case 1: {
        int frame;
        int ahead;
        int behind;

        U32(0x180)++;
        frame = U32(0x180) - 82;
        ahead = frame + 2;
        behind = frame - 1;
        if (frame >= 0 && frame < 68) {
            SpriteLayer_SetResource(P(0x170), lbl_803297E0[frame]);
            SpriteHandle_SetActiveFlag(P(0x170), 1);
            SpriteHandle_RecomputeCull(P(0x170));
        } else {
            SpriteHandle_SetActiveFlag(P(0x170), 0);
        }
        if (ahead >= 0 && ahead < 68) {
            PreloadResource(lbl_803297E0[ahead]);
        }
        if (behind >= 0 && behind < 68) {
            fn_80120A08(lbl_803297E0[behind]);
        }
        if (U32(0x180) > 110) {
            F(0x150) += lbl_806D5044;
            if (1.0f < F(0x150)) {
                F(0x150) = 1.0f;
            }
            SpriteHandle_SetCornerAlpha(P(0x174), (unsigned char)(int)(lbl_806D503C * F(0x150)));
            SpriteHandle_SetActiveFlag(P(0x174), 1);
            SpriteHandle_RecomputeCull(P(0x174));
        }
        if (U32(0x180) > 190) {
            SpriteHandle_Destroy(P(0x170));
            SpriteHandle_Destroy(P(0x174));
            DrawEffect_Free(self);
        }
        break;
    }
    }
}
