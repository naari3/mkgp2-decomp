#ifndef DRAW_SETUP_801F_H
#define DRAW_SETUP_801F_H
/* Minimal GX ABI declarations: the SDK umbrella includes unavailable stdarg.h. */
extern void GXSetNumTexGens(unsigned char);
extern void GXSetTexCoordGen2(int,int,int,unsigned long,unsigned char,unsigned long);
extern void GXSetNumChans(unsigned char);
extern void GXSetNumTevStages(unsigned char);
extern void GXSetTevOrder(int,int,int,int);
extern void GXSetTevOp(int,int);
extern void GXSetTevColorIn(int,int,int,int,int);
extern void GXSetTevColorOp(int,int,int,int,unsigned char,int);
extern void GXSetTevAlphaIn(int,int,int,int,int);
extern void GXSetTevAlphaOp(int,int,int,int,unsigned char,int);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDescv(const void *);
extern void GXSetVtxAttrFmtv(int,const void *);
typedef struct DrawSetup801F {
    void *vtable;
    void *description;
    unsigned char depth;
    unsigned char pad[3];
    int mode;
} DrawSetup801F;
typedef struct DrawAttr801F { int attr, count, type; unsigned char frac, pad[3]; } DrawAttr801F;
typedef struct DrawTables801F {
    unsigned char colorDesc[0x20];
    unsigned char colorFmt[0x40];
    unsigned char colorDepthFmt[0x40];
    unsigned char textureDesc[0x20];
    unsigned char textureFmt[0x40];
    unsigned char textureDepthFmt[0x40];
    unsigned char mixedDesc[0x20];
    DrawAttr801F mixedFmt[8];
    DrawAttr801F mixedDepthFmt[8];
} DrawTables801F;
extern const DrawTables801F lbl_803BEDC0;
#endif
