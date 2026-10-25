typedef struct GXColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GXColor;

extern const GXColor lbl_806D28C0;
extern const GXColor lbl_806D28C4;
extern void GXSetTevOrder(int stage, int coord, int map, int color);
extern void GXSetTevColor(int reg, GXColor color);
extern void GXSetTevColorIn(int stage, int a, int b, int c, int d);
extern void GXSetTevColorOp(int stage, int op, int bias, int scale, unsigned char clamp, int reg);

void KartItem_RenderCb_Mode7_Post(int stage) {
    GXColor color2;

    GXSetTevOrder(stage, 0xFF, 0x100, 6);
    color2 = lbl_806D28C4;
    GXSetTevColor(1, lbl_806D28C0);
    GXSetTevColor(2, color2);
    GXSetTevColorIn(stage, 0, 2, 4, 0xF);
    GXSetTevColorOp(stage, 0, 0, 0, 1, 0);
}
