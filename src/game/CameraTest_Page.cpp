/*
 * CameraTest_Page @ 0x8007044C..0x80070EA8: the camera test page. Owns a
 * NamCam capture object (lbl_806D1104) whose image is drawn in a frame by
 * FlashFadeOverlay_Draw; the operator toggles mirror/photo mode and moves
 * the image offset (data+0x48, data+0x4C). NonMatching: the phase-0 delete
 * loads lbl_806D1104 into r3 and copies it to r30 instead of loading r30.
 */
#include "game/TestMenuPage.h"

extern "C" {
extern MenuItem lbl_803FC768[];
extern const char lbl_806D2CF8[7];
extern const char lbl_806D2D00[6];
extern const char lbl_806D2D64[3];
extern const char lbl_806D2D68[5];
extern void *lbl_806D1100;
void *Alloc(unsigned long size);
void MemoryManager_Free(void *p);
void MemoryManager_TimedFree(void *p);
void *FUN_8003b120(int size);
unsigned char GetVBlankFlag(void);
void NamCam_Init(void);
void NamCam_End(void);
int NamCam_GetImageHandle(void *out, int arg);
void NamCam_LoadImage(void *handle, void *buf, void *out);
void *StrPcb_GetInstance(void);
unsigned char StrPcb_IsInErrorState(void *pcb);
void Backup_PublishShadowCopy_Inline(void);
int MonitorTest_Page(TestPage *self, int phase, int arg);
void fn_801A1280(void);
void Sprite_AdvanceAnim(void *sprite, float dt);
void fn_801A0004(void *sprite);
void fn_8011FA98(void);
void SpriteHandlePool_GC(void);
}

class CameraImage {
public:
    CameraImage()
    {
        active = 0;
        loaded = 0;
        buf = 0;
        buf = FUN_8003b120(0x4B000);
    }
    ~CameraImage()
    {
        MemoryManager_Free(buf);
        if (GetVBlankFlag()) {
            Stop();
            buf = 0;
        }
    }
    void Stop()
    {
        if (GetVBlankFlag() && active) {
            active = 0;
            NamCam_End();
        }
    }
    void Start()
    {
        if (GetVBlankFlag()) {
            if (active == 1) {
                Stop();
            }
            active = 1;
            loaded = 0;
            NamCam_Init();
        }
    }

    unsigned char active;
    unsigned char loaded;
    void *buf;
};

extern "C" void FlashFadeOverlay_Draw(CameraImage *img, float x0, float y0, float x1, float y1, float dx, float dy);

extern "C" {
extern CameraImage *lbl_806D1104;
}

static inline void DestroyImage(void)
{
    CameraImage *p = lbl_806D1104;
    if (p != 0) {
        delete p;
        lbl_806D1104 = 0;
    }
}

#define TIMER(self) (*(int *)((char *)(self) + 0x20))
#define OFS_X(self) (*(int *)((char *)(self)->data + 0x48))
#define OFS_Y(self) (*(int *)((char *)(self)->data + 0x4C))

#pragma exceptions on

extern "C" int CameraTest_Page(TestPage *self, int phase)
{
    char *pool = lbl_8030E598;
    CameraImage *img;
    InputPlayer *pl;

    if (phase == 0) {
        self->cursor = 2;
        self->sub = 0;
        TIMER(self) = -1;
        DestroyImage();
    }
    if (phase == 1) {
        if (!StrPcb_IsInErrorState(StrPcb_GetInstance())) {
            return 1;
        }
        img = lbl_806D1104;
        if (img == 0) {
            img = new CameraImage;
            lbl_806D1104 = img;
            img->Start();
        } else if (self->sub == 0) {
            if (GetVBlankFlag() && img->active) {
                void *handle;
                char info[0x10];
                if (NamCam_GetImageHandle(&handle, 0) == 1) {
                    NamCam_LoadImage(handle, img->buf, info);
                    img->loaded = 1;
                }
            }
        } else {
            if (GetVBlankFlag() && img->active) {
                void *handle;
                NamCam_GetImageHandle(&handle, 0);
            }
        }
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (pl->Pressed(0x2000)) {
            if (self->sub == 0) {
                self->sub = 1;
            } else {
                self->sub = 0;
            }
        }
        if (TIMER(self) == -1) {
            if (pl->Pressed(0x800)) {
                self->blink = 0x1F;
                if (++self->cursor > 2) {
                    self->cursor = 0;
                }
            }
            if (pl->Pressed(0x1000)) {
                if (self->cursor == 0 || self->cursor == 1) {
                    TIMER(self) = 0;
                }
                if (self->cursor == 2) {
                    DestroyImage();
                    Backup_PublishShadowCopy_Inline();
                    self->next = 2;
                    MonitorTest_Page(self, 0, 3);
                }
            }
        } else {
            if (pl->Pressed(0x1000)) {
                self->blink = 0x1F;
                if (++TIMER(self) >= 2) {
                    TIMER(self) = -1;
                }
            }
            if (pl->Pressed(0x800)) {
                if (self->cursor == 0) {
                    if (TIMER(self) == 0) {
                        if (--OFS_X(self) < -12) {
                            OFS_X(self) = -12;
                        }
                    } else {
                        if (++OFS_X(self) > 12) {
                            OFS_X(self) = 12;
                        }
                    }
                } else {
                    if (TIMER(self) == 0) {
                        if (--OFS_Y(self) < -16) {
                            OFS_Y(self) = -16;
                        }
                    } else {
                        if (++OFS_Y(self) > 16) {
                            OFS_Y(self) = 16;
                        }
                    }
                }
            }
        }
    }
    if (phase == 2 && self->text != 0) {
        if (!StrPcb_IsInErrorState(StrPcb_GetInstance())) {
            if (self->blink <= 0x1E) {
                DrawText(self->text, 0x7E, 0xD8, 7, 1.0f, pool + 0x24C4);
            }
        } else {
            const char *modes[2] = { lbl_806D2CF8, lbl_806D2D00 };
            unsigned char colX;
            unsigned char colY;

            TestPage_DrawItems(self, lbl_803FC768, -1);
            DrawText(self->text, 0x118, 0x108, 7, 1.0f, lbl_806D2D64, modes[self->sub]);
            colX = 2;
            colY = 2;
            if (OFS_X(self) != 12) {
                colX = 4;
            }
            if (OFS_Y(self) != -16) {
                colY = 4;
            }
            if (TIMER(self) == -1) {
                if (self->cursor != 0) {
                    DrawText(self->text, 0x2A, 0x150, 7, 1.0f, pool + 0x24E0);
                } else if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x2A, 0x150, 7, 1.0f, pool + 0x24E0);
                }
                DrawText(self->text, 0x2A, 0x150, 7, 1.0f, pool + 0x24EC);
                DrawText(self->text, 0x2A, 0x150, colX, 1.0f, pool + 0x2514, -OFS_X(self));
                if (self->cursor != 1) {
                    DrawText(self->text, 0x2A, 0x168, 7, 1.0f, pool + 0x253C);
                } else if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x2A, 0x168, 7, 1.0f, pool + 0x253C);
                }
                DrawText(self->text, 0x2A, 0x168, 7, 1.0f, pool + 0x2548);
                DrawText(self->text, 0x2A, 0x168, colY, 1.0f, pool + 0x2514, OFS_Y(self));
                if (self->cursor != 2) {
                    DrawText(self->text, 0x2A, 0x180, 7, 1.0f, lbl_806D2D68);
                } else if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x2A, 0x180, 7, 1.0f, lbl_806D2D68);
                }
            } else {
                DrawText(self->text, 0x2A, 0x150, 7, 1.0f, pool + 0x2570);
                if (self->cursor != 0) {
                    DrawText(self->text, 0x2A, 0x150, 7, 1.0f, pool + 0x2598);
                } else {
                    if (TIMER(self) != 0) {
                        DrawText(self->text, 0x2A, 0x150, 7, 1.0f, pool + 0x25B4);
                    } else if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x150, 7, 1.0f, pool + 0x25B4);
                    }
                    if (TIMER(self) != 1) {
                        DrawText(self->text, 0x2A, 0x150, 7, 1.0f, pool + 0x25C8);
                    } else if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x150, 7, 1.0f, pool + 0x25C8);
                    }
                }
                DrawText(self->text, 0x2A, 0x150, colX, 1.0f, pool + 0x2514, -OFS_X(self));
                DrawText(self->text, 0x2A, 0x168, 7, 1.0f, pool + 0x25E4);
                if (self->cursor != 1) {
                    DrawText(self->text, 0x2A, 0x168, 7, 1.0f, pool + 0x260C);
                } else {
                    if (TIMER(self) != 0) {
                        DrawText(self->text, 0x2A, 0x168, 7, 1.0f, pool + 0x2628);
                    } else if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x168, 7, 1.0f, pool + 0x2628);
                    }
                    if (TIMER(self) != 1) {
                        DrawText(self->text, 0x2A, 0x168, 7, 1.0f, pool + 0x2640);
                    } else if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x168, 7, 1.0f, pool + 0x2640);
                    }
                }
                DrawText(self->text, 0x2A, 0x168, colY, 1.0f, pool + 0x2514, OFS_Y(self));
                DrawText(self->text, 0x2A, 0x180, 7, 1.0f, lbl_806D2D68);
            }
            if (lbl_806D1104 != 0) {
                FlashFadeOverlay_Draw(lbl_806D1104, 98.0f, 2.0f, 542.0f, 286.0f,
                                      (float)OFS_Y(self), (float)OFS_X(self));
                fn_801A1280();
                Sprite_AdvanceAnim(lbl_806D1100, 0.0165f);
                fn_801A0004(lbl_806D1100);
                fn_8011FA98();
                SpriteHandlePool_GC();
            }
        }
    }
    return 1;
}

#pragma exceptions reset
