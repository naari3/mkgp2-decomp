/* clFlowChara_HandleConfirm (0x801C393C): character select confirm; picks the next flow state. */

typedef struct {
    char pad00[0x4];
    int visualIdx;
    char pad08[0x60 - 0x8];
    int next;
    char pad64[0x68 - 0x64];
    int cursor;
    float timer;
    char pad70[0xA8 - 0x70];
    int locked[1];
} clFlowChara;

extern const float lbl_806D9B90;
extern const float FLOAT_SPRITE_INIT_TIME;
extern const float FLOAT_BRIGHTNESS_DARK;
extern char *g_pInputState;
extern int g_characterId;
extern int g_gameMode;
extern unsigned char g_playerData[];
extern void *GetInputManager(void);
extern void InputMgr_GetPlayer(void *mgr, int idx);
extern void SetRumbleMode(int a, int b, int c);
extern int GetFrameIdxFromVisualIdx(clFlowChara *self, int idx);
extern void SetKartVariant(int v);
extern void fn_801B7B64(int chara);
extern void SetScreenBrightness(float b);

#pragma exceptions on
int clFlowChara_HandleConfirm(clFlowChara *self) {
    char *input;
    unsigned char *pd;
    unsigned char flag;

    if (self->next != -1) {
        return self->next;
    }
    self->timer -= lbl_806D9B90;
    InputMgr_GetPlayer(GetInputManager(), 0);
    if ((input = g_pInputState) == 0) {
        input = 0;
    }
    if (*(int *)(input + 0x18) == 1 || self->timer < FLOAT_SPRITE_INIT_TIME) {
        SetRumbleMode(0, 1, 1);
        pd = g_playerData;
        g_characterId = GetFrameIdxFromVisualIdx(self, self->visualIdx);
        if (self->locked[self->cursor] >= 1) {
            SetKartVariant(2);
            self->next = 0xF;
        } else {
            SetKartVariant(0);
            flag = 0;
            if (g_gameMode != 2) {
                if (pd[0x19F] == 0) {
                    flag = 1;
                }
                if (pd[0x19D] == 1) {
                    flag = 1;
                }
            } else {
                flag = 1;
            }
            if (!flag) {
                if (g_gameMode == 0) {
                    self->next = 0x15;
                } else {
                    self->next = 0x17;
                }
            } else {
                self->next = 0x13;
            }
        }
        self->timer = FLOAT_BRIGHTNESS_DARK;
        fn_801B7B64(g_characterId);
    }
    SetScreenBrightness(self->timer);
    return self->next;
}
#pragma exceptions reset
