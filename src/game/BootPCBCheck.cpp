/* Boot-time PCB link check screen, 0x80084A84..0x80084D98. */

struct BootInput {
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual bool IsPressed(int mask);
};

typedef struct {
    unsigned char disabled : 1;
    unsigned char unused6 : 1;
    unsigned char ready : 1;
    unsigned char flag4 : 1;
    unsigned char unusedLow : 4;
} ReadyFlags;

typedef struct PcbSlot {
    unsigned char pad_00[0xA2C];
    void *primary;
    void *secondary;
    ReadyFlags flags;
    unsigned char pad_A35[7];
} PcbSlot;

extern "C" {
extern PcbSlot lbl_805A6154[4];
extern void *lbl_806D11B8;
extern int lbl_806D11BC;
extern const float lbl_806D315C;
extern const char lbl_80312244[];
extern const char lbl_80312254[];
extern const char lbl_806D3170[5];
extern const char lbl_806D3178[5];
void DrawText(void *ctx, int x, int y, int color, float scale, const char *fmt, ...);
void DisplayContext_Flush(void *ctx);
void *GetInputManager();
BootInput *InputMgr_GetPlayer(void *, int);
}

extern "C" int BootPCBCheck_Display(void)
{
    int i;

    if (lbl_806D11B8 == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_805A6154[i].flags.disabled == 1) {
            DrawText(lbl_806D11B8, 0x54, (i + 1) * 0x18, 7, lbl_806D315C, lbl_80312244, i + 1);
        } else if (lbl_805A6154[i].primary != 0 && lbl_805A6154[i].secondary != 0) {
            DrawText(lbl_806D11B8, 0x54, (i + 1) * 0x18, 7, lbl_806D315C, lbl_80312244, i + 1);
        } else {
            DrawText(lbl_806D11B8, 0x54, (i + 1) * 0x18, 7, lbl_806D315C, lbl_80312254, i + 1);
        }
    }
    DrawText(lbl_806D11B8, 0xE, 0x18, 7, lbl_806D315C, lbl_806D3170);
    DrawText(lbl_806D11B8, 0x24C, 0x18, 7, lbl_806D315C, lbl_806D3178, lbl_806D11BC / 60);
    DisplayContext_Flush(lbl_806D11B8);
    return 1;
}

extern "C" int BootPCBCheck_Poll(void)
{
    BootInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    int n = 0;
    int i;

    if (lbl_806D11B8 == 0) {
        return 0;
    }
    if (lbl_806D11BC <= 0) {
        return 0;
    }
    lbl_806D11BC--;
    for (i = 0; i < 4; i++) {
        if (lbl_805A6154[i].flags.disabled == 1) {
            n++;
        } else if (lbl_805A6154[i].flags.ready == 1 && lbl_805A6154[i].flags.flag4 == 1) {
            n++;
        }
    }
    if (n == 4) {
        lbl_806D11BC = 0;
    }
    if (input->IsPressed(0x2000) && input->IsPressed(0x400)) {
        lbl_806D11BC = 0;
    }
    return 1;
}
