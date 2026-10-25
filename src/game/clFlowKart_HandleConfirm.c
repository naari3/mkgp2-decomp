/* clFlowKart_HandleConfirm (0x801D7B50): kart select confirm; sets the kart variant and next flow state. */

typedef struct {
    char pad00[0x4];
    int cursor;
    int next;
    char pad0C[0x18 - 0xC];
    float timer;
} clFlowKart;

extern const float lbl_806DA13C;
extern const float lbl_806DA140;
extern const float lbl_806DA144;
extern char *g_pInputState;
extern int g_characterId;
extern int g_gameMode;
extern unsigned char g_playerData[];
extern int g_kartEnhancedUnlockThreshold[];
extern void *GetInputManager(void);
extern void InputMgr_GetPlayer(void *mgr, int idx);
extern void SetRumbleMode(int a, int b, int c);
extern int GetCoinMilage(void *pd);
extern void SetKartVariant(int v);
extern void fn_801B7C64(void);
extern void SetScreenBrightness(float b);

#pragma exceptions on
int clFlowKart_HandleConfirm(clFlowKart *self) {
    char *input;
    unsigned char *pd;
    unsigned char flag;

    if (self->next != -1) {
        return self->next;
    }
    self->timer -= lbl_806DA140;
    InputMgr_GetPlayer(GetInputManager(), 0);
    if ((input = g_pInputState) == 0) {
        input = 0;
    }
    if (*(int *)(input + 0x18) == 1 || self->timer < lbl_806DA13C) {
        SetRumbleMode(0, 1, 1);
        if (self->cursor == 0) {
            SetKartVariant(0);
        } else {
            int chara = g_characterId;
            if (GetCoinMilage(g_playerData) >= g_kartEnhancedUnlockThreshold[chara]) {
                SetKartVariant(3);
            } else {
                SetKartVariant(2);
            }
        }
        pd = g_playerData;
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
        self->timer = lbl_806DA144;
        fn_801B7C64();
    }
    SetScreenBrightness(self->timer);
    return self->next;
}
#pragma exceptions reset
