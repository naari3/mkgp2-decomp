typedef struct GXColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GXColor;

extern const GXColor lbl_806D28C0;
extern const GXColor lbl_806D28C4;
extern void GX_SetTevOrder(int stage, int coord, int map, int color);
extern void fn_80269230(int reg, GXColor color);
extern void fn_802690D8(int stage, int a, int b, int c, int d);
extern void fn_80269160(int stage, int op, int bias, int scale, unsigned char clamp, int reg);

void KartItem_RenderCb_Mode7_Post(int stage) {
    GXColor color2;

    GX_SetTevOrder(stage, 0xFF, 0x100, 6);
    color2 = lbl_806D28C4;
    fn_80269230(1, lbl_806D28C0);
    fn_80269230(2, color2);
    fn_802690D8(stage, 0, 2, 4, 0xF);
    fn_80269160(stage, 0, 0, 0, 1, 0);
}
