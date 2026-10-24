typedef struct GXColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GXColor;

extern const GXColor lbl_806D28B4;
extern void GX_SetTevOrder(int stage, int coord, int map, int color);
extern void fn_80269230(int reg, GXColor color);
extern void fn_802690D8(int stage, int a, int b, int c, int d);
extern void fn_80269160(int stage, int op, int bias, int scale, unsigned char clamp, int reg);

void KartItem_RenderCb_Mode5_Post(int stage) {
    GX_SetTevOrder(stage, 0xFF, 0x100, 6);
    fn_80269230(1, lbl_806D28B4);
    fn_802690D8(stage, 0, 0xF, 0xF, 2);
    fn_80269160(stage, 0, 0, 0, 1, 0);
}
