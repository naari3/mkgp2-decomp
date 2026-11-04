#ifndef GAME_PALETTEBUFFERCTORPRIVATE_H
#define GAME_PALETTEBUFFERCTORPRIVATE_H
struct TextureHeader { unsigned short height,width; };
struct PaletteEntryView { TextureHeader *texture; void *clut; };
struct PaletteView { int unused; int count; };
struct PaletteTextureView {
    char texture[0x20];
    char clut[0xC];
    unsigned short x,y,width,height;
    float u0,v0,u1,v1;
};
extern "C" {
extern void *lbl_804E5508[], *lbl_804E54FC[];
void TEXLoadPalette_Retry(PaletteView **,const char *);
void *FUN_8003b120(unsigned long);
PaletteEntryView *TEXGetPaletteEntry(PaletteView *,int);
void TEXBindPaletteEntry_CI(PaletteView *,void *,void *,int,int);
void TEXBindPaletteEntry_RGB(PaletteView *,void *,int);
extern const float lbl_806DA6C4,lbl_806DA708;
}
struct PaletteRef {
    void *vt;
    PaletteView *palette;
    int refs;
    PaletteRef(const char *name) : vt(lbl_804E5508), palette(0), refs(1) { TEXLoadPalette_Retry(&palette,name); }
    ~PaletteRef();
};
struct PaletteBuffer : PaletteRef {
    int count;
    PaletteTextureView *data;
    PaletteBuffer(const char *name);
};
#endif
