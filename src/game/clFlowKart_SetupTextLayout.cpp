struct Vec2 {
    float x, y;
};
static inline Vec2 operator+(const Vec2 &a, const Vec2 &b)
{
    Vec2 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}
struct TextManager;
struct KartEntry {
    char data[0x1C];
};
struct FlowKartView {
    char pad0[4];
    int kind;
    char pad8[0x38];
    int otherKind;
    char pad44[0x18];
    TextManager *texts[3];
};
extern "C" {
extern KartEntry *lbl_806CFED0[2];
extern Vec2 lbl_8039FC60[];
extern const float lbl_806DA1C8;
int isJapanese(void);
unsigned char fn_801D92D0(FlowKartView *self, KartEntry *e);
void fn_801F93EC(TextManager *tm, float x, float y);
void fn_801F93D0(TextManager *tm, float x, float y);
}

extern "C" void clFlowKart_SetupTextLayout(FlowKartView *self, int kind)
{
    if (fn_801D92D0(self, &lbl_806CFED0[isJapanese()][kind]) == 1) {
        self->kind = kind;
    } else {
        self->otherKind = kind;
    }
    if (isJapanese() == 1 && self->kind == 8) {
        Vec2 p;
        p = lbl_8039FC60[0] + lbl_8039FC60[4];
        fn_801F93EC(self->texts[0], p.x - lbl_806DA1C8, p.y);
        p = lbl_8039FC60[0] + lbl_8039FC60[5];
        fn_801F93EC(self->texts[1], p.x - lbl_806DA1C8, p.y);
        p = lbl_8039FC60[0] + lbl_8039FC60[6];
        fn_801F93EC(self->texts[2], p.x - lbl_806DA1C8, p.y);
        for (int i = 0; i < 3; i++) {
            fn_801F93D0(self->texts[i], 0.7f, 0.7f);
        }
    }
}
