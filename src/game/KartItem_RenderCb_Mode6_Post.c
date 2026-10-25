typedef struct GXColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GXColor;

extern const GXColor lbl_806D28B0;
extern void GXSetTevOrder(int stage, int coord, int map, int color);
extern void GXSetTevColor(int reg, GXColor color);
extern void GXSetTevColorIn(int stage, int a, int b, int c, int d);
extern void GXSetTevColorOp(int stage, int op, int bias, int scale, unsigned char clamp, int reg);

void KartItem_RenderCb_Mode6_Post(int stage) {
    GXSetTevOrder(stage, 0xFF, 0x100, 6);
    GXSetTevColor(1, lbl_806D28B0);
    GXSetTevColorIn(stage, 0, 0xF, 0xF, 2);
    GXSetTevColorOp(stage, 0, 0, 0, 1, 0);
}
