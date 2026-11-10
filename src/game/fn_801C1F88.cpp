#include "game/FlowScene.h"
struct ClassExit {
    void *vt;
    unsigned char flag4, extraMode;
    char pad6[2];
    int state, cursor, field10, field14, handle18, handle1C;
    float brightness;
    int field24, next;
    void *help, *items[3], *title;
};
#include "game/types/AnimIds.h"
extern "C" {
extern AnimIds lbl_8039AA08, lbl_8039AA14;
extern const float lbl_806D9AF0, lbl_806D9AF4, lbl_806D9AF8;
extern int g_ccClass, g_gameMode;
extern signed char lbl_806D184C;
void *GetInputManager();
void *InputMgr_GetPlayer(void *, int);
void SetRumbleMode(int, int, int);
void Sprite_SetupAnim(void *, int, int, int);
void SpriteHandle_Destroy(int);
void Sprite_Destroy(void *, int);
void fn_801B7C64();
void SetScreenBrightness(float);
int fn_801C1F88(ClassExit *self) {
    AnimIds selected = lbl_8039AA08;
    AnimIds normal = lbl_8039AA14;
    if (self->next != -1) return self->next;
    self->brightness -= lbl_806D9AF0;
    InputMgr_GetPlayer(GetInputManager(), 0);
    if (GetInput()->held == 1 || self->brightness < lbl_806D9AF4) {
        SetRumbleMode(0, 1, 1);
        if (GetInput()) {
            InputState *input = GetInput();
            input->enabled = 0;
            input->held = 0;
            input->edge = 0;
        }
        if (self->cursor == 0) g_ccClass = 0;
        if (self->cursor == 1) g_ccClass = 1;
        if (self->cursor == 2) g_ccClass = 2;
        if (g_gameMode != 2) {
            g_gameMode = self->extraMode != 0;
            self->next = 13;
            self->state = 3;
            for (int i = 0; i < 3; i++) {
                if (self->items[i]) {
                    if (i == self->cursor) Sprite_SetupAnim(self->items[i], selected.values[i], 1, 0);
                    else Sprite_SetupAnim(self->items[i], normal.values[i], 1, 0);
                }
            }
        } else {
            self->next = 12;
            self->field14 = 9;
            for (int i = 0; i < 3; i++) {
                if (self->items[i] && i == self->cursor) Sprite_SetupAnim(self->items[i], selected.values[i], 1, 0);
            }
        }
        if (self->handle18) SpriteHandle_Destroy(self->handle18);
        if (self->handle1C) SpriteHandle_Destroy(self->handle1C);
        if (self->title) Sprite_SetupAnim(self->title, 0x45, 1, 0);
        Sprite_Destroy(self->help, 1);
        self->help = 0;
        self->handle18 = 0;
        self->handle1C = 0;
        self->brightness = lbl_806D9AF8;
        lbl_806D184C = -1;
        fn_801B7C64();
    }
    SetScreenBrightness(self->brightness);
    return self->next;
}
}
