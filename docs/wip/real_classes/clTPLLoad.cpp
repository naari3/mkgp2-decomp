/* clTPLexp: a counted handle on a loaded TPL palette. clTPLLoad: the same
 * plus one texture descriptor per palette entry, with half-texel UV bounds.
 * 0x801F6860..0x801F6BD0. */
#include "game/types/size_t.h"
void *operator new[](size_t);
void operator delete(void *);
void operator delete[](void *);
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
void TEXLoadPalette_Retry(PaletteView **,const char *);
void TEXReleasePalette(void **palette);
void *FUN_8003b120(unsigned long);
PaletteEntryView *TEXGetPaletteEntry(PaletteView *,int);
void TEXBindPaletteEntry_CI(PaletteView *,void *,void *,int,int);
void TEXBindPaletteEntry_RGB(PaletteView *,void *,int);
extern const float lbl_806DA6C4,lbl_806DA708;
}
class clTPLexp {
public:
    /* the destructor is declared first so that the vtable pointer is at 0 */
    virtual ~clTPLexp();
    PaletteView *palette;
    int refs;
    int count; /* set before clTPLLoad's vtable pointer is stored, so it is the base's */
    clTPLexp(const char *name) : palette(0), refs(1) {
        TEXLoadPalette_Retry(&palette, name);
        count = palette->count;
    }
};
clTPLexp::~clTPLexp() {
    refs--;
    if (refs <= 0 && palette != 0) {
        TEXReleasePalette((void **)&palette);
        palette = 0;
    }
}
class clTPLLoad : public clTPLexp {
public:
    PaletteTextureView *data;
    clTPLLoad(const char *name);
    clTPLLoad(const char *name, int first);
    virtual ~clTPLLoad();
};

/* Deferred code generation: the functions are in reverse address order. */
clTPLLoad::clTPLLoad(const char *name) : clTPLexp(name) {
    data=0;
    int i;
    PaletteView *pal=palette;
    int num=count;
    PaletteTextureView *out;
    data=(PaletteTextureView *)FUN_8003b120(num*sizeof(PaletteTextureView));
    out=data;
    for(i=0;i<num;i++,out++) {
        PaletteEntryView *entry=TEXGetPaletteEntry(pal,i);
        if(entry->clut) TEXBindPaletteEntry_CI(pal,out,out->clut,0,i);
        else TEXBindPaletteEntry_RGB(pal,out,i);
        out->x=0; out->y=0;
        out->width=entry->texture->width;
        out->height=entry->texture->height;
        float invH;
        float invW=lbl_806DA6C4/(float)out->width;
        invH=lbl_806DA6C4/(float)out->height;
        float u0=lbl_806DA708+out->x;
        u0 *= invW;
        out->u0=u0;
        out->u1=invW*((float)out->x+out->width-lbl_806DA708);
        float v0=lbl_806DA708+out->y;
        v0 *= invH;
        out->v0=v0;
        out->v1=invH*((float)out->y+out->height-lbl_806DA708);
    }
}

clTPLLoad::~clTPLLoad() {
    if (data != 0) {
        delete[] data;
        data = 0;
    }
}

clTPLLoad::clTPLLoad(const char *name, int first) : clTPLexp(name) {
    data = 0;
    data = (PaletteTextureView *)FUN_8003b120(count * sizeof(PaletteTextureView));
    TEXBindPaletteEntry_RGB(palette, data, first);
}
